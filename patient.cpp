#include "patient.h"

#include <QDebug>

Patient::Patient(QString name, QString firstname, QString address, QString town, int postalCode, QDate consultationDate, QTime consultationDuration, int priority)
{
	this->name = name;
	this->firstname = firstname;
	this->address = address;
	this->town = town;
	this->postalCode = postalCode;
	this->consultationDate = consultationDate;
	this->consultationDuration = consultationDuration;
	this->priority = priority;
}

QString Patient::getName() const
{
	return name;
}

void Patient::setName(const QString& value)
{
	if (value.at(0).isUpper())
		name = value;
	else {
		qDebug() << "first char must be upper";
	}
}

QString Patient::getFirstname() const
{
	return firstname;
}

void Patient::setFirstname(const QString& value)
{
	if (value.at(0).isUpper())
		firstname = value;
	else {
		qDebug() << "first char must be upper";
	}
}

QString Patient::getAddress() const
{
	return address;
}

void Patient::setAddress(const QString& value)
{
	address = value;
}

QString Patient::getTown() const
{
	return town;
}

void Patient::setTown(const QString& value)
{
	town = value;
}

int Patient::getPostalCode() const
{
	return postalCode;
}

void Patient::setPostalCode(int value)
{
	if (0 <= value && value <= 99999)
		postalCode = value;
	else {
		qDebug() << "use valid postal code";
	}
}

QDate Patient::getConsultationDate() const
{
	return consultationDate;
}

void Patient::setConsultationDate(const QDate& value)
{
	if (QDate::currentDate() <= value)
		consultationDate = value;
	else {
		qDebug() << "the new date must be later than the current date";
	}
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
	else {
		qDebug() << "The priority must be between 1 and 5";
	}
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
	if (100000000 <= value && value <= 999999999)
		phoneNumber = value;
	else {
		qDebug() << "use valid phone number (+XX format not supported)";
	}
}

