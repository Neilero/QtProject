#ifndef C_INIT_BD_H
#define C_INIT_BD_H

#include <QSqlDatabase>

class C_INIT_BD
{
	private:
		C_INIT_BD();
	public:
		static bool Creation_BD(QSqlDatabase db = QSqlDatabase::database());
};

#endif // C_INIT_BD_H
