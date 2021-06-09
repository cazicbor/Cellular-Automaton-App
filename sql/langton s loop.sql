INSERT INTO automates VALUES (
	"Langton s loop",
	500,
	"Des cellules qui se répandent autour d'une boucle et le long d'un bras.",
	"Christopher Langton",
	1984
);

INSERT INTO EnsembleEtats VALUES(
	4,
	"Langton s loop"
);

-- 8 états : 
    -- Black : vide
    -- Blue : conducteur
    -- Red : limiteur du gène
    -- Green : générateur de ramifications
    -- Yellow : finisseur d'une boucle
    -- Pink : délieur du parent
    -- White : guide du germage
    -- Cyan : gardien d'information  

INSERT INTO Etats VALUES(
	4, 0,
	"vide",
	0, 0, 0
);

INSERT INTO Etats VALUES(
	4, 1,
	"conducteur",
	0, 0, 255
);

INSERT INTO Etats VALUES(
	4, 2,
	"limiteur",
	255, 0, 0
);

INSERT INTO Etats VALUES(
	4, 3,
	"generateur",
	0, 128, 0
);

INSERT INTO Etats VALUES(
	4, 4,
	"finisseur",
	255, 255, 0
);

INSERT INTO Etats VALUES(
	4, 5,
	"delieur",
	255, 192, 203
);

INSERT INTO Etats VALUES(
	4, 6,
	"guide",
	255, 255, 255
);

INSERT INTO Etats VALUES(
	4, 7,
	"gardien",
	0, 255, 255
);

-- utilise un voisinage de Von Neumann de rayon 1

INSERT INTO regles_voisinage VALUES(
	"Langton s loop",
	1,
	1
);

-- 219 règles de transition, 123456 signifie :
    -- si la cellule est dans l'état 1
    -- et que ses voisins sont dans les états 2,3,4 et 5
    -- alors la cellule passe dans l'état 6

-- 000000

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	4, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	4, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
	0, 0
);

-- 000012

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	3, 1, NULL, NULL, NULL, NULL, NULL, NULL,
	3, 1, NULL, NULL, NULL, NULL, NULL, NULL, 
	0, 2
);

-- 000020

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	3, NULL, 1, NULL, NULL, NULL, NULL, NULL,
	3, NULL, 1, NULL, NULL, NULL, NULL, NULL, 
	0, 0
);

-- 000030

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	3, NULL, NULL, 1, NULL, NULL, NULL, NULL,
	3, NULL, NULL, 1, NULL, NULL, NULL, NULL, 
	0, 0
);

-- 000050

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	3, NULL, NULL, NULL, NULL, 1, NULL, NULL,
	3, NULL, NULL, NULL, NULL, 1, NULL, NULL, 
	0, 0
);

-- 000063

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	3, NULL, NULL, NULL, NULL, NULL, 1, NULL,
	3, NULL, NULL, NULL, NULL, NULL, 1, NULL, 
	0, 3
);

-- 000071

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	3, NULL, NULL, NULL, NULL, NULL, NULL, 1,
	3, NULL, NULL, NULL, NULL, NULL, NULL, 1, 
	0, 1
);

-- 000112

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, 2, NULL, NULL, NULL, NULL, NULL, NULL,
	2, 2, NULL, NULL, NULL, NULL, NULL, NULL, 
	0, 2
);

-- 000122

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, 1, 1, NULL, NULL, NULL, NULL, NULL,
	2, 1, 1, NULL, NULL, NULL, NULL, NULL, 
	0, 2
);

-- 000132

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, 1, NULL, 1, NULL, NULL, NULL, NULL,
	2, 1, NULL, 1, NULL, NULL, NULL, NULL, 
	0, 2
);

-- 000212

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, 1, 1, NULL, NULL, NULL, NULL, NULL,
	2, 1, 1, NULL, NULL, NULL, NULL, NULL, 
	0, 2
);

-- 000220

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 2, NULL, NULL, NULL, NULL, NULL,
	2, NULL, 2, NULL, NULL, NULL, NULL, NULL, 
	0, 0
);

-- 000230

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, 1, NULL, NULL, NULL, NULL,
	2, NULL, 1, 1, NULL, NULL, NULL, NULL, 
	0, 0
);

-- 000262

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, NULL, NULL, NULL, 1, NULL,
	2, NULL, 1, NULL, NULL, NULL, 1, NULL, 
	0, 2
);

-- 000272

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, NULL, NULL, NULL, NULL, 1,
	2, NULL, 1, NULL, NULL, NULL, NULL, 1, 
	0, 2
);

-- 000320

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, 1, NULL, NULL, NULL, NULL,
	2, NULL, 1, 1, NULL, NULL, NULL, NULL, 
	0, 0
);

-- 000525

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, NULL, NULL, 1, NULL, NULL,
	2, NULL, 1, NULL, NULL, 1, NULL, NULL, 
	0, 5
);

-- 000622

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, NULL, NULL, NULL, 1, NULL,
	2, NULL, 1, NULL, NULL, NULL, 1, NULL, 
	0, 2
);

-- 000722

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, NULL, NULL, NULL, NULL, 1,
	2, NULL, 1, NULL, NULL, NULL, NULL, 1, 
	0, 2
);

-- 001022

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, 1, 1, NULL, NULL, NULL, NULL, NULL,
	2, 1, 1, NULL, NULL, NULL, NULL, NULL, 
	0, 2
);

-- 001120

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, 2, 1, NULL, NULL, NULL, NULL, NULL,
	1, 2, 1, NULL, NULL, NULL, NULL, NULL, 
	0, 0
);

-- 002020

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 2, NULL, NULL, NULL, NULL, NULL,
	2, NULL, 2, NULL, NULL, NULL, NULL, NULL, 
	0, 0
);

-- 002030

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, 1, NULL, NULL, NULL, NULL,
	2, NULL, 1, 1, NULL, NULL, NULL, NULL, 
	0, 0
);

-- 002050

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, NULL, NULL, 1, NULL, NULL,
	2, NULL, 1, NULL, NULL, 1, NULL, NULL, 
	0, 0
);

-- 002125

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, 1, 2, NULL, NULL, NULL, NULL, NULL,
	1, 1, 2, NULL, NULL, NULL, NULL, NULL, 
	0, 5
);

-- 002220

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, NULL, 3, NULL, NULL, NULL, NULL, NULL,
	1, NULL, 3, NULL, NULL, NULL, NULL, NULL, 
	0, 0
);

-- 002322

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, NULL, 2, 1, NULL, NULL, NULL, NULL,
	1, NULL, 2, 1, NULL, NULL, NULL, NULL, 
	0, 2
);

-- 005222

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, NULL, 2, NULL, NULL, 1, NULL, NULL,
	1, NULL, 2, NULL, NULL, 1, NULL, NULL, 
	0, 2
);

-- 012321

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 2, 1, NULL, NULL, NULL, NULL,
	NULL, 1, 2, 1, NULL, NULL, NULL, NULL, 
	0, 1
);

-- 012421

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 2, NULL, 1, NULL, NULL, NULL,
	NULL, 1, 2, NULL, 1, NULL, NULL, NULL, 
	0, 1
);

-- 012525

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 2, NULL, NULL, 1, NULL, NULL,
	NULL, 1, 2, NULL, NULL, 1, NULL, NULL, 
	0, 5
);

-- 012621

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 2, NULL, NULL, NULL, 1, NULL,
	NULL, 1, 2, NULL, NULL, NULL, 1, NULL, 
	0, 1
);

-- 012721

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 2, NULL, NULL, NULL, NULL, 1,
	NULL, 1, 2, NULL, NULL, NULL, NULL, 1, 
	0, 1
);

-- 012751

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 1, NULL, NULL, 1, NULL, 1,
	NULL, 1, 1, NULL, NULL, 1, NULL, 1, 
	0, 1
);

-- 014221

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 2, NULL, 1, NULL, NULL, NULL,
	NULL, 1, 2, NULL, 1, NULL, NULL, NULL, 
	0, 1
);

-- 014321

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 1, 1, 1, NULL, NULL, NULL,
	NULL, 1, 1, 1, 1, NULL, NULL, NULL, 
	0, 1
);

-- 014421

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 1, NULL, 2, NULL, NULL, NULL,
	NULL, 1, 1, NULL, 2, NULL, NULL, NULL, 
	0, 1
);

-- 014721

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 1, NULL, 1, NULL, NULL, 1,
	NULL, 1, 1, NULL, 1, NULL, NULL, 1, 
	0, 1
);

-- 016251

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 1, NULL, NULL, 1, 1, NULL,
	NULL, 1, 1, NULL, NULL, 1, 1, NULL, 
	0, 1
);

-- 017221

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 2, NULL, NULL, NULL, NULL, 1,
	NULL, 1, 2, NULL, NULL, NULL, NULL, 1, 
	0, 1
);

-- 017255

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 1, NULL, NULL, 1, NULL, 1,
	NULL, 1, 1, NULL, NULL, 1, NULL, 1, 
	0, 5
);

-- 017521

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 1, NULL, NULL, 1, NULL, 1,
	NULL, 1, 1, NULL, NULL, 1, NULL, 1, 
	0, 1
);

-- 017621

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 1, NULL, NULL, NULL, 1, 1,
	NULL, 1, 1, NULL, NULL, NULL, 1, 1, 
	0, 1
);

-- 017721

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 1, NULL, NULL, NULL, NULL, 2,
	NULL, 1, 1, NULL, NULL, NULL, NULL, 2, 
	0, 1
);

-- 025271

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, NULL, 2, NULL, NULL, 1, NULL, 1,
	NULL, NULL, 2, NULL, NULL, 1, NULL, 1, 
	0, 1
);

-- 100011

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	3, 1, NULL, NULL, NULL, NULL, NULL, NULL,
	3, 1, NULL, NULL, NULL, NULL, NULL, NULL, 
	1, 1
);

-- 100061

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	3, NULL, NULL, NULL, NULL, NULL, 1, NULL,
	3, NULL, NULL, NULL, NULL, NULL, 1, NULL, 
	1, 1
);

-- 100077

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	3, NULL, NULL, NULL, NULL, NULL, NULL, 1,
	3, NULL, NULL, NULL, NULL, NULL, NULL, 1, 
	1, 7
);

-- 100111

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, 2, NULL, NULL, NULL, NULL, NULL, NULL,
	2, 2, NULL, NULL, NULL, NULL, NULL, NULL, 
	1, 1
);

-- 100121

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, 1, 1, NULL, NULL, NULL, NULL, NULL,
	2, 1, 1, NULL, NULL, NULL, NULL, NULL, 
	1, 1
);

-- 100211

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, 1, 1, NULL, NULL, NULL, NULL, NULL,
	2, 1, 1, NULL, NULL, NULL, NULL, NULL, 
	1, 1
);

-- 100244

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, NULL, 1, NULL, NULL, NULL,
	2, NULL, 1, NULL, 1, NULL, NULL, NULL, 
	1, 4
);

-- 100277

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, NULL, NULL, NULL, NULL, 1,
	2, NULL, 1, NULL, NULL, NULL, NULL, 1, 
	1, 7
);

-- 100511

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, 1, NULL, NULL, NULL, 1, NULL, NULL,
	2, 1, NULL, NULL, NULL, 1, NULL, NULL, 
	1, 1
);

-- 101011

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, 2, NULL, NULL, NULL, NULL, NULL, NULL,
	2, 2, NULL, NULL, NULL, NULL, NULL, NULL, 
	1, 1
);

-- 101111

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, 3, NULL, NULL, NULL, NULL, NULL, NULL,
	1, 3, NULL, NULL, NULL, NULL, NULL, NULL, 
	1, 1
);

-- 101244

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, 1, 1, NULL, 1, NULL, NULL, NULL,
	1, 1, 1, NULL, 1, NULL, NULL, NULL, 
	1, 4
);

-- 101277

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, 1, 1, NULL, NULL, NULL, NULL, 1,
	1, 1, 1, NULL, NULL, NULL, NULL, 1, 
	1, 7
);

-- 102026

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 2, NULL, NULL, NULL, NULL, NULL,
	2, NULL, 2, NULL, NULL, NULL, NULL, NULL, 
	1, 6
);

-- 102121

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, 1, 2, NULL, NULL, NULL, NULL, NULL,
	1, 1, 2, NULL, NULL, NULL, NULL, NULL, 
	1, 1
);

-- 102211

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, 1, 2, NULL, NULL, NULL, NULL, NULL,
	1, 1, 2, NULL, NULL, NULL, NULL, NULL, 
	1, 1
);

-- 102244

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, NULL, 2, NULL, 1, NULL, NULL, NULL,
	1, NULL, 2, NULL, 1, NULL, NULL, NULL, 
	1, 4
);

-- 102263

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, NULL, 2, NULL, NULL, NULL, 1, NULL,
	1, NULL, 2, NULL, NULL, NULL, 1, NULL, 
	1, 3
);

-- 102277

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, NULL, 2, NULL, NULL, NULL, NULL, 1,
	1, NULL, 2, NULL, NULL, NULL, NULL, 1, 
	1, 7
);

-- 102327

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, NULL, 2, 1, NULL, NULL, NULL, NULL,
	1, NULL, 2, 1, NULL, NULL, NULL, NULL, 
	1, 7
);

-- 102424

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, NULL, 2, NULL, 1, NULL, NULL, NULL,
	1, NULL, 2, NULL, 1, NULL, NULL, NULL, 
	1, 4
);

-- 102626

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, NULL, 2, NULL, NULL, NULL, 1, NULL,
	1, NULL, 2, NULL, NULL, NULL, 1, NULL, 
	1, 6
);

-- 102644

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, NULL, 1, NULL, 1, NULL, 1, NULL,
	1, NULL, 1, NULL, 1, NULL, 1, NULL, 
	1, 4
);

-- 102677

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, NULL, 1, NULL, NULL, NULL, 1, 1,
	1, NULL, 1, NULL, NULL, NULL, 1, 1, 
	1, 7
);

-- 102710

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, 1, 1, NULL, NULL, NULL, NULL, 1,
	1, 1, 1, NULL, NULL, NULL, NULL, 1, 
	1, 0
);

-- 102727

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, NULL, 2, NULL, NULL, NULL, NULL, 1,
	1, NULL, 2, NULL, NULL, NULL, NULL, 1, 
	1, 7
);

-- 105427

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, NULL, 1, NULL, 1, 1, NULL, NULL,
	1, NULL, 1, NULL, 1, 1, NULL, NULL, 
	1, 7
);

-- 111121

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 3, 1, NULL, NULL, NULL, NULL, NULL,
	NULL, 3, 1, NULL, NULL, NULL, NULL, NULL, 
	1, 1
);

-- 111221

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 2, 2, NULL, NULL, NULL, NULL, NULL,
	NULL, 2, 2, NULL, NULL, NULL, NULL, NULL, 
	1, 1
);

-- 111244

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 2, 1, NULL, 1, NULL, NULL, NULL,
	NULL, 2, 1, NULL, 1, NULL, NULL, NULL, 
	1, 4
);

-- 111251

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 2, 1, NULL, NULL, 1, NULL, NULL,
	NULL, 2, 1, NULL, NULL, 1, NULL, NULL, 
	1, 1
);

-- 111261

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 2, 1, NULL, NULL, NULL, 1, NULL,
	NULL, 2, 1, NULL, NULL, NULL, 1, NULL, 
	1, 1
);

-- 111277

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 2, 1, NULL, NULL, NULL, NULL, 1,
	NULL, 2, 1, NULL, NULL, NULL, NULL, 1, 
	1, 7
);

-- 111522

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 2, 1, NULL, NULL, 1, NULL, NULL,
	NULL, 2, 1, NULL, NULL, 1, NULL, NULL, 
	1, 2
);

-- 112121

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 2, 2, NULL, NULL, NULL, NULL, NULL,
	NULL, 2, 2, NULL, NULL, NULL, NULL, NULL, 
	1, 1
);

-- 112221

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 3, NULL, NULL, NULL, NULL, NULL,
	NULL, 1, 3, NULL, NULL, NULL, NULL, NULL, 
	1, 1
);

-- 112244

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 2, NULL, 1, NULL, NULL, NULL,
	NULL, 1, 2, NULL, 1, NULL, NULL, NULL, 
	1, 4
);

-- 112251

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 2, NULL, NULL, 1, NULL, NULL,
	NULL, 1, 2, NULL, NULL, 1, NULL, NULL, 
	1, 1
);

-- 112277

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 2, NULL, NULL, NULL, NULL, 1,
	NULL, 1, 2, NULL, NULL, NULL, NULL, 1, 
	1, 7
);

-- 112321

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 2, 1, NULL, NULL, NULL, NULL,
	NULL, 1, 2, 1, NULL, NULL, NULL, NULL, 
	1, 1
);

-- 112424

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 2, NULL, 1, NULL, NULL, NULL,
	NULL, 1, 2, NULL, 1, NULL, NULL, NULL, 
	1, 4
);

-- 112621

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 2, NULL, NULL, NULL, 1, NULL,
	NULL, 1, 2, NULL, NULL, NULL, 1, NULL, 
	1, 1
);

-- 112727

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 2, NULL, NULL, NULL, NULL, 1,
	NULL, 1, 2, NULL, NULL, NULL, NULL, 1, 
	1, 7
);

-- 113221

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, 1, 2, 1, NULL, NULL, NULL, NULL,
	NULL, 1, 2, 1, NULL, NULL, NULL, NULL, 
	1, 1
);

-- 122244

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, NULL, 3, NULL, 1, NULL, NULL, NULL,
	NULL, NULL, 3, NULL, 1, NULL, NULL, NULL, 
	1, 4
);

-- 122277

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, NULL, 3, NULL, NULL, NULL, NULL, 1,
	NULL, NULL, 3, NULL, NULL, NULL, NULL, 1, 
	1, 7
);

-- 122434

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, NULL, 2, 1, 1, NULL, NULL, NULL,
	NULL, NULL, 2, 1, 1, NULL, NULL, NULL, 
	1, 4
);

-- 122547

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, NULL, 2, NULL, 1, 1, NULL, NULL,
	NULL, NULL, 2, NULL, 1, 1, NULL, NULL, 
	1, 7
);

-- 123244

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, NULL, 2, 1, 1, NULL, NULL, NULL,
	NULL, NULL, 2, 1, 1, NULL, NULL, NULL, 
	1, 4
);

-- 123277

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, NULL, 2, 1, NULL, NULL, NULL, 1,
	NULL, NULL, 2, 1, NULL, NULL, NULL, 1, 
	1, 7
);

-- 124255

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, NULL, 2, NULL, 1, 1, NULL, NULL,
	NULL, NULL, 2, NULL, 1, 1, NULL, NULL, 
	1, 5
);

-- 124267

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, NULL, 2, NULL, 1, NULL, 1, NULL,
	NULL, NULL, 2, NULL, 1, NULL, 1, NULL, 
	1, 7
);

-- 125275

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	NULL, NULL, 2, NULL, NULL, 1, NULL, 1,
	NULL, NULL, 2, NULL, NULL, 1, NULL, 1, 
	1, 5
);

-- 200012

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	3, 1, NULL, NULL, NULL, NULL, NULL, NULL,
	3, 1, NULL, NULL, NULL, NULL, NULL, NULL, 
	2, 2
);

-- 200022

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	3, NULL, 1, NULL, NULL, NULL, NULL, NULL,
	3, NULL, 1, NULL, NULL, NULL, NULL, NULL, 
	2, 2
);

-- 200042

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	3, NULL, NULL, NULL, 1, NULL, NULL, NULL,
	3, NULL, NULL, NULL, 1, NULL, NULL, NULL, 
	2, 2
);

-- 200071

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	3, NULL, NULL, NULL, NULL, NULL, NULL, 1,
	3, NULL, NULL, NULL, NULL, NULL, NULL, 1, 
	2, 1
);

-- 200122

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, 1, 1, NULL, NULL, NULL, NULL, NULL,
	2, 1, 1, NULL, NULL, NULL, NULL, NULL, 
	2, 2
);

-- 200152

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, 1, NULL, NULL, NULL, 1, NULL, NULL,
	2, 1, NULL, NULL, NULL, 1, NULL, NULL, 
	2, 2
);

-- 200212

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, 1, 1, NULL, NULL, NULL, NULL, NULL,
	2, 1, 1, NULL, NULL, NULL, NULL, NULL, 
	2, 2
);

-- 200222

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 2, NULL, NULL, NULL, NULL, NULL,
	2, NULL, 2, NULL, NULL, NULL, NULL, NULL, 
	2, 2
);

-- 200232

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, 1, NULL, NULL, NULL, NULL,
	2, NULL, 1, 1, NULL, NULL, NULL, NULL, 
	2, 2
);

-- 200242

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, NULL, 1, NULL, NULL, NULL,
	2, NULL, 1, NULL, 1, NULL, NULL, NULL, 
	2, 2
);

-- 200250

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, NULL, NULL, 1, NULL, NULL,
	2, NULL, 1, NULL, NULL, 1, NULL, NULL, 
	2, 2
);

-- 200262

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, NULL, NULL, NULL, 1, NULL,
	2, NULL, 1, NULL, NULL, NULL, 1, NULL, 
	2, 2
);

-- 200272

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, NULL, NULL, NULL, NULL, 1,
	2, NULL, 1, NULL, NULL, NULL, NULL, 1, 
	2, 2
);

-- 200326

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, 1, NULL, NULL, NULL, NULL,
	2, NULL, 1, 1, NULL, NULL, NULL, NULL, 
	2, 6
);

-- 200423

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, NULL, 1, NULL, NULL, NULL,
	2, NULL, 1, NULL, 1, NULL, NULL, NULL, 
	2, 3
);

-- 200517

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, NULL, NULL, NULL, 1, NULL, 1,
	2, NULL, NULL, NULL, NULL, 1, NULL, 1, 
	2, 7
);

-- 200522

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, NULL, NULL, 1, NULL, NULL,
	2, NULL, 1, NULL, NULL, 1, NULL, NULL, 
	2, 2
);

-- 200575

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, NULL, NULL, NULL, 1, NULL, 1,
	2, NULL, NULL, NULL, NULL, 1, NULL, 1, 
	2, 5
);

-- 200722

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, NULL, 1, NULL, NULL, NULL, NULL, 1,
	2, NULL, 1, NULL, NULL, NULL, NULL, 1, 
	2, 2
);

-- 201022

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	2, 1, 1, NULL, NULL, NULL, NULL, NULL,
	2, 1, 1, NULL, NULL, NULL, NULL, NULL, 
	2, 2
);

-- 201122

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, 2, 1, NULL, NULL, NULL, NULL, NULL,
	1, 2, 1, NULL, NULL, NULL, NULL, NULL, 
	2, 2
);

-- 201222

INSERT INTO regles_transition VALUES(
	"Langton s loop",
	1, 1, 2, NULL, NULL, NULL, NULL, NULL,
	1, 1, 2, NULL, NULL, NULL, NULL, NULL, 
	2, 2
);

-- 201422
-- 201722
-- 202022
-- 202032
-- 202052
-- 202073
-- 202122
-- 202152
-- 202212
-- 202222
-- 202272
-- 202321
-- 202422
-- 202452
-- 202520
-- 202552
-- 202622
-- 202722
-- 203122
-- 203216
-- 203226
-- 203422
-- 204222
-- 205122
-- 205212
-- 205222
-- 205521
-- 205725
-- 206222
-- 206722
-- 207122
-- 207222
-- 207422
-- 207722
-- 211222
-- 211261
-- 212222
-- 212242
-- 212262
-- 212272
-- 214222
-- 215222
-- 216222
-- 217222
-- 222272
-- 222442
-- 222462
-- 222762
-- 222772
-- 300013
-- 300022
-- 300041
-- 300076
-- 300123
-- 300421
-- 300622
-- 301021
-- 301220
-- 302511
-- 401120
-- 401220
-- 401250
-- 402120
-- 402221
-- 402326
-- 402520
-- 403221
-- 500022
-- 500215
-- 500225
-- 500232
-- 500272
-- 500520
-- 502022
-- 502122
-- 502152
-- 502220
-- 502244
-- 502722
-- 512122
-- 512220
-- 512422
-- 512722
-- 600011
-- 600021
-- 602120
-- 612125
-- 612131
-- 612225
-- 700077
-- 701120
-- 701220
-- 701250
-- 702120
-- 702221
-- 702251
-- 702321
-- 702525
-- 702720
