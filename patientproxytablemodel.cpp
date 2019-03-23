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

/**
 * @brief PatientProxyTableModel::flags used to allow the source model to be editable without allowing the view to edit the model
 * @param index the index of the model (not used)
 * @return Qt::ItemIsEnabled | Qt::ItemIsSelectable (all items are enabled and selectable)
 */
Qt::ItemFlags PatientProxyTableModel::flags(const QModelIndex& index) const
{
	Q_UNUSED(index);
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
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

bool PatientProxyTableModel::deletePatient(const QModelIndex& indexToDelete)
{
	int rowSelected = indexToDelete.row();

	PatientSqlTableModel * patientSourceModel = static_cast<PatientSqlTableModel*>( sourceModel() );
	bool deleted = removeRow(rowSelected);
	patientSourceModel->select();

	return deleted;
}
