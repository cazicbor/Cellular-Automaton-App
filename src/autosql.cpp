#include <iostream>
#include <autosql.h>

std::unique_ptr<Database> Database::instance = nullptr;

Database::Database(std::string path): db(QSqlDatabase::addDatabase("QSQLITE")) {
	db.setDatabaseName(path.c_str());
	if (!db.open()) {
		throw "Unable to open database";
	}

	db.exec("CREATE TABLE IF NOT EXISTS automates (nom VARCHAR(30) PRIMARY KEY, defaut INTEGER NOT NULL, description TEXT NOT NULL, auteur VARCHAR(30), annee DATE)");

	db.exec("CREATE TABLE IF NOT EXISTS regles_transition (id VARCHAR(30) NOT NULL, min1 INTEGER, min2 INTEGER, min3 INTEGER, min4 INTEGER, min5 INTEGER, min6 INTEGER, min7 INTEGER, min8 INTEGER, max1 INTEGER, max2 INTEGER, max3 INTEGER, max4 INTEGER, max5 INTEGER, max6 INTEGER, max7 INTEGER, max8 INTEGER, courant INTEGER, destination INTEGER NOT NULL, FOREIGN KEY('id') REFERENCES 'automates'('nom'))");

	db.exec("CREATE TABLE IF NOT EXISTS regles_voisinage (id VARCHAR(30) PRIMARY KEY, type INTEGER NOT NULL, rayon INTEGER, FOREIGN KEY('id') REFERENCES 'automates'('nom'))");

	db.exec("CREATE TABLE IF NOT EXISTS coord_voisinage (id VARCHAR(30) NOT NULL, x INTEGER NOT NULL, y INTEGER NOT NULL,FOREIGN KEY('id') REFERENCES 'automates'('nom'))");

	db.exec("CREATE TABLE IF NOT EXISTS reseaux (id INTEGER PRIMARY KEY, nom VARCHAR(30) NOT NULL, h INTEGER NOT NULL, 	l INTEGER NOT NULL, automate VARCHAR(30) NOT NULL, FOREIGN KEY('automate') REFERENCES 'automates'('nom'))");

    db.exec("CREATE TABLE IF NOT EXISTS EnsembleEtats (id INTEGER PRIMARY KEY, automate VARCHAR(30) NOT NULL, UNIQUE(automate), FOREIGN KEY('automate') REFERENCES 'automates'('nom'))");

    db.exec("CREATE TABLE IF NOT EXISTS Etats (ensemble INTEGER NOT NULL, indice INTEGER NOT NULL, label VARCHAR NOT NULL, r INTEGER NOT NULL, g INTEGER NOT NULL, b INTEGER NOT NULL, CHECK(indice>=0), CHECK(r>=0), CHECK(r<=255), CHECK(g>=0), CHECK(g<=255), CHECK(b>=0), CHECK(b<=255), PRIMARY KEY (ensemble, indice), FOREIGN KEY(ensemble') REFERENCES 'EnsembleEtats'('id'))");

    db.exec("CREATE TABLE IF NOT EXISTS Cellules (reseau INTEGER NOT NULL, ensemble INTEGER NOT NULL, etat INTEGER NOT NULL, x INTEGER NOT NULL, y INTEGER NOT NULL, FOREIGN KEY('reseau') REFERENCES 'reseaux'('id'))");

}

std::vector<QString> Database::getAutomates() const {
	QSqlQuery query = db.exec("SELECT nom FROM automates");
	std::vector<QString> names;
	if(query.first()) {
		names.push_back(query.value("nom").toString());
	}
	while(query.next()) {
		names.push_back(query.value("nom").toString());
	}

	return names;
}

void Database::initEnsEtat(Automate& a) const {
	QSqlQuery query(db);

	query.prepare("SELECT indice, label, r, g, b FROM Etats INNER JOIN EnsembleEtats ON Etats.ensemble = EnsembleEtats.id WHERE automate = :nom");
	query.bindValue(":nom", a.getTitle().c_str());
	query.exec();

	if(!query.first())
		throw "Unable to select this object";

	EnsembleEtat& ens = a.getEnsemble();
	ens.reset();

	do {
		unsigned int ind = static_cast<unsigned int>(query.value("indice").toInt());
		int r = query.value("r").toInt();
		int g = query.value("g").toInt();
		int b = query.value("b").toInt();
		std::string label = query.value("label").toString().toStdString();

		ens.ajouterEtat(ind, label, r, g, b);
	} while(query.next());
}

/// Retourne la fonction de transition d'un automate par son nom
///
/// Une règle prend en compte l'état courant seulement s'il est défini à non nul dans la BDD
Fonction* Database::getFonction(Automate& a) const {
	QSqlQuery query(db);

	query.prepare("SELECT defaut FROM automates WHERE nom = :nom");
	query.bindValue(":nom", a.getTitle().c_str());
	query.exec();

	if(!query.first())
		throw "Unable to select this object";

	Fonction* fonction = new Fonction(a.getEnsemble().getEtat(query.value("defaut").toInt()));

	query.prepare("SELECT * FROM regles_transition WHERE id = :id");
	query.bindValue(":id", a.getTitle().c_str());
	query.exec();

	if(!query.first())
		throw "No rule defined for this object";

	do {
		int min[8] = {-1};
		int max[8] = {-1};

		if(!query.isNull("min1")) {
			min[0] = query.value("min1").toInt();
		}
		if(!query.isNull("min2")) {
			min[1] = query.value("min2").toInt();
		}
		if(!query.isNull("min3")) {
			min[2] = query.value("min3").toInt();
		}
		if(!query.isNull("min4")) {
			min[3] = query.value("min4").toInt();
		}
		if(!query.isNull("min5")) {
			min[4] = query.value("min5").toInt();
		}
		if(!query.isNull("min6")) {
			min[5] = query.value("min6").toInt();
		}
		if(!query.isNull("min7")) {
			min[6] = query.value("min7").toInt();
		}
		if(!query.isNull("min8")) {
			min[7] = query.value("min8").toInt();
		}
		if(!query.isNull("max1")) {
			max[0] = query.value("max1").toInt();
		}
		if(!query.isNull("max2")) {
			max[1] = query.value("max2").toInt();
		}
		if(!query.isNull("max3")) {
			max[2] = query.value("max3").toInt();
		}
		if(!query.isNull("max4")) {
			max[3] = query.value("max4").toInt();
		}
		if(!query.isNull("max5")) {
			max[4] = query.value("max5").toInt();
		}
		if(!query.isNull("max6")) {
			max[5] = query.value("max6").toInt();
		}
		if(!query.isNull("max7")) {
			max[6] = query.value("max7").toInt();
		}
		if(!query.isNull("max8")) {
			max[7] = query.value("max8").toInt();
		}

		if(query.isNull("courant")) { // on ne prend pas en compte l'état courant
			fonction->ajouterRegle(a.getEnsemble().getEtat(query.value("destination").toInt()), min, max);
		} else {
			fonction->ajouterRegle(a.getEnsemble().getEtat(query.value("destination").toInt()), min, max, query.value("courant").toInt());
		}
	} while (query.next());

	return fonction;
}

/// Dans la base de donnée:
///
/// - type = 1 => von Neumann
/// - type = 2 => Moore
/// - type = 3 => arbitraire
RegleVoisinage* Database::getRegleVoisinage(const QString& name) const {
	QSqlQuery query(db);

	query.prepare("SELECT type, rayon FROM regles_voisinage WHERE id = :id");
	query.bindValue(":id", name);
	query.exec();

	if(!query.first())
		throw "Unable to select this object";

	int type = query.value("type").toInt();

	if(type == 1) {
		if(query.isNull("rayon"))
			throw "Error: r can't be undefined here";

		RegleVoisinageNeumann *regle = new RegleVoisinageNeumann;
		regle->setr(query.value("rayon").toInt());

		return regle;
	} else if(type == 2) {
		if(query.isNull("rayon"))
			throw "Error: r can't be undefined here";

		RegleVoisinageMoore *regle = new RegleVoisinageMoore;
		regle->setr(query.value("rayon").toInt());

		return regle;
	} else if(type != 3) // n'existe pas
		throw "Unknown type of rule";

	query.prepare("SELECT x, y FROM coord_voisinage WHERE id = :id");
	query.bindValue(":id", name);
	query.exec();

	if(!query.first())
		throw "There must be at least one coord in this rule";

	RegleVoisinageArbitraire *regle = new RegleVoisinageArbitraire;

	do {
		/// @todo voisinage arbitraire
		///
		/// dans l'attente de la possibilité de le faire
	} while(query.next());

	return regle;
}

/// Retourne un descriptif des réseaux ("id", "nom", "id", "nom", etc.) liés à un automate
std::vector<QString> Database::getListeReseaux(const QString& name) const
{
    QSqlQuery query(db);

    query.prepare("SELECT id, nom FROM reseaux WHERE nom = ':nom'");
    query.bindValue(":nom", name);
    query.exec();

    std::vector<QString> names;
    if(query.first()) {
        names.push_back(query.value("id").toString());
        names.push_back(query.value("nom").toString());
    }
    while(query.next()) {
        names.push_back(query.value("id").toString());
        names.push_back(query.value("nom").toString());
    }

    return names;
}


/// Cette fonction réinitialise le singleton EnsembleEtat avec des valeurs contenues dans la BDD, afin de retourner un réseau à partir des valeurs stockées dans la BDD.
/// @param idReseau correspond à la clé primaire du réseau dans la BDD, il est conseillé de l'avoir récupérée avec getListeReseaux() auparavant
Reseau& Database::getReseau(int idReseau) const {
    //initialisation du réseau de retour
    QSqlQuery reseau(db);
    reseau.prepare("SELECT * FROM reseaux WHERE id = :id");
    reseau.bindValue(":id", idReseau);
    reseau.exec();
    Reseau* r = new Reseau(reseau.value("h").toUInt(), reseau.value("l").toUInt());

    //remplissage du réseau
    for(size_t i = 0; i<reseau.value("h").toUInt(); i++)
    {
        for(size_t j = 0; j<reseau.value("l").toUInt(); j++)
        {
            QSqlQuery cellule(db);
            cellule.prepare("SELECT etat FROM Cellules WHERE (reseau = :id AND x = :i AND y = :j)");
            cellule.bindValue(":id", idReseau);
            cellule.bindValue(":i", static_cast<int>(i));
            cellule.bindValue(":j", static_cast<int>(j));
            cellule.exec();
            while(static_cast<int>(r->getReseau()[i][j].getIndEtat()) != cellule.value("etat").toInt())
                r->getReseau()[i][j].incrementerEtat();
        }
    }

    return *r;
}

void Database::saveAutomaton(const Automate& a) const {
	QSqlQuery query(db);
	query.prepare("INSERT INTO automates (nom, defaut, description, auteur, annee) VALUES (:nom, :etatDefaut, :description, :auteur, :annee)");
	query.bindValue(":nom", a.getTitle().c_str());
	query.bindValue(":etatDefaut", a.getFonction().getEtatDefaut().getIndice());
	query.bindValue(":description", a.getDesc().c_str());
	query.bindValue(":auteur", a.getAuthor().c_str());
	query.bindValue(":annee", a.getYear());
	query.exec();

	saveFunction(a.getTitle().c_str(), a.getFonction());
	saveVoisinage(a.getTitle().c_str(), a.getRegleVoisinage());
	stockerReseau(a.getReseauInit(), "To be determined", a.getTitle().c_str());
}

void Database::saveFunction(const QString& name, const Fonction& f) const {
	QSqlQuery query(db);
	for(auto rule: f.getRules()) {
		query.prepare("INSERT INTO regles_transition VALUES (:name, :min1, :min2, :min3, :min4, :min5, :min6, :min7, :min8, :max1, :max2, :max3, :max4, :max5, :max6, :max7, :max8, :courant, :dest)");
		query.bindValue(":name", name);
		query.bindValue(":dest", static_cast<int>(rule->getDestination().getIndice()));
		if(rule->getCourant() != -1) {
			query.bindValue(":courant", rule->getCourant());
		}
		else { // NULL value
			query.bindValue(":courant", QVariant(QVariant::Int));
		}

		if(rule->getMin(1) != -1) {
			query.bindValue(":min1", rule->getMin(1));
		}
		else { // NULL value
			query.bindValue(":min1", QVariant(QVariant::Int));
		}
		if(rule->getMin(2) != -1) {
			query.bindValue(":min2", rule->getMin(2));
		}
		else { // NULL value
			query.bindValue(":min2", QVariant(QVariant::Int));
		}
		if(rule->getMin(3) != -1) {
			query.bindValue(":min3", rule->getMin(3));
		}
		else { // NULL value
			query.bindValue(":min3", QVariant(QVariant::Int));
		}
		if(rule->getMin(4) != -1) {
			query.bindValue(":min4", rule->getMin(4));
		}
		else { // NULL value
			query.bindValue(":min4", QVariant(QVariant::Int));
		}
		if(rule->getMin(5) != -1) {
			query.bindValue(":min5", rule->getMin(5));
		}
		else { // NULL value
			query.bindValue(":min5", QVariant(QVariant::Int));
		}
		if(rule->getMin(6) != -1) {
			query.bindValue(":min6", rule->getMin(6));
		}
		else { // NULL value
			query.bindValue(":min6", QVariant(QVariant::Int));
		}
		if(rule->getMin(7) != -1) {
			query.bindValue(":min7", rule->getMin(7));
		}
		else { // NULL value
			query.bindValue(":min7", QVariant(QVariant::Int));
		}
		if(rule->getMin(8) != -1) {
			query.bindValue(":min8", rule->getMin(8));
		}
		else { // NULL value
			query.bindValue(":min8", QVariant(QVariant::Int));
		}

		if(rule->getMax(1) != -1) {
			query.bindValue(":max1", rule->getMax(1));
		}
		else { // NULL value
			query.bindValue(":max1", QVariant(QVariant::Int));
		}
		if(rule->getMax(2) != -1) {
			query.bindValue(":max2", rule->getMax(2));
		}
		else { // NULL value
			query.bindValue(":max2", QVariant(QVariant::Int));
		}
		if(rule->getMax(3) != -1) {
			query.bindValue(":max3", rule->getMax(3));
		}
		else { // NULL value
			query.bindValue(":max3", QVariant(QVariant::Int));
		}
		if(rule->getMax(4) != -1) {
			query.bindValue(":max4", rule->getMax(4));
		}
		else { // NULL value
			query.bindValue(":max4", QVariant(QVariant::Int));
		}
		if(rule->getMax(5) != -1) {
			query.bindValue(":max5", rule->getMax(5));
		}
		else { // NULL value
			query.bindValue(":max5", QVariant(QVariant::Int));
		}
		if(rule->getMax(6) != -1) {
			query.bindValue(":max6", rule->getMax(6));
		}
		else { // NULL value
			query.bindValue(":max6", QVariant(QVariant::Int));
		}
		if(rule->getMax(7) != -1) {
			query.bindValue(":max7", rule->getMax(7));
		}
		else { // NULL value
			query.bindValue(":max7", QVariant(QVariant::Int));
		}
		if(rule->getMax(8) != -1) {
			query.bindValue(":max8", rule->getMax(8));
		}
		else { // NULL value
			query.bindValue(":max8", QVariant(QVariant::Int));
		}

		query.exec();
	}
}

void Database::saveVoisinage(const QString& name, const RegleVoisinage& r) const {
	QSqlQuery query(db);
	int type = r.getType();

	if(type == 1 || type == 2) { //Von Neumann OR Moore (same structure)
		query.prepare("INSERT INTO regles_voisinage (id, type, rayon) VALUES (:nom, :type, :rayon)");
		query.bindValue(":nom", name);
		query.bindValue(":type", type);
		query.bindValue(":rayon", r.getr());

		query.exec();
	}
	else if(type == 3) { //Arbitrary
		throw "Unimplemented!";
	}
	else {
		throw "Unknown type!";
	}
}

void Database::saveEnsemble(Automate& a) const {
    //On passe à la création du tuple de l'ensemble d'état :
    //les tuples de Cellules prennent une clé étrangère d'EnsembleEtats (car elle appartient à la clé d'Etats) !
    //Il nous faut donc : id, automate --> on a la clé étrangère vers automate (nomAutomate), il faut créer l'id

    //Création de l'id du nouvel ensemble d'états
	QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM EnsembleEtats");
    query.exec();
    int idEns = query.value(0).toInt() + 1;

    //Insertion du tuple dans EnsembleEtats
    query.prepare("INSERT INTO EnsembleEtats VALUES (:id, :automate)");
    query.bindValue(":id", idEns);
    query.bindValue(":automate", a.getTitle().c_str());
    query.exec();

    EnsembleEtat& enseEtats = a.getEnsemble();

    //On passe au stockage des états de l'ensemble :
    //les tuples de Cellules prennent une clé étrangère d'Etats !
    //Il nous faut prendre de chaque état : ensemble (idEns), indice, label, r, g, b
    for(unsigned int i = 0 ; i < enseEtats.getNbEtats() ; i++)
    {
        query.prepare("INSERT INTO Etats VALUES (:ensemble, :indice, ':label', :r, :g, :b)");
        query.bindValue(":ensemble", idEns);
        query.bindValue(":indice", enseEtats.getEtat(i).getIndice());
        query.bindValue(":label", QString::fromStdString(enseEtats.getEtat(i).getLabel()));
        query.bindValue(":r", enseEtats.getEtat(i).getColor().red());
        query.bindValue(":g", enseEtats.getEtat(i).getColor().green());
        query.bindValue(":b", enseEtats.getEtat(i).getColor().blue());
        query.exec();
    }
}

///Cette fonction permet de stocker un réseau dans la BDD
///@param reseau est le réseau à stocker
///@param nomReseau est le nom du réseau à stocker
///@param nomAutomate est le nom de l'automate en cours
void Database::stockerReseau(const Reseau& reseau, const QString& nomReseau, const QString& nomAutomate) const
{
    //Tout d'abord, on a besoin de créer un tuple dans la table reseaux :
    //toutes les autres tables l'ont en clé étrangère !
    //Il nous faut donc : id, nom, h, l, automate --> tout est en paramètre ou dans reseau (avec getH, getL) sauf l'id à recréer

    //Création de l'id du nouveau réseau
    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM reseaux");
    query.exec();
    int idReseau = query.value(0).toInt() + 1;

    //Insertion du tuple dans reseaux
    query.prepare("INSERT INTO reseaux VALUES (:id, ':nom', :h, :l, ':automate')");
    query.bindValue(":id", idReseau);
    query.bindValue(":nom", nomReseau);
    query.bindValue(":h", reseau.getHauteur());
    query.bindValue(":l", reseau.getLargeur());
    query.bindValue(":automate", nomAutomate);
    query.exec();
    //On termine avec les Cellules.
    //Il nous faut : reseau (idReseau), ensemble (idEns), etat (indice de la cellule), x, y
    for(int i = 0 ; i < reseau.getHauteur() ; i++)
    {
        for(int j = 0 ; j < reseau.getLargeur() ; j++)
        {
            query.prepare("INSERT INTO Cellules VALUES (:reseau, :etat, :x, :y)");
            query.bindValue(":reseau", idReseau);
            query.bindValue(":etat", reseau.getReseau()[i][j].getIndEtat());
            query.bindValue(":x", i);
            query.bindValue(":x", j);
            query.exec();
        }
    }
}

