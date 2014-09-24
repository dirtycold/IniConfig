#include "iniconfigreader.h"
#include <QLayout>
#include <QScrollArea>
#include <QFileDialog>
#include <QDir>

#include "iniconfigreader.h"
#include "iniconfigwidget.h"

using namespace RP;

IniConfigReader::IniConfigReader(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    QScrollArea *area = new QScrollArea(this);


    QString filename = QFileDialog::getOpenFileName (this,tr("Open Ini Config File"),QDir::currentPath (),tr("Ini Config File (*.ini *.cfg)"));
    IniConfigWidget *widget = new IniConfigWidget(filename, this);
    area->setWidget(widget);
    area->setWidgetResizable(true);
    layout->addWidget(area);
    this->setLayout(layout);
    this->resize(640,480);
}

IniConfigReader::~IniConfigReader()
{

}
