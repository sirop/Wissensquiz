#include <QSettings>
#include <QRegExpValidator>

#include "options.h"

#define INIFILE "files/wissensquiz.ini"

Options::Options (QWidget *parent): QWidget(parent)
{
    gLayout = new QGridLayout();
    gLayout->setSizeConstraint(QLayout::SetNoConstraint);
    gLayout->setColumnMinimumWidth(0,800);
    gLayout->setColumnMinimumWidth(3,800);
    gLayout->setRowMinimumHeight(0,800);
    gLayout->setRowMinimumHeight(5,800);

    lZeitnot = new QLabel(tr("Set Zeitnot [min] (<= 60)"));
    lSubset = new QLabel(tr("Set the least number of questions (>= 4)"));

    QSettings settings(INIFILE, QSettings::IniFormat , this);

    editZeitnot = new QLineEdit();
    editZeitnot->setText(settings.value("Zeitnot", 1).toString());
    editZeitnot->setMaxLength(12);

    editSubset = new QLineEdit();
    editSubset->setText(settings.value("Subset", 4).toString());
    editSubset->setMaxLength(16);

    saveButton = new QPushButton(tr("Save"));

    gLayout->addWidget(lZeitnot,1,1);
    gLayout->addWidget(lSubset,2,1);
    gLayout->addWidget(editZeitnot,1,2);
    gLayout->addWidget(editSubset,2,2);
    gLayout->addWidget(saveButton,4,2);

    setLayout(gLayout);

    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveButton_clicked()));
}


void Options::saveButton_clicked()
{
    QRegExp rxZeit("[1-9]+[0-9]?");

    QString sZeitnot = editZeitnot->text();
    QString sSubset = editSubset->text();

    bool ok;
    int zeitnot = sZeitnot.toInt(&ok, 10);

    if (!rxZeit.exactMatch(sZeitnot) || zeitnot > 60)
    {
        editZeitnot->setStyleSheet("background-color: red");
        editZeitnot->setText("[1-9]+[0-9]?");
        return ;
    }


    int subset = sSubset.toInt(&ok, 10);
    if (!ok || subset<4)
    {
        editSubset->setStyleSheet("background-color: red");
        return ;
    }
    else
    {
       editSubset->setStyleSheet("background-color: white");
    }

    QSettings settings(INIFILE, QSettings::IniFormat , this);
    settings.setValue("Zeitnot", sZeitnot);
    settings.setValue("Subset", sSubset);
}
