#ifndef _AUTOSQL_H
#define _AUTOSQL_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <Fonction.h>
#include <voisinage.h>
#include <Automate.h>

/// Cette classe adapte un objet base de données pour le rendre facile d'utilisation dans le cadre de l'application
///
/// Il suffit de lui donner le nom du fichier sqlite à la création et d'appeler les méthodes pour intéragir avec. Les pointeurs retournés par les méthodes getFonction, getRegleVoisinage et getReseau pointent vers des objets dynamiques dont la charge de la destruction est laissée à l'utilisateur
class Database {
	private:
		QSqlDatabase db;

		static std::unique_ptr<Database> instance;
		Database& operator=(const Database& a) = delete;
		Database(const Database& a) = delete;
		Database(std::string path);
	public:
		/// Obtenir une référence vers l'instance unique du singleton database
		///
		/// Le chemin vers la base de données et hardcodé pour le moment mais pourrait aisément être rendu dynamique
		static Database& getInstance() {
			if(instance == nullptr)
				instance.reset(new Database("application.db"));
			return *instance;
		}

		~Database() { db.close(); }
		/// Obtenir la liste de tous les noms d'automate disponibles
		std::vector<QString> getAutomates() const;
		/// Obtenir la fonction d'un automate donné
		Fonction* getFonction(Automate& a) const;
		/// Obtenir la règle de voisinage d'un automate par son nom
		RegleVoisinage* getRegleVoisinage(const QString& name) const;
		/// Obtenir la liste des grilles disponibles pour un automate par son nom
		std::vector<QString> getListeReseaux(const QString& name) const;
		/// Obtenir un réseau par son nom
		Reseau& getReseau(int idReseau) const;
		/// Sauvegarder un réseau en base de donnée
		void stockerReseau(const Reseau& reseau, const QString& nomReseau, const QString& nomAutomate) const;
		/// Initialise l'ensemble d'état d'un automate
		void initEnsEtat(Automate& a) const;
		/// Sauvegarder un automate en BDD
		void saveAutomaton(const Automate& a) const;
		/// Sauvegarder une fonction en BDD
		void saveFunction(const QString& name, const Fonction& f) const;
		/// Sauvegarder une règle de voisinage en BDD
		void saveVoisinage(const QString& name, const RegleVoisinage& r) const;
		/// Sauvegarder un ensemble d'états en BDD
		void saveEnsemble(Automate& a) const;
		/// initialiser le singleton automate depuis la bdd par son nom
		void initSingletonAutomate(const QString& modele) const;
};

#endif
