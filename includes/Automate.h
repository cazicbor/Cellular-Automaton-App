#ifndef _AUTOMATE_H
#define _AUTOMATE_H

#include <memory>
#include <Fonction.h>
#include <voisinage.h>
#include <QObject>

/// La classe automate se charge de gérer les informations d'un automate (fonction de transition, règle de voisinage, réseau, ...) et joue également le rôle de simulateur
///
/// Cette classe est un singletion est l'objet unique n'est disponible qu'avec la méthode statique getInstance(). Ainsi, il est impossible de créer des objets de cette classe. La classe agrège une fonction et une règle de voisinage dont l'utilisateur a la responsabilité. Il est également possible de laisser l'automate simuler avec un délai réglable.
class Automate {
	private:
		static std::unique_ptr<Automate> instance;
		std::string title;
		unsigned int delai;
		Fonction* fonction;
		RegleVoisinage* regleVoisinage;
		std::list<Reseau> buffer;
		std::list<Reseau>::iterator itBuffer;
		unsigned int h;
		unsigned int l;
		bool isRunning;

		Automate(): delai(500), fonction(nullptr), regleVoisinage(nullptr), itBuffer(buffer.begin()), h(0), l(0), isRunning(false), title("") {} //modifié
		~Automate() = default;
		Automate(const Automate& a) = delete;
		Automate& operator=(const Automate& a) = delete;
		std::string getTitle() const { return title; }
		std::string setTitle(const std::string& t) { title = t; }
		class Timer: public QObject {
			private:
				int timerID;
				Automate *automate;
				Timer(Automate *a): timerID(0), automate(a) {}
				~Timer() { destroy(); }

			protected:
				void timerEvent(QTimerEvent *event) { automate->step(); }

			public:
				void install(const int delai) {
					if(timerID != 0)
						destroy();

					timerID = startTimer(delai);
					if(timerID == 0)
						throw "Unable to install timer";
				}
				void destroy() {
					if(timerID != 0)
						killTimer(timerID);
				}

			friend class Automate;
		};
		Timer timer(this);

	public:
		/// récupérer une référence sur l'instance unique du singleton Automate
		static Automate& getInstance() {
			if(instance == nullptr) {
				instance.reset(new Automate);
			}

			return *instance;
		}
		/// Définir la fonction de transition de l'automate, le cycle de vie de la focntion est géré par l'utilisateur
		void setFonction(Fonction& f) { fonction = &f; }
		/// Définir une règle de voisinage, le cycle de vie de la règle est géré par l'utilisateur
		void setRegleVoisinage(RegleVoisinage& r) { regleVoisinage = &r; }
		/// Définir le délai entre 2 itérations de l'automate en mode Timer
		void setDelai(const unsigned int d) { delai = d; }

		/// définir la hauteur de la grille
		void setHauteur(unsigned int hauteur) { h = hauteur; }
		/// définir la largheur de la grille
		void setLargeur(unsigned int largeur) { l = largeur; }

		/// Se placer sur l'état précédent si disponible
		void previous() { if(itBuffer!=buffer.begin()) itBuffer--; }
		/// Se placer sur l'état suivant si disponible
		void next() { if(itBuffer!=buffer.end()) itBuffer++; }
		/// L'automate revient au premier état du buffer
		void reset() { itBuffer = buffer.begin(); }
		/// On vide la buffer et on l'initialise avec une première grille
		void reset(const Reseau& r) { buffer.clear(); buffer.push_back(r); }

		/// Se placer sur l'état suivant du buffer et le calculer s'il n'y en a plus de disponible
		void step() {
			if(itBuffer==buffer.end())
				nextTimer();
			itBuffer++;
		}
		/// Execution multiple de la méthode step
		void run(int n) {
			for(int i=0;i<n;i++)
				step();
		}

		/// Calcule d'une nouvelle étape à partir de la dernière
		void nextTimer();

		/// Démarre l'exécution automatique de l'automate avec une vitesse selon l'attribut delai s'il n'est pas déjà en route
		void start() { timer.install(delai); }
		/// Supprime le timer s'il est en route
		void pause() { timer.destroy(); }

		/// Récupérer un réseau correspondant à l'état courant de l'automate
		Reseau getReseauCourant() { return *itBuffer; }

		/// initialiser le buffer s'il est vide avec un réseau
		void initialiserBuffer(Reseau& r) { if(buffer.begin()==buffer.end()) buffer.push_front(r); }
};

#endif
