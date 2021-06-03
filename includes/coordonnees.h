#ifndef COORDONNEES_H
#define COORDONNEES_H

//on définit ici une structure Coordonnees permettant de décrire les coordonnées d'une cellule
//etant donné que notre grille est en 2D, on a donc deux coordonnées x et y

struct Coordonnees //peu d'intérêt de définir une classe pour qq chose de si simple, une structure fait l'affaire
{
    int x; //abscisse
    int y; //ordonnée
};

inline bool operator==(const Coordonnees& gauche, const Coordonnees& droite) { //test de l'égalité entre deux coordonnées
    return gauche.x == droite.x && gauche.y == droite.y;
}

inline bool operator!=(const Coordonnees& gauche, const Coordonnees& droite) { //test si deux coordonnées sont différentes
    return !(gauche == droite);
}

inline Coordonnees operator+(const Coordonnees& gauche, const Coordonnees& droite) { //opération d'addition entre deux coordonnées
    return {gauche.x + droite.x, gauche.y + droite.y};
}

inline Coordonnees operator-(const Coordonnees& gauche, const Coordonnees& droite) { //opération de soustraction entre deux coordonnées
    return {gauche.x - droite.x, gauche.y - droite.y};
}


#endif // COORDONNEES_H

