#include "bigintutils.h"

#include <algorithm>

#include "error.h"

namespace {

    using namespace BigInt;

    bool validateDigit(char ch, Digits d) {
        switch (d) {
        case Digits::Bin:
            return ch == '0' || ch == '1';
        case Digits::Dec:
            return ch >= '0' && ch <= '9';
        case Digits::Hex:
            return (ch >= '0' && ch <= '9') ||
                    (std::toupper(ch) >= 'A' && std::toupper(ch) <= 'F');
        }

        return false;
    }

    uint64_t maxDigitValue(BigInt::Digits d) {
        switch (d) {
        case BigInt::Digits::Bin:
            return 1;
        case BigInt::Digits::Dec:
            return 9;
        case BigInt::Digits::Hex:
            return 15;
        }

        return false;
    }

    uint64_t chToInt(char ch, Digits d) {
        if (!validateDigit(ch, d))
            throw Error{ "chToInt: not digit passed." };

        ch = std::toupper(ch);

        if ((ch >= 'A' && ch <= 'F'))
            return 10 + ch - 'A';

        return ch - '0';
    }

    char digitToChar(uint64_t digit, Digits d) {
        if (digit > maxDigitValue(d) || digit < 0)
            throw Error{ "digitToChar: not digit passed." };

        if (digit > 9)
            return 'A' + digit - 10;

        return '0' + static_cast<char>(digit);
    }

    const std::string add(const std::string &left, const std::string &right,
                          Digits d) {
        if (left.empty() || right.empty())
            throw Error{ "add: empty string passed." };

        std::string result;

        uint64_t index = 0;
        uint64_t remainder = 0;

        while (index < left.size() || index < right.size() || remainder) {
            uint64_t sum = remainder;

            if (index < left.size())
                sum += chToInt(left[left.size() - 1 - index], d);

            if (index < right.size())
                sum += chToInt(right[right.size() - 1 - index], d);

            remainder = sum / (maxDigitValue(d) + 1);
            sum %= (maxDigitValue(d) + 1);

            result.push_back(digitToChar(sum, d));

            ++index;
        }

        std::reverse(result.begin(), result.end());

        return result;
    }

    const std::string twoToThePowerOf(uint64_t power, Digits d) {
        if (power < 0)
            throw Error{ "twoToThePowerOf: negative power." };

        std::string result = "1";

        for (uint64_t i = 0; i < power; ++i)
            result = add(result, result, d);

        return result;
    }

    uint64_t modTwo(const std::string &num, Digits d) {
        if (num.empty())
            throw Error{ "modTwo: empty string passed." };

        return chToInt(num.back(), d) % 2;
    }

    const std::string divByUint(const std::string &num, uint64_t divisor,
                                Digits d) {
        if (divisor == 0)
            throw Error{ "divByUint: zero division." };

        std::string result;

        uint64_t index = 0;
        uint64_t remainder = 0;

        while (index < num.size() || remainder >= divisor) {
            remainder *= maxDigitValue(d) + 1;

            if (index < num.size())
                remainder += chToInt(num[index], d);

            const uint64_t divisionResult = remainder / divisor;

            if (divisionResult || !result.empty())
                result.push_back(digitToChar(divisionResult, d));

            remainder %= divisor;

            ++index;
        }

        if (result.empty()) result.push_back('0');

        return result;
    }

}

namespace BigInt {
    const std::vector<bool> toBoolVector(const std::string &num, Digits d) {
        std::vector<bool> reversed;

        auto remainder = num;

        while (!remainder.empty() && remainder != "0") {
            reversed.push_back(modTwo(remainder, d));
            remainder = divByUint(remainder, 2, d);
        }

        return { std::find(reversed.rbegin(), reversed.rend(), true),
                    reversed.rend() };
    }

    const std::string fromBoolVector(const std::vector<bool> &num, Digits d) {
        std::string result = "0";

        for (size_t i = 0; i < num.size(); ++i) {
            if (num[i])
                result = add(result, twoToThePowerOf(num.size() - 1 - i, d), d);
        }

        return result;
    }

    const std::vector<bool> incremented(const std::vector<bool> &num) {
        std::vector<bool> reversed;

        size_t i = 0;
        bool takeOver = true;
        while (true) {
            const auto bit = num[num.size() - i - 1];

            if (i < num.size()) {
                reversed.push_back(takeOver ^ bit);
                takeOver &= bit;
            }
            else if (takeOver) {
                reversed.push_back(takeOver);
                takeOver = false;
            }

            ++i;

            if (!takeOver && !(i < num.size()))
                break;
        }

        return { reversed.rbegin(), reversed.rend() };
    }

    const std::vector<bool> decremented(const std::vector<bool> &num) {
        std::vector<bool> reversed;

        bool takeOver = true;
        for (auto bitIt = num.crbegin(); bitIt < num.crend(); ++bitIt) {
            reversed.push_back(takeOver ^ *bitIt);
            takeOver &= !*bitIt;
        }

        return { reversed.rbegin(), reversed.rend() };
    }
}
