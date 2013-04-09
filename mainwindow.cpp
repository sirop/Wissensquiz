#include <QVBoxLayout>
#include <QMessageBox>
#include <QKeyEvent>

#include "mainwindow.h"
#include "Mainmenu/mainmenu.h"




MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    tabWidget = new QTabWidget;
    tabWidget->setTabsClosable(true);
    connect(tabWidget, SIGNAL(tabCloseRequested(int)),this, SLOT(removeTab(int)));

    tabWidget->addTab(new MainMenu(), tr("MainMenu"));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);

    setWindowTitle(tr("WissensQuiz"));
}

void MainWindow::removeTab(int index)
{
    if (!qobject_cast<MainMenu*>(tabWidget->widget(index)))
    {
        tabWidget->removeTab(index);
        tabWidget->addTab(new MainMenu(), tr("MainMenu"));
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Wissensquiz will be closed."));
        msgBox.setInformativeText(tr("Do you want to proceed?"));
        msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        switch (ret)
        {
        case QMessageBox::Ok:
            this->close();
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && qobject_cast<MainMenu*>(tabWidget->currentWidget()))
        MainWindow::removeTab(tabWidget->currentIndex());
}
