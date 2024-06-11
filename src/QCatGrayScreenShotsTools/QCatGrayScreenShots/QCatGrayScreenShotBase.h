#pragma once
#include <QtCore>
#if (QT_VERSION > QT_VERSION_CHECK(6,0,0))
#include <QtTypes>
#endif

class QCatGrayScreenShotBase
{

public:
    QCatGrayScreenShotBase();
    virtual ~QCatGrayScreenShotBase();

    virtual void* getScreenShot(int screenid,
                                int x, int y,
                                int width, int height, qint64 winid = 0) const = 0;

    virtual double logicalDotsPerInchX(int screenid) const = 0;
    virtual double logicalDotsPerInchY(int screenid) const = 0;
    virtual double physicalDotsPerInchX(int screenid) const = 0;
    virtual double physicalDotsPerInchY(int screenid) const = 0;
    virtual double devicePixelRatio(int screenid) const = 0;
    virtual int depth(int screenid) const = 0;

private:


};
