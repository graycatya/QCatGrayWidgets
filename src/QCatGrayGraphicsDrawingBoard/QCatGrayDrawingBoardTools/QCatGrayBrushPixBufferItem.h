#pragma once

#include <QGraphicsPixmapItem>

#include <QPainter>

#include "QCatGrayBrushObject.h"

class QCatGrayBrushPixBufferItem : public QGraphicsPixmapItem
{
public:
    explicit QCatGrayBrushPixBufferItem(QGraphicsItem *parent = nullptr);
    ~QCatGrayBrushPixBufferItem();

    void Clear();
    void DrawToBuffer(QCatGrayBrushObject *object);

    void InitSizeRect(QRectF size);
    void UpdateSizeRect(QRectF size);

protected:
    QRectF boundingRect() const;

private:
    void InitProperty();
    void InitBrush();

private:
    QRectF m_ySizeRect;
    QRectF m_yLastSizeRect;

    QPixmap *m_pBufferBrush;
    QPainter *m_pBufferPainter;
};


