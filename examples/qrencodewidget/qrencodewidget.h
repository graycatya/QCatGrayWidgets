#ifndef QRENCODEWIDGET_H
#define QRENCODEWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class qrencodewidget; }
QT_END_NAMESPACE

class qrencodewidget : public QWidget
{
    Q_OBJECT

public:
    qrencodewidget(QWidget *parent = nullptr);
    ~qrencodewidget();

private:
    void InitConnect();

    void UpdateQrenCode();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    Ui::qrencodewidget *ui;

};
#endif // QRENCODEWIDGET_H
