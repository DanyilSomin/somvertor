#include "formatrules.h"

const std::array<FormatRules::Style, 3> FormatRules::styles{
    FormatRules::Style::Plain,
    FormatRules::Style::Cpp,
    FormatRules::Style::Space,
};

const QString FormatRules::styleName(Style style)
{
    switch (style) {
    case FormatRules::Style::Plain:
        return QStringLiteral("Plain");
    case FormatRules::Style::Cpp:
        return QStringLiteral("Cpp");
    case FormatRules::Style::Space:
        return QStringLiteral("Space");
    }
}

const QString FormatRules::prefix(Style s, BigInt::Digits d)
{
    if (s == Style::Cpp && d == BigInt::Digits::Bin) return "0b";
    if (s == Style::Cpp && d == BigInt::Digits::Hex) return "0x";

    return QStringLiteral("");
}

const QString FormatRules::separator(Style s)
{
    if (s == Style::Cpp) return QStringLiteral("'");
    if (s == Style::Space) return QStringLiteral(" ");

    return QStringLiteral("");
}

const size_t FormatRules::groupLength(Style s, BigInt::Digits d)
{
    if ((s == Style::Cpp || s == Style::Space) && d == BigInt::Digits::Bin) return 4;
    if ((s == Style::Cpp || s == Style::Space) && d == BigInt::Digits::Dec) return 3;
    if ((s == Style::Cpp || s == Style::Space) && d == BigInt::Digits::Hex) return 4;

    return 0;
}

const QRegularExpression FormatRules::regex(Style s, BigInt::Digits d)
{
    const auto separatorRegex = separator(s).isEmpty() ?
                QStringLiteral("") :
                QString("%1?").arg(separator(s));

   const auto regexString = QString("(%1(%2[%3]+)*)?|%1%4")
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
