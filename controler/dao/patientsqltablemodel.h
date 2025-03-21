#ifndef PATIENTSQLTABLEMODEL_H
#define PATIENTSQLTABLEMODEL_H

#include <QSqlTableModel>

#include "model/patient.h"

class PatientSqlTableModel : public QSqlTableModel
{
	Q_OBJECT

public:
	PatientSqlTableModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());

	Qt::ItemFlags flags(const QModelIndex &index) const;

	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

public slots:
	void insertPatient(Patient newPatient);
	void editPatient(Patient editedPatient, int row);

signals:
	void patientInserted();
	void patientEdited();

};

#endif // PATIENTSQLTABLEMODEL_H
