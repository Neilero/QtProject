#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "createpatientdialog.h"
#include "c_init_bd.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->statusBar->showMessage("Bienvenue");

	if (!C_INIT_BD::Creation_BD()) {
		QMessageBox::critical(this, "Erreur de base de données", "Erreur lors de l'initialisation de la base de données.");
		QApplication::quit();
	}

	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setHostName("localhost");
	db.setDatabaseName("base_tmp.sqli");

	db.open();

	this->model = new PatientSqlTableModel(this, db);
	model->setTable("TPatient");
	model->select();

//	model->insertRow( model->rowCount() );
//	model->setData( model->index(model->rowCount()-1, 0), 8);
//	model->setData( model->index(model->rowCount()-1, 1), "Nameless");
//	model->submit();

	ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
	db.close();
	delete ui;
}

void MainWindow::on_actionQuitter_triggered()
{
	QApplication::quit();
}

void MainWindow::on_action_propos_triggered()
{
	AboutDialog about(this);
	about.exec();
}

void MainWindow::on_actionPatient_triggered()
{
	CreatePatientDialog createpatientdialog(this);
	createpatientdialog.exec();
	ui->statusBar->showMessage("Patient ajouté", 5000);
}

void MainWindow::on_actionPersonnel_de_soin_triggered()
{
	ui->statusBar->showMessage("Personnel ajouté", 5000);
}

void MainWindow::on_pushButtonEditHealthWorker_clicked()
{
	ui->statusBar->showMessage("Personnel édité", 5000);
}

void MainWindow::on_pushButtonDeleteHealthWorker_clicked()
{
	ui->statusBar->showMessage("Personnel supprimé", 5000);
}

void MainWindow::on_pushButtonSearchPatient_clicked()
{

}
