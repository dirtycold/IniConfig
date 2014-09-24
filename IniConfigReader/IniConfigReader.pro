#-------------------------------------------------
#
# Project created by QtCreator 2014-09-24T10:53:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IniConfigReader
TEMPLATE = app


SOURCES += main.cpp\
        iniconfigreader.cpp \
    iniconfigwidget.cpp

HEADERS  += iniconfigreader.h \
    iniconfigwidget.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../IniConfig/release/ -lIniConfig
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../IniConfig/debug/ -lIniConfig
else:unix: LIBS += -L$$OUT_PWD/../IniConfig/ -lIniConfig

INCLUDEPATH += $$PWD/../IniConfig
DEPENDPATH += $$PWD/../IniConfig
