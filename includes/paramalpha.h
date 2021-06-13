#ifndef _PARAMALPHA_H
#define _PARAMALPHA_H

#include <QObject>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QWidget>
#include <QFormLayout>
#include <reseau_cellule_etats.h>

/// @brief Classe correspondant à la fenêtre pour paramétrer l'alphabet
///
/// Cette classe s'occupe d'afficher le bon nombre de formulaire selon le nombre de cellules souhaité et paramètre directement l'alphabet de l'automate
class ParamAlpha: public QWidget {
	Q_OBJECT
	private:
		EnsembleEtat ense;

		int nb;
		QGridLayout *general;
		QFormLayout* form[8];
		QLineEdit* label[8];
		QSpinBox* red[8];
		QSpinBox* green[8];
		QSpinBox* blue[8];

		QPushButton* valider;
	public:
		/// Construire une fenêtre de paramétrage de l'alphabet
		/// @param[in] nbEtats nombre d'états à initialiser
		ParamAlpha(const int nbEtats, const QWidget* parent);
	public slots:
		/// Valider le paramétrage de l'alphabet, a pour effet de l'initialiser dans l'automate
		void valide();
};

#endif
