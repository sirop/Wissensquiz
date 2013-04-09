#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QObject>

#include <QGridLayout>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDir>

#include "MyFrame/myframe.h"

//! Game class.
/*!
Contains widgets for two players.
Loads game settings.
*/

class Game : public QWidget
{
   Q_OBJECT

public:
    /*!
      Constructs a Game tab.
    */
    Game(QWidget *parent = 0);

private slots:

    //! Selects xmlFile .
   /*!
     Sets  xmlFile to be the source of questions.
     Checks the validity of xmlFile.
     \sa XmlQuery::checkFiles() .
   */
    void setXMLFile(int id);

    void  chkLogin_clicked();
    void  chkMachine_checked();



private:
    QDir* xmlDir;
    QStringList xmlFiles;
    QString xmlFile;
    QLabel* lPlayer1 ;
    QLabel* lPlayer2 ;
    QLineEdit* namePlayer1 ;
    QLineEdit* namePlayer2 ;
    QCheckBox* chkMachine ;
    QPushButton* chkLogin ;
    QGridLayout *gLayout;
    QHBoxLayout *hlayout;
    MyFrame* player1;
    MyFrame* player2;


    //! Loads categories of questions.
   /*!
     Displays names of Xml files from  xmlDir("files") .
   */
    void loadCategories();

    //! Sets  the login mask.
   /*!
     Lets two players log in.
     Has option "Play against the macheine".
   */
    void loadLoginMask();

    //! Prepares player frames of the Game tab.
   /*!
   \param s1 is the name of the first user.
   \param hm1 lets the frame be owned by human or machine.
   \param s2 is the name of the second user.
   \param hm2 lets the frame be owned by human or machine.
   */
    void setPlayerFrames(const QString & s1, int hm1, const QString & s2, int hm2);
};

#endif // GAME_H
