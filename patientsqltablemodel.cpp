#include "patientsqltablemodel.h"

#include <QSqlRecord>
#include <QSqlField>
#include <QDebug>

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

void PatientSqlTableModel::insertPatient(Patient newPatient)
{
	//start a transaction
	database().transaction();

	//create an empty record from the model structure
	QSqlRecord patientLine = record();

	//the Id is auto-increment so we don't set it up
	patientLine.remove( patientLine.indexOf("Id") );

	//set the other fields of the new patient db line

	patientLine.setValue("Nom", newPatient.getName());

	patientLine.setValue("Prenom", newPatient.getFirstname());

	patientLine.setValue("Adresse", newPatient.getAddress());

	patientLine.setValue("Ville", newPatient.getTown());

	patientLine.setValue("CP", newPatient.getPostalCode());

	patientLine.setValue("Commentaire", newPatient.getCommentary());

	patientLine.setValue("Tel", newPatient.getPhoneNumber());

	patientLine.setValue("DateConsultation", newPatient.getConsultationDate());

	int consultationDuration = newPatient.getConsultationDuration().minute() + (newPatient.getConsultationDuration().hour() * 60);
	patientLine.setValue("DureeConsultation", consultationDuration);

	patientLine.setValue("Priorite", newPatient.getPriority());

	//try adding the record to the db

	if( insertRecord(-1, patientLine) ){
		//if ok, commit changes
		submitAll();

		emit patientInserted();
	}
	else{
		//else, rollback
		database().rollback();
	}
}

bool PatientSqlTableModel::deletePatient(const QModelIndex& indexToDelete)
{
	qDebug() << indexToDelete.data(0);

	return true;
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
					return tr("Nom");
				case 2:
					return tr("Prénom");
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
