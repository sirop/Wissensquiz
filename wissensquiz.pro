#-------------------------------------------------
#
# Project created by QtCreator 2013-02-13T08:40:19
#
#-------------------------------------------------

QT       += core gui xml xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wissensquiz

SOURCES += main.cpp\
    mainwindow.cpp \
    XMLQuery/xmlquery.cpp \
    XmlEditor/highlight/xmlsyntaxhighlighter.cpp \
    XmlEditor/xmleditor.cpp \
    Statistics/statistics.cpp \
    Options/options.cpp \
    Mainmenu/mainmenu.cpp \
    Game/game.cpp \
    MyFrame/myframe.cpp

HEADERS  += \
    mainwindow.h \
    XMLQuery/xmlquery.h \
    XmlEditor/highlight/xmlsyntaxhighlighter.h \
    XmlEditor/xmleditor.h \
    Statistics/statistics.h \
    Options/options.h \
    Mainmenu/mainmenu.h \
    Game/game.h \
    MyFrame/myframe.h

#FORMS    += mainwindow.ui

OTHER_FILES += \
    files/wissensquiz.ini \
    files/statistics.txt \
    files/wissensquiz.xsd \
    files/category_example.xml

FORMS += \
    XmlEditor/xmleditor.ui \


TRANSLATIONS    = wissensquiz_de.ts
