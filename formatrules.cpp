#include "formatrules.h"

const std::array<FormatRules::Style, 5> FormatRules::styles{
    FormatRules::Style::Plain,
    FormatRules::Style::Space,
    FormatRules::Style::Prefix,
    FormatRules::Style::Programmer,
    FormatRules::Style::Cpp,
};

const QString FormatRules::styleName(Style style)
{
    switch (style) {
    case FormatRules::Style::Plain:
        return QStringLiteral("Plain");
    case FormatRules::Style::Space:
        return QStringLiteral("Space");
    case FormatRules::Style::Prefix:
        return QStringLiteral("Prefix");
    case FormatRules::Style::Programmer:
        return QStringLiteral("Programmer");
    case FormatRules::Style::Cpp:
        return QStringLiteral("Cpp");
    }
}

const QString FormatRules::prefix(Style s, BigInt::Digits d)
{
    bool hasStandardPrefix =
               s == Style::Prefix
            || s == Style::Programmer
            || s == Style::Cpp;

    if (hasStandardPrefix && d == BigInt::Digits::Bin) return "0b";
    if (hasStandardPrefix && d == BigInt::Digits::Hex) return "0x";

    return QStringLiteral("");
}

const QString FormatRules::separator(Style s)
{
    if (s == Style::Space) return QStringLiteral(" ");
    if (s == Style::Programmer) return QStringLiteral("_");
    if (s == Style::Cpp) return QStringLiteral("'");

    return QStringLiteral("");
}

const size_t FormatRules::groupLength(Style s, BigInt::Digits d)
{
    bool hasSeparator =
               s == Style::Space
            || s == Style::Prefix
            || s == Style::Programmer
            || s == Style::Cpp;

    if (hasSeparator && d == BigInt::Digits::Bin) return 4;
    if (hasSeparator && d == BigInt::Digits::Dec) return 3;
    if (hasSeparator && d == BigInt::Digits::Hex) return 4;

    return 0;
}

const QRegularExpression FormatRules::regex(Style s, BigInt::Digits d)
{
    const auto separatorRegex = separator(s).isEmpty() ?
                QStringLiteral("") :
                QString("%1?").arg(separator(s));

   const auto regexString = QString("(%1([%3]+%2)*)?|%1%4")
                           .arg(prefix(s, d),
                                separatorRegex,
                                charsetRegex(d),
                                QStringLiteral("0"));

   return QRegularExpression(regexString);
}

const QString FormatRules::charsetRegex(BigInt::Digits d)
{
    if (d == BigInt::Digits::Bin) return "0-1";
    if (d == BigInt::Digits::Dec) return "0-9";
    if (d == BigInt::Digits::Hex) return "0-9a-fA-F";
    return "\\d";
}
