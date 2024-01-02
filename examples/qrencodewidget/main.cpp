#include "qrencodewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qrencodewidget w;
    w.show();
    return a.exec();
}
