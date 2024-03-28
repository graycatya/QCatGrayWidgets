#include "QCatGrayScreenShotsToolBackdrop.h"
#include <QPainter>


QCatGrayScreenShotsToolBackdrop::QCatGrayScreenShotsToolBackdrop(QWidget *parent)
    : QWidget(parent)
{

}

QCatGrayScreenShotsToolBackdrop::~QCatGrayScreenShotsToolBackdrop()
{

}

QTransform QCatGrayScreenShotsToolBackdrop::getTransform() const
{
    return m_Transform;
}

void QCatGrayScreenShotsToolBackdrop::setBackdrop(QPixmap* pixmap)
{
    m_Backdrop = pixmap;
}

void QCatGrayScreenShotsToolBackdrop::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    if(m_Backdrop)
    {
        if(!m_Backdrop->isNull())
        {
            QPainter painter(this);
            QImage image(m_Backdrop->toImage());

            painter.drawImage(0, 0, image);
            m_Transform = painter.transform();
        }
    }
}
