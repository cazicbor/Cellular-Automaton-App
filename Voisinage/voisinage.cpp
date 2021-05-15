#include"voisinage.hpp"
#include<math.h>

void Voisinage::setr(unsigned int rayon){
   if(rayon >= 0){
		r = rayon;
	}
	else throw ("Rayon incorrect !\n");
	 
}

void RegleVoisinage::setNbVoisins(unsigned int r) {
	if (r == 0) { //voisinage arbitraire
		printf("Entrez le nombre de voisins.\n");
		scanf("%u", &nbVoisin);
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
	v.voisinage = new Cellule* [nbVoisin];
	for (int k = 0; k < nbVoisin; k++) {
		unsigned int i, j;
		while (i >= r.hauteur || j >= r.largeur) {
			printf("Entrez l'abscisse de la %d ième cellule.\n", k);
			scanf("%u", &i);
			printf("Entrez l'ordonnée de la %d ième cellule.\n", k);
			scanf("%u", &j);
			if (i >= r.hauteur || j >= r.largeur)
				printf("Coordonnées incorrecte!\n");
		}
		if (i < r.hauteur && j < r.largeur)
			v.voisinage[k] = &r.reseau[i][j];
	}
}

void RegleVoisinageNeumann::calculVoisinage(Voisinage& v, const Reseau& r) {
	v.voisinage = new Cellule * [nbVoisin];
	int nb = 0;
	unsigned int abs = v.celluleCentre->abs;
	unsigned int ord = v.celluleCentre->ord;
	unsigned int hauteur = r.hauteur;
	unsigned int largeur = r.largeur;

	for (int i = 0; i < v.r; i++) {
		for (int j = 0; j < v.r; j++) {
			if ((i + j) <= v.r || (i + j) != 0) {
				
				v.voisinage[nb] = &r.reseau[(abs + i)%hauteur][(ord + j)%largeur];
				nb++;

				if ((ord - j) < 0) {
					v.voisinage[nb] = &r.reseau[(abs + i) % hauteur][largeur + ord - j];
					nb++;
					if ((abs - i >= 0)) {
						v.voisinage[nb] = &r.reseau[abs - i][(ord + j) % largeur];
						nb++;

						v.voisinage[nb] = &r.reseau[abs - i][largeur + ord - j];
						nb++;
					}
					else {
						v.voisinage[nb] = &r.reseau[hauteur + abs - i][(ord + j) % largeur];
						nb++;

						v.voisinage[nb] = &r.reseau[hauteur + abs - i][largeur + ord - j];
						nb++;
					}
				}					
				else {
					v.voisinage[nb] = &r.reseau[(abs + i) % hauteur][ord - j];
					nb++;

					if ((abs - i >= 0)) {
						v.voisinage[nb] = &r.reseau[abs - i][(ord + j) % largeur];
						nb++;

						v.voisinage[nb] = &r.reseau[abs - i][abs - j];
						nb++;
					}
					else {
						v.voisinage[nb] = &r.reseau[hauteur + abs - i][(ord + j) % largeur];
						nb++;

						v.voisinage[nb] = &r.reseau[hauteur + abs - i][ord - j];
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
	v.voisinage = new Cellule * [nbVoisin];
	int nb = 0;
	unsigned int abs = v.celluleCentre->abs;
	unsigned int ord = v.celluleCentre->ord;
	unsigned int hauteur = r.hauteur;
	unsigned int largeur = r.largeur;

	for (int i = 1; i <= v.r; i++) {
		for (int j = 1; j <= i; j++) {
			v.voisinage[nb] = &r.reseau[(abs + i) % hauteur][(ord + j) % largeur];
			nb++;

			if ((abs - i) < 0) {
				if ((ord - j) < 0) {
					v.voisinage[nb] = &r.reseau[hauteur + abs - i][largeur + ord - j];
					nb++;

					v.voisinage[nb] = &r.reseau[(abs + i) % hauteur][largeur + ord - j];
					nb++;

					v.voisinage[nb] = &r.reseau[hauteur + abs - i][(ord + j) % largeur];
					nb++;
				}
				else {
					v.voisinage[nb] = &r.reseau[hauteur + abs - i][ord - j];
					nb++;

					v.voisinage[nb] = &r.reseau[(abs + i) % hauteur][ord - j];
					nb++;

					v.voisinage[nb] = &r.reseau[hauteur + abs - i][(ord + j) % largeur];
					nb++;
				}
			}
			else {
				if ((ord - j) < 0) {
					v.voisinage[nb] = &r.reseau[abs - i][largeur + ord - j];
					nb++;

					v.voisinage[nb] = &r.reseau[(abs + i) % hauteur][largeur + ord - j];
					nb++;

					v.voisinage[nb] = &r.reseau[abs - i][(ord + j) % largeur];
					nb++;
				}
				else {
					v.voisinage[nb] = &r.reseau[abs - i][ord - j];
					nb++;

					v.voisinage[nb] = &r.reseau[(abs + i) % hauteur][ord - j];
					nb++;

					v.voisinage[nb] = &r.reseau[abs - i][(ord + j) % largeur];
					nb++;

				}
			}
		}

	}
}

Voisinage::~Voisinage() {
	VoisinageIterator *cellules = creerIterator();
	cellules->first();
	int nb = 0;

	while (!cellules->isDone()){
		delete voisinage[nb];
		nb++;
	}

	delete[] voisinage;

}
