#include <Automate.h>

std::unique_ptr<Automate> Automate::instance = nullptr;

void Automate::nextTimer()
{
    if((l!=0)&&(h!=0)) //il faut que l et h aient été initialisés autrement que nuls
    {
        if(buffer.size()!=0)    //il faut que l'on ait un premier réseau dans le buffer,  
        {                       //choisi par l'utilisateur (besoin d'une fonction initialiser() dans automate ?)
            Reseau r(*buffer.end()); //on crée un nouveau réseau à partir de l'ancien
            //on parcourt la liste de ses cellules
            for(size_t i = 0; i<h; i++)
            {
                for(size_t j = 0; j<l; j++)
                {
                    Etat& e = fonction->getEtatSuivant(, r.getReseau()[i][j]); //besoin d'un voisinage
                    while(r.getReseau()[i][j].getIndEtat()!=e.getIndice()) //besoin de getIndice
                        r.getReseau()[i][j].incrementerEtat();
                }
            }
            buffer.push_back(r);
        }
    }
}
