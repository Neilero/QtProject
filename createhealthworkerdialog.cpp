#include "createhealthworkerdialog.h"
#include "ui_createhealthworkerdialog.h"

CreateHealthWorkerDialog::CreateHealthWorkerDialog(QWidget *parent, int editedRow) :
	QDialog(parent),
	ui(new Ui::CreateHealthWorkerDialog),
	healthworker(new HealthWorker())
{
	ui->setupUi(this);

	//set the edit mode according to the constructor parameters
	if (editedRow < 0) {
		editMode = false;
		ui->labelTitle->setText("Création d'un nouveau personnel de soins");
	}
	else {
		editMode = true;
		this->editedRow = editedRow;
		ui->labelTitle->setText("Édition d'un personnel de soins");
	}

	//get the datas from the db
	QSqlDatabase db = QSqlDatabase::database();
	healthWorkerTypeTable = new QSqlTableModel(this, db);
	healthWorkerTypeTable->setTable("TType");
	healthWorkerTypeTable->select();

	//get each type and add the combobox
	for(int typeIndex = 0; typeIndex < healthWorkerTypeTable->rowCount(); typeIndex++)
	{
		QString healthWorkerTypeName = healthWorkerTypeTable->record(typeIndex).field(1).value().toString();
		int healthWorkerTypeID = healthWorkerTypeTable->record(typeIndex).field(0).value().toInt();

		ui->comboBoxType->addItem(healthWorkerTypeName, healthWorkerTypeID);
	}
}

CreateHealthWorkerDialog::~CreateHealthWorkerDialog()
{
	delete ui;
}

void CreateHealthWorkerDialog::setName(QString name)
{
	ui->lineEditName->setText(name);
}

void CreateHealthWorkerDialog::setFirstName(QString firstName)
{
	ui->lineEditFirstName->setText(firstName);
}

void CreateHealthWorkerDialog::setType(int type)
{
	ui->comboBoxType->setCurrentIndex( type-1 );
}

void CreateHealthWorkerDialog::setLogin(QString login)
{
	ui->lineEditLogin->setText(login);
}

void CreateHealthWorkerDialog::setPassword(QString password)
{
	ui->lineEditPassword->setText(password);
}

void CreateHealthWorkerDialog::accept()
{
	qDebug() <<"TODO erreurs de conversion (createhealthworkerdialog.cpp"<<endl;
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

	//set the type
	int typeID = ui->comboBoxType->currentData().toInt();
	this->healthworker->setType( static_cast<HealthWorkerType>(typeID) );

	//check login and password in case of type = "informaticien"
	if(this->healthworker->getType() == HealthWorkerType::computerScientist)
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
	if(error.isEmpty()) {
		this->close();

		if (editMode) {
			emit healthworkerEdited(*healthworker, editedRow);
		}
		else {
			emit healthworkerCreated(*healthworker);
		}
	}
	else {
		QString warningTitle;

		if (editMode) {
			warningTitle = "Erreur d'édition du personnel de soins";
		}
		else {
			warningTitle = "Erreur de création du personnel de soins";
		}

		QMessageBox::warning(this,warningTitle,error);
	}
}

void CreateHealthWorkerDialog::on_buttonBox_rejected()
{
	this->close();
}

void CreateHealthWorkerDialog::on_comboBoxType_currentIndexChanged(int index)
{
	int typeID = ui->comboBoxType->itemData(index).toInt();
	if( typeID == 7 )
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
