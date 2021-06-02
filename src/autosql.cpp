#include <iostream>
#include <autosql.h>

Database::Database(std::string path): db(QSqlDatabase::addDatabase("QSQLITE")) {
	db.setDatabaseName(path.c_str());
	if (!db.open()) {
		throw "Unable to open database";
	}

	db.exec("CREATE TABLE IF NOT EXISTS automates (nom VARCHAR(30) PRIMARY KEY, voisinage INTEGER, fonction INTEGER)");
}

std::vector<QString> Database::getAutomates() const {
	QSqlQuery query = db.exec("SELECT nom FROM automates");
	std::vector<QString> names;
	if(query.first()) {
		names.push_back(query.value("nom").toString());
	}
	while(query.next()) {
		names.push_back(query.value("nom").toString());
	}

	return names;
}
