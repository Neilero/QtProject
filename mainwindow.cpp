#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlField>
#include <QDebug>

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
	QModelIndex currentIndex = ui->treeViewHealthWorker->currentIndex();

	if (currentIndex.isValid()) {
		if (healthworkerModel->deleteHealthWorker( currentIndex )) {
			ui->statusBar->showMessage("Personnel supprimé", 5000);
		}
		else {
			ui->statusBar->showMessage("Erreur lors de la suppression d'un personnel de soin !", 5000);
		}
	}
}

void MainWindow::on_pushButtonDeletePatient_clicked()
{
	QModelIndex currentIndex = ui->tableView->currentIndex();

	if (currentIndex.isValid()) {
		if ( patientProxy->deletePatient( ui->tableView->currentIndex() ) ) {
			ui->statusBar->showMessage("Patient supprimé, 5000");
		}
		else {
			ui->statusBar->showMessage("Erreur lors de la suppression d'un patient !", 5000);
		}
	}
}

void MainWindow::on_patientInserted()
{
	ui->statusBar->showMessage("Patient ajouté", 5000);
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
	QSqlRecord patientRecord = patientModel->record( patientProxy->data( patientProxy->index( index.row(), 0 ) ).toInt() -1 );

	createPatientDialog = new CreatePatientDialog(this, true);

	createPatientDialog->setName( patientRecord.field(1).value().toString() );

	createPatientDialog->setFirstname( patientRecord.field(2).value().toString() );

	createPatientDialog->setAddress( patientRecord.field(3).value().toString() );

	createPatientDialog->setTown( patientRecord.field(4).value().toString() );

	createPatientDialog->setPostalCode( patientRecord.field(5).value().toInt() );

	createPatientDialog->setCommentary( patientRecord.field(6).value().toString() );

	createPatientDialog->setPhoneNumber( patientRecord.field(7).value().toInt() );

	createPatientDialog->setConsultationDate( patientRecord.field(8).value().toDate() );

	QTime consultationDuration = QTime( patientRecord.field(9).value().toInt() / 60, patientRecord.field(9).value().toInt() % 60 );
	createPatientDialog->setConsultationDuration( consultationDuration );

	createPatientDialog->setPriority( patientRecord.field(10).value().toInt() );

	//connect the dialog to the appropriate slot of the DAO
	QObject::connect(createPatientDialog, SIGNAL(patientEdited(Patient)), patientModel, SLOT(insertPatient(Patient)));

	createPatientDialog->exec();

	QObject::disconnect(createPatientDialog, SIGNAL(patientEdited(Patient)), patientModel, SLOT(insertPatient(Patient)));
}
