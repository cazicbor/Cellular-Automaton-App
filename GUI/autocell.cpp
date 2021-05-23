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
#include <QPushButton>
#include <QCheckBox>
#include <QFormLayout>
#include <QObject>
#include <string>
#include <QBrush>

#include <iostream>
#include <iomanip>

extern EnsembleEtat& enseEtats;

using namespace std;

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

    lab_model_choice = new QLabel("Choisir un modèle dans la liste :", win_model_choice);

    liste = new QComboBox(win_model_choice);
    liste->addItem("modèle 1");
    liste->addItem("modèle 2");
    liste->addItem("modèle 3");
    liste->addItem("modèle 4");
    liste->setStyleSheet("background-color : rgb(251, 252, 252 )");

    connect(liste,SIGNAL(currentIndexChanged(int)),this,SLOT(RAZ()));

    grid_model_choice = new QGridLayout(win_model_choice);
    grid_model_choice->addWidget(lab_model_choice, 0, 0, 1, 2);
    grid_model_choice->addWidget(liste, 1,0,3,1);

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

    form_init->addWidget(lab_init,0,0);

    general->addWidget(win_init,0,1,1,2);

    //définition de la frame "panneau de contrôle de l'exécution"

    win_run_ctrl = new QWidget;
    lab_run_crtl = new QLabel("Outils de contrôle :", win_run_ctrl);
    win_run_ctrl->setStyleSheet("background-color: rgb(174, 182, 191)");

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

void AutoCell::afficherGrille(Reseau& Grille)
{
    win_grid = new QWidget;

    unsigned int l = Grille.getLargeur();
    unsigned int h = Grille.getHauteur();

    delete grid;
    grid = new QTableWidget(h,l,win_grid);
    int dim_pixels_h=32; //Taille en pixel.
    int dim_pixels_v=30;

    grid->setFixedSize((l)*dim_pixels_h, h*dim_pixels_v);

    grid->horizontalHeader()->setVisible(false); //Pas de nom pour les colonnes.
    grid->verticalHeader()->setVisible(false);
    grid->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //Pas de barre pour scroller.
    grid->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QSize size(30, 30);
    QFont serifFont("Times", 8, QFont::DemiBold);

    for(unsigned int i=0; i<h; i++){
            for(unsigned int j=0; j<l; j++)
        {
            //vérifier si les cellules ont ou non été générés (!= nullptr)

            QString indice; indice.setNum(Grille.getReseau()[i][j].getIndEtat());

            QString label; label = QString::fromStdString(enseEtats.getEtat(indice.toInt()).getLabel()); //label de la cellule

            if (grid->item(i,j) == nullptr)
                grid->setItem(i, j, new QTableWidgetItem(label));

            //afficherCellule

            QColor color; color = enseEtats.getEtat(indice.toInt()).getColor();

            //QColor color(236, 240, 21);

            //QColor color = enseEtats.getEtat((Grille.getReseau()[i][j]).getIndEtat()).getColor(); //couleur de la cellule

            QBrush brush_color;
            brush_color.setColor(color);

            grid->item(i,j)->setBackground(brush_color.color());
            grid->item(i,j)->setForeground(Qt::black);
            grid->item(i,j)->setSizeHint(size);
            grid->item(i,j)->setFont(serifFont);

            grid->setColumnWidth(j,25);
        }
    }

    general->addWidget(win_grid,1,1,2,2);

};


void AutoCell::initialiserGrille(){
    bool ok;

    int l = (edit_largeur->text()).toInt(&ok, 10);

    int h = (edit_hauteur->text()).toInt(&ok, 10);

    QString str_l; str_l.setNum(l);
    QString str_h; str_h.setNum(h);

    Reseau Grille1(h,l);
    //Reseau Grille1(12,12);

    this->afficherGrille(Grille1);

}; //méthode à implémenter qui récupère les données du formulaire - penser à réinitialiser les données annexes


void AutoCell::RAZ(){
    delete grid;
    grid = new QTableWidget(0,0,win_grid);
    edit_largeur->setText("");
    edit_hauteur->setText("");
}
