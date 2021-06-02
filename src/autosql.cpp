#include <iostream>
#include <autosql.h>

Database::Database(std::string path): db(QSqlDatabase::addDatabase("QSQLITE")) {
	db.setDatabaseName(path.c_str());
	if (!db.open()) {
		throw "Unable to open database";
	}

	db.exec("CREATE TABLE IF NOT EXISTS automates (nom VARCHAR(30) PRIMARY KEY, defaut INTEGER)");
	db.exec("CREATE TABLE IF NOT EXISTS regles_transition (id VARCHAR(30) REFERENCES automate(nom), min1 INTEGER, min2 INTEGER, min3 INTEGER, min4 INTEGER, min5 INTEGER, min6 INTEGER, min7 INTEGER, min8 INTEGER, max1 INTEGER, max2 INTEGER, max3 INTEGER, max4 INTEGER, max5 INTEGER, max6 INTEGER, max7 INTEGER, max8 INTEGER, courant INTEGER, destination INTEGER)");
	db.exec("CREATE TABLE IF NOT EXISTS regles_voisinage (id VARCHAR(30) PRIMARY KEY REFERENCES automates(nom), type INTEGER)");
	db.exec("CREATE TABLE IF NOT EXISTS coord_voisinage (id VARCHAR(30) REFERENCES automates(nom), x INTEGER, y INTEGER)");
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
