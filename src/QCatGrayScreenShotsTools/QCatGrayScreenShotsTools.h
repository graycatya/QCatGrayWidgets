#pragma once

#include <QWidget>

class QCatGrayScreenShotBase;
class QCatGrayScreenShotsToolScene;
class QCatGrayScreenShotsToolView;
class QCatGrayScreenShotsToolBackdrop;
class QCatGrayScreenShotsToolMasklayer;
class QCatGrayScreenShotsToolFilterbox;
class QVBoxLayout;

class QCatGrayScreenShotsTools : public QWidget
{
    Q_OBJECT
public:
    enum SCREENINGMODE {
        FOCUSINGLIGHT_MODE,
        MAGNIFYINGGLASS_MODE,
    };
    Q_ENUM(SCREENINGMODE)
    explicit QCatGrayScreenShotsTools(QWidget* parent = nullptr);
    ~QCatGrayScreenShotsTools();

    void setMasklayerColor(QColor color);
    void setBorderColor(QColor color);
    void setBorderWidth(qreal width);
    void setRectRadius(int radius);
    void setBoundingRect(QRectF rect);
    void setScreeningMode(SCREENINGMODE mode);
    void setFilterBoxMovable(bool flag);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void InitProperty();

private:
    QVBoxLayout * mLayout = nullptr;
    QCatGrayScreenShotBase *m_CatGrayScreenShotBase = nullptr;
    QCatGrayScreenShotsToolScene * m_CatGrayScreenShotsToolScene = nullptr;
    QCatGrayScreenShotsToolView * m_CatGrayScreenShotsToolView = nullptr;
    QCatGrayScreenShotsToolBackdrop * m_CatGrayScreenShotsToolBackdrop = nullptr;
    QCatGrayScreenShotsToolMasklayer * m_CatGrayScreenShotsToolMasklayer = nullptr;
    QCatGrayScreenShotsToolFilterbox *m_CatGrayScreenShotsToolFilterbox = nullptr;
};
