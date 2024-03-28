#pragma once

#include <QWidget>
#include <QTransform>


class QCatGrayScreenShotsToolBackdrop : public QWidget
{
    Q_OBJECT
public:
    explicit QCatGrayScreenShotsToolBackdrop(QWidget *parent = nullptr);
    ~QCatGrayScreenShotsToolBackdrop();

    QTransform getTransform() const;

    void setBackdrop(QPixmap* pixmap);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QTransform m_Transform;
    QPixmap *m_Backdrop;
};
