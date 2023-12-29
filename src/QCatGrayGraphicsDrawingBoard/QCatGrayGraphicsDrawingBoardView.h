#pragma once

#include <QGraphicsView>

class QCatGrayGraphicsDrawingBoardView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QCatGrayGraphicsDrawingBoardView(QWidget *parent = nullptr);
    ~QCatGrayGraphicsDrawingBoardView();

    void ScaleZoomIn();
    void ScaleZoomOut();
    void Reset();

private:
    void InitProperty();
    void InitConnect();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPointF lastPoint;
    QPointF endPoint;
    bool m_bPress;

};

