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
