TEMPLATE = app

CONFIG -= app_bundle
CONFIG -= qt
SOURCES += main.cpp

CONFIG += console

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../IniConfig/release/ -lIniConfig
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../IniConfig/debug/ -lIniConfig
else:unix: LIBS += -L$$OUT_PWD/../IniConfig/ -lIniConfig

INCLUDEPATH += $$PWD/../IniConfig
DEPENDPATH += $$PWD/../IniConfig
