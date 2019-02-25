#include "patientsqltablemodel.h"



PatientSqlTableModel::PatientSqlTableModel(QObject* parent, QSqlDatabase db)
	: QSqlTableModel(parent, db)
{
}

Qt::ItemFlags PatientSqlTableModel::flags(const QModelIndex& index) const
{
	if (index.column() != 0) {
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
	}
	else {
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	}
}
