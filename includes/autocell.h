#ifndef AUTOCELL_H
#define AUTOCELL_H

#include <reseau_cellule_etats.h>

#include <memory>
#include <QObject>
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QLayoutItem>
#include <QFont>
#include <QPushButton>
#include <QCheckBox>
#include <QFormLayout>
#include <QSpinBox>

/*! @mainpage Cellulut - Projet de LO21 P21
 * @author Victor Blanchet
 * @author Boris Cazic
 * @author Romain de Laage
 * @author Leon Do Castelo
 * @author Maxime Goret
 * @author Luning Yang
 *
 * @include README.md
 */

using namespace std;

/// Classe représentant l'interface principale de l'application
class AutoCell : public QWidget {
		static std::unique_ptr<AutoCell> instance;

		unique_ptr<Reseau> Grille = nullptr;
		std::vector<QString> listeGrille;

		Q_OBJECT
		QGridLayout* general;

		//définition de la frame choix du modèle
		QWidget* win_model_choice;
		QLabel* lab_model_choice;
		QComboBox* liste;
		QGridLayout* grid_model_choice;
		QPushButton* button_add_model;

		//définition de la frame initialisation
		QWidget* win_init;
		QLabel* lab_init;
		QGridLayout* form_init;

		QFormLayout* form_saved_grids;
		QFormLayout* form_config;

		QComboBox *list_grids;
		QCheckBox* check_load_grid;

		QLineEdit* edit_largeur;
		QLineEdit* edit_hauteur;
		QCheckBox* check_aleatoire;
		QPushButton* button_valide_init;

		//définition de la frame "panneau de contrôle de l'exécution"
		QWidget* win_run_ctrl;
		QLabel* lab_run_crtl;

		QGridLayout* grid_run_control;

		QCheckBox* matriceTorique;
		QLabel* lab_time_step;
		QSpinBox* spin_time_step;
		QPushButton* button_prev;
		QPushButton* button_run;
		QPushButton* button_next;
		QPushButton* button_reinitialiser;

		QLabel* lab_nb_step;
		QLineEdit* edit_nb_step;
		QLabel* lab_periode;
		QLineEdit* edit_periode;

		QLabel* lab_sauv_grille;
		QLineEdit* edit_nom_grille;
		QPushButton* button_save_grid;

		//définition de la frame affichage de la grille
		QWidget* win_grid;
		QTableWidget* grid;

		//notice
		std::unique_ptr<QWidget> fenetre_notice;
		std::unique_ptr<QLabel> lab_notice;

		explicit AutoCell(QWidget* parent=nullptr);
		friend class NouveauModele;

	public:
		/// Obtenir une référence vers l'instance unique du singleton AutoCell
		static AutoCell& getInstance() {
			if(instance == nullptr) {
				instance.reset(new AutoCell);
			}
			return *instance;
		}

	public slots:
		//void chargerModele();
		//void listerModele(); //à faire en dernier
		/// slot pour charger les Reseau disponibles pour le modèle sélectionné
		void chargerGrilles();
		//void listerGrille(); //déjà réfléchir à la recopie
		//Reseau initialiserGrille(); //méthode à implémenter qui récupère les données du formulaire - penser à réinitialiser les données annexes
		//void afficherGrille(Reseau&); //affiche une grille
		//void chargerGrilles(const QString &text);
		/// Afficher un Reseau dans l'espace dédié
		/// @param[in] Grille pointeur vers le Reseau à afficher
		void afficherGrille(const Reseau* Grille);
		/// Initialiser un Reseau
		void initialiserGrille();
		/// Remettre à 0 la simulation
		void RAZ();
		/// Gérer la mise en route automatique ou non
		void gererSimulation();
		//void sauvegarderGrille();
		//Reseau& modifierCellule(const QModelIndex&, Reseau& Grille);//à implémenter
		/// Modifier l'état d'une cellule de la grille affichée (par clic par exemple)
		/// @param[in] index localisation de la cellule à modifier
		void modifierCellule(const QModelIndex& index);
		/// Sauvegarder le Reseau courant dans la BDD
		void sauvegarderGrille();
		/// Créer un nouveau modèle
		void defNouveauModele();
		/// Afficher une boîte d'erreur
		/// @param[in] msg Message à afficher
		void afficherErreur(QString& msg);
		/// Initialiser un Automate par son nom
		/// @param[in] name de l'Automate à initialiser
		void initAutomate(const QString& name);
		/// Changer le délai de l'Automate
		void changeDelai();
		/// Aller en arrière dans la simulation
		void previous();
		/// Aller en avant dans la simulation
		void next();
		/// Changer le comportement de la matrice aux frontières
		/// @param[in] val comportement à avoir (true = matrice torique, false = ignorer)
		void setMatriceTorique(int val);
		/// Revenir au réseau initial
		void reinitialiserSimulation();
		///Afficher la notice d'utilisation
		void afficherNotice();
};

#endif // AUTOCELL_H
