#include "bigintutils.h"

#include <string>
#include <algorithm>
#include <cassert>

namespace StringDecMath {
    uint64_t chToInt(char ch) {
        return ch - '0';
    }

    char digitToChar(uint64_t digit) {
        return '0' + static_cast<char>(digit);
    }

    const std::string add(const std::string &left, const std::string &right) {
        std::string result;

        uint64_t index = 0;
        uint64_t remainder = 0;

        while (index < left.size() || index < right.size() || remainder) {
            uint64_t sum = remainder;

            if (index < left.size())
                sum += chToInt(left[left.size() - 1 - index]);

            if (index < right.size())
                sum += chToInt(right[right.size() - 1 - index]);

            remainder = sum / 10;
            sum %= 10;

            result.push_back(digitToChar(sum));

            ++index;
        }

        std::reverse(result.begin(), result.end());

        return result;
    }

    const std::string twoToThePowerOf(uint64_t power) {
        std::string result = "1";

        for (uint64_t i = 0; i < power; ++i) {
            result = add(result, result);
        }

        return result;
    }

    uint64_t modTwo(const std::string &num) {
        return chToInt(num.front()) % 2;
    }

    const std::string divByUint(const std::string &num, uint64_t divisor) {
        assert(divisor != 0);

        std::string result;

        uint64_t index = 0;
        uint64_t remainder = 0;

        while (index < num.size() || remainder >= divisor) {
            remainder *= 10;

            if (index < num.size())
                remainder += chToInt(num[index]);

            const uint64_t divisionResult = remainder / divisor;

            if (divisionResult || !result.empty())
                result.push_back(digitToChar(divisionResult));

            remainder %= divisor;

            ++index;
        }

        if (result.empty()) result.push_back('0');

        return result;
    }
}
