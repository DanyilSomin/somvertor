#pragma once

#include <string>

namespace StringDecMath {
    size_t chToInt(char ch);

    char digitToChar(size_t digit);

    const std::string add(const std::string &left, const std::string &right);
}
