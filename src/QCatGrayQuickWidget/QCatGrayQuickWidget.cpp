#include "QCatGrayQuickWidget.h"
#include <QQuickView>
#include <QBoxLayout>

QVBoxLayout *m_Layout = nullptr;

QCatGrayQuickWidget::QCatGrayQuickWidget(const QUrl &source, QWidget *parent)
    : QWidget(parent)
{
    m_Layout = new QVBoxLayout(this);
    m_Layout->setMargin(0);

    m_pView = new QQuickView;
    QWidget *containerWidget = QWidget::createWindowContainer(m_pView, this);
    m_pView->setResizeMode(QQuickView::SizeRootObjectToView);
    connect(m_pView, &QQuickView::statusChanged, this, &QCatGrayQuickWidget::statusChanged);

    m_Layout->addWidget(containerWidget);

    m_pView->setSource(source);
}

QCatGrayQuickWidget::QCatGrayQuickWidget(QWidget *parent)
    : QWidget(parent)
{
    m_Layout = new QVBoxLayout(this);
    m_Layout->setMargin(0);

    m_pView = new QQuickView;
    QWidget *containerWidget = QWidget::createWindowContainer(m_pView, this);
    m_pView->setResizeMode(QQuickView::SizeRootObjectToView);
    connect(m_pView, &QQuickView::statusChanged, this, &QCatGrayQuickWidget::statusChanged);

    m_Layout->addWidget(containerWidget);
}

QCatGrayQuickWidget::~QCatGrayQuickWidget()
{

}

QCatGrayQuickWidget::ResizeMode QCatGrayQuickWidget::resizeMode() const
{
    return static_cast<QCatGrayQuickWidget::ResizeMode>(m_pView->resizeMode());
}

void QCatGrayQuickWidget::setResizeMode(ResizeMode mode)
{
    m_pView->setResizeMode(static_cast<QQuickView::ResizeMode>(mode));
}

QCatGrayQuickWidget::Status QCatGrayQuickWidget::status() const
{
    return static_cast<QCatGrayQuickWidget::Status>(m_pView->status());
}

QUrl QCatGrayQuickWidget::source() const
{
    return m_pView->source();
}

void QCatGrayQuickWidget::setSource(const QUrl &url)
{
    return m_pView->setSource(url);
}
