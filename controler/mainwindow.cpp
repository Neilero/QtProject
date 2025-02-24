#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include <QTimer>
#include <QDebug>
#include <QFile>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "controler/dao/c_init_bd.h"

/**
 * @brief constructor of the MainWindow
 * @param the parent of the MainWindow
 */
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	patientModel = nullptr;

	if (!initDb()) {
		QMessageBox::critical(this, "Erreur de base de données", "Erreur lors de l'initialisation de la base de données. La base de donnée va être mis à zéro.");
		resetDb();
	}

	initModels();

	createConnections();

	ui->statusBar->showMessage("Bienvenue");
}

/**
 * @brief destructor of the MainWindow
 */
MainWindow::~MainWindow()
{
	delete patientModel;
	delete patientProxy;
	delete healthworkerModel;

	db.close();
	db.removeDatabase("QSQLITE");
	delete ui;
}

/**
 * @brief ititialize the database
 * @return true is the database is initialized
 */
bool MainWindow::initDb()
{
	db = QSqlDatabase::addDatabase("QSQLITE");

	if(db.isValid())
	{
		db.setHostName("localhost");
		db.setUserName("root");
		db.setPassword("password");

		if (!QFile::exists("base_tmp.sqli")) {
			return false;
		}

		db.setDatabaseName("base_tmp.sqli");
		db.open();

		if(!db.isOpen())
		{
			qDebug() << db.lastError().text();
			qDebug() << "Erreur à louverture de la base !\n";
			return false;
		}
	}

	return true;
}

/**
 * @brief initialize the models
 */
void MainWindow::initModels()
{
	//init patient model
	this->patientModel = new PatientSqlTableModel(this, db);

	//init patient proxy model
	this->patientProxy = new PatientProxyTableModel(this);

	//init patient table
	patientProxy->setSourceModel(patientModel);
	ui->tableView->setModel(patientProxy);

	//init healthworker model
	this->healthworkerModel = new HealthWorkerTreeModel(this, db);

	//init healthworker tree
	ui->treeViewHealthWorker->setModel(healthworkerModel);
}

/**
 * @brief create a connection between the signals and the slots
 */
void MainWindow::createConnections()
{
	//connect ui filters to proxy filter model
	QObject::connect(ui->searchNameLineEdit, SIGNAL(textChanged(QString)), patientProxy, SLOT(setFilterName(QString)));
	QObject::connect(ui->searchFirstnameLineEdit, SIGNAL(textChanged(QString)), patientProxy, SLOT(setFilterFirstname(QString)));
	QObject::connect(ui->searchIDSpinBox, SIGNAL(valueChanged(int)), patientProxy, SLOT(setFilterID(int)));
	QObject::connect(ui->searchBeginDateEdit, SIGNAL(dateChanged(QDate)), patientProxy, SLOT(setFilterBeginDate(QDate)));
	QObject::connect(ui->searchEndDateEdit, SIGNAL(dateChanged(QDate)), patientProxy, SLOT(setFilterEndDate(QDate)));

	//connect signal patient inserted into the DB to the corresponding slot in this
	QObject::connect(patientModel, SIGNAL(patientInserted(void)), this, SLOT(on_patientInserted(void)));

	//connect signal patient edited into the DB to the corresponding slot in this
	QObject::connect(patientModel, SIGNAL(patientEdited(void)), this, SLOT(on_patientEdited(void)));

	//connect signal dataChanged to the tree model
	QObject::connect(healthworkerModel->getHealthWorkerTableModel(),
					 SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&)),
					 healthworkerModel, SLOT(updateData()));
	QObject::connect(healthworkerModel->getHealthWorkerTypeTableModel(),
					 SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&, const QVector<int>&)),
					 healthworkerModel, SLOT(updateData()));

	//connect signal healthworker inserted into the DB to the corresponding slot in this
	QObject::connect(healthworkerModel, SIGNAL(healthWorkerInserted(void)), this, SLOT(on_healthWorkerInserted(void)));

	//connect signal healthworker edited into the DB to the corresponding slot in this
	QObject::connect(healthworkerModel, SIGNAL(healthWorkerEdited(void)), this, SLOT(on_healthWorkerEdited(void)));
}

/**
 * @brief slot associated to the triggered signal of actionQuitter button
 * quit the application
 */
void MainWindow::on_actionQuitter_triggered()
{
	QApplication::quit();
}

/**
 * @brief slot associated to the triggered signal of propos action
 * show the about dialog
 */
void MainWindow::on_action_propos_triggered()
{
	AboutDialog about(this);
	about.exec();
}

/**
 * @brief slot associated to the triggered signal of create patient action
 * show the create patient dialog
 */
void MainWindow::on_actionPatient_triggered()
{
	createPatientDialog = new CreatePatientDialog(this);

	QObject::connect(createPatientDialog, SIGNAL(patientCreated(Patient)), patientModel, SLOT(insertPatient(Patient)));

	createPatientDialog->exec();

	QObject::disconnect(createPatientDialog, SIGNAL(patientCreated(Patient)), patientModel, SLOT(insertPatient(Patient)));
	delete createPatientDialog;
}

/**
 * @brief slot associated to the triggered signal of create health worker action
 * show the create health worker dialog
 */
void MainWindow::on_actionPersonnel_de_soin_triggered()
{
	createHealthWorkerDialog = new CreateHealthWorkerDialog(this);

	QObject::connect(createHealthWorkerDialog, SIGNAL(healthworkerCreated(HealthWorker)), healthworkerModel, SLOT(insertHealthWorker(HealthWorker)));

	createHealthWorkerDialog->exec();

	QObject::disconnect(createHealthWorkerDialog, SIGNAL(healthworkerCreated(HealthWorker)), healthworkerModel, SLOT(insertHealthWorker(HealthWorker)));

	delete createHealthWorkerDialog;
}

/**
 * @brief slot associated to the triggered signal of delete health worker action
 * delete health worker
 */
void MainWindow::on_pushButtonDeleteHealthWorker_clicked()
{
	QModelIndex currentIndex = ui->treeViewHealthWorker->currentIndex();

	if (currentIndex.isValid()) {
		if (healthworkerModel->deleteHealthWorker( currentIndex )) {
			ui->statusBar->showMessage("Personnel supprimé");
		}
		else {
			ui->statusBar->showMessage("Erreur lors de la suppression d'un personnel de soin !");
		}
	}
}

/**
 * @brief slot associated to the triggered signal of delete patient action
 * delete parient
 */
void MainWindow::on_pushButtonDeletePatient_clicked()
{
	QModelIndex currentIndex = ui->tableView->currentIndex();

	if (currentIndex.isValid()) {
		if ( patientProxy->deletePatient( ui->tableView->currentIndex() ) ) {
			ui->statusBar->showMessage("Patient supprimé");
		}
		else {
			ui->statusBar->showMessage("Erreur lors de la suppression d'un patient !");
		}
	}
}

/**
 * @brief slot associated to the patient insered signal
 * show a message on the statusBar
 */
void MainWindow::on_patientInserted()
{
	ui->statusBar->showMessage("Patient ajouté");
}

/**
 * @brief slot associated to the patient edited signal
 * show a message on the statusBar
 */
void MainWindow::on_patientEdited()
{
	ui->statusBar->showMessage("Patient édité");
}

/**
 * @brief slot associated to the health worker insered signal
 * show a message on the statusBar
 */
void MainWindow::on_healthWorkerInserted()
{
	ui->statusBar->showMessage("Personnel de soins ajouté");
}

/**
 * @brief slot associated to the health worker edited signal
 * show a message on the statusBar
 */
void MainWindow::on_healthWorkerEdited()
{
	ui->statusBar->showMessage("Personnel de soins édité");
}

/**
 * @brief slot associated the the double click on tableView signal
 * @param index the index of the double click
 */
void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
	QSqlRecord patientRecord = patientModel->record( patientProxy->data( patientProxy->index( index.row(), 0 ) ).toInt() -1 );

	createPatientDialog = new CreatePatientDialog(this, patientRecord.field(0).value().toInt() -1);

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
	QObject::connect(createPatientDialog, SIGNAL(patientEdited(Patient, int)), patientModel, SLOT(editPatient(Patient, int)));

	createPatientDialog->exec();

	QObject::disconnect(createPatientDialog, SIGNAL(patientEdited(Patient, int)), patientModel, SLOT(editPatient(Patient, int)));

	delete createPatientDialog;
}

/**
 * @brief slot associated the the double click on treeView signal
 * @param index the index of the double click
 */
void MainWindow::on_treeViewHealthWorker_doubleClicked(const QModelIndex &index)
{
	// if it's a HealthWorkerType, we don't want to be able to modify it.
	if (index.parent() == QModelIndex()) return;

	int healthWorkerId = healthworkerModel->itemFromIndex(index)->data().toInt();
	QSqlRecord healthWorkerRecord = healthworkerModel->getHealthWorkerTableModel()->record( healthWorkerId -1 );

	createHealthWorkerDialog = new CreateHealthWorkerDialog(this, healthWorkerRecord.field(0).value().toInt() -1);

	createHealthWorkerDialog->setName( healthWorkerRecord.field(1).value().toString() );

	createHealthWorkerDialog->setFirstName( healthWorkerRecord.field(2).value().toString() );

	HealthWorkerType healthworkerType = static_cast<HealthWorkerType>( healthWorkerRecord.field(3).value().toInt() );
	createHealthWorkerDialog->setType( healthworkerType );

	if ( healthworkerType == HealthWorkerType::computerScientist ) {

		int healthWorkerId = healthWorkerRecord.field(0).value().toInt();

		for (int row=0; row < healthworkerModel->getAccountTableModel()->rowCount(); row++) {
			QSqlRecord accountRecord = healthworkerModel->getAccountTableModel()->record( row );

			if ( accountRecord.field(1).value().toInt() == healthWorkerId ) {
				createHealthWorkerDialog->setLogin( accountRecord.field(2).value().toString() );

				createHealthWorkerDialog->setPassword( accountRecord.field(3).value().toString() );
			}
		}
	}

	//connect the dialog to the appropriate slot of the DAO
	QObject::connect(createHealthWorkerDialog,
					 SIGNAL(healthworkerEdited(HealthWorker, int)),
					 healthworkerModel,
					 SLOT(editHealthWorker(HealthWorker, int)));

	createHealthWorkerDialog->exec();

	QObject::disconnect(createHealthWorkerDialog,
						SIGNAL(healthworkerEdited(HealthWorker, int)),
						healthworkerModel,
						SLOT(editHealthWorker(HealthWorker, int)));

	delete createHealthWorkerDialog;
}

/**
 * @brief get the database in use
 * @return the database in use
 */
QSqlDatabase MainWindow::getDb() const
{
	return db;
}

/**
 * @brief reset the database
 * @return true if the database is deleted
 */
bool MainWindow::resetDb()
{
	if (patientModel != nullptr) {
		delete patientModel;
		delete patientProxy;
		delete healthworkerModel;
	}

	db.close();
	db.removeDatabase("QSQLITE");

	if (! C_INIT_BD::Creation_BD() )
		return false;

	initDb();
	initModels();
	createConnections();

	return true;
}
