#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "patientsqltablemodel.h"
#include "patientproxytablemodel.h"
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

	void on_pushButtonEditHealthWorker_clicked();

	void on_pushButtonDeleteHealthWorker_clicked();

	void on_pushButtonSearchPatient_clicked();

private:
	Ui::MainWindow *ui;
	PatientSqlTableModel *model;
	PatientProxyTableModel *proxy;
	QSqlDatabase db;
	CreatePatientDialog *createPatientDialog;
};

#endif // MAINWINDOW_H
