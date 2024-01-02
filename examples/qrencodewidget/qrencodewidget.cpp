#include "qrencodewidget.h"
#include "./ui_qrencodewidget.h"
#include "QCatGrayQrenCode.h"

qrencodewidget::qrencodewidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::qrencodewidget)
{
    ui->setupUi(this);
    InitConnect();
}

qrencodewidget::~qrencodewidget()
{
    delete ui;
}

void qrencodewidget::InitConnect()
{
    connect(ui->lineEdit, &QLineEdit::textEdited, this, [=](QString){
        UpdateQrenCode();
    });
}

void qrencodewidget::UpdateQrenCode()
{
    QPixmap qrPixmap;
    int width = ui->QrenCodeLabel->width();
    int height = ui->QrenCodeLabel->height();
    QRCODE qrproperty;
    qrproperty.text = ui->lineEdit->text();
    qrproperty.size = QSize(width, height);
    qrproperty.qrpercent = 0;
    qrproperty.backgroundColor = "#FFFFFF";
    qrproperty.qrencodeColor = "#000000";
    GernerateQRCode(qrproperty, qrPixmap);

    ui->QrenCodeLabel->setPixmap(qrPixmap);
}

void qrencodewidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    UpdateQrenCode();
}

void qrencodewidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    UpdateQrenCode();
}

