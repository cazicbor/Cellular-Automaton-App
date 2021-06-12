#pragma once
#include <iostream>
#include <array>
#include <QColor>

using namespace std;

class Cellule{
private:
    unsigned int indEtat;
    unsigned int abs;
    unsigned int ord;
    //inline Cellule():indEtat(0), abs(0), ord(0){};
    void initCellule(const unsigned int ind, const unsigned int &x, const unsigned int &y);
    friend class Reseau;
    friend class RegleVoisinage;
    friend class RegleVoisinageNeumann;
    friend class RegleVoisinageMoore;
    friend class RegleVoisinageArbitraire;

public:
    inline unsigned int getIndEtat() const {return indEtat;}
    void incrementerEtat();
    Cellule();
    Cellule(const Cellule& c): indEtat(c.indEtat), abs(c.abs), ord(c.ord) {}
};

class Etat{
private:
    unsigned int indice;
    std::string label;
    QColor color;
    Etat(unsigned int ind, std::string lab, int r = 0, int g = 0, int b = 0):
    indice(ind),label(lab),color(r,g,b){}
    Etat(unsigned int ind, std::string lab, QColor col):
    indice(ind),label(lab),color(col){} //constructeur privé (l'utilisateur ne doit pas pouvoir créer un Etat par ce biais)
    friend class EnsembleEtat;

public:
    std::string getLabel(){return label;}
    QColor getColor(){return color;}
	unsigned int getIndice() const { return indice; }
};


class EnsembleEtat{ //singleton qui regroupe l'ensemble des états
private:          //permet d'éviter que chaque cellule inclue une instance d'Etat
    size_t nbEtats = 0;
    static const size_t nbEtatsMax = 10;
    Etat* ensEtats[nbEtatsMax];
    EnsembleEtat(const EnsembleEtat&) = delete;
    EnsembleEtat operator=(const EnsembleEtat&) = delete;

public:
    EnsembleEtat();
    ~EnsembleEtat();
    void ajouterEtat(unsigned int ind, std::string lab,int r = 0, int g = 0, int b = 0);
    void supprimerEtat(const unsigned int ind);
    void initEtat(const Etat* init_etats = nullptr);//initialisation du tableau d'Etats à partir d'un tableau externe
    Etat& getEtat(const unsigned int &ind){return *ensEtats[ind];}
    unsigned int getNbEtats() const {return nbEtats;};
    void reset();
};

class Reseau{
private:
    unsigned int hauteur;
    unsigned int largeur;
    Cellule** reseau;

public:
    int getLargeur() const {return largeur;};
    int getHauteur() const {return hauteur;};
    Reseau& setAleatoire();
    Cellule** getReseau() const {return reseau;};
    Reseau(const unsigned int &h, const unsigned int &l);
    Reseau(const Reseau&);
    ~Reseau();
    Reseau& operator=(const Reseau& r);
    bool operator==(const Reseau&r);
};
