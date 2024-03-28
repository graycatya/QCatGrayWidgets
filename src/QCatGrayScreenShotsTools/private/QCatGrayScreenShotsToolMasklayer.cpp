#include "QCatGrayScreenShotsToolMasklayer.h"

#include <QPainter>

void moveUpdateMasklayerBoundingRect(QCatGrayScreenShotsToolMasklayer *masklayer)
{
    QRectF rectF = QRectF(masklayer->x(), masklayer->y(),
                          masklayer->boundingRect().width(),
                          masklayer->boundingRect().height());
    masklayer->setBoundingRect(rectF);
}

QCatGrayScreenShotsToolMasklayer::QCatGrayScreenShotsToolMasklayer()
{
    InitProperty();
    InitConnect();
}

QCatGrayScreenShotsToolMasklayer::~QCatGrayScreenShotsToolMasklayer()
{

}

void QCatGrayScreenShotsToolMasklayer::setBoundingRect(QRectF rect)
{
    if(m_BoundingRect != rect)
    {
        m_BoundingRect = rect;
        emit boundingRectChanged();
    }
}

QRectF QCatGrayScreenShotsToolMasklayer::boundingRect() const
{
    return m_BoundingRect;
}

void QCatGrayScreenShotsToolMasklayer::setMasklayerColor(QColor color)
{
    if(m_MasklayerColor != color)
    {
        m_MasklayerColor = color;
        emit masklayerColorChanged();
    }
}

QColor QCatGrayScreenShotsToolMasklayer::masklayerColor() const
{
    return m_MasklayerColor;
}

void QCatGrayScreenShotsToolMasklayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    painter->setBrush(m_MasklayerColor);
    painter->fillRect(0, 0, boundingRect().width(), boundingRect().height(), m_MasklayerColor);
}

QPainterPath QCatGrayScreenShotsToolMasklayer::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void QCatGrayScreenShotsToolMasklayer::InitProperty()
{

}

void QCatGrayScreenShotsToolMasklayer::InitConnect()
{
    connect(this, &QCatGrayScreenShotsToolMasklayer::xChanged, this, [=](){
        moveUpdateMasklayerBoundingRect(this);
    });
    connect(this, &QCatGrayScreenShotsToolMasklayer::xChanged, this, [=](){
        moveUpdateMasklayerBoundingRect(this);
    });
}
