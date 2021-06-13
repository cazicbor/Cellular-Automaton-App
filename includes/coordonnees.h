#ifndef COORDONNEES_H
#define COORDONNEES_H

/// @brief Structure de Coordonnees permettant de décrire les coordonnées d'une cellule
///
/// etant donné que notre grille est en 2D, on a donc deux coordonnées x et y
/// peu d'intérêt de définir une classe pour qq chose de si simple, une structure fait l'affaire
/// les opérateurs ==, !=, + et - ont été redéfinis pour cette classe
struct Coordonnees
{
	/// Abscisse de la Coordonnees
	int x;
	/// Ordonnées de la Coordonnees
	int y;
};

/// Test de l'égalité entre deux Coordonnees
/// @param[in] gauche Coordonnees 1 de l'assertion
/// @param[in] droite Coordonnees 2 de l'assertion
inline bool operator==(const Coordonnees& gauche, const Coordonnees& droite) {
	return gauche.x == droite.x && gauche.y == droite.y;
}

/// Test si deux coordonnées sont différentes
/// @param[in] gauche Coordonnees 1 de l'assertion
/// @param[in] droite Coordonnees 2 de l'assertion
inline bool operator!=(const Coordonnees& gauche, const Coordonnees& droite) {
	return !(gauche == droite);
}

/// Opération d'addition entre deux coordonnées
/// @param[in] gauche Coordonnees 1 de l'opération
/// @param[in] droite Coordonnees 2 de l'opération
inline Coordonnees operator+(const Coordonnees& gauche, const Coordonnees& droite) {
	return {gauche.x + droite.x, gauche.y + droite.y};
}

/// Opération de soustraction entre deux coordonnées
/// @param[in] gauche Coordonnees 1 de l'opération
/// @param[in] droite Coordonnees 2 de l'opération
inline Coordonnees operator-(const Coordonnees& gauche, const Coordonnees& droite) {
	return {gauche.x - droite.x, gauche.y - droite.y};
}

#endif // COORDONNEES_H

