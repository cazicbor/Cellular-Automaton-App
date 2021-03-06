INSERT INTO automates VALUES (
	"Game of Life",
	1,
	"Le jeu de la vie est un automate cellulaire imaginé par John Horton Conway en 1970 et qui est probablement le plus connu de tous les automates cellulaires. Malgré des règles très simples, le jeu de la vie est Turing-complet.",
	"John Horton Conway",
	1970
);

INSERT INTO EnsembleEtats VALUES(
	2,
	"Game of Life"
);

-- 2 états : vivant (blanc), mort (noir)

INSERT INTO Etats VALUES(
	2,
	0,
	"vivante",
	255,
	255,
	255
);

INSERT INTO Etats VALUES(
	2,
	1,
	"morte",
	0,
	0,
	0
);

-- utilise un voisinage de Moore de rayon 1

INSERT INTO regles_voisinage VALUES(
	"Game of Life",
	2,
	1
);

-- règles transition : 

-- cellule vivante le reste seulement si 2 à 3 cellules vivantes dans les voisins

INSERT INTO regles_transition VALUES(
	"Game of Life",
	2, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	3, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	0, 
	0
);

-- cellule morte revient à la vie si 3 voisines vivantes

INSERT INTO regles_transition VALUES(
	"Game of Life",
	3, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	3, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	-1, 
	1, 
	0
);

-- Grille de test 4 * 4 - Oscillateur

INSERT INTO reseaux VALUES(
	3,  
	"Grille 4*4 - Game of Life - Oscillateur", 
	4, 
	4,
	"Game of Life"
);

INSERT INTO Cellules VALUES(
	3, 
	1,
	0,
	0
);

INSERT INTO Cellules VALUES(
	3, 
	1,
	1,
	0
);

INSERT INTO Cellules VALUES(
	3, 
	1,
	2,
	0
);

INSERT INTO Cellules VALUES(
	3, 
	1,
	3,
	0
);

INSERT INTO Cellules VALUES(
	3, 
	0,
	0,
	1
);

INSERT INTO Cellules VALUES(
	3, 
	0,
	1,
	1
);

INSERT INTO Cellules VALUES(
	3, 
	0,
	2,
	1
);

INSERT INTO Cellules VALUES(
	3, 
	1,
	3,
	1
);

INSERT INTO Cellules VALUES(
	3, 
	1,
	0,
	2
);

INSERT INTO Cellules VALUES(
	3, 
	1,
	1,
	2
);

INSERT INTO Cellules VALUES(
	3, 
	1,
	2,
	2
);

INSERT INTO Cellules VALUES(
	3, 
	1,
	3,
	2
);

INSERT INTO Cellules VALUES(
	3, 
	1,
	0,
	3
);

INSERT INTO Cellules VALUES(
	3, 
	1,
	1,
	3
);

INSERT INTO Cellules VALUES(
	3, 
	1,
	2,
	3
);

INSERT INTO Cellules VALUES(
	3, 
	1,
	3,
	3
);

--- Exemple 2 : planeur 5*5

INSERT INTO reseaux VALUES(
	4,  
	"Grille 5*5 - Game of Life - Planeur", 
	5, 
	5,
	"Game of Life"
);

INSERT INTO Cellules VALUES(
	4, 
	0,
	0,
	0
);

INSERT INTO Cellules VALUES(
	4, 
	0,
	1,
	0
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	2,
	0
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	3,
	0
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	4,
	0
);

INSERT INTO Cellules VALUES(
	4, 
	0,
	0,
	1
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	1,
	1
);

INSERT INTO Cellules VALUES(
	4, 
	0,
	2,
	1
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	3,
	1
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	4,
	1
);

INSERT INTO Cellules VALUES(
	4, 
	0,
	0,
	2
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	1,
	2
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	2,
	2
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	3,
	2
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	4,
	2
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	0,
	3
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	1,
	3
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	2,
	3
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	3,
	3
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	4,
	3
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	0,
	4
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	1,
	4
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	2,
	4
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	3,
	4
);

INSERT INTO Cellules VALUES(
	4, 
	1,
	4,
	4
);
