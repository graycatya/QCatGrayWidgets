#include "QCatGrayScreenShotsToolView.h"
#include <QDebug>

QCatGrayScreenShotsToolView::QCatGrayScreenShotsToolView(QWidget *parent)
    : QGraphicsView(parent)
{
    this->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    this->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

QCatGrayScreenShotsToolView::QCatGrayScreenShotsToolView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    this->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

QCatGrayScreenShotsToolView::~QCatGrayScreenShotsToolView()
{

}

void QCatGrayScreenShotsToolView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

void QCatGrayScreenShotsToolView::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << "QCatGrayScreenShotsToolView mouseMoveEvent";
    QGraphicsView::mouseMoveEvent(event);
}

void QCatGrayScreenShotsToolView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}
