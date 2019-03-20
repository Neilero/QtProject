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

	QSqlTableModel* getHealthWorkerTableModel() const;
	QSqlTableModel* getHealthWorkerTypeTableModel() const;

public slots:
	void updateData();
};

#endif // HEALTHWORKERTREEMODEL_H
