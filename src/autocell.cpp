#include "autocell.h"
#include "reseau_cellule_etats.h"
#include "autosql.h"
#include "Automate.h"

#include <QApplication>
#include <QPushButton>
    button_add_model->setFixedWidth(140);

    liste = new QComboBox(win_model_choice);
    liste->setPlaceholderText("--- select ---");

    // récupération des automates en mémoire

    /*vector<QString> noms_modeles = database.getAutomates();
    for(auto : nom, noms_modeles){
        liste->addItem(nom);
    }*/

    liste->addItem("modèle 1");
    liste->addItem("modèle 2");
    liste->addItem("modèle 3");
    liste->addItem("modèle 4");


    liste->setStyleSheet("background-color : rgb(251, 252, 252 )");
    liste->setFixedWidth(140);

    connect(liste,SIGNAL(currentIndexChanged(int)),this,SLOT(RAZ()));
    connect(liste,SIGNAL(currentTextChanged(const QString &text)),this,SLOT(chargerGrilles(const QString &text)));


    grid_model_choice = new QGridLayout(win_model_choice);
    grid_model_choice->addWidget(lab_model_choice, 0, 0, 1, 2);

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

    button_save_grid = new QPushButton("sauvegarder la grille");

    grid_run_control->addWidget(button_save_grid,4,1,4,3,Qt::AlignBottom);

    general->addWidget(win_run_ctrl,1,0,2,1);

    delete grid;
    grid = new QTableWidget(h,l,win_grid);

    int dim_pixels_h=40; //Taille en pixel.
    int dim_pixels_v=40;

    grid->setFixedSize((l)*dim_pixels_h, h*dim_pixels_v);

    grid->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //Pas de barre pour scroller.
    grid->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    grid->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    QFont serifFont("Times", 8, QFont::DemiBold);

    for(unsigned int i=0; i<h; i++){
            for(unsigned int j=0; j<l; j++)
        {
            //vérifier si les cellules ont ou non été générés (!= nullptr)
            QString indice; indice.setNum(Grille->getReseau()[i][j].getIndEtat());

            QString label; label = QString::fromStdString(enseEtats.getEtat(indice.toInt()).getLabel()); //label de la cellule

            grid->setItem(i, j, new QTableWidgetItem(indice));
            grid->item(i,j)->setFlags(Qt::ItemIsEnabled);

            //afficherCellule

            QColor color; color = enseEtats.getEtat(indice.toInt()).getColor();
            grid->item(i,j)->setBackground(brush_color.color());
            grid->item(i,j)->setForeground(Qt::black);
            grid->item(i,j)->setFont(serifFont);
            grid->setColumnWidth(j,40);
        }
    grid->setRowHeight(i,40);
    }
    connect(grid,SIGNAL(clicked(const QModelIndex&)),this,SLOT(modifierCellule(const QModelIndex&)));
    general->addWidget(win_grid,1,1,2,2);
    bool ok;

    int l = (edit_largeur->text()).toInt(&ok, 10);
    int h = (edit_hauteur->text()).toInt(&ok, 10);

    QString str_l; str_l.setNum(l);

    if (check_aleatoire->isChecked()) Grille->setAleatoire();

    QString nom_grille = list_grids->currentText();
    /*if (check_load_grid->isChecked()) {
      delete Grille;
      Grille = new Reseau(getGrilleFromDb(nom_grille)) /// Méthode à implémenter
      QString str_largeur;
      QString str_hauteur;
      edit_largeur->setText(str_largeur.setNum(Grille.getLargeur,10);
      edit_hauteur->setText(str_hauteur.setNum(Grille.getHauteur,10);
      }*/

    //réinitialiser l'automate

    this->afficherGrille(this->Grille);

};
    edit_largeur->setText("");
    edit_hauteur->setText("");
    edit_time_step->setText("1");
    check_aleatoire->setCheckState(Qt::Unchecked);
    check_load_grid->setCheckState(Qt::Unchecked);
;}

void AutoCell::modifierCellule(const QModelIndex& index) {
    unsigned int i = index.row();
    unsigned int j = index.column();

    Grille->getReseau()[i][j].incrementerEtat();

    unsigned int indice = (Grille->getReseau()[i][j].getIndEtat());

    QString str_indice ; str_indice.setNum(indice, 10);

    QColor color; color = enseEtats.getEtat(indice).getColor();

    
    QBrush brush_color;
    brush_color.setColor(color);

    grid->item(i,j)->setBackground(brush_color.color());
    grid->item(i,j)->setText(str_indice);

    //réitnitialiser l'automate ou modif du buffer d
}

void AutoCell::chargerGrilles(const QString& text){
    list_grids->clear();
    /*vector<QString> noms = database.getListesReseaux(text);
    for(auto nom : noms) list_grids->addItem(nom);*/
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
