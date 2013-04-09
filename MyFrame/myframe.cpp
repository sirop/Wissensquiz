#include <QTimer>
#include <QCoreApplication>
#include <QSettings>
#include <QFile>
#include <QTextStream>

#include "MyFrame.h"
#include "XMLQuery/xmlquery.h"

#define XSDFILE "files/wissensquiz.xsd"
#define INIFILE "files/wissensquiz.ini"

MyFrame::MyFrame(QWidget *parent, const QString userName, int pIndex, const QString & xmlFile) :
    QFrame(parent), xmlfile(xmlFile)
{
    QSettings settings(INIFILE ,QSettings::IniFormat , this);
    tZeitnot = settings.value("Zeitnot",1).toInt()*60000;
    subset = settings.value("Subset",4).toInt();


    QString error = loadQuestions();
    if (error == NULL)
    {
        username = userName;
        index = pIndex;
        bZeitnot = false;

        setFrameStyle(QFrame::Box);
        groupBox = new QGroupBox(username);
        lQuestion = new QLabel();
        lAnswer1 = new QLabel();
        lAnswer2 = new QLabel();
        lAnswer3 = new QLabel();
        lAnswer4 = new QLabel();
        PlaceHolder = new QLabel();
        vboxGroup = new QVBoxLayout;
        vboxGroup->addWidget(lQuestion);
        vboxGroup->addWidget(lAnswer1);
        vboxGroup->addWidget(lAnswer2);
        vboxGroup->addWidget(lAnswer3);
        vboxGroup->addWidget(lAnswer4);
        vboxGroup->addWidget(PlaceHolder);

        lcd = new QLCDNumber(6, this);
        timer = new QTimer(this);
        vboxGroup->addWidget(lcd);

        groupBox->setLayout(vboxGroup);

        vboxFrame = new QVBoxLayout;
        vboxFrame->addWidget(groupBox);

        setLayout(vboxFrame);

        if (index<3) // human players
        {
           initializeActions();
        }


        qIndex = 0;
        nextQuestion();

        connect(timer, SIGNAL(timeout()), this, SLOT(processTime()));
        timer->start(1000);
        t = new QTime;
        t->start();

        showTime();
    }
    else
    {
        setFrameStyle(QFrame::Box);
        QVBoxLayout* vbox = new QVBoxLayout;
        QString errorMessage = error+"\n"+tr("Please return to the Mainmenu by closing this tab.");
        QLabel* lError = new QLabel(errorMessage);
        vbox->addWidget(lError);
        setLayout(vbox);

    }



}

QString MyFrame::loadQuestions()
{

    XmlQuery temp(XSDFILE, xmlfile, subset);
    int errorCode = XmlQuery::checkFiles(XSDFILE, xmlfile);
    if (errorCode == 0)
    {
        qList = new QStringList(*temp.qRandomList);
        aList = new QStringList(*temp.aRandomList);
        caList = new QList<int>(*temp.caRandomList);
        userAnswers = new QVector<int>();
        return NULL;
    }
    else
    {
        return(XmlQuery::getErrorMessage(errorCode));
    }

}

void MyFrame::nextQuestion()
{
    if(qIndex < qList->size())
    {
      MyFrame::setText();
      qIndex++;
      if (index < 3)
      {
       MyFrame::addActions();
      }

    }
    else
    {
        this->disconnect();
        if (index < 3)
        {
          MyFrame::removeActions();
        }

        QLayoutItem *child;
        while ((child = vboxGroup->takeAt(0)) != 0)
        {
            delete child->widget();
            delete child;
        }
        delete timer;

        QLabel* result= new QLabel();

        if (bZeitnot)
        {
           result->setText("ZEITNOT");
        }
        else
        {
            result->setText(tr("Result: ")+getScore()+tr("Time: ")+QString::number(t->elapsed())+"ms");
            QFile statFile( "files/statistics.txt");
            if (statFile.open(QIODevice::Append | QIODevice::Text))
              {
                int correctAnswers = getScore().section(" / ",0,0).toInt();
                int totalAnswers = getScore().section(" / ",1,1).toInt();
                int t_elapsed = t->elapsed();
                double finalScore =static_cast<double> (correctAnswers/(totalAnswers*t_elapsed));
                QTextStream out(&statFile);
                out<< username << ","<< finalScore<<endl;
                statFile.close();
               }
        }

        vboxGroup->addWidget(result);

    }
}

void MyFrame::initializeActions()
{
    key1 = new QAction( this);
    key2 = new QAction( this);
    key3 = new QAction( this);
    key4 = new QAction( this);

    if (index ==1)
    {

        key1->setAutoRepeat (false);
        key1 -> setShortcut (Qt::Key_1);
        connect(key1, SIGNAL(triggered()), this, SLOT(keyAction1()));

        key2 -> setShortcut (Qt::Key_2);
        key2->setAutoRepeat (false);
        connect(key2, SIGNAL(triggered()), this, SLOT(keyAction2()));

        key3 -> setShortcut (Qt::Key_3);
        key3->setAutoRepeat (false);
        connect(key3, SIGNAL(triggered()), this, SLOT(keyAction3()));

        key4 -> setShortcut (Qt::Key_4);
        key4->setAutoRepeat (false);
        connect(key4, SIGNAL(triggered()), this, SLOT(keyAction4()));

        MyFrame::addActions();
    }

    if (index ==2)
    {

        key1 -> setShortcut (Qt::Key_H);
        key1->setAutoRepeat (false);
        connect(key1, SIGNAL(triggered()), this, SLOT(keyAction1()));

        key2 -> setShortcut (Qt::Key_J);
        key2->setAutoRepeat (false);
        connect(key2, SIGNAL(triggered()), this, SLOT(keyAction2()));

        key3 -> setShortcut (Qt::Key_K);
        key3->setAutoRepeat (false);
        connect(key3, SIGNAL(triggered()), this, SLOT(keyAction3()));


        key4 -> setShortcut (Qt::Key_L);
        key4->setAutoRepeat (false);
        connect(key4, SIGNAL(triggered()), this, SLOT(keyAction4()));

        MyFrame::addActions();
    }
}

void MyFrame::keyAction1()
{
      lAnswer1->setStyleSheet("background-color: skyblue");
      userAnswers->append(1);
      removeActions();
      QTimer::singleShot(500, this , SLOT(nextQuestion()));


}

void MyFrame::keyAction2()
{
    lAnswer2->setStyleSheet("background-color: skyblue");
    userAnswers->append(2);
    removeActions();
    QTimer::singleShot(500, this , SLOT(nextQuestion()));

}

void MyFrame::keyAction3()
{
    lAnswer3->setStyleSheet("background-color: skyblue");
    userAnswers->append(3);
    removeActions();
    QTimer::singleShot(500, this , SLOT(nextQuestion()));

}

void MyFrame::keyAction4()
{
    lAnswer4->setStyleSheet("background-color: skyblue");
    userAnswers->append(4);
    removeActions();
    QTimer::singleShot(500, this , SLOT(nextQuestion()));
}



void MyFrame::removeActions()
{
    QList<QAction *> temp(actions());
    for (int i=0; i< temp.size(); i++)
    {
        removeAction(temp.at(i));
    }
}

void MyFrame::addActions()
{
    addAction(key1);
    addAction(key2);
    addAction(key3);
    addAction(key4);
}

void MyFrame::setText()
{
    if (index == 1)
    {
        lQuestion->setText(qList->at(qIndex));
        lAnswer1->setText("1 ) " + aList->at(4*qIndex));
        lAnswer2->setText("2 ) " + aList->at(4*qIndex+1));
        lAnswer3->setText("3 ) " + aList->at(4*qIndex+2));
        lAnswer4->setText("4 ) " + aList->at(4*qIndex+3));

    }

    if (index == 2 || index == 3)
    {
        lQuestion->setText(qList->at(qIndex));
        lAnswer1->setText("H ) " + aList->at(4*qIndex));
        lAnswer2->setText("J ) " + aList->at(4*qIndex+1));
        lAnswer3->setText("K ) " + aList->at(4*qIndex+2));
        lAnswer4->setText("L ) " + aList->at(4*qIndex+3));

    }

    lAnswer1->setStyleSheet("background-color: white");
    lAnswer2->setStyleSheet("background-color: white");
    lAnswer3->setStyleSheet("background-color: white");
    lAnswer4->setStyleSheet("background-color: white");
}

QString MyFrame::getScore()
{
    int correctAnswers = 0;
    for (int i=0; i < userAnswers->size(); i++)
    {
        if (userAnswers->at(i)== caList->at(i))
        {
            correctAnswers++;
        }
    }

    QString str = QString::number(correctAnswers)+" / "+ QString::number(caList->size())+"\n";

    return (str);
}

void MyFrame::showTime()
{

    QString min = QString( "%1" ).arg(static_cast<uint>(t->elapsed()/60000), 2,10, QLatin1Char( '0' ));
    QString sec = QString("%1").arg(static_cast<uint>((t->elapsed() / 1000) % 60), 2,10, QLatin1Char( '0' ));
    lcd->display(min+":"+sec);
}

void MyFrame::processTime()
{
    showTime();

    if (index == 3) // machine
    {
        if (t->elapsed() >= (tZeitnot/qList->size())*qIndex)
        {
            qsrand(t->elapsed());
            int random = qrand() % 3;
            userAnswers->append(random + 1);
            QLabel* temp = qobject_cast<QLabel*> (vboxGroup->itemAt(random + 1)->widget());
            temp->setStyleSheet("background-color: skyblue");
            QTimer::singleShot(500, this , SLOT(nextQuestion()));
        }
    }

    if (t->elapsed() >= tZeitnot+1000)
    {
        qIndex = qList->size();
        bZeitnot = true;
        nextQuestion();
        return ;
    }
}

