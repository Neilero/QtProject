#include "createhealthworkerdialog.h"
#include "ui_createhealthworkerdialog.h"

CreateHealthWorkerDialog::CreateHealthWorkerDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CreateHealthWorkerDialog)
{
    ui->setupUi(this);

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
    //check the convertions errors
    bool * conversionOk = nullptr;
    //report all input error
    QString error = "";

    //Set the name
    try
    {
        this->healthworker->setName(ui->lineEditName->text());
    }
    catch(int e)
    {
       if(e==1)
           error.append("Completer le nom du personnel.\n");
       else if(e==2)
           error.append("La première lettre du nom doit être une majuscule.\n");
       else
           error.append("Le nom du patient est incorrect.\n");
    }

    //Set the firstname
    try
    {
        this->healthworker->setFirstname(ui->lineEditFirstName->text());
    }
    catch(int e)
    {
       if(e==1)
           error.append("Completer le prenom du personnel.\n");
       else if(e==2)
           error.append("La première lettre du prenom doit être une majuscule.\n");
       else
           error.append("Le prenom du patient est incorrect.\n");
    }

    //check login and password in case of type = "informaticien"
    if(ui->comboBoxType->currentText() == "Informaticien")
    {
        //check login
        if(ui->lineEditLogin->text().isEmpty())
            error.append("Entrer le login.\n");
        else
            this->healthworker->setLogin(ui->lineEditLogin->text());

        //check password
        if(ui->lineEditLogin->text().isEmpty())
            error.append("Entrer le mot de passe.\n");
        else
            this->healthworker->setPassword(ui->lineEditPassword->text());
    }


    //check if error was reported
    if(error.isEmpty())
        this->close();
    else
        QMessageBox::warning(this,"warningTitle",error);
}

void CreateHealthWorkerDialog::on_buttonBox_rejected()
{
	this->close();
}

void CreateHealthWorkerDialog::on_comboBoxType_currentIndexChanged(int index)
{

    if(ui->comboBoxType->itemText(index) == "Informaticien")
    {
        ui->labelLogin->setVisible(true);
        ui->lineEditLogin->setVisible(true);
        ui->labelPassword->setVisible(true);
        ui->lineEditPassword->setVisible(true);
    }
    else
    {
        ui->labelLogin->setVisible(false);
        ui->lineEditLogin->setVisible(false);
        ui->labelPassword->setVisible(false);
        ui->lineEditPassword->setVisible(false);
    }
}
