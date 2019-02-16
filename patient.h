#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <QDate>

class patient
{

private:
	//compulsory attributes
	QString name;				//first char : uppercase
	QString firstname;			//first char : uppercase
	QString address;
	QString town;				//first char : uppercase
	int postalCode;
	QDate consultationDate;		//must never be earlier than "today"
	QTime consultationDuration; //default : 1h
	int priority;				// 1 (default) <= priority <= 5

	//optional attributes
	QString commentary;
	QString phoneNumber;		//only number (ie. size == 10)

	//default constructor shouldn't be used since we have compulsory attributes
	patient();

public:
	patient(QString name, QString firstname, QString address, QString town, int postalCode, QDate consultationDate, QTime consultationDuration = QTime(1,0), int priority = 1);

};

#endif // PATIENT_H
