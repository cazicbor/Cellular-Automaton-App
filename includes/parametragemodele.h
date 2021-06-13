#ifndef PARAMETRAGEMODELE_H
#define PARAMETRAGEMODELE_H

#include <reseau_cellule_etats.h>
#include <paramalpha.h>
#include <autocell.h>

#include <QObject>
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
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
#include <QBrush>
#include <QMouseEvent>

using namespace std;

/// @brief Cette classe définit la fenêtre de paramétrage de l'Automate
///
/// Le but est de pouvoir choisir la RegleVoisinage, les Etat et la Fonction de transition
class NouveauModele : public QWidget {
		Q_OBJECT
		QGridLayout* general;

		//définition de la frame paramétrage du modèle
		QWidget* fenetre_init;
		QLabel* label_init;
		QGridLayout* form_init;

		QFormLayout* form_choix;

		QLineEdit* nom_modele;
		QLineEdit* nom_automate;
		QLineEdit* auteur;
		QLineEdit* annee;
		QLineEdit* description;

		QSpinBox* nb_etats;
		QComboBox* liste_voisinage;
		QComboBox* liste_regle_transition = nullptr;
		QPushButton* bouton_valide;

		QPushButton* valider_Etat = nullptr;
		QPushButton* valider_EtatDefault = nullptr;

		QHBoxLayout* layoutvalid = nullptr;

		//definition frame règle de transitions
		QWidget* fenetre_regle;
		QLabel* seuilMax= nullptr;
		QLabel* seuilMin= nullptr;
		QLabel* destination= nullptr;
		QLabel* etatCourant= nullptr;
		QLabel* etatCourant2 = nullptr;
		QLabel* etat_d = nullptr;
		QLabel* etat= nullptr;

		QComboBox* valid_Etat;
		QSpinBox* numEtatCourant = nullptr;
		QSpinBox* etatDest= nullptr;
		QSpinBox* etat_default = nullptr;

		QPushButton* fin = nullptr;
		QPushButton* next = nullptr;
		QIntValidator* seuilValidator;
		QLineEdit* numSeuilMin[8];
		QLineEdit* numSeuilMax[8];

		QVBoxLayout* layoutv = nullptr;
		QHBoxLayout* layouth1 = nullptr;
		QHBoxLayout* layouth2 = nullptr;
		QHBoxLayout* layouth3 = nullptr;
		QHBoxLayout* layouth4 = nullptr;
		QHBoxLayout* layouth = nullptr;

		QVBoxLayout* layoutv2 = nullptr;
		QHBoxLayout* layouth5 = nullptr;
		QHBoxLayout* layouth6 = nullptr;

		QHBoxLayout* layoutEtat;

		//définition de la frame paramétrage du choix
		QWidget* fenetre_param;
		QGridLayout* form_param;
		QLabel* label_param;

		//Voisiange non arbitraire
		QFormLayout* form_rayon = nullptr;
		QSpinBox* rayon;

		//définition de la frame contenant la grille de sélection du voisinage
		QTableWidget* grid = nullptr;
		std::unique_ptr<ParamAlpha> paramAlpha;
		QPushButton* boutonEtat;

		AutoCell* nvAutocell = nullptr;

	public:
		/// Construire la fenêtre de paramétrage de l'Automate
		NouveauModele(QWidget* parent = nullptr);
	public slots:
		/// Permet d'ouvir le formulaire de paramétrage de la RegleVoisinage
		/// @param[in] choix_voisinage nom du type de voisinage choisi
		void paramVoisinage(const QString& choix_voisinage);
		/// Initialise la Fonction de transition de l'automate et affiche les choix disponibles pour le voisinage
		void changerVoisinage();
		/// Affiche la grille de paramétrage de RegleVoisinageArbitraire
		void affGrille();
		/// Gère la sélection ou non d'une cellule dans le voisinage
		void modifGrille(const QModelIndex& index);
		/// Affiche la première partie du formulaire de paramétrage d'une Regle de transition
		void paramRegle();
		/// Termine l'initialisation de l'Automate et ferme la fenêtre
		void validerParametrage();
		/// Affiche la seconde partie du formulaire de paramétrage de la Regle de transition
		/// @param[in] validEtat définit si on prend ou non l'état courant de la cellule en compte
		void choisirEtatCourant(const QString& validEtat);
		/// Permet de paramétrer l'alphabet de l'Automate grâce à la classe ParamAlpha
		void parametrerEtats();
		/// Permet de valider la Regle de transition courante et d'en configurer une nouvelle
		void addRegle();
		/// Permet de changer l'Etat par défaut d'une Fonction de transition
		void changerEtatDefault();
		/// termine la configuration de l'Automate et permet d'afficher un bouton pour fermer la configuration
		void validation();
};


#endif // PARAMETRAGEMODELE_H
