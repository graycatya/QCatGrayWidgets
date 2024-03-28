#include "QCatGrayScreenShotsToolScene.h"


QCatGrayScreenShotsToolScene::QCatGrayScreenShotsToolScene(QObject *parent)
    : QGraphicsScene(parent)
{

}

QCatGrayScreenShotsToolScene::QCatGrayScreenShotsToolScene(const QRectF &sceneRect, QObject *parent)
    : QGraphicsScene(sceneRect, parent)
{

}

QCatGrayScreenShotsToolScene::QCatGrayScreenShotsToolScene(qreal x, qreal y, qreal width, qreal height, QObject *parent)
    : QGraphicsScene(x, y, width, height, parent)
{

}

QCatGrayScreenShotsToolScene::~QCatGrayScreenShotsToolScene()
{

}
