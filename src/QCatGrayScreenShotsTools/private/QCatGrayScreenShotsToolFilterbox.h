#pragma once

#include <QGraphicsObject>

class QWidget;

class QCatGrayScreenShotsToolFilterbox : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QRectF boundingRect READ boundingRect WRITE setBoundingRect NOTIFY boundingRectChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(qreal borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged)
public:
    QCatGrayScreenShotsToolFilterbox();
    ~QCatGrayScreenShotsToolFilterbox();

    void setBoundingRect(QRectF rect);
    QRectF boundingRect() const;

    void setBorderColor(QColor color);
    QColor borderColor() const;

    void setBorderWidth(qreal width);
    qreal borderWidth() const;

    void setBackdropWidget(QWidget *widget);
    QWidget *backdropWidget() const;


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QPainterPath shape() const;
private:
    void InitProperty();
    void InitConnect();

signals:
    void boundingRectChanged();
    void borderColorChanged();
    void borderWidthChanged();

private:
    QRectF m_BoundingRect = QRectF(0, 0, 0, 0);
    QColor m_BorderColor = QColor(0, 0, 0, 0);
    qreal m_BorderWidth = 0;
    QWidget *m_BackdropWidget = nullptr;
};
