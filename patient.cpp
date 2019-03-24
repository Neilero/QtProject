#include "patient.h"

#include <QDebug>

Patient::Patient()
{

}

Patient::Patient(QString name, QString firstname, QString address, QString town, int postalCode, QDate consultationDate, QTime consultationDuration, int priority, QString commentary, int phoneNumber)
{
	this->setName(name);
	this->setFirstname(firstname);
	this->setAddress(address);
	this->setTown(town);
	this->setPostalCode(postalCode);
	this->setConsultationDate(consultationDate);
	this->setConsultationDuration(consultationDuration);
	this->setPriority(priority);
	this->setCommentary(commentary);
    this->setPhoneNumber(phoneNumber);
}

QString Patient::getName() const
{
	return name;
}

void Patient::setName(const QString& value)
{
    if (value.isEmpty())
        throw(1);
    else if (value.at(0).isUpper())
        name = value;
    else
        throw(2);

}

QString Patient::getFirstname() const
{
	return firstname;
}

void Patient::setFirstname(const QString& value)
{
    if(value.isEmpty())
        throw(1);
    else if (value.at(0).isUpper())
            firstname = value;
        else
            throw(2);
}

QString Patient::getAddress() const
{
	return address;
}

void Patient::setAddress(const QString& value)
{
    if(value.isEmpty())
        throw(1);
    else
        address = value;
}

QString Patient::getTown() const
{
	return town;
}

void Patient::setTown(const QString& value)
{
    if(value.isEmpty())
        throw(1);
    else if(value.at(0).isUpper())
        town = value;
    else
        throw(2);
}

int Patient::getPostalCode() const
{
	return postalCode;
}

void Patient::setPostalCode(int value)
{
    if (value == 0)
        throw(1);
    else if (0 <= value && value <= 99999)
        postalCode = value;
    else
        throw(2);
}

QDate Patient::getConsultationDate() const
{
	return consultationDate;
}

void Patient::setConsultationDate(const QDate& value)
{
	if (QDate::currentDate() <= value)
		consultationDate = value;
    else
        throw(1);
}

QTime Patient::getConsultationDuration() const
{
	return consultationDuration;
}

void Patient::setConsultationDuration(const QTime& value)
{
	consultationDuration = value;
}

int Patient::getPriority() const
{
	return priority;
}

void Patient::setPriority(int value)
{
	if (1 <= value && value <= 5)
		priority = value;
    else
        throw(1);
}

QString Patient::getCommentary() const
{
	return commentary;
}

void Patient::setCommentary(const QString& value)
{
	commentary = value;
}

int Patient::getPhoneNumber() const
{
	return phoneNumber;
}

void Patient::setPhoneNumber(int value)
{
   if(value == 0)
      phoneNumber = 0;
   else if (100000000 <= value && value <= 999999999)
       phoneNumber = value;
   else
       throw(2);

}

