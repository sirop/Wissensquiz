#include "mainwindow.h"
#include "mainmenu.h"
#include "Game/game.h"
#include "Options/options.h"
#include "Statistics/statistics.h"
#include "XmlEditor/xmleditor.h"


MainMenu::MainMenu()
{

    buttonNewGame = new QPushButton(tr("&New Game?"),this);

    buttonOptions = new QPushButton(tr("&Options?"),this);
    buttonStatistics = new QPushButton(tr("&Statistics"),this);
    buttonEditXml = new QPushButton(tr("&Edit XML"),this);

    layout = new QGridLayout;
    layout->setSizeConstraint(QLayout::SetNoConstraint);

    layout->addWidget(buttonNewGame, 0, 0);
    layout->addWidget(buttonOptions, 0, 1);
    layout->addWidget(buttonStatistics, 1, 0);
    layout->addWidget(buttonEditXml, 1, 1);

    setLayout(layout);

    connect(buttonNewGame, SIGNAL(clicked()), this, SLOT(buttonNewGame_clicked()));
    connect(buttonOptions, SIGNAL(clicked()), this, SLOT(buttonOptions_clicked()));
    connect(buttonStatistics, SIGNAL(clicked()), this, SLOT(buttonStatistics_clicked()));
    connect(buttonEditXml, SIGNAL(clicked()), this, SLOT(buttonEditXml_clicked()));

}



void MainMenu::buttonNewGame_clicked()
{

    QTabWidget* temp = qobject_cast<QTabWidget*>(parent()->parent());
    temp->removeTab(0);
    temp->addTab(new Game(), tr("New Game"));

}

void MainMenu::buttonOptions_clicked()
{

    QTabWidget* temp = qobject_cast<QTabWidget*>(parent()->parent());
    temp->removeTab(0);
    temp->addTab(new Options(), tr("Options"));

}

void MainMenu::buttonStatistics_clicked()
{

    QTabWidget* temp = qobject_cast<QTabWidget*>(parent()->parent());
    temp->removeTab(0);
    temp->addTab(new Statistics(), tr("Statistics"));

}


void MainMenu::buttonEditXml_clicked()
{

    QTabWidget* temp = qobject_cast<QTabWidget*>(parent()->parent());
    temp->removeTab(0);
    temp->addTab(new XmlEditor(), tr("Xml Editor"));

}
