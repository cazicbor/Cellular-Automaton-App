#ifndef _FONCTION_H
#define _FONCTION_H

#include <memory>
#include <reseau_cellule_etats.h>
#include <voisinage.h>

class Regle {
	protected:
		int seuilsMin[8];
		int seuilsMax[8];

	private:
		Etat destination;

	public:
		/// Construire une règle
		/// @param[in] nDestination Etat de destination en cas de validation de la règle
		/// @param[in] nSeuilsMax   Tableau de seuils à ne pas dépasser en nombre de voisins par état pour vérifier la règle
		/// @param[in] nSeuilsMin   Tableau de seuils à dépasser en nombre de voisins par état pour vérifier la règle
		Regle(const Etat& nDestination, const int nSeuilsMax[8], const int nSeuilsMin[8]);
		virtual ~Regle() = default;
		/// Obtenir la destination de cette règle
		const Etat& getDestination() const { return destination; }
		/// Vérifier si une règle est vérifiée
		/// @param[in] voisins Le voisinage de la cellule pour laquelle on vérifie la règle
		/// @param[in] cellule La cellule pour laquelle on vérifie la règle
		virtual bool verify(const Voisinage& voisins, const Cellule& cellule) const;
};

class RegleAvecEtatCourant: public Regle {
	private:
		unsigned int etatCourant;

	public:
		/// Construire une règle
		/// @param[in] nDestination Etat de destination en cas de validation de la règle
		/// @param[in] nSeuilsMax   Tableau de seuils à ne pas dépasser en nombre de voisins par état pour vérifier la règle
		/// @param[in] nSeuilsMin   Tableau de seuils à dépasser en nombre de voisins par état pour vérifier la règle
		/// @param[in] nEtat        numéro de l'état courant de la cellule nécessaire pour vérifier la règle
		RegleAvecEtatCourant(const Etat& nDestination, const int nSeuilsMax[8], const int nSeuilsMin[8], const int nEtat);
		/// Vérifier si une règle est vérifiée
		/// @param[in] voisins Le voisinage de la cellule pour laquelle on vérifie la règle
		/// @param[in] cellule La cellule pour laquelle on vérifie la règle
		bool verify(const Voisinage& voisins, const Cellule& cellule) const;
};

class Fonction {
	private:
		std::list<Regle*> regles;
		Etat etatDefaut;

	public:
		/// Construire une fonction de transition
		/// @param[in] etat État par défaut à retourner si aucune règle définie n'est satisfaite
		Fonction(const Etat& etat):etatDefaut(etat){}
		virtual ~Fonction();
		/// Obtenir l'état par défaut de cette fonction
		const Etat& getEtatDefaut() const { return etatDefaut; }
		/// Définir l'état par défaut de cette fonction
		/// @param[in] nouveau Nouvel état par défaut de la fonction
		void setEtatDefaut(const Etat& nouveau) { etatDefaut = nouveau; }
		/// Ajouter une règle à la fonction
		/// @param[in] nDestination Etat de destination en cas de validation de la règle
		/// @param[in] nSeuilsMax   Tableau de seuils à ne pas dépasser en nombre de voisins par état pour vérifier la règle
		/// @param[in] nSeuilsMin   Tableau de seuils à dépasser en nombre de voisins par état pour vérifier la règle
		void ajouterRegle(const Etat& destination, const int seuilsMin[8], const int seuilsMax[8]);
		/// Ajouter une règle prenant en compte l'état courant à la fonction
		/// @param[in] nDestination Etat de destination en cas de validation de la règle
		/// @param[in] nSeuilsMax   Tableau de seuils à ne pas dépasser en nombre de voisins par état pour vérifier la règle
		/// @param[in] nSeuilsMin   Tableau de seuils à dépasser en nombre de voisins par état pour vérifier la règle
		/// @param[in] nEtat        numéro de l'état courant de la cellule nécessaire pour vérifier la règle
		void ajouterRegle(const Etat& destination, const int seuilsMin[8], const int seuilsMax[8], const int etat);
		/// Appliquer la fonction de transition à une cellule et obtenir son prochain état
		/// @param[in] voisins voisins de la cellule à laquelle appliquer la fonction
		/// @param[in] cellule cellule à laquelle appliquer la fonction
		virtual const Etat& getEtatSuivant(const Voisinage& voisins, const Cellule& cellule) const;
};

#endif
