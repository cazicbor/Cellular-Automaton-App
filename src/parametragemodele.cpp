#include"parametragemodele.h"
#include <autocell.h>
#include <Automate.h>
#include <autosql.h>


NouveauModele::NouveauModele(QWidget* parent) : QWidget() {
    this->setWindowTitle("Paramétrage d'un nouveau modèle");
    this->setMinimumSize(850, 650);

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

    // infos sur l'automate
    QString nomDefaut = "Nouvel automate";
    nom_automate = new QLineEdit(nomDefaut);
    QString auteurDefaut = "Anonym";
    auteur = new QLineEdit(auteurDefaut);
    QString anneeDefaut = "2000";
    annee = new QLineEdit(anneeDefaut);
    QString descDefaut = "Nouvel automate créé par l'utilisateur";
    description = new QLineEdit(descDefaut);
    // nb d'états
    nb_etats = new QSpinBox;
    nb_etats->setRange(2, 8);
    etat = new QLabel("Nombre d'états :");

    //choisir un voisinage
    liste_voisinage = new QComboBox;



    liste_voisinage->setPlaceholderText("--- select ---");
    liste_voisinage->setCurrentIndex(-1);


    connect(liste_voisinage, SIGNAL(currentTextChanged(const QString&)), this, SLOT(paramVoisinage(const QString&)));

    //choisir une règle de transition

    //connect(liste_regle_transition, SIGNAL(currentIndexChanged(int)), liste_voisinage, SLOT(setCurrentIndex(int)));


    bouton_valide = new QPushButton("Valider");

    layoutvalid = new QHBoxLayout;

    boutonEtat = new QPushButton("Etats");

    layoutEtat = new QHBoxLayout;
    layoutEtat->addWidget(etat);
    layoutEtat->addWidget(nb_etats);




    valider_Etat = new QPushButton("Valider le nombre d'états");




    connect(boutonEtat, SIGNAL(clicked()), this, SLOT(parametrerEtats()));

    connect(bouton_valide, SIGNAL(clicked()), this, SLOT(validerParametrage()));
    connect(valider_Etat, SIGNAL(clicked()), this, SLOT(changerEtatDefault()));


    //ajout regle :
    form_choix->addRow("Nom automate :", nom_automate);
    form_choix->addRow("Auteur :", auteur);
    form_choix->addRow("Année :", annee);
    form_choix->addRow("Description :", description);
    form_choix->addRow(layoutEtat);
    form_choix->addRow(valider_Etat);



    //form_choix->addRow("Etat défaut :", etat_default);



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

void NouveauModele::parametrerEtats() {
    paramAlpha.reset(new ParamAlpha(nb_etats->value(), this));
	paramAlpha->show();
}

void NouveauModele::paramVoisinage(const QString& choix_voisinage){
    if(choix_voisinage == "Voisinage de von Neumann" || choix_voisinage == "Voisinage de Moore"){
        if (form_rayon != nullptr) delete form_rayon;
        if (grid != nullptr) delete grid;

        grid = new QTableWidget;
        grid = nullptr;

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

void NouveauModele::changerVoisinage(){

    Fonction* automateFonction = new Fonction(Automate::getInstance().getEnsemble().getEtat(static_cast<unsigned int>(etat_default->value())));
    Automate::getInstance().setFonction(automateFonction);

    //delete liste_voisinage;
    form_choix->removeRow(7);
    liste_voisinage = new QComboBox();
    layoutvalid = new QHBoxLayout;

    liste_voisinage->addItem("Voisinage de Moore");
    liste_voisinage->addItem("Voisinage de von Neumann");
    liste_voisinage->addItem("Voisinage arbitraire");
    liste_voisinage->setCurrentIndex(-1);


    form_choix->insertRow(7, "Voisinage :", liste_voisinage);

    connect(liste_voisinage, SIGNAL(currentTextChanged(const QString&)), this, SLOT(paramVoisinage(const QString&)));
}


void NouveauModele::choisirEtatCourant(const QString& validEtat){

    if (validEtat == "Oui"){

        if (fin != nullptr) delete fin;
        if (next != nullptr) delete next;
        if (layouth5 != nullptr) delete layouth5;
        if (layouth6 != nullptr) delete layouth6;
        if (layoutv2 != nullptr) delete layoutv2;
        if (etatCourant2 != nullptr) delete etatCourant2;
        if (numEtatCourant != nullptr) delete numEtatCourant;


        layouth6 = new QHBoxLayout;
        layouth5 = new QHBoxLayout;
        layoutv2 = new QVBoxLayout;


        fin = new QPushButton("Terminer");
        next = new QPushButton("Règle suivante");

        form_choix->insertRow(9,layoutv2);
        layoutv2->addLayout(layouth5);
        layoutv2->addLayout(layouth6);

        etatCourant2 = new QLabel("Etat Courant : ");

        numEtatCourant = new QSpinBox;
        numEtatCourant->setRange(0,nb_etats->value()-1);

        layouth5->addWidget(etatCourant2);
        layouth5->addWidget(numEtatCourant);

        layouth6->addWidget(fin);
        layouth6->addWidget(next);


        connect(next, SIGNAL(clicked()), this, SLOT(addRegle()));
        connect(fin, SIGNAL(clicked()), this, SLOT(validation()));


    }else{


       if (fin != nullptr) delete fin;
       if (next != nullptr) delete next;
       if (layouth5 != nullptr) delete layouth5;
       if (layouth6 != nullptr) delete layouth6;
       if (layoutv2 != nullptr) delete layoutv2;
       if (etatCourant2 != nullptr) delete etatCourant2;
       if (numEtatCourant != nullptr) delete numEtatCourant;


       numEtatCourant = new QSpinBox;
       numEtatCourant = nullptr;

       layouth6 = new QHBoxLayout;
       layouth5 = new QHBoxLayout;
       layoutv2 = new QVBoxLayout;


       etatCourant2 = new QLabel("Etat Courant non pris en compte ");

       fin = new QPushButton("Terminer");
       next = new QPushButton("Règle suivante");

       form_choix->insertRow(9,layoutv2);
       layoutv2->addLayout(layouth5);
       layoutv2->addLayout(layouth6);


       layouth5->addWidget(etatCourant2);

       layouth6->addWidget(fin);
       layouth6->addWidget(next);


       connect(next, SIGNAL(clicked()), this, SLOT(addRegle()));
       connect(fin, SIGNAL(clicked()), this, SLOT(validation()));


    }


}

void NouveauModele::paramRegle() {

    seuilMax = new QLabel("Seuil Max : ");
    seuilMin = new QLabel("Seuil Min : ");
    destination = new QLabel("Destination : ");
    etatCourant = new QLabel("Etat Courant : ");

    etatDest = new QSpinBox;
    etatDest->setRange(0, nb_etats->value()-1);

    valid_Etat = new QComboBox;
    valid_Etat->addItem("Oui");
    valid_Etat->addItem("Non");
    valid_Etat->setCurrentIndex(-1);


        seuilValidator=new QIntValidator;

        if(layouth1 != nullptr) delete layouth1;
        if(layouth2 != nullptr) delete layouth2;
        if(layouth3 != nullptr) delete layouth3;
        if(layouth4 != nullptr) delete layouth4;
        if(layoutv != nullptr) delete layoutv;
        if(layouth5 != nullptr) delete layouth5;
        if(layouth6 != nullptr) delete layouth6;
        if(layoutv2 != nullptr) delete layoutv2;


        layoutv = new QVBoxLayout;
        layouth1 = new QHBoxLayout;
        layouth2 = new QHBoxLayout;
        layouth3 = new QHBoxLayout;
        layouth4 = new QHBoxLayout;

        layouth6 = new QHBoxLayout;
        layouth5 = new QHBoxLayout;
        layoutv2 = new QVBoxLayout;


        form_choix->insertRow(8,layoutv);
        layoutv->addLayout(layouth1);
        layoutv->addLayout(layouth2);
        layoutv->addLayout(layouth3);
        layoutv->addLayout(layouth4);



        seuilValidator->setRange(0,1);

        layouth1->addWidget(seuilMin);
        for(int i=0; i<8; i++) {
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
         for(int i=0; i<8; i++) {
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



void NouveauModele::addRegle(){
    if(valid_Etat->currentIndex()==(-1));
    else
    {
        int min[8], max[8];

        for(int i = 0; i<8; i++)
        {
            min[i] = numSeuilMin[i]->text().toInt();
            max[i] = numSeuilMax[i]->text().toInt();
        }

        if(valid_Etat->currentIndex()==1)
            Automate::getInstance().getFonction().ajouterRegle(Automate::getInstance().getEnsemble().getEtat(etatDest->value()), min, max);

        else
            Automate::getInstance().getFonction().ajouterRegle(Automate::getInstance().getEnsemble().getEtat(etatDest->value()), min, max, numEtatCourant->value());

        paramRegle();
    }
}

void NouveauModele::validerParametrage(){

    Automate::getInstance().setTitle(nom_automate->text().toStdString());
    Automate::getInstance().setAuthor(auteur->text().toStdString());
    Automate::getInstance().setDesc(description->text().toStdString());
    Automate::getInstance().setYear(annee->text().toInt());

    Reseau* reseauInit = new Reseau(9,10);
    reseauInit = &reseauInit->setAleatoire();
    Automate::getInstance().setReseauInit(*reseauInit);

    Automate::getInstance().getFonction().setEtatDefaut(Automate::getInstance().getEnsemble().getEtat(etat_default->value()));

    if(liste_voisinage->currentIndex()==-1);
    else
        if(liste_voisinage->currentIndex()==0) //moore
        {
            RegleVoisinageMoore *regle_voisins = new RegleVoisinageMoore;
            regle_voisins->setr(rayon->value());
            Automate::getInstance().setRegleVoisinage(regle_voisins);
            Database::getInstance().saveAutomaton(Automate::getInstance());
            this->close();
        }
    else
        if(liste_voisinage->currentIndex()==1) //von neumann
        {
            RegleVoisinageNeumann *regle_voisins = new RegleVoisinageNeumann;
            regle_voisins->setr(rayon->value());
            Automate::getInstance().setRegleVoisinage(regle_voisins);
            Database::getInstance().saveAutomaton(Automate::getInstance());
            this->close();
        }
    else //arbitraire
        {
            RegleVoisinageArbitraire *regle_voisins = new RegleVoisinageArbitraire;
	    regle_voisins->getVoisinage(grid);
            Automate::getInstance().setRegleVoisinage(regle_voisins);
            Database::getInstance().saveAutomaton(Automate::getInstance());
            this->close();
        }
}




void NouveauModele::changerEtatDefault(){
    etat_default = new QSpinBox;
    etat_default->setRange(0,(nb_etats->value())-1);

    valider_EtatDefault = new QPushButton("Valider l'état de défaut");

    form_choix->removeRow(6);
    form_choix->addRow("Etat défaut : ",etat_default);
    form_choix->addRow(valider_EtatDefault);
    connect(valider_EtatDefault, SIGNAL(clicked()), this, SLOT(parametrerEtats()));
}

void NouveauModele::validation(){
    if(valid_Etat->currentIndex()==(-1));
    else
    {
        int min[8], max[8];

        for(int i = 0; i<8; i++)
        {
            min[i] = numSeuilMin[i]->text().toInt();
            max[i] = numSeuilMax[i]->text().toInt();
        }

        if(valid_Etat->currentIndex()==1)
            Automate::getInstance().getFonction().ajouterRegle(Automate::getInstance().getEnsemble().getEtat(etatDest->value()), min, max);

        else
            Automate::getInstance().getFonction().ajouterRegle(Automate::getInstance().getEnsemble().getEtat(etatDest->value()), min, max, numEtatCourant->value());
    }

    //bouton_valide = new QPushButton("Valider");
    form_choix->addRow(bouton_valide);
}
