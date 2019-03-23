#ifndef CREATEHEALTHWORKERDIALOG_H
#define CREATEHEALTHWORKERDIALOG_H

#include <QDialog>
#include "healthworker.h"

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

signals:
//    void healthWorkerCreated(HealthWorker newHealthWorker);

private slots:
	void accept();

	void on_buttonBox_rejected();

private:
	Ui::CreateHealthWorkerDialog *ui;
	HealthWorker* healthworker;
};

#endif // CREATEHEALTHWORKERDIALOG_H
