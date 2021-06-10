#include "reseau_cellule_etats.h"
#include "autocell.h"

#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QLayoutItem>
#include <QFont>

using namespace std;


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    AutoCell::getInstance().show();

    return app.exec();
}


