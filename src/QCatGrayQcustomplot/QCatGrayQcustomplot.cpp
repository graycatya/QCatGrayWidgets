#include "QCatGrayQcustomplot.h"
#include "QCatGrayQcustomplotBars.h"

QCatGrayQcustomplot::QCatGrayQcustomplot(QWidget *parent)
    : QCustomPlot(parent)
{
    InitProperty();
}

QCatGrayQcustomplot::~QCatGrayQcustomplot()
{

}

QCPGraph *QCatGrayQcustomplot::AddGraph(QPen pen, QString name, QCPScatterStyle style, QCPGraph::LineStyle linestyle)
{
    QCPGraph *graph = this->addGraph();
    graph->setPen(pen);
    graph->setName(name);
    graph->setScatterStyle(style);
    graph->setLineStyle(linestyle);
    return graph;
}

QCPBars *QCatGrayQcustomplot::AddBars(int width, QPen pen, QBrush brush, QString name, QCPBars::WidthType type)
{
    QCatGrayQcustomplotBars *bars = new QCatGrayQcustomplotBars(xAxis, yAxis);
    m_pBars.push_back(bars);
    bars->setWidth(width);
    bars->setPen(pen);
    bars->setBrush(brush);
    bars->setWidthType(type);
    bars->setName(name);
    return bars;
}

QVector<QCPBars *> QCatGrayQcustomplot::GetBars()
{
    return m_pBars;
}

QStringList QCatGrayQcustomplot::ScatterShapeList()
{
    QStringList list;
    list.clear();
    QMetaEnum metaEnum = QMetaEnum::fromType<QCPScatterStyle::ScatterShape>();
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        list += metaEnum.valueToKey(metaEnum.value(i));
    }
    return list;
}

QStringList QCatGrayQcustomplot::GraphLineStyleList()
{
    QStringList list;
    list.clear();
    QMetaEnum metaEnum = QMetaEnum::fromType<QCPGraph::LineStyle>();
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        list += metaEnum.valueToKey(metaEnum.value(i));
    }
    return list;
}

QStringList QCatGrayQcustomplot::BarsWidthType()
{
    QStringList list;
    list.clear();
    QMetaEnum metaEnum = QMetaEnum::fromType<QCPBars::WidthType>();
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        list += metaEnum.valueToKey(metaEnum.value(i));
    }
    return list;
}

QStringList QCatGrayQcustomplot::TracerStyleList()
{
    QStringList list;
    list.clear();
    QMetaEnum metaEnum = QMetaEnum::fromType<QCPItemTracer::TracerStyle>();
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        list += metaEnum.valueToKey(metaEnum.value(i));
    }
    return list;
}

QStringList QCatGrayQcustomplot::PositionTypeList()
{
    QStringList list;
    list.clear();
    QMetaEnum metaEnum = QMetaEnum::fromType<QCPItemPosition::PositionType>();
    for (int i = 0; i < metaEnum.keyCount(); i++) {
        list += metaEnum.valueToKey(metaEnum.value(i));
    }
    return list;
}

void QCatGrayQcustomplot::SetLegenAlignment(int index, Qt::Alignment alignment)
{
    axisRect()->insetLayout()->setInsetAlignment(index, alignment);
}

void QCatGrayQcustomplot::InitProperty()
{
    //添加自定义类控制
    setAttribute(Qt::WA_StyledBackground,true);
}

void QCatGrayQcustomplot::mouseMoveEvent(QMouseEvent *event)
{
    QCustomPlot::mouseMoveEvent(event);
}

void QCatGrayQcustomplot::mousePressEvent(QMouseEvent *event)
{
    QCustomPlot::mousePressEvent(event);
}

void QCatGrayQcustomplot::SetBackground(QBrush brush)
{
    setBackground(brush);
}

void QCatGrayQcustomplot::SetLegendBackground(QBrush brush)
{
    legend->setBrush(brush);
}

void QCatGrayQcustomplot::SetLegendSelectBackground(QBrush brush)
{
    legend->setSelectedBrush(brush);
}

void QCatGrayQcustomplot::SetLegendFont(QFont font)
{
    legend->setFont(font);
}

void QCatGrayQcustomplot::SetLegendSelectFont(QFont font)
{
    legend->setSelectedFont(font);
}

void QCatGrayQcustomplot::SetLegendBorder(QPen border)
{
    legend->setBorderPen(border);
}

void QCatGrayQcustomplot::SetLegendSelectBorder(QPen border)
{
    legend->setSelectedBorderPen(border);
}

void QCatGrayQcustomplot::SetLegendBorderColor(QColor color)
{
    QPen pen = legend->borderPen();
    pen.setColor(color);
    legend->setBorderPen(pen);
}

void QCatGrayQcustomplot::SetLegendSelectBorderColor(QColor color)
{
    QPen pen = legend->selectedBorderPen();
    pen.setColor(color);
    legend->setSelectedBorderPen(pen);
}

void QCatGrayQcustomplot::SetLegendBorderWide(qint32 width)
{
    QPen pen = legend->borderPen();
    pen.setWidth(width);
    legend->setBorderPen(pen);
}

void QCatGrayQcustomplot::SetLegendSelectBorderWide(qint32 width)
{
    QPen pen = legend->selectedBorderPen();
    pen.setWidth(width);
    legend->setSelectedBorderPen(pen);
}

void QCatGrayQcustomplot::SetLegendTextColor(QColor color)
{
    legend->setTextColor(color);
}

void QCatGrayQcustomplot::SetLegendSelectTextColor(QColor color)
{
    legend->setSelectedTextColor(color);
}


void QCatGrayQcustomplot::SetAxisBasePen_x(QPen pen)
{
    xAxis->setBasePen(pen);
}

void QCatGrayQcustomplot::SetAxisBasePenWidth_x(int width)
{
    QPen pen = xAxis->basePen();
    pen.setWidth(width);
    xAxis->setBasePen(pen);
}

void QCatGrayQcustomplot::SetAxisBasePenColor_x(QColor color)
{
    QPen pen = xAxis->basePen();
    pen.setColor(color);
    xAxis->setBasePen(pen);
}

void QCatGrayQcustomplot::SetAxis2BasePen_x(QPen pen)
{
    xAxis2->setBasePen(pen);
}

void QCatGrayQcustomplot::SetAxis2BasePenWidth_x(int width)
{
    QPen pen = xAxis2->basePen();
    pen.setWidth(width);
    xAxis2->setBasePen(pen);
}

void QCatGrayQcustomplot::SetAxis2BasePenColor_x(QColor color)
{
    QPen pen = xAxis2->basePen();
    pen.setColor(color);
    xAxis2->setBasePen(pen);
}

void QCatGrayQcustomplot::SetAxisBasePen_y(QPen pen)
{
    yAxis->setBasePen(pen);
}

void QCatGrayQcustomplot::SetAxisBasePenWidth_y(int width)
{
    QPen pen = yAxis->basePen();
    pen.setWidth(width);
    yAxis->setBasePen(pen);
}

void QCatGrayQcustomplot::SetAxisBasePenColor_y(QColor color)
{
    QPen pen = yAxis->basePen();
    pen.setColor(color);
    yAxis->setBasePen(pen);
}

void QCatGrayQcustomplot::SetAxis2BasePen_y(QPen pen)
{
    yAxis2->setBasePen(pen);
}

void QCatGrayQcustomplot::SetAxis2BasePenWidth_y(int width)
{
    QPen pen = yAxis2->basePen();
    pen.setWidth(width);
    yAxis2->setBasePen(pen);
}

void QCatGrayQcustomplot::SetAxis2BasePenColor_y(QColor color)
{
    QPen pen = yAxis2->basePen();
    pen.setColor(color);
    yAxis2->setBasePen(pen);
}

void QCatGrayQcustomplot::SetAxisTickPen_x(QPen pen)
{
    xAxis->setTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisTickPenWidth_x(int width)
{
    QPen pen = xAxis->tickPen();
    pen.setWidth(width);
    xAxis->setTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisTickPenColor_x(QColor color)
{
    QPen pen = xAxis->tickPen();
    pen.setColor(color);
    xAxis->setTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2TickPen_x(QPen pen)
{
    xAxis2->setTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2TickPenWidth_x(int width)
{
    QPen pen = xAxis2->tickPen();
    pen.setWidth(width);
    xAxis2->setTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2TickPenColor_x(QColor color)
{
    QPen pen = xAxis2->tickPen();
    pen.setColor(color);
    xAxis2->setTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisTickPen_y(QPen pen)
{
    yAxis->setTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisTickPenWidth_y(int width)
{
    QPen pen = yAxis->tickPen();
    pen.setWidth(width);
    yAxis->setTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisTickPenColor_y(QColor color)
{
    QPen pen = yAxis->tickPen();
    pen.setColor(color);
    yAxis->setTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2TickPen_y(QPen pen)
{
    yAxis2->setTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2TickPenWidth_y(int width)
{
    QPen pen = yAxis2->tickPen();
    pen.setWidth(width);
    yAxis2->setTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2TickPenColor_y(QColor color)
{
    QPen pen = yAxis2->tickPen();
    pen.setColor(color);
    yAxis2->setTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisSubTickPen_x(QPen pen)
{
    xAxis->setSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisSubTickPenWidth_x(int width)
{
    QPen pen = xAxis->subTickPen();
    pen.setWidth(width);
    xAxis->setSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisSubTickPenColor_x(QColor color)
{
    QPen pen = xAxis->subTickPen();
    pen.setColor(color);
    xAxis->setSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SubTickPen_x(QPen pen)
{
    xAxis2->setSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SubTickPenWidth_x(int width)
{
    QPen pen = xAxis2->subTickPen();
    pen.setWidth(width);
    xAxis2->setSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SubTickPenColor_x(QColor color)
{
    QPen pen = xAxis2->subTickPen();
    pen.setColor(color);
    xAxis2->setSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisSubTickPen_y(QPen pen)
{
    yAxis->setSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisSubTickPenWidth_y(int width)
{
    QPen pen = yAxis->subTickPen();
    pen.setWidth(width);
    yAxis->setSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisSubTickPenColor_y(QColor color)
{
    QPen pen = yAxis->subTickPen();
    pen.setColor(color);
    yAxis->setSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SubTickPen_y(QPen pen)
{
    yAxis2->setSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SubTickPenWidth_y(int width)
{
    QPen pen = yAxis2->subTickPen();
    pen.setWidth(width);
    yAxis2->setSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SubTickPenColor_y(QColor color)
{
    QPen pen = yAxis2->subTickPen();
    pen.setColor(color);
    yAxis2->setSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisGridPen_x(QPen pen)
{
    xAxis->grid()->setPen(pen);
}

void QCatGrayQcustomplot::SetAxisGridPenWidth_x(int width)
{
    QPen pen = xAxis->grid()->pen();
    pen.setWidth(width);
    xAxis->grid()->setPen(pen);
}

void QCatGrayQcustomplot::SetAxisGridPenColor_x(QColor color)
{
    QPen pen = xAxis->grid()->pen();
    pen.setColor(color);
    xAxis->grid()->setPen(pen);
}

void QCatGrayQcustomplot::SetAxis2GridPen_x(QPen pen)
{
    xAxis2->grid()->setPen(pen);
}

void QCatGrayQcustomplot::SetAxis2GridPenWidth_x(int width)
{
    QPen pen = xAxis2->grid()->pen();
    pen.setWidth(width);
    xAxis2->grid()->setPen(pen);
}

void QCatGrayQcustomplot::SetAxis2GridPenColor_x(QColor color)
{
    QPen pen = xAxis2->grid()->pen();
    pen.setColor(color);
    xAxis2->grid()->setPen(pen);
}

void QCatGrayQcustomplot::SetAxisGridPen_y(QPen pen)
{
    yAxis->grid()->setPen(pen);
}

void QCatGrayQcustomplot::SetAxisGridPenWidth_y(int width)
{
    QPen pen = yAxis->grid()->pen();
    pen.setWidth(width);
    yAxis->grid()->setPen(pen);
}

void QCatGrayQcustomplot::SetAxisGridPenColor_y(QColor color)
{
    QPen pen = yAxis->grid()->pen();
    pen.setColor(color);
    yAxis->grid()->setPen(pen);
}

void QCatGrayQcustomplot::SetAxis2GridPen_y(QPen pen)
{
    yAxis2->grid()->setPen(pen);
}

void QCatGrayQcustomplot::SetAxis2GridPenWidth_y(int width)
{
    QPen pen = yAxis2->grid()->pen();
    pen.setWidth(width);
    yAxis2->grid()->setPen(pen);
}

void QCatGrayQcustomplot::SetAxis2GridPenColor_y(QColor color)
{
    QPen pen = yAxis2->grid()->pen();
    pen.setColor(color);
    yAxis2->grid()->setPen(pen);
}

void QCatGrayQcustomplot::SetAxisSubGridPen_x(QPen pen)
{
    xAxis->grid()->setSubGridPen(pen);
}

void QCatGrayQcustomplot::SetAxisSubGridPenWidth_x(int width)
{
    QPen pen = xAxis->grid()->subGridPen();
    pen.setWidth(width);
    xAxis->grid()->setSubGridPen(pen);
}

void QCatGrayQcustomplot::SetAxisSubGridPenColor_x(QColor color)
{
    QPen pen = xAxis->grid()->subGridPen();
    pen.setColor(color);
    xAxis->grid()->setSubGridPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SubGridPen_x(QPen pen)
{
    xAxis2->grid()->setSubGridPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SubGridPenWidth_x(int width)
{
    QPen pen = xAxis2->grid()->subGridPen();
    pen.setWidth(width);
    xAxis2->grid()->setSubGridPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SubGridPenColor_x(QColor color)
{
    QPen pen = xAxis2->grid()->subGridPen();
    pen.setColor(color);
    xAxis2->grid()->setSubGridPen(pen);
}

void QCatGrayQcustomplot::SetAxisSubGridPen_y(QPen pen)
{
    yAxis->grid()->setSubGridPen(pen);
}

void QCatGrayQcustomplot::SetAxisSubGridPenWidth_y(int width)
{
    QPen pen = yAxis->grid()->subGridPen();
    pen.setWidth(width);
    yAxis->grid()->setSubGridPen(pen);
}

void QCatGrayQcustomplot::SetAxisSubGridPenColor_y(QColor color)
{
    QPen pen = yAxis->grid()->subGridPen();
    pen.setColor(color);
    yAxis->grid()->setSubGridPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SubGridPen_y(QPen pen)
{
    yAxis2->grid()->setSubGridPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SubGridPenWidth_y(int width)
{
    QPen pen = yAxis2->grid()->subGridPen();
    pen.setWidth(width);
    yAxis2->grid()->setSubGridPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SubGridPenColor_y(QColor color)
{
    QPen pen = yAxis2->grid()->subGridPen();
    pen.setColor(color);
    yAxis2->grid()->setSubGridPen(pen);
}

void QCatGrayQcustomplot::SetAxisLabelColor_x(QColor color)
{
    xAxis->setLabelColor(color);
}

void QCatGrayQcustomplot::SetAxis2LabelColor_x(QColor color)
{
    xAxis2->setLabelColor(color);
}

void QCatGrayQcustomplot::SetAxisLabelColor_y(QColor color)
{
    yAxis->setLabelColor(color);
}

void QCatGrayQcustomplot::SetAxis2LabelColor_y(QColor color)
{
    yAxis2->setLabelColor(color);
}

void QCatGrayQcustomplot::SetAxisLabelFont_x(QFont font)
{
    xAxis->setLabelFont(font);
}

void QCatGrayQcustomplot::SetAxis2LabelFont_x(QFont font)
{
    xAxis2->setLabelFont(font);
}

void QCatGrayQcustomplot::SetAxisLabelFont_y(QFont font)
{
    yAxis->setLabelFont(font);
}

void QCatGrayQcustomplot::SetAxis2LabelFont_y(QFont font)
{
    yAxis2->setLabelFont(font);
}

void QCatGrayQcustomplot::SetAxisTickLabelColor_x(QColor color)
{
    xAxis->setTickLabelColor(color);
}

void QCatGrayQcustomplot::SetAxis2TickLabelColor_x(QColor color)
{
    xAxis2->setTickLabelColor(color);
}

void QCatGrayQcustomplot::SetAxisTickLabelColor_y(QColor color)
{
    yAxis->setTickLabelColor(color);
}

void QCatGrayQcustomplot::SetAxis2TickLabelColor_y(QColor color)
{
    yAxis2->setTickLabelColor(color);
}

void QCatGrayQcustomplot::SetAxisTickLabelFont_x(QFont font)
{
    xAxis->setTickLabelFont(font);
}

void QCatGrayQcustomplot::SetAxis2TickLabelFont_x(QFont font)
{
    xAxis2->setTickLabelFont(font);
}

void QCatGrayQcustomplot::SetAxisTickLabelFont_y(QFont font)
{
    yAxis->setTickLabelFont(font);
}

void QCatGrayQcustomplot::SetAxis2TickLabelFont_y(QFont font)
{
    yAxis2->setTickLabelFont(font);
}

void QCatGrayQcustomplot::SetGraphSelectionDecoratorWidth(int width)
{
    m_qSelectionDecorator.setWidth(width);
}

void QCatGrayQcustomplot::SetGraphSelectionDecoratorColor(QColor color)
{
    m_qSelectionDecorator.setColor(color);
}

void QCatGrayQcustomplot::SetLegendSelectIconBorderWidth(int width)
{
    QPen pen = legend->selectedIconBorderPen();
    pen.setWidth(width);
    legend->setSelectedIconBorderPen(pen);
}

void QCatGrayQcustomplot::SetLegendSelectIconBordeColor(QColor color)
{
    QPen pen = legend->selectedIconBorderPen();
    pen.setColor(color);
    legend->setSelectedIconBorderPen(pen);
}

void QCatGrayQcustomplot::SetAxisSelectedBasePenWidth_x(int width)
{
    QPen pen = xAxis->selectedBasePen();
    pen.setWidth(width);
    xAxis->setSelectedBasePen(pen);
}

void QCatGrayQcustomplot::SetAxisSelectedBasePenColor_x(QColor color)
{
    QPen pen = xAxis->selectedBasePen();
    pen.setColor(color);
    xAxis->setSelectedBasePen(pen);
}

void QCatGrayQcustomplot::SetAxis2SelectedBasePenWidth_x(int width)
{
    QPen pen = xAxis2->selectedBasePen();
    pen.setWidth(width);
    xAxis2->setSelectedBasePen(pen);
}

void QCatGrayQcustomplot::SetAxis2SelectedBasePenColor_x(QColor color)
{
    QPen pen = xAxis2->selectedBasePen();
    pen.setColor(color);
    xAxis2->setSelectedBasePen(pen);
}

void QCatGrayQcustomplot::SetAxisSelectedBasePenWidth_y(int width)
{
    QPen pen = yAxis->selectedBasePen();
    pen.setWidth(width);
    yAxis->setSelectedBasePen(pen);
}

void QCatGrayQcustomplot::SetAxisSelectedBasePenColor_y(QColor color)
{
    QPen pen = yAxis->selectedBasePen();
    pen.setColor(color);
    yAxis->setSelectedBasePen(pen);
}

void QCatGrayQcustomplot::SetAxis2SelectedBasePenWidth_y(int width)
{
    QPen pen = yAxis2->selectedBasePen();
    pen.setWidth(width);
    yAxis2->setSelectedBasePen(pen);
}

void QCatGrayQcustomplot::SetAxis2SelectedBasePenColor_y(QColor color)
{
    QPen pen = yAxis2->selectedBasePen();
    pen.setColor(color);
    yAxis2->setSelectedBasePen(pen);
}

void QCatGrayQcustomplot::SetAxisSelectedTickPenWidth_x(int width)
{
    QPen pen = xAxis->selectedTickPen();
    pen.setWidth(width);
    xAxis->setSelectedTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisSelectedTickPenColor_x(QColor color)
{
    QPen pen = xAxis->selectedTickPen();
    pen.setColor(color);
    xAxis->setSelectedTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SelectedTickPenWidth_x(int width)
{
    QPen pen = xAxis2->selectedTickPen();
    pen.setWidth(width);
    xAxis2->setSelectedTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SelectedTickPenColor_x(QColor color)
{
    QPen pen = xAxis2->selectedTickPen();
    pen.setColor(color);
    xAxis2->setSelectedTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisSelectedTickPenWidth_y(int width)
{
    QPen pen = yAxis->selectedTickPen();
    pen.setWidth(width);
    yAxis->setSelectedTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisSelectedTickPenColor_y(QColor color)
{
    QPen pen = yAxis->selectedTickPen();
    pen.setColor(color);
    yAxis->setSelectedTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SelectedTickPenWidth_y(int width)
{
    QPen pen = yAxis2->selectedTickPen();
    pen.setWidth(width);
    yAxis2->setSelectedTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SelectedTickPenColor_y(QColor color)
{
    QPen pen = yAxis2->selectedTickPen();
    pen.setColor(color);
    yAxis2->setSelectedTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisSelectedSubTickPenWidth_x(int width)
{
    QPen pen = xAxis->selectedSubTickPen();
    pen.setWidth(width);
    xAxis->setSelectedSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisSelectedSubTickPenColor_x(QColor color)
{
    QPen pen = xAxis->selectedSubTickPen();
    pen.setColor(color);
    xAxis->setSelectedSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SelectedSubTickPenWidth_x(int width)
{
    QPen pen = xAxis2->selectedSubTickPen();
    pen.setWidth(width);
    xAxis2->setSelectedSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SelectedSubTickPenColor_x(QColor color)
{
    QPen pen = xAxis2->selectedSubTickPen();
    pen.setColor(color);
    xAxis2->setSelectedSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisSelectedSubTickPenWidth_y(int width)
{
    QPen pen = yAxis->selectedSubTickPen();
    pen.setWidth(width);
    yAxis->setSelectedSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisSelectedSubTickPenColor_y(QColor color)
{
    QPen pen = yAxis->selectedSubTickPen();
    pen.setColor(color);
    yAxis->setSelectedSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SelectedSubTickPenWidth_y(int width)
{
    QPen pen = yAxis2->selectedSubTickPen();
    pen.setWidth(width);
    yAxis2->setSelectedSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxis2SelectedSubTickPenColor_y(QColor color)
{
    QPen pen = yAxis2->selectedSubTickPen();
    pen.setColor(color);
    yAxis2->setSelectedSubTickPen(pen);
}

void QCatGrayQcustomplot::SetAxisSelectedLabelColor_x(QColor color)
{
    xAxis->setSelectedLabelColor(color);
}

void QCatGrayQcustomplot::SetAxis2SelectedLabelColor_x(QColor color)
{
    xAxis2->setSelectedLabelColor(color);
}

void QCatGrayQcustomplot::SetAxisSelectedLabelColor_y(QColor color)
{
    yAxis->setSelectedLabelColor(color);
}

void QCatGrayQcustomplot::SetAxis2SelectedLabelColor_y(QColor color)
{
    yAxis2->setSelectedLabelColor(color);
}

void QCatGrayQcustomplot::SetAxisSelectedLabelFont_x(QFont font)
{
    xAxis->setSelectedLabelFont(font);
}

void QCatGrayQcustomplot::SetAxis2SelectedLabelFont_x(QFont font)
{
    xAxis2->setSelectedLabelFont(font);
}

void QCatGrayQcustomplot::SetAxisSelectedLabelFont_y(QFont font)
{
    yAxis->setSelectedLabelFont(font);
}

void QCatGrayQcustomplot::SetAxis2SelectedLabelFont_y(QFont font)
{
    yAxis2->setSelectedLabelFont(font);
}

void QCatGrayQcustomplot::SetAxisSelectedTickLabelColor_x(QColor color)
{
    xAxis->setSelectedTickLabelColor(color);
}

void QCatGrayQcustomplot::SetAxis2SelectedTickLabelColor_x(QColor color)
{
    xAxis2->setSelectedTickLabelColor(color);
}

void QCatGrayQcustomplot::SetAxisSelectedTickLabelColor_y(QColor color)
{
    yAxis->setSelectedTickLabelColor(color);
}

void QCatGrayQcustomplot::SetAxis2SelectedTickLabelColor_y(QColor color)
{
    yAxis2->setSelectedTickLabelColor(color);
}

void QCatGrayQcustomplot::SetAxisSelectedTickLabelFont_x(QFont font)
{
    xAxis->setSelectedTickLabelFont(font);
}

void QCatGrayQcustomplot::SetAxis2SelectedTickLabelFont_x(QFont font)
{
    xAxis2->setSelectedTickLabelFont(font);
}

void QCatGrayQcustomplot::SetAxisSelectedTickLabelFont_y(QFont font)
{
    yAxis->setSelectedTickLabelFont(font);
}

void QCatGrayQcustomplot::SetAxis2SelectedTickLabelFont_y(QFont font)
{
    yAxis2->setSelectedTickLabelFont(font);
}
