#include <QAction>
#include <QTabWidget>
#include <QRegExpValidator>
#include <QDateTime>
#include <QButtonGroup>
#include <QMessageBox>


#include "game.h"
#include "MyFrame/myframe.h"
#include "XMLQuery/xmlquery.h"

#define XSDFILE "files/wissensquiz.xsd"

Game::Game(QWidget *parent): QWidget(parent)
{
    gLayout = new QGridLayout();
    gLayout->setSizeConstraint(QLayout::SetNoConstraint);

    loadCategories();
}

void Game::chkLogin_clicked()
{
     QRegExp rx("[A-Za-z]+[0-9]*");
     QRegExpValidator v(rx,0);
     int pos = 32;

     QString sPlayer1 = namePlayer1->text();
     QString sPlayer2 = namePlayer2->text();

     if (v.validate(sPlayer1,pos)!=2)
     {
         namePlayer1->setStyleSheet("background-color: red");
         namePlayer1->setText("[A-Za-z]+[0-9]*");
         return;
     }

     if (v.validate(sPlayer2,pos)!=2)
     {
         namePlayer2->setStyleSheet("background-color: red");
         namePlayer2->setText("[A-Za-z]+[0-9]*");
         return;
     }

     if (sPlayer1==sPlayer2)
     {
         namePlayer2->setText(tr("Choose a different name."));
         return;
     }


     if (chkMachine->isChecked())
     {

         setPlayerFrames(sPlayer1, 1, sPlayer2, 3);
     }
     else
     {
         setPlayerFrames(sPlayer1, 1, sPlayer2, 2);
     }



}

void Game::setPlayerFrames(const QString & s1, int hm1, const QString & s2, int hm2)
{
    QLayoutItem *child;
    while ((child = gLayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }
    delete gLayout;

    QHBoxLayout *hLayout = new QHBoxLayout();
    MyFrame* player1 = new MyFrame(this, s1,hm1, xmlFile);

    MyFrame* player2 = new MyFrame(this,s2,hm2, xmlFile);

    hLayout->addWidget(player1);
    hLayout->addWidget(player2);

    setLayout(hLayout);
}

void Game::chkMachine_checked()
{
    if (chkMachine->isChecked())
    {
        QString str = "Machine" + QDateTime::currentDateTime().toString("dMyyHm");
        namePlayer2->setText(str);
        namePlayer2->setEnabled(false);
    }
    else
    {
        namePlayer2->setEnabled(true);
    }

}

void Game::loadCategories()
{
    xmlDir = new QDir("files");
    QStringList filter;
    filter << "*.xml";
    xmlDir->setNameFilters(filter);
    xmlDir->setSorting(QDir::Name);
    xmlFiles = xmlDir->entryList();


    QButtonGroup* buttongroup = new QButtonGroup(this);
    buttongroup->setExclusive (true);
    for (int i = 0; i < xmlFiles.size(); i++)
    {
        QPushButton* button = new QPushButton (xmlFiles.at(i).section('.', 0, 0),this);
        buttongroup->addButton(button , i);
        gLayout->addWidget(button, i / 3, i % 3);
    }
    setLayout(gLayout);
    connect(buttongroup, SIGNAL(buttonPressed(int)),this, SLOT(setXMLFile(int)));
}

void Game::setXMLFile(int id)
{
    xmlFile = xmlDir->absolutePath()+"/"+xmlFiles.at(id);
    QLayoutItem *child;
    while ((child = gLayout->takeAt(0)) != 0)
    {
    delete child->widget();
    delete child;
    }

    int errorCode =  XmlQuery::checkFiles(XSDFILE, xmlFile);
    if ( errorCode == 0)
        loadLoginMask();
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(tr("Error: ")+ XmlQuery::getErrorMessage(errorCode)+"\n");
        msgBox.setInformativeText(tr("Please return to Main Menu"));
        msgBox.exec();
    }

}

void Game::loadLoginMask()
{
    gLayout->setColumnMinimumWidth(0,800);
    gLayout->setColumnMinimumWidth(3,800);
    gLayout->setRowMinimumHeight(0,800);
    gLayout->setRowMinimumHeight(5,800);

    lPlayer1 = new QLabel("Player 1");
    lPlayer2 = new QLabel("Player 2");
    namePlayer1 = new QLineEdit();
    namePlayer1->setPlaceholderText("[A-Za-z]+[0-9]*");
    namePlayer1->setMaxLength(32);

    namePlayer2 = new QLineEdit();
    namePlayer2->setPlaceholderText("[A-Za-z]+[0-9]*");
    namePlayer2->setMaxLength(32);
    chkMachine = new QCheckBox(tr("Play against the Machine"));
    chkLogin = new QPushButton(tr("Log in"));
    gLayout->addWidget(lPlayer1,1,1);
    gLayout->addWidget(lPlayer2,2,1);
    gLayout->addWidget(namePlayer1,1,2);
    gLayout->addWidget(namePlayer2,2,2);
    gLayout->addWidget(chkMachine,3,2);
    gLayout->addWidget(chkLogin,4,2);

    setLayout(gLayout);

    connect(chkMachine, SIGNAL(clicked()),this,SLOT(chkMachine_checked()));
    connect(chkLogin, SIGNAL(clicked()),this,SLOT(chkLogin_clicked()));
}
