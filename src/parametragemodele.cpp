#include"parametragemodele.h"


NouveauModele::NouveauModele(QWidget* parent) : QWidget() {
    this->setWindowTitle("Paramétrage d'un nouveau modèle");
    this->setMinimumSize(850, 550);

    general = new QGridLayout;
    this->setLayout(general);

    //définition de la frame paramétrage du modèle

    fenetre_init = new QWidget;
    fenetre_init->setStyleSheet("background-color: rgb(204, 209, 209)");
    fenetre_init->setFixedWidth(400);
    label_init = new QLabel("Configuration du modèle :");

    form_init = new QGridLayout(fenetre_init);

    form_param = new QFormLayout;

    form_init->addWidget(label_init, 0, 0, 1, 2);
    form_init->addLayout(form_param, 1, 0, 8, 2);

    nb_etats = new QSpinBox;

    liste_voisinage = new QComboBox;
    liste_voisinage->addItem("Voisinage de von Neumann");
    liste_voisinage->addItem("Voisinage de Moore");
    liste_voisinage->addItem("Voisinage arbitraire");

    liste_regle_transition = new QComboBox;
    liste_regle_transition->addItem("Life Game");
    liste_regle_transition->addItem("Brian's brain");
    liste_regle_transition->addItem("Circulaire de Griffeath");
    liste_regle_transition->addItem("Langston's Loop");

    bouton_valide = new QPushButton("Valider");
    bouton_valide->setFixedWidth(50);

    //connect(bouton_valide, SIGNAL(clicked()), SLOT(ajouterModele));

    form_param->addRow("Nombre d'états :", nb_etats);
    form_param->addRow("Voisinage :", liste_voisinage);
    form_param->addRow("Règle de transition :", liste_regle_transition);
    form_param->addWidget(bouton_valide);

    general->addWidget(fenetre_init, 0, 0);

    //définition de la frame contenant la grille de sélection du voisinage

}

void NouveauModele::affGrille(Reseau* Grille) {

}

