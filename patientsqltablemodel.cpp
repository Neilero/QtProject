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

QVariant PatientSqlTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal) {
			switch (section)
			{
				case 0:
					return tr("ID");
				case 1:
					return tr("Prénom");
				case 2:
					return tr("Nom");
				case 3:
					return tr("Adresse");
				case 4:
					return tr("Ville");
				case 5:
					return tr("Code postal");
				case 6:
					return tr("Commentaire");
				case 7:
					return tr("Téléphone");
				case 8:
					return tr("Date de consultation");
				case 9:
					return tr("Durée de consultation");
				case 10:
					return tr("Priorité");

				default:
					return QString("");
			}
		}
	}

	return QVariant();
}
