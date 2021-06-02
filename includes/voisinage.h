//
//  voisinage.h
//  LO21-Projet
//
//  Created by Maxime Goret on 20/04/2021.
//

#ifndef voisinage_h
#define voisinage_h

#include "reseau_cellule_etats.h"
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>

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
            return (vsn->voisinage.size() <= i);
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
    void calculVoisinage(Voisinage& v, const Reseau& r);
    
    
};

/*class RegleVoisinageRayon : public RegleVoisinage { //voisinage rayon hérite de voisinage puisque spécification
protected:
    unsigned int rayon;
public:
    unsigned int getRayon() const { return rayon; }
    explicit RegleVoisinageRayon(unsigned int ray) : rayon(ray) {} //explicit car


};*/



class RegleVoisinageNeumann : public RegleVoisinage {
public:
    void setNbVoisins(unsigned int r);
    void calculVoisinage(Voisinage& v, const Reseau& r);

};






class RegleVoisinageMoore : public RegleVoisinage {
public:
    void setNbVoisins(unsigned int r);
    void calculVoisinage(Voisinage& v, const Reseau& r);

};



#endif /* voisinage_h */
