INSERT INTO automates VALUES (
	"Brian's brain",
	500
);

INSERT INTO EnsembleEtats VALUES(
	1,
	"Brian's brain"
);

//3 états : on, dying and off --> vivant (blanc), mourant (gris), mort (noir)

INSERT INTO Etats VALUES(
	1,
	0,
	"vivant",
	255,
	255,
	255
);

INSERT INTO Etats VALUES(
	1,
	1,
	"mourant",
	127,
	127,
	127
);

INSERT INTO Etats VALUES(
	1,
	2,
	"mort",
	0,
	0,
	0
);

//utilise un voisinage de Moore

INSERT INTO regles_voisinage VALUES(
	"Brian's brain",
	2,
	1
);

//règles transition : 

//	cellule devient vivante si elle est morte et a 2 voisins vivants

INSERT INTO regles_transition VALUES(
	"Brian's brain",
	2, 
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
	2, 
	0
);

//	cellule vivante devient mourante

INSERT INTO regles_transition VALUES(
	"Brian's brain",
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
	NULL, 
	0, 
	1
);

//	cellule mourante devient morte

INSERT INTO regles_transition VALUES(
	"Brian's brain",
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
	NULL, 
	1, 
	2
);

//Grille de test

INSERT INTO reseaux VALUES(
	0,  
	"Grille 5*5 - Brian's Brain", 
	5, 
	5,
	"Brian's brain"
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	2,
	0,
	0
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	2,
	0,
	1
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	0,
	0,
	2
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	0,
	0,
	3
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	2,
	0,
	4
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	0,
	1,
	0
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	2,
	1,
	1
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	2,
	1,
	2
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	0,
	1,
	3
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	0,
	1,
	4
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	2,
	2,
	0
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	2,
	2,
	1
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	2,
	2,
	2
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	0,
	2,
	3
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	2,
	2,
	4
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	2,
	4,
	0
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	2,
	4,
	1
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	2,
	4,
	2
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	2,
	4,
	3
);

INSERT INTO Cellules VALUES(
	0, 
	1,
	2,
	4,
	4
);
