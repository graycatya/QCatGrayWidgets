#include <QApplication>

#include "QCatGrayScreenShotsTools.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCatGrayScreenShotsTools w;
    w.showFullScreen();
    return a.exec();
}
