#pragma once

#include <QRegularExpression>

#include "bigintutils.h"

class FormatRules
{
public:
    enum class Style {
        Plain,
        Cpp,
        Space
    };

    static const QString prefix(Style s, BigInt::Digits d);
    static const QString separator(Style s);
    static const size_t groupPopulation(Style s, BigInt::Digits d);
    static const QRegularExpression regex(Style s, BigInt::Digits d);

private:
    static const QString charsetRegex(BigInt::Digits d);
    static const QString firstDigitRegex(BigInt::Digits d);
};
