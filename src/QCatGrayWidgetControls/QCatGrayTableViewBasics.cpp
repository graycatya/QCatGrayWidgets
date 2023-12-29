﻿#include "QCatGrayTableViewBasics.h"
#include <QHeaderView>
#include <QAbstractSlider>
#include <QScrollBar>
#include <QDebug>

QCatGrayTableViewBasics::QCatGrayTableViewBasics(QWidget *parent)
    : QTableView(parent)
{

    hideHeader();

    initTable();

    // 将两个表视图的标题和滚动条连接在一起
    connect(horizontalHeader(),&QHeaderView::sectionResized, this,
            &QCatGrayTableViewBasics::updateSectionWidth);
    connect(verticalHeader(),&QHeaderView::sectionResized, this,
            &QCatGrayTableViewBasics::updateSectionHeight);

}

QCatGrayTableViewBasics::~QCatGrayTableViewBasics()
{
    DisconnectSelectColumn();
    DisconnectSelectRow();
}

void QCatGrayTableViewBasics::setModel(QAbstractItemModel *model)
{
    QTableView::setModel(model);
}

void QCatGrayTableViewBasics::FrostTableHead(int row)
{
    if(m_pTopTableWidget == nullptr)
    {
        m_iFrostRow = row;
        InitTopTable();
        if(m_pLeftTableWidget)
        {
            InitIntersectionTable();
            m_pIntersectionWidget->show();
        }
        updateFrozenTableGeometry(); //更新位置
        m_pTopTableWidget->show();
    }
}

void QCatGrayTableViewBasics::CancelTableHead()
{
    if(m_pTopTableWidget != nullptr)
    {
        delete m_pTopTableWidget;
        m_pTopTableWidget = nullptr;
    }
    CancelTableIntersection();
    updateFrozenTableGeometry();
}

void QCatGrayTableViewBasics::FrostTableLeft(int column)
{
    if(m_pLeftTableWidget == nullptr)
    {
        m_iFrostColumn = column;
        InitLeftTable();
        if(m_pTopTableWidget)
        {
            InitIntersectionTable();
            m_pIntersectionWidget->show();
        }
        updateFrozenTableGeometry(); //更新位置
        m_pLeftTableWidget->show();
    }
}

void QCatGrayTableViewBasics::CancelTableLeft()
{
    if(m_pLeftTableWidget != nullptr)
    {
        delete m_pLeftTableWidget;
        m_pLeftTableWidget = nullptr;
    }
    CancelTableIntersection();
    updateFrozenTableGeometry();
}

QTableView *QCatGrayTableViewBasics::GetTopTableView()
{
    return m_pTopTableWidget;
}

QTableView *QCatGrayTableViewBasics::GetIntersectionView()
{
    return m_pIntersectionWidget;
}

QTableView *QCatGrayTableViewBasics::GetLeftTableView()
{
    return m_pLeftTableWidget;
}

void QCatGrayTableViewBasics::SetHorizontalHeaderSectionResizeMode(QHeaderView::ResizeMode mode)
{
    horizontalHeader()->setSectionResizeMode(mode);
    if(m_pTopTableWidget) m_pTopTableWidget->horizontalHeader()->setSectionResizeMode(mode);
    if(m_pLeftTableWidget) m_pLeftTableWidget->horizontalHeader()->setSectionResizeMode(mode);
    if(m_pIntersectionWidget) m_pIntersectionWidget->horizontalHeader()->setSectionResizeMode(mode);
    updateEditorGeometries();
}

void QCatGrayTableViewBasics::SetVerticalHeaderSectionResizeMode(QHeaderView::ResizeMode mode)
{
    verticalHeader()->setSectionResizeMode(mode);
    if(m_pTopTableWidget) m_pTopTableWidget->verticalHeader()->setSectionResizeMode(mode);
    if(m_pLeftTableWidget) m_pLeftTableWidget->verticalHeader()->setSectionResizeMode(mode);
    if(m_pIntersectionWidget) m_pIntersectionWidget->verticalHeader()->setSectionResizeMode(mode);
    updateEditorGeometries();
}

void QCatGrayTableViewBasics::ShowHorizontalHeader()
{
    horizontalHeader()->show();
    if(m_pTopTableWidget) m_pTopTableWidget->horizontalHeader()->show();
    if(m_pLeftTableWidget) m_pLeftTableWidget->horizontalHeader()->show();
    if(m_pIntersectionWidget) m_pIntersectionWidget->horizontalHeader()->show();
    updateEditorGeometries();
}

void QCatGrayTableViewBasics::HideHorizontalHeader()
{
    horizontalHeader()->hide();
    if(m_pTopTableWidget) m_pTopTableWidget->horizontalHeader()->hide();
    if(m_pLeftTableWidget) m_pLeftTableWidget->horizontalHeader()->hide();
    if(m_pIntersectionWidget) m_pIntersectionWidget->horizontalHeader()->hide();
    updateEditorGeometries();
}

void QCatGrayTableViewBasics::ShowVerticalHeader()
{
    verticalHeader()->show();
    if(m_pTopTableWidget) m_pTopTableWidget->verticalHeader()->show();
    if(m_pLeftTableWidget) m_pLeftTableWidget->verticalHeader()->show();
    if(m_pIntersectionWidget) m_pIntersectionWidget->verticalHeader()->show();
    updateEditorGeometries();
}

void QCatGrayTableViewBasics::HideVerticalHeader()
{
    verticalHeader()->hide();
    if(m_pTopTableWidget) m_pTopTableWidget->verticalHeader()->hide();
    if(m_pLeftTableWidget) m_pLeftTableWidget->verticalHeader()->hide();
    if(m_pIntersectionWidget) m_pIntersectionWidget->verticalHeader()->hide();
    updateEditorGeometries();
}

void QCatGrayTableViewBasics::ConnectSelectColumn()
{
    if(!m_pThisTableSelectColumn)
    {
        m_pThisTableSelectColumn = connect(this, &QTableView::clicked, this, [=](const QModelIndex &index){
            if(index.row() == 0)
            {
                selectTableColumn(index.column());
            }
        });
    }
    if(m_pTopTableWidget && !m_pTopTableSelectColumn)
    {
        m_pTopTableSelectColumn = connect(m_pTopTableWidget, &QTableView::clicked, this, [=](const QModelIndex &index){
            if(index.row() == 0)
            {
                selectTableColumn(index.column());
            }
        });
    }
    if(m_pLeftTableWidget && !m_pLeftTableSelectColumn)
    {
        m_pLeftTableSelectColumn = connect(m_pLeftTableWidget, &QTableView::clicked, this, [=](const QModelIndex &index){
            if(index.row() == 0)
            {
                selectTableColumn(index.column());
            }
        });
    }
    if(m_pIntersectionWidget && !m_pIntersectionSelectColumn)
    {
        m_pIntersectionSelectColumn = connect(m_pIntersectionWidget, &QTableView::clicked, this, [=](const QModelIndex &index){
            if(index.row() == 0)
            {
                selectTableColumn(index.column());
            }
        });
    }
}

void QCatGrayTableViewBasics::DisconnectSelectColumn()
{
    disconnect(m_pThisTableSelectColumn);
    disconnect(m_pTopTableSelectColumn);
    disconnect(m_pLeftTableSelectColumn);
    disconnect(m_pIntersectionSelectColumn);
}

void QCatGrayTableViewBasics::ConnectSelectRow()
{
    if(!m_pThisTableSelectRow)
    {
        m_pThisTableSelectRow = connect(this, &QTableView::clicked, this, [=](const QModelIndex &index){
            if(index.column() == 0)
            {
                selectTableRow(index.row());
            }
        });
    }
    if(m_pTopTableWidget && !m_pTopTableSelectRow)
    {
        m_pTopTableSelectRow = connect(m_pTopTableWidget, &QTableView::clicked, this, [=](const QModelIndex &index){
            if(index.column() == 0)
            {
                selectTableRow(index.row());
            }
        });
    }
    if(m_pLeftTableWidget && !m_pLeftTableSelectRow)
    {
        m_pLeftTableSelectRow = connect(m_pLeftTableWidget, &QTableView::clicked, this, [=](const QModelIndex &index){
            if(index.column() == 0)
            {
                selectTableRow(index.row());
            }
        });
    }
    /*if(m_pIntersectionWidget && !m_pIntersectionSelectRow)
    {
        m_pIntersectionSelectRow = connect(m_pIntersectionWidget, &QTableView::clicked, this, [=](const QModelIndex &index){
            if(index.column() == 0)
            {
                selectTableRow(index.row());
            }
        });
    }*/
}

void QCatGrayTableViewBasics::DisconnectSelectRow()
{
    disconnect(m_pThisTableSelectRow);
    disconnect(m_pTopTableSelectRow);
    disconnect(m_pLeftTableSelectRow);
    disconnect(m_pIntersectionSelectRow);
}

void QCatGrayTableViewBasics::updateFrozenTableGeometry()
{
    if(m_pTopTableWidget && m_pLeftTableWidget)
    {
        m_pTopTableWidget->verticalHeader()->setMinimumWidth(verticalHeader()->width());
        m_pTopTableWidget->horizontalHeader()->setMinimumHeight(horizontalHeader()->height());
        m_pLeftTableWidget->verticalHeader()->setMinimumWidth(verticalHeader()->width());
        m_pLeftTableWidget->horizontalHeader()->setMinimumHeight(horizontalHeader()->height());
        m_pIntersectionWidget->verticalHeader()->setMinimumWidth(verticalHeader()->width());
        m_pIntersectionWidget->horizontalHeader()->setMinimumHeight(horizontalHeader()->height());
        int height = 0;
        int width = 0;
        for(int i = 0; i < m_iFrostRow; i++)
        {
            height += rowHeight(i);
        }
        for(int i = 0; i < m_iFrostColumn; i++)
        {
            width += columnWidth(i);
        }

        m_pIntersectionWidget->setGeometry((verticalHeader()->isVisible() ? 0 : verticalHeader()->width())
                                           + frameWidth(),
                                           (horizontalHeader()->isVisible() ? 0 : horizontalHeader()->height())
                                           + frameWidth(),
                                           (verticalHeader()->isVisible() ? verticalHeader()->width() : 0)
                                           + width,
                                           (horizontalHeader()->isVisible() ? horizontalHeader()->height() : 0)
                                           + height);

        m_pTopTableWidget->setGeometry((verticalHeader()->isVisible() ? 0 : verticalHeader()->width()) + frameWidth(),
                                       (horizontalHeader()->isVisible() ? 0 : horizontalHeader()->height()) + frameWidth(),
                                        (verticalHeader()->isVisible() ? verticalHeader()->width() : 0) + viewport()->width(),
                                        (horizontalHeader()->isVisible() ? horizontalHeader()->height() : 0) + height);

        m_pLeftTableWidget->setGeometry((verticalHeader()->isVisible() ? 0 : verticalHeader()->width()) + frameWidth(),
                                        (horizontalHeader()->isVisible() ? 0 : horizontalHeader()->height()) + frameWidth(),
                                        (verticalHeader()->isVisible() ? verticalHeader()->width() : 0) + width,
                                        (horizontalHeader()->isVisible() ? horizontalHeader()->height() : 0) + viewport()->height());

        viewport()->stackUnder(m_pLeftTableWidget);//设置窗口层次
        viewport()->stackUnder(m_pIntersectionWidget);
        viewport()->stackUnder(m_pTopTableWidget);//设置窗口层次

    } else if(m_pTopTableWidget)
    {
        m_pTopTableWidget->verticalHeader()->setMinimumWidth(verticalHeader()->width());
        m_pTopTableWidget->horizontalHeader()->setMinimumHeight(horizontalHeader()->height());
        int height = 0;
        for(int i = 0; i < m_iFrostRow; i++)
        {
            height += rowHeight(i);
        }
        m_pTopTableWidget->setGeometry((verticalHeader()->isVisible() ? 0 : verticalHeader()->width()) + frameWidth(),
                                       (horizontalHeader()->isVisible() ? 0 : horizontalHeader()->height()) + frameWidth(),
                                        (verticalHeader()->isVisible() ? verticalHeader()->width() : 0) + viewport()->width(),
                                        (horizontalHeader()->isVisible() ? horizontalHeader()->height() : 0) + height);
    } else if(m_pLeftTableWidget)
    {
        m_pLeftTableWidget->verticalHeader()->setMinimumWidth(verticalHeader()->width());
        m_pLeftTableWidget->horizontalHeader()->setMinimumHeight(horizontalHeader()->height());
        int width = 0;
        for(int i = 0; i < m_iFrostColumn; i++)
        {
            width += columnWidth(i);
        }
        m_pLeftTableWidget->setGeometry((verticalHeader()->isVisible() ? 0 : verticalHeader()->width()) + frameWidth(),
                                        (horizontalHeader()->isVisible() ? 0 : horizontalHeader()->height()) + frameWidth(),
                                        (verticalHeader()->isVisible() ? verticalHeader()->width() : 0) + width,
                                        (horizontalHeader()->isVisible() ? horizontalHeader()->height() : 0) + viewport()->height());
    }
}

void QCatGrayTableViewBasics::InitTopTable()
{
    m_pTopTableWidget = new QTableView(this);
    m_pTopTableWidget->setObjectName("CatTopTableWidget");
    m_pTopTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //隐藏滚动条
    m_pTopTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //
    m_pTopTableWidget->setHorizontalScrollMode(ScrollPerPixel);
    m_pTopTableWidget->setVerticalScrollMode(ScrollPerPixel);
    m_pTopTableWidget->setFocusPolicy(Qt::NoFocus);

    m_pTopTableWidget->setModel(model());

    viewport()->stackUnder(m_pTopTableWidget);//设置窗口层次

    m_pTopTableWidget->setSelectionModel(selectionModel());
    for (int row = m_iFrostRow; row < model()->rowCount(); ++row)
          m_pTopTableWidget->setRowHidden(row, true);

    connect(m_pTopTableWidget->horizontalHeader(),&QHeaderView::sectionResized, this,
            &QCatGrayTableViewBasics::updateSectionWidth);
    connect(m_pTopTableWidget->verticalHeader(),&QHeaderView::sectionResized, this,
            &QCatGrayTableViewBasics::updateSectionHeight);

    //连接信号槽, 用于滚动条联动
    connect(m_pTopTableWidget->horizontalScrollBar(), &QAbstractSlider::valueChanged,
            horizontalScrollBar(), &QAbstractSlider::setValue);
    connect(horizontalScrollBar(), &QAbstractSlider::valueChanged,
            m_pTopTableWidget->horizontalScrollBar(), &QAbstractSlider::setValue);

    connect(m_pTopTableWidget->verticalScrollBar(), &QScrollBar::valueChanged, this, [=](int value){
        Q_UNUSED(value)
        m_pTopTableWidget->verticalScrollBar()->setValue(0);
    });
    m_pTopTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pTopTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pTopTableWidget->show();

    setHorizontalScrollMode(ScrollPerPixel);
    setVerticalScrollMode(ScrollPerPixel);


}

void QCatGrayTableViewBasics::InitLeftTable()
{
    m_pLeftTableWidget = new QTableView(this);
    m_pLeftTableWidget->setObjectName("CatLeftTableWidget");
    m_pLeftTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏滚动条
    m_pLeftTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//
    m_pLeftTableWidget->setHorizontalScrollMode(ScrollPerPixel);
    m_pLeftTableWidget->setFocusPolicy(Qt::NoFocus);

    m_pLeftTableWidget->setModel(model());

    viewport()->stackUnder(m_pLeftTableWidget);//设置窗口层次

    m_pLeftTableWidget->setSelectionModel(selectionModel());
    for (int col = m_iFrostColumn; col < model()->columnCount(); ++col)
          m_pLeftTableWidget->setColumnHidden(col, true);

    connect(m_pLeftTableWidget->horizontalHeader(),&QHeaderView::sectionResized, this,
            &QCatGrayTableViewBasics::updateSectionWidth);
    connect(m_pLeftTableWidget->verticalHeader(),&QHeaderView::sectionResized, this,
            &QCatGrayTableViewBasics::updateSectionHeight);

    //连接信号槽, 用于滚动条联动
    connect(m_pLeftTableWidget->verticalScrollBar(), &QAbstractSlider::valueChanged,
            verticalScrollBar(), &QAbstractSlider::setValue);
    connect(verticalScrollBar(), &QAbstractSlider::valueChanged,
            m_pLeftTableWidget->verticalScrollBar(), &QAbstractSlider::setValue);

    connect(m_pLeftTableWidget->horizontalScrollBar(), &QScrollBar::valueChanged, this, [=](int value){
        Q_UNUSED(value)
        m_pLeftTableWidget->horizontalScrollBar()->setValue(0);
    });

    m_pLeftTableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pLeftTableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pLeftTableWidget->show();

    setHorizontalScrollMode(ScrollPerPixel);
    setVerticalScrollMode(ScrollPerPixel);
    m_pLeftTableWidget->setVerticalScrollMode(ScrollPerPixel);
}

void QCatGrayTableViewBasics::InitIntersectionTable()
{
    m_pIntersectionWidget = new QTableView(this);
    m_pIntersectionWidget->setObjectName("CatIntersectionWidget");
    m_pIntersectionWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//隐藏滚动条
    m_pIntersectionWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//
    m_pIntersectionWidget->setHorizontalScrollMode(ScrollPerPixel);
    m_pIntersectionWidget->setFocusPolicy(Qt::NoFocus);

    m_pIntersectionWidget->setModel(model());
    viewport()->stackUnder(m_pIntersectionWidget);//设置窗口层次
    m_pIntersectionWidget->setSelectionModel(selectionModel());
    for (int col = m_iFrostColumn; col < model()->columnCount(); ++col)
          m_pIntersectionWidget->setColumnHidden(col, true);
    for (int row = m_iFrostRow; row < model()->rowCount(); ++row)
          m_pIntersectionWidget->setRowHidden(row, true);

    connect(m_pIntersectionWidget->horizontalHeader(),&QHeaderView::sectionResized, this,
            &QCatGrayTableViewBasics::updateSectionWidth);
    connect(m_pIntersectionWidget->verticalHeader(),&QHeaderView::sectionResized, this,
            &QCatGrayTableViewBasics::updateSectionHeight);

    connect(m_pIntersectionWidget->verticalScrollBar(), &QScrollBar::valueChanged, this, [=](int value){
        Q_UNUSED(value)
        m_pIntersectionWidget->verticalScrollBar()->setValue(0);
    });

    //连接信号槽, 用于滚动条联动
    /*connect(m_pIntersectionWidget->verticalScrollBar(), &QAbstractSlider::valueChanged,
            verticalScrollBar(), &QAbstractSlider::setValue);
    connect(verticalScrollBar(), &QAbstractSlider::valueChanged,
            m_pIntersectionWidget->verticalScrollBar(), &QAbstractSlider::setValue);*/

    m_pIntersectionWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pIntersectionWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pIntersectionWidget->show();

    setHorizontalScrollMode(ScrollPerPixel);
    setVerticalScrollMode(ScrollPerPixel);
    m_pIntersectionWidget->setVerticalScrollMode(ScrollPerPixel);
}

void QCatGrayTableViewBasics::CancelTableIntersection()
{
    if(m_pIntersectionWidget != nullptr)
    {
        delete m_pIntersectionWidget;
        m_pIntersectionWidget = nullptr;
    }
}

void QCatGrayTableViewBasics::initTable()
{

}

void QCatGrayTableViewBasics::resizeEvent(QResizeEvent *event)
{
    QTableView::resizeEvent(event);
    updateFrozenTableGeometry();
}

QModelIndex QCatGrayTableViewBasics::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);
    if(m_pTopTableWidget && m_pLeftTableWidget)
    {
        int width = 0;
        for(int i = 0; i < m_iFrostColumn; i++)
        {
            width += columnWidth(i);
        }
        int height = 0;
        for(int i = 0; i < m_iFrostRow; i++)
        {
            height += rowHeight(i);
        }
        if (cursorAction == MoveLeft && current.column() > 0
                && visualRect(current).topLeft().x() < width ){
              const int newValue = horizontalScrollBar()->value() + visualRect(current).topLeft().x()
                                   - width;
              horizontalScrollBar()->setValue(newValue);
        }
        if (cursorAction == MoveUp && current.row() > 0
                && visualRect(current).topLeft().y() < height ){
              const int newValue = verticalScrollBar()->value() + visualRect(current).topLeft().x()
                                   - height;
              verticalScrollBar()->setValue(newValue);
        }
    }
    else if(m_pLeftTableWidget)
    {
        int width = 0;
        for(int i = 0; i < m_iFrostColumn; i++)
        {
            width += columnWidth(i);
        }
        if (cursorAction == MoveLeft && current.column() > 0
                && visualRect(current).topLeft().x() < width ){
              const int newValue = horizontalScrollBar()->value() + visualRect(current).topLeft().x()
                                   - width;
              horizontalScrollBar()->setValue(newValue);
        }
    }
    else if(m_pTopTableWidget)
    {
        int height = 0;
        for(int i = 0; i < m_iFrostRow; i++)
        {
            height += rowHeight(i);
        }
        int width = 0;
        for(int i = 0; i < m_iFrostColumn; i++)
        {
            width += columnWidth(i);
        }
        if (cursorAction == MoveUp && current.row() > 0
                && visualRect(current).topLeft().x() < width ){
              const int newValue = verticalScrollBar()->value() + visualRect(current).topLeft().x()
                                   - width;
              verticalScrollBar()->setValue(newValue);
        }
    }

    return current;
}

void QCatGrayTableViewBasics::scrollTo(const QModelIndex &index, ScrollHint hint)
{
    QTableView::scrollTo(index, hint);
}

void QCatGrayTableViewBasics::hideHeader()
{
    this->verticalHeader()->hide();
    this->horizontalHeader()->hide();
}

void QCatGrayTableViewBasics::updateSectionWidth(int logicalIndex, int oldSize, int newSize)
{
    if(m_pTopTableWidget)
    {
        m_pTopTableWidget->setColumnWidth(logicalIndex, newSize);
    }
    if(m_pLeftTableWidget)
    {
        m_pLeftTableWidget->setColumnWidth(logicalIndex, newSize);
    }
    if(m_pIntersectionWidget)
    {
        m_pIntersectionWidget->setColumnWidth(logicalIndex, newSize);
    }
    this->setColumnWidth(logicalIndex, newSize);
    updateFrozenTableGeometry();
}

void QCatGrayTableViewBasics::updateSectionHeight(int logicalIndex, int oldSize, int newSize)
{
    if(m_pTopTableWidget)
    {
        m_pTopTableWidget->setRowHeight(logicalIndex, newSize);
    }
    if(m_pLeftTableWidget)
    {
        m_pLeftTableWidget->setRowHeight(logicalIndex, newSize);
    }
    if(m_pIntersectionWidget)
    {
        m_pIntersectionWidget->setRowHeight(logicalIndex, newSize);
    }
    this->setRowHeight(logicalIndex, newSize);
    updateFrozenTableGeometry();
}

void QCatGrayTableViewBasics::selectTableColumn(int column)
{
    this->selectColumn(column);
    if(m_pTopTableWidget)
    {
        m_pTopTableWidget->selectColumn(column);
    }
    if(m_pLeftTableWidget)
    {
        m_pLeftTableWidget->selectColumn(column);
    }
    if(m_pIntersectionWidget)
    {
        m_pIntersectionWidget->selectColumn(column);
    }
}

void QCatGrayTableViewBasics::selectTableRow(int row)
{
    this->selectRow(row);
    if(m_pTopTableWidget)
    {
        m_pTopTableWidget->selectRow(row);
    }
    if(m_pLeftTableWidget)
    {
        m_pLeftTableWidget->selectRow(row);
    }
    if(m_pIntersectionWidget)
    {
        m_pIntersectionWidget->selectRow(row);
    }
}
