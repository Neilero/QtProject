#include "patientsqltablemodel.h"

#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include <QDebug>

/**
 * @brief Constructor
 * @param parent the parent of the object
 * @param db the database to connect to
 */
PatientSqlTableModel::PatientSqlTableModel(QObject* parent, QSqlDatabase db)
	: QSqlTableModel(parent, db)
{
	setTable("TPatient");
	select();
}

/**
 * @brief Returns the item flags for the given index
 * @param index the flags' index
 * @return The item flags for the given index
 */
Qt::ItemFlags PatientSqlTableModel::flags(const QModelIndex& index) const
{
	if ( index.column() == 0 )
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
	else {
		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
	}
}

/**
 * @brief Insert a new patient to the database
 * @param newPatient the patient to add
 */
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
		database().commit();
		submitAll();
		select();

		emit patientInserted();
	}
	else{
		//else, rollback
		database().rollback();
	}
}

/**
 * @brief edit a patient in the database
 * @param the patient to edit
 * @param the row to modify
 */
void PatientSqlTableModel::editPatient(Patient editedPatient, int row)
{
	//start a transaction
	database().transaction();

	//set the values of the edited patient to its new ones

	setData( index(row, 1), editedPatient.getName() );

	setData( index(row, 2), editedPatient.getFirstname() );

	setData( index(row, 3), editedPatient.getAddress() );

	setData( index(row, 4), editedPatient.getTown() );

	setData( index(row, 5), editedPatient.getPostalCode() );

	setData( index(row, 6), editedPatient.getCommentary() );

	setData( index(row, 7), editedPatient.getPhoneNumber() );

	setData( index(row, 8), editedPatient.getConsultationDate() );

	int consultationDuration = editedPatient.getConsultationDuration().minute() + (editedPatient.getConsultationDuration().hour() * 60);
	setData( index(row, 9), consultationDuration );

	setData( index(row, 10), editedPatient.getPriority() );

	//submit changes
	if (submitAll()) {
		database().commit();
		select();

		emit patientEdited();
	}
	else {
		database().rollback();
	}
}

/**
 * @brief Return string to set to the header
 * @param section the section of the header
 * @param orientation the orientation of the header
 * @param role the role of the header
 * @return
 */
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
