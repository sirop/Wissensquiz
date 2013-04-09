#include <QtXmlPatterns>
#include <QDomDocument>


#include "xmlquery.h"

//! Message Handler debugging class.
/*!
 Used here for debugging purposes only.
 Redirection from stderr.
*/

class MessageHandlerDebug : public QAbstractMessageHandler
{
    public:
        MessageHandlerDebug()
            : QAbstractMessageHandler(0)
        {
        }


    protected:
        virtual void handleMessage(QtMsgType type, const QString &description,
                                   const QUrl &identifier, const QSourceLocation &sourceLocation)
        {
            Q_UNUSED(type);
            Q_UNUSED(identifier);
            Q_UNUSED(description);

            m_messageType = type;
            m_description = description;
            m_sourceLocation = sourceLocation;
        }

    private:
        QtMsgType m_messageType;
        QString m_description;
        QSourceLocation m_sourceLocation;
};



XmlQuery::XmlQuery(const QString &xsdFile, const QString &xmlFile, int subset)
{

    if (checkFiles(xsdFile, xmlFile) == 0)
      {
        QFile qfile(xmlFile);
        QDomDocument doc;
        doc.setContent(&qfile, true);

        QByteArray xmlDoc = doc.toByteArray();
        QBuffer xmlBuffer(&xmlDoc);
        xmlBuffer.open(QIODevice::ReadOnly);

        query = new QXmlQuery();
        query->bindVariable("xmlDoc", &xmlBuffer);
        query->setQuery("doc($xmlDoc)/db/QuestionAnswers/question/normalize-space()");
        qList = new QStringList();
        query->evaluateTo(qList);
        randomList = new QList<int>(randomize(subset,qList->size()));

        qRandomList = new QStringList (getRandomizedQuestions());
        aRandomList = new QStringList(getRandomizedAnswers());
        caRandomList = new QList<int>(getRandomizedCA());

        xmlBuffer.close();
    }

}



QList<int> XmlQuery::randomize(int subset, int listsize)
{
    QList<int> temp;
    QList<int> list;
    for (int i = 0; i < listsize; i++)
    {
        temp.append(i);
    }

    QTime time = QTime::currentTime();

    if(subset > listsize)
    {
        subset = listsize;
    }

    for (int i = listsize - 1; i > (listsize - subset)-1; i--)
    {
        qsrand((uint)time.msec()+i);
        int n = qrand() % (i+1);
        temp.swap(i, n);
        list.append(temp.at(i));
    }

 return list;
}

QStringList XmlQuery::getRandomizedQuestions( )
{
  QStringList  list;
  for (int i = 0; i < randomList->size(); i++)
  {
      list.append(qList->at(randomList->at(i)));
  }

 return list;
}

QStringList XmlQuery::getRandomizedAnswers()
{

  query->setQuery("doc($xmlDoc)/db/QuestionAnswers/answer/normalize-space()");
  QStringList aList;
  query->evaluateTo(&aList);
  QStringList  list;
  for (int i = 0; i < randomList->size(); i++)
  {
      list.append(aList.at(4*randomList->at(i)+0));
      list.append(aList.at(4*randomList->at(i)+1));
      list.append(aList.at(4*randomList->at(i)+2));
      list.append(aList.at(4*randomList->at(i)+3));
  }

 return list;
}

QList<int> XmlQuery::getRandomizedCA()
{
  query->setQuery("doc($xmlDoc)/db/QuestionAnswers/CorrectAnswer/normalize-space()");
  QStringList cList;
  query->evaluateTo(&cList);
  QList<int>  list;

  bool ok;
  for (int i = 0; i < randomList->size(); i++)
  {
      list.append((cList.at(randomList->at(i))).toUShort(&ok));
  }

 return list;

}

int XmlQuery::checkFiles(const QString &xsdFile, const QString &xmlFile)
{
    QFile sfile(xsdFile);

    MessageHandlerDebug messageHandler;

    int errorCode = 0;

    if (!sfile.open(QIODevice::ReadOnly))
       {
        errorCode=1;
        return errorCode;
       }
    else
       {
        QXmlSchema schema;
        schema.setMessageHandler(&messageHandler);
        if (!schema.load(&sfile, QUrl::fromLocalFile(sfile.fileName())))
          {
            errorCode=2;
            return errorCode;
          }
        else
          {
            QFile xfile(xmlFile);
            if(!xfile.open(QIODevice::ReadOnly))
            {
               errorCode=3;
               return errorCode;
            }
            else
            {
                xfile.close();
                QXmlSchemaValidator validator(schema);
                if (!validator.validate(QUrl::fromLocalFile(xmlFile)))
                {
                   errorCode = 4;
                   return errorCode ;
                }
             }
           sfile.close();
          }
       }

    return errorCode;

}

QString XmlQuery::getErrorMessage(int &errorCode)
{
     switch (errorCode)
     {
       case 1:
         return "Schema Datei nicht lesbar.";
         //break;
       case 2:
         return "Schema nicht valide.";
         //break;
       case 3:
         return "XML Datei nicht lesbar.";
         //break;
       case 4:
         return "XML nicht valide.";
       default:
         return NULL;
     }
}
