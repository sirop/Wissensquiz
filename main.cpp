/*! \mainpage
  This is a simple Qt application,
  which is more a proof of consept than something serious.

  The usage is more or less self explaining.

  Questions have to be defined according to XML Schema (wissensquiz.xsd)
  within an XML file (category_example.xml).
  You can have as many as quiz categories as you like. Of course, their number should not exceed the
  maximum integer of your system. ;)

  The Options tab lets you set a time limit (Zeitnot) and a number (Subset)
  of randomly chosen questions.

  You can play against another human player or against the machine simultaneously.
  Use keys {1, 2, 3, 4}  or  {H, J, K, L).

  The Statistics tab shows the players' statistics. ;)

  Compiled with Qt 4.8.3 .

*/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.showMaximized();
    w.showFullScreen();
    return a.exec();
}
