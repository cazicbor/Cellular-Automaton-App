#include <paramalpha.h>

void ParamAlpha::addEtats() {
	this->setWindowTitle("Configuration des états");
	this->setMinimumSize(900, 700);

	general = new QGridLayout;
	this->setLayout(general);

	valider = new QPushButton("Valider");

	for(size_t i = 0; i < 8; ++i) {
		form[i] = new QFormLayout;
		red[i] = new QSpinBox;
		green[i] = new QSpinBox;
		blue[i] = new QSpinBox;
		label[i] = new QLineEdit;
		red[i].setRange(0,255);
		green[i].setRange(0,255);
		blue[i].setRange(0,255);
		std::string formLabel = "Etat ";
		formLabel = formLabel + std::to_string(i);
		form[i].addWidget(new QLabel(formLabel.c_str()));
		form[i].addRow("Label:", label[i]);
		form[i].addRow("Rouge:", red[i]);
		form[i].addRow("Vert:", green[i]);
		form[i].addRow("Bleu:", blue[i]);
	}

	connect(valider, SIGNAL(clicked()), this, SLOT(valide()));

	general->addWidget(form[0], 0, 0, 1, 1);
	general->addWidget(form[0], 0, 1, 1, 1);
	general->addWidget(form[0], 0, 2, 1, 1);
	general->addWidget(form[0], 1, 0, 1, 1);
	general->addWidget(form[0], 1, 1, 1, 1);
	general->addWidget(form[0], 1, 2, 1, 1);
	general->addWidget(form[0], 2, 0, 1, 1);
	general->addWidget(form[0], 2, 1, 1, 1);
	general->addWidget(valider, 2, 1, 1, 1);
}

void ParamAlpha::valide() {
	EnsembleEtat& e = Automate::getInstance().getEnsemble();

	e.reset();
	for(size_t i = 0; i < 8; ++i) {
		e.ajouterEtat(i, label[i].text().toStdString(), red[i].value(), green[i].value(), blue[i].value());
	}
}
