#ifndef PARAMETRAGEMODELE_H
#define PARAMETRAGEMODELE_H

#include "reseau_cellule_etats.h"

#include <QObject>
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QSpinBox>
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

class NouveauModele : public QWidget {
    Q_OBJECT
    QGridLayout* general;

    //définition de la frame paramétrage du modèle
    QWidget* fenetre_init;
    QGridLayout* form_init;
    QFormLayout* form_param;

    QSpinBox* nb_etats;
    QComboBox* liste_voisinage;
    QComboBox* liste_regle_transition;
    QPushButton* bouton_valide;


    //définition de la frame contenant la grille de sélection du voisinage
    QLabel* label_init;

    QWidget* fenetre_grid;
    QTableWidget* grid;
public:
    NouveauModele(QWidget* parent = nullptr);
public slots:
    void affGrille(Reseau* Grille);





};


#endif // PARAMETRAGEMODELE_H
