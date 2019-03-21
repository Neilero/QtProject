#include "healthworkertreemodel.h"

#include <QSqlRecord>
#include <QSqlField>
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

		//build healthworker item
		QStandardItem * healthWorker = new QStandardItem(healthWorkerName + " " + healthWorkerFirstname);
		healthWorker->setData(healthWorkerID);
		healthWorker->setEditable(false);

		//insert healthworker into its type item.
		healthWorkerTypes.value(healthWorkerType)->insertRow(0, healthWorker);
	}
}
