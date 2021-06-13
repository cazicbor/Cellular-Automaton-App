#pragma once
#include <iostream>
#include <array>
#include <QColor>

using namespace std;

/// Classe représentant la cellule
class Cellule{
	private:
		unsigned int indEtat;
		unsigned int abs;
		unsigned int ord;
		//inline Cellule():indEtat(0), abs(0), ord(0){};
		void initCellule(const unsigned int ind, const unsigned int &x, const unsigned int &y);
		friend class Reseau;
		friend class RegleVoisinage;
		friend class RegleVoisinageNeumann;
		friend class RegleVoisinageMoore;
		friend class RegleVoisinageArbitraire;

	public:
		/// Obtenir l'indice de l'état correspondant à cette cellule
		inline unsigned int getIndEtat() const {return indEtat;}
		/// Incrémenter l'état de la cellule
		///
		/// Retourne à 0 quand on a atteint l'état maximal
		void incrementerEtat();
		/// Construire une cellule
		Cellule();
		/// Construire une cellule par recopie
		Cellule(const Cellule& c): indEtat(c.indEtat), abs(c.abs), ord(c.ord) {}
};

/// Classe représentant un état
class Etat{
	private:
		unsigned int indice;
		std::string label;
		QColor color;
		Etat(unsigned int ind, std::string lab, int r = 0, int g = 0, int b = 0):
		indice(ind),label(lab),color(r,g,b){}
		Etat(unsigned int ind, std::string lab, QColor col):
		indice(ind),label(lab),color(col){} //constructeur privé (l'utilisateur ne doit pas pouvoir créer un Etat par ce biais)
		friend class EnsembleEtat;

	public:
		/// Obtenir le label d'un état
		std::string getLabel() const { return label; }
		/// Obtenir la couleur d'un état
		QColor getColor() const { return color; }
		/// Obtenir l'indice correspondant à un état
		unsigned int getIndice() const { return indice; }
};

/// Regroupement cohérent d'états
class EnsembleEtat{
	private:
		size_t nbEtats = 0;
		static const size_t nbEtatsMax = 10;
		Etat* ensEtats[nbEtatsMax];
		EnsembleEtat(const EnsembleEtat&) = delete;
		EnsembleEtat operator=(const EnsembleEtat&) = delete;

	public:
		EnsembleEtat();
		~EnsembleEtat();
		/// Ajouter un état à l'ensemble
		/// @param[in] ind indice correspondant à l'état
		/// @param[in] lab label correspondant à l'état
		/// @param[in] r   niveau de rouge de la couleur de l'état
		/// @param[in] g   niveau de vert de la couleur de l'état
		/// @param[in] b   niveau de bleu de la couleur de l'état
		void ajouterEtat(unsigned int ind, std::string lab,int r = 0, int g = 0, int b = 0);
		/// Supprimer un état par son indice
		/// @param[in] ind indice de l'état à supprimer
		void supprimerEtat(const unsigned int ind);
		/// Initialisation du tableau d'Etats à partir d'un tableau externe
		/// @param[in] init_etats tableau d'Etat
		void initEtat(const Etat* init_etats = nullptr);
		/// obtenir une référence vers un état par son indice
		/// @param[in] ind indice de l'état à obtenir
		Etat& getEtat(const unsigned int &ind) { return *ensEtats[ind]; }
		/// Obtenir le nombre d'état disponibles
		unsigned int getNbEtats() const { return nbEtats; }
		/// Remettre à l'état vide l'ensemble
		void reset();
};

/// @brief Classe correspondant à un réseau d'une simulation
///
/// Un ensemble fini de cellules en 2 dimensions
class Reseau{
	private:
		unsigned int hauteur;
		unsigned int largeur;
		Cellule** reseau;

	public:
		/// Obtenir la largeur du réseau
		int getLargeur() const { return largeur; }
		/// Obtenir la hauteur du réseau
		int getHauteur() const { return hauteur; }
		/// Remplir aléatoirement un réseau
		Reseau& setAleatoire();
		/// Obtenir le tableau de cellules du réseau
		Cellule** getReseau() const { return reseau; }
		/// Construire un réseau
		/// @param[in] h Hauteur du réseau
		/// @param[in] l Largeur du réseau
		Reseau(const unsigned int &h, const unsigned int &l);
		/// Construire un réseau par recopie d'un autre
		/// @param[in] r Réseau à recopier
		Reseau(const Reseau& r);
		~Reseau();
		/// copier un réseau dans un autre existant
		/// @param[in] r Réseau à recopier
		Reseau& operator=(const Reseau& r);
		/// Comparer deux réseaux pour vérifier une égalité
		/// @param[in] r Réseau à comparer
		bool operator==(const Reseau& r);
};
