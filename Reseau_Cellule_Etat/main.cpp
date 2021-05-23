#include "autocell.h"
#include "reseau_cellule_etats.h"

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

    enseEtats.ajouterEtat(0, "vivant", 100, 30, 22);
    enseEtats.ajouterEtat(1, "mort", 236, 240, 21);

    int largeur = 15;
    int hauteur = 12;

    Reseau Grille(hauteur, largeur);

    AutoCell autocell;
    autocell.afficherGrille(Grille);
    autocell.show();

    return app.exec();
}


