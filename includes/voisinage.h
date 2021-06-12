//
//  voisinage.h
//  LO21-Projet
//
//  Created by Maxime Goret on 20/04/2021.
//

#ifndef voisinage_h
#define voisinage_h

#include"reseau_cellule_etats.h"
#include"coordonnees.h"
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
#include"parametragemodele.h"


using namespace std;

/// Classe conteneur d'un voisinage
///
/// Elle contient l'ensemble des voisins d'une cellule après application d'une règle de voisinage et définit la cellule au centre du voisinage
class Voisinage {
	private :
		const Cellule* celluleCentre;
		vector<Cellule*> voisinage;

		friend class RegleVoisinage;
		friend class RegleVoisinageMoore;
		friend class RegleVoisinageNeumann;
		friend class RegleVoisinageArbitraire;
		friend class VoisinageIterator;

	public:
		/// Classe d'itérateur sur les cellules contenus dans le voisinage
		class VoisinageIterator {
			const Voisinage *vsn;
			size_t i;

			public :
				///Construire un itérateur sur le voisinage
				VoisinageIterator(const Voisinage *v) { vsn = v; }
				/// place l'itérateur sur le premier élément
				void first() { i = 0; }
				/// placer l'itérateur sur l'élément suivant
				void next() { i++; }
				/// vérifier si les itérations sont terminées
				bool isDone() { return !(i < vsn->voisinage.size()); }
				/// Récupérer l'élément courant de l'itérateur
				Cellule* currentItem() { return vsn->voisinage[i]; }
		};

		Voisinage(const Cellule* centre): celluleCentre(centre) {}
		~Voisinage();
		/// Obtenir la cellule au centre du voisinage
		Cellule getCelluleCentre() const { return *celluleCentre; }
		/// Créer un itérateur sur les cellules du voisinage
		VoisinageIterator *creerIterator() const { return new VoisinageIterator(this); }
};

/// Classe mère abtraite de toutes les règles de voisinage
class RegleVoisinage{
	private:
		bool matriceTorique;

	public :
		/// Calculer un voisinage sur un réseau à partir de la règle
		/// @param[in] v Objet Voisinage dans lequel on souhaite stocker les voisins
		/// @param[in] r Réseau à partir duquel on souhaite calculer le voisinage
		virtual void calculVoisinage(Voisinage& v, const Reseau& r) const = 0;
		/// Obtenir le type de la règle de voisinage
		///
		/// Principalement utilisé pour la sauvegarde
		virtual int getType() const = 0;
		/// Renvoie le rayon d'une règle de voisinage, 0 si ce n'est pas pertinant pour ce voisinage (arbitraire, ...)
		///
		/// Principalement utilisé pour la sauvegarde
		virtual unsigned int getr() const { return 0; }
		virtual ~RegleVoisinage() = default;
		/// Définir le comportement aux frontières du voisinage
		///
		/// Si true, on se comporte comme une matrice torique, quand on arrive en haut on continu en utilisant les lignes du bas, de même pour quand on est à gauche ou à droite de la matrice
		/// Si false, on ne prend pas en compte les voisins au delà de la matrice affichée.
		/// @param[in] val valeur de la propriété
		void setMatriceTorique(const bool val) { matriceTorique = val; }
		/// Obtenir l'état du comportement aux frontières
		bool getMatriceTorique() const { return matriceTorique; }
};

/// Règle générale pour un voisinage de Von Neumann
class RegleVoisinageNeumann : public RegleVoisinage {
	private:
		unsigned int rayon;
	public:
		/// Calculer un voisinage sur un réseau à partir de la règle
		/// @param[in] v Objet Voisinage dans lequel on souhaite stocker les voisins
		/// @param[in] r Réseau à partir duquel on souhaite calculer le voisinage
		void calculVoisinage(Voisinage& v, const Reseau& r) const override;
		/// Définir le rayon du voisinage
		void setr(unsigned int r) { rayon = r; }
		/// Obtenir le rayon du voisinage
		unsigned int getr() const override { return rayon; }
		/// Obtenir le type de la règle de voisinage
		///
		/// Principalement utilisé pour la sauvegarde
		int getType() const override { return 1; }
};

/// Règle générale pour un voisinage de Moore
class RegleVoisinageMoore : public RegleVoisinage {
	private:
		unsigned int rayon;
	public:
		/// Calculer un voisinage sur un réseau à partir de la règle
		/// @param[in] v Objet Voisinage dans lequel on souhaite stocker les voisins
		/// @param[in] r Réseau à partir duquel on souhaite calculer le voisinage
		void calculVoisinage(Voisinage& v, const Reseau& r) const override;
		/// Définir le rayon du voisinage
		void setr(unsigned int r) { rayon = r; }
		/// Obtenir le rayon du voisinage
		unsigned int getr() const override { return rayon; }
		/// Obtenir le type de la règle de voisinage
		///
		/// Principalement utilisé pour la sauvegarde
		int getType() const override { return 2; }
};

///définit la règle pour le voisinage arbitraire
class RegleVoisinageArbitraire : public RegleVoisinage {
	public:
		/// Obtenir le type de la règle de voisinage
		///
		/// Principalement utilisé pour la sauvegarde
		int getType() const override{ return 3; }
		/// Obtenir le nombre de voisins de cette règle de voisinage
		unsigned int getNbVoisin() { return coordonnees.size(); }
		/// coordonnées relatives des voisins d'une cellule
		vector<Coordonnees> coordonnees;
		/// Calculer un voisinage sur un réseau à partir de la règle
		/// @param[in] v Objet Voisinage dans lequel on souhaite stocker les voisins
		/// @param[in] r Réseau à partir duquel on souhaite calculer le voisinage
		void calculVoisinage(Voisinage& v, const Reseau& r) const override;
		/// Obtenir les coordonnées relative d'un voisinage arbitraire en fonction d'un outil QTableWidget
		void getVoisinage(const QTableWidget* grid );
};

#endif /* voisinage_h */
