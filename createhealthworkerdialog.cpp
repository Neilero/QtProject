#include "createhealthworkerdialog.h"
#include "ui_createhealthworkerdialog.h"

CreateHealthWorkerDialog::CreateHealthWorkerDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CreateHealthWorkerDialog)
{
	ui->setupUi(this);
}

CreateHealthWorkerDialog::~CreateHealthWorkerDialog()
{
	delete ui;
}

void CreateHealthWorkerDialog::accept()
{
	//TODO creation of healthworker
}

void CreateHealthWorkerDialog::on_buttonBox_rejected()
{
	this->close();
}
