#ifndef CREATEHEALTHWORKERDIALOG_H
#define CREATEHEALTHWORKERDIALOG_H

#include <QDialog>
#include "healthworker.h"

#include "healthworker.h"

namespace Ui {
class createHealthWorkerDialog;
}

class CreateHealthWorkerDialog : public QDialog
{
	Q_OBJECT

public:
	explicit createHealthWorkerDialog(QWidget *parent = nullptr);
	~createHealthWorkerDialog();

signals:
//    void healthWorkerCreated(HealthWorker newHealthWorker);

private slots:
    void accept();

    void on_buttonBox_rejected();

private:
    Ui::createHealthWorkerDialog *ui;
    HealthWorker* healthworker;
};

#endif // CREATEHEALTHWORKERDIALOG_H
