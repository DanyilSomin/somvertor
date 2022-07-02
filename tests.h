#pragma once

#include <string>

namespace StringDecMath {
    uint64_t chToInt(char ch);

    char digitToChar(uint64_t digit);

    const std::string add(const std::string &left, const std::string &right);

    const std::string twoToThePowerOf(uint64_t power);

    uint64_t modTwo(const std::string &num);

    const std::string divByUint(const std::string &num, uint64_t divisor);
}
