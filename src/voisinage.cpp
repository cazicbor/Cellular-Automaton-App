#include"voisinage.h"
#include"reseau_cellule_etats.h"
#include<cmath>
#include<iostream>

void Voisinage::setr(unsigned int rayon){
   if(rayon >= 0)
        r = rayon;
	else throw ("Rayon incorrect !\n");
	 
}

void RegleVoisinage::setNbVoisins(unsigned int r) {
	if (r == 0) { //voisinage arbitraire
        cout << "Entrez le nombre de voisins.\n";
        cin >> nbVoisin;
	}
}

void RegleVoisinageNeumann::setNbVoisins(unsigned int r) {
	if (r == 1) { // voisinage de von Neumann
		nbVoisin = 4;
	}
	else { // voisiange de von Neumann avec un rayon
		nbVoisin = 2 * r * (1 + r);
	}
}

void RegleVoisinageMoore::setNbVoisins(unsigned int r) {
	if (r == 1) { // voisinage de Moore
		nbVoisin = 8;
	}
	else { // voisiange de Moore avec un rayon
		nbVoisin = pow((2 * r + 1), 2) - 1;
	}
}

void RegleVoisinage::calculVoisinage(Voisinage& v, const Reseau& r) {
	v.voisinage = std::vector<Cellule*>();
	for (int k = 0; k < nbVoisin; k++) {
		unsigned int i, j;
		while (i >= r.getHauteur() || j >= r.getLargeur()) {
            cout << "Entrez l'abscisse de la" << k << "ième cellule.\n";
            cin >> i;
            cout << "Entrez l'ordonnée de la "<< k << "ième cellule.\n";
            cin >> j;
			if (i >= r.getHauteur() || j >= r.getLargeur())
                cout << "Coordonnées incorrecte !\n";
		}
		if (i < r.getHauteur() && j < r.getLargeur())
			v.voisinage[k] = &r.getReseau()[i][j];
	}
}

void RegleVoisinageNeumann::calculVoisinage(Voisinage& v, const Reseau& r) {
    v.voisinage = std::vector<Cellule*>();
	int nb = 0;
	unsigned int abs = v.celluleCentre->abs;
	unsigned int ord = v.celluleCentre->ord;
	unsigned int hauteur = r.getHauteur();
	unsigned int largeur = r.getLargeur();

	for (int i = 0; i < v.r; i++) {
		for (int j = 0; j < v.r; j++) {
			if ((i + j) <= v.r || (i + j) != 0) {
				
				v.voisinage[nb] = &r.getReseau()[(abs + i)%hauteur][(ord + j)%largeur];
				nb++;

				if ((ord - j) < 0) {
					v.voisinage[nb] = &r.getReseau()[(abs + i) % hauteur][largeur + ord - j];
					nb++;
					if ((abs - i >= 0)) {
						v.voisinage[nb] = &r.getReseau()[abs - i][(ord + j) % largeur];
						nb++;

						v.voisinage[nb] = &r.getReseau()[abs - i][largeur + ord - j];
						nb++;
					}
					else {
						v.voisinage[nb] = &r.getReseau()[hauteur + abs - i][(ord + j) % largeur];
						nb++;

						v.voisinage[nb] = &r.getReseau()[hauteur + abs - i][largeur + ord - j];
						nb++;
					}
				}					
				else {
					v.voisinage[nb] = &r.getReseau()[(abs + i) % hauteur][ord - j];
					nb++;

					if ((abs - i >= 0)) {
						v.voisinage[nb] = &r.getReseau()[abs - i][(ord + j) % largeur];
						nb++;

						v.voisinage[nb] = &r.getReseau()[abs - i][abs - j];
						nb++;
					}
					else {
						v.voisinage[nb] = &r.getReseau()[hauteur + abs - i][(ord + j) % largeur];
						nb++;

						v.voisinage[nb] = &r.getReseau()[hauteur + abs - i][ord - j];
						nb++;
					}
				}
				if (nb >= nbVoisin) {
					break;
					break;
				}
			}

		}

	}
}

void RegleVoisinageMoore::calculVoisinage(Voisinage& v, const Reseau& r){
    v.voisinage = std::vector<Cellule*>();
	int nb = 0;
	unsigned int abs = v.celluleCentre->abs;
	unsigned int ord = v.celluleCentre->ord;
	unsigned int hauteur = r.getHauteur();
	unsigned int largeur = r.getLargeur();

	for (int i = 1; i <= v.r; i++) {
		for (int j = 1; j <= i; j++) {
			v.voisinage[nb] = &r.getReseau()[(abs + i) % hauteur][(ord + j) % largeur];
			nb++;

			if ((abs - i) < 0) {
				if ((ord - j) < 0) {
					v.voisinage[nb] = &r.getReseau()[hauteur + abs - i][largeur + ord - j];
					nb++;

					v.voisinage[nb] = &r.getReseau()[(abs + i) % hauteur][largeur + ord - j];
					nb++;

					v.voisinage[nb] = &r.getReseau()[hauteur + abs - i][(ord + j) % largeur];
					nb++;
				}
				else {
					v.voisinage[nb] = &r.getReseau()[hauteur + abs - i][ord - j];
					nb++;

					v.voisinage[nb] = &r.getReseau()[(abs + i) % hauteur][ord - j];
					nb++;

					v.voisinage[nb] = &r.getReseau()[hauteur + abs - i][(ord + j) % largeur];
					nb++;
				}
			}
			else {
				if ((ord - j) < 0) {
					v.voisinage[nb] = &r.getReseau()[abs - i][largeur + ord - j];
					nb++;

					v.voisinage[nb] = &r.getReseau()[(abs + i) % hauteur][largeur + ord - j];
					nb++;

					v.voisinage[nb] = &r.getReseau()[abs - i][(ord + j) % largeur];
					nb++;
				}
				else {
					v.voisinage[nb] = &r.getReseau()[abs - i][ord - j];
					nb++;

					v.voisinage[nb] = &r.getReseau()[(abs + i) % hauteur][ord - j];
					nb++;

					v.voisinage[nb] = &r.getReseau()[abs - i][(ord + j) % largeur];
					nb++;

				}
			}
		}

	}
}

Voisinage::~Voisinage() {
    voisinage.clear();
}
