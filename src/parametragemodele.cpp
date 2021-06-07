#include"parametragemodele.h"


NouveauModele::NouveauModele(QWidget* parent) : QWidget() {
    this->setWindowTitle("Paramétrage d'un nouveau modèle");
    this->setMinimumSize(850, 550);

    fenetre_init = new QWidget;
    fenetre_init->setFixedWidth(400);
    label_init = new QLabel("Configuration du modèle :");
}

void NouveauModele::affGrille(Reseau* Grille) {

}

