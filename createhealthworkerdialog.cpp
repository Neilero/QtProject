#include "createhealthworkerdialog.h"
#include "ui_createhealthworkerdialog.h"

CreateHealthWorkerDialog::CreateHealthWorkerDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CreateHealthWorkerDialog)
{
    //Combobox
    QObject::connect(ui->comboBoxType,SIGNAL(currentIndexChanged(int)),this,SLOT(on_ComboxBoxCurrentIndex_Changed(int)));
    QSqlDatabase db = QSqlDatabase::database();
    healthWorkerTypeTable = new QSqlTableModel(this, db);
    healthWorkerTypeTable->setTable("TType");
    healthWorkerTypeTable->select();
    QString healthWorkerTypeField = healthWorkerTypeTable->record(0).field(1).value().toString();

    ui->comboBoxType->addItem(healthWorkerTypeField);
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

void CreateHealthWorkerDialog::on_ComboxBoxCurrentIndex_Changed(int index)
{

    this->close();
}
