#include "iniconfigflatter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IniConfigFlatter w;
    w.show();

    return a.exec();
}
