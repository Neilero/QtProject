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

	void insertPatient(Patient &newPatient);

	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // PATIENTSQLTABLEMODEL_H
