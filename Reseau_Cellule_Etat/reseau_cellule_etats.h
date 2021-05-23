#pragma once
#include <iostream>
#include <array>
#include <QColor>

class Cellule{
private:
    unsigned int indEtat;
    unsigned int abs;
    unsigned int ord;
    Cellule();
    //inline Cellule():indEtat(0), abs(0), ord(0){};
    void initCellule(const unsigned int ind, const unsigned int &x, const unsigned int &y);
    friend class Reseau;
public:
    inline unsigned int getIndEtat() const {return indEtat;}
};

class Etat{
private:
    unsigned int indice;
    std::string label;
    QColor color;
    inline Etat(unsigned int ind, std::string lab, int r = 0, int g = 0, int b = 0, int a = 1):
    indice(ind),label(lab),color(r,g,b,a){};
    inline Etat(unsigned int ind, std::string lab, QColor col):
    indice(ind),label(lab),color(col){};//constructeur privé (l'utilisateur ne doit pas pouvoir créer un Etat par ce biais)
    friend class EnsembleEtat;

public:
    inline std::string& getLabel(){return label;}
    inline QColor& getColor(){return color;}
};

class EnsembleEtat{ //singleton qui regroupe l'ensemble des états
private:          //permet d'éviter que chaque cellule inclue une instance d'Etat
    size_t nbEtats = 0;
    static const size_t nbEtatsMax = 10;
    Etat* ensEtats[nbEtatsMax];
    struct Handler {
        EnsembleEtat* instance=nullptr;
        ~Handler() { delete instance; }
    };
    static Handler handler;
    friend struct Handler;
    EnsembleEtat();
    ~EnsembleEtat();
    EnsembleEtat(const EnsembleEtat&) = delete;
    EnsembleEtat operator=(const EnsembleEtat&) = delete;

public:
    void ajouterEtat(unsigned int ind, std::string lab,int r = 0, int g = 0, int b = 0, int a = 1);
    void supprimerEtat(const unsigned int ind);
    static EnsembleEtat& getInstance();
    static void libererInstance();
    void initEtat(const Etat* init_etats = nullptr);//initialisation du tableau d'Etats à partir d'un tableau externe
    inline Etat& getEtat(const unsigned int &ind){return *ensEtats[ind];}
};

class Reseau{
private:
    unsigned int hauteur;
    unsigned int largeur;
    Cellule** reseau;

public:
    /* inline Reseau(const unsigned int &h, const unsigned int &l):hauteur(h),largeur(l){
            reseau = new Cellule* [hauteur];
                for(unsigned int i=0; i<hauteur; i++)
                    reseau[i] = new Cellule [largeur];
            for(unsigned int i=0; i<hauteur; i++) //initialisation des cellules dans un second temps car pas possible avec l'allocation dynamique
                for(unsigned int j=0; j<largeur; j++)
                    reseau[i][j].initCellule(0,i,j);
    }*/
    inline int getLargeur() const {return largeur;};
    inline int getHauteur() const {return hauteur;};
    inline Cellule** getReseau() const {return reseau;};
    Reseau(const unsigned int &h, const unsigned int &l);
    ~Reseau();
    void affiche();
};
