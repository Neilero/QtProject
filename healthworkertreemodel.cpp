#include "healthworkertreemodel.h"

#include <QSqlRecord>
#include <QSqlField>
#include <QSqlRecord>
#include <QMap>
#include <QDebug>

HealthWorkerTreeModel::HealthWorkerTreeModel(QObject* parent, QSqlDatabase db)
	: QStandardItemModel(parent)
{
	healthWorkerTableModel = new QSqlTableModel(this, db);
	healthWorkerTableModel->setTable("TRessource");
	healthWorkerTableModel->select();

	healthWorkerTypeTableModel = new QSqlTableModel(this, db);
	healthWorkerTypeTableModel->setTable("TType");
	healthWorkerTypeTableModel->select();

	updateData();
}

QVariant HealthWorkerTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal) {

			if (section == 0 )
				return QString("Personnel de soin");

		}
	}

	return QVariant();
}

QSqlTableModel* HealthWorkerTreeModel::getHealthWorkerTableModel() const
{
	return healthWorkerTableModel;
}

QSqlTableModel* HealthWorkerTreeModel::getHealthWorkerTypeTableModel() const
{
	return healthWorkerTypeTableModel;
}

void HealthWorkerTreeModel::updateData()
{
	//empty all data
	removeRows(0, rowCount());

	QMap<int, QStandardItem*> healthWorkerTypes;

	for (int typeIndex = 0 ; typeIndex < healthWorkerTypeTableModel->rowCount() ; typeIndex++)
	{
		//get healthworker type ID and name
		QSqlRecord healthWorkerTypeRecord = healthWorkerTypeTableModel->record(typeIndex);
		int healthWorkerTypeID = healthWorkerTypeRecord.field(0).value().toInt();
		QString healthWorkerTypeName = healthWorkerTypeRecord.field(1).value().toString();

		//build healthworker type item
		QStandardItem * healthWorkerType = new QStandardItem( healthWorkerTypeName );
		healthWorkerType->setData( healthWorkerTypeID );
		healthWorkerType->setEditable(false);
		healthWorkerType->setSelectable(false);

		//add healthworker type to list of types and to model
		healthWorkerTypes.insert(healthWorkerTypeID, healthWorkerType);
		insertRow(typeIndex, healthWorkerType);
	}

	for (int healthWorkerIndex = 0 ; healthWorkerIndex < healthWorkerTableModel->rowCount() ; healthWorkerIndex++)
	{
		//get healthworker ID, name, lastname, type
		QSqlRecord healthWorkerRecord = healthWorkerTableModel->record(healthWorkerIndex);
		int healthWorkerID = healthWorkerRecord.field(0).value().toInt();
		QString healthWorkerName = healthWorkerRecord.field(1).value().toString();
		QString healthWorkerFirstname = healthWorkerRecord.field(2).value().toString();
		int healthWorkerType = healthWorkerRecord.field(3).value().toInt();

		//check if record has been removed
		if (healthWorkerID == 0){
			continue;
		}

		//build healthworker item
		QStandardItem * healthWorker = new QStandardItem(healthWorkerName + " " + healthWorkerFirstname);
		healthWorker->setData(healthWorkerID);
		healthWorker->setEditable(false);

		//insert healthworker into its type item.
		healthWorkerTypes.value(healthWorkerType)->insertRow(0, healthWorker);
	}
}

bool HealthWorkerTreeModel::deleteHealthWorker(const QModelIndex& indexToDelete)
{
	if (!indexToDelete.isValid())
		return false;

	QStandardItem * itemToDelete = itemFromIndex(indexToDelete);

	bool healthWorkerDeleted = healthWorkerTableModel->removeRow( itemToDelete->data().toInt() -1 );

	if (!healthWorkerDeleted)
		return false;

	healthWorkerDeleted = healthWorkerTableModel->submitAll();

	return healthWorkerDeleted;
}

void HealthWorkerTreeModel::insertHealthWorker(HealthWorker newHealthWorker)
{
	//start a transaction
	healthWorkerTableModel->database().transaction();

	//create an empty record from the model structure
	QSqlRecord healthWorkerLine = healthWorkerTableModel->record();

	//the Id is auto-increment so we don't set it up
	healthWorkerLine.remove( healthWorkerLine.indexOf("Id") );

	//set the other fields of the new patient db line

	healthWorkerLine.setValue("Nom", newHealthWorker.getName());

	healthWorkerLine.setValue("Prenom", newHealthWorker.getFirstname());

	int IdType = static_cast<int>(newHealthWorker.getType());
	healthWorkerLine.setValue("IdType", IdType);

	if (newHealthWorker.getType() == HealthWorkerType::computerScientist) {
		//TODO add login and pass to db
	}

	//try adding the record to the db

	if( healthWorkerTableModel->insertRecord(-1, healthWorkerLine) ){
		//if ok, commit changes
		healthWorkerTableModel->submitAll();
		healthWorkerTableModel->select();

		emit healthWorkerInserted();
	}
	else{
		//else, rollback
		healthWorkerTableModel->database().rollback();
	}
}

void HealthWorkerTreeModel::editHealthWorker(HealthWorker editedHealthWorker, int editedRow)
{
	//start a transaction
	healthWorkerTableModel->database().transaction();

	//set the values of the edited patient to its new ones

	healthWorkerTableModel->setData( index(editedRow, 1), editedHealthWorker.getName() );

	healthWorkerTableModel->setData( index(editedRow, 2), editedHealthWorker.getFirstname() );

	int IdType = static_cast<int>(editedHealthWorker.getType());
	healthWorkerTableModel->setData( index(editedRow, 3), IdType );

	//submit changes
	if (healthWorkerTableModel->submitAll()) {
		emit healthWorkerEdited();
		healthWorkerTableModel->select();
	}
}
