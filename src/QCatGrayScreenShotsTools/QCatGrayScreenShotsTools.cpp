#include "QCatGrayScreenShotsTools.h"
#include "private/QCatGrayScreenShotsToolScene.h"
#include "private/QCatGrayScreenShotsToolView.h"
#include "private/QCatGrayScreenShotsToolBackdrop.h"
#include "private/QCatGrayScreenShotsToolMasklayer.h"
#include "private/QCatGrayScreenShotsToolFilterbox.h"

#include <QCatGrayScreenShot.h>
#include <QApplication>
#include <QScreen>
#include <QPixmap>
#include <QVBoxLayout>
#include <QGraphicsProxyWidget>
//#include <QDesktopWidget>
#include <QDebug>

QPixmap *m_Backdrop = nullptr;

QCatGrayScreenShotsTools::QCatGrayScreenShotsTools(QWidget *parent)
    : QWidget(parent)
{
    InitProperty();
}

QCatGrayScreenShotsTools::~QCatGrayScreenShotsTools()
{
    if(mLayout)
    {
        delete mLayout;
        mLayout = nullptr;
    }
    if(m_Backdrop != nullptr)
    {
        delete m_Backdrop;
        m_Backdrop = nullptr;
    }
}

void QCatGrayScreenShotsTools::setMasklayerColor(QColor color)
{
    if(m_CatGrayScreenShotsToolMasklayer)
    {
        m_CatGrayScreenShotsToolMasklayer->setMasklayerColor(color);
    }
}

void QCatGrayScreenShotsTools::setBorderColor(QColor color)
{
    if(m_CatGrayScreenShotsToolFilterbox)
    {
        m_CatGrayScreenShotsToolFilterbox->setBorderColor(color);
    }
}

void QCatGrayScreenShotsTools::setBorderWidth(qreal width)
{
    if(m_CatGrayScreenShotsToolFilterbox)
    {
        m_CatGrayScreenShotsToolFilterbox->setBorderWidth(width);
    }
}

void QCatGrayScreenShotsTools::setRectRadius(int radius)
{
    if(m_CatGrayScreenShotsToolFilterbox)
    {
        m_CatGrayScreenShotsToolFilterbox->setRectRadius(radius);
    }
}

void QCatGrayScreenShotsTools::setBoundingRect(QRectF rect)
{
    if(m_CatGrayScreenShotsToolFilterbox)
    {
        m_CatGrayScreenShotsToolFilterbox->setBoundingRect(rect);
    }
}

void QCatGrayScreenShotsTools::setScreeningMode(SCREENINGMODE mode)
{
    if(m_CatGrayScreenShotsToolFilterbox)
    {
        m_CatGrayScreenShotsToolFilterbox->setScreeningMode((QCatGrayScreenShotsToolFilterbox::SCREENINGMODE)mode);
    }
}

void QCatGrayScreenShotsTools::setFilterBoxMovable(bool flag)
{
    if(m_CatGrayScreenShotsToolFilterbox)
    {
        m_CatGrayScreenShotsToolFilterbox->setMovable(flag);
    }
}

void QCatGrayScreenShotsTools::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    if(m_CatGrayScreenShotsToolBackdrop)
    {
        m_CatGrayScreenShotsToolBackdrop->resize(this->size());
        m_CatGrayScreenShotsToolBackdrop->update();
    }
}

void QCatGrayScreenShotsTools::InitProperty()
{
    mLayout = new QVBoxLayout;
    mLayout->setContentsMargins(0,0,0,0);
    m_CatGrayScreenShotBase = new QCatGrayScreenShot(this);
    int screenid = QApplication::screens().indexOf(QApplication::primaryScreen());
    m_Backdrop = static_cast<QPixmap *>(m_CatGrayScreenShotBase->getScreenShot(screenid, 0, 0,
                                        QApplication::primaryScreen()->size().width(),
                                        QApplication::primaryScreen()->size().height(),
                                        this->winId()));
    m_CatGrayScreenShotsToolMasklayer = new QCatGrayScreenShotsToolMasklayer();
    m_CatGrayScreenShotsToolScene = new QCatGrayScreenShotsToolScene(this);
    m_CatGrayScreenShotsToolView = new QCatGrayScreenShotsToolView(m_CatGrayScreenShotsToolScene, this);
    m_CatGrayScreenShotsToolView->setAttribute(Qt::WA_TranslucentBackground);
    m_CatGrayScreenShotsToolView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_CatGrayScreenShotsToolView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mLayout->addWidget(m_CatGrayScreenShotsToolView);

    m_CatGrayScreenShotsToolBackdrop = new QCatGrayScreenShotsToolBackdrop;
    QGraphicsProxyWidget *backdrop = m_CatGrayScreenShotsToolScene->addWidget(m_CatGrayScreenShotsToolBackdrop);
    backdrop->setZValue(-1);
    m_CatGrayScreenShotsToolScene->addItem(m_CatGrayScreenShotsToolMasklayer);
    m_CatGrayScreenShotsToolMasklayer->setBoundingRect(QRectF(0,0,
                                                            QApplication::primaryScreen()->size().width(),
                                                            QApplication::primaryScreen()->size().height()));
    // m_CatGrayScreenShotsToolMasklayer->setMasklayerColor(QColor(0, 0, 0, 199));

    m_CatGrayScreenShotsToolFilterbox = new QCatGrayScreenShotsToolFilterbox();
    m_CatGrayScreenShotsToolFilterbox->setBackdropWidget(m_CatGrayScreenShotsToolBackdrop);
    connect(m_CatGrayScreenShotsToolFilterbox, &QCatGrayScreenShotsToolFilterbox::boundingRectChanged, this, [=](){
        m_CatGrayScreenShotsToolView->update(m_CatGrayScreenShotsToolFilterbox->x() - 100,
                                             m_CatGrayScreenShotsToolFilterbox->y() - 100,
                                             m_CatGrayScreenShotsToolFilterbox->boundingRect().width() + 100,
                                             m_CatGrayScreenShotsToolFilterbox->boundingRect().height() + 100);
    });
    // m_CatGrayScreenShotsToolFilterbox->setBorderColor(Qt::red);
    // m_CatGrayScreenShotsToolFilterbox->setBorderWidth(5);
    // m_CatGrayScreenShotsToolFilterbox->setRectRadius(250);
    // m_CatGrayScreenShotsToolFilterbox->setBoundingRect(QRectF(100,100,
    //                                                           500,
    //                                                           500));
    m_CatGrayScreenShotsToolScene->addItem(m_CatGrayScreenShotsToolFilterbox);
    m_CatGrayScreenShotsToolBackdrop->setBackdrop(m_Backdrop);

    this->setLayout(mLayout);

}
