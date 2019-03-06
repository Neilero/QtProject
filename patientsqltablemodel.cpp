#include "patientsqltablemodel.h"

#include <QSqlRecord>
#include <QSqlField>

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
	QSqlRecord patientLine;

	//add fields to db line

	QSqlField name("Nom", QVariant::String);
	name.setValue(newPatient.getName());
	patientLine.append(name);

	QSqlField firstname("Prenom", QVariant::String);
	firstname.setValue(newPatient.getFirstname());
	patientLine.append(firstname);

	QSqlField address("Adresse", QVariant::String);
	address.setValue(newPatient.getAddress());
	patientLine.append(address);

	QSqlField town("Ville", QVariant::String);
	town.setValue(newPatient.getTown());
	patientLine.append(town);

	QSqlField postalCode("CP", QVariant::Int);
	postalCode.setValue(newPatient.getPostalCode());
	patientLine.append(postalCode);

	QSqlField comment("Commentaire", QVariant::String);
	comment.setValue(newPatient.getCommentary());
	patientLine.append(comment);

	QSqlField phone("Tel", QVariant::Int);
	phone.setValue(newPatient.getPhoneNumber());
	patientLine.append(phone);

	QSqlField consultationDate("DateConsultation", QVariant::Date);
	consultationDate.setValue(newPatient.getConsultationDate());
	patientLine.append(consultationDate);

	QSqlField consultationDuration("DureeConsultation", QVariant::Int);
	int duration = newPatient.getConsultationDuration().minute() + (newPatient.getConsultationDuration().hour() * 60);
	consultationDuration.setValue(duration);
	patientLine.append(consultationDuration);

	QSqlField priority("Priorite", QVariant::Int);
	priority.setValue(newPatient.getPriority());
	patientLine.append(priority);

	//add the record to the db

	insertRecord(-1, patientLine);
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
