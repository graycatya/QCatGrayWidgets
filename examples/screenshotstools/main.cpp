#include <QApplication>

#include "QCatGrayScreenShotsTools.h"

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QCoreApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Round);
#endif

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
