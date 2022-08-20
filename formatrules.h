#pragma once

#include <QRegularExpression>

#include "bigintutils.h"

class FormatRules
{
public:
    enum class Style {
        Plain,
        Space,
        Prefix,
        Programmer,
        Cpp,
    };

    static const std::array<Style, 5> styles;
    static const QString styleName(Style style);

    static const QString prefix(Style s, BigInt::Digits d);
    static const QString separator(Style s);
    static const size_t groupLength(Style s, BigInt::Digits d);
    static const QRegularExpression regex(Style s, BigInt::Digits d);

private:
    static const QString charsetRegex(BigInt::Digits d);
};

Q_DECLARE_METATYPE(FormatRules::Style)
