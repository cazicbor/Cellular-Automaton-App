#ifndef AUTOCELL_H
#define AUTOCELL_H

#include <reseau_cellule_etats.h>

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

class AutoCell : public QWidget

{
    static std::unique_ptr<AutoCell> instance;

    Reseau* Grille = nullptr;
    std::vector<QString> listeGrille;

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
    QPushButton* button_valider_delai;
    QPushButton* button_prev;
    QPushButton* button_run;
    QPushButton* button_next;
    QPushButton* button_reinitialiser;

    QLabel* lab_sauv_grille;
    QLineEdit* edit_nom_grille;
    QPushButton* button_save_grid;

    //définition de la frame affichage de la grille
    QWidget* win_grid;
    QTableWidget* grid;

    //notice
    QWidget* win_notice;
    QLabel* lab_notice;

    explicit AutoCell(QWidget* parent=nullptr);

    public:

    static AutoCell& getInstance() {
        if(instance == nullptr) {
            instance.reset(new AutoCell);
        }

        return *instance;
    }

    public slots:
    //void chargerModele();
    //void listerModele(); //à faire en dernier
    void chargerGrilles();
    //void listerGrille(); //déjà réfléchir à la recopie
    //Reseau initialiserGrille(); //méthode à implémenter qui récupère les données du formulaire - penser à réinitialiser les données annexes
    //void afficherGrille(Reseau&); //affiche une grille
    //void chargerGrilles(const QString &text);

    void afficherGrille(Reseau* Grille);

    void initialiserGrille();
    void RAZ();
    void gererSimulation();
    //void sauvegarderGrille();
    //Reseau& modifierCellule(const QModelIndex&, Reseau& Grille);//à implémenter

    void modifierCellule(const QModelIndex& index);
    void sauvegarderGrille();
    void defNouveauModele();
    void afficherErreur(QString& msg);
};

#endif // AUTOCELL_H
