#pragma once

#include <QIntValidator>

class QCatGrayIntValidator : public QIntValidator
{
    Q_OBJECT
public:
    explicit QCatGrayIntValidator(QObject *parent = nullptr);
    ~QCatGrayIntValidator();

public:
    virtual QValidator::State validate(QString &input, int &pos) const override;
    virtual void fixup(QString &input) const override;
};


