#pragma once

#include <QObject>
#include "QCatGrayScreenShotBase.h"

class QCatGrayScreenShot : public QObject, public QCatGrayScreenShotBase
{
    Q_OBJECT
public:
    explicit QCatGrayScreenShot(QObject *parent = nullptr);
    ~QCatGrayScreenShot();

    void* getScreenShot(int screenid,
                        int x, int y,
                        int width, int height,
                        int winid = 0) const;

    double logicalDotsPerInchX(int screenid) const;
    double logicalDotsPerInchY(int screenid) const;
    double physicalDotsPerInchX(int screenid) const;
    double physicalDotsPerInchY(int screenid) const;
    double devicePixelRatio(int screenid) const;
    int depth(int screenid) const;

};

