#pragma once

#include <QDoubleValidator>

class QCatGrayCatDoubleValidator : public QDoubleValidator
{
    Q_OBJECT
public:
    explicit QCatGrayCatDoubleValidator(QObject *parent = nullptr);
    ~QCatGrayCatDoubleValidator();

public:

    virtual QValidator::State validate(QString &input, int &pos) const override;
    virtual void fixup(QString &input) const override;

};


