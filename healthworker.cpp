#include "healthworker.h"

HealthWorker::HealthWorker(QString name, QString firstname, HealthWorkerType type = computerScientist, QString login, QString password)
{
    this->setName(name);
    this->setFirstname(firstname);
    this->setType(type);
    this->setLogin(login);
    this->setPassword(password);
}

HealthWorker::HealthWorker(QString name, QString firstname, HealthWorkerType type)
{
    this->setName(name);
    this->setFirstname(firstname);
    this->setType(type);
}
