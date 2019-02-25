#include "createpatientdialog.h"
#include "ui_createpatientdialog.h"

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
	QString name = ui->lineEditName->text();
	QString surname = ui->lineEditSurname->text();
	QString adress = ui->lineEditAddress->text();
	QString town = ui->lineEditTown->text();
	QString postcode = ui->lineEditPostCode->text();
	QString phonenumber = ui->lineEditPhone->text();
}

void CreatePatientDialog::on_buttonBox_rejected()
{
	this->close();
}
