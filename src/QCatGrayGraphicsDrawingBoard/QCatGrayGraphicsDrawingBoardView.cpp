#include "QCatGrayGraphicsDrawingBoardView.h"
#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsScale>
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
#include <QGLWidget>
#endif
#include <QGraphicsScene>
#include "QCatGrayGraphicsDrawingBoardScene.h"

QCatGrayGraphicsDrawingBoardView::QCatGrayGraphicsDrawingBoardView(QWidget *parent)
    : QGraphicsView(parent)
{
    InitProperty();
    InitConnect();
}

QCatGrayGraphicsDrawingBoardView::~QCatGrayGraphicsDrawingBoardView()
{

}

void QCatGrayGraphicsDrawingBoardView::ScaleZoomIn()
{

    scale(1.2, 1.2);
}

void QCatGrayGraphicsDrawingBoardView::ScaleZoomOut()
{

    scale(1 / 1.2, 1 / 1.2);
}

void QCatGrayGraphicsDrawingBoardView::Reset()
{
    //this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
    QMatrix q;
    q.setMatrix(1, matrix().m12(), matrix().m21(),1, matrix().dx(), matrix().dy());
    setMatrix(q,false);
#else
    resetTransform();
#endif
}

void QCatGrayGraphicsDrawingBoardView::InitProperty()
{
    //this->setDragMode(QGraphicsView::RubberBandDrag);
    m_bPress = false;
    scale(1.0 , 1.0);
    this->setCacheMode(QGraphicsView::CacheBackground);
}

void QCatGrayGraphicsDrawingBoardView::InitConnect()
{
    /*connect(scene(), &QGraphicsScene::sceneRectChanged, this, [=](const QRectF &rect){
        qDebug() << "scene Rect: " << rect;
    });*/
}

void QCatGrayGraphicsDrawingBoardView::mousePressEvent(QMouseEvent *event)
{
    m_bPress = true;
    /*QPointF point = this->mapToScene(event->pos());
    lastPoint = point;
    dynamic_cast<QCatGrayGraphicsDrawingBoardScene*>(this->scene())->mousePressEventPenState(point);*/
    QGraphicsView::mousePressEvent(event);
}

void QCatGrayGraphicsDrawingBoardView::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bPress)
    {
        //qDebug() << "QCatGrayGraphicsDrawingBoardView::mouseMoveEvent";
        /*QPointF point = this->mapToScene(event->pos());
        dynamic_cast<QCatGrayGraphicsDrawingBoardScene*>(this->scene())->mouseMoveEventPenState(lastPoint, point);
        lastPoint = point;*/
    }
    QGraphicsView::mouseMoveEvent(event);
}

void QCatGrayGraphicsDrawingBoardView::mouseReleaseEvent(QMouseEvent *event)
{
    m_bPress = false;
    /*QPointF point = this->mapToScene(event->pos());
    dynamic_cast<QCatGrayGraphicsDrawingBoardScene*>(this->scene())->mouseReleaseEventPenState(point);*/
    QGraphicsView::mouseReleaseEvent(event);
}
