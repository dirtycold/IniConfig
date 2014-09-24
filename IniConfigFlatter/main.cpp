#include "iniconfigflatter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RP::IniConfigFlatter w;
    w.show();

    return a.exec();
}
