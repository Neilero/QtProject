#ifndef CREATEPATIENTDIALOG_H
#define CREATEPATIENTDIALOG_H

#include <QDialog>

namespace Ui {
class CreatePatientDialog;
}

class CreatePatientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreatePatientDialog(QWidget *parent = nullptr);
    ~CreatePatientDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CreatePatientDialog *ui;
};

#endif // CREATEPATIENTDIALOG_H
