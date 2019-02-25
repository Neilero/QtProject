#include "authentificationdialog.h"
#include "ui_authentificationdialog.h"

#include <QMessageBox>
#include "mainwindow.h"

AuthentificationDialog::AuthentificationDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AuthentificationDialog),
	parent{parent}
{
	ui->setupUi(this);
}

AuthentificationDialog::~AuthentificationDialog()
{
	delete ui;
}

void AuthentificationDialog::on_pushButtonConnect_clicked()
{
	if(checkPasswordIsValid()) {
		parent->show();
		this->close();
	}
	else {
		QMessageBox::warning(this, "Erreur d'authentitification", "Login ou Mot de passe incorrecte...");
		ui->lineEditPassword->clear();
	}
}

void AuthentificationDialog::on_pushButtonCancel_clicked()
{
	QApplication::quit();
}

bool AuthentificationDialog::checkPasswordIsValid()
{
	QString login = ui->lineEditLogin->text();
	QString password = ui->lineEditPassword->text();

	if ( login == "" && password == "" )
		return true;

	return false;
}
