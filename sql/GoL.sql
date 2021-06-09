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

-- 3 états : on, dying and off --> vivant (blanc), mourant (gris), mort (noir)

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
	NULL, 
	NULL, 
	NULL, 
	NULL, 
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
	0, 
	0
);

-- cellule morte revient à la vie si 3 voisines vivantes

INSERT INTO regles_transition VALUES(
	"Game of Life",
	3, 
	NULL, 
	NULL, 
	NULL, 
	NULL, 
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
	1, 
	0
);

-- Grille de test

INSERT INTO reseaux VALUES(
	1,  
	"Grille 3*3 - Game of Life", 
	3, 
	3,
	"Game of Life"
);

INSERT INTO Cellules VALUES(
	1, 
	2,
	0,
	0,
	0
);

INSERT INTO Cellules VALUES(
	1, 
	2,
	0,
	1,
	0
);

INSERT INTO Cellules VALUES(
	1, 
	2,
	0,
	2,
	0
);

INSERT INTO Cellules VALUES(
	1, 
	2,
	1,
	0,
	1
);

INSERT INTO Cellules VALUES(
	1, 
	2,
	1,
	1,
	1
);

INSERT INTO Cellules VALUES(
	1, 
	2,
	1,
	2,
	1
);

INSERT INTO Cellules VALUES(
	1, 
	2,
	0,
	0,
	2
);

INSERT INTO Cellules VALUES(
	1, 
	2,
	0,
	1,
	2
);

INSERT INTO Cellules VALUES(
	1, 
	2,
	0,
	2,
	2
);
