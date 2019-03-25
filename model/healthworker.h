#ifndef HEALTHWORKER_H
#define HEALTHWORKER_H

#include <QObject>
#include <QMetaType>
#include <QString>
#include <QDebug>

#include <healthworkertype.h>

class HealthWorker
{

private:
	//Generic attributes
	QString name;
	QString firstname;
	HealthWorkerType type;

	//Attributes specific to "computerScientist" type
	QString login;
	QString password;

public:
	HealthWorker(QString name, QString firstname,QString login, QString password);
	HealthWorker(QString name, QString firstname, HealthWorkerType type);
	HealthWorker();

	QString getName() const;
	void setName(const QString &value);
	QString getFirstname() const;
	void setFirstname(const QString &value);
	HealthWorkerType getType() const;
	void setType(const HealthWorkerType &value);
	QString getLogin() const;
	void setLogin(const QString &value);
	QString getPassword() const;
	void setPassword(const QString &value);
};

#endif // HEALTHWORKER_H
