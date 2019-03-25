#ifndef CREATEHEALTHWORKERDIALOG_H
#define CREATEHEALTHWORKERDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlField>
#include <QComboBox>
#include <QDebug>

#include "model/healthworker.h"

namespace Ui {
class CreateHealthWorkerDialog;
}

class CreateHealthWorkerDialog : public QDialog
{
	Q_OBJECT

public:
	explicit CreateHealthWorkerDialog(QWidget *parent = nullptr, int editedRow = -1);
	~CreateHealthWorkerDialog();

	void setName(QString name);
	void setFirstName(QString firstName);
	void setType(HealthWorkerType type);
	void setLogin(QString login);
	void setPassword(QString password);

signals:
	void healthworkerCreated(HealthWorker newHealthWorker);
	void healthworkerEdited(HealthWorker editedHealthWorker, int editedRow);

private slots:
	void accept();
	void on_buttonBox_rejected();
	void on_comboBoxType_currentIndexChanged(int index);

private:
	void init_comboBox(QComboBox comboBox);
	Ui::CreateHealthWorkerDialog *ui;
	HealthWorker* healthworker;
	QSqlTableModel* healthWorkerTypeTable;
	bool editMode;
	int editedRow;
};

#endif // CREATEHEALTHWORKERDIALOG_H
