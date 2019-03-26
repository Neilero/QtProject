#include "createpatientdialog.h"
#include "ui_createpatientdialog.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QDebug>

/**
 * @brief CreatePatientDialog::CreatePatientDialog sole constructor with 2 arguments
 * @param parent the QWidget parent of the dialog
 * @param editedRow the edited row in the model (-1 if the dialog is used to create instead of editing a patient)
 */
CreatePatientDialog::CreatePatientDialog(QWidget *parent, int editedRow) :
	QDialog(parent),
	ui(new Ui::CreatePatientDialog),
	patient(new Patient())
{
	//init the table for listWidget
	db = static_cast<MainWindow*>(parent)->getDb();
	resourceTable = new QSqlTableModel(this, db);
	resourceTable->setTable("TRessource");
	resourceTable->select();

	ui->setupUi(this);

	//Check if the patient is edited or created
	if (editedRow < 0) {
		editMode = false;
		ui->labelTitle->setText("Création d'un nouveau patient");
	}
	else {
		editMode = true;
		this->editedRow = editedRow;
		ui->labelTitle->setText("Édition d'un patient");
	}

	//add each items to the listWidget
	for(int resourceIndex = 0;resourceIndex < resourceTable->rowCount();resourceIndex++ )
	{
		//add the item to the list
		QSqlRecord ressource = resourceTable->record(resourceIndex);
		QString ressourceName = ressource.field(1).value().toString();
		QString ressourceFirstname = ressource.field(2).value().toString();

		QListWidgetItem * ressourceItem = new QListWidgetItem(ressourceName + " " + ressourceFirstname, ui->listWidget);

		ui->listWidget->addItem( ressourceItem );

		//add flag
		ressourceItem->setFlags(ressourceItem->flags() | Qt::ItemIsUserCheckable);

		//set the item unchecked
		ressourceItem->setCheckState(Qt::Unchecked);
	}
}

/**
 * @brief CreatePatientDialog::~CreatePatientDialog basic destructor
 */
CreatePatientDialog::~CreatePatientDialog()
{
	delete ui;
}

/**
 * @brief CreatePatientDialog::setName sets the lineEdit content corresponding to the name field
 * @param name the value to show in the lineEdit
 */
void CreatePatientDialog::setName(QString name)
{
	ui->lineEditName->setText(name);
}

/**
 * @brief CreatePatientDialog::setFirstname sets the lineEdit content corresponding to the firstName field
 * @param firstname the value to show in the lineEdit
 */
void CreatePatientDialog::setFirstname(QString firstname)
{
	ui->lineEditSurname->setText(firstname);
}

/**
 * @brief CreatePatientDialog::setAddress sets the lineEdit content corresponding to the address field
 * @param address the value to show in the lineEdit
 */
void CreatePatientDialog::setAddress(QString address)
{
	ui->lineEditAddress->setText(address);
}

/**
 * @brief CreatePatientDialog::setCommentary sets the plainTextEdit content corresponding to the commentary field
 * @param commentary the value to show in the plainTextEdit
 */
void CreatePatientDialog::setCommentary(QString commentary)
{
	ui->plainTextEditCommentary->setPlainText(commentary);
}

/**
 * @brief CreatePatientDialog::setConsultationDate sets the dateEdit value corresponding to the consultation date field
 * @param consultationDate the value to show in the dateEdit
 */
void CreatePatientDialog::setConsultationDate(QDate consultationDate)
{
	ui->dateEditConsultationDay->setDate( consultationDate );
}

/**
 * @brief CreatePatientDialog::setConsultationDuration sets the timeEdit value corresponding to the duration field
 * @param duration the value to show in the timeEdit
 */
void CreatePatientDialog::setConsultationDuration(QTime duration)
{
	ui->timeEditDuration->setTime( duration );
}

/**
 * @brief CreatePatientDialog::setPhoneNumber sets the lineEdit content corresponding to the phone number field
 * @param phoneNumber the value to show in the lineEdit
 */
void CreatePatientDialog::setPhoneNumber(int phoneNumber)
{
	ui->lineEditPhone->setText( QString::number(phoneNumber, 10).insert(0, '0') );
}

/**
 * @brief CreatePatientDialog::setPostalCode sets the lineEdit content corresponding to the postal code field
 * @param postalCode the value to show in the lineEdit
 */
void CreatePatientDialog::setPostalCode(int postalCode)
{
	ui->lineEditPostCode->setText( QString::number(postalCode, 10) );
}

/**
 * @brief CreatePatientDialog::setPriority sets the slider value corresponding to the priority field
 * @param priority the value to show in the slider
 */
void CreatePatientDialog::setPriority(int priority)
{
	ui->horizontalSliderPriority->setValue(priority);
}

/**
 * @brief CreatePatientDialog::setTown sets the lineEdit content corresponding to the town field
 * @param town the value to show in the lineEdit
 */
void CreatePatientDialog::setTown(QString town)
{
	ui->lineEditTown->setText(town);
	ui->lineEditTown->setCursorPosition(0);
}

/**
 * @brief CreatePatientDialog::setResources sets the listWidget values corresponding to the consultations' ressource field
 * @param resourceIndexesList the value to show in the listWidget
 */
void CreatePatientDialog::setResources(QList<int> resourceIndexesList)
{
	for(int resourceIndex=0; resourceIndex < resourceIndexesList.size();resourceIndex++)
	{
		ui->listWidget->item(resourceIndexesList.at(resourceIndex))->setCheckState(Qt::Checked);
	}
}

/**
 * @brief CreatePatientDialog::accept override checking the contents of the form.
 *
 * Prompt a QMessageBox::warning in case of incorect content detected.
 * Otherwise, sends a patientCreated or a patientEdited signal.
 */
void CreatePatientDialog::accept()
{
	//check the convertions errors
	bool * conversionOk = nullptr;
	//report all input error
	QString error = "";

	//Set the name of the patient
	try
	{
		this->patient->setName(ui->lineEditName->text());
	}
	catch(int e)
	{
		if(e==1)
			error.append("Completer le nom du patient.\n");
		else if(e==2)
			error.append("la première lettre du nom du patient doit être une majuscule.\n");
		else
			error.append("Le nom du patient est incorrect.\n");
	}


	//Set the firstname of the patient
	try{
		this->patient->setFirstname(ui->lineEditSurname->text());
	}
	catch(int e){
		if(e==1)
			error.append("Completer le prenom du patient.\n");
		else if(e==2)
			error.append("la première lettre du prenom du patient doit être une majuscule.\n");
		else
			error.append("Le prenom du patient est incorrect.\n");
	}


	//Set the adresse of the patient
	try{
		this->patient->setAddress(ui->lineEditAddress->text());
	}
	catch(int e){
		if (e == 1)
			error.append("L'adresse du patient est vide.\n");
		else {
			error.append("L'adresse du patient est incorrect.\n");
		}
	}


	//Set the town of the patient
	try{
		this->patient->setTown(ui->lineEditTown->text());
	}
	catch(int e){
		if(e==1)
			error.append("Completer le nom de la ville du patient.\n");
		else if(e==2)
			error.append("la première lettre du nom de la ville du patient doit être une majuscule.\n");
		else
			error.append("Le nom de la ville du patient est incorrect.\n");
	}


	//Set the postal code of the patient
	try{
		this->patient->setPostalCode(ui->lineEditPostCode->text().remove(" ").toInt(conversionOk, 10));
	}
	catch(int e){
		if(e == 1)
			error.append("Entrer le code postal du patient.\n");
		else
			error.append("Le code postal du patient est incorrect.\n");
	}


	//Set the number of the patient
	try{
		this->patient->setPhoneNumber(ui->lineEditPhone->text().remove(" ").toInt(conversionOk, 10));
	}
	catch(int e){
		if(e==1)
			error.append("Entrer le numéro de téléphone du patient.\n");
		else
			error.append("Le numéro de téléphone du patient est incorrect.\n");
	}


	//set the date of the consultation
	try{
		this->patient->setConsultationDate(ui->dateEditConsultationDay->date());
	}
	catch(int e){
		if(e==1)
			error.append("La date de consultation ne doit pas être antérieure à aujourd'hui.\n");
		else
			error.append("La date de consultation est incorrecte.\n");
	}


	//set the durations of the consultations
	this->patient->setConsultationDuration(ui->timeEditDuration->time());


	//set the priority of the consultation
	try{
		this->patient->setPriority(ui->horizontalSliderPriority->value());
	}
	catch(int e){
		if(e==1)
			error.append("La priorité doit être comprise entre 1 et 5.\n");
		else
			error.append("La priorité est invalide.\n");
	}


	//add a commentary
	this->patient->setCommentary(ui->plainTextEditCommentary->toPlainText());

	//add each resource
	for(int resourceIndex=0; resourceIndex < ui->listWidget->count(); resourceIndex++)
	{
		if(ui->listWidget->item(resourceIndex)->checkState() == Qt::Checked)
			patient->addToResourceList(resourceTable->record(resourceIndex).field(0).value().toInt());
	}

	//check if error was reported
	if(error.isEmpty()){
		this->close();

		if (editMode) {
			emit patientEdited(*patient, editedRow);
		}
		else {
			emit patientCreated(*patient);
		}
	}
	else
	{
		QString warningTitle;

		if (editMode) {
			warningTitle = "Erreur d'édition du patient";
		}
		else {
			warningTitle = "Erreur de création du patient";
		}

		QMessageBox::warning(this,warningTitle,error);
	}
}

/**
 * @brief CreatePatientDialog::on_buttonBox_rejected basic override closing the dialog
 */
void CreatePatientDialog::on_buttonBox_rejected()
{
	this->close();
}
