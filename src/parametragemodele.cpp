#include"parametragemodele.h"


NouveauModele::NouveauModele(QWidget* parent) : QWidget() {
    this->setWindowTitle("Paramétrage d'un nouveau modèle");
    this->setMinimumSize(850, 550);

    general = new QGridLayout;
    this->setLayout(general);

    //définition de la frame paramétrage du modèle

    fenetre_init = new QWidget;
    fenetre_init->setStyleSheet("background-color: rgb(204, 209, 209)");
    fenetre_init->setFixedWidth(300);
    label_init = new QLabel("Configuration du modèle :");

    form_init = new QGridLayout(fenetre_init);

    form_choix = new QFormLayout;

    form_init->addWidget(label_init, 0, 0, 1, 2);
    form_init->addLayout(form_choix, 1, 0, 8, 2);

    // nb d'états
    nb_etats = new QSpinBox;
    nb_etats->setRange(1, 8);

    //choisir un voisinage
    liste_voisinage = new QComboBox;
    liste_voisiange->setPlaceholderText("--- select ---");
    liste_voisinage->setCurrentIndex(-1);

    //liste_voisinage->addItem("--- select ---");
    liste_voisinage->addItem("Voisinage de von Neumann");
    liste_voisinage->addItem("Voisinage de Moore");
    liste_voisinage->addItem("Voisinage arbitraire");

    connect(liste_voisinage, SIGNAL(currentTextChanged(const QString&)), this, SLOT(paramVoisinage(const QString&)));

    //choisir une règle de transition
    liste_regle_transition = new QComboBox;
    liste_regle_transition->addItem("Life Game");
    liste_regle_transition->addItem("Brian's brain");
    liste_regle_transition->addItem("Circulaire de Griffeath");
    liste_regle_transition->addItem("Langston's Loop");

    bouton_valide = new QPushButton("Valider");
    bouton_valide->setFixedWidth(50);

    //connect(bouton_valide, SIGNAL(clicked()), SLOT(affParametrage()));

    form_choix->addRow("Nombre d'états :", nb_etats);
    form_choix->addRow("Voisinage :", liste_voisinage);
    form_choix->addRow("Règle de transition :", liste_regle_transition);
    form_choix->addWidget(bouton_valide);

    general->addWidget(fenetre_init, 0, 0, 9, 1);

    //définition de la frame contenant la grille de sélection du voisinage
    fenetre_param = new QWidget;
    fenetre_param->setFixedWidth(500);
    label_param = new QLabel("Paramétrer votre choix :");

    form_param = new QGridLayout(fenetre_param);
    form_rayon = new QFormLayout;
    rayon = new QSpinBox;

    general->addWidget(label_param, 0, 1, 1, 1);
    general->addWidget(fenetre_param, 1, 1, 8, 1);

    /*
    form_param->addWidget(label_param, 0, 0, 1, 1);
    form_param->addLayout(form_rayon, 1, 0, 8, 1);

    general->addWidget(fenetre_param, 0, 1, 9, 1);
    */

}

void NouveauModele::paramVoisinage(const QString& choix_voisinage){
    if(choix_voisinage == "Voisinage de von Neumann" || choix_voisinage == "Voisinage de Moore"){
        delete form_rayon;
        delete grid;
        form_rayon = new QFormLayout;
        rayon = new QSpinBox;

        form_rayon->addRow("Rayon du voisinage :", rayon);
        form_param->addLayout(form_rayon, 0, 0, 1, 1);
        //form_param->addLayout(form_rayon, 1, 0, 8, 1);
    }
    else if(choix_voisinage == "Voisinage arbitraire") {
        this->affGrille();
    }
    else if(choix_voisinage == "--- select ---"){
        //delete form_rayon;
        //delete grid;
    }

}

void NouveauModele::affGrille() {
    delete grid;
    grid = new QTableWidget(5, 5);
    form_param->addWidget(grid, 0, 0, 8, 1);

    grid->horizontalHeader()->setVisible(false); //Pas de nom pour les colonnes.
    grid->verticalHeader()->setVisible(false);
    grid->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //Pas de barre pour scroller.
    grid->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(unsigned int i=0; i<5; i++){
        for(unsigned int j=0; j<5; j++)
        {
            grid->setRowHeight(j,80);
            grid->setColumnWidth(j, 80);
        }
    }

}


