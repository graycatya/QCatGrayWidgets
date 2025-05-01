#ifndef QCATGRAYTABBAR_P_H
#define QCATGRAYTABBAR_P_H

#include <QtWidgets/private/qtwidgetsglobal_p.h>
#include "QCatGrayTabbar.h"
#include "private/qwidget_p.h"

#include <qicon.h>
#include <qtoolbutton.h>
#include <qdebug.h>
#if QT_CONFIG(animation)
#include <qvariantanimation.h>
#endif

#define ANIMATION_DURATION 250


QT_BEGIN_NAMESPACE

class QCatGrayTabbarPrivateSignals : public QObject
{
    Q_OBJECT

public:
    explicit QCatGrayTabbarPrivateSignals(QObject *parent = nullptr): QObject(parent) {}
    ~QCatGrayTabbarPrivateSignals() {}
    enum ITEMMOVESTATE {
        NOTSTATE,
        LEFTORTOPSTATE,
        RIGHTORBOTTOMSTATE
    };
    Q_ENUM(ITEMMOVESTATE)

    void setItemMoveState(ITEMMOVESTATE state);
    ITEMMOVESTATE itemMoveState() const { return mItemMoveState; }
signals:
    void insertItemChanged(int index, QCatGrayTabbarItem *item);
    void appendItemChanged(int index, QCatGrayTabbarItem *item);
    void removeItemChanged(int index);
    void realsticSizeChanged(int size, bool animationItem = false);
    void wheelChanged(int lastslidernum, int slidernum, bool animationItem = false);
    void itemMoveStateChanged();
    void itemMoveUpdate(QCatGrayTabbarItem *moveitem);
private:
    ITEMMOVESTATE mItemMoveState = NOTSTATE;
};

class CatMovableTabWidget : public QWidget
{
public:
    explicit CatMovableTabWidget(QWidget *parent = nullptr);
    void setPixmap(const QPixmap &pixmap);

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    QPixmap m_pixmap;
};

class QCatGrayTabbarPrivate : public QWidgetPrivate
{
    Q_DECLARE_PUBLIC(QCatGrayTabbar)
public:
    QCatGrayTabbarPrivate();
    ~QCatGrayTabbarPrivate();

    int currentIndex;
    QCatGrayTabbar::Shape shape;
    QCatGrayTabbar::ScrollbuttonPosition scrollbuttonPosition;
    QList<QCatGrayTabbarItem*> tabList;
    QMargins layoutMargins;
    int layoutSpacing;
    int minItemSize;
    int maxItemSize;
    int realisticSize;
    int lastslidernum;
    int slidernum;


    inline bool validIndex(int index) const { return index >= 0 && index < tabList.count(); }
    inline bool validLayoutSpacing(int spacing) const { return spacing >= 0; }
    inline static bool verticalTabs(QCatGrayTabbar::Shape shape);
    inline int contentSize() const;
    inline int contentSlidernum(int size);
    void _q_scrollTabs();
    void _q_closeTab();

    void refresh();
};


QT_END_NAMESPACE

#endif // QCatGrayTabbar_P_H


