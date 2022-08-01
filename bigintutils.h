#pragma once

#include <string>
#include <vector>

namespace BigInt {

enum class Digits {
    Bin,
    Dec,
    Hex,
};

const std::vector<bool> toBoolVector(const std::string &num, Digits d);
const std::string fromBoolVector(const std::vector<bool> &num, Digits d);

}
