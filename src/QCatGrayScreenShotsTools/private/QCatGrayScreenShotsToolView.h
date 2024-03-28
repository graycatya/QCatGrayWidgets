#pragma once


#include <QGraphicsView>

class QCatGrayScreenShotsToolView : public QGraphicsView
{
    Q_OBJECT
public:
    QCatGrayScreenShotsToolView(QWidget *parent = nullptr);
    QCatGrayScreenShotsToolView(QGraphicsScene *scene, QWidget *parent = nullptr);
    ~QCatGrayScreenShotsToolView();

};
