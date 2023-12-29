#pragma once

#include <QWidget>

class QCatGrayShadowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QCatGrayShadowWidget(QWidget *widget);
    ~QCatGrayShadowWidget();

public slots:
    void SetShadowColor(QColor color);
    void SetShadowWeight(int weight);
    void SetShadowRadius(int radius);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    // 阴影属性
    QColor ShadowColor;
    int ShadowWeight = 0;
    int ShadowRadius = 0;

};

