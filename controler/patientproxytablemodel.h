#ifndef PATIENTPROXYTABLEMODEL_H
#define PATIENTPROXYTABLEMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>
#include <QDate>

#include "patientsqltablemodel.h"

class PatientProxyTableModel : public QSortFilterProxyModel
{
	Q_OBJECT

private:
	QString filterName;
	QString filterFirstname;
	int filterID;
	QDate filterBeginDate;
	QDate filterEndDate;

public:
	PatientProxyTableModel(QObject* parent = nullptr);

	bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

public slots:
	void setFilterName(QString name);
	void setFilterFirstname(QString firstname);
	void setFilterID(int ID);
	void setFilterBeginDate(QDate beginDate);
	void setFilterEndDate(QDate endDate);

	bool deletePatient(const QModelIndex& indexToDelete);
};

#endif // PATIENTPROXYTABLEMODEL_H
