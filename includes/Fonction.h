#ifndef _FONCTION_H
#define _FONCTION_H

#include <memory>
#include <reseau_cellule_etats.h>
#include <voisinage.h>
#include <list>

/// Règle générale
///
/// Classe mère abstraite de toutes les règles, utilisé pour rendre le code évoluable, définir des règles au comportement totalement différent de ce que nous avons.
class RegleGen {
	private:
		Etat destination;

	public:
		RegleGen(const Etat& nDestination): destination(nDestination) {}
		virtual ~RegleGen() = default;
		/// Vérifier si une règle est vérifiée
		/// @param[in] voisins Le voisinage de la cellule pour laquelle on vérifie la règle
		/// @param[in] cellule La cellule pour laquelle on vérifie la règle
		virtual bool verify(const Voisinage& voisins, const Cellule& cellule) const = 0;
		/// Utilisé pour obtenir l'état courant de la règle s'il existe, n'a pas de sens pour toutes donc on préfère mettre -1 par défaut
		virtual int getCourant() const { return -1; }
		/// Obtenir la destination de cette règle
		const Etat& getDestination() const { return destination; }
};

/// Règle verifiant le nombre de voisins
///
/// Cette règle regarde le nombre de voisins dans un certain état pour être vérifiée.
class Regle: public RegleGen {
	protected:
		int seuilsMin[8];
		int seuilsMax[8];

	public:
		/// Construire une règle
		/// @param[in] nDestination Etat de destination en cas de validation de la règle
		/// @param[in] nSeuilsMax   Tableau de seuils à ne pas dépasser en nombre de voisins par état pour vérifier la règle
		/// @param[in] nSeuilsMin   Tableau de seuils à dépasser en nombre de voisins par état pour vérifier la règle
		Regle(const Etat& nDestination, const int nSeuilsMin[8], const int nSeuilsMax[8]);
		/// Vérifier si une règle est vérifiée
		/// @param[in] voisins Le voisinage de la cellule pour laquelle on vérifie la règle
		/// @param[in] cellule La cellule pour laquelle on vérifie la règle
		virtual bool verify(const Voisinage& voisins, const Cellule& cellule) const override;
		/// Obtenir le seuil minimum du nombre de voisins requis pour un état donné afin de valider la règle
		/// Principalement utilisé pour sauvegarder une règle de transition
		/// @param[in] i numéro de l'état
		int getMin(const size_t i) { if(i > 0 && i <= 8) return seuilsMin[i - 1]; else throw "Invalid number!"; }
		/// Obtenir le seuil maximum du nombre de voisins requis pour un état donné afin de valider la règle
		/// Principalement utilisé pour sauvegarder une règle de transition
		/// @param[in] i numéro de l'état
		int getMax(const size_t i) { if(i > 0 && i <= 8) return seuilsMax[i - 1]; else throw "Invalid number!"; }
};

/// Règle prenant en compte l'état courant
///
/// Cette règle en plus de vérifier le nombre de voisins, permet de vérifier l'état courant de la cellule à laquelle on applique la règle
class RegleAvecEtatCourant: public Regle {
	private:
		unsigned int etatCourant;

	public:
		/// Construire une règle
		/// @param[in] nDestination Etat de destination en cas de validation de la règle
		/// @param[in] nSeuilsMax   Tableau de seuils à ne pas dépasser en nombre de voisins par état pour vérifier la règle
		/// @param[in] nSeuilsMin   Tableau de seuils à dépasser en nombre de voisins par état pour vérifier la règle
		/// @param[in] nEtat        numéro de l'état courant de la cellule nécessaire pour vérifier la règle
		RegleAvecEtatCourant(const Etat& nDestination, const int nSeuilsMin[8], const int nSeuilsMax[8], const int nEtat);
		/// Vérifier si une règle est vérifiée
		/// @param[in] voisins Le voisinage de la cellule pour laquelle on vérifie la règle
		/// @param[in] cellule La cellule pour laquelle on vérifie la règle
		bool verify(const Voisinage& voisins, const Cellule& cellule) const override;
		/// Obtenir l'état courant requis pour valider la règle
		/// Principalement utilisé pour sauvegarder une règle de transition
		int getCourant() const override { return static_cast<int>(etatCourant); }
};

/// Fonction de transition
///
/// Cette fonction permet de regrouper des règles et de connaître l'état suivant d'une cellule
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
		/// Accesseur sur la liste de règles, il est impossible de modifier les règles de cette manière, la liste est en lecture seule
		const std::list<Regle*>& getRules() const { return regles; }
};

#endif
