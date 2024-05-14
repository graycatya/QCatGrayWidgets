#include "QCatGrayGraphicsDrawingBoardScene.h"
#include "QCatGrayTeachingTools/QCatGrayTeachingToolCompass.h"
#include "QCatGrayTeachingTools/QCatGrayTeachingToolProtractor.h"
#include "QCatGrayTeachingTools/QCatGrayTeachingToolRuler.h"
#include "QCatGrayTeachingTools/QCatGrayTeachingToolTrangle.h"
#include "QCatGrayGraphicsDrawingBoardView.h"

#include "QCatGrayDrawingBoardTools/QCatGrayBrushPixItem.h"
#include "QCatGrayDrawingBoardTools/QCatGrayBrushArcBufferItem.h"

#include <QGraphicsSceneMouseEvent>
#include <QPixmapCache>
#include <QDebug>
#include <QTimer>
#include <QSvgRenderer>
#include <QSvgGenerator>

QGraphicsView* GetView(QGraphicsScene* scene)
{
    Q_INIT_RESOURCE(QCatGrayTeachingTools);
    return dynamic_cast<QCatGrayGraphicsDrawingBoardScene*>(scene)->View();
}


QCatGrayGraphicsDrawingBoardScene::QCatGrayGraphicsDrawingBoardScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_yView(nullptr)
    , m_pCatGraphicsObject(new QCatGrayGraphicsDrawingBoardObject(this))
{
    m_pCatBrushArcBufferItem = nullptr;
    //InitProperty();
}

QCatGrayGraphicsDrawingBoardScene::~QCatGrayGraphicsDrawingBoardScene()
{

}

void QCatGrayGraphicsDrawingBoardScene::SetView(QCatGrayGraphicsDrawingBoardView *view)
{
    m_yView = view;
}

QCatGrayGraphicsDrawingBoardView *QCatGrayGraphicsDrawingBoardScene::View()
{
    return m_yView;
}


void QCatGrayGraphicsDrawingBoardScene::AddTeachingToolProtractor()
{
    QCatGrayTeachingToolProtractor *Teaching = new QCatGrayTeachingToolProtractor;
    this->addItem(Teaching);
    m_pTeachingToolProtractor.push_back(Teaching);
    if(m_pCatGraphicsObject->GetDrawingBoardState() == QCatGrayGraphicsDrawingBoardObject::PEN
            || m_pCatGraphicsObject->GetDrawingBoardState() == QCatGrayGraphicsDrawingBoardObject::ERASER)
    {
        Teaching->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_DORMANCY);
    }
}

void QCatGrayGraphicsDrawingBoardScene::AddTeachingToolRuler()
{
    QCatGrayTeachingToolRuler *Teaching = new QCatGrayTeachingToolRuler;
    Teaching->SetCurrentView(GetView);
    this->addItem(Teaching);
    m_pTeachingToolRuler.push_back(Teaching);
    connect(Teaching, &QCatGrayAbsTeachingTool::HoverEntered, this, [=](){
        m_pCatGraphicsObject->SetDrawingBoardState(QCatGrayGraphicsDrawingBoardObject::CAT_DRAWINGBOARD_STATE::TeachingPen);
    });
    connect(Teaching, &QCatGrayAbsTeachingTool::HoverLeaveed, this, [=](){
        m_pCatGraphicsObject->SetDrawingBoardState(m_pCatGraphicsObject->GetLastDrawingBoardState());
    });
    connect(Teaching, &QCatGrayAbsTeachingTool::LineStartPos, this, [=](QPointF point){
        m_pCatBrushPixItem->DrawPress(1, point);
        m_yLastTeachingPoint = point;
    });
    connect(Teaching, &QCatGrayAbsTeachingTool::LineUpdatePos, this, [=](QPointF point){
        m_pCatBrushPixItem->DrawMove(1, m_yLastTeachingPoint, point);
        m_yLastTeachingPoint = point;
    });
    connect(Teaching, &QCatGrayAbsTeachingTool::LineEnd, this, [=](QPointF point){
        m_pCatBrushPixItem->DrawRelease(1, point);
        m_yLastTeachingPoint = point;
    });
    if(m_pCatGraphicsObject->GetDrawingBoardState() == QCatGrayGraphicsDrawingBoardObject::PEN)
    {
        Teaching->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_PEN);
    }
    if(m_pCatGraphicsObject->GetDrawingBoardState() == QCatGrayGraphicsDrawingBoardObject::ERASER)
    {
        Teaching->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_DORMANCY);
    }
}

void QCatGrayGraphicsDrawingBoardScene::AddTeachingToolTrangle()
{
    QCatGrayTeachingToolTrangle *Teaching = new QCatGrayTeachingToolTrangle;
    this->addItem(Teaching);
    Teaching->SetCurrentView(GetView);
    m_pTeachingToolTrangle.push_back(Teaching);
    connect(Teaching, &QCatGrayAbsTeachingTool::HoverEntered, this, [=](){
        m_pCatGraphicsObject->SetDrawingBoardState(QCatGrayGraphicsDrawingBoardObject::CAT_DRAWINGBOARD_STATE::TeachingPen);
    });
    connect(Teaching, &QCatGrayAbsTeachingTool::HoverLeaveed, this, [=](){
        m_pCatGraphicsObject->SetDrawingBoardState(m_pCatGraphicsObject->GetLastDrawingBoardState());
    });
    connect(Teaching, &QCatGrayAbsTeachingTool::LineStartPos, this, [=](QPointF point){
        m_pCatBrushPixItem->DrawPress(1, point);
        m_yLastTeachingPoint = point;
    });
    connect(Teaching, &QCatGrayAbsTeachingTool::LineUpdatePos, this, [=](QPointF point){
        m_pCatBrushPixItem->DrawMove(1, m_yLastTeachingPoint, point);
        m_yLastTeachingPoint = point;
    });
    connect(Teaching, &QCatGrayAbsTeachingTool::LineEnd, this, [=](QPointF point){
        m_pCatBrushPixItem->DrawRelease(1, point);
        m_yLastTeachingPoint = point;
    });
    if(m_pCatGraphicsObject->GetDrawingBoardState() == QCatGrayGraphicsDrawingBoardObject::PEN)
    {
        Teaching->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_PEN);
    }
    if(m_pCatGraphicsObject->GetDrawingBoardState() == QCatGrayGraphicsDrawingBoardObject::ERASER)
    {
        Teaching->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_DORMANCY);
    }
}

void QCatGrayGraphicsDrawingBoardScene::AddTeachingToolCompass()
{
    QCatGrayTeachingToolCompass *Teaching = new QCatGrayTeachingToolCompass;
    this->addItem(Teaching);
    m_pTeachingToolCompass.push_back(Teaching);
    connect(Teaching, &QCatGrayAbsTeachingTool::HoverEntered, this, [=](){
        //qDebug() << "compass hover";
        m_pCatGraphicsObject->SetDrawingBoardState(QCatGrayGraphicsDrawingBoardObject::CAT_DRAWINGBOARD_STATE::TeachingPen);
    });
    connect(Teaching, &QCatGrayAbsTeachingTool::HoverLeaveed, this, [=](){
        m_pCatGraphicsObject->SetDrawingBoardState(m_pCatGraphicsObject->GetLastDrawingBoardState());
    });
    connect(Teaching, &QCatGrayAbsTeachingTool::ArcStart, this, [=](QRectF rect, qreal startAngle){
        m_pCatBrushArcBufferItem = new QCatGrayBrushArcBufferItem();
        m_pCatBrushArcBufferItem->SetProperty(Qt::red, 5);
        m_pCatBrushArcBufferItem->ArcStart(rect, startAngle * 16);
        this->addItem(m_pCatBrushArcBufferItem);
    });
    connect(Teaching, &QCatGrayAbsTeachingTool::ArcUpdate, this, [=](qreal updateAngle){
        m_pCatBrushArcBufferItem->ArcUpdate(updateAngle * 16);
    });
    connect(Teaching, &QCatGrayAbsTeachingTool::ArcEnd, this, [=](){
        m_pCatBrushPixItem->DrawArcPress(m_pCatBrushArcBufferItem->GetRectF(),
                                         m_pCatBrushArcBufferItem->GetStartAngle(),
                                         m_pCatBrushArcBufferItem->GetUpdateAngle());
        this->removeItem(m_pCatBrushArcBufferItem);
        m_pCatBrushArcBufferItem = nullptr;
    });
    if(m_pCatGraphicsObject->GetDrawingBoardState() == QCatGrayGraphicsDrawingBoardObject::PEN)
    {
        Teaching->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_PEN);
        Teaching->update();
    }
    if(m_pCatGraphicsObject->GetDrawingBoardState() == QCatGrayGraphicsDrawingBoardObject::ERASER)
    {
        Teaching->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_DORMANCY);
    }
}

void QCatGrayGraphicsDrawingBoardScene::Clear()
{
    this->clear();
    m_pTeachingToolCompass.clear();
    m_pTeachingToolProtractor.clear();
    m_pTeachingToolRuler.clear();
    m_pTeachingToolTrangle.clear();

    m_pCatBrushPixItem = nullptr;
    m_pCatBrushPixItem = new QCatGrayBrushPixItem();
    //m_pCatBrushPixItem->SetBackgroundColor(Qt::transparent);
    m_pCatBrushPixItem->SetBrushSize(this->sceneRect());

    this->addItem(m_pCatBrushPixItem);
    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case QCatGrayGraphicsDrawingBoardObject::PEN:
        {
            m_pCatBrushPixItem->SetMode(QCatGrayBrushObject::BrushMode::PenBrushMode);
            break;
        }
        case QCatGrayGraphicsDrawingBoardObject::ERASER:
        {
            m_pCatBrushPixItem->SetMode(QCatGrayBrushObject::BrushMode::EraserMode);
            break;
        }
        default:
        {
            break;
        }
    }


}

void QCatGrayGraphicsDrawingBoardScene::mousePressEventPenState(QPointF &point)
{
    m_bMousePress = true;
    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case QCatGrayGraphicsDrawingBoardObject::PEN:
        case QCatGrayGraphicsDrawingBoardObject::ERASER:
        {
            scenePress(1,point);
            update();
        }
        default:
        {
            break;
        }
    }
}

void QCatGrayGraphicsDrawingBoardScene::mouseMoveEventPenState(QPointF &lastpoint, QPointF &point)
{
    if(m_bMousePress)
    {
        switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
            case QCatGrayGraphicsDrawingBoardObject::PEN:
            case QCatGrayGraphicsDrawingBoardObject::ERASER:
            {
                sceneMove(1, lastpoint, point);
                update();
            }
            default:
            {
                break;
            }
        }
    }

}

void QCatGrayGraphicsDrawingBoardScene::mouseReleaseEventPenState(QPointF &point)
{
    m_bMousePress = false;

    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case QCatGrayGraphicsDrawingBoardObject::PEN:
        case QCatGrayGraphicsDrawingBoardObject::ERASER:
        {
            sceneRelease(1, point);
            update();
        }
        default:
        {
            break;
        }
    }

}

void QCatGrayGraphicsDrawingBoardScene::InitProperty()
{
    m_pCatGraphicsObject->SetDrawingBoardState(QCatGrayGraphicsDrawingBoardObject::SELECT);

    m_pCatBrushPixItem = new QCatGrayBrushPixItem();
    //m_pCatBrushPixItem->SetBackgroundColor(Qt::transparent);
    m_pCatBrushPixItem->SetBrushSize(this->sceneRect());
    this->addItem(m_pCatBrushPixItem);
    //QPixmapCache::setCacheLimit(204800);

    m_bMousePress = false;
}

void QCatGrayGraphicsDrawingBoardScene::mousePressEventPenState(QGraphicsSceneMouseEvent *event)
{
    m_bMousePress = true;
    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case QCatGrayGraphicsDrawingBoardObject::PEN:
        case QCatGrayGraphicsDrawingBoardObject::ERASER:
        {
            scenePress(1,event->scenePos());
        }
        default:
        {
            break;
        }
    }
    if(m_pCatGraphicsObject->GetDrawingBoardState() == QCatGrayGraphicsDrawingBoardObject::PEN)
    {
        View()->setCursor(QCursor(Qt::CrossCursor));
    }
    QGraphicsScene::mousePressEvent(event);
}

void QCatGrayGraphicsDrawingBoardScene::mouseMoveEventPenState(QGraphicsSceneMouseEvent *event)
{
    if(m_bMousePress)
    {
        switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
            case QCatGrayGraphicsDrawingBoardObject::PEN:
            case QCatGrayGraphicsDrawingBoardObject::ERASER:
            {
                sceneMove(1, event->lastScenePos(), event->scenePos());
            }
            default:
            {
                break;
            }
        }
        if(m_pCatGraphicsObject->GetDrawingBoardState() == QCatGrayGraphicsDrawingBoardObject::PEN)
        {
            View()->setCursor(QCursor(Qt::CrossCursor));
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void QCatGrayGraphicsDrawingBoardScene::mouseReleaseEventPenState(QGraphicsSceneMouseEvent *event)
{
    m_bMousePress = false;

    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case QCatGrayGraphicsDrawingBoardObject::PEN:
        case QCatGrayGraphicsDrawingBoardObject::ERASER:
        {
            sceneRelease(1, event->scenePos());
        }
        default:
        {
            break;
        }
    }
    if(m_pCatGraphicsObject->GetDrawingBoardState() == QCatGrayGraphicsDrawingBoardObject::PEN)
    {
        View()->setCursor(QCursor(Qt::ArrowCursor));
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

bool QCatGrayGraphicsDrawingBoardScene::event(QEvent *event)
{
    switch (event->type())
    {
        case QEvent::TouchEnd:
        case QEvent::TouchBegin:
        case QEvent::TouchUpdate:
        {
            if(touchEvent(static_cast<QTouchEvent*>(event)))
            {
                return true;
            }
            break;
        }
        default: break;
    }
    return QGraphicsScene::event(event);
}

void QCatGrayGraphicsDrawingBoardScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_bMousePress = true;
    QGraphicsScene::mousePressEvent(event);
    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case QCatGrayGraphicsDrawingBoardObject::CAT_DRAWINGBOARD_STATE::PEN:
        case QCatGrayGraphicsDrawingBoardObject::CAT_DRAWINGBOARD_STATE::ERASER:
        {
            mousePressEventPenState(event);
            break;
        }
        default: {
            break;
        }
    }
    //this->update();
}

void QCatGrayGraphicsDrawingBoardScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case QCatGrayGraphicsDrawingBoardObject::CAT_DRAWINGBOARD_STATE::PEN:
        case QCatGrayGraphicsDrawingBoardObject::CAT_DRAWINGBOARD_STATE::ERASER:
        {
            mouseMoveEventPenState(event);
            break;
        }
        default: {
            break;
        }
    }
    //this->update();
}

void QCatGrayGraphicsDrawingBoardScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_bMousePress = false;
    QGraphicsScene::mouseReleaseEvent(event);
    switch (m_pCatGraphicsObject->GetDrawingBoardState()) {
        case QCatGrayGraphicsDrawingBoardObject::CAT_DRAWINGBOARD_STATE::PEN:
        case QCatGrayGraphicsDrawingBoardObject::CAT_DRAWINGBOARD_STATE::ERASER:
        {
            mouseReleaseEventPenState(event);
            break;
        }
        default: {
            break;
        }
    }
}

bool QCatGrayGraphicsDrawingBoardScene::touchEvent(QTouchEvent *event)
{
    Q_UNUSED(event)
    bool rel = true;
    return rel;
}

bool QCatGrayGraphicsDrawingBoardScene::scenePress(int id, const QPointF &pos)
{
    m_pCatBrushPixItem->DrawPress(id, pos);
    return true;
}

bool QCatGrayGraphicsDrawingBoardScene::sceneMove(int id, const QPointF &presspos, const QPointF &pos)
{
    m_pCatBrushPixItem->DrawMove(id, presspos, pos);
    return true;
}

bool QCatGrayGraphicsDrawingBoardScene::sceneRelease(int id, const QPointF &pos)
{
    m_pCatBrushPixItem->DrawRelease(id, pos);
    return true;
}

void QCatGrayGraphicsDrawingBoardScene::On_DrawingBoard_SelectState()
{
    m_pCatGraphicsObject->SetDrawingBoardState(QCatGrayGraphicsDrawingBoardObject::SELECT);
    foreach(auto temp, m_pTeachingToolCompass)
    {
        temp->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_NONE);
    }
    foreach(auto temp, m_pTeachingToolProtractor)
    {
        temp->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_NONE);
    }
    foreach(auto temp, m_pTeachingToolRuler)
    {
        temp->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_NONE);
    }
    foreach(auto temp, m_pTeachingToolTrangle)
    {
        temp->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_NONE);
    }
}

void QCatGrayGraphicsDrawingBoardScene::On_DrawingBoard_PenState()
{
    m_pCatGraphicsObject->SetDrawingBoardState(QCatGrayGraphicsDrawingBoardObject::PEN);
    m_pCatBrushPixItem->SetMode(QCatGrayBrushObject::BrushMode::PenBrushMode);
    foreach(auto temp, m_pTeachingToolCompass)
    {
        temp->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_PEN);
    }
    foreach(auto temp, m_pTeachingToolProtractor)
    {
        temp->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_DORMANCY);
    }
    foreach(auto temp, m_pTeachingToolRuler)
    {
        temp->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_PEN);
    }
    foreach(auto temp, m_pTeachingToolTrangle)
    {
        temp->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_PEN);
    }
}

void QCatGrayGraphicsDrawingBoardScene::On_DrawingBoard_EraserState()
{
    m_pCatGraphicsObject->SetDrawingBoardState(QCatGrayGraphicsDrawingBoardObject::ERASER);
    m_pCatBrushPixItem->SetMode(QCatGrayBrushObject::BrushMode::EraserMode);
    foreach(auto temp, m_pTeachingToolCompass)
    {
        temp->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_NONE);
    }
    foreach(auto temp, m_pTeachingToolProtractor)
    {
        temp->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_NONE);
    }
    foreach(auto temp, m_pTeachingToolRuler)
    {
        temp->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_NONE);
    }
    foreach(auto temp, m_pTeachingToolTrangle)
    {
        temp->SetState(QCatGrayAbsTeachingTool::TEAHINGTOOL_STATE_NONE);
    }
}
