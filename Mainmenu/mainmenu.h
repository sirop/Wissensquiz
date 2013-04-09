#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QGridLayout>


//! MainMenu class.
/*!
Lets the user load other tabs.
*/

class MainMenu : public QWidget
{
   Q_OBJECT
    
public:

   /*!
     Sets the layout and connects signals and slots.
   */
    MainMenu();

private slots:


    /*!
      Removes the Mainmenu tab and opens a New Game tab.
    */
    void buttonNewGame_clicked();


    /*!
      Removes the Mainmenu tab and opens an Options tab.
    */
    void buttonOptions_clicked();


    /*!
      Removes the Mainmenu tab and opens a Statistics tab.
    */
    void buttonStatistics_clicked();


    /*!
      Removes the Mainmenu tab and opens an XML-Editor tab.
    */
    void buttonEditXml_clicked();

private:

    QPushButton* buttonNewGame;
    QPushButton* buttonOptions;
    QPushButton* buttonStatistics;
    QPushButton* buttonEditXml;
    QGridLayout* layout;

};

#endif // MAINMENU_H
