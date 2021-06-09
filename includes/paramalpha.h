#ifndef _PARAMALPHA_H
#define _PARAMALPHA_H

class ParamAlpha: public QObject {
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

		QPushButton valider("Valider", this);
	public slots:
		void addEtats(const int nbEtats);
		void valide();
};

#endif
