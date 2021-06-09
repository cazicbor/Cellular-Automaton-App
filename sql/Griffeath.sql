INSERT INTO automates VALUES (
	"Griffeath",
	0,
	"",
	"David Griffeath",
	1970
);

INSERT INTO EnsembleEtats VALUES(
	3,
	"Griffeath"
);

-- 4 états jaune, orange clair, orange foncé, rouge

INSERT INTO Etats VALUES(
	3,
	0,
	"Jaune",
	255,
	255,
	0
);

INSERT INTO Etats VALUES(
	3,
	1,
	"Orange clair",
	255,
	165,
	0
);

INSERT INTO Etats VALUES(
	3,
	2,
	"Orange foncé",
	255,
	69,
	0
);

INSERT INTO Etats VALUES(
	3,
	3,
	"Rouge",
	255,
	0,
	0
);

-- utilise un voisinage de Von Neumann de rayon 2 (pas trouvé un voisinage universel dans la littérature)

INSERT INTO regles_voisinage VALUES(
	"Griffeath",
	1,
	2
);

-- règles transition : 

-- cellule jaune le reste: si 2- voisins orange clair

INSERT INTO regles_transition VALUES(
	"Griffeath",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	2,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	0,
	0
);

-- cellule jaune -> orange clair: si 3+ voisins orange clair

INSERT INTO regles_transition VALUES(
	"Griffeath",
	NULL,
	3,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	0,
	1
);

-- cellule orange clair le reste: si 2- voisins orange foncé

INSERT INTO regles_transition VALUES(
	"Griffeath",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	2,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	1,
	1
);

-- cellule orange clair -> orange foncé: si 3+ voisins orange foncé

INSERT INTO regles_transition VALUES(
	"Griffeath",
	NULL,
	NULL,
	3,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	1,
	2
);

-- cellule orange foncé le reste: si 2- voisins rouge

INSERT INTO regles_transition VALUES(
	"Griffeath",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	2,
	NULL,
	NULL,
	NULL,
	NULL,
	2,
	2
);

-- cellule orange foncé -> rouge: si 3+ voisins rouge

INSERT INTO regles_transition VALUES(
	"Griffeath",
	NULL,
	NULL,
	NULL,
	3,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	2,
	3
);

-- cellule rouge le reste: si 2- voisins jaune

INSERT INTO regles_transition VALUES(
	"Griffeath",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	2,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	3,
	3
);

-- cellule rouge -> jaune: si 3+ voisins jaune

INSERT INTO regles_transition VALUES(
	"Griffeath",
	3,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	3,
	0
);

-- Grille de test

INSERT INTO reseaux VALUES(
	2,
	"Grille 5*5 - Griffeath",
	5,
	5,
	"Griffeath"
);

INSERT INTO Cellules VALUES(
	2,
	0,
	0,
	0
);

INSERT INTO Cellules VALUES(
	2,
	2,
	1,
	0
);

INSERT INTO Cellules VALUES(
	2,
	1,
	2,
	0
);

INSERT INTO Cellules VALUES(
	2,
	1,
	3,
	0
);

INSERT INTO Cellules VALUES(
	2,
	0,
	4,
	0
);

INSERT INTO Cellules VALUES(
	2,
	2,
	0,
	1
);

INSERT INTO Cellules VALUES(
	2,
	3,
	1,
	1
);

INSERT INTO Cellules VALUES(
	2,
	1,
	2,
	1
);

INSERT INTO Cellules VALUES(
	2,
	3,
	3,
	1
);

INSERT INTO Cellules VALUES(
	2,
	2,
	4,
	1
);

INSERT INTO Cellules VALUES(
	2,
	2,
	0,
	2
);

INSERT INTO Cellules VALUES(
	2,
	1,
	1,
	2
);

INSERT INTO Cellules VALUES(
	2,
	1,
	2,
	2
);

INSERT INTO Cellules VALUES(
	2,
	2,
	3,
	2
);

INSERT INTO Cellules VALUES(
	2,
	2,
	4,
	2
);

INSERT INTO Cellules VALUES(
	2,
	3,
	0,
	3
);

INSERT INTO Cellules VALUES(
	2,
	0,
	1,
	3
);

INSERT INTO Cellules VALUES(
	2,
	1,
	2,
	3
);

INSERT INTO Cellules VALUES(
	2,
	1,
	3,
	3
);

INSERT INTO Cellules VALUES(
	2,
	3,
	4,
	3
);

INSERT INTO Cellules VALUES(
	2,
	0,
	0,
	4
);

INSERT INTO Cellules VALUES(
	2,
	1,
	1,
	4
);

INSERT INTO Cellules VALUES(
	2,
	0,
	2,
	4
);

INSERT INTO Cellules VALUES(
	2,
	2,
	3,
	4
);

INSERT INTO Cellules VALUES(
	2,
	3,
	3,
	4
);
