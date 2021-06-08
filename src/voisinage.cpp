#include"voisinage.h"
#include"reseau_cellule_etats.h"
#include<cmath>
#include<iostream>

void Voisinage::setr(unsigned int rayon){
	if(rayon >= 0)
		r = rayon;
	else
		throw ("Rayon incorrect !\n");
}

void RegleVoisinageNeumann::calculVoisinage(Voisinage& v, const Reseau& r) {
	v.voisinage = std::vector<Cellule*>();
	int nb = 0;
	unsigned int abs = v.celluleCentre->abs;
	unsigned int ord = v.celluleCentre->ord;
	unsigned int hauteur = r.getHauteur();
	unsigned int largeur = r.getLargeur();

	for (int i = -v.r; i <= v.r; i++)
		for (int j = -v.r; j <= v.r; j++)
			if (abs(i) + abs(j) <= v.r && i != 0 && j != 0)
				v.voisinage.push_back(&r.getReseau()[(abs+i)%hauteur][(ord+j)%largeur]);
}

void RegleVoisinageMoore::calculVoisinage(Voisinage& v, const Reseau& r) {
	v.voisinage = std::vector<Cellule*>();
	int nb = 0;
	unsigned int abs = v.celluleCentre->abs;
	unsigned int ord = v.celluleCentre->ord;
	unsigned int hauteur = r.getHauteur();
	unsigned int largeur = r.getLargeur();

	for (int i = -v.r; i <= v.r; i++)
		for (int j = -v.r; j <= v.r; j++)
			if (abs(i) <= v.r && abs(j) <= v.r && i != 0 && j != 0)
				v.voisinage.push_back(&r.getReseau()[(abs+i)%hauteur][(ord+j)%largeur]);
}

Voisinage::~Voisinage() {
	voisinage.clear();
}

void RegleVoisinageArbitraire::calculVoisinage(Voisinage &v, const Reseau& r) { //définir get?
	v.voisinage = std::vector<Cellule*>();
	
	unsigned int abs = v.celluleCentre->abs;
	unsigned int ord = v.celluleCentre->ord;
	unsigned int hauteur = r.getHauteur();
	unsigned int largeur = r.getLargeur();

	for (int nb = 0; nb < coordonnees.size(); nb++){
		v.voisinage[nb] = &r.getReseau()[abs - coordonnees[nb].getx()] [ord - coordonnees[nb].gety()];
	}
}

Coordonnees RegleVoisinageArbitraire::getVoisinage(const Reseau& r) {
	
	vector<Coordonnees> coordonnees;

	Cellule* cellulecentre = getCelluleCentre();
	

	for (int k = 0; k < nbVoisin; k++) {
		unsigned int i, j;
		while (i >= r.getHauteur() || j >= r.getLargeur()) {
			cout << "Entrez l'abscisse de la" << k << "ieme cellule.\n";
			cin >> i;
			cout << "Entrez l'ordonnee de la " << k << "ieme cellule.\n";
			cin >> j;
			if (i >= r.getHauteur() || j >= r.getLargeur())
				cout << "Coordonnees incorrectes !\n";
		}
		if (i < r.getHauteur() && j < r.getLargeur()) {
			coordonnees[k].x = cellulecentre->abs - i;
			coordonnees[k].y = cellulecentre->ord - j;
		}
	}

	return coordonnees;
	// While (!utilisateur clique sur bouton valider){
		//recuprer abs et ord de Cellule slectionne;
		//rentrer la diffrence des coordonnes dans le vecteur co
	//}

}
