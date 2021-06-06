#include <iostream>
#include <autosql.h>

extern EnsembleEtat& enseEtats;

Database::Database(std::string path): db(QSqlDatabase::addDatabase("QSQLITE")) {
	db.setDatabaseName(path.c_str());
	if (!db.open()) {
		throw "Unable to open database";
	}

	db.exec("CREATE TABLE IF NOT EXISTS automates (nom VARCHAR(30) PRIMARY KEY, defaut INTEGER NOT NULL)");
	db.exec("CREATE TABLE IF NOT EXISTS regles_transition (id VARCHAR(30) REFERENCES automate(nom) NOT NULL, min1 INTEGER, min2 INTEGER, min3 INTEGER, min4 INTEGER, min5 INTEGER, min6 INTEGER, min7 INTEGER, min8 INTEGER, max1 INTEGER, max2 INTEGER, max3 INTEGER, max4 INTEGER, max5 INTEGER, max6 INTEGER, max7 INTEGER, max8 INTEGER, courant INTEGER, destination INTEGER NOT NULL)");
	db.exec("CREATE TABLE IF NOT EXISTS regles_voisinage (id VARCHAR(30) PRIMARY KEY REFERENCES automates(nom), type INTEGER NOT NULL, rayon INTEGER)");
	db.exec("CREATE TABLE IF NOT EXISTS coord_voisinage (id VARCHAR(30) REFERENCES automates(nom) NOT NULL, x INTEGER NOT NULL, y INTEGER NOT NULL)");
	db.exec("CREATE TABLE IF NOT EXISTS reseaux (id INTEGER PRIMARY KEY, nom VARCHAR(30) NOT NULL, h INTEGER NOT NULL, l INTEGER NOT NULL, automate VARCHAR(30) REFERENCES automates(nom) NOT NULL)");
    db.exec("CREATE TABLE IF NOT EXISTS EnsembleEtats (id INTEGER PRIMARY KEY, reseau INTEGER REFERENCES reseau(id) NOT NULL,UNIQUE(reseau))");
    db.exec("CREATE TABLE IF NOT EXISTS Etats (ensemble INTEGER REFERENCES EnsembleEtats(id) NOT NULL, indice INTEGER NOT NULL, label VARCHAR NOT NULL, r INTEGER NOT NULL, g INTEGER NOT NULL, b INTEGER NOT NULL, CHECK(indice>=0), CHECK(r>=0), CHECK(r<=255), CHECK(g>=0), CHECK(g<=255), CHECK(b>=0), CHECK(b<=255), PRIMARY KEY (ensemble, indice))");
    db.exec("CREATE TABLE IF NOT EXISTS Cellules (reseau INTEGER REFERENCES reseau(id) NOT NULL,  ensemble INTEGER REFERENCES EnsembleEtats(id) NOT NULL, etat INTEGER REFERENCES Etats(indice) NOT NULL, x INTEGER NOT NULL, y INTEGER NOT NULL);");
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
		int min[8] = {0};
		int max[8] = {0};

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

		RegleVoisinage *regle = new RegleVoisinageNeumann;
		regle->setNbVoisins(query.value("rayon").toInt());

		return regle;
	} else if(type == 2) {
		if(query.isNull("rayon"))
			throw "Error: r can't be undefined here";

		RegleVoisinage *regle = new RegleVoisinageMoore;
		regle->setNbVoisins(query.value("rayon").toInt());

		return regle;
	} else if(type != 3) // n'existe pas
		throw "Unknown type of rule";

	query.prepare("SELECT x, y FROM coord_voisinage WHERE id = :id");
	query.bindValue(":id", name);
	query.exec();

	if(!query.first())
		throw "There must be at least one coord in this rule";

	RegleVoisinage *regle = new RegleVoisinage;

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
            cellule.bindValue(":i", i);
            cellule.bindValue(":j", j);
            cellule.exec();
            while(r->getReseau()[i][j].getIndEtat() != cellule.value("etat").toInt())
                r->getReseau()[i][j].incrementerEtat();
        }
    }

    return *r;
}

