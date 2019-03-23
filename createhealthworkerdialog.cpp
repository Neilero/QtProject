#include "createhealthworkerdialog.h"
#include "ui_createhealthworkerdialog.h"

CreateHealthWorkerDialog::CreateHealthWorkerDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CreateHealthWorkerDialog)
{
    ui->setupUi(this);

    //Signal when the combobox index changes
    QObject::connect(ui->comboBoxType,SIGNAL(currentIndexChanged(int)),this,SLOT(on_ComboxBoxCurrentIndex_Changed(int)));

    //get the datas from the db
    QSqlDatabase db = QSqlDatabase::database();
    healthWorkerTypeTable = new QSqlTableModel(this, db);
    healthWorkerTypeTable->setTable("TType");
    healthWorkerTypeTable->select();

    //get each type and add the combobox
    for(int typeIndex = 0; typeIndex < healthWorkerTypeTable->rowCount(); typeIndex++)
    {
        QString healthWorkerTypeField = healthWorkerTypeTable->record(typeIndex).field(1).value().toString();
        ui->comboBoxType->addItem(healthWorkerTypeField);
    }
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

    //this->close();
}
