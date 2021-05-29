#ifndef _AUTOMATE_H
#define _AUTOMATE_H

#include <memory>

class Automate {
	private:
		static std::unique_ptr<Automate> instance;
		unsigned int delai;
		Automate(): delai(500) {};
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
		void setFonction(Fonction& f);
		void setRegleVoisinage(RegleVoisinage& r);
		void setDelai(const unsigned int d) { delai = d; }
};

#endif
