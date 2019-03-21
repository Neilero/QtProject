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

	//init patient model
	this->patientModel = new PatientSqlTableModel(this, db);
	patientModel->setTable("TPatient");
	patientModel->select();

	//init patient proxy model
	this->patientProxy = new PatientProxyTableModel(this);

	//init patient table
	patientProxy->setSourceModel(patientModel);
	ui->tableView->setModel(patientProxy);

	//init healthworker model
	this->healthworkerModel = new HealthWorkerTreeModel(this, db);

	//init healthworker tree
	ui->treeViewHealthWorker->setModel(healthworkerModel);

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
	QObject::connect(ui->searchNameLineEdit, SIGNAL(textChanged(QString)), patientProxy, SLOT(setFilterName(QString)));
	QObject::connect(ui->searchFirstnameLineEdit, SIGNAL(textChanged(QString)), patientProxy, SLOT(setFilterFirstname(QString)));
	QObject::connect(ui->searchIDSpinBox, SIGNAL(valueChanged(int)), patientProxy, SLOT(setFilterID(int)));
	QObject::connect(ui->searchBeginDateEdit, SIGNAL(dateChanged(QDate)), patientProxy, SLOT(setFilterBeginDate(QDate)));
	QObject::connect(ui->searchEndDateEdit, SIGNAL(dateChanged(QDate)), patientProxy, SLOT(setFilterEndDate(QDate)));

	//connect signal patient inserted into the DB
	QObject::connect(patientModel, SIGNAL(patientInserted(void)), this, SLOT(on_patientInserted(void)));

	//connect signal dataChanged to the tree model
	QObject::connect(healthworkerModel->getHealthWorkerTableModel(),
					 SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&)),
					 healthworkerModel, SLOT(updateData()));
	QObject::connect(healthworkerModel->getHealthWorkerTypeTableModel(),
					 SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&)),
					 healthworkerModel, SLOT(updateData()));
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

	QObject::connect(createPatientDialog, SIGNAL(patientCreated(Patient)), patientModel, SLOT(insertPatient(Patient)));

	createPatientDialog->exec();

	QObject::disconnect(createPatientDialog, SIGNAL(patientCreated(Patient)), patientModel, SLOT(insertPatient(Patient)));
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
	//nothing to do since the search is in real time...
}

void MainWindow::on_patientInserted()
{
	ui->statusBar->showMessage("Patient ajouté", 5000);
}
