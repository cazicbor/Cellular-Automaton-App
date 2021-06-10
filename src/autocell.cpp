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
    this->setMinimumSize(1150, 650);

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
        std::cout<<"modele :"<<noms_modeles[i].toStdString()<<std::endl;
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
    win_init->setFixedWidth(400);
    lab_init = new QLabel("Configuration du modèle :");

    form_init = new QGridLayout(win_init);

    form_saved_grids = new QFormLayout;
    form_config = new QFormLayout;

    form_init->addLayout(form_saved_grids, 1,1);
    form_init->addLayout(form_config, 1,0);

    list_grids = new QComboBox;
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

    grid_run_control->setColumnMinimumWidth(1,100);
    grid_run_control->setColumnMinimumWidth(2,100);
    grid_run_control->setRowMinimumHeight(3,80);
    grid_run_control->setRowMinimumHeight(4,400);

    grid_run_control->addWidget(lab_run_crtl, 0,0,1,3,Qt::AlignTop);

    lab_time_step = new QLabel("Pas de temps : ");
    edit_time_step = new QLineEdit;
    edit_time_step->setStyleSheet("background-color: rgb(255,255,255)");
    edit_time_step->setFixedWidth(30);
    edit_time_step->setText("1"); //valeur par défaut pour le pas de temps
    button_valider_delai = new QPushButton("valider");
    button_valider_delai->setStyleSheet("background-color: rgb(255,255,255)");
    button_valider_delai->setFixedWidth(50);
    //connect(button_valider_delai, SIGNAL(clicked()), Automate::getInstance(), SLOT(Automate::getInstance().setDelai()));
    button_prev = new QPushButton("<<");
    button_prev->setStyleSheet("background-color: rgb(255,255,255)");
    button_prev->setFixedSize(40,40);
    button_run = new QPushButton("RUN");
    button_run->setFixedSize(40,40);
    button_run->setStyleSheet("background-color: rgb(255,255,255)");
    connect(button_run, SIGNAL(clicked()), this, SLOT(gererSimulation()));
    button_next = new QPushButton(">>");
    button_next->setFixedSize(40,40);
    button_next->setStyleSheet("background-color: rgb(255,255,255)");
    button_reinitialiser = new QPushButton("Réinitialiser la simulation");
    button_reinitialiser->setStyleSheet("background-color: rgb(255,255,255)");
    button_reinitialiser->setFixedWidth(200);

    grid_run_control->addWidget(lab_time_step, 1, 0);
    grid_run_control->addWidget(edit_time_step, 1, 1);
    grid_run_control->addWidget(button_valider_delai, 1, 2);
    grid_run_control->addWidget(button_prev, 2, 0);
    grid_run_control->addWidget(button_run, 2, 1);
    grid_run_control->addWidget(button_next, 2, 2);
    grid_run_control->addWidget(button_reinitialiser, 3, 0, Qt::AlignCenter);

    lab_sauv_grille = new QLabel("Sauvegarder la grille courante");
    edit_nom_grille = new QLineEdit;
    edit_nom_grille->setPlaceholderText("Entrer un nom");
    edit_nom_grille->setStyleSheet("background-color: rgb(255,255,255)");

    edit_nom_grille->setFixedWidth(180);

    button_save_grid = new QPushButton("sauvegarder");
    button_save_grid->setFixedWidth(90);
    connect(button_save_grid,SIGNAL(clicked()),this,SLOT(sauvegarderGrille()));

    grid_run_control->addWidget(lab_sauv_grille,4,0,1,3, Qt::AlignBottom);
    grid_run_control->addWidget(edit_nom_grille,5,0, Qt::AlignBottom);
    grid_run_control->addWidget(button_save_grid,5,2,Qt::AlignBottom);

    general->addWidget(win_run_ctrl,1,0,2,1);

    //définition de la frame affichage de la grille

    win_grid = new QWidget;

    grid = new QTableWidget(0,0,win_grid);

    //notice

    win_notice = new QWidget;
    win_notice->setStyleSheet("background-color: rgb(204, 209, 209)");
    win_notice->setMaximumWidth(300);
    win_notice->setMinimumWidth(200);
    lab_notice = new QLabel("Notice :", win_notice);

    general->addWidget(win_notice,0,2,3,1);
};

void AutoCell::afficherGrille(Reseau* Grille)
{
    win_grid = new QWidget;

    unsigned int l = Grille->getLargeur();
    unsigned int h = Grille->getHauteur();

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

    for(unsigned int i=0; i<h; i++){
            for(unsigned int j=0; j<l; j++)
        {
            //vérifier si les cellules ont ou non été générés (!= nullptr)
            QString indice; indice.setNum(Grille->getReseau()[i][j].getIndEtat());

            QString label; label = QString::fromStdString(Automate::getInstance().getEnsemble().getEtat(indice.toInt()).getLabel()); //label de la cellule

            grid->setItem(i, j, new QTableWidgetItem(indice));
            grid->item(i,j)->setFlags(Qt::ItemIsEnabled);

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

    delete Grille;

    this->Grille = new Reseau(h,l);

    if (check_aleatoire->isChecked()) Grille->setAleatoire();

    QString nom_grille = list_grids->currentText();

    if (check_load_grid->isChecked()) {
      delete Grille;
      Grille = new Reseau(Database::getInstance().getReseau(listeGrille[list_grids->currentIndex()*2].toInt())); /// Méthode à implémenter
      QString str_largeur;
      //str_largeur.setNum(listeGrille[list_grids->currentIndex()*2].toInt());
      QString str_hauteur;
      //edit_largeur->setText(str_largeur);
      edit_largeur->setText(str_largeur.setNum(Grille->getLargeur(),10));
      edit_hauteur->setText(str_hauteur.setNum(Grille->getHauteur(),10));
      }

    //réinitialiser l'automate
    Automate::getInstance().reset();

    this->afficherGrille(this->Grille);

};
void AutoCell::RAZ(){
    delete grid;
    grid = new QTableWidget(0,0,win_grid);
    edit_largeur->setText("");
    edit_hauteur->setText("");
    edit_time_step->setText("1");
    check_aleatoire->setCheckState(Qt::Unchecked);
    check_load_grid->setCheckState(Qt::Unchecked);
;}

void AutoCell::defNouveauModele() {
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
        //Automate::getInstance().start();
    }
    else {
        button_run->setText("RUN");
        //Automate::getInstance().pause();
    }
}

void AutoCell::afficherErreur(QString& msg){
    QMessageBox messageBox;
    messageBox.critical(0,"Error",msg);
    messageBox.setFixedSize(500,200);
}

void AutoCell::initAutomate(const QString& name) {
	std::cout << name.toStdString() << std::endl;
	Database::getInstance().initSingletonAutomate(name);
}
