#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_actionQuitter_triggered();

	void on_action_propos_triggered();

	void on_actionPatient_triggered();

	void on_actionPersonnel_de_soin_triggered();

	void on_healthWorker_created();

	void on_pushButtonEditHealthWorker_clicked();

	void on_pushButtonDeleteHealthWorker_clicked();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
