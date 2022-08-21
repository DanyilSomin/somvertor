#include "bigintspinbox.h"

#include <QLineEdit>
#include <QTextStream>
#include <QRegularExpression>

BigIntSpinBox::BigIntSpinBox(QWidget *parent)
    : QAbstractSpinBox{ parent }
{
    connect(this, &QAbstractSpinBox::editingFinished,
            this, &BigIntSpinBox::onEditingFinished);

    connect(lineEdit(), &QLineEdit::textEdited,
            this, &BigIntSpinBox::onTextEdited);

    _stepEnabled.setFlag(StepUpEnabled, true);
}

void BigIntSpinBox::init(FormatRules::Style s, BigInt::Digits d)
{
    _formatStyle = s;
    _digits = d;

    lineEdit()->setValidator(new QRegularExpressionValidator(
                                 FormatRules::regex(_formatStyle,
                                                    _digits),
                             this));

    setBigInt({});
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
    const auto bigIntStr = BigInt::fromBoolVector(bigInt, _digits);

    if (bigIntStr == "0")
        _stepEnabled.setFlag(StepDownEnabled, false);
    else
        _stepEnabled.setFlag(StepDownEnabled, true);

    lineEdit()->setText(applyStyle(
                            QString::fromStdString(bigIntStr)));
}

QAbstractSpinBox::StepEnabled BigIntSpinBox::stepEnabled() const
{
    return _stepEnabled;
}

void BigIntSpinBox::stepBy(int step)
{
    if (step == 1) emit incrementPressed();
    if (step == -1) emit decrementPressed();
}

void BigIntSpinBox::onEditingFinished()
{
    const auto text = lineEdit()->text();
    const auto separator = FormatRules::separator(_formatStyle);

    if (text.endsWith(separator)) {
        lineEdit()->setText(text.chopped(separator.size()));
    }

    try {
        setBigInt(getBigInt());
    }
    catch (...) { }
}

void BigIntSpinBox::onTextEdited(const QString &text)
{
    try {
        emit valueEdited(getBigInt());

        const auto prefix = FormatRules::prefix(_formatStyle, _digits);

        const bool firstDigitWasZero = (text.size() == prefix.size() + 2)
                                   && text.startsWith(prefix + "0");
        const bool cursorAtTheEnd = lineEdit()->cursorPosition() == text.size();

        if (firstDigitWasZero && cursorAtTheEnd) {
            const auto withoutLeadingZero = prefix + text.back();
            lineEdit()->setText(withoutLeadingZero);
        }
    }
    catch (...) { }
}

QString BigIntSpinBox::applyStyle(const QString &bigIntStr) const
{
    QString result;
    result.append(FormatRules::prefix(_formatStyle, _digits));

    const auto numLen = bigIntStr.length();
    const auto groupLen = FormatRules::groupLength(_formatStyle, _digits);
    const auto separator = FormatRules::separator(_formatStyle);
    for (int i = 0; i < numLen; ++i) {
        if (groupLen && i && !((numLen - i) % groupLen))
            result.append(separator);

        result.append(bigIntStr[i]);
    }

    return result;
}
