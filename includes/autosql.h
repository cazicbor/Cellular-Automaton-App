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

/// @brief Cette classe adapte un objet base de données pour le rendre facile d'utilisation dans le cadre de l'application
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
		/// @param[in] a Automate dont on souhaite obtenir la Fonction
		Fonction* getFonction(Automate& a) const;
		/// Obtenir la règle de voisinage d'un automate par son nom
		/// @param[in] name nom de l'Automate dont on souhaite la RegleVoisinage
		RegleVoisinage* getRegleVoisinage(const QString& name) const;
		/// Obtenir la liste des Reseau disponibles pour un Automate par son nom
		/// @param[in] name nom de l'Automate
		std::vector<QString> getListeReseaux(const QString& name) const;
		/// Obtenir un réseau par son nom
		/// @param[in] idReseau identifiant du Reseau dans la base de donnée
		Reseau& getReseau(int idReseau) const;
		/// Sauvegarder un réseau en base de donnée
		/// @param[in] reseau      Reseau à sauvegarder
		/// @param[in] nomReseau   nom du Reseau à sauvegarder
		/// @param[in] nomAutomate nom de l'Automate à qui il appartient
		void stockerReseau(const Reseau& reseau, const QString& nomReseau, const QString& nomAutomate) const;
		/// Initialise l'ensemble d'état d'un automate
		/// @param[in] a Automate dont on souhaite initialiser l'EnsembleEtat
		void initEnsEtat(Automate& a) const;
		/// Sauvegarder un automate en BDD
		/// @param[in] a Automate que l'on souhaite sauvegarder
		void saveAutomaton(const Automate& a) const;
		/// Sauvegarder une fonction en BDD
		/// @param[in] name nom de l'Automate à qui appartien la Fonction
		/// @param[in] f    Fonction à sauvegarder
		void saveFunction(const QString& name, const Fonction& f) const;
		/// Sauvegarder une règle de voisinage en BDD
		/// @param[in] name nom de l'Automate à qui appartien la RegleVoisinage
		/// @param[in] r    RegleVoisinage à sauvegarder
		void saveVoisinage(const QString& name, const RegleVoisinage& r) const;
		/// Sauvegarder un ensemble d'états en BDD
		/// @param[in] a Automate dont on souhaite sauvegarder l'ensemble
		void saveEnsemble(Automate& a) const;
		/// initialiser le singleton automate depuis la bdd par son nom
		/// @param[in] modele nom du modèle que l'on souhaite initialiser
		void initSingletonAutomate(const QString& modele) const;
};

#endif
