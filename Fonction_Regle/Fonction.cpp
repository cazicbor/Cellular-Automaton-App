#include "Fonction.h"

bool RegleAvecEtatCourant::verify(const Voisinage& voisins, const Cellule& cellule) const {
	if(cellule.getIndEtat() != etatCourant)
		return false;

	int nb[8];

	auto *cellules = voisins.creerIterator();
	cellules->first();

	while(!cellules->isDone())
		nb[cellules->currentItem()->getIndEtat()]++;

	delete cellules;

	for(int i = 0; i < 8; ++i)
		if(nb[i] < seuilsMin[i] || nb[i] > seuilsMax[i])
			return false;

	return true;
}

bool Regle::verify(const Voisinage& voisins) const {
	int nb[8];

	auto *cellules = voisins.creerIterator();
	cellules->first();

	while(!cellules->isDone())
		nb[cellules->currentItem()->getIndEtat()]++;

	delete cellules;

	for(int i = 0; i < 8; i++)
		if(nb[i] < seuilsMin[i] || nb[i] > seuilsMax[i])
			return false;

	return true;
}

const Etat& Fonction::getEtatSuivant(const Voisinage& voisins) const {
	for(int i = 0; i < nbRegles; ++i)
		if (regles[i]->verify(voisins))
			return regles[i]->getDestination();

	return etatDefaut;
}

const Etat& FonctionAvecEtatCourant::getEtatSuivant(const Voisinage& voisins, const Cellule& cellule) const {
	for(int i = 0; i < nbRegles; ++i)
		if (regles[i]->verify(voisins, cellule))
			return regles[i]->getDestination();

	return etatDefaut;
}

void Fonction::ajouterRegle(const Etat& destination, const int seuilsMin[8], const int seuilsMax[8]) {
	Regle** nouveau = new Regle*[nbRegles + 1];

	for(int i = 0; i < nbRegles; ++i)
		nouveau[i] = regles[i];

	nouveau[nbRegles] = new Regle(destination, seuilsMin, seuilsMax);
	++nbRegles;
	delete[] regles;
	regles = nouveau;
}

void FonctionAvecEtatCourant::ajouterRegle(const Etat& destination, const int seuilsMin[8], const int seuilsMax[8], const int etat) {
	RegleAvecEtatCourant** nouveau = new RegleAvecEtatCourant*[nbRegles + 1];

	for(int i = 0; i < nbRegles; ++i)
		nouveau[i] = regles[i];

	nouveau[nbRegles] = new RegleAvecEtatCourant(destination, seuilsMin, seuilsMax, etat);
	++nbRegles;
	delete[] regles;
	regles = nouveau;
}

Fonction::~Fonction() {
	for(int i = 0; i < nbRegles; ++i)
		delete regles[i];

	delete[] regles;
}

FonctionAvecEtatCourant::~FonctionAvecEtatCourant() {
	for(int i = 0; i < nbRegles; ++i)
		delete regles[i];

	delete[] regles;
}

Regle::Regle(const Etat& nDestination, const int nSeuilsMin[8], const int nSeuilsMax[8]): destination(nDestination) {
	for(int i = 0; i < 8; ++i)
		seuilsMin[i] = nSeuilsMin[i];

	for(int i = 0; i < 8; ++i)
		seuilsMax[i] = nSeuilsMax[i];
}

RegleAvecEtatCourant::RegleAvecEtatCourant(const Etat& nDestination, const int nSeuilsMin[8], const int nSeuilsMax[8], const int nEtat): Regle(nDestination, nSeuilsMin, nSeuilsMax), etatCourant(nEtat) {
}
