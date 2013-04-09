 /****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>
#include <QtXmlPatterns>

#include "xmleditor.h"
#include "highlight/xmlsyntaxhighlighter.h"

#define XSDFILE "files/wissensquiz.xsd"


//! Message Handler  class.
/*!
 Redirects error messages from stderr.
*/

class MessageHandler : public QAbstractMessageHandler
{
    public:
        MessageHandler()
            : QAbstractMessageHandler(0)
        {
        }

        QString statusMessage() const
        {
            return m_description;
        }

        int line() const
        {
            return m_sourceLocation.line();
        }

        int column() const
        {
            return m_sourceLocation.column();
        }

    protected:
        virtual void handleMessage(QtMsgType type, const QString &description,
                                   const QUrl &identifier, const QSourceLocation &sourceLocation)
        {
            Q_UNUSED(type);
            Q_UNUSED(identifier);

            m_messageType = type;
            m_description = description;
            m_sourceLocation = sourceLocation;
        }

    private:
        QtMsgType m_messageType;
        QString m_description;
        QSourceLocation m_sourceLocation;
};

XmlEditor::XmlEditor()
{
    setupUi(this);
    connect(newButton, SIGNAL(clicked()), this,SLOT(newFile()));
    connect(openButton, SIGNAL(clicked()), this,SLOT(openFile()));
    connect(saveButton, SIGNAL(clicked()), this,SLOT(saveFile()));

    new XmlSyntaxHighlighter(schemaView->document());
    new XmlSyntaxHighlighter(instanceEdit->document());


    QFile schemaFile(XSDFILE);
    schemaFile.open(QIODevice::ReadOnly | QIODevice::Text);

    const QString schemaText(QString::fromUtf8(schemaFile.readAll()));
    schemaView->setPlainText(schemaText);
    schemaView->setPlainText(schemaText);

    connect(validateButton, SIGNAL(clicked()), SLOT(validate()));
    connect(instanceEdit, SIGNAL(textChanged()), SLOT(textChanged()));

    validationStatus->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

}



void XmlEditor::validate()
{
    const QByteArray schemaData = schemaView->toPlainText().toUtf8();
    const QByteArray instanceData = instanceEdit->toPlainText().toUtf8();

    MessageHandler messageHandler;

    QXmlSchema schema;
    schema.setMessageHandler(&messageHandler);

    schema.load(schemaData);

    bool errorOccurred = false;
    if (!schema.isValid()) {
        errorOccurred = true;
    } else {
        QXmlSchemaValidator validator(schema);
        if (!validator.validate(instanceData))
            errorOccurred = true;
    }

    if (errorOccurred) {
        validationStatus->setText(messageHandler.statusMessage());
        moveCursor(messageHandler.line(), messageHandler.column());
    } else {
        validationStatus->setText(tr("validation successful"));
    }

    const QString styleSheet = QString("QLabel {background: %1; padding: 3px}")
                                      .arg(errorOccurred ? QColor(Qt::red).lighter(160).name() :
                                                           QColor(Qt::green).lighter(160).name());
    validationStatus->setStyleSheet(styleSheet);
}


void XmlEditor::textChanged()
{
    instanceEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>());
}

void XmlEditor::moveCursor(int line, int column)
{
    instanceEdit->moveCursor(QTextCursor::Start);
    for (int i = 1; i < line; ++i)
         instanceEdit->moveCursor(QTextCursor::Down);

    for (int i = 1; i < column; ++i)
         instanceEdit->moveCursor(QTextCursor::Right);

    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextEdit::ExtraSelection selection;

    const QColor lineColor = QColor(Qt::red).lighter(160);
    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = instanceEdit->textCursor();
    selection.cursor.clearSelection();
    extraSelections.append(selection);

    instanceEdit->setExtraSelections(extraSelections);

    instanceEdit->setFocus();
}

void XmlEditor::newFile()
{
    xmlFile = "";
    instanceEdit->setPlainText("");
    instanceEdit->setFocus();
}

void XmlEditor::openFile()
{
    xmlFile = QFileDialog::getOpenFileName(this, tr("Open XML File"), "c:", tr("XML Files (*.xml)"));
    QFile instanceFile(xmlFile);
    instanceFile.open(QIODevice::ReadOnly | QIODevice::Text);

        const QString instanceText(QString::fromUtf8(instanceFile.readAll()));
        instanceEdit->setPlainText(instanceText);

}

void XmlEditor::saveFile()
{
    xmlFile = QFileDialog::getSaveFileName(this, tr("Open XML File"), "c:", tr("XML Files (*.xml)"));
    QFile file(xmlFile);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "WissensQuiz",
                             tr("Cannot write file %1:\n%2.")
                             .arg(xmlFile)
                             .arg(file.errorString()));
        return ;
    }

    QTextStream out(&file);
    out << instanceEdit->toPlainText();
    return ;
}

