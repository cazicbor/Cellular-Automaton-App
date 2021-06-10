#include <Automate.h>

std::unique_ptr<Automate> Automate::instance = nullptr;

/// La méthode nextTimer calcule un nouveau pas de temps, elle s'occupe également de la taille du buffer des réseaux qui est pour le moment hardcodé mais qui peut très facilement devenir un attribut modifiable par accesseur si besoin
void Automate::nextTimer()
{
	std::cout << l << h << std::endl;
	if((l!=0)&&(h!=0)) //il faut que l et h aient été initialisés autrement que nuls
	{
		if(buffer.size()!=0)    //il faut que l'on ait un premier réseau dans le buffer,  
		{                       //choisi par l'utilisateur (besoin d'une fonction initialiser() dans automate ?)
			Reseau r = Reseau(*(--buffer.end())); //on crée un nouveau réseau à partir de l'ancien
			//on parcourt la liste de ses cellules
			for(size_t i = 0; i<h; i++)
			{
				for(size_t j = 0; j<l; j++)
				{
					Voisinage voisinage(&(*(--buffer.end())).getReseau()[i][j]);
					regleVoisinage->calculVoisinage(voisinage, *(--buffer.end()));
					const Etat e = fonction->getEtatSuivant(voisinage, r.getReseau()[i][j]);
					while(r.getReseau()[i][j].getIndEtat()!=e.getIndice())
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

void Automate::reinitialiserAutomate(){
    title = "";
    delai = 500;
    delete fonction;
    delete regleVoisinage;
    buffer.clear();
    itBuffer = buffer.begin();
    h = 0;
    l = 0;
    reseauInit = Reseau(0, 0);
    year = 2000;
    author = "Anonym";
    desc = "";
    ensemble.reset();
}
