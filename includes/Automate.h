#ifndef _AUTOMATE_H
#define _AUTOMATE_H

#include <memory>
#include <Fonction.h>
#include <voisinage.h>

/// La classe automate se charge de gérer les informations d'un automate (fonction de transition, règle de voisinage, réseau, ...) et joue également le rôle de simulateur
///
/// Cette classe est un singletion est l'objet unique n'est disponible qu'avec la méthode statique getInstance(). Ainsi, il est impossible de créer des objets de cette classe. La classe agrège une fonction et une règle de voisinage dont l'utilisateur a la responsabilité. Il est également possible de laisser l'automate simuler avec un délai réglable.
class Automate {
	private:
		static std::unique_ptr<Automate> instance;
		unsigned int delai;
		Fonction* fonction;
		RegleVoisinage* regleVoisinage;
		std::list<Reseau> buffer; //ajouté : faut-il appeler buffer.clear() dans le destructeur ?
        std::list<Reseau>::iterator itBuffer; //ajouté
        unsigned int h; //ajouté pour construire des réseaux
        unsigned int l; //de même
        bool isRunning; //ajouté

		Automate(): delai(500), fonction(nullptr), regleVoisinage(nullptr), itBuffer(buffer.begin()), h(0), l(0), isRunning(false) {} //modifié
		Automate(const Automate& a) = delete;
		Automate& operator=(const Automate& a) = delete;

	public:
		static Automate& getInstance() {
			if(instance == nullptr) {
				instance.reset(new Automate);
			}

			return *instance;
		}
		~Automate() = default;
		void setFonction(Fonction& f) { fonction = &f; }
		void setRegleVoisinage(RegleVoisinage& r) { regleVoisinage = &r; }
		void setDelai(const unsigned int d) { delai = d; }

		//nouvelles fonctions

        void setHauteur(unsigned int hauteur) { h = hauteur; }
        void setLargeur(unsigned int largeur) { l = largeur; }

        void previous() { if(itBuffer!=buffer.begin()) itBuffer--; }
        void next() { if(itBuffer!=buffer.end()) itBuffer++; }
        void reset() { itBuffer = buffer.begin(); }

        void step() { if(isRunning) { if(itBuffer==buffer.end()) nextTimer(); itBuffer++;} }
        void run(int n) { for(int i=0;i<n;i++) step(); }

	void nextTimer();

        void start() { isRunning = true; }
        void pause() { isRunning = false; }
};

#endif
