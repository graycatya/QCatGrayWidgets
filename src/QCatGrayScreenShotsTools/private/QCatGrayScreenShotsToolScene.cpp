#include "QCatGrayScreenShotsToolScene.h"

#include <QDebug>

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


bool QCatGrayScreenShotsToolScene::event(QEvent *event)
{
    return QGraphicsScene::event(event);
}

void QCatGrayScreenShotsToolScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
}

void QCatGrayScreenShotsToolScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}

void QCatGrayScreenShotsToolScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}
