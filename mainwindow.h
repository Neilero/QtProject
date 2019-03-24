#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "patientsqltablemodel.h"
#include "patientproxytablemodel.h"
#include "healthworkertreemodel.h"
#include "createpatientdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	void createConnections();

private slots:
	void on_actionQuitter_triggered();

	void on_action_propos_triggered();

	void on_actionPatient_triggered();

	void on_actionPersonnel_de_soin_triggered();

	void on_pushButtonDeleteHealthWorker_clicked();

	void on_pushButtonDeletePatient_clicked();

	void on_patientInserted();

	void on_patientEdited();

	void on_healthWorkerInserted();

	void on_healthWorkerEdited();

	void on_tableView_doubleClicked(const QModelIndex &index);

	void on_treeViewHealthWorker_doubleClicked(const QModelIndex &index);

private:
	Ui::MainWindow *ui;
	PatientSqlTableModel *patientModel;
	PatientProxyTableModel *patientProxy;
	HealthWorkerTreeModel *healthworkerModel;
	QSqlDatabase db;
	CreatePatientDialog *createPatientDialog;
	CreateHealthWorkerDialog *createHealthWorkerDialog;
};

#endif // MAINWINDOW_H
