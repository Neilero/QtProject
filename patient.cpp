#include "patient.h"

#include <QDebug>

/**
 * @brief Default constructor
 */
Patient::Patient()
{

}

/**
 * @brief Constructor
 * @param name The name to set to the patient
 * @param firstname The first name to set to the patient
 * @param address The address to set to the patient
 * @param town The town to set to the patient
 * @param postalCode The postalCode to set to the patient
 * @param consultationDate The consultationDate to set
 * @param consultationDuration The duration of the consultation
 * @param priority The priority of the consultation
 * @param commentary A commentary to add
 * @param phoneNumber The phone number to set to the patient
 */
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

/**
 * @brief Get the name of the patient
 * @return The name of the patient
 */
QString Patient::getName() const
{
	return name;
}

/**
 * @brief Set a new name to the patient
 * @param The new name to set to the patient
 */
void Patient::setName(const QString& value)
{
    if (value.isEmpty())
        throw(1);
    else if (value.at(0).isUpper())
        name = value;
    else
        throw(2);
}

/**
 * @brief Get the first name of the patient
 * @return The first name of the patient
 */
QString Patient::getFirstname() const
{
	return firstname;
}

/**
 * @brief Set a new first name to the patient
 * @param The new fist name to set to the patient
 */
void Patient::setFirstname(const QString& value)
{
    if(value.isEmpty())
        throw(1);
    else if (value.at(0).isUpper())
            firstname = value;
        else
            throw(2);
}

/**
 * @brief Get the address of the patient
 * @return The address of the patient
 */
QString Patient::getAddress() const
{
	return address;
}

/**
 * @brief Set a new address to the patient
 * @param The new fist name to set to the patient
 */
void Patient::setAddress(const QString& value)
{
    if(value.isEmpty())
        throw(1);
    else
        address = value;
}

/**
 * @brief Get the town of the patient
 * @return The town of the patient
 */
QString Patient::getTown() const
{
	return town;
}

/**
 * @brief Set a new town to the patient
 * @param The new town to set to the patient
 */
void Patient::setTown(const QString& value)
{
    if(value.isEmpty())
        throw(1);
    else if(value.at(0).isUpper())
        town = value;
    else
        throw(2);
}

/**
 * @brief Get the postal code of the patient
 * @return The postal code of the patient
 */
int Patient::getPostalCode() const
{
	return postalCode;
}

/**
 * @brief Set a new postal code to the patient
 * @param The new postal code to set to the patient
 */
void Patient::setPostalCode(int value)
{
    if (value == 0)
        throw(1);
    else if (0 <= value && value <= 99999)
        postalCode = value;
    else
        throw(2);
}

/**
 * @brief Get the date of the consultation
 * @return The date of the consultation
 */
QDate Patient::getConsultationDate() const
{
	return consultationDate;
}

/**
 * @brief Set a new consultation date
 * @param The date of the consultation
 */
void Patient::setConsultationDate(const QDate& value)
{
	if (QDate::currentDate() <= value)
		consultationDate = value;
    else
        throw(1);
}

/**
 * @brief Get the duration of the consultation
 * @return The duration of the consultation
 */
QTime Patient::getConsultationDuration() const
{
	return consultationDuration;
}

/**
 * @brief Change the duration of the consultation
 * @param The new duration of the consultation
 */
void Patient::setConsultationDuration(const QTime& value)
{
	consultationDuration = value;
}

/**
 * @brief Get the priority of the consultation
 * @return The priority of the consulation
 */
int Patient::getPriority() const
{
	return priority;
}

/**
 * @brief Change the priority of the consultation
 * @param The new priority of the consultation
 */
void Patient::setPriority(int value)
{
	if (1 <= value && value <= 5)
		priority = value;
    else
        throw(1);
}

/**
 * @brief Get the commentary about the patient
 * @return The commentary
 */
QString Patient::getCommentary() const
{
	return commentary;
}

/**
 * @brief Set a new commentary about the patient
 * @param The commentary to set
 */
void Patient::setCommentary(const QString& value)
{
	commentary = value;
}

/**
 * @brief Get the phone number of the patient
 * @return The phone number of the patient
 */
int Patient::getPhoneNumber() const
{
	return phoneNumber;
}

/**
 * @brief Change the phone number of the patient
 * @param The new the phone number to set to the patient
 */
void Patient::setPhoneNumber(int value)
{
   if(value == 0)
      phoneNumber = 0;
   else if (100000000 <= value && value <= 999999999)
       phoneNumber = value;
   else
       throw(2);
}

/**
 * @brief Get the ressources list
 * @return The ressources list
 */
QList<int> Patient::getResourceList() const
{
    return resourceList;
}

/**
 * @brief Change the ressources list
 * @param The ressources list to set
 */
void Patient::setResourceList(const QList<int> &value)
{
    resourceList = value;
}

/**
 * @brief Add a ressource to the ressource list
 * @param The id of the ressource to add
 */
void Patient::addToResourceList(int value)
{
    resourceList.append(value);
}
