#include "healthworker.h"

/**
 * @brief HealthWorker constructor for a computerScientist
 * @param name The name of the health worker
 * @param firstname The firstname of the health worker
 * @param login The login of the health worker
 * @param password The password of the health worker
 */
HealthWorker::HealthWorker(QString name, QString firstname,QString login, QString password)
{
	this->setName(name);
	this->setFirstname(firstname);
	this->setType(HealthWorkerType::computerScientist);
	this->setLogin(login);
	this->setPassword(password);
}

/**
 * @brief HealthWorker constructor
 * @param name The name of the health worker
 * @param firstname The fistname of the health worker
 * @param type The type of the health worker
 */
HealthWorker::HealthWorker(QString name, QString firstname, HealthWorkerType type)
{
	this->setName(name);
	this->setFirstname(firstname);
	this->setType(type);
}

/**
 * @brief Default constructor
 */
HealthWorker::HealthWorker()
{

}

/**
 * @brief Get the name of the health worker
 * @return The name of the health worker
 */
QString HealthWorker::getName() const
{
	return name;
}

/**
 * @brief Set a new name to the health worker
 * @param The name to set to the health worker
 */
void HealthWorker::setName(const QString &value)
{
	if (value.isEmpty())
		throw(1);
	else if (value.at(0).isUpper())
		this->name = value;
	else
		throw(2);
}

/**
 * @brief Get the first name of the health worker
 * @return The first name of the health worker
 */
QString HealthWorker::getFirstname() const
{
	return firstname;
}


/**
 * @brief Set a new first name to the health worker
 * @param The first name to set to the health worker
 */
void HealthWorker::setFirstname(const QString &value)
{
	if(value.isEmpty())
		throw(1);
	else if (value.at(0).isUpper())
		firstname = value;
	else
		throw(2);
}

/**
 * @brief Get the type of the health worker
 * @return The type of the health worker
 */
HealthWorkerType HealthWorker::getType() const
{
	return type;
}

/**
 * @brief Set a new type to the health worker
 * @param The type to set to the health worker
 */
void HealthWorker::setType(const HealthWorkerType &value)
{
	type = value;
}

/**
 * @brief Get the login of the health worker
 * @return The login of the health worker
 */
QString HealthWorker::getLogin() const
{
	return login;
}

/**
 * @brief Set a new login to the employee
 * @param The login to set to the employee
 */
void HealthWorker::setLogin(const QString &value)
{
	if(value.isEmpty())
		throw(1);
	else
		login = value;
}

/**
 * @brief Get the password the employee
 * @return The password of the employee
 */
QString HealthWorker::getPassword() const
{
	return password;
}

/**
 * @brief Set a new password to the employee
 * @param the password to set to the employee
 */
void HealthWorker::setPassword(const QString &value)
{
	if(value.isEmpty())
		throw(1);
	else
		password = value;
}
