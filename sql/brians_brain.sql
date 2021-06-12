INSERT INTO automates VALUES (
	"Brian s brain",
	2,
	"Comparable à un cerveau, dont les cellules seraient des neurones qui peuvent être dans trois états.",
	"Brian Silverman",
	1996
);

INSERT INTO EnsembleEtats VALUES(
	1,
	"Brian s brain"
);

-- 3 états : on, dying and off --> vivant (blanc), mourant (gris), mort (noir)

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

-- utilise un voisinage de Moore

INSERT INTO regles_voisinage VALUES(
	"Brian s brain",
	2,
	1
);

-- règles transition : 

-- cellule devient vivante si elle est morte et a 2 voisins vivants

INSERT INTO regles_transition VALUES(
	"Brian s brain",
	2, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	2, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	2, 
	0
);

-- cellule vivante devient mourante

INSERT INTO regles_transition VALUES(
	"Brian s brain",
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	0, 
	1
);

-- cellule mourante devient morte

INSERT INTO regles_transition VALUES(
	"Brian s brain",
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	1, 
	2
);

-- Grille de test

INSERT INTO reseaux VALUES(
	0,  
	"Grille 5*5 - Brian s Brain", 
	5, 
	5,
	"Brian s brain"
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	0,
	0
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	0,
	1
);

INSERT INTO Cellules VALUES(
	0, 
	0,
	0,
	2
);

INSERT INTO Cellules VALUES(
	0, 
	0,
	0,
	3
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	0,
	4
);

INSERT INTO Cellules VALUES(
	0, 
	0,
	1,
	0
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	1,
	1
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	1,
	2
);

INSERT INTO Cellules VALUES(
	0, 
	0,
	1,
	3
);

INSERT INTO Cellules VALUES(
	0, 
	0,
	1,
	4
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	2,
	0
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	2,
	1
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	2,
	2
);

INSERT INTO Cellules VALUES(
	0, 
	0,
	2,
	3
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	2,
	4
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	3,
	0
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	3,
	1
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	3,
	2
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	3,
	3
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	3,
	4
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	4,
	0
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	4,
	1
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	4,
	2
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	4,
	3
);

INSERT INTO Cellules VALUES(
	0, 
	2,
	4,
	4
);

-- Oscillateur

INSERT INTO reseaux VALUES(
	1,  
	"Grille oscillateur 4*4 - Brian s Brain", 
	4, 
	4,
	"Brian s brain"
);

INSERT INTO Cellules VALUES(
	1, 
	2, 
	0,
	0
);

INSERT INTO Cellules VALUES(
	1, 
	2, 
	0,
	1
);

INSERT INTO Cellules VALUES(
	1, 
	2, 
	0,
	2
);

INSERT INTO Cellules VALUES(
	1, 
	2, 
	0,
	3
);

INSERT INTO Cellules VALUES(
	1, 
	2, 
	1,
	0
);

INSERT INTO Cellules VALUES(
	1, 
	0, 
	1,
	1
);

INSERT INTO Cellules VALUES(
	1,  
	0, 
	1,
	2
);

INSERT INTO Cellules VALUES(
	1,  
	2, 
	1,
	3
);

INSERT INTO Cellules VALUES(
	1,  
	2, 
	2,
	0
);

INSERT INTO Cellules VALUES(
	1,  
	0, 
	2,
	1
);

INSERT INTO Cellules VALUES(
	1,  
	0, 
	2,
	2
);

INSERT INTO Cellules VALUES(
	1,  
	2, 
	2,
	3
);

INSERT INTO Cellules VALUES(
	1,  
	2, 
	3,
	0
);

INSERT INTO Cellules VALUES(
	1,  
	2, 
	3,
	1
);

INSERT INTO Cellules VALUES(
	1,  
	2, 
	3,
	2
);

INSERT INTO Cellules VALUES(
	1,  
	2, 
	3,
	3
);

-- Planeur

INSERT INTO reseaux VALUES (
	5,
	"Grille 6*4 - Brian s brain - Planeur",
	4,
	6,
	"Brian s brain"
);

INSERT INTO Cellules VALUES (
	5,
	2,
	0,
	0
);

INSERT INTO Cellules VALUES (
	5,
	2,
	0,
	1
);

INSERT INTO Cellules VALUES (
	5,
	2,
	0,
	2
);

INSERT INTO Cellules VALUES (
	5,
	2,
	0,
	3
);

INSERT INTO Cellules VALUES (
	5,
	2,
	1,
	0
);

INSERT INTO Cellules VALUES (
	5,
	2,
	1,
	1
);

INSERT INTO Cellules VALUES (
	5,
	0,
	1,
	2
);

INSERT INTO Cellules VALUES (
	5,
	1,
	1,
	3
);

INSERT INTO Cellules VALUES (
	5,
	2,
	2,
	0
);

INSERT INTO Cellules VALUES (
	5,
	0,
	2,
	1
);

INSERT INTO Cellules VALUES (
	5,
	1,
	2,
	2
);

INSERT INTO Cellules VALUES (
	5,
	2,
	2,
	3
);

INSERT INTO Cellules VALUES (
	5,
	2,
	3,
	0
);

INSERT INTO Cellules VALUES (
	5,
	0,
	3,
	1
);

INSERT INTO Cellules VALUES (
	5,
	1,
	3,
	2
);

INSERT INTO Cellules VALUES (
	5,
	2,
	3,
	3
);

INSERT INTO Cellules VALUES (
	5,
	2,
	4,
	0
);

INSERT INTO Cellules VALUES (
	5,
	2,
	4,
	1
);

INSERT INTO Cellules VALUES (
	5,
	0,
	4,
	2
);

INSERT INTO Cellules VALUES (
	5,
	1,
	4,
	3
);

INSERT INTO Cellules VALUES (
	5,
	2,
	5,
	0
);

INSERT INTO Cellules VALUES (
	5,
	2,
	5,
	1
);

INSERT INTO Cellules VALUES (
	5,
	2,
	5,
	2
);

INSERT INTO Cellules VALUES (
	5,
	2,
	5,
	3
);
