#ifndef _FONCTION_H
#define _FONCTION_H

#include "../Reseau_Cellule_Etat/reseau_cellule_etats.h"
#include "../Voisinage/voisinage.hpp"

class Regle {
	protected:
		int seuilsMin[8];
		int seuilsMax[8];

	private:
		Etat destination;

	public:
		Regle(const Etat& nDestination, const int nSeuilsMax[8], const int nSeuilsMin[8]);
		const Etat& getDestination() const { return destination; }
		bool verify(const Voisinage& voisins) const;
};

class RegleAvecEtatCourant: public Regle {
	private:
		int etatCourant;

	public:
		RegleAvecEtatCourant(const Etat& nDestination, const int nSeuilsMax[8], const int nSeuilsMin[8], const int nEtat);
		bool verify(const Voisinage& voisins, const Cellule& cellule) const;
};

class Fonction {
	private:
		Etat etatDefaut;
		Regle** regles;
		int nbRegles;

	public:
		Fonction(const Etat& etat):regles(nullptr),nbRegles(0),etatDefaut(etat){}
		~Fonction();
		const Etat& getEtatDefaut() const { return etatDefaut; }
		void setEtatDefaut(const Etat& nouveau) { etatDefaut = nouveau; }
		void ajouterRegle(const Etat& destination, const int seuilsMin[8], const int seuilsMax[8]);
		const Etat& getEtatSuivant(const Voisinage& voisins) const;
};

class FonctionAvecEtatCourant {
	private:
		Etat etatDefaut;
		RegleAvecEtatCourant** regles;
		int nbRegles;
	
	public:
		FonctionAvecEtatCourant(const Etat& etat):regles(nullptr),nbRegles(0),etatDefaut(etat){}
		~FonctionAvecEtatCourant();
		const Etat& getEtatDefaut() const { return etatDefaut; }
		void setEtatDefaut(const Etat& nouveau) { etatDefaut = nouveau; }
		void ajouterRegle(const Etat& destination, const int seuilsMin[8], const int seuilsMax[8], const int etat);
		const Etat& getEtatSuivant(const Voisinage& voisins, const Cellule& cellule) const;
};

#endif
