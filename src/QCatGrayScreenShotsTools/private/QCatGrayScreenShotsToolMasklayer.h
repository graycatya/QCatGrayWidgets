#pragma once

#include <QGraphicsObject>


class QCatGrayScreenShotsToolMasklayer : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QRectF boundingRect READ boundingRect WRITE setBoundingRect NOTIFY boundingRectChanged)
    Q_PROPERTY(QColor masklayerColor READ masklayerColor WRITE setMasklayerColor NOTIFY masklayerColorChanged FINAL)
public:
    QCatGrayScreenShotsToolMasklayer();
    ~QCatGrayScreenShotsToolMasklayer();

    void setBoundingRect(QRectF rect);
    QRectF boundingRect() const;

    void setMasklayerColor(QColor color);
    QColor masklayerColor() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QPainterPath shape() const;

private:
    void InitProperty();
    void InitConnect();

signals:
    void boundingRectChanged();
    void masklayerColorChanged();

private:
    QRectF m_BoundingRect = QRectF(0, 0, 0, 0);
    QColor m_MasklayerColor = QColor(0, 0, 0, 0);;

};
