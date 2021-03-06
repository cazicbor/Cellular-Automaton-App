#include <autocell.h>
#include <reseau_cellule_etats.h>
#include <autosql.h>
#include <Automate.h>
#include <parametragemodele.h>

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
#include <QPushButton>
#include <QCheckBox>
#include <QFormLayout>
#include <QObject>
#include <string>
#include <QBrush>
#include <QWindow>
#include <QMessageBox>

#include <array>
#include <iostream>
#include <iomanip>

using namespace std;

std::unique_ptr<AutoCell> AutoCell::instance = nullptr;

AutoCell::AutoCell(QWidget* parent):QWidget(parent)
{
this->setWindowTitle("Automate cellulaire");
    this->setMinimumSize(1000, 650);

    //division en frame de la fenêtre de l'application

    general = new QGridLayout;

    this->setLayout(general);

    //définition de la frame choix du modèle

    win_model_choice = new QWidget;
    win_model_choice->setStyleSheet("background-color: rgb(204, 209, 209)");
    win_model_choice->setFixedSize(300, 100);

    lab_model_choice = new QLabel("Choisir un modèle dans la liste ou \nen paramétrer un nouveau :", win_model_choice);

    button_add_model = new QPushButton("Ajouter un modèle");
    button_add_model->setToolTip("Configurer un nouveau modèle");
    button_add_model->setStyleSheet("background-color : rgb(251, 252, 252 )");
    button_add_model->setFixedWidth(140);

    connect(button_add_model, SIGNAL(clicked()), this, SLOT(defNouveauModele()));

    liste = new QComboBox(win_model_choice);
    liste->setPlaceholderText("--- select ---");

    // récupération des automates en mémoire

    std::vector<QString> noms_modeles = Database::getInstance().getAutomates();
    for(size_t i = 0 ; i<noms_modeles.size() ; i++){
        liste->addItem(noms_modeles[i]);
    }

    liste->setStyleSheet("background-color : rgb(251, 252, 252 )");
    liste->setFixedWidth(140);

    connect(liste,SIGNAL(currentIndexChanged(int)),this,SLOT(RAZ()));
    connect(liste,SIGNAL(currentIndexChanged(int)),this,SLOT(chargerGrilles()));
    connect(liste,SIGNAL(currentTextChanged(const QString&)),this,SLOT(initAutomate(const QString&)));


    grid_model_choice = new QGridLayout(win_model_choice);
    grid_model_choice->addWidget(lab_model_choice, 0, 0, 1, 2);
    grid_model_choice->addWidget(liste, 1,0,1,1);
    grid_model_choice->addWidget(button_add_model,1,1);

    general->addWidget(win_model_choice,0,0);

    //définition de la frame initialisation

    win_init = new QWidget;
    win_init->setFixedWidth(500);
    lab_init = new QLabel("Configuration du modèle :");

    form_init = new QGridLayout(win_init);

    form_saved_grids = new QFormLayout;
    form_config = new QFormLayout;

    form_init->addLayout(form_saved_grids, 1,1);
    form_init->addLayout(form_config, 1,0);

    list_grids = new QComboBox;
    list_grids->setFixedWidth(150);
    check_load_grid = new QCheckBox;

    edit_largeur = new QLineEdit;
    edit_largeur->setFixedWidth(30);
    edit_hauteur= new QLineEdit;
    edit_hauteur->setFixedWidth(30);
    check_aleatoire = new QCheckBox;
    button_valide_init = new QPushButton("Valider");
    button_valide_init->setFixedWidth(50);

    connect(button_valide_init,SIGNAL(clicked()),this,SLOT(initialiserGrille()));

    form_saved_grids->addRow(tr("Importer une grille"), check_load_grid);
    form_saved_grids->addRow(tr("Grilles enregistrées"), list_grids);
    form_saved_grids->addWidget(button_valide_init);

    form_config->addRow(tr("Largeur :"), edit_largeur);
    form_config->addRow(tr("Hauteur :"), edit_hauteur);
    form_config->addRow(tr("Remplissage aléatoire"), check_aleatoire);

    form_init->addWidget(lab_init,0,0,1,3);

    general->addWidget(win_init,0,1,1,2);

    //définition de la frame "panneau de contrôle de l'exécution"

    win_run_ctrl = new QWidget;
    win_run_ctrl->setFixedWidth(300);
    lab_run_crtl = new QLabel("Outils de contrôle :");
    win_run_ctrl->setStyleSheet("background-color: rgb(174, 182, 191)");


    grid_run_control = new QGridLayout(win_run_ctrl);

    grid_run_control->setColumnMinimumWidth(1,80);
    grid_run_control->setColumnMinimumWidth(2,80);
    grid_run_control->setRowMinimumHeight(3,80);
    grid_run_control->setRowMinimumHeight(7,300);

    grid_run_control->addWidget(lab_run_crtl, 0,0,1,3,Qt::AlignTop);

    matriceTorique = new QCheckBox("Matrice torique");
    connect(matriceTorique, SIGNAL(stateChanged(int)), this, SLOT(setMatriceTorique(int)));

    lab_time_step = new QLabel("Pas de temps : ");
    spin_time_step = new QSpinBox;
    spin_time_step->setStyleSheet("background-color: rgb(255,255,255)");
    spin_time_step->setFixedWidth(70);
    spin_time_step->setValue(1000);
    spin_time_step->setRange(500,2500);
    connect(spin_time_step, SIGNAL(valueChanged(int)), this, SLOT(changeDelai()));
    button_prev = new QPushButton("<<");
    button_prev->setStyleSheet("background-color: rgb(255,255,255)");
    button_prev->setFixedSize(40,40);
    connect(button_prev, SIGNAL(clicked()), this, SLOT(previous()));
    button_run = new QPushButton("RUN");
    button_run->setFixedSize(40,40);
    button_run->setStyleSheet("background-color: rgb(255,255,255)");
    connect(button_run, SIGNAL(clicked()), this, SLOT(gererSimulation()));
    button_next = new QPushButton(">>");
    button_next->setFixedSize(40,40);
    button_next->setStyleSheet("background-color: rgb(255,255,255)");
    connect(button_next, SIGNAL(clicked()), this, SLOT(next()));
    button_reinitialiser = new QPushButton("Réinitialiser la simulation");
    button_reinitialiser->setStyleSheet("background-color: rgb(255,255,255)");
    button_reinitialiser->setFixedWidth(200);
    connect(button_reinitialiser, SIGNAL(clicked()), this, SLOT(reinitialiserSimulation()));

    lab_nb_step = new QLabel("Nombre d'étapes : ");
    edit_nb_step = new QLineEdit;
    edit_nb_step->setReadOnly(true);
    edit_nb_step->setFixedWidth(30);
    edit_nb_step->setText("0");
    edit_nb_step->setStyleSheet("background-color: rgb(255,255,255)");
    lab_periode = new QLabel("Période observée : ");
    edit_periode = new QLineEdit;
    edit_periode->setReadOnly(true);
    edit_periode->setFixedWidth(30);
    edit_periode->setText("0");
    edit_periode->setStyleSheet("background-color: rgb(255,255,255)");

    grid_run_control->addWidget(matriceTorique, 1, 0, Qt::AlignCenter);
    grid_run_control->addWidget(lab_time_step, 2, 0);
    grid_run_control->addWidget(spin_time_step, 2, 1);
    grid_run_control->addWidget(button_prev, 3, 0);
    grid_run_control->addWidget(button_run, 3, 1);
    grid_run_control->addWidget(button_next, 3, 2);
    grid_run_control->addWidget(button_reinitialiser, 4, 0, Qt::AlignTop);

    grid_run_control->addWidget(lab_nb_step, 5,0);
    grid_run_control->addWidget(edit_nb_step, 5,1);
    grid_run_control->addWidget(lab_periode,6,0);
    grid_run_control->addWidget(edit_periode,6,1);

    lab_sauv_grille = new QLabel("Sauvegarder la grille courante");
    edit_nom_grille = new QLineEdit;
    edit_nom_grille->setPlaceholderText("Entrer un nom");
    edit_nom_grille->setStyleSheet("background-color: rgb(255,255,255)");

    edit_nom_grille->setFixedWidth(180);

    button_save_grid = new QPushButton("sauvegarder");
    button_save_grid->setFixedWidth(90);
    connect(button_save_grid,SIGNAL(clicked()),this,SLOT(sauvegarderGrille()));

    grid_run_control->addWidget(lab_sauv_grille,7,0,1,3, Qt::AlignBottom);
    grid_run_control->addWidget(edit_nom_grille,8,0, Qt::AlignBottom);
    grid_run_control->addWidget(button_save_grid,8,2,Qt::AlignBottom);

    general->addWidget(win_run_ctrl,1,0,2,1);

    //définition de la frame affichage de la grille

    win_grid = new QWidget;

    grid = new QTableWidget(0,0,win_grid);

    afficherNotice();
};

void AutoCell::afficherGrille(const Reseau* grille)
{
	Grille.reset(new Reseau(*grille));
    win_grid = new QWidget;

    int l = Grille->getLargeur();
    int h = Grille->getHauteur();

    delete grid;
    grid = new QTableWidget(h,l,win_grid);

    int dim_pixels_h=40; //Taille en pixel.
    int dim_pixels_v=40;

    grid->setFixedSize((l)*dim_pixels_h, h*dim_pixels_v);

    grid->horizontalHeader()->setVisible(false); //Pas de nom pour les colonnes.
    grid->verticalHeader()->setVisible(false);
    grid->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //Pas de barre pour scroller.
    grid->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    grid->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    QFont serifFont("Times", 8, QFont::DemiBold);

    for(int i=0; i < h; ++i) {
            for(int j=0; j < l; ++j) {
            QString indice; indice.setNum(Grille->getReseau()[i][j].getIndEtat());

            QString label; label = QString::fromStdString(Automate::getInstance().getEnsemble().getEtat(indice.toInt()).getLabel()); //label de la cellule

            grid->setItem(i, j, new QTableWidgetItem(indice));
            grid->item(i,j)->setFlags(Qt::ItemIsEnabled);
            grid->item(i,j)->setToolTip(label);

            //afficherCellule

            QColor color; color = Automate::getInstance().getEnsemble().getEtat(indice.toInt()).getColor();

            QBrush brush_color;
            brush_color.setColor(color);

            grid->item(i,j)->setBackground(brush_color.color());
            grid->item(i,j)->setForeground(Qt::black);
            grid->item(i,j)->setFont(serifFont);
            grid->setColumnWidth(j,40);
        }
    grid->setRowHeight(i,40);
    }
    connect(grid,SIGNAL(clicked(const QModelIndex&)),this,SLOT(modifierCellule(const QModelIndex&)));
    general->addWidget(win_grid,1,1,2,2);

    edit_nb_step->setText(to_string(Automate::getInstance().getNbStep()).c_str());
    edit_periode->setText(to_string(Automate::getInstance().getNbCycle()).c_str());
};


void AutoCell::initialiserGrille(){
    bool ok;

    int l = (edit_largeur->text()).toInt(&ok, 10);
    int h = (edit_hauteur->text()).toInt(&ok, 10);

    QString str_l; str_l.setNum(l);
    QString str_h; str_h.setNum(h);

    if((0>=h || h>21 || 0>=l || l>41) && !check_load_grid->isChecked()){
        QString msg("erreur dimensions");
        afficherErreur(msg);
        edit_largeur->setText("");
        edit_hauteur->setText("");
        return;
    }

    Reseau grille = Reseau(h,l, Automate::getInstance().getFonction().getEtatDefaut().getIndice());

    if (check_aleatoire->isChecked())
	    grille.setAleatoire();

    QString nom_grille = list_grids->currentText();

    if (check_load_grid->isChecked()) {
      grille = Reseau(Database::getInstance().getReseau(listeGrille[list_grids->currentIndex()*2].toInt()));
      QString str_largeur;
      QString str_hauteur;
      edit_largeur->setText(str_largeur.setNum(grille.getLargeur(),10));
      edit_hauteur->setText(str_hauteur.setNum(grille.getHauteur(),10));
      }

    this->afficherGrille(&grille);
    Automate::getInstance().reset();
    Automate::getInstance().setReseauInit(grille);
    Automate::getInstance().initialiserBuffer();
};
void AutoCell::RAZ(){
    delete grid;
    grid = new QTableWidget(0,0,win_grid);
    edit_largeur->setText("");
    edit_hauteur->setText("");
    edit_nb_step->setText("0");
    edit_periode->setText("0");
    spin_time_step->setValue(1000);
    check_aleatoire->setCheckState(Qt::Unchecked);
    check_load_grid->setCheckState(Qt::Unchecked);
;}

void AutoCell::defNouveauModele() {
    Automate::getInstance().reinitialiserAutomate();
    NouveauModele* nouveaumodele = new NouveauModele;
    nouveaumodele->show();
}

void AutoCell::modifierCellule(const QModelIndex& index) {
    unsigned int i = index.row();
    unsigned int j = index.column();

    Grille->getReseau()[i][j].incrementerEtat();

    unsigned int indice = (Grille->getReseau()[i][j].getIndEtat());

    QString str_indice ; str_indice.setNum(indice, 10);

    QColor color; color = Automate::getInstance().getEnsemble().getEtat(indice).getColor();

    QBrush brush_color;
    brush_color.setColor(color);

    grid->item(i,j)->setBackground(brush_color.color());
    grid->item(i,j)->setText(str_indice);

    //réitnitialiser l'automate ou modif du buffer d
    Automate::getInstance().reset();
    Automate::getInstance().setReseauInit(*Grille);
    Automate::getInstance().initialiserBuffer();
}

void AutoCell::sauvegarderGrille(){
     if(edit_nom_grille->text()==""){
        QString msg("Entrer un nom");
        afficherErreur(msg);
        return;
    }
    QString nom_grille;
    nom_grille = edit_nom_grille->text();
    QString nom_automate;
    nom_automate = liste->currentText();
    Database::getInstance().stockerReseau(*Grille, nom_grille, nom_automate);
    edit_nom_grille->setText("");
    QMessageBox messageBox;
    messageBox.critical(0,"Confirmation", "Grille enregistrée");
    messageBox.setFixedSize(500,200);
};

void AutoCell::chargerGrilles(){
    listeGrille.clear();
    QString text;
    QString nb;
    text = liste->currentText();

    list_grids->clear();
    vector<QString> noms = Database::getInstance().getListeReseaux(text);
    nb.setNum(noms.size());

    for(size_t i=1 ; i<noms.size() ; i = i + 2)
        list_grids->addItem(noms[i]);
    listeGrille = noms;
}

void AutoCell::gererSimulation(){
    if(button_run->text() == "RUN"){
        button_run->setText("STOP");
        Automate::getInstance().start();
    }
    else {
        button_run->setText("RUN");
        Automate::getInstance().pause();
    }
}

void AutoCell::afficherErreur(QString& msg){
    QMessageBox messageBox;
    messageBox.critical(0,"Error",msg);
    messageBox.setFixedSize(500,200);
}

void AutoCell::initAutomate(const QString& name) {
	try {
		Database::getInstance().initSingletonAutomate(name);
	}
	catch(const char* m) {
		QString msg(m);
		afficherErreur(msg);
	}
	Automate::getInstance().setMatriceTorique(true);
	matriceTorique->setCheckState(Qt::Checked);
}

void AutoCell::changeDelai() {
    Automate::getInstance().setDelai(static_cast<unsigned int>(spin_time_step->value()));
}

void AutoCell::next() {
	Automate::getInstance().step();
}

void AutoCell::previous() {
	try {
		Automate::getInstance().previous();
	}
	catch (const char* m)
	{
		QString msg(m);
		afficherErreur(msg);
	}
}

void AutoCell::setMatriceTorique(int val) {
	try {
		if (val == 0)
			Automate::getInstance().setMatriceTorique(false);
		else
			Automate::getInstance().setMatriceTorique(true);
	}
	catch (const char* m) {
		QString msg(m);
		afficherErreur(msg);
	}
}

void AutoCell::reinitialiserSimulation()
{
    Automate::getInstance().reset();
    afficherGrille(&Automate::getInstance().getReseauInit());
}

void AutoCell::afficherNotice(){
    fenetre_notice.reset(new QWidget);
    fenetre_notice.get()->setMinimumWidth(1000);
    fenetre_notice.get()->setMinimumHeight(800);
    fenetre_notice->setWindowTitle("Notice");
    QString str_notice("--- Partie simulation ---\n\n1/ Choix du modèle\n \n Sélectionnez un modèle d'automate préenregistré ou en enregistrez un nouveau. Un modèle comprend ; un ensemble d'états, une fonction de transistion, un mode de détermination du\n voisinnage.\n \n2/ Initialisation de la grille de départ\n \nPour importer une grille préenregistrée associée à l'automate chargé, sélectionnez 'Importer Grille' et choisir une grille dans la liste déroulante.\nPour définir une grille personnalisable ; entrez la largeur souhaitée (entre 1 et 40) puis la hauteur (entre 1 et 20). Si vous souhaitez que la grille soit générée aléatoirement,\ncliquez sur 'Aléatoire'. Pour intitialiser l'automate selon vos choix ; cliquez sur 'Valider'.\n \n3/ Gestion de la simulation\n \nAprès avoir sélectionné un modèle et initialisé la grille de départ, vous pouvez choisir un pas de temps et cliquer sur 'RUN' pour lancer la simulation en mode automatique.\nPour indiquer un nouveau pas de temps, il faut mettre la simulation en pause puis la relancer pour que le changement devienne effectif. Les boutons << et >> servent respectivement\nà revenir aux états précédents (15 grilles sont sauvegardées) et à avancer manuellement dans la simulation.\nLe champs 'période' indique le nombre d'étapes nécéssaires pour revenir à la grille initiale. Si ce n'est jamais le cas, ce champs reste à 0.\n \n4/ Sauvegarde des données\n \nVous pouvez sauvegarder la grille qui s'affiche à tout moment en cliquant sur le bouton 'sauvegarder'.\nLa grille sera alors enregistrée en mémoire avec le nom indiqué dans la barre de saisie et automatiquement associée au modèle de l'automate chargé.\nVous pourrez alors sélectionner cette grille lors du prochain chargement de ce modèle.");
    lab_notice.reset(new QLabel(str_notice, fenetre_notice.get()));
    fenetre_notice.get()->show();
};
