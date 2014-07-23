#ifndef INICONFIGFLATTER_H
#define INICONFIGFLATTER_H

#include <QWidget>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>

class IniConfigFlatter : public QWidget
{
    Q_OBJECT

public:
    IniConfigFlatter(QWidget *parent = 0);
    ~IniConfigFlatter();

protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dragMoveEvent(QDragMoveEvent *e);
    void dragLeaveEvent(QDragLeaveEvent *e);
    void dropEvent(QDropEvent *e);
};

#endif // INICONFIGFLATTER_H
