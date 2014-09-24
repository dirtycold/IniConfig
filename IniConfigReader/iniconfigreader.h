#ifndef INICONFIGREADER_H
#define INICONFIGREADER_H

#include <QWidget>

class IniConfigReader : public QWidget
{
    Q_OBJECT

public:
    explicit IniConfigReader(QWidget *parent = 0);
    virtual ~IniConfigReader();
};

#endif // INICONFIGREADER_H
