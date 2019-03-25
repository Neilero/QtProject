#include "authentificationdialog.h"
#include "ui_authentificationdialog.h"

#include <QMessageBox>
#include <QSqlError>

#include "mainwindow.h"

AuthentificationDialog::AuthentificationDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AuthentificationDialog)
{
	ui->setupUi(this);

	this->parent = static_cast<MainWindow*>(parent);

	accountModel = new QSqlTableModel(this, this->parent->getDb());
	accountModel->setTable("TCompte");
	accountModel->select();
}

/**
 * @brief Destructor
 */
AuthentificationDialog::~AuthentificationDialog()
{
	delete ui;
}

/**
 * @brief when the connect button is clicked, connect if the login and password are correct
 */
void AuthentificationDialog::on_pushButtonConnect_clicked()
{
	if(checkPasswordIsValid()) {

		if (ui->checkBoxResetDb->isChecked()) {
			parent->resetDb();
		}

		parent->show();
		this->close();
	}
	else {
		QMessageBox::warning(this, "Erreur d'authentitification", "Login ou Mot de passe incorrecte...");
		ui->lineEditPassword->clear();
	}
}

/**
 * @brief when the cancel button is click, quit the application
 */
void AuthentificationDialog::on_pushButtonCancel_clicked()
{
	QApplication::quit();
}

/**
 * @brief Check if the password is valid
 * @return true if the password is valid, false if it's wrong
 */
bool AuthentificationDialog::checkPasswordIsValid()
{
	QString login = ui->lineEditLogin->text();
	QString password = ui->lineEditPassword->text();

	for (int i=0; i < accountModel->rowCount(); i++) {
		QSqlRecord record = accountModel->record(i);

		QString recordLogin = record.field(2).value().toString();
		QString recordPassword = record.field(3).value().toString();

		if ( login == recordLogin && password == recordPassword )
			return true;
	}

	return false;
}
