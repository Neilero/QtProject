#ifndef PATIENTSQLTABLEMODEL_H
#define PATIENTSQLTABLEMODEL_H

#include <QSqlTableModel>

#include "patient.h"

class PatientSqlTableModel : public QSqlTableModel
{
	Q_OBJECT

public:
	PatientSqlTableModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());

	Qt::ItemFlags flags(const QModelIndex &index) const;

	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

public slots:
	void insertPatient(Patient newPatient);
	bool deletePatient(const QModelIndex &indexToDelete);

signals:
	void patientInserted();

};

#endif // PATIENTSQLTABLEMODEL_H
