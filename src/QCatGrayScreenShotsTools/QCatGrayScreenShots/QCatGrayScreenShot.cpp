#include "QCatGrayScreenShot.h"
#include "QtWidgets/qapplication.h"
#include <QGuiApplication>
#include <QPixmap>
#include <QScreen>

QCatGrayScreenShot::QCatGrayScreenShot(QObject *parent)
    : QObject{parent}
{

}

QCatGrayScreenShot::~QCatGrayScreenShot()
{

}

void *QCatGrayScreenShot::getScreenShot(int screenid,
                                        int x, int y,
                                        int width, int height,
                                        int winid) const
{
    QPixmap *map = nullptr;
    if(QGuiApplication::screens().length() > screenid && screenid >= 0)
    {
        QScreen *screen = QGuiApplication::screens().at(screenid);
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
        map = new QPixmap(screen->grabWindow(
            static_cast<WId>(winid),
            x,
            y,
            width,
            height
            ));
#else
        map = new QPixmap(screen->grabWindow(
            static_cast<WId>(winid),
            x,
            y,
            width,
            height
            ));
#endif
    }
    return map;
}

double QCatGrayScreenShot::logicalDotsPerInchX(int screenid) const
{
    double logicalDotsPerInchX = -1;
    if(QGuiApplication::screens().length() > screenid && screenid >= 0)
    {
        logicalDotsPerInchX = QGuiApplication::screens().at(screenid)->logicalDotsPerInchX();
    }
    return logicalDotsPerInchX;
}

double QCatGrayScreenShot::logicalDotsPerInchY(int screenid) const
{
    double logicalDotsPerInchY = -1;
    if(QGuiApplication::screens().length() > screenid && screenid >= 0)
    {
        logicalDotsPerInchY = QGuiApplication::screens().at(screenid)->logicalDotsPerInchY();
    }
    return logicalDotsPerInchY;
}

double QCatGrayScreenShot::physicalDotsPerInchX(int screenid) const
{
    double physicalDotsPerInchX = -1;
    if(QGuiApplication::screens().length() > screenid && screenid >= 0)
    {
        physicalDotsPerInchX = QGuiApplication::screens().at(screenid)->physicalDotsPerInchX();
    }
    return physicalDotsPerInchX;
}

double QCatGrayScreenShot::physicalDotsPerInchY(int screenid) const
{
    double physicalDotsPerInchY = -1;
    if(QGuiApplication::screens().length() > screenid && screenid >= 0)
    {
        physicalDotsPerInchY = QGuiApplication::screens().at(screenid)->physicalDotsPerInchY();
    }
    return physicalDotsPerInchY;
}

double QCatGrayScreenShot::devicePixelRatio(int screenid) const
{
    double devicePixelRatio = -1;
    if(QGuiApplication::screens().length() > screenid && screenid >= 0)
    {
        devicePixelRatio = QGuiApplication::screens().at(screenid)->devicePixelRatio();
    }
    return devicePixelRatio;
}


int QCatGrayScreenShot::depth(int screenid) const
{
    int depth = -1;
    if(QGuiApplication::screens().length() > screenid && screenid >= 0)
    {
        depth = QGuiApplication::screens().at(screenid)->depth();
    }
    return depth;
}

