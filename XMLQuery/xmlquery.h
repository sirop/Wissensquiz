#ifndef XMLQUERY_H
#define XMLQUERY_H

#include <QXmlQuery>

//! XmlQuery class.
/*!
 Constructs and executes Xml queries.
*/

class XmlQuery
{

public:

    /*!
      \param xsdFile is XSD schema file.
      \param xmlFile is XML file containing questions.
      \param subset is the number of questions to be chosen randomly.
    */
    XmlQuery(const QString& xsdFile, const QString& xmlFile, int subset);

    QStringList* qRandomList;  /*!< Randomized list of questions. */
    QStringList* aRandomList;  /*!< Randomized list of answers, corresponding to questions. */
    QList<int>*  caRandomList; /*!< Randomized list of answer values. */

    static QString getErrorMessage(int& errorCode);

    static int checkFiles(const QString& xsdFile, const QString& xmlFile);


private:

    QXmlQuery* query;
    QStringList* qList;
    QList<int> * randomList;

    QList<int> randomize(int subset, int listsize);
    QStringList getRandomizedQuestions();
    QStringList getRandomizedAnswers( );
    QList<int> getRandomizedCA();

};

#endif // XMLQUERY_H
