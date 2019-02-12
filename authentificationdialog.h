#ifndef AUTHENTIFICATIONDIALOG_H
#define AUTHENTIFICATIONDIALOG_H

#include <QDialog>

namespace Ui {
class AuthentificationDialog;
}

class AuthentificationDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AuthentificationDialog(QWidget *parent = nullptr);
	~AuthentificationDialog();

private slots:
	void on_pushButtonConnect_clicked();

	void on_pushButtonCancel_clicked();

private:
	Ui::AuthentificationDialog *ui;
	QWidget *parent;

	bool checkPasswordIsValid();
};

#endif // AUTHENTIFICATIONDIALOG_H
