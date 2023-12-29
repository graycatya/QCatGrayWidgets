#include "QCatGrayToolTip.h"
#include <QToolTip>

QCatGrayToolTip *QCatGrayToolTip::_instance = nullptr;
std::mutex* QCatGrayToolTip::m_pMutex = new std::mutex;


void QCatGrayToolTip::ShowToolTip(QString text, int sleep)
{
    std::unique_lock<std::mutex> lock(*m_pMutex);
    m_sShowText = text;
    m_pTimer->start(sleep);
}

void QCatGrayToolTip::HideToolTip()
{
    std::unique_lock<std::mutex> lock(*m_pMutex);
    if(m_pTimer->isActive())
    {
        m_pTimer->stop();
    }
    QToolTip::hideText();
}

QCatGrayToolTip::QCatGrayToolTip()
{
    m_pTimer = new QTimer(this);
    m_sShowText.clear();
    InitConnect();
}

QCatGrayToolTip::~QCatGrayToolTip()
{

}

void QCatGrayToolTip::InitConnect()
{
    connect(m_pTimer, &QTimer::timeout, this, [=](){
        QToolTip::showText(QCursor::pos(), m_sShowText);
    });
}
