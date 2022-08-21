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

    StepEnabled stepEnabled() const override;
    void stepBy(int step) override;

signals:
    void valueEdited(const std::vector<bool> &bigInt);
    void incrementPressed();
    void decrementPressed();

private slots:
    void onEditingFinished();
    void onTextEdited(const QString &);

private:
    QString applyStyle(const QString &bigIntStr) const;

    BigInt::Digits _digits{ BigInt::Digits::Bin };
    FormatRules::Style _formatStyle{ FormatRules::Style::Plain };

    mutable StepEnabled _stepEnabled{ };
};
