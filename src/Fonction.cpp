#include <Fonction.h>

bool RegleAvecEtatCourant::verify(const Voisinage& voisins, const Cellule& cellule) const {
	if(cellule.getIndEtat() != etatCourant)
		return false;

	int nb[8] = {0};

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

bool Regle::verify(const Voisinage& voisins, const Cellule& cellule) const {
	int nb[8] = {0};

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

const Etat& Fonction::getEtatSuivant(const Voisinage& voisins, const Cellule& cellule) const {
	for(const auto& regle: regles)
		if (regle->verify(voisins, cellule))
			return regle->getDestination();

	return etatDefaut;
}

void Fonction::ajouterRegle(const Etat& destination, const int seuilsMin[8], const int seuilsMax[8]) {
	regles.push_back(new Regle(destination, seuilsMin, seuilsMax));
}

void Fonction::ajouterRegle(const Etat& destination, const int seuilsMin[8], const int seuilsMax[8], const int etat) {
	regles.push_back(new RegleAvecEtatCourant(destination, seuilsMin, seuilsMax, etat));
}

Fonction::~Fonction() {
	for(auto& regle: regles)
		delete regle;
}

Regle::Regle(const Etat& nDestination, const int nSeuilsMin[8], const int nSeuilsMax[8]): destination(nDestination) {
	for(int i = 0; i < 8; ++i)
		seuilsMin[i] = nSeuilsMin[i];

	for(int i = 0; i < 8; ++i)
		seuilsMax[i] = nSeuilsMax[i];
}

RegleAvecEtatCourant::RegleAvecEtatCourant(const Etat& nDestination, const int nSeuilsMin[8], const int nSeuilsMax[8], const int nEtat): Regle(nDestination, nSeuilsMin, nSeuilsMax), etatCourant(nEtat) {
}
