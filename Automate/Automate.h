#ifndef _AUTOMATE_H
#define _AUTOMATE_H

#include <memory>
#include "../Fonction_Regle/Fonction.h"
#include "../Voisinage/voisinage.hpp"

class Automate {
	private:
		static std::unique_ptr<Automate> instance;
		unsigned int delai;
		Fonction* fonction;
		RegleVoisinage* regleVoisinage;
		Automate(): delai(500), fonction(nullptr), regleVoisinage(nullptr) {}
		Automate(const Automate& a) = delete;
		Automate& operator=(const Automate& a) = delete;

	public:
		static Automate& getInstance() {
			if(instance == nullptr) {
				instance.reset(new Automate);
			}

			return *instance;
		}
		~Automate() { delete fonction; delete regleVoisinage; }
		void setFonction(Fonction& f) { delete fonction; fonction = new Fonction(f); }
		void setRegleVoisinage(RegleVoisinage& r) { delete regleVoisinage; regleVoisinage = new RegleVoisinage(r); }
		void setDelai(const unsigned int d) { delai = d; }
};

#endif
