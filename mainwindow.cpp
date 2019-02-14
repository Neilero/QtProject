#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "createpatientdialog.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->statusBar->showMessage("Vous venez de vous connecter", 3000);
}

MainWindow::~MainWindow()
{
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
	ui->statusBar->showMessage("Patient ajouté", 3000);
}

void MainWindow::on_actionPersonnel_de_soin_triggered()
{
	ui->statusBar->showMessage("Personnel ajouté", 3000);
}
