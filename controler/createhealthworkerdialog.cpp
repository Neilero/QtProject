#include "createhealthworkerdialog.h"
#include "ui_createhealthworkerdialog.h"
#include "mainwindow.h"

/**
 * @brief CreateHealthWorkerDialog::CreateHealthWorkerDialog Sole constructor with 2 arguments
 * @param parent the parent QWidget
 * @param editedRow the edited row in the model (-1 if the dialog is used to create instead of editing a healthworker)
 */
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
	QSqlDatabase db = static_cast<MainWindow*>(parent)->getDb();
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

/**
 * @brief CreateHealthWorkerDialog::~CreateHealthWorkerDialog basic destructor
 */
CreateHealthWorkerDialog::~CreateHealthWorkerDialog()
{
	delete ui;
}

/**
 * @brief CreateHealthWorkerDialog::setName sets the lineEdit content corresponding to the line field
 * @param name the value to show in the lineEdit
 */
void CreateHealthWorkerDialog::setName(QString name)
{
	ui->lineEditName->setText(name);
}

/**
 * @brief CreateHealthWorkerDialog::setFirstName sets the lineEdit content corresponding to the firstName field
 * @param firstName the value to show in the lineEdit
 */
void CreateHealthWorkerDialog::setFirstName(QString firstName)
{
	ui->lineEditFirstName->setText(firstName);
}

/**
 * @brief CreateHealthWorkerDialog::setType sets the comboBox value corresponding to the type field
 * @param type the value to show in the comboBox
 */
void CreateHealthWorkerDialog::setType(HealthWorkerType type)
{
	ui->comboBoxType->setCurrentIndex( static_cast<int>(type) -1 );
}

/**
 * @brief CreateHealthWorkerDialog::setLogin sets the lineEdit content corresponding to the login field
 * @param login the value to show in the lineEdit
 */
void CreateHealthWorkerDialog::setLogin(QString login)
{
	ui->lineEditLogin->setText(login);
}

/**
 * @brief CreateHealthWorkerDialog::setPassword sets the lineEdit content corresponding to the password field
 * @param password the value to show in the lineEdit
 */
void CreateHealthWorkerDialog::setPassword(QString password)
{
	ui->lineEditPassword->setText(password);
}

/**
 * @brief CreateHealthWorkerDialog::accept override checking the contents of the form.
 *
 * Prompt a QMessageBox::warning in case of incorect content detected.
 * Otherwise, sends a healthworkerCreated or a healthworkerEdited signal.
 */
void CreateHealthWorkerDialog::accept()
{
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

/**
 * @brief CreateHealthWorkerDialog::on_buttonBox_rejected basic override closing the dialog
 */
void CreateHealthWorkerDialog::on_buttonBox_rejected()
{
	this->close();
}

/**
 * @brief CreateHealthWorkerDialog::on_comboBoxType_currentIndexChanged slot for the currentIndexChanged of the comboBoxType
 * @param index the new current index
 *
 * Sets the lineEdits and their associated labels corresponding to the login and password
 * to either visible or not visible according to the given index.
 */
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
