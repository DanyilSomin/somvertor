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

private:
    BigInt::Digits _digits = BigInt::Digits::Bin;
    FormatRules::Style _formatStyle = FormatRules::Style::Plain;
};
