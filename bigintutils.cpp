#include "bigintutils.h"

#include <string>
#include <algorithm>

namespace StringDecMath {
    size_t chToInt(char ch) {
        return ch - '0';
    }

    char digitToChar(size_t digit) {
        return '0' + static_cast<char>(digit);
    }

    const std::string add(const std::string &left, const std::string &right) {
        std::string result;

        size_t index = 0;
        size_t remainder = 0;

        while (index < left.size() || index < right.size() || remainder) {
            size_t sum = remainder;

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

    const std::string powerOfTwo(size_t power);
}
