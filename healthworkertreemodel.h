#ifndef HEALTHWORKERTREEMODEL_H
#define HEALTHWORKERTREEMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QSqlTableModel>

#include "createhealthworkerdialog.h"

class HealthWorkerTreeModel : public QStandardItemModel
{
	Q_OBJECT

private:
	QSqlTableModel * healthWorkerTableModel;
	QSqlTableModel * healthWorkerTypeTableModel;
	QSqlTableModel * accountTableModel;

public:
	HealthWorkerTreeModel(QObject* parent = nullptr, QSqlDatabase db = QSqlDatabase());
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	QSqlTableModel* getHealthWorkerTableModel() const;
	QSqlTableModel* getHealthWorkerTypeTableModel() const;
	QSqlTableModel* getAccountTableModel() const;

signals:
	void healthWorkerInserted();
	void healthWorkerEdited();

public slots:
	void updateData();
	bool deleteHealthWorker(const QModelIndex& indexToDelete);
	void insertHealthWorker(HealthWorker newHealthWorker);
	void editHealthWorker(HealthWorker editedHealthWorker, int editedRow);
};

#endif // HEALTHWORKERTREEMODEL_H
