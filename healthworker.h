#ifndef HEALTHWORKER_H
#define HEALTHWORKER_H

#include <QString>

#include "healthworkertype.h"

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
	HealthWorker();


};

#endif // HEALTHWORKER_H
