#ifndef AUTOCELL_H
#define AUTOCELL_H

#include "reseau_cellule_etats.h"

#include <QObject>
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

using namespace std;

extern EnsembleEtat& enseEtats;

class AutoCell : public QWidget

{
    Reseau* Grille = nullptr;

    Q_OBJECT
    QGridLayout* general;

    //définition de la frame choix du modèle
    QWidget* win_model_choice;
    QLabel* lab_model_choice;
    QComboBox* liste;
    QGridLayout* grid_model_choice;
    QPushButton* button_add_model;

    //définition de la frame initialisation
    QWidget* win_init;
    QLabel* lab_init;
    QGridLayout* form_init;

    QFormLayout* form_saved_grids;
    QFormLayout* form_config;

    QComboBox *list_grids;
    QCheckBox* check_load_grid;

    QLineEdit* edit_largeur;
    QLineEdit* edit_hauteur;
    QCheckBox* check_aleatoire;
    QPushButton* button_valide_init;

    //définition de la frame "panneau de contrôle de l'exécution"
    QWidget* win_run_ctrl;
    QLabel* lab_run_crtl;

    QGridLayout* grid_run_control;

    QLabel* lab_time_step;
    QLineEdit* edit_time_step;
    QPushButton* button_prev;
    QPushButton* button_run;
    QPushButton* button_next;

    QPushButton* button_save_grid;

    //définition de la frame affichage de la grille
    QWidget* win_grid;
    QTableWidget* grid;

    //notice
    QWidget* win_notice;
    QLabel* lab_notice;

    public:
    explicit AutoCell(QWidget* parent=nullptr);

    public slots:
    //void chargerModele();
    //void listerModele(); //à faire en dernier
    //void chargerGrille();
    //void listerGrille(); //déjà réfléchir à la recopie
    //Reseau initialiserGrille(); //méthode à implémenter qui récupère les données du formulaire - penser à réinitialiser les données annexes
    //void afficherGrille(Reseau&); //affiche une grille

    void afficherGrille(Reseau* Grille);

    void initialiserGrille();
    void RAZ();
    //void faireSimulation();
    //void sauvegarderGrille();
    //Reseau& modifierCellule(const QModelIndex&, Reseau& Grille);//à implémenter

    void modifierCellule(const QModelIndex& index);
    void defNouveauModele();

};


#endif // AUTOCELL_H
