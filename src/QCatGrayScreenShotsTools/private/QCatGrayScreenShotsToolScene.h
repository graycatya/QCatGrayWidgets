#pragma once


#include <QGraphicsScene>

class QCatGrayScreenShotsToolScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QCatGrayScreenShotsToolScene(QObject *parent = nullptr);
    QCatGrayScreenShotsToolScene(const QRectF &sceneRect, QObject *parent = nullptr);
    QCatGrayScreenShotsToolScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);
    ~QCatGrayScreenShotsToolScene();

private:

};
