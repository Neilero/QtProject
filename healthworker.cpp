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

QString HealthWorker::getName() const
{
    return name;
}

void HealthWorker::setName(const QString &value)
{
    if (value.isEmpty())
        throw(1);
    else if (value.at(0).isUpper())
        name = value;
    else
        throw(2);
}


QString HealthWorker::getFirstname() const
{
    return firstname;
}

void HealthWorker::setFirstname(const QString &value)
{
    if(value.isEmpty())
        throw(1);
    else if (value.at(0).isUpper())
        firstname = value;
    else
        throw(2);
}

HealthWorkerType HealthWorker::getType() const
{
    return type;
}

void HealthWorker::setType(const HealthWorkerType &value)
{
    qDebug() << "TODO Je sais plus comment ça fait quand c'est vide ça" << endl;
}

QString HealthWorker::getLogin() const
{
    return login;
}

void HealthWorker::setLogin(const QString &value)
{
    if(value.isEmpty())
        throw(1);
    else
        login = value;
}

QString HealthWorker::getPassword() const
{
    return password;
}

void HealthWorker::setPassword(const QString &value)
{
    if(value.isEmpty())
        throw(1);
    else
        password = value;
}
