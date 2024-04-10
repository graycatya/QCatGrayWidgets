#include "QCatGrayScreenShotsToolFilterbox.h"
#include "QCatGrayScreenShotsToolBackdrop.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneHoverEvent>
#include <QKeyEvent>

bool isupdate = false;

QCatGrayScreenShotsToolFilterbox::QCatGrayScreenShotsToolFilterbox()
{
    InitProperty();
    InitConnect();
}

QCatGrayScreenShotsToolFilterbox::~QCatGrayScreenShotsToolFilterbox()
{

}

void QCatGrayScreenShotsToolFilterbox::setBoundingRect(QRectF rect)
{
    // if(m_BoundingRect.width() != rect.width()
    //     || m_BoundingRect.height() != rect.height()
    //     || x() != rect.x()
    //     || y() != rect.y())
    // {
        //qDebug() << __FUNCTION__ << rect;
        //this->setPos(QPointF(rect.topLeft()));
        // m_BoundingRect.setTopLeft(QPointF(0, 0));
        // m_BoundingRect.setSize(rect.size());
    this->setPos(QPointF(rect.topLeft()));
    m_BoundingRect = rect;

    emit boundingRectChanged();
    PainterMode();
    // }
}

QRectF QCatGrayScreenShotsToolFilterbox::boundingRect() const
{
    return QRectF(0,0,m_BoundingRect.width(), m_BoundingRect.height());
}

void QCatGrayScreenShotsToolFilterbox::setBorderColor(QColor color)
{
    if(m_BorderColor != color)
    {
        m_BorderColor = color;
        emit borderColorChanged();
    }
}

QColor QCatGrayScreenShotsToolFilterbox::borderColor() const
{
    return  m_BorderColor;
}

void QCatGrayScreenShotsToolFilterbox::setBorderWidth(qreal width)
{
    if(m_BorderWidth != width)
    {
        m_BorderWidth = width;
        emit borderWidthChanged();
    }
}

qreal QCatGrayScreenShotsToolFilterbox::borderWidth() const
{
    return m_BorderWidth;
}

void QCatGrayScreenShotsToolFilterbox::setBackdropWidget(QCatGrayScreenShotsToolBackdrop *widget)
{
    if(m_BackdropWidget != widget)
    {
        m_BackdropWidget = widget;
    }
}

QWidget *QCatGrayScreenShotsToolFilterbox::backdropWidget() const
{
    return m_BackdropWidget;
}

void QCatGrayScreenShotsToolFilterbox::setRectRadius(int radius)
{
    if(m_RectRadius != radius)
    {
        m_RectRadius = radius;
        emit rectRadiusChanged();
    }
}

int QCatGrayScreenShotsToolFilterbox::rectRadius() const
{
    return m_RectRadius;
}

void QCatGrayScreenShotsToolFilterbox::setScreeningMode(SCREENINGMODE mode)
{
    if(m_ScreeningMode != mode)
    {
        m_ScreeningMode = mode;
        emit screeningModeChanged();
    }
}

QCatGrayScreenShotsToolFilterbox::SCREENINGMODE QCatGrayScreenShotsToolFilterbox::screeningMode() const
{
    return m_ScreeningMode;
}

void QCatGrayScreenShotsToolFilterbox::setMovable(bool flag)
{
    this->setAcceptHoverEvents(flag);
    this->setAcceptTouchEvents(flag);
    setFlag(QGraphicsItem::ItemIsMovable, flag);
}

void QCatGrayScreenShotsToolFilterbox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)


    if(m_BackdropWidget)
    {
        // switch (m_ScreeningMode) {
        // case FOCUSINGLIGHT_MODE:
        //     FocusingLight(painter);
        //     break;
        // case MAGNIFYINGGLASS_MODE:
        //     MagnifyingGlass(painter);
        //     break;
        // default:
        //     break;
        // }

        // painter->setPen(QPen(m_BorderColor, m_BorderWidth));

        // painter->drawRoundedRect(QRect(0,0,boundingRect().width(), boundingRect().height()), 0, 0);
        //PainterMode();
        isupdate = true;
        if(!m_Painter.isNull())
        {
            painter->drawPixmap(QRect(0,0, m_BoundingRect.width(), m_BoundingRect.height()), m_Painter);
        } else {
            PainterMode();
        }

    }
}

QPainterPath QCatGrayScreenShotsToolFilterbox::shape() const
{
    QPainterPath path;
    path.addRoundedRect(boundingRect(),
                        boundingRect().width()/2,
                        boundingRect().height()/2);
    return path;
}

void QCatGrayScreenShotsToolFilterbox::InitProperty()
{
    // this->setAcceptHoverEvents(true);
    // this->setAcceptTouchEvents(true);
    // setFlag(QGraphicsItem::ItemIsMovable, true);
}

void QCatGrayScreenShotsToolFilterbox::InitConnect()
{
    // connect(this, &QCatGrayScreenShotsToolFilterbox::boundingRectChanged, this, [=](){
    //     PainterMode();
    // });
}

void QCatGrayScreenShotsToolFilterbox::MagnifyingGlass(QPainter *painter)
{
    QTransform transform = m_BackdropWidget->getTransform();
    qreal zWidth = m_BoundingRect.width() / (2 * transform.m11());
    qreal zWidthHalf = zWidth / 2;
    qreal zHeight = m_BoundingRect.height() / (2 * transform.m22());
    qreal zHeightHalf = zHeight / 2;

    float zX = m_BoundingRect.x() + zWidthHalf;
    float zY = m_BoundingRect.y() + zHeightHalf;

    QPointF leftTop(zX, zY);
    QPointF rightBottom(zX + zWidth, zY + zHeight);
    QRectF srcRect(leftTop, rightBottom);


    QPixmap pixmap(srcRect.width(), srcRect.height());
    m_BackdropWidget->render(&pixmap, QPoint(0,0), srcRect.toRect());

    QPixmap pMap(m_BoundingRect.width(), m_BoundingRect.height());
    pMap.fill(Qt::transparent);
    pMap = pixmap.scaled(QSize(m_BoundingRect.width(), m_BoundingRect.height()));
    QBrush brush(pMap);
    painter->setBrush(brush);
}

void QCatGrayScreenShotsToolFilterbox::FocusingLight(QPainter *painter)
{
    QPixmap pixmap(m_BoundingRect.width(), m_BoundingRect.height());
    m_BackdropWidget->render(&pixmap, QPoint(0,0), m_BoundingRect.toRect());
    QBrush brush(pixmap);
    painter->setBrush(brush);

}

void QCatGrayScreenShotsToolFilterbox::PainterMode()
{
    if(m_BackdropWidget && isupdate)
    {
        m_Painter = QPixmap(m_BoundingRect.width(), m_BoundingRect.height());
        if(!m_Painter.isNull())
        {
            m_Painter.fill(Qt::transparent);
            QPainter painter(&m_Painter);

            switch (m_ScreeningMode) {
            case FOCUSINGLIGHT_MODE:
                FocusingLight(&painter);
                break;
            case MAGNIFYINGGLASS_MODE:
                MagnifyingGlass(&painter);
                break;
            default:
                break;
            }

            painter.setPen(QPen(m_BorderColor, m_BorderWidth));

            painter.drawRoundedRect(QRect(m_BorderWidth/2,
                                          m_BorderWidth/2,
                                          boundingRect().width() - m_BorderWidth,
                                          boundingRect().height() - m_BorderWidth),
                                    m_RectRadius, m_RectRadius);
        }
        update();

    }
}

void QCatGrayScreenShotsToolFilterbox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void QCatGrayScreenShotsToolFilterbox::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = mapToScene(event->pos());
    setBoundingRect({pos.x() - event->pos().x(),
                     pos.y() - event->pos().y(),
                     this->m_BoundingRect.width(), this->m_BoundingRect.height()});
    QGraphicsItem::mouseMoveEvent(event);
}

void QCatGrayScreenShotsToolFilterbox::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}


void QCatGrayScreenShotsToolFilterbox::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event);
}

void QCatGrayScreenShotsToolFilterbox::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverMoveEvent(event);
}

void QCatGrayScreenShotsToolFilterbox::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event);
}

void QCatGrayScreenShotsToolFilterbox::keyPressEvent(QKeyEvent *event)
{
    QGraphicsItem::keyPressEvent(event);
}

void QCatGrayScreenShotsToolFilterbox::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsItem::keyReleaseEvent(event);
}
