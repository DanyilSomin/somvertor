#include "bigintspinbox.h"

#include <QLineEdit>
#include <QRegularExpression>

BigIntSpinBox::BigIntSpinBox(QWidget *parent)
    : QAbstractSpinBox{ parent }
{
    connect(lineEdit(), &QLineEdit::textEdited, this, [this](const QString &text) {
        const auto separator = FormatRules::separator(FormatRules::Style::Cpp);

        if (text.endsWith(separator)) {
            lineEdit()->setText(text.chopped(separator.size()));
        }
    });

    connect(lineEdit(), &QLineEdit::textEdited, this, [this]() {
        try {
            emit valueEdited(getBigInt());
        }
        catch (...) {

        }
    });
}

void BigIntSpinBox::init(FormatRules::Style s, BigInt::Digits d)
{
    _formatStyle = s;
    _digits = d;

    lineEdit()->setValidator(new QRegularExpressionValidator(
                                 FormatRules::regex(_formatStyle,
                                                    _digits),
                             this));

    lineEdit()->clear();
}

void BigIntSpinBox::setFormatStyle(FormatRules::Style s)
{
    const auto bigInt = getBigInt();

    _formatStyle = s;

    lineEdit()->setValidator(new QRegularExpressionValidator(
                                 FormatRules::regex(_formatStyle,
                                                    _digits),
                             this));

    setBigInt(bigInt);
}

std::vector<bool> BigIntSpinBox::getBigInt() const
{
    auto bigIntStr = lineEdit()->text();

    bigIntStr.remove(FormatRules::prefix(_formatStyle, _digits));
    bigIntStr.remove(FormatRules::separator(_formatStyle));

    return BigInt::toBoolVector(bigIntStr.toStdString(), _digits);
}

void BigIntSpinBox::setBigInt(const std::vector<bool> &bigInt) const
{
    lineEdit()->setText(applyStyle(QString::fromStdString(
                                       BigInt::fromBoolVector(bigInt, _digits))));
}

QString BigIntSpinBox::applyStyle(const QString &bigIntStr) const
{
    QString result = bigIntStr;

    result.push_front(FormatRules::prefix(_formatStyle, _digits));

    return result;
}
