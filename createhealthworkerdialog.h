#ifndef CREATEHEALTHWORKERDIALOG_H
#define CREATEHEALTHWORKERDIALOG_H

#include <QDialog>

namespace Ui {
class createHealthWorkerDialog;
}

class createHealthWorkerDialog : public QDialog
{
	Q_OBJECT

public:
	explicit createHealthWorkerDialog(QWidget *parent = nullptr);
	~createHealthWorkerDialog();

private:
	Ui::createHealthWorkerDialog *ui;
};

#endif // CREATEHEALTHWORKERDIALOG_H
