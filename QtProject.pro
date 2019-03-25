#-------------------------------------------------
#
# Project created by QtCreator 2019-02-11T17:20:57
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtProject
CONFIG += c++11
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
		main.cpp \
		controler/mainwindow.cpp \
	controler/authentificationdialog.cpp \
	controler/aboutdialog.cpp \
	controler/createpatientdialog.cpp \
	model/patient.cpp \
	model/healthworker.cpp \
	controler/dao/c_init_bd.cpp \
	controler/dao/patientsqltablemodel.cpp \
	controler/patientproxytablemodel.cpp \
	controler/createhealthworkerdialog.cpp \
	controler/dao/healthworkertreemodel.cpp

HEADERS += \
		controler/mainwindow.h \
	controler/authentificationdialog.h \
	controler/aboutdialog.h \
	controler/createpatientdialog.h \
	model/patient.h \
	model/healthworker.h \
	model/healthworkertype.h \
	controler/dao/c_init_bd.h \
	controler/dao/patientsqltablemodel.h \
	controler/patientproxytablemodel.h \
	controler/createhealthworkerdialog.h \
	controler/dao/healthworkertreemodel.h

FORMS += \
		view/mainwindow.ui \
	view/authentificationdialog.ui \
	view/aboutdialog.ui \
	view/createpatientdialog.ui \
	view/createhealthworkerdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
	ressources.qrc
