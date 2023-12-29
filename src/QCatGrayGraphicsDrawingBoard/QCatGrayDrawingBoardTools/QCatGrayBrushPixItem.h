#pragma once

#include <QGraphicsPixmapItem>

#include "QCatGrayBrushObject.h"
#include "QCatGrayBrushPixBufferItem.h"

class QCatGrayBrushPixItem : public QGraphicsPixmapItem
{
public:
    explicit QCatGrayBrushPixItem(QGraphicsItem *parent = nullptr);
    ~QCatGrayBrushPixItem();

    void DrawPress(int id,const QPointF &point);
    void DrawMove(int id,const QPointF &lastPoint,const QPointF &curPoint);
    void DrawRelease(int id, const QPointF &point);
    void DrawArcPress(const QRectF rect, qreal startangle, qreal updateangle);
    void SetBackgroundColor(const QColor & color);
    void SetMode(QCatGrayBrushObject::BrushMode mode);
    void SetBrushSize(QRectF size);

    void Clear();

protected:
    QRectF boundingRect() const;

private:
    void InitProperty();
    void DrawToReal(QCatGrayBrushObject* object);  //在真实层绘非矢量图
    void InitBrush();                    //初始化图层
    void DoErase(QPointF pos1, QPointF pos2, int width);    // 线擦除
    QPainterPath CreateStrokePath(const QPointF &pos1, const QPointF &pos2, int width);
    void UpdateRectSize(QPointF point);

private:
    QRectF m_ySizeRect;
    QRectF m_yLastSizeRect;

    QCatGrayBrushPixBufferItem *m_pCatBrushPixBufferItem;

    QPixmap *m_pRealBrush;
    QPainter *m_pRealPainter;

    QMap<int, QCatGrayBrushObject*> m_yBrushObjects;

    QColor m_yBgColor;

    QCatGrayBrushObject::BrushMode m_yBrushMode;

    bool m_bFixedSize;

};

