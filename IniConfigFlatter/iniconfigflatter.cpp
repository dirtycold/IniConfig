#include "iniconfigflatter.h"

#include <QLabel>
#include <QMimeData>
#include <QUrl>
#include <QLayout>

#include "../IniConfig/iniconfig.h"

using namespace RP;

IniConfigFlatter::IniConfigFlatter(QWidget *parent)
    : QWidget(parent)
{
    QLabel* label = new QLabel("<p align=center>Drop Pre-Ini File(s) here</p>",this);
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget (label);
    resize(300,300);
    setAcceptDrops(true);
}

IniConfigFlatter::~IniConfigFlatter()
{

}

void IniConfigFlatter::dragEnterEvent(QDragEnterEvent *e)
{
    e->acceptProposedAction();
}

void IniConfigFlatter::dragMoveEvent(QDragMoveEvent *e)
{
    e->acceptProposedAction();
}

void IniConfigFlatter::dragLeaveEvent(QDragLeaveEvent *e)
{
    e->accept();
}

void IniConfigFlatter::dropEvent(QDropEvent *e)
{
    const QMimeData *mime = e->mimeData();
    if (mime->hasUrls())
    {
        QList<QUrl> urls= mime->urls();
        foreach(QUrl url, urls)
        {
            QString filepath = url.toLocalFile();
            {
                RP::IniConfig config(filepath.toStdString(), RP::IniConfig::ReadWrite);
                Q_UNUSED(config);
            }
        }
    }
}
