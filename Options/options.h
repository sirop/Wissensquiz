#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
#include <QObject>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

//! Options class.
/*!
Lets the user set a Zeitnot and set the number of questions.
*/

class Options : public QWidget
{
    Q_OBJECT


public:

   /*!
     Sets the layout and connects signals and slots.
   */
    Options(QWidget *parent = 0);


private slots:


    /*!
      Saves the options to INIFILE "files/wissensquiz.ini" .
    */
    void saveButton_clicked();

private:
    QLabel* lZeitnot;
    QLabel* lSubset;
    QLineEdit* editZeitnot;
    QLineEdit* editSubset;
    QPushButton* saveButton;
    QGridLayout* gLayout;
};

#endif // OPTIONS_H



