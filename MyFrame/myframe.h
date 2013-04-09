#ifndef MYFRAME_H
#define MYFRAME_H

#include <QFrame>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLCDNumber>

#include <QTimer>
#include <QTime>
#include <QAction>

//! MyFrame class.
/*!
Contains widgets for one player.
*/

class MyFrame : public QFrame
{
    Q_OBJECT
public:

   /*!
     Sets the layout, connects signals and slots.
     \param pIndex is either {1,2} for human player
     or {3} for the machine.
   */
    MyFrame(QWidget *parent = 0, const QString userName = "0", int pIndex=1, const QString & xmlFile="0");
    

    
private slots:


    /*!
      Loads a randomized list of questions from \sa xmlFile .
    */
    QString loadQuestions();


    /*!
      Sets a key action.
    */
    void keyAction1();


    /*!
      Sets a key action .
    */
    void keyAction2();


    /*!
     Sets a key action.
    */
    void keyAction3();


    /*!
     Sets a key action.
    */
    void keyAction4();


    /*!
     Loads next question.
    */
    void nextQuestion();


    /*!
     Processes time.
    */
    void processTime();


private:
    QString username;
    QStringList* qList;
    QStringList* aList;
    QList<int>*  caList;
    QVector<int>* userAnswers;
    QGroupBox *groupBox;
    QVBoxLayout *vboxGroup;
    QVBoxLayout *vboxFrame;
    QLabel* lQuestion;
    QLabel* lAnswer1;
    QLabel* lAnswer2;
    QLabel* lAnswer3;
    QLabel* lAnswer4;
    QLabel* PlaceHolder;
    QTimer* timer;
    QLCDNumber* lcd;
    QTime* t;
    QAction* key1;
    QAction* key2;
    QAction* key3;
    QAction* key4;
    int index;
    int qIndex;
    bool bZeitnot;
    int tZeitnot;
    int subset;
    QString xmlfile;

    void initializeActions();
    void addActions();
    void removeActions();
    void setText();
    void showTime();
    QString getScore();

};

#endif // MYFRAME_H
