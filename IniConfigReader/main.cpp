#include "iniconfigreader.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IniConfigReader w;
    w.show();

    return a.exec();
}
