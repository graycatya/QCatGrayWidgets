#include "QCatGrayListingOptions.h"
#include <QFile>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QSharedPointer>

QCatGrayListingOptions::QCatGrayListingOptions(QCatGrayListingOptions::LAYOUT layout, QWidget *parent)
 : QWidget(parent)
 , m_yLayout(layout)
 , m_pItem_left(nullptr)
 , m_pItem_right(nullptr)
{
    InitUi();

    InitProperty();
}

QCatGrayListingOptions::~QCatGrayListingOptions()
{

}

void QCatGrayListingOptions::AddButton(QPushButton *button, int id, int row, int colum, Qt::Alignment alignment)
{
    switch (m_yLayout) {
        case VBox: {
            static_cast<QVBoxLayout*>(m_pButtonListsLayout)->addWidget(button);
            break;
        }
        case HBox: {
            static_cast<QHBoxLayout*>(m_pButtonListsLayout)->addWidget(button);
            break;
        }
        case Grid: {
            static_cast<QGridLayout*>(m_pButtonListsLayout)->addWidget(button, row, colum,  alignment);
            break;
        }
    }
    button->setCheckable(true);
    m_pButtonGroup->addButton(button, id);
    //button->setChecked(true);
}

void QCatGrayListingOptions::AddButtonNoGroup(QPushButton *button, int row, int colum, Qt::Alignment alignment)
{
    switch (m_yLayout) {
        case VBox: {
            static_cast<QVBoxLayout*>(m_pButtonListsLayout)->addWidget(button);
            break;
        }
        case HBox: {
            static_cast<QHBoxLayout*>(m_pButtonListsLayout)->addWidget(button);
            break;
        }
        case Grid: {
            static_cast<QGridLayout*>(m_pButtonListsLayout)->addWidget(button, row, colum,  alignment);
            break;
        }
    }
}

void QCatGrayListingOptions::AddWidget(QWidget *widget, int row, int colum, Qt::Alignment alignment)
{
    switch (m_yLayout) {
        case VBox: {
            static_cast<QVBoxLayout*>(m_pButtonListsLayout)->addWidget(widget);
            break;
        }
        case HBox: {
            static_cast<QHBoxLayout*>(m_pButtonListsLayout)->addWidget(widget);
            break;
        }
        case Grid: {
            static_cast<QGridLayout*>(m_pButtonListsLayout)->addWidget(widget, row, colum,  alignment);
            break;
        }
    }
}

void QCatGrayListingOptions::AddItem(QSpacerItem *item, int row, int colum, Qt::Alignment alignment)
{
    switch (m_yLayout) {
        case VBox: {
            static_cast<QVBoxLayout*>(m_pButtonListsLayout)->addItem(item);
            break;
        }
        case HBox: {
            static_cast<QHBoxLayout*>(m_pButtonListsLayout)->addItem(item);
            break;
        }
        case Grid: {
            static_cast<QGridLayout*>(m_pButtonListsLayout)->addItem(item, row, colum,  alignment);
            break;
        }
    }
}

QWidget *QCatGrayListingOptions::GetRootWidget() const
{
    return m_pButtonLists;
}

QWidget *QCatGrayListingOptions::GetWidget() const
{
    return m_pRootWidget;
}

QButtonGroup *QCatGrayListingOptions::GetButtonGroup() const
{
    return m_pButtonGroup;
}

void QCatGrayListingOptions::Clear()
{
    for(auto button : m_lButtonList)
    {
        switch (m_yLayout) {
            case VBox: {
                static_cast<QVBoxLayout*>(m_pButtonListsLayout)->removeWidget(button);
                break;
            }
            case HBox: {
                static_cast<QHBoxLayout*>(m_pButtonListsLayout)->removeWidget(button);
                break;
            }
            case Grid: {
                static_cast<QGridLayout*>(m_pButtonListsLayout)->removeWidget(button);
                break;
            }
        }
        m_pButtonGroup->removeButton(button);
    }
    for(auto item : m_lItemList)
    {
        switch (m_yLayout) {
            case VBox: {
                static_cast<QVBoxLayout*>(m_pButtonListsLayout)->removeItem(item);
                break;
            }
            case HBox: {
                static_cast<QHBoxLayout*>(m_pButtonListsLayout)->removeItem(item);
                break;
            }
            case Grid: {
                static_cast<QGridLayout*>(m_pButtonListsLayout)->removeItem(item);
                break;
            }
        }
    }
}

void *QCatGrayListingOptions::GetButtonlayout()
{
    return m_pButtonListsLayout;
}

void QCatGrayListingOptions::RemoveBackGaugeItem()
{

    switch (m_yLayout) {
        case VBox: {
            static_cast<QVBoxLayout*>(m_pHboxLayoutButton)->removeItem(m_pItem_left);
            static_cast<QVBoxLayout*>(m_pHboxLayoutButton)->removeItem(m_pItem_right);
            break;
        }
        case HBox: {
            static_cast<QHBoxLayout*>(m_pHboxLayoutButton)->removeItem(m_pItem_left);
            static_cast<QHBoxLayout*>(m_pHboxLayoutButton)->removeItem(m_pItem_right);
            break;
        }
        case Grid: {
            static_cast<QVBoxLayout*>(m_pHboxLayoutButton)->removeItem(m_pItem_left);
            static_cast<QVBoxLayout*>(m_pHboxLayoutButton)->removeItem(m_pItem_right);
            break;
        }
    }

}

void QCatGrayListingOptions::RemoveItem(QSpacerItem *item)
{
    switch (m_yLayout) {
        case VBox: {
            static_cast<QVBoxLayout*>(m_pButtonListsLayout)->removeItem(item);
            break;
        }
        case HBox: {
            static_cast<QHBoxLayout*>(m_pButtonListsLayout)->removeItem(item);
            break;
        }
        case Grid: {
            static_cast<QGridLayout*>(m_pButtonListsLayout)->removeItem(item);
            break;
        }
    }
}

void QCatGrayListingOptions::RemoveWidget(QWidget *widget)
{
    switch (m_yLayout) {
        case VBox: {
            static_cast<QVBoxLayout*>(m_pButtonListsLayout)->removeWidget(widget);
            break;
        }
        case HBox: {
            static_cast<QHBoxLayout*>(m_pButtonListsLayout)->removeWidget(widget);
            break;
        }
        case Grid: {
            static_cast<QGridLayout*>(m_pButtonListsLayout)->removeWidget(widget);
            break;
        }
    }
}

void QCatGrayListingOptions::InitUi()
{
    m_pRootLayout = new QVBoxLayout(this);
    m_pRootLayout->setContentsMargins(0,0,0,0);
    m_pRootLayout->setSpacing(0);

    m_pRootWidget = new QWidget(this);
    m_pRootWidget->setObjectName("ListiongOptionsRootWidget");
    m_pRootLayout->addWidget(m_pRootWidget);

    m_pRootWidgetLayout = new QVBoxLayout(m_pRootWidget);
    m_pRootWidgetLayout->setContentsMargins(0,0,0,0);
    m_pRootWidgetLayout->setSpacing(0);
    m_pScrollArea = new QScrollArea(m_pRootWidget);
    m_pScrollArea->setObjectName("ListingOptionsScroll");
    m_pScrollArea->setWidgetResizable(true);
    //m_pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_pRootWidgetLayout->addWidget(m_pScrollArea);

    m_pButtonLists = new QWidget();
    m_pButtonLists->setObjectName(QString::fromUtf8("ButtonLists"));
    m_pScrollArea->setWidget(m_pButtonLists);

    QSpacerItem *item_0 = nullptr;
    QSpacerItem *item_1 = nullptr;
    switch (m_yLayout) {
        case VBox: {
            m_pHboxLayoutButton = new QHBoxLayout(m_pButtonLists);
            static_cast<QHBoxLayout*>(m_pHboxLayoutButton)->setContentsMargins(0,0,0,0);
            static_cast<QHBoxLayout*>(m_pHboxLayoutButton)->setSpacing(0);
            item_0 = new QSpacerItem(5, 5, QSizePolicy::Expanding, QSizePolicy::Expanding);
            item_1 = new QSpacerItem(5, 5, QSizePolicy::Expanding, QSizePolicy::Expanding);
            static_cast<QHBoxLayout*>(m_pHboxLayoutButton)->addItem(item_0);
            m_pButtonListsLayout = new QVBoxLayout();
            static_cast<QVBoxLayout*>(m_pButtonListsLayout)->setContentsMargins(0,0,0,0);
            static_cast<QVBoxLayout*>(m_pButtonListsLayout)->setSpacing(0);
            static_cast<QHBoxLayout*>(m_pHboxLayoutButton)->addLayout(static_cast<QVBoxLayout*>(m_pButtonListsLayout));
            static_cast<QHBoxLayout*>(m_pHboxLayoutButton)->addItem(item_1);
            break;
        }
        case HBox: {
            m_pHboxLayoutButton = new QVBoxLayout(m_pButtonLists);
            static_cast<QVBoxLayout*>(m_pHboxLayoutButton)->setContentsMargins(0,0,0,0);
            static_cast<QVBoxLayout*>(m_pHboxLayoutButton)->setSpacing(0);
            item_0 = new QSpacerItem(5, 5, QSizePolicy::Expanding, QSizePolicy::Expanding);
            item_1 = new QSpacerItem(5, 5, QSizePolicy::Expanding, QSizePolicy::Expanding);
            static_cast<QVBoxLayout*>(m_pHboxLayoutButton)->addItem(item_0);
            m_pButtonListsLayout = new QHBoxLayout();
            static_cast<QHBoxLayout*>(m_pButtonListsLayout)->setContentsMargins(0,0,0,0);
            static_cast<QHBoxLayout*>(m_pButtonListsLayout)->setSpacing(0);
            static_cast<QHBoxLayout*>(m_pHboxLayoutButton)->addLayout(static_cast<QHBoxLayout*>(m_pButtonListsLayout));
            static_cast<QVBoxLayout*>(m_pHboxLayoutButton)->addItem(item_1);
            break;
        }
        case Grid: {
            m_pHboxLayoutButton = new QHBoxLayout(m_pButtonLists);
            static_cast<QVBoxLayout*>(m_pHboxLayoutButton)->setContentsMargins(0,0,0,0);
            static_cast<QVBoxLayout*>(m_pHboxLayoutButton)->setSpacing(0);
            item_0 = new QSpacerItem(5, 5, QSizePolicy::Expanding, QSizePolicy::Expanding);
            item_1 = new QSpacerItem(5, 5, QSizePolicy::Expanding, QSizePolicy::Expanding);
            static_cast<QHBoxLayout*>(m_pHboxLayoutButton)->addItem(item_0);
            m_pButtonListsLayout = new QGridLayout();
            static_cast<QVBoxLayout*>(m_pButtonListsLayout)->setContentsMargins(0,0,0,0);
            static_cast<QVBoxLayout*>(m_pButtonListsLayout)->setSpacing(0);
            static_cast<QHBoxLayout*>(m_pHboxLayoutButton)->addLayout(static_cast<QVBoxLayout*>(m_pButtonListsLayout));
            static_cast<QHBoxLayout*>(m_pHboxLayoutButton)->addItem(item_1);
            break;
        }
    }

    if(item_0 != nullptr)
    {
        m_pItem_left = item_0;
    }
    if(item_1 != nullptr)
    {
        m_pItem_right = item_1;
    }

    m_pButtonGroup = new QButtonGroup(m_pButtonLists);
    m_pButtonGroup->setExclusive(true);
}

void QCatGrayListingOptions::InitProperty()
{
    m_lButtonList.clear();
    m_pRootWidget->installEventFilter(this);
    m_pRootWidget->setMouseTracking(true);
    m_pScrollArea->installEventFilter(this);
    m_pScrollArea->setMouseTracking(true);
    m_pButtonLists->installEventFilter(this);
    m_pButtonLists->setMouseTracking(true);
    /*QFile resourceqss(":/qss/CatGray/ListingOptions.css");
    resourceqss.open(QFile::ReadOnly);
    this->setStyleSheet(resourceqss.readAll());
    resourceqss.close();*/
}

bool QCatGrayListingOptions::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched, event);
}

void QCatGrayListingOptions::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
}
