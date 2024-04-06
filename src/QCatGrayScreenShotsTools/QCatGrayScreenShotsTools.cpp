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
#include <QDesktopWidget>

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
    mLayout->setMargin(0);
    m_CatGrayScreenShotBase = new QCatGrayScreenShot(this);
    int screenid = QApplication::screens().indexOf(QApplication::primaryScreen());
    m_Backdrop = static_cast<QPixmap *>(m_CatGrayScreenShotBase->getScreenShot(screenid, 0, 0,
                                        QApplication::primaryScreen()->size().width(),
                                        QApplication::primaryScreen()->size().height(),
                                        QApplication::desktop()->winId()));
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
    m_CatGrayScreenShotsToolMasklayer->setMasklayerColor(QColor(0, 0, 0, 199));

    m_CatGrayScreenShotsToolFilterbox = new QCatGrayScreenShotsToolFilterbox();
    m_CatGrayScreenShotsToolFilterbox->setBackdropWidget(m_CatGrayScreenShotsToolBackdrop);
    m_CatGrayScreenShotsToolFilterbox->setBoundingRect(QRectF(100,100,
                                                              500,
                                                              500));
    m_CatGrayScreenShotsToolScene->addItem(m_CatGrayScreenShotsToolFilterbox);
    m_CatGrayScreenShotsToolBackdrop->setBackdrop(m_Backdrop);

    this->setLayout(mLayout);

}
