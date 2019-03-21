#ifndef HEALTHWORKERTREEMODEL_H
#define HEALTHWORKERTREEMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QSqlTableModel>

class HealthWorkerTreeModel : public QStandardItemModel
{
	Q_OBJECT

private:
	QSqlTableModel * healthWorkerTableModel;
	QSqlTableModel * healthWorkerTypeTableModel;

public:
	HealthWorkerTreeModel(QObject* parent = nullptr, QSqlDatabase db = QSqlDatabase());
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;


	QSqlTableModel* getHealthWorkerTableModel() const;
	QSqlTableModel* getHealthWorkerTypeTableModel() const;

public slots:
	void updateData();
	void deleteHealthWorker(const QModelIndex& indexToDelete);
	void updateHealthWorker(QModelIndex * indexToUpdate);
};

#endif // HEALTHWORKERTREEMODEL_H
