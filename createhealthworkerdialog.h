#ifndef CREATEHEALTHWORKERDIALOG_H
#define CREATEHEALTHWORKERDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlField>
#include <QComboBox>
#include <QDebug>
#include "healthworker.h"

namespace Ui {
class CreateHealthWorkerDialog;
}

class CreateHealthWorkerDialog : public QDialog
{
	Q_OBJECT

public:
	explicit CreateHealthWorkerDialog(QWidget *parent = nullptr);
	~CreateHealthWorkerDialog();

private slots:
	void accept();

	void on_buttonBox_rejected();

    void on_comboBoxType_currentIndexChanged(int index);

private:
    void init_comboBox(QComboBox comboBox);
	Ui::CreateHealthWorkerDialog *ui;
	HealthWorker* healthworker;
    QSqlTableModel* healthWorkerTypeTable;
};

#endif // CREATEHEALTHWORKERDIALOG_H
