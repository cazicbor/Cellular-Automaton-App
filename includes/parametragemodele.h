#ifndef PARAMETRAGEMODELE_H
#define PARAMETRAGEMODELE_H

#include <reseau_cellule_etats.h>
#include <paramalpha.h>
#include <autocell.h>

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

    QHBoxLayout* layoutvalid;

    //definition frame règle de transitions
    QWidget* fenetre_regle;
    QLabel* seuilMax;
    QLabel* seuilMin;
    QLabel* destination;
    QLabel* etatCourant;
    QLabel* etatCourant2 = nullptr;

    QComboBox* valid_Etat;
    QSpinBox* numEtatCourant = nullptr;
    QSpinBox* etatDest;

    QPushButton* fin = nullptr;
    QPushButton* next = nullptr;
    QIntValidator* seuilValidator;
    QLineEdit* numSeuilMin[8];
    QLineEdit* numSeuilMax[8];

    QVBoxLayout* layoutv = nullptr;
    QHBoxLayout* layouth1 = nullptr;
    QHBoxLayout* layouth2 = nullptr;
    QHBoxLayout* layouth3 = nullptr;
    QHBoxLayout* layouth4 = nullptr;

    QVBoxLayout* layoutv2 = nullptr;
    QHBoxLayout* layouth5 = nullptr;
    QHBoxLayout* layouth6 = nullptr;

    //définition de la frame paramétrage du choix
    QWidget* fenetre_param;
    QGridLayout* form_param;
    QLabel* label_param;

    //Voisiange non arbitraire
    QFormLayout* form_rayon = nullptr;
    QSpinBox* rayon;

    //définition de la frame contenant la grille de sélection du voisinage
    QTableWidget* grid = nullptr;
    std::unique_ptr<ParamAlpha> paramAlpha;
    QPushButton* boutonEtat;

    AutoCell* nvAutocell = nullptr;

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

    void addRegle();

    void validerParametrage();



};


#endif // PARAMETRAGEMODELE_H
