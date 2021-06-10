#ifndef PARAMETRAGEMODELE_H
#define PARAMETRAGEMODELE_H

#include <reseau_cellule_etats.h>
#include <paramalpha.h>

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
#include <QBrush>
#include <QMouseEvent>

using namespace std;

class NouveauModele : public QWidget {
    Q_OBJECT
    QGridLayout* general;

    //définition de la frame paramétrage du modèle
    QWidget* fenetre_init;
    QLabel* label_init;
    QGridLayout* form_init;

    QFormLayout* form_choix;

    QSpinBox* nb_etats;
    QComboBox* liste_voisinage;
    QComboBox* liste_regle_transition;
    QPushButton* bouton_valide;

    //definition frame règle de transitions
    QWidget* fenetre_regle;
    QLabel* seuilMax;
    QLabel* seuilMin;
    QLabel* destination;
    QLabel* etatCourant;
    QLabel* etatCourant2;

    QComboBox* valid_Etat;
    QSpinBox* numEtatCourant;
    QSpinBox* etatDest;

    QPushButton* fin;
    QPushButton* next;
    QIntValidator* seuilValidator;
    QLineEdit* numSeuilMin[8];
    QLineEdit* numSeuilMax[8];

    QVBoxLayout* layoutv = new QVBoxLayout;
    QHBoxLayout* layouth1 = new QHBoxLayout;
    QHBoxLayout* layouth2 = new QHBoxLayout;
    QHBoxLayout* layouth3 = new QHBoxLayout;
    QHBoxLayout* layouth4 = new QHBoxLayout;

    QVBoxLayout* layoutv2 = new QVBoxLayout;
    QHBoxLayout* layouth5 = new QHBoxLayout;
    QHBoxLayout* layouth6 = new QHBoxLayout;

    //définition de la frame paramétrage du choix
    QWidget* fenetre_param;
    QGridLayout* form_param;
    QLabel* label_param;

    //Voisiange non arbitraire
    QFormLayout* form_rayon;
    QSpinBox* rayon;

    //définition de la frame contenant la grille de sélection du voisinage
    QTableWidget* grid;
    std::unique_ptr<ParamAlpha> paramAlpha;
    QPushButton* boutonEtat;

public:
    NouveauModele(QWidget* parent = nullptr);
public slots:
    void paramVoisinage(const QString& choix_voisinage);
    void changerVoisinage(const QString& choix_regle);
    void affGrille();
    void modifGrille(const QModelIndex& index);
    void paramRegle(const QString& choix_regle);

    void choisirEtatCourant(const QString& validEtat);
    void parametrerEtats();



};


#endif // PARAMETRAGEMODELE_H
