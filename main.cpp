#include "controler/mainwindow.h"
#include "controler/authentificationdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow w;

	AuthentificationDialog authentificationDialog(&w);
	authentificationDialog.show();

	return a.exec();
}
