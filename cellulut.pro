QT += core
QT += sql
QT += widgets

INCLUDEPATH += "includes"

QMAKE_CXXFLAGS = -g -ggdb

SOURCES += src/autocell.cpp
SOURCES += src/voisinage.cpp
SOURCES += src/reseau_cellule_etats.cpp
SOURCES += src/main.cpp
SOURCES += src/autosql.cpp
SOURCES += src/Fonction.cpp
SOURCES += src/Automate.cpp
SOURCES += src/parametragemodele.cpp
SOURCES += src/paramalpha.cpp

HEADERS += includes/autocell.h \
    includes/coordonnees.h
HEADERS += includes/fonction.h
HEADERS += includes/autosql.h
HEADERS += includes/voisinage.h
HEADERS += includes/reseau_cellule_etats.h
HEADERS += includes/Fonction.h
HEADERS += includes/Automate.h
HEADERS += includes/parametragemodele.h
HEADERS += includes/paramalpha.h
