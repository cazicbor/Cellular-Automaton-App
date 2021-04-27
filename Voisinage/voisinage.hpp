//
//  voisinnage.hpp
//  LO21-Projet
//
//  Created by Maxime Goret on 20/04/2021.
//

#ifndef voisinnage_hpp
#define voisinnage_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class Voisinage {
private :
    
    const Cellule* celluleCentre;
    Cellule** voisinage;
    unsigned int r;
    friend class RegleVoisinage;
    friend class RegleVoisinageMoore;
    friend class RegleVoisinageNeumann;
public:

    Voisinage();
    ~Voisinage();
    Cellule* getCelluleCentre()const {return celluleCentre;}
    void setr(unsigned int rayon);
    unsigned int getr() const {return r;}
    
};

class RegleVoisinage{
    private :
    unsigned int nbVoisin;
    
    
    public :
    void setNbVoisins(unsigned int r);
    unsigned int getNbVoisin() {return nbVoisin;}
    void calculVoisinage(Voisinage& v);
    
    
};



class RegleVoisinageNeumann {
public:
    void calculVoisinage(Voisinage& v);

};





class RegleVoisinageMoore : public RegleVoisinage {
public:
    void calculVoisinage(Voisinage& v);

};
#endif /* voisinnage_hpp */
