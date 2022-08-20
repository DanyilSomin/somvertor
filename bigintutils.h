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

const std::vector<bool> incremented(const std::vector<bool> &num);
const std::vector<bool> decremented(const std::vector<bool> &num);

}
