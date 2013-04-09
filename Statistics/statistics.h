#ifndef STATISTICS_H
#define STATISTICS_H

#include <QWidget>
#include <QGridLayout>
#include <QTableWidget>

//! Statistics class.
/*!
Shows players' sttistics.
*/

class Statistics : public QWidget
{
    Q_OBJECT
    
public:

   /*!
     Sets the layout.
   */
    Statistics(QWidget *parent = 0);

    
private:

    QGridLayout*  gLayout;
    QTableWidget* table;/*!< Statistics table widget. */

};

#endif // STATISTICS_H
