#include"parametragemodele.h"


NouveauModele::NouveauModele(QWidget* parent) : QWidget() {
    this->setWindowTitle("Paramétrage d'un nouveau modèle");
    this->setMinimumSize(850, 550);

    general = new QGridLayout;
    this->setLayout(general);

    //définition de la frame paramétrage du modèle

    fenetre_init = new QWidget;
    fenetre_init->setStyleSheet("background-color: rgb(204, 209, 209)");
    fenetre_init->setFixedWidth(410);
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



    liste_voisinage->setPlaceholderText("--- select ---");
    liste_voisinage->setCurrentIndex(-1);


    connect(liste_voisinage, SIGNAL(currentTextChanged(const QString&)), this, SLOT(paramVoisinage(const QString&)));

    //choisir une règle de transition
    liste_regle_transition = new QComboBox;

    liste_regle_transition->setPlaceholderText("--- select ---");

    //liste_regle_transition->addItem("--- select ---");
    liste_regle_transition->addItem("Life Game");
    liste_regle_transition->addItem("Langston's Loop");
    liste_regle_transition->addItem("Brian's brain");
    liste_regle_transition->addItem("Circulaire de Griffeath");
    liste_regle_transition->addItem("Nouvelle fonction de transition");

    liste_regle_transition->setCurrentIndex(-1);

    //connect(liste_regle_transition, SIGNAL(currentIndexChanged(int)), liste_voisinage, SLOT(setCurrentIndex(int)));
    connect(liste_regle_transition, SIGNAL(currentTextChanged(const QString&)), this, SLOT(changerVoisinage(const QString&)));
    connect(liste_regle_transition, SIGNAL(currentTextChanged(const QString&)), this, SLOT(paramRegle(const QString)));

    bouton_valide = new QPushButton("Valider");
    bouton_valide->setFixedWidth(50);


    //ajout regle :

    form_choix->addRow("Nombre d'états :", nb_etats);
    form_choix->addRow("Règle de transition :", liste_regle_transition);
    form_choix->addRow("Voisinage :", liste_voisinage);
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
    boutonEtat = new QPushButton("Etats");
    boutonEtat->setFixedWidth(50);
    connect(boutonEtat, SIGNAL(clicked()), this, SLOT(parametrerEtats()));
    form_choix->addWidget(boutonEtat);


}

void NouveauModele::parametrerEtats() {
	paramAlpha.reset(new ParamAlpha(nb_etats->value()));
	paramAlpha->show();
}

void NouveauModele::paramVoisinage(const QString& choix_voisinage){
    if(choix_voisinage == "Voisinage de von Neumann" || choix_voisinage == "Voisinage de Moore"){
        if (form_rayon != nullptr)delete form_rayon;
        if (grid != nullptr) delete grid;

        form_rayon = new QFormLayout;
        rayon = new QSpinBox;

        form_rayon->addRow("Rayon du voisinage :", rayon);
        form_param->addLayout(form_rayon, 0, 0, 1, 1);
        //form_param->addLayout(form_rayon, 1, 0, 8, 1);
    }
    else if(choix_voisinage == "Voisinage arbitraire") {
        this->affGrille();
    }
    //else if(choix_voisinage == "--- select ---"){
        //delete form_rayon;
        //delete grid;
    //}

}
void NouveauModele::paramRegle(const QString& choix_regle) {
    seuilMax = new QLabel("Seuil Max : ");
    seuilMin = new QLabel("Seuil Min : ");
    destination = new QLabel("Destination : ");
    etatCourant = new QLabel("Etat Courant : ");

    etatDest = new QSpinBox;

    valid_Etat = new QComboBox;
    valid_Etat->addItem("Oui");
    valid_Etat->addItem("Non");
    valid_Etat->setCurrentIndex(-1);

    if (choix_regle == "Nouvelle fonction de transition") {
        seuilValidator=new QIntValidator;

        if(layouth1 != nullptr) delete layouth1;
        if(layouth2 != nullptr) delete layouth2;
        if(layouth3 != nullptr) delete layouth3;
        if(layouth4 != nullptr) delete layouth4;
        if(layoutv != nullptr) delete layoutv;
        if(layouth5 != nullptr) delete layouth5;
        if(layouth6 != nullptr) delete layouth6;
        if(layoutv2 != nullptr) delete layoutv2;

        layouth1 = new QHBoxLayout;
        layouth2 = new QHBoxLayout;
        layouth3 = new QHBoxLayout;
        layouth4 = new QHBoxLayout;
        layoutv = new QVBoxLayout;

        layouth6 = new QHBoxLayout;
        layouth5 = new QHBoxLayout;
        layoutv2 = new QVBoxLayout;

        form_choix->addRow(layoutv);
        layoutv->addLayout(layouth1);
        layoutv->addLayout(layouth2);
        layoutv->addLayout(layouth3);
        layoutv->addLayout(layouth4);



        seuilValidator->setRange(0,1);

        layouth1->addWidget(seuilMin);
        for(unsigned int i=0; i<8; i++) {
            numSeuilMin[i]=new QLineEdit;
            numSeuilMin[i]->setFixedWidth(22);
            numSeuilMin[i]->setMaxLength(2);
            numSeuilMin[i]->setText("-1");
            numSeuilMin[i]->setValidator(seuilValidator);
            if (i<nb_etats->value()){
            layouth1->addWidget(numSeuilMin[i]);
            }
         }


         layouth2->addWidget(seuilMax);
         for(unsigned int i=0; i<8; i++) {
             numSeuilMax[i]=new QLineEdit;
             numSeuilMax[i]->setFixedWidth(22);
             numSeuilMax[i]->setMaxLength(2);
             numSeuilMax[i]->setText("-1");
             numSeuilMax[i]->setValidator(seuilValidator);
             if (i<nb_etats->value()){
             layouth2->addWidget(numSeuilMax[i]);
             }
         }
         layouth3->addWidget(destination);
         layouth3->addWidget(etatDest);

         layouth4->addWidget(etatCourant);
         layouth4->addWidget(valid_Etat);
         connect(valid_Etat, SIGNAL(currentTextChanged(const QString&)), this, SLOT(choisirEtatCourant(const QString&)));
    }
}

void NouveauModele::choisirEtatCourant(const QString& validEtat){

    fin = new QPushButton("Terminer");
    next = new QPushButton("Règle suivante");




    if (validEtat == "Oui"){

        if(layouth5 != nullptr) delete layouth5;
        if(layouth6 != nullptr) delete layouth6;
        if(layoutv2 != nullptr) delete layoutv2;
        if(etatCourant2 != nullptr) delete etatCourant2;


        layouth6 = new QHBoxLayout;
        layouth5 = new QHBoxLayout;
        layoutv2 = new QVBoxLayout;

        form_choix->addRow(layoutv2);
        layoutv2->addLayout(layouth5);
        layoutv2->addLayout(layouth6);


        etatCourant2 = new QLabel("Etat Courant : ");

        numEtatCourant = new QSpinBox;
        numEtatCourant->setRange(1,8);

        layouth5->addWidget(etatCourant2);
        layouth5->addWidget(numEtatCourant);

        layouth6->addWidget(fin);
        layouth6->addWidget(next);

    }else{

       if(layouth5 != nullptr) delete layouth5;
       if(layouth6 != nullptr) delete layouth6;
       if(layoutv2 != nullptr) delete layoutv2;
       if(etatCourant2 != nullptr) delete etatCourant2;

       etatCourant2 = new QLabel("Etat Courant non pris en compte ");

       layouth6 = new QHBoxLayout;
       layouth5 = new QHBoxLayout;
       layoutv2 = new QVBoxLayout;

       form_choix->addRow(layoutv2);
       layoutv2->addLayout(layouth5);
       layoutv2->addLayout(layouth6);
       layouth5->addWidget(etatCourant2);
       layouth6->addWidget(fin);
       layouth6->addWidget(next);


    }

}


void NouveauModele::affGrille() {
    if (grid != nullptr) delete grid;
    grid = new QTableWidget(5,5);
    form_param->addWidget(grid, 0, 0, 7, 3);

    grid->horizontalHeader()->setVisible(false); //Pas de nom pour les colonnes.
    grid->verticalHeader()->setVisible(false);
    grid->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //Pas de barre pour scroller.
    grid->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(unsigned int i=0; i<5; i++){
        for(unsigned int j=0; j<5; j++)
        {
            grid->setRowHeight(j,80);
            grid->setColumnWidth(j,80);

            /*
            int x = i-3;
            int y = -1*(j-2);
            std::string co = "(";
            co += x;
            co += ",";
            co += y;
            co += ")";
            QString coordonnees = co;
            */

            grid->setItem(i, j, new QTableWidgetItem);
                grid->item(i, j)->setFlags(Qt::ItemIsEnabled);
                grid->item(i,j)->setBackground(Qt::white);

            }
        }
    QColor noir = Qt::black;
    grid->item(2,2)->setBackground(noir);

    connect(grid, SIGNAL(clicked(const QModelIndex&)), this, SLOT(modifGrille(const QModelIndex&)));
}



void NouveauModele::modifGrille(const QModelIndex& index){
    unsigned int i = index.row();
    unsigned int j = index.column();

    QColor rouge = Qt::red;
    QColor blanc = Qt::white;

    if (i == 2 && j == 2){
       return;
    }else if (grid->item(i,j)->background() == blanc){
         grid->item(i,j)->setBackground(rouge);
    }else if(grid->item(i,j)->background() == rouge){
         grid->item(i,j)->setBackground(blanc);
    }

}

void NouveauModele::changerVoisinage(const QString& choix_regle){

    //delete liste_voisinage;
    form_choix->removeRow(2);
    liste_voisinage = new QComboBox();



    if(choix_regle == "Life Game"){
        //liste_voisinage->addItem("--- select ---");
        liste_voisinage->addItem("Voisinage de von Neumann");
        liste_voisinage->addItem("Voisinage arbitraire");
        liste_voisinage->setCurrentIndex(-1);
    }
    else if(choix_regle == "Langston's Loop"){
        liste_voisinage->addItem("Voisinage de Moore");
        liste_voisinage->addItem("Voisinage arbitraire");
        liste_voisinage->setCurrentIndex(-1);
    }
    else if(choix_regle == "Brian's brain" || choix_regle == "Circulaire de Griffeath" || choix_regle == "Nouvelle fonction de transition"){
        //liste_voisinage->addItem("--- select ---");
        liste_voisinage->addItem("Voisinage de Moore");
        liste_voisinage->addItem("Voisinage de von Neumann");
        liste_voisinage->addItem("Voisinage arbitraire");
        liste_voisinage->setCurrentIndex(-1);
    }
    form_choix->insertRow(2, "Voisinage :", liste_voisinage);
    connect(liste_voisinage, SIGNAL(currentTextChanged(const QString&)), this, SLOT(paramVoisinage(const QString&)));
}

