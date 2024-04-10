#pragma once

#include <QGraphicsObject>

class QCatGrayScreenShotsToolBackdrop;

class QCatGrayScreenShotsToolFilterbox : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QRectF boundingRect READ boundingRect WRITE setBoundingRect NOTIFY boundingRectChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(qreal borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged)
    Q_PROPERTY(int rectRadius READ rectRadius WRITE setRectRadius NOTIFY rectRadiusChanged)
    Q_PROPERTY(SCREENINGMODE screeningMode READ screeningMode WRITE setScreeningMode NOTIFY screeningModeChanged)
public:
    enum SCREENINGMODE {
        FOCUSINGLIGHT_MODE,
        MAGNIFYINGGLASS_MODE,
    };
    Q_ENUM(SCREENINGMODE)
    QCatGrayScreenShotsToolFilterbox();
    ~QCatGrayScreenShotsToolFilterbox();

    void setBoundingRect(QRectF rect);
    QRectF boundingRect() const override;

    void setBorderColor(QColor color);
    QColor borderColor() const;

    void setBorderWidth(qreal width);
    qreal borderWidth() const;

    void setBackdropWidget(QCatGrayScreenShotsToolBackdrop *widget);
    QWidget *backdropWidget() const;

    void setRectRadius(int radius);
    int rectRadius() const;

    void setScreeningMode(SCREENINGMODE mode);
    SCREENINGMODE screeningMode() const;

    void setMovable(bool flag);


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
    QPainterPath shape() const override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    void InitProperty();
    void InitConnect();

    void MagnifyingGlass(QPainter *painter);
    void FocusingLight(QPainter *painter);
    void PainterMode();

signals:
    void boundingRectChanged();
    void borderColorChanged();
    void borderWidthChanged();
    void rectRadiusChanged();
    void screeningModeChanged();

private:
    QRectF m_BoundingRect = QRectF(0, 0, 0, 0);
    QColor m_BorderColor = QColor(0, 0, 0, 0);
    qreal m_BorderWidth = 0;
    int m_RectRadius = 0;
    QCatGrayScreenShotsToolBackdrop *m_BackdropWidget = nullptr;
    SCREENINGMODE m_ScreeningMode = FOCUSINGLIGHT_MODE;
    QPixmap m_Painter;
};
