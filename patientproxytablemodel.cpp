#include "patientproxytablemodel.h"

#include <QDebug>

PatientProxyTableModel::PatientProxyTableModel(QObject* parent):
	QSortFilterProxyModel (parent),
	filterID(0)
{

}

bool PatientProxyTableModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
	QModelIndex indexName = sourceModel()->index(source_row, 1, source_parent);
	QModelIndex indexFirstname = sourceModel()->index(source_row, 2, source_parent);
	QModelIndex indexID = sourceModel()->index(source_row, 0, source_parent);
	QModelIndex indexDate = sourceModel()->index(source_row, 8, source_parent);

	if (filterName != nullptr)
		if (! sourceModel()->data(indexName).toString().contains(filterName, Qt::CaseInsensitive) )
			return false;

	if (filterFirstname != nullptr)
		if (! sourceModel()->data(indexFirstname).toString().contains(filterFirstname, Qt::CaseInsensitive) )
			return false;

	if (filterID != 0)
		if ( sourceModel()->data(indexID).toInt() != filterID )
			return false;

	if (! (filterBeginDate.isNull() || filterEndDate.isNull()) )
		if ( sourceModel()->data(indexDate).toDate() < filterBeginDate || filterEndDate < sourceModel()->data(indexDate).toDate() )
			return false;

	return true;
}

QVariant PatientProxyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	return sourceModel()->headerData(section, orientation, role);
}

void PatientProxyTableModel::setFilterName(QString name)
{
	filterName = name;

	invalidateFilter();
}

void PatientProxyTableModel::setFilterFirstname(QString firstname)
{
	filterFirstname = firstname;

	invalidateFilter();
}

void PatientProxyTableModel::setFilterID(int ID)
{
	filterID = ID;

	invalidateFilter();
}

void PatientProxyTableModel::setFilterBeginDate(QDate beginDate)
{
	if (beginDate < filterEndDate) {
		filterBeginDate = beginDate;

		invalidateFilter();
	}
}

void PatientProxyTableModel::setFilterEndDate(QDate endDate)
{
	if (endDate > filterBeginDate) {
		filterEndDate = endDate;

		invalidateFilter();
	}
}
