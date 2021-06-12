#ifndef _AUTOMATE_H
#define _AUTOMATE_H

#include <memory>
#include <Fonction.h>
#include <voisinage.h>
#include <QObject>
#include <autocell.h>

/// La classe automate se charge de gérer les informations d'un automate (fonction de transition, règle de voisinage, réseau, ...) et joue également le rôle de simulateur
///
/// Cette classe est un singletion est l'objet unique n'est disponible qu'avec la méthode statique getInstance(). Ainsi, il est impossible de créer des objets de cette classe. La classe agrège une fonction et une règle de voisinage dont l'utilisateur a la responsabilité. Il est également possible de laisser l'automate simuler avec un délai réglable.
class Automate {
	private:
		static std::unique_ptr<Automate> instance;
		std::string title;
		unsigned int delai;
		std::unique_ptr<Fonction> fonction;
		std::unique_ptr<RegleVoisinage> regleVoisinage;
		std::list<Reseau> buffer;
		std::list<Reseau>::iterator itBuffer;
		unsigned int h;
		unsigned int l;
		Reseau reseauInit;
		int year;
		std::string author;
		std::string desc;
		EnsembleEtat ensemble;
		int nbStep;
		int nbCycle;

		Automate(): title(""), delai(500), fonction(nullptr), regleVoisinage(nullptr), itBuffer(buffer.begin()), h(0), l(0), reseauInit(Reseau(0, 0)), year(2000), author("Anonym"), desc(""), nbStep(0), nbCycle(0) { timer.automate = this; }
		Automate(const Automate& a) = delete;
		Automate& operator=(const Automate& a) = delete;
		class Timer: public QObject {
			private:
				int timerID;
				Automate *automate;
				Timer(): timerID(0) {}
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
		Timer timer;

	public:
		~Automate() = default;
		/// récupérer une référence sur l'instance unique du singleton Automate
		static Automate& getInstance() {
			if(instance == nullptr) {
				instance.reset(new Automate);
			}

			return *instance;
		}
		/// Définir la fonction de transition de l'automate
		///
		/// L'objet est géré dynamiquement par l'utilisateur mais une fois donnné à l'automate il gère son cycle de vie
		void setFonction(Fonction* f) { fonction.reset(f); }
		/// Récupérer la fonction de transition
		const Fonction& getFonction() const { return *fonction; }
		/// Définir une règle de voisinage
		///
		/// L'objet est géré dynamiquement par l'utilisateur mais une fois donnné à l'automate il gère son cycle de vie
		void setRegleVoisinage(RegleVoisinage* r) { regleVoisinage.reset(r); }
		/// Récupérer la règle de voisinage
		const RegleVoisinage& getRegleVoisinage() const { return *regleVoisinage; }
		/// Définir le délai entre 2 itérations de l'automate en mode Timer
		void setDelai(const unsigned int d) { delai = d; }

		/// Accesseur ensemble états
		EnsembleEtat& getEnsemble() { return ensemble; }
		/// Accesseur ensemble états
		const EnsembleEtat& getEnsemble() const { return ensemble; }
		/// définir la hauteur de la grille
		void setHauteur(unsigned int hauteur) { h = hauteur; }
		/// définir la largheur de la grille
		void setLargeur(unsigned int largeur) { l = largeur; }

		/// Se placer sur l'état précédent si disponible
		void previous() {
			if(itBuffer!=buffer.begin()) {
				itBuffer--;
				AutoCell::getInstance().afficherGrille(&*itBuffer);
			}
			else
				throw "No more state available before in the buffer (max: 15)";
		}
		/// Se placer sur l'état suivant si disponible
		void next() { if(itBuffer!=(--buffer.end())) itBuffer++; }
		/// On vide la buffer et on l'initialise avec une première grille
		void reset() { buffer.clear(); buffer.push_back(reseauInit); }

		/// Se placer sur l'état suivant du buffer et le calculer s'il n'y en a plus de disponible
		void step();
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
		void initialiserBuffer() { buffer.clear(); buffer.push_front(reseauInit); itBuffer = buffer.begin(); }

		/// Définir le réseau initial de l'automate
		void setReseauInit(Reseau& r) { reseauInit = r; h = r.getHauteur(); l = r.getLargeur(); }
		/// Récupérer le réseau initial de l'automate
		const Reseau& getReseauInit() const { return reseauInit; }
		/// Récupérer le nom de l'automate
		std::string getTitle() const { return title; }
		/// Redéfinir le nom de l'automate
		void setTitle(const std::string& t) { title = t; }
		/// Récupérer le nom de l'auteur
		std::string getAuthor() const { return author; }
		/// Redéfinir le nom de l'auteur
		void setAuthor(const std::string& a) { author = a; }
		/// Récupérer la description
		std::string getDesc() const { return desc; }
		/// Redéfinir la description
		void setDesc(const std::string& d) { desc = d; }
		/// Récupérer l'année
		int getYear() const { return year; }
		/// Redéfinir le nom de l'automate
		void setYear(const int y) { year = y; }

		/// Réinitialiser totalement la configuration de l'automate
		void reinitialiserAutomate();

		/// Définir le comportement aux frontières
		void setMatriceTorique(const bool val) { regleVoisinage->setMatriceTorique(val); }
		bool getMatriceTorique() { return regleVoisinage->getMatriceTorique(); }

		int getNbStep() const { return nbStep; }
		int getNbCycle() const { return nbCycle; }
};

#endif
