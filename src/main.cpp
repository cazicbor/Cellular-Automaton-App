#include "reseau_cellule_etats.h"
#include "autocell.h"

#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QLayoutItem>
#include <QFont>

using namespace std;

EnsembleEtat &enseEtats = EnsembleEtat::getInstance();


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    EnsembleEtat &enseEtats = EnsembleEtat::getInstance();

    enseEtats.ajouterEtat(0, "vivant", 239, 239, 239);
    enseEtats.ajouterEtat(1, "mort", 90, 94, 107);
    enseEtats.ajouterEtat(2, "zombie", 131, 166, 151);
    enseEtats.ajouterEtat(3, "fantôme", 22, 166, 151);


    //int largeur = 15;
    //int hauteur = 12;

    //Reseau Grille(hauteur, largeur);

    //Grille.setAleatoire();

    AutoCell autocell;
    //autocell.afficherGrille(&Grille);
    autocell.show();

    return app.exec();
}

