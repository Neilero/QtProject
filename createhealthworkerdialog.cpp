#include "createhealthworkerdialog.h"
#include "ui_createhealthworkerdialog.h"

createHealthWorkerDialog::createHealthWorkerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createHealthWorkerDialog)
{
    ui->setupUi(this);
}

createHealthWorkerDialog::~createHealthWorkerDialog()
{
    delete ui;
}
