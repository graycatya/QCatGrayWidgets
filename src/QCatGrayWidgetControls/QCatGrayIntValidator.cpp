#include "QCatGrayIntValidator.h"

QCatGrayIntValidator::QCatGrayIntValidator(QObject *parent)
    : QIntValidator(parent)
{

}

QCatGrayIntValidator::~QCatGrayIntValidator()
{

}

QValidator::State QCatGrayIntValidator::validate(QString &input, int &pos) const
{
    Q_UNUSED(pos)
    if (input.isEmpty())
    {
        return QValidator::Intermediate;
    }
    if(bottom()<0)
        return QValidator::Intermediate;

    bool cOK = false;
    double val = input.toDouble(&cOK);

    if (!cOK)
    {
        return QValidator::Invalid;
    }

    /*int dotPos = input.size();
    if (dotPos > 0)
    {
        if (input.right(input.length() - dotPos-1).length() > decimals())
        {
            return QValidator::Invalid;
        }
    }*/
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

void QCatGrayIntValidator::fixup(QString &input) const
{
    if(input.toInt()<bottom())
    {
        QString *str=&input;
        *str=QString::number(bottom());
    }
}
