#include "patientproxytablemodel.h"

#include <QDebug>

/**
 * @brief Constructor
 * @param parent the parent of the object
 */
PatientProxyTableModel::PatientProxyTableModel(QObject* parent):
	QSortFilterProxyModel (parent),
	filterID(0)
{
}

/**
 * @brief filter the the given row
 * @param source_row the row to filter
 * @param source_parent the index of the row in the source model
 * @return true if the row should be display on the view
 */
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

/**
 * @brief return the header data of the source model
 * @param section
 * @param orientation
 * @param role
 * @return the header data of the source model
 */
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

/**
 * @brief setter for name filter
 * @param name the new value of the filter
 */
void PatientProxyTableModel::setFilterName(QString name)
{
	filterName = name;

	invalidateFilter();
}

/**
 * @brief setter for firstname filter
 * @param firstname the new value of the filter
 */
void PatientProxyTableModel::setFilterFirstname(QString firstname)
{
	filterFirstname = firstname;

	invalidateFilter();
}

/**
 * @brief setter for id filter
 * @param id the new value of the filter
 */
void PatientProxyTableModel::setFilterID(int ID)
{
	filterID = ID;

	invalidateFilter();
}

/**
 * @brief setter for beginDate filter
 * @param nbeginDateame the new value of the filter
 */
void PatientProxyTableModel::setFilterBeginDate(QDate beginDate)
{
	if (beginDate < filterEndDate) {
		filterBeginDate = beginDate;

		invalidateFilter();
	}
}

/**
 * @brief setter for endDate filter
 * @param endDate the new value of the filter
 */
void PatientProxyTableModel::setFilterEndDate(QDate endDate)
{
	if (endDate > filterBeginDate) {
		filterEndDate = endDate;

		invalidateFilter();
	}
}

/**
 * @brief delete the patient
 * @param the index of the patient to delete
 * @return if the patient is deleted
 */
bool PatientProxyTableModel::deletePatient(const QModelIndex& indexToDelete)
{
	int rowSelected = indexToDelete.row();

	PatientSqlTableModel * patientSourceModel = static_cast<PatientSqlTableModel*>( sourceModel() );
	bool deleted = removeRow(rowSelected);
	patientSourceModel->select();

	return deleted;
}
