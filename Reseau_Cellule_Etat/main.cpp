#include <iostream>
#include <iomanip>
#include <reseau_cellule_etats.h>

using namespace std;

int main()
{
    std::cout<<"--- Affichage d'une grille initialisee par defaut --- \n";

    EnsembleEtat &enseEtats = EnsembleEtat::getInstance();

    enseEtats.ajouterEtat(0, "vivant", "white");
    enseEtats.ajouterEtat(1, "mort", "black");

    //std::cout<<enseEtats.getEtat(0).getLabel()<<endl;

    int largeur = 10;
    int hauteur = 12;

    Reseau Grille(hauteur, largeur);
    Grille.affiche();

    return 0;
}
