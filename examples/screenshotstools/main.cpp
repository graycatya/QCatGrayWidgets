#include <QApplication>

#include "QCatGrayScreenShotsTools.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCatGrayScreenShotsTools w;
    w.setMasklayerColor(QColor(0, 0, 0, 199));

    w.setBorderColor(Qt::red);
    w.setBorderWidth(5);
    w.setRectRadius(250);
    w.setScreeningMode(QCatGrayScreenShotsTools::MAGNIFYINGGLASS_MODE);
    w.setFilterBoxMovable(true);
    w.setBoundingRect(QRectF(100,100,
                              500,
                              500));
    w.showFullScreen();
    return a.exec();
}
