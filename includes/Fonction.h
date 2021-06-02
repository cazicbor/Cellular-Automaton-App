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
		Regle(const Etat& nDestination, const int nSeuilsMax[8], const int nSeuilsMin[8]);
		virtual ~Regle() = default;
		const Etat& getDestination() const { return destination; }
		virtual bool verify(const Voisinage& voisins, const Cellule& cellule) const;
};

class RegleAvecEtatCourant: public Regle {
	private:
		unsigned int etatCourant;

	public:
		RegleAvecEtatCourant(const Etat& nDestination, const int nSeuilsMax[8], const int nSeuilsMin[8], const int nEtat);
		bool verify(const Voisinage& voisins, const Cellule& cellule) const;
};

class Fonction {
	private:
		std::list<Regle*> regles;
		Etat etatDefaut;

	public:
		Fonction(const Etat& etat):etatDefaut(etat){}
		virtual ~Fonction();
		const Etat& getEtatDefaut() const { return etatDefaut; }
		void setEtatDefaut(const Etat& nouveau) { etatDefaut = nouveau; }
		void ajouterRegle(const Etat& destination, const int seuilsMin[8], const int seuilsMax[8]);
		void ajouterRegle(const Etat& destination, const int seuilsMin[8], const int seuilsMax[8], const int etat);
		virtual const Etat& getEtatSuivant(const Voisinage& voisins, const Cellule& cellule) const;
};

#endif
