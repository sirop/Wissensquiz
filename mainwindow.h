#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTabWidget>


//! MainWindow class.
/*!
Serves as contrainer for child widgets.
*/

class MainWindow : public QWidget
{
    Q_OBJECT

 public:

   /*!
   Opens with the tabWidget MainMenu.
   */
     MainWindow(QWidget *parent = 0);

     QTabWidget* tabWidget; /*!< inner widget of MainWindow */


 private slots:

    //! Removes the current tab.
    /*! In case of MainMenu tab yields a dialogue
     for closing the game.
    */
    void removeTab(int index);


 private:
    //! Handles Esc-Key event.
   /*! Grabs Escape key only in case of
       MainMenu tab.
   */
    void keyPressEvent(QKeyEvent *event);

};

#endif // MAINWINDOW_H
