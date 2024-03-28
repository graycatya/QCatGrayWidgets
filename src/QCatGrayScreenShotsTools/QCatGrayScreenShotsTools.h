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
    explicit QCatGrayScreenShotsTools(QWidget* parent = nullptr);
    ~QCatGrayScreenShotsTools();

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
