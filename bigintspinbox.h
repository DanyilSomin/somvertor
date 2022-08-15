#pragma once

#include <QAbstractSpinBox>

#include "bigintutils.h"
#include "formatrules.h"

class BigIntSpinBox : public QAbstractSpinBox
{
    Q_OBJECT
public:
    explicit BigIntSpinBox(QWidget *parent = nullptr);

    void init(FormatRules::Style s, BigInt::Digits d);

    void setFormatStyle(FormatRules::Style s);

    std::vector<bool> getBigInt() const;
    void setBigInt(const std::vector<bool> &bigInt) const;

signals:
    void valueEdited(const std::vector<bool> &bigInt);

private:
    QString applyStyle(const QString &bigIntStr) const;

    BigInt::Digits _digits = BigInt::Digits::Bin;
    FormatRules::Style _formatStyle = FormatRules::Style::Plain;
};
