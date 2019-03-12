#include "healthworker.h"

HealthWorker::HealthWorker(QString name, QString firstname,QString login, QString password)
{
    this->setName(name);
    this->setFirstname(firstname);
    this->setType(HealthWorkerType::computerScientist);
    this->setLogin(login);
    this->setPassword(password);
}

HealthWorker::HealthWorker(QString name, QString firstname, HealthWorkerType type)
{
    this->setName(name);
    this->setFirstname(firstname);
    this->setType(type);
}


QString HealthWorker::getFirstname() const
{
    return firstname;
}

void HealthWorker::setFirstname(const QString &value)
{
    firstname = value;
}

HealthWorkerType HealthWorker::getType() const
{
    return type;
}

void HealthWorker::setType(const HealthWorkerType &value)
{
    type = value;
}

QString HealthWorker::getLogin() const
{
    return login;
}

void HealthWorker::setLogin(const QString &value)
{
    login = value;
}

QString HealthWorker::getPassword() const
{
    return password;
}

void HealthWorker::setPassword(const QString &value)
{
    password = value;
}
QString HealthWorker::getName() const
{
    return name;
}

void HealthWorker::setName(const QString &value)
{
    name = value;
}
