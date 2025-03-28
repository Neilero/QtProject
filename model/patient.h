#ifndef PATIENT_H
#define PATIENT_H

#include <QString>
#include <QDate>
#include <QList>

class Patient
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
    QList<int> resourceList;

	//optional attributes
	QString commentary;
	int phoneNumber;		//only number (ie. size == 10)

public:
    Patient();
	Patient(QString name, QString firstname, QString address, QString town, int postalCode, QDate consultationDate, QTime consultationDuration = QTime(1,0), int priority = 1, QString commentary = QString(""), int phoneNumber = 0);

	QString getName() const;
	void setName(const QString& value);
	QString getFirstname() const;
	void setFirstname(const QString& value);
	QString getAddress() const;
	void setAddress(const QString& value);
	QString getTown() const;
	void setTown(const QString& value);
	int getPostalCode() const;
	void setPostalCode(int value);
	QDate getConsultationDate() const;
	void setConsultationDate(const QDate& value);
	QTime getConsultationDuration() const;
	void setConsultationDuration(const QTime& value);
	int getPriority() const;
	void setPriority(int value);
	QString getCommentary() const;
	void setCommentary(const QString& value);
	int getPhoneNumber() const;
	void setPhoneNumber(int value);
    QList<int> getResourceList() const;
    void setResourceList(const QList<int> &value);
    void addToResourceList(int value);
};

#endif // PATIENT_H
