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
#include <Automate.h>

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
	public slots:
		void addEtats(const int nbEtats);
		void valide();
};

#endif
