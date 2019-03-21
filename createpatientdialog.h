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

signals:
	void patientCreated(Patient newPatient);

private slots:
    void on_buttonBox_accepted();

    void accept();

	void on_buttonBox_rejected();

private:
	Ui::CreatePatientDialog *ui;
    Patient* patient;
};

#endif // CREATEPATIENTDIALOG_H
