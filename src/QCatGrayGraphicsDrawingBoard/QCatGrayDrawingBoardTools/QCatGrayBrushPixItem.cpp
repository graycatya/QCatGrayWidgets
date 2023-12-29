#include "QCatGrayBrushPixItem.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QCursor>

#include <QDebug>

QCatGrayBrushPixItem::QCatGrayBrushPixItem(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    InitProperty();
    InitBrush();
}

QCatGrayBrushPixItem::~QCatGrayBrushPixItem()
{
    if(m_pRealPainter != nullptr)
    {
        delete m_pRealPainter;
        m_pRealPainter = nullptr;
    }

    if(m_pRealBrush != nullptr)
    {
        delete m_pRealBrush;
        m_pRealBrush = nullptr;
    }
}

void QCatGrayBrushPixItem::DrawPress(int id, const QPointF &point)
{
    if(!m_bFixedSize)
    {
        UpdateRectSize(point);
    }
    QCatGrayBrushObject *BrushObject = new QCatGrayBrushObject(point, this);
    BrushObject->AddToPath(point, point, this);
    m_yBrushObjects.insert(id, BrushObject);
    m_pCatBrushPixBufferItem->DrawToBuffer(BrushObject);

}

void QCatGrayBrushPixItem::DrawMove(int id, const QPointF &lastPoint, const QPointF &curPoint)
{
    QCatGrayBrushObject *BrushObject = m_yBrushObjects.value(id, nullptr);
    if(BrushObject == nullptr)
    {
        return;
    }
    if(!m_bFixedSize)
    {
        UpdateRectSize(curPoint);
    }
    /*if(BrushObject->ElementPixmapCount() > 100)
    {*/
        BrushObject->CreateNewPixmapPath();
    //}
    BrushObject->AddToPath(lastPoint, curPoint, this);

    if(m_yBrushMode == QCatGrayBrushObject::BrushMode::PenBrushMode)
    {

        DrawToReal(BrushObject);

    } else if(m_yBrushMode == QCatGrayBrushObject::BrushMode::EraserMode)
    {
        DoErase(lastPoint, curPoint, 30);
    }
}

void QCatGrayBrushPixItem::DrawRelease(int id, const QPointF &point)
{
    QCatGrayBrushObject *BrushObject = m_yBrushObjects.value(id, nullptr);
    if(BrushObject == nullptr)
    {
        return;
    }
    if(!m_bFixedSize)
    {
        UpdateRectSize(point);
    }
    BrushObject->AddToPath(point, point, this);

    if(m_yBrushMode == QCatGrayBrushObject::BrushMode::PenBrushMode)
    {
        DrawToReal(BrushObject);

    } else if(m_yBrushMode == QCatGrayBrushObject::BrushMode::EraserMode)
    {
        DoErase(point, point, 30);
    }

    m_yBrushObjects.remove(id);
    delete BrushObject;
    BrushObject = nullptr;
}

void QCatGrayBrushPixItem::DrawArcPress(const QRectF rect, qreal startangle, qreal updateangle)
{
    if(m_pRealPainter != nullptr && m_pCatBrushPixBufferItem != nullptr)
    {

        m_pRealPainter->setCompositionMode(QPainter::CompositionMode_Source);
        m_pRealPainter->setRenderHint(QPainter::Antialiasing, true);
        m_pRealPainter->setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        //QPainterPath path = object->StrokePixmapPath(5);
        QPointF point = rect.topLeft() - boundingRect().topLeft();
        qreal rectw = rect.width();
        qreal recth = rect.height();


        QRectF arcr = QRectF(point.rx(), point.ry(), rectw, recth);
        m_pRealPainter->drawArc(arcr, startangle, updateangle);

        this->setPixmap(*m_pRealBrush);
        this->update();
        //this->update(path.boundingRect());
    }
}

void QCatGrayBrushPixItem::SetBackgroundColor(const QColor &color)
{
    m_yBgColor = color;
    if(m_pRealBrush != nullptr)
    {
        m_pRealBrush->fill(color);
    }
}

void QCatGrayBrushPixItem::SetMode(QCatGrayBrushObject::BrushMode mode)
{
    m_yBrushMode = mode;
}

void QCatGrayBrushPixItem::SetBrushSize(QRectF size)
{
    m_bFixedSize = true;
    m_ySizeRect = size;
    if(m_pRealBrush != nullptr)
    {
        delete m_pRealBrush;
        m_pRealBrush = nullptr;
    }
    if(m_pRealPainter != nullptr)
    {
        delete m_pRealPainter;
        m_pRealPainter = nullptr;
    }
    m_pRealBrush = new QPixmap(m_ySizeRect.size().toSize());
    m_pRealBrush->fill(Qt::transparent);

    m_pRealPainter = new QPainter(m_pRealBrush);
    m_pCatBrushPixBufferItem->InitSizeRect(m_ySizeRect);
    this->setOffset(m_ySizeRect.x(), m_ySizeRect.y());
}

void QCatGrayBrushPixItem::Clear()
{
    if(m_pRealBrush != nullptr)
    {
        m_pRealBrush->fill(m_yBgColor);
        update();
    }
}

QRectF QCatGrayBrushPixItem::boundingRect() const
{
    return m_ySizeRect;
}

void QCatGrayBrushPixItem::InitProperty()
{
    m_bFixedSize = false;
    m_pRealBrush = nullptr;
    m_pRealPainter = nullptr;
    m_pCatBrushPixBufferItem = nullptr;
    m_ySizeRect = QRectF(0,0,0,0);
    m_yLastSizeRect = QRectF(0,0,0,0);
}

void QCatGrayBrushPixItem::DrawToReal(QCatGrayBrushObject *object)
{
    if(m_pRealPainter != nullptr && m_pCatBrushPixBufferItem != nullptr)
    {

        m_pRealPainter->setCompositionMode(QPainter::CompositionMode_Source);
        m_pRealPainter->setRenderHint(QPainter::Antialiasing, true);
        m_pRealPainter->setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        QPainterPath path = object->StrokePixmapPath(5);
        m_pRealPainter->fillPath(path, Qt::red);

        m_pCatBrushPixBufferItem->Clear();
        this->setPixmap(*m_pRealBrush);
        this->setOffset(m_ySizeRect.x(), m_ySizeRect.y());
        this->update(object->UpatePixmapRect());
        //this->update(path.boundingRect());
    }
}

void QCatGrayBrushPixItem::InitBrush()
{
    m_pCatBrushPixBufferItem = new QCatGrayBrushPixBufferItem(this);
    m_pCatBrushPixBufferItem->setZValue(10);
}

void QCatGrayBrushPixItem::DoErase(QPointF pos1, QPointF pos2, int width)
{
    if(m_pRealPainter != nullptr)
    {
        QPainterPath path = CreateStrokePath(pos1, pos2, width);

        m_pRealPainter->setCompositionMode(QPainter::CompositionMode_Source);
        m_pRealPainter->setRenderHint(QPainter::Antialiasing, true);
        m_pRealPainter->setPen(QPen(Qt::transparent, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        m_pRealPainter->fillPath(path, Qt::transparent);
        this->setPixmap(*m_pRealBrush);
        //this->setOffset(m_ySizeRect.x(), m_ySizeRect.y());
        this->update();
    }
}

QPainterPath QCatGrayBrushPixItem::CreateStrokePath(const QPointF &pos1, const QPointF &pos2, int width)
{
    QPainterPath path;
    path.moveTo(pos1 - boundingRect().topLeft());
    path.lineTo(pos2 - boundingRect().topLeft());

    if(path.isEmpty())
    {
        path.addRegion(QRegion(QRect(pos1.x() - boundingRect().x() - 0.5, pos2.y() - boundingRect().y() - 0.5, 1, 1),
                               QRegion::Ellipse));
    }

    QPainterPathStroker stroker;
    stroker.setWidth(width);
    stroker.setCapStyle(Qt::RoundCap);
    stroker.setJoinStyle(Qt::RoundJoin);

    return stroker.createStroke(path);
}

void QCatGrayBrushPixItem::UpdateRectSize(QPointF point)
{
    //qDebug() << "Scene: " << scene()->sceneRect();
    qreal left = boundingRect().left();
    qreal right = boundingRect().right();
    qreal top = boundingRect().top();
    qreal bottom = boundingRect().bottom();

    if(left == 0 && right == 0 && top == 0 && bottom == 0)
    {
        left = point.x();
        right = point.x() + 5;
        top = point.y();
        bottom = point.y() + 5;
        m_ySizeRect = QRectF(left, top, right - left, bottom - top);
        m_yLastSizeRect = m_ySizeRect;
    } else {
        if(point.x() < boundingRect().left())
        {
            left = point.x();
        }
        if(point.x() > boundingRect().right())
        {
            right = point.x();
        }
        if(point.y() < boundingRect().top())
        {
            top = point.y();
        }
        if(point.y() > boundingRect().bottom())
        {
            bottom = point.y();
        }
        m_yLastSizeRect = m_ySizeRect;
        m_ySizeRect = QRectF(left, top, right - left, bottom - top);
    }


    if(m_pRealBrush == nullptr)
    {
        m_pRealBrush = new QPixmap(m_ySizeRect.size().toSize());
        m_pRealBrush->fill(Qt::transparent);

        m_pRealPainter = new QPainter(m_pRealBrush);
        m_pCatBrushPixBufferItem->InitSizeRect(m_ySizeRect);


    } else {
        QPixmap *temp = new QPixmap(m_ySizeRect.size().toSize());
        temp->fill(Qt::transparent);

        QPainter *tempPainter = new QPainter(temp);
        m_pCatBrushPixBufferItem->UpdateSizeRect(m_ySizeRect);
        qreal x = 0.0;
        qreal y = 0.0;
        if(m_yLastSizeRect.x() - m_ySizeRect.x() > 0)
        {
            x = m_yLastSizeRect.x() - m_ySizeRect.x();
        }

        if(m_yLastSizeRect.y() - m_ySizeRect.y() > 0)
        {
            y = m_yLastSizeRect.y() - m_ySizeRect.y();
        }
        tempPainter->drawPixmap(QPointF(x, y), *m_pRealBrush);
        this->setOffset(m_ySizeRect.x(), m_ySizeRect.y());


        delete m_pRealPainter;
        m_pRealPainter = nullptr;

        delete m_pRealBrush;
        m_pRealBrush = nullptr;

        m_pRealBrush = temp;
        m_pRealPainter = tempPainter;
    }
}
