#include "QCatGrayShadowWidget.h"
#include <QtMath>
#include <QPainterPath>
#include <QPainter>
#include <QDebug>

QCatGrayShadowWidget::QCatGrayShadowWidget(QWidget *widget)
    : QWidget(widget)
{

}

QCatGrayShadowWidget::~QCatGrayShadowWidget()
{

}

void QCatGrayShadowWidget::SetShadowColor(QColor color)
{
    ShadowColor = color;
    update();
}

void QCatGrayShadowWidget::SetShadowWeight(int weight)
{
    ShadowWeight = weight;
    update();
}

void QCatGrayShadowWidget::SetShadowRadius(int radius)
{
    ShadowRadius = radius;
    update();
}

void QCatGrayShadowWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRoundedRect(ShadowWeight, ShadowWeight,
                 this->width()-ShadowWeight*2, this->height()-ShadowWeight*2, ShadowRadius, ShadowRadius);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color = ShadowColor;
    for(int i=0; i<ShadowWeight; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRoundedRect(ShadowWeight-i, ShadowWeight-i,
                     this->width()-(ShadowWeight-i)*2,
                     this->height()-(ShadowWeight-i)*2, ShadowRadius, ShadowRadius);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}

void QCatGrayShadowWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}
