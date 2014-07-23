#-------------------------------------------------
#
# Project created by QtCreator 2014-07-23T10:27:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IniConfigFlatter
TEMPLATE = app


SOURCES += main.cpp\
        iniconfigflatter.cpp

HEADERS  += iniconfigflatter.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../IniConfig/release/ -lIniConfig
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../IniConfig/debug/ -lIniConfig
else:unix: LIBS += -L$$OUT_PWD/../IniConfig/ -lIniConfig

INCLUDEPATH += $$PWD/../IniConfig
DEPENDPATH += $$PWD/../IniConfig
