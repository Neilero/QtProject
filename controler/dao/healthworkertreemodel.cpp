#include "healthworkertreemodel.h"

#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include <QMap>
#include <QDebug>

/**
 * @brief Constructor
 * @param the parent of the object
 * @param the database
 */
HealthWorkerTreeModel::HealthWorkerTreeModel(QObject* parent, QSqlDatabase db)
	: QStandardItemModel(parent)
{
	healthWorkerTableModel = new QSqlTableModel(this, db);
	healthWorkerTableModel->setTable("TRessource");
	healthWorkerTableModel->select();

	healthWorkerTypeTableModel = new QSqlTableModel(this, db);
	healthWorkerTypeTableModel->setTable("TType");
	healthWorkerTypeTableModel->select();

	accountTableModel = new QSqlTableModel(this, db);
	accountTableModel->setTable("TCompte");
	accountTableModel->select();

	updateData();
}

/**
 * @brief Return string to set to the header
 * @param the section of the header
 * @param the orientation of the header
 * @param the role role of the header
 * @return
 */
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

/**
 * @brief get the accountTableModel
 * @return the accountTableModel
 */
QSqlTableModel* HealthWorkerTreeModel::getAccountTableModel() const
{
    return accountTableModel;
}

/**
 * @brief get the healthWorkerTableModel
 * @return the healthWorkerTableModel
 */
QSqlTableModel* HealthWorkerTreeModel::getHealthWorkerTableModel() const
{
	return healthWorkerTableModel;
}

/**
 * @brief get the healthWorkerTypeTableModel
 * @return the healthWorkerTypeTableModel
 */
QSqlTableModel* HealthWorkerTreeModel::getHealthWorkerTypeTableModel() const
{
	return healthWorkerTypeTableModel;
}

/**
 * @brief update the datas for the treeModel
 */
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

/**
 * @brief delete a health worker
 * @param index of the health worker to delete
 * @return true if the health worker is deleted
 */
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

/**
 * @brief add a health worker
 * @param the new health worker to ass
 */
void HealthWorkerTreeModel::insertHealthWorker(HealthWorker newHealthWorker)
{
	//start a transaction
	healthWorkerTableModel->database().transaction();

	//create an empty record from the model structure
	QSqlRecord healthWorkerLine = healthWorkerTableModel->record();
	QSqlRecord *accountLine = nullptr;

	//the Id is auto-increment so we don't set it up
	healthWorkerLine.remove( healthWorkerLine.indexOf("Id") );

	//set the other fields of the new patient db line

	healthWorkerLine.setValue("Nom", newHealthWorker.getName());

	healthWorkerLine.setValue("Prenom", newHealthWorker.getFirstname());

	int IdType = static_cast<int>(newHealthWorker.getType());
	healthWorkerLine.setValue("IdType", IdType);

	if (newHealthWorker.getType() == HealthWorkerType::computerScientist) {
		//start a transaction
		accountTableModel->database().transaction();

		//create an empty record from the model structure
		accountLine = new QSqlRecord( accountTableModel->record() );

		//the Id is auto-increment so we don't set it up
		accountLine->remove( accountLine->indexOf("Id") );

		//set the other fields of the new patient db line

		accountLine->setValue("IdRessource", healthWorkerTableModel->rowCount() );

		accountLine->setValue("Login", newHealthWorker.getLogin());

		accountLine->setValue("MdP", newHealthWorker.getPassword());
	}

	//try adding the record(s) to the db
	if (accountLine == nullptr) {
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
	else {
		if( healthWorkerTableModel->insertRecord(-1, healthWorkerLine) && accountTableModel->insertRecord(-1, *accountLine) ){
			//if ok, commit changes
			healthWorkerTableModel->submitAll();
			accountTableModel->submitAll();

			healthWorkerTableModel->select();
			accountTableModel->select();

			emit healthWorkerInserted();
		}
		else{
			//else, rollback
			healthWorkerTableModel->database().rollback();
			accountTableModel->database().rollback();
		}
	}

}

/**
 * @brief edit an existing health worker
 * @param the new health worker
 * @param the line to edit
 */
void HealthWorkerTreeModel::editHealthWorker(HealthWorker editedHealthWorker, int editedRow)
{
	//start a transaction
	healthWorkerTableModel->database().transaction();

	//set the values of the edited patient to its new ones

	healthWorkerTableModel->setData( healthWorkerTableModel->index(editedRow, 1), editedHealthWorker.getName() );

	healthWorkerTableModel->setData( healthWorkerTableModel->index(editedRow, 2), editedHealthWorker.getFirstname() );

	int IdType = static_cast<int>(editedHealthWorker.getType());
	healthWorkerTableModel->setData( healthWorkerTableModel->index(editedRow, 3), IdType );

	if ( editedHealthWorker.getType() == HealthWorkerType::computerScientist ) {
		int editedHealthWorkerId = healthWorkerTableModel->data( healthWorkerTableModel->index( editedRow, 0 ) ).toInt();

		//start a transaction
		accountTableModel->database().transaction();

		for (int row=0; row < accountTableModel->rowCount(); row++) {

			if ( accountTableModel->data( accountTableModel->index(row, 1) ).toInt() == editedHealthWorkerId ) {

				accountTableModel->setData( accountTableModel->index(row, 2), editedHealthWorker.getLogin() );

				accountTableModel->setData( accountTableModel->index(row, 3), editedHealthWorker.getPassword() );

				if (accountTableModel->submitAll())
					accountTableModel->select();
				else {
					qDebug() << accountTableModel->lastError();
					qDebug() << "Erreur lors de l'édition d'un compte";
				}
			}
		}
	}

	//submit changes
	if (healthWorkerTableModel->submitAll()) {
		emit healthWorkerEdited();
		healthWorkerTableModel->select();
	}
	else {
		qDebug() << healthWorkerTableModel->lastError();
		qDebug() << "Erreur lors de l'édition d'un personnel de soins";
	}

}
