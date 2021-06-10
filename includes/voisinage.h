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
#include"parametragemodele.h"


using namespace std;

class Voisinage {
private :
    const Cellule* celluleCentre;
    vector<Cellule*> voisinage;
    friend class RegleVoisinage;
    friend class RegleVoisinageMoore;
    friend class RegleVoisinageNeumann;
    friend class RegleVoisinageArbitraire;
    friend class VoisinageIterator;
    
public:
    
    class VoisinageIterator {
        const Voisinage *vsn;
        size_t i;
        public :
        
        VoisinageIterator(const Voisinage *v){
            vsn = v;
        }
        
        void first(){
            i = 0;
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

    Voisinage(const Cellule* centre) : celluleCentre(centre) {}
    ~Voisinage();
    Cellule getCelluleCentre()const {return *celluleCentre;}

    VoisinageIterator *creerIterator()const{
        return new VoisinageIterator(this);
    }
    
};

class RegleVoisinage{
	public :
		virtual void calculVoisinage(Voisinage& v, const Reseau& r) const = 0;
		virtual int getType() const = 0;
		/// Renvoie le rayon d'une règle de voisinage, 0 si ce n'est pas pertinant pour ce voisinage (arbitraire, ...)
		virtual unsigned int getr() const { return 0; }
		virtual ~RegleVoisinage() = default;
};

class RegleVoisinageNeumann : public RegleVoisinage {
	private:
		unsigned int rayon;
	public:
		void calculVoisinage(Voisinage& v, const Reseau& r) const override;
		void setr(unsigned int r) { rayon = r; }
        unsigned int getr() const override { return rayon; }
        int getType() const override { return 1; }
};

class RegleVoisinageMoore : public RegleVoisinage {
	private:
		unsigned int rayon;
	public:
		void calculVoisinage(Voisinage& v, const Reseau& r) const override;
		void setr(unsigned int r) { rayon = r; }
        unsigned int getr() const override { return rayon; }
        int getType() const override { return 2; }
};

class RegleVoisinageArbitraire : public RegleVoisinage { //définit la règle pour le voisinage arbitraire
    private:
        unsigned int nbVoisin;
    public:
        int getType() const override{ return 3; }
        void setNbVoisins(unsigned int r) { nbVoisin = r; }
        unsigned int getNbVoisin() { return nbVoisin; }
        vector<Coordonnees> coordonnees;
        void calculVoisinage(Voisinage& v, const Reseau& r) const override; // Calcul du voisinage en fonction de la cellule centre
        vector<Coordonnees> getVoisinage(const QTableWidget* grid ); // Dééfinition des coordonnées relatives pour le calcul du voisinage
};

#endif /* voisinage_h */
