#ifndef INICONFIGWIDGET_H
#define INICONFIGWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMap>

#include "../IniConfig/iniconfig.h"

class IniConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IniConfigWidget(const QString& filename, QWidget *parent = 0);
    virtual ~IniConfigWidget();

    void read();
    void write();

private:
    QGridLayout *layout;
    RP::IniConfig *config;
    QMap<QLabel*,QLineEdit*> valuemap;
};

#endif // INICONFIGWIDGET_H
