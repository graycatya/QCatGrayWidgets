#ifndef QCATGRAYQUICKWIDGET_H
#define QCATGRAYQUICKWIDGET_H

#include <QWidget>
#include <QtCore/qurl.h>


class QQuickView;
class QQmlEngine;

class QCatGrayQuickWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(ResizeMode resizeMode READ resizeMode WRITE setResizeMode)
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QUrl source READ source WRITE setSource DESIGNABLE true)
public:
    QCatGrayQuickWidget(const QUrl &source, QWidget *parent = nullptr);
    explicit QCatGrayQuickWidget(QWidget *parent = nullptr);

    virtual ~QCatGrayQuickWidget() override;


    enum ResizeMode { SizeViewToRootObject, SizeRootObjectToView };
    Q_ENUM(ResizeMode)
    ResizeMode resizeMode() const;
    void setResizeMode(ResizeMode);

    enum Status { Null, Ready, Loading, Error };
    Q_ENUM(Status)
    Status status() const;

    QQuickView* view() const {
        return m_pView;
    };

    QUrl source() const;

signals:
    void statusChanged();

public slots:
    void setSource(const QUrl &url);

private:
    QQuickView *m_pView = nullptr;
    QUrl m_qSource;
};

#endif
