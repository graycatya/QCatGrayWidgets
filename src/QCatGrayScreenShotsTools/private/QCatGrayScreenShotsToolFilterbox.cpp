#include "QCatGrayScreenShotsToolFilterbox.h"

#include <QPainter>
#include <QWidget>


QCatGrayScreenShotsToolFilterbox::QCatGrayScreenShotsToolFilterbox()
{
    InitProperty();
    InitConnect();
}

QCatGrayScreenShotsToolFilterbox::~QCatGrayScreenShotsToolFilterbox()
{

}

void QCatGrayScreenShotsToolFilterbox::setBoundingRect(QRectF rect)
{
    if(m_BoundingRect.width() != rect.width()
        || m_BoundingRect.height() != rect.height()
        || x() != rect.x()
        || y() != rect.y())
    {
        this->setPos(QPointF(rect.topLeft()));
        m_BoundingRect.setTopLeft(QPointF(0, 0));
        m_BoundingRect.setSize(rect.size());
        m_BoundingRect = rect;
        emit boundingRectChanged();
    }
}

QRectF QCatGrayScreenShotsToolFilterbox::boundingRect() const
{
    return m_BoundingRect;
}

void QCatGrayScreenShotsToolFilterbox::setBorderColor(QColor color)
{
    if(m_BorderColor != color)
    {
        m_BorderColor = color;
        emit borderColorChanged();
    }
}

QColor QCatGrayScreenShotsToolFilterbox::borderColor() const
{
    return  m_BorderColor;
}

void QCatGrayScreenShotsToolFilterbox::setBorderWidth(qreal width)
{
    if(m_BorderWidth != width)
    {
        m_BorderWidth = width;
        emit borderWidthChanged();
    }
}

qreal QCatGrayScreenShotsToolFilterbox::borderWidth() const
{
    return m_BorderWidth;
}

void QCatGrayScreenShotsToolFilterbox::setBackdropWidget(QWidget *widget)
{
    if(m_BackdropWidget != widget)
    {
        m_BackdropWidget = widget;
    }
}

QWidget *QCatGrayScreenShotsToolFilterbox::backdropWidget() const
{
    return m_BackdropWidget;
}

void QCatGrayScreenShotsToolFilterbox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)


    if(m_BackdropWidget)
    {
        painter->setPen(QPen(m_BorderColor, m_BorderWidth));
        QPixmap pixmap(boundingRect().width(), boundingRect().height());
        m_BackdropWidget->render(&pixmap, QPoint(0,0), boundingRect().toRect());

        QBrush brush(pixmap);
        painter->setBrush(brush);
        painter->drawRoundedRect(QRect(0,0,boundingRect().width(), boundingRect().height()), 0, 0);
    }
}

QPainterPath QCatGrayScreenShotsToolFilterbox::shape() const
{
    QPainterPath path;
    path.addRoundedRect(boundingRect(),
                        boundingRect().width()/2,
                        boundingRect().height()/2);
    return path;
}

void QCatGrayScreenShotsToolFilterbox::InitProperty()
{

}

void QCatGrayScreenShotsToolFilterbox::InitConnect()
{

}
