#include "Fonction.h"

bool RegleAvecEtatCourant::verify(const Voisinage& voisins, const Cellule& cellule) const {
	if(cellule.getEtat() != etatCourant.getEtat())
		return false;

	int nb[8];

	VoisinageIterator *cellules = voisins.creerIterator();
	cellules.first()

	while(!cellules.isDone())
		nb[cellules.currentItem().getEtat()]++;

	delete cellules;

	for(int i = 0; i < 8; ++i)
		if(nb[i] < seuilMin[i] || nb[i] > seuilMax[i])
			return false;

	return true;
}

bool Regle::verify(const Voisinage& voisins) const {
	int nb[8];

	VoisinageIterator *cellules = voisins.creerIterator();
	cellules.first()

	while(!cellules.isDone())
		nb[cellules.currentItem().getEtat()]++;

	delete cellules;

	for(int i = 0; i < 8; i++)
		if(nb[i] < seuilMin[i] || nb[i] > seuilMax[i])
			return false;

	return true;
}

const Etat& Fonction::getEtatSuivant(const Voisinage& voisins) const {
	for(int i = 0; i < nbRegles; ++i)
		if (regles[i].verify(voisins))
			return regles[i].getDestination;

	return etatDefaut;
}

const Etat& FonctionAvecEtatCourant::getEtatSuivant(const Voisinage& voisins, const Cellule& cellule) const {
	for(int i = 0; i < nbRegles; ++i)
		if (regles[i].verify(voisins, cellule))
			return regles[i].getDestination;

	return etatDefaut;
}
