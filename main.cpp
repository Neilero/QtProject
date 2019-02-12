#include "mainwindow.h"
#include "authentificationdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainWindow w;

	AuthentificationDialog authentificationDialog(&w);
	authentificationDialog.show();

//	w.show();

	return a.exec();
}
