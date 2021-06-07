CREATE TABLE IF NOT EXISTS automates (
	nom VARCHAR(30) PRIMARY KEY, 
	defaut INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS reseaux (
	id INTEGER PRIMARY KEY,  
	nom VARCHAR(30) NOT NULL, 
	h INTEGER NOT NULL, 
	l INTEGER NOT NULL,
	automate VARCHAR(30) NOT NULL,
	FOREIGN KEY("automate") REFERENCES "automates"("nom") 
);

CREATE TABLE IF NOT EXISTS EnsembleEtats (
	id INTEGER PRIMARY KEY, 
	automate VARCHAR(30) NOT NULL,
	UNIQUE(automate),
	FOREIGN KEY("automate") REFERENCES "automates"("nom")
);

CREATE TABLE IF NOT EXISTS Etats (
	ensemble INTEGER NOT NULL, 
	indice INTEGER NOT NULL,
	label VARCHAR NOT NULL,
	r INTEGER NOT NULL,
	g INTEGER NOT NULL,
	b INTEGER NOT NULL,
	CHECK(indice>=0),
	CHECK(r>=0),
	CHECK(r<=255),
	CHECK(g>=0),
	CHECK(g<=255),
	CHECK(b>=0),
	CHECK(b<=255),
	PRIMARY KEY (ensemble, indice)
	FOREIGN KEY("ensemble") REFERENCES "EnsembleEtats"("id")
);

CREATE TABLE IF NOT EXISTS Cellules (
	reseau INTEGER NOT NULL, 
	ensemble INTEGER NOT NULL,
	etat INTEGER NOT NULL,
	x INTEGER NOT NULL,
	y INTEGER NOT NULL,
	FOREIGN KEY("reseau") REFERENCES "reseaux"("id")
);


CREATE TABLE IF NOT EXISTS regles_transition (
	id VARCHAR(30) NOT NULL,
	min1 INTEGER, 
	min2 INTEGER, 
	min3 INTEGER, 
	min4 INTEGER, 
	min5 INTEGER, 
	min6 INTEGER, 
	min7 INTEGER, 
	min8 INTEGER, 
	max1 INTEGER, 
	max2 INTEGER, 
	max3 INTEGER, 
	max4 INTEGER, 
	max5 INTEGER, 
	max6 INTEGER, 
	max7 INTEGER, 
	max8 INTEGER, 
	courant INTEGER, 
	destination INTEGER NOT NULL,
	FOREIGN KEY("id") REFERENCES "automates"("nom") 
);



CREATE TABLE IF NOT EXISTS regles_voisinage (
	id VARCHAR(30) PRIMARY KEY, 
	type INTEGER NOT NULL, 
	rayon INTEGER,
	FOREIGN KEY("id") REFERENCES "automates"("nom") 
);


CREATE TABLE IF NOT EXISTS coord_voisinage (
	id VARCHAR(30) NOT NULL,
	x INTEGER NOT NULL, 
	y INTEGER NOT NULL,
	FOREIGN KEY("id") REFERENCES "automates"("nom") 
);
