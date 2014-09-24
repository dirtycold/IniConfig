#include "iniconfigwidget.h"

IniConfigWidget::IniConfigWidget(const QString &filename, QWidget *parent) :
    QWidget(parent)
{
    layout = new QGridLayout(this);
    config = new RP::IniConfig(filename.toStdString (),false);
    read();
}

IniConfigWidget::~IniConfigWidget ()
{
    write();
    delete config;
}

void IniConfigWidget::read()
{
    valuemap.clear();
    config->read();
    RP::StringMap map = config->mapRef();
    RP::StringMap::const_iterator it;
    uint count = 0;
    for (it = map.begin(); it != map.end(); it++, count++)
    {
        QLabel *l = new QLabel(QString::fromStdString(it->first));
        l->setAlignment(Qt::AlignLeft);
        layout->addWidget(l,count,0);
        QLineEdit *e = new QLineEdit(QString::fromStdString(it->second));
        e->setAlignment(Qt::AlignRight);
        layout->addWidget(e,count,1);
        valuemap.insert(l,e);
    }
}

void IniConfigWidget::write()
{
    QMap<QLabel*,QLineEdit*>::const_iterator it;
    for (it = valuemap.begin(); it != valuemap.end(); it++)
    {
        config->set(it.key()->text().toStdString(),it.value()->text().toStdString());
    }
    config->write();
}
