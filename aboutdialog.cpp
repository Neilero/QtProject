#include "aboutdialog.h"
#include "ui_aboutdialog.h"

/**
 * @brief AboutDialog::AboutDialog basic constructor with the parent argument
 * @param parent the parent QWidget
 */
AboutDialog::AboutDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AboutDialog)
{
	ui->setupUi(this);
}

/**
 * @brief AboutDialog::~AboutDialog basic destructor
 */
AboutDialog::~AboutDialog()
{
	delete ui;
}
