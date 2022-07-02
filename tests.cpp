#include "tests.h"

#include <iostream>

bool testStringDecMathChToInt();
bool testStringDecMathDigitToChar();
bool testStringDecMathAdd();

int main() {
    bool ok;

    ok = testStringDecMathChToInt();
    std::cout << "testStringDecMathChToInt() : "
              << (ok ? "PASSED" : "FAILED") << '\n';

    ok = testStringDecMathDigitToChar();
    std::cout << "testStringDecMathDigitToChar() : "
              << (ok ? "PASSED" : "FAILED") << '\n';

    ok = testStringDecMathAdd();
    std::cout << "testStringDecMathAdd() : "
              << (ok ? "PASSED" : "FAILED") << '\n';

    return 0;
}

bool testStringDecMathChToInt() {
    if (StringDecMath::chToInt('0') != 0) return false;
    if (StringDecMath::chToInt('0') != 0) return false;
    if (StringDecMath::chToInt('1') != 1) return false;
    if (StringDecMath::chToInt('2') != 2) return false;
    if (StringDecMath::chToInt('3') != 3) return false;
    if (StringDecMath::chToInt('4') != 4) return false;
    if (StringDecMath::chToInt('5') != 5) return false;
    if (StringDecMath::chToInt('6') != 6) return false;
    if (StringDecMath::chToInt('7') != 7) return false;
    if (StringDecMath::chToInt('8') != 8) return false;
    if (StringDecMath::chToInt('9') != 9) return false;

    return true;
}

bool testStringDecMathDigitToChar() {
    if (StringDecMath::digitToChar(0) != '0') return false;
    if (StringDecMath::digitToChar(1) != '1') return false;
    if (StringDecMath::digitToChar(2) != '2') return false;
    if (StringDecMath::digitToChar(3) != '3') return false;
    if (StringDecMath::digitToChar(4) != '4') return false;
    if (StringDecMath::digitToChar(5) != '5') return false;
    if (StringDecMath::digitToChar(6) != '6') return false;
    if (StringDecMath::digitToChar(7) != '7') return false;
    if (StringDecMath::digitToChar(8) != '8') return false;
    if (StringDecMath::digitToChar(9) != '9') return false;

    return true;
}

bool testStringDecMathAdd() {
    if (StringDecMath::add("0", "0") != "0") return false;
    if (StringDecMath::add("1", "0") != "1") return false;
    if (StringDecMath::add("1", "1") != "2") return false;
    if (StringDecMath::add("9", "1") != "10") return false;
    if (StringDecMath::add("999999", "1") != "1000000") return false;
    if (StringDecMath::add("59327", "34755653") != "34814980") return false;

    return true;
}
