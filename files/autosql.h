#ifndef _AUTOSQL_H
#define _AUTOSQL_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

class Database {
	private:
		QSqlDatabase db;
	public:
		Database(std::string path);
		~Database() { db.close(); }
		std::vector<QString> getAutomates() const;
};

#endif
