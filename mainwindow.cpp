#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
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

	db = QSqlDatabase::database();

	this->model = new PatientSqlTableModel(this, db);
	model->setTable("TPatient");
	model->select();

	this->proxy = new PatientProxyTableModel(this);

	proxy->setSourceModel(model);
	ui->tableView->setModel(proxy);

	createConnections();
}

MainWindow::~MainWindow()
{
	db.close();
	delete ui;
}

void MainWindow::createConnections()
{
	//connect ui filters to proxy filter model
	QObject::connect(ui->searchNameLineEdit, SIGNAL(textChanged(QString)), proxy, SLOT(setFilterName(QString)));
	QObject::connect(ui->searchFirstnameLineEdit, SIGNAL(textChanged(QString)), proxy, SLOT(setFilterFirstname(QString)));
	QObject::connect(ui->searchIDSpinBox, SIGNAL(valueChanged(int)), proxy, SLOT(setFilterID(int)));
	QObject::connect(ui->searchBeginDateEdit, SIGNAL(dateChanged(QDate)), proxy, SLOT(setFilterBeginDate(QDate)));
	QObject::connect(ui->searchEndDateEdit, SIGNAL(dateChanged(QDate)), proxy, SLOT(setFilterEndDate(QDate)));

	//connect signal patient inserted into the DB
	QObject::connect(model, SIGNAL(patientInserted(void)), this, SLOT(on_patientInserted(void)));
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
	createPatientDialog = new CreatePatientDialog(this);

	QObject::connect(createPatientDialog, SIGNAL(patientCreated(Patient)), model, SLOT(insertPatient(Patient)));

	createPatientDialog->exec();

	QObject::disconnect(createPatientDialog, SIGNAL(patientCreated(Patient)), model, SLOT(insertPatient(Patient)));
	delete createPatientDialog;
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
	//...
}

void MainWindow::on_patientInserted()
{
	ui->statusBar->showMessage("Patient ajouté", 5000);
}
