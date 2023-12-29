#pragma once

#include <QGraphicsScene>
#include <QTouchEvent>

#include "QCatGrayGraphicsDrawingBoardObject.h"

class QCatGrayGraphicsDrawingBoardView;
class QCatGrayTeachingToolCompass;
class QCatGrayTeachingToolProtractor;
class QCatGrayTeachingToolRuler;
class QCatGrayTeachingToolTrangle;

class QCatGrayBrushPixItem;

class QCatGrayBrushArcBufferItem;

class QCatGrayGraphicsDrawingBoardScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit QCatGrayGraphicsDrawingBoardScene(QObject *parent = nullptr);
    ~QCatGrayGraphicsDrawingBoardScene();

    void InitProperty();

    void SetView(QCatGrayGraphicsDrawingBoardView *view);
    QCatGrayGraphicsDrawingBoardView *View( void );


    void AddTeachingToolProtractor();
    void AddTeachingToolRuler();
    void AddTeachingToolTrangle();
    void AddTeachingToolCompass();

    void Clear();

    void mousePressEventPenState(QPointF &point);
    void mouseMoveEventPenState(QPointF &lastpoint, QPointF &point);
    void mouseReleaseEventPenState(QPointF &point);

private:

    void mousePressEventPenState(QGraphicsSceneMouseEvent *event);
    void mouseMoveEventPenState(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEventPenState(QGraphicsSceneMouseEvent *event);

protected:
    bool event(QEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    bool touchEvent(QTouchEvent *event);
    bool scenePress(int id, const QPointF &pos);
    bool sceneMove(int id, const QPointF &presspos, const QPointF &pos);
    bool sceneRelease(int id, const QPointF &pos);

public slots:
    void On_DrawingBoard_SelectState();
    void On_DrawingBoard_PenState();
    void On_DrawingBoard_EraserState();

private:
    QCatGrayGraphicsDrawingBoardView *m_yView;
    QVector<QCatGrayTeachingToolCompass*> m_pTeachingToolCompass;
    QVector<QCatGrayTeachingToolProtractor*> m_pTeachingToolProtractor;
    QVector<QCatGrayTeachingToolRuler*> m_pTeachingToolRuler;
    QVector<QCatGrayTeachingToolTrangle*> m_pTeachingToolTrangle;
    QCatGrayBrushPixItem *m_pCatBrushPixItem;


    QCatGrayGraphicsDrawingBoardObject *m_pCatGraphicsObject;

    bool m_bMousePress;
    QPointF m_yLastTeachingPoint;

    QCatGrayBrushArcBufferItem *m_pCatBrushArcBufferItem;
};


