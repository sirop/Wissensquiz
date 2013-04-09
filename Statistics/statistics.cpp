#include <QDebug>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QHeaderView>


#include "statistics.h"


Statistics::Statistics(QWidget *parent) :
    QWidget(parent)
{
    QStringList headerlist;
    headerlist << tr("Player") << tr("Score");
    table = new QTableWidget();


    QFile statFile( "files/statistics.txt");

    if (statFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&statFile);
        QString str = in.readAll();
        QStringList rows = str.split('\n' , QString::SkipEmptyParts);

        int numRows = rows.count();
        int numColumns = 2;
        table->setRowCount(numRows);
        table->setColumnCount(numColumns);

        QStringList columns = rows[0].split(',');

        for (int i = 0; i < numRows; ++i)
        {
            QStringList columns = rows[i].split(',');
            for (int j = 0; j < numColumns; ++j)
            {
                QTableWidgetItem *cell = new QTableWidgetItem(columns[j],0);
                cell->setTextAlignment(Qt::AlignHCenter);
                table->setItem(i, j, cell);
            }
        }
        statFile.close();
    }

   table->sortByColumn(1,Qt::DescendingOrder);
   table->setSortingEnabled(true);
   table->horizontalHeader()-> setResizeMode ( QHeaderView::Interactive );
   table->horizontalHeader()->setStretchLastSection( true );
   table->setHorizontalHeaderLabels(headerlist);

   gLayout = new QGridLayout(this);
   gLayout -> addWidget(table,0,0);
   setLayout(gLayout);
}


