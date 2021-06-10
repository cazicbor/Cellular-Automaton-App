#include <paramalpha.h>
#include <Automate.h>

ParamAlpha::ParamAlpha(const int nbEtats): QWidget(), nb(nbEtats) {
	this->setWindowTitle("Configuration des états");
	this->setMinimumSize(900, 700);

	general = new QGridLayout;
	this->setLayout(general);

	valider = new QPushButton("Valider");

	for(int i = 0; i < nb; ++i) {
		form[i] = new QFormLayout;
		red[i] = new QSpinBox;
		green[i] = new QSpinBox;
		blue[i] = new QSpinBox;
		label[i] = new QLineEdit;
		red[i]->setRange(0,255);
		green[i]->setRange(0,255);
		blue[i]->setRange(0,255);
		std::string formLabel = "Etat ";
		formLabel = formLabel + std::to_string(i);
		form[i]->addWidget(new QLabel(formLabel.c_str()));
		form[i]->addRow("Label:", label[i]);
		form[i]->addRow("Rouge:", red[i]);
		form[i]->addRow("Vert:", green[i]);
		form[i]->addRow("Bleu:", blue[i]);
	}

	connect(valider, SIGNAL(clicked()), this, SLOT(valide()));

	general->addLayout(form[0], 0, 0, 1, 1);
	if(nb >= 2)
		general->addLayout(form[1], 0, 1, 1, 1);
	if(nb >= 3)
		general->addLayout(form[2], 0, 2, 1, 1);
	if(nb >= 4)
		general->addLayout(form[3], 1, 0, 1, 1);
	if(nb >= 5)
		general->addLayout(form[4], 1, 1, 1, 1);
	if(nb >= 6)
		general->addLayout(form[5], 1, 2, 1, 1);
	if(nb >= 7)
		general->addLayout(form[6], 2, 0, 1, 1);
	if(nb == 8)
		general->addLayout(form[7], 2, 1, 1, 1);
	general->addWidget(valider, 2, 2, 1, 1, Qt::AlignBottom);
}

void ParamAlpha::valide() {
	EnsembleEtat& e = Automate::getInstance().getEnsemble();

	e.reset();
	for(int i = 0; i < nb; ++i) {
		e.ajouterEtat(i, label[i]->text().toStdString(), red[i]->value(), green[i]->value(), blue[i]->value());
	}
}
