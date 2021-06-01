#ifndef _FONCTION_H
#define _FONTION_H


class Regle {
	int* seuil[8]; //seuil : valeurs minimales pour chacun des états dans le voisinage pour valider la règle en question
	Etat destination;
public:
	bool verify(Voisinage& voisins) const;
	const Etat& getDestination() const { return destination; }
};

class RegleAvecEtatCourant : public Regle {
	Etat etatCourant;
public:
	bool verify(Voisinage& voisins, Cellule& cellule) const;
};

class Fonction {
	Etat defaut;
	Regle** regle;
public:
	Fonction();
	~Fonction();
	const Etat& getEtatDefaut() const { return defaut; }
	void setEtatDefaut(const Etat& nouv) { defaut = nouv; }
	void ajouterRegle(const Etat& destination, const int* seuil[8]);
	void ajouterRegle(Etat& destination, int* seuil, Etat& etatCourant);
	const Etat& getEtatSuivant(Cellule& cellule, Voisinage& voisins) const;



};

#endif
