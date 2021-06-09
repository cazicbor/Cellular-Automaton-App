#include <iostream>
#include <autosql.h>

extern EnsembleEtat& enseEtats;

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

void Database::initEnsEtat(const QString& name) const {
	QSqlQuery query(db);

	query.prepare("SELECT indice, label, r, g, b FROM Etats INNER JOIN EnsembleEtats ON Etats.ensemble = EnsembleEtats.id WHERE automate = :nom");
	query.bindValue(":nom", name);
	query.exec();

	if(!query.first())
		throw "Unable to select this object";

	EnsembleEtat& ens = EnsembleEtat::getInstance();
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
Fonction* Database::getFonction(const QString& name) const {
	QSqlQuery query(db);

	query.prepare("SELECT defaut FROM automates WHERE nom = :nom");
	query.bindValue(":nom", name);
	query.exec();

	if(!query.first())
		throw "Unable to select this object";

	Fonction* fonction = new Fonction(enseEtats.getEtat(query.value("defaut").toInt()));

	query.prepare("SELECT * FROM regles_transition WHERE id = :id");
	query.bindValue(":id", name);
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
			fonction->ajouterRegle(enseEtats.getEtat(query.value("destination").toInt()), min, max);
		} else {
			fonction->ajouterRegle(enseEtats.getEtat(query.value("destination").toInt()), min, max, query.value("courant").toInt());
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
Reseau& Database::getReseau(int idReseau) const
{
    QSqlQuery ensemble(db);
    ensemble.prepare("SELECT * FROM EnsembleEtats WHERE reseau = :id");
    ensemble.bindValue(":id", idReseau);
    ensemble.exec();

    //récuperation de l'identifiant de l'ensemble d'états lié au réseau
    int idEnsemble = ensemble.value("id").toInt();

    //récupération des états de l'ensemble
    QSqlQuery etats(db);
    etats.prepare("SELECT * FROM Etats WHERE ensemble = :id");
    etats.bindValue(":id", idEnsemble);
    etats.exec();

    //reset et remplissage du singleton de l'ensemble d'état
    enseEtats.reset();
    if(etats.first()) {
        enseEtats.ajouterEtat(etats.value("indice").toUInt(), etats.value("label").toString().toStdString(), etats.value("r").toInt(), etats.value("g").toInt(), etats.value("b").toInt());
    }
    while(etats.next()) {
        enseEtats.ajouterEtat(etats.value("indice").toUInt(), etats.value("label").toString().toStdString(), etats.value("r").toInt(), etats.value("g").toInt(), etats.value("b").toInt());
    }

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
            cellule.prepare("SELECT etat FROM Cellules WHERE (reseau = :id AND ensemble = :idE AND x = :i AND y = :j)");
            cellule.bindValue(":id", idReseau);
            cellule.bindValue(":idE", idEnsemble);
            cellule.bindValue(":i", static_cast<int>(i));
            cellule.bindValue(":j", static_cast<int>(j));
            cellule.exec();
            while(r->getReseau()[i][j].getIndEtat() != cellule.value("etat").toInt())
                r->getReseau()[i][j].incrementerEtat();
        }
    }

    return *r;
}

void Database::saveAutomaton(const Automate& a) const {
	QSqlQuery query(db);
	query.prepare("INSERT INTO automates (nom, defaut, description, auteur, annee) VALUES (:nom, :etatDefaut, :description, :auteur, :annee)");
	query.bind(":nom", a.getTitle());
	query.bind(":etatDefaut", a.getFonction().getEtatDefaut());
	query.bind(":description", a.getDescription());
	query.bind(":auteur", a.getAuteur());
	query.bind(":annee", a.getAnnee());
	query.exec();

	saveFunction(a.getTitle(), a.getFonction());
	saveVoisinage(a.getTitle(), a.getRegleVoisinage());
	stockerReseau(a.getReseauInit(), "To be determined", a.getTitle());
}

void Database::saveFunction(const QString& name, const Fonction& f) const {
	QSqlQuery query(db);
	for(auto rule: f.getRules()) {
		query.prepare("INSERT INTO regles_transition VALUES (:name, :min1, :min2, :min3, :min4, :min5, :min6, :min7, :min8, :max1, :max2, :max3, :max4, :max5, :max6, :max7, :max8, :courant, :dest)");
		query.bind(":name", name);
		query.bind(":dest", static_cast<int>(rule->getDestination().getIndice()));
		if(rule.getCourant() != -1) {
			query.bind(":courant", rule.getCourant());
		}
		else { // NULL value
			query.bind(":courant", QVariant(QVariant::Int));
		}

		if(rule.getMin(1) != -1) {
			query.bind(":min1", rule.getMin(1));
		}
		else { // NULL value
			query.bind(":min1", QVariant(QVariant::Int));
		}
		if(rule.getMin(2) != -1) {
			query.bind(":min2", rule.getMin(2));
		}
		else { // NULL value
			query.bind(":min2", QVariant(QVariant::Int));
		}
		if(rule.getMin(3) != -1) {
			query.bind(":min3", rule.getMin(3));
		}
		else { // NULL value
			query.bind(":min3", QVariant(QVariant::Int));
		}
		if(rule.getMin(4) != -1) {
			query.bind(":min4", rule.getMin(4));
		}
		else { // NULL value
			query.bind(":min4", QVariant(QVariant::Int));
		}
		if(rule.getMin(5) != -1) {
			query.bind(":min5", rule.getMin(5));
		}
		else { // NULL value
			query.bind(":min5", QVariant(QVariant::Int));
		}
		if(rule.getMin(6) != -1) {
			query.bind(":min6", rule.getMin(6));
		}
		else { // NULL value
			query.bind(":min6", QVariant(QVariant::Int));
		}
		if(rule.getMin(7) != -1) {
			query.bind(":min7", rule.getMin(7));
		}
		else { // NULL value
			query.bind(":min7", QVariant(QVariant::Int));
		}
		if(rule.getMin(8) != -1) {
			query.bind(":min8", rule.getMin(8));
		}
		else { // NULL value
			query.bind(":min8", QVariant(QVariant::Int));
		}

		if(rule.getMax(1) != -1) {
			query.bind(":max1", rule.getMax(1));
		}
		else { // NULL value
			query.bind(":max1", QVariant(QVariant::Int));
		}
		if(rule.getMax(2) != -1) {
			query.bind(":max2", rule.getMax(2));
		}
		else { // NULL value
			query.bind(":max2", QVariant(QVariant::Int));
		}
		if(rule.getMax(3) != -1) {
			query.bind(":max3", rule.getMax(3));
		}
		else { // NULL value
			query.bind(":max3", QVariant(QVariant::Int));
		}
		if(rule.getMax(4) != -1) {
			query.bind(":max4", rule.getMax(4));
		}
		else { // NULL value
			query.bind(":max4", QVariant(QVariant::Int));
		}
		if(rule.getMax(5) != -1) {
			query.bind(":max5", rule.getMax(5));
		}
		else { // NULL value
			query.bind(":max5", QVariant(QVariant::Int));
		}
		if(rule.getMax(6) != -1) {
			query.bind(":max6", rule.getMax(6));
		}
		else { // NULL value
			query.bind(":max6", QVariant(QVariant::Int));
		}
		if(rule.getMax(7) != -1) {
			query.bind(":max7", rule.getMax(7));
		}
		else { // NULL value
			query.bind(":max7", QVariant(QVariant::Int));
		}
		if(rule.getMax(8) != -1) {
			query.bind(":max8", rule.getMax(8));
		}
		else { // NULL value
			query.bind(":max8", QVariant(QVariant::Int));
		}

		query.exec();
	}
}

void Database::saveVoisinage(const QString& name, const RegleVoisinage& r) const {
	QSqlQuery query(db);
	int type = r.getType();

	if(type == 1 || type == 2) { //Von Neumann OR Moore (same structure)
		query.prepare("INSERT INTO regles_voisinage (id, type, rayon) VALUES (:nom, :type, :rayon)");
		query.bind(":nom", name);
		query.bind(":type", type);
		query.bind(":rayon", r.getr());

		query.exec();
	}
	else if(type == 3) { //Arbitrary
		throw "Unimplemented!";
	}
	else {
		throw "Unknown type!";
	}
}

///Cette fonction permet de stocker un réseau dans la BDD
///@param reseau est le réseau à stocker
///@param nomReseau est le nom du réseau à stocker
///@param nomAutomate est le nom de l'automate en cours
void Database::stockerReseau(Reseau& reseau, QString nomReseau, QString nomAutomate) const
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

    //On passe à la création du tuple de l'ensemble d'état :
    //les tuples de Cellules prennent une clé étrangère d'EnsembleEtats (car elle appartient à la clé d'Etats) !
    //Il nous faut donc : id, automate --> on a la clé étrangère vers automate (nomAutomate), il faut créer l'id

    //Création de l'id du nouvel ensemble d'états
    query.prepare("SELECT COUNT(*) FROM EnsembleEtats");
    query.exec();
    int idEns = query.value(0).toInt() + 1;

    //Insertion du tuple dans EnsembleEtats
    query.prepare("INSERT INTO EnsembleEtats VALUES (:id, :automate)");
    query.bindValue(":id", idEns);
    query.bindValue(":automate", nomAutomate);
    query.exec();

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

    //On termine avec les Cellules.
    //Il nous faut : reseau (idReseau), ensemble (idEns), etat (indice de la cellule), x, y
    for(int i = 0 ; i < reseau.getHauteur() ; i++)
    {
        for(int j = 0 ; j < reseau.getLargeur() ; j++)
        {
            query.prepare("INSERT INTO Cellules VALUES (:reseau, :ensemble, :etat, :x, :y)");
            query.bindValue(":reseau", idReseau);
            query.bindValue(":ensemble", idEns);
            query.bindValue(":etat", reseau.getReseau()[i][j].getIndEtat());
            query.bindValue(":x", i);
            query.bindValue(":x", j);
            query.exec();
        }
    }
}

