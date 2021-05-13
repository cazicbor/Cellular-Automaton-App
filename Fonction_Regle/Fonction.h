#ifndef _FONCTION_H
#define _FONCTION_H

class Regle {
	private:
		int seuilsMin[8];
		int seuilsMax[8];
		Etat destination;

	public:
		const Etat& getDestination() const { return destination; }
		bool verify(const Voisinage& voisins) const;
};

class RegleAvecEtatCourant: public Regle {
	private:
		Etat etatCourant;

	public:
		bool verify(const Voisinage& voisins, const Cellule& cellule) const;
};

class Fonction {
	private:
		Etat etatDefaut;
		Regle** regles;

	public:
		Fonction();
		~Fonction();
		const Etat& getEtatDefaut() const { return etatDefaut; }
		void setEtatDefaut(const Etat& nouveau) { etatDefaut = nouveau; }
		void ajouterRegle(const Etat& destination, const int seuils[8]);
		const Etat& getEtatSuivant(const Voisinage& voisins) const;
};

class FonctionAvecEtatCourant {
	private:
		Etat etatDefaut;
		RegleAvecEtatCourant** regles;
	
	public:
		FonctionAvecEtatCourant();
		~FonctionAvecEtatCourant();
		const Etat& getEtatDefaut() const { return etatDefaut; }
		void setEtatDefaut(const Etat& nouveau) { etatDefaut = nouveau; }
		void ajouterRegle(const Etat& destination, const int seuils[8], const Etat& courant);
		const Etat& getEtatSuivant(const Voisinage& voisins, const Cellule& cellule) const;
};

#endif
