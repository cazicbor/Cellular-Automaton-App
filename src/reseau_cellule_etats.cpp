#include <reseau_cellule_etats.h>
#include <Automate.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

//méthodes de la classe EnsembleEtat

EnsembleEtat::EnsembleEtat() {
    for (size_t i = 0; i < nbEtatsMax; i++) ensEtats[i] = nullptr;
}

EnsembleEtat::~EnsembleEtat() {
    for (size_t i = 0; i < nbEtats; i++) delete ensEtats[i];
}

void EnsembleEtat::ajouterEtat(unsigned int ind, std::string lab,int r, int g, int b){
    ensEtats[nbEtats] = new Etat(ind, lab, r, g, b);
    nbEtats++;
}

void EnsembleEtat::supprimerEtat(const unsigned int ind){
    unsigned int i = 0;
    for(i=0; i<nbEtats; i++)
    {
        if(ensEtats[i]->indice == ind)
        {

            for(unsigned j = i; j<(nbEtats-1); j++){
                ensEtats[j] = ensEtats[j+1];}
                //ensEtats[j]->indice--; à voir si l'on veut laisser ou non l'utilisateur gérer les indices
        delete ensEtats[nbEtats];
        nbEtats--;
        }
    }
}

void EnsembleEtat::initEtat(const Etat* init_etats){
    /*if(ensEtats != nullptr){
        delete[] ensEtats;}*/

    for(unsigned int i=0; i< (sizeof (init_etats)-1); i++)
        ensEtats[i] = new Etat(init_etats[i].indice, init_etats[i].label, init_etats[i].color);
    nbEtats = sizeof (init_etats);
}

void EnsembleEtat::reset(){
    if (ensEtats != nullptr){
        for(auto it : ensEtats){
            delete it;
        }
        nbEtats=0;
    }
};

//méthodes de la classe Etat


//méthodes dela classe Cellule

Cellule::Cellule():indEtat(0), abs(0), ord(0){};

void Cellule::initCellule(const unsigned int ind, const unsigned int &x, const unsigned int &y){
    this->indEtat = ind;
    this->abs = x;
    this->ord = y;
}

void Cellule::incrementerEtat(){
    indEtat = (indEtat+1) % Automate::getInstance().getEnsemble().getNbEtats();}

//méthodes de la classe Reseau

Reseau::Reseau(const unsigned int &h, const unsigned int &l):hauteur(h),largeur(l){
        reseau = new Cellule* [hauteur];
            for(unsigned int i=0; i<hauteur; i++)
                reseau[i] = new Cellule [largeur];
        for(unsigned int i=0; i<hauteur; i++) //initialisation des cellules dans un second car pas possible avec l'allocation dynamique
            for(unsigned int j=0; j<largeur; j++)
                reseau[i][j].initCellule(1,i,j);}

Reseau::~Reseau(){
    for(unsigned int i=0; i<hauteur; i++)
        delete[] reseau[i];
    delete[] reseau;
}

Reseau& Reseau::setAleatoire(){
    srand(time(NULL));
    for(unsigned int i=0; i<hauteur; i++)
        for(unsigned int j=0; j<largeur; j++)
        {
            unsigned int random_ind = rand() % (Automate::getInstance().getEnsemble().getNbEtats());
            reseau[i][j].initCellule(random_ind,i,j);
        };
    return *this;
}

Reseau::Reseau(const Reseau& init_grille){
    hauteur = init_grille.hauteur;
    largeur = init_grille.largeur;
    reseau = new Cellule* [hauteur];
    for(unsigned int i=0; i<hauteur; i++)
        reseau[i] = new Cellule [largeur];

    for(unsigned int i=0; i<hauteur; i++)
        for(unsigned int j=0; j<largeur; j++)
        {
            reseau[i][j].initCellule(init_grille.reseau[i][j].getIndEtat(),i,j);
        }

};
