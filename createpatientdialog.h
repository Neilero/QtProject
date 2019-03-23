#ifndef CREATEPATIENTDIALOG_H
#define CREATEPATIENTDIALOG_H

#include <QDialog>

#include "patient.h"

namespace Ui {
class CreatePatientDialog;
}

class CreatePatientDialog : public QDialog
{
	Q_OBJECT

public:
	explicit CreatePatientDialog(QWidget *parent = nullptr);
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

signals:
	void patientCreated(Patient newPatient);

private slots:
	void accept();
	void on_buttonBox_rejected();

private:
	Ui::CreatePatientDialog *ui;
	Patient* patient;
};

#endif // CREATEPATIENTDIALOG_H
