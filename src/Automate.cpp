#include <Automate.h>

std::unique_ptr<Automate> Automate::instance = nullptr;

/// La méthode nextTimer calcule un nouveau pas de temps, elle s'occupe également de la taille du buffer des réseaux qui est pour le moment hardcodé mais qui peut très facilement devenir un attribut modifiable par accesseur si besoin
void Automate::nextTimer() {
	if((l != 0) && (h != 0)) { //il faut que l et h aient été initialisés autrement que nuls
		if(buffer.size() != 0) { //il faut que l'on ait un premier réseau dans le buffer, choisi par l'utilisateur
			Reseau r = Reseau(h, l);
			//on parcourt la liste de ses cellules
			for(size_t i = 0; i < h; ++i) {
				for(size_t j = 0; j < l; ++j) {
					Voisinage voisinage(&(*(--buffer.end())).getReseau()[i][j]);
					regleVoisinage->calculVoisinage(voisinage, *(--buffer.end()));
					const Etat e = fonction->getEtatSuivant(voisinage);
					while(r.getReseau()[i][j].getIndEtat() != e.getIndice())
						r.getReseau()[i][j].incrementerEtat();
				}
			}
			buffer.push_back(r);
			if(buffer.size() > 15) { // taille maximum du buffer : 15
				buffer.erase(buffer.begin());
			}
		}
		else {
			buffer.push_back(reseauInit);
			nextTimer();
		}
	}
}

void Automate::reinitialiserAutomate() {
	title = "";
	delai = 500;
	fonction.reset(nullptr);
	regleVoisinage.reset(nullptr);
	reseauInit = Reseau(0, 0);
	buffer.clear();
	itBuffer = buffer.begin();
	h = 0;
	l = 0;
	year = 2000;
	author = "Anonym";
	desc = "";
	ensemble.reset();
}

void Automate::step() {
	if(itBuffer==(--buffer.end())) {
		nextTimer();
		++nbStep;
	}
	itBuffer++;
	if(nbCycle == 0 && *(--buffer.end()) == reseauInit)
		nbCycle = nbStep;
	AutoCell::getInstance().afficherGrille(&*itBuffer);
}
