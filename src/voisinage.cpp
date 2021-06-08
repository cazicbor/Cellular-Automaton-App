#include"voisinage.h"
#include"reseau_cellule_etats.h"
#include<cmath>
#include<iostream>

void RegleVoisinageNeumann::setr(unsigned int r){
	if(r >= 0)
		rayon = r;
	else
		throw ("Rayon incorrect !\n");
}

void RegleVoisinageMoore::setr(unsigned int r){
	if(r >= 0)
		rayon = r;
	else
		throw ("Rayon incorrect !\n");
}

void RegleVoisinageNeumann::calculVoisinage(Voisinage& v, const Reseau& r) const {
	v.voisinage = std::vector<Cellule*>();
	int nb = 0;
	unsigned int cellX = v.celluleCentre->abs;
	unsigned int cellY = v.celluleCentre->ord;
	unsigned int hauteur = r.getHauteur();
	unsigned int largeur = r.getLargeur();

	for (int i = -rayon; i <= rayon; i++)
		for (int j = -rayon; j <= rayon; j++)
			if (abs(i) + abs(j) <= rayon && i != 0 && j != 0)
				v.voisinage.push_back(&r.getReseau()[(cellY+i)%hauteur][(cellX+j)%largeur]);
}

void RegleVoisinageMoore::calculVoisinage(Voisinage& v, const Reseau& r) const {
	v.voisinage = std::vector<Cellule*>();
	int nb = 0;
	unsigned int cellX = v.celluleCentre->abs;
	unsigned int cellY = v.celluleCentre->ord;
	unsigned int hauteur = r.getHauteur();
	unsigned int largeur = r.getLargeur();

	for (int i = -rayon; i <= rayon; i++)
		for (int j = -rayon; j <= rayon; j++)
			if (abs(i) <= rayon && abs(j) <= rayon && i != 0 && j != 0)
				v.voisinage.push_back(&r.getReseau()[(cellY+i)%hauteur][(cellX+j)%largeur]);
}

Voisinage::~Voisinage() {
	voisinage.clear();
}

void RegleVoisinageArbitraire::calculVoisinage(Voisinage &v, const Reseau& r) const { //définir get?
	v.voisinage = std::vector<Cellule*>();
	
	unsigned int abs = v.celluleCentre->abs;
	unsigned int ord = v.celluleCentre->ord;
	unsigned int hauteur = r.getHauteur();
	unsigned int largeur = r.getLargeur();

	for (int nb = 0; nb < coordonnees.size(); nb++){
		v.voisinage[nb] = &r.getReseau()[abs - coordonnees[nb].x] [ord - coordonnees[nb].y];
	}
}

//Coordonnees RegleVoisinageArbitraire::getVoisinage(const Reseau& r) {
//	
//	vector<Coordonnees> coordonnees;
//
//	Cellule* cellulecentre = celluleCentre;
//	
//
//	for (int k = 0; k < nbVoisin; k++) {
//		unsigned int i, j;
//		while (i >= r.getHauteur() || j >= r.getLargeur()) {
//			cout << "Entrez l'abscisse de la" << k << "ieme cellule.\n";
//			cin >> i;
//			cout << "Entrez l'ordonnee de la " << k << "ieme cellule.\n";
//			cin >> j;
//			if (i >= r.getHauteur() || j >= r.getLargeur())
//				cout << "Coordonnees incorrectes !\n";
//		}
//		if (i < r.getHauteur() && j < r.getLargeur()) {
//			coordonnees[k].x = cellulecentre->abs - i;
//			coordonnees[k].y = cellulecentre->ord - j;
//		}
//	}
//
//	return coordonnees;
//	// While (!utilisateur clique sur bouton valider){
//		//recuprer abs et ord de Cellule slectionne;
//		//rentrer la diffrence des coordonnes dans le vecteur co
//	//}
//
//}
