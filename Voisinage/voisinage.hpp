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
    friend class VoisinageIterator;
public:

    Voisinage();
    ~Voisinage();
    Cellule* getCelluleCentre()const {return celluleCentre;}
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
    int currentItem(){
        
        return vsn->voisinage[i];
        
    }
    
};

#endif /* voisinnage_hpp */
