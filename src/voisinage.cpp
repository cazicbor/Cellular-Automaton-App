#include"voisinage.h"
#include"reseau_cellule_etats.h"
#include<cmath>
#include<iostream>

void RegleVoisinageNeumann::calculVoisinage(Voisinage& v, const Reseau& r) const {
	v.voisinage = std::vector<Cellule*>();
	int cellX = static_cast<int>(v.celluleCentre->abs);
	int cellY = static_cast<int>(v.celluleCentre->ord);
	int hauteur = static_cast<int>(r.getHauteur());
	int largeur = static_cast<int>(r.getLargeur());

	for (int i = -static_cast<int>(rayon); i <= static_cast<int>(rayon); i++)
		for (int j = -static_cast<int>(rayon); j <= static_cast<int>(rayon); j++)
			if (abs(i) + abs(j) <= static_cast<int>(rayon) && (i != 0 || j != 0))
			{
				int x = (cellY+i)%largeur;
				if (x < 0)
					x = largeur + x;
				int y = (cellX+j)%hauteur;
				if (y < 0)
					y = hauteur + y;
				if(this->getMatriceTorique())
					v.voisinage.push_back(new Cellule(r.getReseau()[y][x]));
				else if (x == cellY+i && y == cellX+j)
					v.voisinage.push_back(new Cellule(r.getReseau()[y][x]));
			}
}

void RegleVoisinageMoore::calculVoisinage(Voisinage& v, const Reseau& r) const {
	v.voisinage = std::vector<Cellule*>();
	int cellX = static_cast<int>(v.celluleCentre->abs);
	int cellY = static_cast<int>(v.celluleCentre->ord);
	int hauteur = static_cast<int>(r.getHauteur());
	int largeur = static_cast<int>(r.getLargeur());

	for (int i = -static_cast<int>(rayon); i <= static_cast<int>(rayon); i++)
		for (int j = -static_cast<int>(rayon); j <= static_cast<int>(rayon); j++)
			if (i != 0 || j != 0)
			{
				int x = (cellY+i)%largeur;
				if (x < 0)
					x = largeur + x;
				int y = (cellX+j)%hauteur;
				if (y < 0)
					y = hauteur + y;
				if(this->getMatriceTorique())
					v.voisinage.push_back(new Cellule(r.getReseau()[y][x]));
				else if (x == cellY+i && y == cellX+j)
					v.voisinage.push_back(new Cellule(r.getReseau()[y][x]));
			}
}

Voisinage::~Voisinage() {
	for(auto& cel: voisinage)
		delete cel;
	voisinage.clear();
}

void RegleVoisinageArbitraire::calculVoisinage(Voisinage &v, const Reseau& r) const { //définir get?
	v.voisinage = std::vector<Cellule*>();
	int cellX = static_cast<int>(v.celluleCentre->abs);
	int cellY = static_cast<int>(v.celluleCentre->ord);
	int hauteur = static_cast<int>(r.getHauteur());
	int largeur = static_cast<int>(r.getLargeur());

	for (size_t nb = 0; nb < coordonnees.size(); nb++){
		int x = (cellY+coordonnees[nb].y)%largeur;
		if (x < 0)
			x = largeur + x;
		int y = (cellX+coordonnees[nb].x)%hauteur;
		if (y < 0)
			y = hauteur + y;
		v.voisinage.push_back(new Cellule(r.getReseau()[y][x]));
	}
}

void RegleVoisinageArbitraire::getVoisinage(const QTableWidget* grid) {
	Coordonnees coordonnee;
	for (unsigned int i = 0; i < 5; i++) {
		for (unsigned int j = 0; j < 5; j++){
			if (grid->item(i,j)->background() == Qt::red){
				coordonnee.x = (i - 2);
				coordonnee.y = (j - 2);
				coordonnees.push_back(coordonnee);
			}
		}
	}
}
