#ifndef QCATGRAYTABBAR_H
#define QCATGRAYTABBAR_H

#include <QWidget>

QT_BEGIN_NAMESPACE

class QCatGrayTabbarPrivate;
class QCatGrayTabbarPrivateSignals;
class QCatGrayTabbarItem;
class CatMovableTabWidget;
class QPropertyAnimation;
class QSequentialAnimationGroup;
class QMouseEvent;

class QCatGrayTabbar : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(Shape shape READ shape WRITE setShape)
    Q_PROPERTY(ScrollbuttonPosition scrollbuttonPosition READ scrollbuttonPosition WRITE setScrollbuttonPosition)
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentChanged)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(QMargins layoutmargins READ layoutmargins WRITE setLayoutmargins NOTIFY layoutmarginsChanged)
    Q_PROPERTY(int minItemSize READ minItemSize WRITE setMinItemSize NOTIFY minItemSizeChanged)
    Q_PROPERTY(int maxItemSize READ maxItemSize WRITE setMaxItemSize NOTIFY maxItemSizeChanged)
    Q_PROPERTY(int realisticSize READ realisticSize NOTIFY realisticSizeChanged)
    Q_PROPERTY(int slidernum READ slidernum NOTIFY slidernumChanged)
    Q_PROPERTY(int contentSize READ contentSize)
public:
    explicit QCatGrayTabbar(QWidget *parent = nullptr);
    ~QCatGrayTabbar();

    enum Shape { North, South, West, East };
    Q_ENUM(Shape)

    enum ScrollbuttonPosition {
        UpOrLeftSideScrool,
        DownOrRightSideScrool,
        UpDownOrLeftRightSideScrool
    };
    Q_ENUM(ScrollbuttonPosition)

    Shape shape() const;
    void setShape(Shape shape);

    int currentIndex() const;
    int count() const;

    ScrollbuttonPosition scrollbuttonPosition() const;
    void setScrollbuttonPosition(ScrollbuttonPosition scrollbuttonPosition);

    QMargins layoutmargins() const;
    void setLayoutmargins(QMargins layoutmargins);

    void addItem(QCatGrayTabbarItem *item);
    void removeItem(int index);
    void insertItem(int index, QCatGrayTabbarItem *item);

    int minItemSize() const;
    void setMinItemSize(int size);

    int maxItemSize() const;
    void setMaxItemSize(int size);

    int realisticSize() const;

    int slidernum() const;

    int contentSize() const;

private:
    void updateItemRect(QCatGrayTabbarItem *item, bool animationItem = false);
    void updateInsertItemRect(QCatGrayTabbarItem *item, bool animationItem = false);
    void updateItemSize(QCatGrayTabbarItem *item);
    void updateRealisticSize(bool emitrealistic = true, bool animationItem = false);
    void updateRealisticSize(QCatGrayTabbarItem *item, bool animationItem = false);;
    void updatePrivateRealisticSize(bool emitrealistic = true, bool animationItem = false);
    void updateRemoveItemRect(QCatGrayTabbarItem *item, bool animationItem = false);
    void updateWheelItemRect(QCatGrayTabbarItem *item, bool animationItem = false);
    void updateWheelSlidernum(QWheelEvent *event, bool animationItem = false);
    void updateMoveItem(QCatGrayTabbarItem *item, QPoint point);
    void updateNotMoveItem(QCatGrayTabbarItem *moveitem, QCatGrayTabbarItem *notmoveitem);
protected:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
public Q_SLOTS:
    void setCurrentIndex(int index);

Q_SIGNALS:
    void currentChanged(int index);
    void layoutmarginsChanged();
    void minItemSizeChanged(int size);
    void maxItemSizeChanged(int size);
    void realisticSizeChanged(int size);
    void slidernumChanged(int num);

private:
    int durationMssecs;
    int lastSzie;
    int currentSize;

private:
    Q_DISABLE_COPY(QCatGrayTabbar)
    Q_DECLARE_PRIVATE(QCatGrayTabbar)
    Q_PRIVATE_SLOT(d_func(), void _q_scrollTabs())
    Q_PRIVATE_SLOT(d_func(), void _q_closeTab())

private:
    QCatGrayTabbarPrivateSignals *privateSignals = nullptr;
};

class QCatGrayTabbarItem : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText)
    Q_PROPERTY(int index READ getIndex WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(int minItemSize READ minItemSize WRITE setMinItemSize NOTIFY minItemSizeChanged)
    Q_PROPERTY(int maxItemSize READ maxItemSize WRITE setMaxItemSize NOTIFY maxItemSizeChanged)
    Q_PROPERTY(int realisticSize READ realisticSize WRITE setRealisticSize NOTIFY realisticSizeChanged)
    Q_PROPERTY(bool isMoveState READ isMoveState WRITE setIsMoveState NOTIFY isMoveStateChanged)
public:
    explicit QCatGrayTabbarItem(QCatGrayTabbar *parent = nullptr);
    ~QCatGrayTabbarItem();

    QString getText() { return mText; } const
    void setText(QString data) { this->mText = data; }
    void animationItem(const QByteArray &propertyName, int durationMssecs,
                       const QVariant &startValue, const QVariant &endValue);

    int getIndex() { return mIndex; } const
    void setIndex(int index) {
        if(mIndex != index)
        {
            mIndex = index;
            emit indexChanged();
            update();
        }
    }

    int minItemSize() const;
    void setMinItemSize(int size);

    int maxItemSize() const;
    void setMaxItemSize(int size);

    int realisticSize() const;
    void setRealisticSize(int size);

    bool isMoveState() const;


Q_SIGNALS:
    void indexChanged();
    void minItemSizeChanged(int size);
    void maxItemSizeChanged(int size);
    void realisticSizeChanged(int size);
    void moveItemChanged(QPoint point);
    void fremoveItemChanged();
    void isMoveStateChanged();

private:
    void setIsMoveState(bool state);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    QString mText = "";
    int mIndex = -1;
    int mMinItemSize = 0;
    int mMaxItemSize = 0;
    int mRealisticSize = 0;
    //QPropertyAnimation *animation = nullptr;
    QSequentialAnimationGroup *animationgroup = nullptr;
    bool isPress = false;
    bool mIsMoveState = false;
    QPoint mPressPoint = QPoint();
};

QT_END_NAMESPACE

#endif // QCatGrayTabbar_H
