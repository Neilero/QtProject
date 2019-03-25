#ifndef CREATEPATIENTDIALOG_H
#define CREATEPATIENTDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QSqlTableModel>
#include <QSqlField>
#include <QSqlRecord>
#include <QList>
#include "patient.h"

namespace Ui {
class CreatePatientDialog;
}

class CreatePatientDialog : public QDialog
{
	Q_OBJECT

public:
	explicit CreatePatientDialog(QWidget *parent = nullptr, int editedRow = -1);
	~CreatePatientDialog();

	void setName(QString name);
	void setFirstname(QString firstname);
	void setAddress(QString address);
	void setCommentary(QString commentary);
	void setConsultationDate(QDate consultationDate);
	void setConsultationDuration(QTime duration);
	void setPhoneNumber(int phoneNumber);
	void setPostalCode(int postalCode);
	void setPriority(int priority);
	void setTown(QString town);
	void setResources(QList<int> resourcesList);

signals:
	void patientCreated(Patient newPatient);
	void patientEdited(Patient editedPatient, int editedRow);

private slots:
	void accept();
	void on_buttonBox_rejected();

private:
    QListWidget* ressourceList;
	Ui::CreatePatientDialog *ui;
    Patient* patient;
    QSqlDatabase db;
	QSqlTableModel* resourceTable;
	bool editMode;
	int editedRow;
};

#endif // CREATEPATIENTDIALOG_H
