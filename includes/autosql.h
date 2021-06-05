#ifndef _AUTOSQL_H
#define _AUTOSQL_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <Fonction.h>
#include <voisinage.h>

/// Cette classe adapte un objet base de données pour le rendre facile d'utilisation dans le cadre de l'application
///
/// Il suffit de lui donner le nom du fichier sqlite à la création et d'appeler les méthodes pour intéragir avec. Les pointeurs retournés par les méthodes getFonction et getRegleVoisinage pointent vers des objets dynamiques dont la charge de la destruction est laissée à l'utilisateur
class Database {
	private:
		QSqlDatabase db;
	public:
		Database(std::string path);
		~Database() { db.close(); }
		std::vector<QString> getAutomates() const;
		Fonction* getFonction(const QString& name) const;
		RegleVoisinage* getRegleVoisinage(const QString& name) const;
};

#endif