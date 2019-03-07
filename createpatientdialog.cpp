#include "createpatientdialog.h"
#include "ui_createpatientdialog.h"

#include <QDebug>

CreatePatientDialog::CreatePatientDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CreatePatientDialog)
{
	ui->setupUi(this);
}

CreatePatientDialog::~CreatePatientDialog()
{
	delete ui;
}

void CreatePatientDialog::on_buttonBox_accepted()
{
	bool * conversionOk = nullptr;

	//TODO : change to 1. Create empty patient 2. set all values and check set for error
	//ERROR : crash if try to create an empty patient
	qDebug() << "WARNING : TODO in CreatePatientDialog::on_buttonBox_accepted function" << endl;

	QString name = ui->lineEditName->text();
	QString surname = ui->lineEditSurname->text();
	QString address = ui->lineEditAddress->text();
	QString town = ui->lineEditTown->text();
	int postcode = ui->lineEditPostCode->text().toInt(conversionOk, 10);
	int phonenumber = ui->lineEditPhone->text().remove(" ").toInt(conversionOk, 10);
	QDate consultationDate = ui->dateEditConsultationDay->date();
	QTime consultationDuration = ui->timeEditDuration->time();
	int priority = ui->horizontalSliderPriority->value();
	QString commentary = ui->plainTextEditCommentary->toPlainText();

	Patient newPatient(name, surname, address, town, postcode, consultationDate, consultationDuration, priority, commentary, phonenumber);

	emit patientCreated(newPatient);
}

void CreatePatientDialog::on_buttonBox_rejected()
{
	this->close();
}
