
#include "QCatGrayTabbar_p.h"
#include <QWheelEvent>
#include <QPainter>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QSequentialAnimationGroup>
#include <QResizeEvent>
#include <QTimer>

QT_BEGIN_NAMESPACE

#define insertItemId -10

QCatGrayTabbarItem::QCatGrayTabbarItem(QCatGrayTabbar *parent)
    : QWidget(parent)
{
    //animation = new QPropertyAnimation(this);
    animationgroup = new QSequentialAnimationGroup(this);
    connect(animationgroup, &QSequentialAnimationGroup::finished, this, [=](){

    });
}

QCatGrayTabbarItem::~QCatGrayTabbarItem()
{
    if(animationgroup)
    {
        if(animationgroup->state() != QSequentialAnimationGroup::Stopped)
        {
            animationgroup->stop();
        }
        delete animationgroup;
        animationgroup = nullptr;
    }
}

void QCatGrayTabbarItem::animationItem(const QByteArray &propertyName, int durationMssecs, const QVariant &startValue, const QVariant &endValue)
{
    QPropertyAnimation *animation = new QPropertyAnimation(this);
    animation->setTargetObject(this);
    animation->setPropertyName(propertyName);
    animation->setDuration(durationMssecs);
    animation->setStartValue(startValue);
    animation->setEndValue(endValue);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

int QCatGrayTabbarItem::minItemSize() const
{
    return this->mMinItemSize;
}

void QCatGrayTabbarItem::setMinItemSize(int size)
{
    if(mMinItemSize != size)
    {
        mMinItemSize = size;
        emit minItemSizeChanged(size);
    }
}

int QCatGrayTabbarItem::maxItemSize() const
{
    return this->mMaxItemSize;
}

void QCatGrayTabbarItem::setMaxItemSize(int size)
{
    if(mMaxItemSize != size)
    {
        mMaxItemSize = size;
        emit maxItemSizeChanged(size);
    }
}

int QCatGrayTabbarItem::realisticSize() const
{
    return this->mRealisticSize;
}

void QCatGrayTabbarItem::setRealisticSize(int size)
{
    if(mRealisticSize != size)
    {
        mRealisticSize = size;
        emit realisticSizeChanged(size);
    }
}

bool QCatGrayTabbarItem::isMoveState() const
{
    return mIsMoveState;
}

void QCatGrayTabbarItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    if(painter.isActive())
    {
        painter.fillRect(rect(), QColor(200, 200, 200));
        painter.drawText(0,0,this->width(),this->height(),Qt::AlignCenter, mText);
    }
}

void QCatGrayTabbarItem::resizeEvent(QResizeEvent *event)
{
    //qDebug() << "item event: " << event;
}

void QCatGrayTabbarItem::mousePressEvent(QMouseEvent *event)
{
    isPress = true;
    QWidget::mousePressEvent(event);
    mPressPoint = event->pos();
}

void QCatGrayTabbarItem::mouseMoveEvent(QMouseEvent *event)
{
    if(isPress)
    {
        setIsMoveState(true);
        QPoint movePoint = event->pos() - mPressPoint;
        emit moveItemChanged(movePoint);
    }
    QWidget::mouseMoveEvent(event);
}

void QCatGrayTabbarItem::mouseReleaseEvent(QMouseEvent *event)
{
    isPress = false;
    setIsMoveState(false);
    emit fremoveItemChanged();
    QWidget::mouseReleaseEvent(event);
}


void QCatGrayTabbarItem::setIsMoveState(bool state)
{
    if(mIsMoveState != state)
    {
        mIsMoveState = state;
        emit isMoveStateChanged();
    }
}

CatMovableTabWidget::CatMovableTabWidget(QWidget *parent)
    : QWidget(parent)
{

}

void CatMovableTabWidget::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
    update();
}

void CatMovableTabWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.drawPixmap(0, 0, m_pixmap);
}

QCatGrayTabbar::QCatGrayTabbar(QWidget *parent)
    : QWidget(*new QCatGrayTabbarPrivate, parent, {})
    , durationMssecs(100)
    , lastSzie(0)
    , currentSize(0)
{
    Q_D(QCatGrayTabbar);
    privateSignals = new QCatGrayTabbarPrivateSignals(this);
}

QCatGrayTabbar::~QCatGrayTabbar()
{
    if(privateSignals)
    {
        delete privateSignals;
        privateSignals = nullptr;
    }
}

QCatGrayTabbar::Shape QCatGrayTabbar::shape() const
{
    Q_D(const QCatGrayTabbar);
    return d->shape;
}

void QCatGrayTabbar::setShape(Shape shape)
{
    Q_D(QCatGrayTabbar);
    if (d->shape == shape)
        return;
    d->shape = shape;
    d->refresh();
}

int QCatGrayTabbar::currentIndex() const
{
    Q_D(const QCatGrayTabbar);
    if (d->validIndex(d->currentIndex))
        return d->currentIndex;
    return -1;
}

int QCatGrayTabbar::count() const
{
    Q_D(const QCatGrayTabbar);
    return d->tabList.count();
}

QCatGrayTabbar::ScrollbuttonPosition QCatGrayTabbar::scrollbuttonPosition() const
{
    Q_D(const QCatGrayTabbar);
    return d->scrollbuttonPosition;
}

void QCatGrayTabbar::setScrollbuttonPosition(ScrollbuttonPosition scrollbuttonPosition)
{
    Q_D(QCatGrayTabbar);
    if(d->scrollbuttonPosition == scrollbuttonPosition)
        return;
    d->scrollbuttonPosition = scrollbuttonPosition;
    d->refresh();
}

QMargins QCatGrayTabbar::layoutmargins() const
{
    Q_D(const QCatGrayTabbar);
    return d->layoutMargins;
}

void QCatGrayTabbar::setLayoutmargins(QMargins layoutmargins)
{
    Q_D(QCatGrayTabbar);
    if(d->layoutMargins == layoutmargins)
        return;
    d->layoutMargins = layoutmargins;
    emit layoutmarginsChanged();
}

void QCatGrayTabbar::addItem(QCatGrayTabbarItem *item)
{
    this->insertItem(-1, item);
}

void QCatGrayTabbar::removeItem(int index)
{
    Q_D(QCatGrayTabbar);
    if(!d->tabList.isEmpty() && d->validIndex(index))
    {
        QCatGrayTabbarItem* item = d->tabList.value(index);
        delete item;
        item = nullptr;
        d->tabList.removeAt(index);
        emit privateSignals->removeItemChanged(index);
    }
}

void QCatGrayTabbar::insertItem(int index, QCatGrayTabbarItem *item)
{
    Q_D(QCatGrayTabbar);
    item->setParent(this);

    item->setIndex(-1);
    connect(item, &QCatGrayTabbarItem::moveItemChanged, this, [=](QPoint point){
        if(item->isMoveState())
        {
            item->raise();
            updateMoveItem(item, point);
            privateSignals->itemMoveUpdate(item);
        }
    });
    connect(item, &QCatGrayTabbarItem::fremoveItemChanged, this, [=](){
        privateSignals->setItemMoveState(QCatGrayTabbarPrivateSignals::NOTSTATE);
        updateInsertItemRect(item, true);
    });
    connect(this, &QCatGrayTabbar::minItemSizeChanged, item, [=](int size){
        Q_UNUSED(size);
        updateItemSize(item);
        updateRealisticSize(false);
        updateItemRect(item);
    }, Qt::DirectConnection);
    connect(this, &QCatGrayTabbar::maxItemSizeChanged, item, [=](int size){
        Q_UNUSED(size);
        updateItemSize(item);
        updateRealisticSize(false);
        updateItemRect(item);
    }, Qt::DirectConnection);
    connect(privateSignals, &QCatGrayTabbarPrivateSignals::itemMoveUpdate, item, [=](QCatGrayTabbarItem *moveitem){
        if(!item->isMoveState())
        {
            updateNotMoveItem(moveitem, item);
        }
    });
    connect(privateSignals, &QCatGrayTabbarPrivateSignals::realsticSizeChanged, item, [=](int size, bool animationItem){
        Q_UNUSED(size);
        item->setRealisticSize(size);
        updateItemRect(item, animationItem);
    });
    connect(privateSignals, &QCatGrayTabbarPrivateSignals::insertItemChanged, item, [=](int index, QCatGrayTabbarItem *titem){
        updateRealisticSize(false);
        if(item->getIndex() >= index)
        {
            item->setIndex(item->getIndex()+1);
            item->setText(QString::number(item->getIndex()));
            updateInsertItemRect(item, true);
        } else if(item->getIndex() >= 0 && item->getIndex() < index) {
            updateRealisticSize(item, true);
        } else if(item->getIndex() == insertItemId) {
            item->setIndex(index);
            updateItemRect(item, true);
            item->show();
        }
    }, Qt::DirectConnection);
    connect(privateSignals, &QCatGrayTabbarPrivateSignals::removeItemChanged, item, [=](int index){
        if(item->getIndex() > index)
        {
            item->setIndex(item->getIndex()-1);
            item->setText(QString::number(item->getIndex()));
        }
        updateWheelSlidernum(nullptr, false);
        updateRealisticSize(false);
        updateRemoveItemRect(item, true);
    }, Qt::DirectConnection);
    connect(privateSignals, &QCatGrayTabbarPrivateSignals::wheelChanged, item, [=](int lastslidernum, int slidernum, bool animationItem){
        updateWheelItemRect(item, animationItem);
    });
    connect(privateSignals, &QCatGrayTabbarPrivateSignals::appendItemChanged, item, [=](int index, QCatGrayTabbarItem *titem){
        updateRealisticSize(false);
        if(item->getIndex() == index)
        {
            updateItemRect(item, true);
            item->show();
        } else {
            updateRealisticSize(item, true);
        }
    });
    updateItemSize(item);
    if (!d->validIndex(index)) {
        d->tabList.append(item);
        item->setIndex(d->tabList.count()-1);
        emit privateSignals->appendItemChanged(item->getIndex(), item);
    } else {
        d->tabList.insert(index, item);
        item->setIndex(insertItemId);
        emit privateSignals->insertItemChanged(index, item);

    }
    item->setText(QString::number(item->getIndex()));

}

int QCatGrayTabbar::minItemSize() const
{
    Q_D(const QCatGrayTabbar);
    return d->minItemSize;
}

void QCatGrayTabbar::setMinItemSize(int size)
{
    Q_D(QCatGrayTabbar);
    if(d->minItemSize != size)
    {
        d->minItemSize = size;
        emit minItemSizeChanged(size);
    }
}

int QCatGrayTabbar::maxItemSize() const
{
    Q_D(const QCatGrayTabbar);
    return d->maxItemSize;
}

void QCatGrayTabbar::setMaxItemSize(int size)
{
    Q_D(QCatGrayTabbar);
    if(d->maxItemSize != size)
    {
        d->maxItemSize = size;
        emit maxItemSizeChanged(size);
    }
}

int QCatGrayTabbar::realisticSize() const
{
    Q_D(const QCatGrayTabbar);
    return d->realisticSize;
}

int QCatGrayTabbar::slidernum() const
{
    Q_D(const QCatGrayTabbar);
    return d->slidernum;
}

int QCatGrayTabbar::contentSize() const
{
    Q_D(const QCatGrayTabbar);
    return d->contentSize();
}

void QCatGrayTabbar::updateItemRect(QCatGrayTabbarItem *item, bool animationItem)
{
    Q_D(QCatGrayTabbar);
    QRect rect;
    if(d->verticalTabs(this->shape()))
    {
        int realitywidth = this->width() - layoutmargins().left() - layoutmargins().right();
        item->setMinimumSize(realitywidth, 0);
        item->setMaximumSize(realitywidth, d->maxItemSize);
        rect.setRect(layoutmargins().left(),
                     item->getIndex() * d->realisticSize +
                     (item->getIndex() == 0 ? d->layoutMargins.top()
                        : (item->getIndex()+1) * d->layoutSpacing) + d->slidernum,
                     realitywidth,
                     d->realisticSize);
    } else {
        int realityheight = this->height() - layoutmargins().top() - layoutmargins().bottom();
        item->setMinimumSize(0, realityheight);
        item->setMaximumSize(d->maxItemSize, realityheight);
        rect.setRect(item->getIndex() * d->realisticSize +
                     (item->getIndex() == 0 ? d->layoutMargins.left()
                        : (item->getIndex()+1) * d->layoutSpacing)  + d->slidernum,
                     layoutmargins().top(),
                     d->realisticSize,
                     realityheight);
    }
    if(animationItem)
    {
        QRect startRect = rect;
        if(d->verticalTabs(this->shape()))
        {
            startRect.setHeight(0);
        } else {
            startRect.setWidth(0);
        }

        QRect stopRect = rect;
        item->animationItem("geometry", durationMssecs, startRect, stopRect);
    } else {
        item->setGeometry(rect);
    }
}

void QCatGrayTabbar::updateInsertItemRect(QCatGrayTabbarItem *item, bool animationItem)
{
    Q_D(QCatGrayTabbar);
    QRect lastrect = item->geometry();
    QRect rect;
    if(d->verticalTabs(this->shape()))
    {
        int realitywidth = this->width() - layoutmargins().left() - layoutmargins().right();
        item->setMinimumSize(realitywidth, 0);
        item->setMaximumSize(realitywidth, d->maxItemSize);
        rect.setRect(layoutmargins().left(),
                    item->getIndex() * d->realisticSize +
                    (item->getIndex() == 0 ? d->layoutMargins.top()
                        : (item->getIndex()+1) * d->layoutSpacing) + d->slidernum,
                    realitywidth,
                    d->realisticSize);
    } else {
        int realityheight = this->height() - layoutmargins().top() - layoutmargins().bottom();
        item->setMinimumSize(0, realityheight);
        item->setMaximumSize(d->maxItemSize, realityheight);
        rect.setRect(item->getIndex() * d->realisticSize +
                    (item->getIndex() == 0 ? d->layoutMargins.left()
                        : (item->getIndex()+1) * d->layoutSpacing) + d->slidernum,
                    layoutmargins().top(),
                    d->realisticSize,
                    realityheight);
    }
    if(animationItem)
    {
        item->animationItem("geometry", durationMssecs, lastrect, rect);
    } else {
        item->setGeometry(rect);
    }

}

void QCatGrayTabbar::updateItemSize(QCatGrayTabbarItem *item)
{
    Q_D(QCatGrayTabbar);
    if(d->minItemSize < d->maxItemSize)
    {
        if(d->minItemSize < 0)
        {
            d->minItemSize = 0;
        }
        if(d->maxItemSize > 16777215)
        {
            d->maxItemSize = 16777215;
        } else if(d->maxItemSize < d->minItemSize)
        {
            d->maxItemSize = d->minItemSize;
        }


        //item->setRealisticSize(d->realisticSize);
        item->setMinItemSize(d->minItemSize);
        item->setMaxItemSize(d->maxItemSize);
    }

}

void QCatGrayTabbar::updateRealisticSize(bool emitrealistic, bool animationItem)
{
    Q_D(QCatGrayTabbar);
    int trealisticSize = d->realisticSize;

    int tablistcount = d->tabList.count();
    if(d->verticalTabs(this->shape()))
    {
        int theight = this->height() - d->layoutMargins.top()
                - d->layoutMargins.bottom()
                - (d->layoutSpacing * (tablistcount%2 == 0 ?
                                       tablistcount - 1 :
                                       tablistcount - 2));
        if(tablistcount > 0)
        {
            trealisticSize = theight / tablistcount;
        }
    } else {
        int twidth = this->width() - d->layoutMargins.left()
                - d->layoutMargins.right()
                - (d->layoutSpacing * (tablistcount%2 == 0 ?
                                           tablistcount - 1 :
                                           tablistcount - 2));
        if(tablistcount > 0)
        {
            trealisticSize = twidth / tablistcount;
        }
    }
    if(d->realisticSize != trealisticSize)
    {
        d->realisticSize = trealisticSize > d->maxItemSize ? d->maxItemSize
                                          : trealisticSize < d->minItemSize
                                          ? d->minItemSize : trealisticSize;
        if(emitrealistic)
        {
            emit privateSignals->realsticSizeChanged(d->realisticSize, animationItem);
        }
    }
}

void QCatGrayTabbar::updateRealisticSize(QCatGrayTabbarItem *item, bool animationItem)
{
    Q_D(QCatGrayTabbar);
    QRect startRect = item->geometry();
    QRect stopRect;
    QRect rect;
    if(d->verticalTabs(this->shape()))
    {
        int realitywidth = this->width() - layoutmargins().left() - layoutmargins().right();
        item->setMinimumSize(realitywidth, 0);
        item->setMaximumSize(realitywidth, d->maxItemSize);
        rect.setRect(layoutmargins().left(),
                     item->getIndex() * d->realisticSize +
                     (item->getIndex() == 0 ? d->layoutMargins.top()
                        : (item->getIndex()+1) * d->layoutSpacing) + d->slidernum,
                     realitywidth,
                     d->realisticSize);
    } else {
        int realityheight = this->height() - layoutmargins().top() - layoutmargins().bottom();
        item->setMinimumSize(0, realityheight);
        item->setMaximumSize(d->maxItemSize, realityheight);
        rect.setRect(item->getIndex() * d->realisticSize +
                     (item->getIndex() == 0 ? d->layoutMargins.left()
                        : (item->getIndex()+1) * d->layoutSpacing) + d->slidernum,
                     layoutmargins().top(),
                     d->realisticSize,
                     realityheight);
    }
    stopRect = rect;
    if(startRect != stopRect)
    {
        if(animationItem)
        {

            item->animationItem("geometry", durationMssecs, startRect, stopRect);
        } else {
            item->setGeometry(rect);
        }
    }
}

void QCatGrayTabbar::updatePrivateRealisticSize(bool emitrealistic, bool animationItem)
{
    Q_D(QCatGrayTabbar);
    int trealisticSize = d->realisticSize;
    int tablistcount = d->tabList.count();
    if(d->verticalTabs(this->shape()))
    {
        int theight = this->height() - d->layoutMargins.top()
                      - d->layoutMargins.bottom()
                      - (d->layoutSpacing * (tablistcount%2 == 0 ?
                                                 tablistcount - 1 :
                                                 tablistcount - 2));
        if(tablistcount > 0)
        {
            trealisticSize = theight / tablistcount;
        }
    } else {
        int twidth = this->width() - d->layoutMargins.left()
                     - d->layoutMargins.right()
                     - (d->layoutSpacing * (tablistcount%2 == 0 ?
                                                tablistcount - 1 :
                                                tablistcount - 2));
        if(tablistcount > 0)
        {
            trealisticSize = twidth / tablistcount;
        }
    }
    d->realisticSize = trealisticSize > d->maxItemSize ? d->maxItemSize
                       : trealisticSize < d->minItemSize
                           ? d->minItemSize : trealisticSize;
    if(emitrealistic)
    {
        emit privateSignals->realsticSizeChanged(d->realisticSize, animationItem);
    }
}

void QCatGrayTabbar::updateRemoveItemRect(QCatGrayTabbarItem *item, bool animationItem)
{
    Q_D(QCatGrayTabbar);
    QRect lastrect = item->geometry();
    QRect rect;
    if(d->verticalTabs(this->shape()))
    {
        int realitywidth = this->width() - layoutmargins().left() - layoutmargins().right();
        item->setMinimumSize(realitywidth, 0);
        item->setMaximumSize(realitywidth, d->maxItemSize);
        rect.setRect(layoutmargins().left(),
                    item->getIndex() * d->realisticSize +
                    (item->getIndex() == 0 ? d->layoutMargins.top()
                        : (item->getIndex()+1) * d->layoutSpacing) + d->slidernum,
                    realitywidth,
                    d->realisticSize);
    } else {
        int realityheight = this->height() - layoutmargins().top() - layoutmargins().bottom();
        item->setMinimumSize(0, realityheight);
        item->setMaximumSize(d->maxItemSize, realityheight);
        rect.setRect(item->getIndex() * d->realisticSize +
                    (item->getIndex() == 0 ? d->layoutMargins.left()
                        : (item->getIndex()+1) * d->layoutSpacing) + d->slidernum,
                    layoutmargins().top(),
                    d->realisticSize,
                    realityheight);
    }
    if(lastrect != rect)
    {
        if(animationItem)
        {
            item->animationItem("geometry", durationMssecs, lastrect, rect);
        } else {
            item->setGeometry(rect);
        }
    }
}

void QCatGrayTabbar::updateWheelItemRect(QCatGrayTabbarItem *item, bool animationItem)
{
    Q_D(QCatGrayTabbar);
    QRect lastrect = item->geometry();
    QRect rect;
    if(d->verticalTabs(this->shape()))
    {
        int realitywidth = this->width() - layoutmargins().left() - layoutmargins().right();
        item->setMinimumSize(realitywidth, 0);
        item->setMaximumSize(realitywidth, d->maxItemSize);
        rect.setRect(layoutmargins().left(),
                    item->getIndex() * d->realisticSize +
                    (item->getIndex() == 0 ? d->layoutMargins.top()
                        : (item->getIndex()+1) * d->layoutSpacing) + d->slidernum,
                    realitywidth,
                    d->realisticSize);
    } else {
        int realityheight = this->height() - layoutmargins().top() - layoutmargins().bottom();
        item->setMinimumSize(0, realityheight);
        item->setMaximumSize(d->maxItemSize, realityheight);
        rect.setRect(item->getIndex() * d->realisticSize +
                    (item->getIndex() == 0 ? d->layoutMargins.left()
                        : (item->getIndex()+1) * d->layoutSpacing) + d->slidernum,
                    layoutmargins().top(),
                    d->realisticSize,
                    realityheight);
    }
    if(lastrect != rect)
    {
        if(animationItem)
        {
            item->animationItem("geometry", durationMssecs, lastrect, rect);
        } else {
            item->setGeometry(rect);
        }
    }
}

void QCatGrayTabbar::updateWheelSlidernum(QWheelEvent *event, bool animationItem)
{
    Q_D(QCatGrayTabbar);
    bool iswheel = false;
    int contentSliderSize = -99999;
    if(d->verticalTabs(this->shape()))
    {
        if(d->contentSize() > this->height())
        {
            iswheel = true;
            contentSliderSize = this->height();
        }
        lastSzie = currentSize;
        currentSize = this->height();
    } else {
        if(d->contentSize() > this->width())
        {
            iswheel = true;
            contentSliderSize = this->width();
        }
        lastSzie = currentSize;
        currentSize = this->width();
    }

    if(iswheel)
    {
        if(event != nullptr)
        {
            d->lastslidernum = d->slidernum;
            int angledeltay = event->angleDelta().y();
            int moveslidernum = d->slidernum + angledeltay;
            if(moveslidernum > 0)
            {
                d->slidernum = 0;
            } else {
                int contentslider = d->contentSlidernum(contentSliderSize);
                if(moveslidernum < contentslider)
                {
                    d->slidernum = contentslider;
                } else {
                    d->slidernum = moveslidernum;
                }
            }

            if(d->slidernum != d->lastslidernum)
            {
                privateSignals->wheelChanged(d->lastslidernum, d->slidernum, animationItem);
            }
        } else {
                if(d->slidernum < d->contentSlidernum(contentSliderSize))
                {
                    d->slidernum = d->contentSlidernum(contentSliderSize);
                    if(d->slidernum != d->lastslidernum)
                    {
                        d->lastslidernum = d->slidernum;
                        privateSignals->wheelChanged(d->lastslidernum, d->slidernum, animationItem);
                    }
                }
        }
    } else {
        d->slidernum = 0;
        if(d->slidernum != d->lastslidernum)
        {
            d->lastslidernum = d->slidernum;
            privateSignals->wheelChanged(d->lastslidernum, d->slidernum, animationItem);
        }
    }
}

void QCatGrayTabbar::updateMoveItem(QCatGrayTabbarItem *item, QPoint point)
{
    Q_D(QCatGrayTabbar);
    if(item->isMoveState())
    {
        QPoint itemmapFromParent = item->geometry().topLeft() + point;

        if(d->verticalTabs(this->shape()))
        {
            if(point.y() < 0)
            {
                privateSignals->setItemMoveState(QCatGrayTabbarPrivateSignals::LEFTORTOPSTATE);
            } else if(point.y() > 0) {
                privateSignals->setItemMoveState(QCatGrayTabbarPrivateSignals::RIGHTORBOTTOMSTATE);
            }
            item->setGeometry(QRect(this->layoutmargins().left(), itemmapFromParent.y(), item->width(), item->height()));
        } else {
            if(point.x() < 0)
            {
                privateSignals->setItemMoveState(QCatGrayTabbarPrivateSignals::LEFTORTOPSTATE);
            } else if(point.x() > 0) {
                privateSignals->setItemMoveState(QCatGrayTabbarPrivateSignals::RIGHTORBOTTOMSTATE);
            }
            item->setGeometry(QRect(itemmapFromParent.x(), this->layoutmargins().top(), item->width(), item->height()));
        }

    }
}

void QCatGrayTabbar::updateNotMoveItem(QCatGrayTabbarItem *moveitem, QCatGrayTabbarItem *notmoveitem)
{
    Q_D(QCatGrayTabbar);
    if(moveitem != nullptr && notmoveitem != nullptr)
    {
        QRect notmoveitemRect = notmoveitem->geometry();
        QRect moveitemRect = moveitem->geometry();
        int notmoveitemindex = notmoveitem->getIndex();
        int moveitemindex = moveitem->getIndex();
        bool isswap = false;
        if(d->verticalTabs(this->shape()))
        {
            if(privateSignals->itemMoveState() == QCatGrayTabbarPrivateSignals::LEFTORTOPSTATE)
            {
                if(moveitemRect.top() < notmoveitemRect.center().y() && moveitem->getIndex() > notmoveitem->getIndex())
                {
                    isswap = true;
                }
            } else if(privateSignals->itemMoveState() == QCatGrayTabbarPrivateSignals::RIGHTORBOTTOMSTATE) {
                if(moveitemRect.bottom() > notmoveitemRect.center().y() && moveitem->getIndex() < notmoveitem->getIndex())
                {
                    isswap = true;
                }
            }
        } else {
            if(privateSignals->itemMoveState() == QCatGrayTabbarPrivateSignals::LEFTORTOPSTATE)
            {
                if(moveitemRect.left() < notmoveitemRect.center().x() && moveitem->getIndex() > notmoveitem->getIndex())
                {
                    isswap = true;
                }
            } else if(privateSignals->itemMoveState() == QCatGrayTabbarPrivateSignals::RIGHTORBOTTOMSTATE) {
                if(moveitemRect.right() > notmoveitemRect.center().x() && moveitem->getIndex() < notmoveitem->getIndex())
                {
                    isswap = true;
                }
            }
        }
        if(isswap)
        {
            notmoveitem->setIndex(moveitemindex);
            moveitem->setIndex(notmoveitemindex);
            d->tabList.move(moveitemindex, notmoveitemindex);
            updateInsertItemRect(notmoveitem, true);
        }
    }
}

void QCatGrayTabbar::wheelEvent(QWheelEvent *event)
{
    updateWheelSlidernum(event, true);
}

void QCatGrayTabbar::resizeEvent(QResizeEvent *event)
{
    updateWheelSlidernum(nullptr, false);
    updateRealisticSize();
}

void QCatGrayTabbar::setCurrentIndex(int index)
{
    Q_D(QCatGrayTabbar);
    if(d->validIndex(index) && d->currentIndex != index)
    {
        d->currentIndex = index;
        emit currentChanged(index);
    }
}

QCatGrayTabbarPrivate::QCatGrayTabbarPrivate()
    : currentIndex(0), shape(QCatGrayTabbar::North),
        scrollbuttonPosition(QCatGrayTabbar::DownOrRightSideScrool),
        layoutMargins(QMargins(1,1,1,1)), layoutSpacing(1),
        minItemSize(100), maxItemSize(150),realisticSize(100),
        lastslidernum(0), slidernum(0)
{
    tabList.clear();
}

QCatGrayTabbarPrivate::~QCatGrayTabbarPrivate()
{

}

bool QCatGrayTabbarPrivate::verticalTabs(QCatGrayTabbar::Shape shape)
{
    return shape == QCatGrayTabbar::West
            || shape == QCatGrayTabbar::East;
}

int QCatGrayTabbarPrivate::contentSize() const
{
    int contentSize = 0;
    int tablistcount = tabList.count();
    int spacingsnum = layoutSpacing * (tablistcount%2 == 0 ?
                                           tablistcount - 1 :
                                           tablistcount - 2);
    if(tablistcount > 0)
    {
        if(this->verticalTabs(this->shape))
        {
            contentSize = (tablistcount * realisticSize) + spacingsnum + layoutMargins.top() + layoutMargins.bottom();
        } else {
            contentSize = (tablistcount * realisticSize) + spacingsnum + layoutMargins.left() + layoutMargins.right();
        }
    }
    return contentSize;
}

int QCatGrayTabbarPrivate::contentSlidernum(int size)
{
    return size - contentSize();
}

void QCatGrayTabbarPrivate::_q_scrollTabs()
{
    Q_Q(QCatGrayTabbar);
}

void QCatGrayTabbarPrivate::_q_closeTab()
{
    Q_Q(QCatGrayTabbar);
}

void QCatGrayTabbarPrivate::refresh()
{

}

void QCatGrayTabbarPrivateSignals::setItemMoveState(ITEMMOVESTATE state)
{
    if(mItemMoveState != state)
    {
        mItemMoveState = state;
        emit itemMoveStateChanged();
    }
}

QT_END_NAMESPACE

#include "moc_QCatGrayTabbar.cpp"
//#include "QCatGrayTabbar.moc"
