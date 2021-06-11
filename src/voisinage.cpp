#include"voisinage.h"
#include"reseau_cellule_etats.h"
#include<cmath>
#include<iostream>

void RegleVoisinageNeumann::calculVoisinage(Voisinage& v, const Reseau& r) const {
	v.voisinage = std::vector<Cellule*>();
	unsigned int cellX = v.celluleCentre->abs;
	unsigned int cellY = v.celluleCentre->ord;
	unsigned int hauteur = r.getHauteur();
	unsigned int largeur = r.getLargeur();

	for (int i = -static_cast<int>(rayon); i <= static_cast<int>(rayon); i++)
		for (int j = -static_cast<int>(rayon); j <= static_cast<int>(rayon); j++)
			if (abs(i) + abs(j) <= static_cast<int>(rayon) && (i != 0 || j != 0))
			{
				int x = (cellY+i)%hauteur;
				if (x < 0)
					x = largeur + x;
				int y = (cellX+j)%largeur;
				if (y < 0)
					y = hauteur + y;
				v.voisinage.push_back(new Cellule(r.getReseau()[y][x]));
			}
}

void RegleVoisinageMoore::calculVoisinage(Voisinage& v, const Reseau& r) const {
	v.voisinage = std::vector<Cellule*>();
	int cellX = static_cast<int>(v.celluleCentre->abs);
	int cellY = static_cast<int>(v.celluleCentre->ord);
	int hauteur = r.getHauteur();
	int largeur = r.getLargeur();

	for (int i = -static_cast<int>(rayon); i <= static_cast<int>(rayon); i++)
		for (int j = -static_cast<int>(rayon); j <= static_cast<int>(rayon); j++)
			if (i != 0 || j != 0)
			{
				int x = (cellY+i)%hauteur;
				if (x < 0)
					x = largeur + x;
				int y = (cellX+j)%largeur;
				if (y < 0)
					y = hauteur + y;
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

    unsigned int abs = v.celluleCentre->abs;
    unsigned int ord = v.celluleCentre->ord;
    unsigned int hauteur = r.getHauteur();
    unsigned int largeur = r.getLargeur();

    for (size_t nb = 0; nb < coordonnees.size(); nb++){
        v.voisinage[nb] = new Cellule(r.getReseau()[(abs - coordonnees[nb].x)%hauteur] [(ord - coordonnees[nb].y)%largeur]);
    }
}

vector<Coordonnees> RegleVoisinageArbitraire::getVoisinage(const QTableWidget* grid)
{
    vector<Coordonnees> coordonnees;
    int k = 0;

    for (unsigned int i = 0; i < 5; i++) {
        for (unsigned int j = 0; j < 5; j++){
            if (grid->item(i,j)->background() == Qt::red){
               coordonnees[k].x = (2-i);
               coordonnees[k].y = (2-j);
               k += 1;
            }
        }

      }

    return coordonnees;
}
