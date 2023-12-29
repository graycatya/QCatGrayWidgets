#include "QCatGrayCatDoubleValidator.h"
#include <QDebug>


QCatGrayCatDoubleValidator::QCatGrayCatDoubleValidator(QObject *parent)
    :QDoubleValidator(parent)
{

}

QCatGrayCatDoubleValidator::~QCatGrayCatDoubleValidator()
{

}

QValidator::State QCatGrayCatDoubleValidator::validate(QString &input, int &pos) const
{
    Q_UNUSED(pos)
    if (input.isEmpty())
    {
        return QValidator::Intermediate;
    }
    if(bottom()<0 && input=="-")
        return QValidator::Intermediate;

    bool cOK = false;
    double val = input.toDouble(&cOK);

    if (!cOK)
    {
        return QValidator::Invalid;
    }

    int dotPos = input.indexOf(".");
    if (dotPos > 0)
    {
        if (input.right(input.length() - dotPos-1).length() > decimals())
        {
            return QValidator::Invalid;
        }
    }
    if (val<= top() && val >= bottom())
    {
        return QValidator::Acceptable;
    }
    else if(val>top())
    {
        return QValidator::Invalid;
    }
    else if(val<bottom())
    {
        return QValidator::Invalid;
    }
    return QValidator::Invalid;
}

void QCatGrayCatDoubleValidator::fixup(QString &input) const
{
    if(input.toDouble()<bottom())
    {
        QString *str=&input;
        *str=QString::number(bottom());
    }
}
