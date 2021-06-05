//
//  voisinage.h
//  LO21-Projet
//
//  Created by Maxime Goret on 20/04/2021.
//

#ifndef voisinage_h
#define voisinage_h

#include"reseau_cellule_etats.h"
#include"coordonnees.h"
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Voisinage {
private :
    const Cellule* celluleCentre;
    vector<Cellule*> voisinage;
    unsigned int r;
    friend class RegleVoisinage;
    friend class RegleVoisinageMoore;
    friend class RegleVoisinageNeumann;
    friend class VoisinageIterator;
public:
    
    class VoisinageIterator {
        const Voisinage *vsn;
        int i;
        public :
        
        VoisinageIterator(const Voisinage *v){
            vsn = v;
        }
        
        void first(){
            i=0;
        }
        
        void next(){
            i++;
        }
        bool isDone(){
            return (vsn->voisinage.size() <=  i);
        }
        Cellule* currentItem(){
            return vsn->voisinage[i];
        }
        
    };

    Voisinage(const Cellule* centre, vector<Cellule*> v) : celluleCentre(centre), voisinage(v) {}
    ~Voisinage();
    Cellule getCelluleCentre()const {return *celluleCentre;}

    void setr(unsigned int rayon);
    unsigned int getr() const {return r;}
    VoisinageIterator *creerIterator()const{
        return new VoisinageIterator(this);
    }
    
};

class RegleVoisinage{
private :
    

public :
    unsigned int nbVoisin;
    void setNbVoisins(unsigned int r);
    unsigned int getNbVoisin() {return nbVoisin;}
    virtual void calculVoisinage(Voisinage& v, const Reseau& r);
    
    
};


class RegleVoisinageNeumann : public RegleVoisinage {
public:
    //void setNbVoisins(unsigned int r);
    void calculVoisinage(Voisinage& v, const Reseau& r, const unsigned int rayon);

};


class RegleVoisinageMoore : public RegleVoisinage {
public:
    //void setNbVoisins(unsigned int r);
    void calculVoisinage(Voisinage& v, const Reseau& r, const unsigned int rayon);

};

class RegleVoisinageArbitraire : public RegleVoisinage { //définit la règle pour le voisinage arbitraire
public:
    Voisinage getVoisinage(const Reseau& reseau, Coordonnees position) const;
    //à compléter
    void calculVoisinage(Voisinage &v, const Reseau& r);
};



#endif /* voisinage_h */
