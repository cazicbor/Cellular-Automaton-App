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
    friend class RegleVoisinageArbitraire;
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
	public :
		virtual void calculVoisinage(Voisinage& v, const Reseau& r) = 0;
};

class RegleVoisinageNeumann : public RegleVoisinage {
	public:
		void calculVoisinage(Voisinage& v, const Reseau& r) override;
};

class RegleVoisinageMoore : public RegleVoisinage {
	public:
		void calculVoisinage(Voisinage& v, const Reseau& r) override;
};

class RegleVoisinageArbitraire : public RegleVoisinage { //définit la règle pour le voisinage arbitraire
	private:
		unsigned int nbVoisin;
	public:
		void setNbVoisins(unsigned int r) { nbVoisin = r; }
		unsigned int getNbVoisin() { return nbVoisin; }
		vector<Coordonnees> coordonnees;
		void calculVoisinage(Voisinage& v, const Reseau& r, const Coordonnees co) const; // Calcul du voisinage en fonction de la cellule centre
		Coordonnees getVoisinage(const Reseau& r); // Dééfinition des coordonnées relatives pour le calcul du voisinage
};

#endif /* voisinage_h */
