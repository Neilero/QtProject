#include "createpatientdialog.h"
#include "ui_createpatientdialog.h"

#include <QMessageBox>
#include <QDebug>

CreatePatientDialog::CreatePatientDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CreatePatientDialog)
{
	ui->setupUi(this);
	patient = new Patient();
	qDebug() << "TODO : liste d’identifiants de ressource (CreatePatientDialog)" << endl;
}

CreatePatientDialog::~CreatePatientDialog()
{
	delete ui;
}

void CreatePatientDialog::setName(QString name)
{
	ui->lineEditName->setText(name);
}

void CreatePatientDialog::setFirstname(QString firstname)
{
	ui->lineEditSurname->setText(firstname);
}

void CreatePatientDialog::setAddress(QString address)
{
	ui->lineEditAddress->setText(address);
}

void CreatePatientDialog::setCommentary(QString commentary)
{
	ui->plainTextEditCommentary->setPlainText(commentary);
}

void CreatePatientDialog::setConsultationDate(QDate consultationDate)
{
	ui->dateEditConsultationDay->setDate(consultationDate);
}

void CreatePatientDialog::setConsultationDuration(QTime duration)
{
	ui->timeEditDuration->setTime(duration);
}

void CreatePatientDialog::setPhoneNumber(int phoneNumber)
{
	ui->lineEditPhone->setText( QString(phoneNumber) );
}

void CreatePatientDialog::setPostalCode(int postalCode)
{
	ui->lineEditPostCode->setText( QString(postalCode) );
}

void CreatePatientDialog::setPriority(int priority)
{
	ui->horizontalSliderPriority->setValue(priority);
}

void CreatePatientDialog::setTown(QString town)
{
	ui->lineEditTown->setText(town);
}

void CreatePatientDialog::accept()
{
	bool * conversionOk = nullptr;
	QString error = "";

	//Set the name of the patient
	try{
		this->patient->setName(ui->lineEditName->text());
	}
	catch(int e){
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

	if(error.isEmpty()){
		this->close();
		emit patientCreated(*patient);
	}
	else
	{
		QMessageBox::warning(this,"Erreur de création du patient",error);
	}
}

void CreatePatientDialog::on_buttonBox_rejected()
{
	this->close();
}
