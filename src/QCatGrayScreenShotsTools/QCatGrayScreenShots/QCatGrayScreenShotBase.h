#pragma once


class QCatGrayScreenShotBase
{

public:
    QCatGrayScreenShotBase();
    virtual ~QCatGrayScreenShotBase();

    virtual void* getScreenShot(int screenid,
                                int x, int y,
                                int width, int height, int winid = 0) const = 0;

    virtual double logicalDotsPerInchX(int screenid) const = 0;
    virtual double logicalDotsPerInchY(int screenid) const = 0;
    virtual double physicalDotsPerInchX(int screenid) const = 0;
    virtual double physicalDotsPerInchY(int screenid) const = 0;
    virtual double devicePixelRatio(int screenid) const = 0;
    virtual int depth(int screenid) const = 0;

private:


};
