#include "tests.h"

#include <iostream>
#include <functional>

// ------------------------------------------------------------------------

bool testStringDecMathChToInt();
bool testStringDecMathDigitToChar();
bool testStringDecMathAdd();
bool testStringDecMathTwoToThePowerOf();
bool testStringDecMathModTwo();
bool testStringDecMathDivByUint();
bool testStringDecMathToBoolVector();
bool testStringDecMathFromBoolVector();

// ------------------------------------------------------------------------

void doTest(std::function<bool()> test, const char *name)
{
    bool ok = test();
    std::cout << name << " : " << (ok ? "PASSED" : "FAILED") << '\n';
}

int main() {
    doTest(testStringDecMathChToInt, "testStringDecMathChToInt");
    doTest(testStringDecMathDigitToChar, "testStringDecMathDigitToChar");
    doTest(testStringDecMathAdd, "testStringDecMathAdd");
    doTest(testStringDecMathTwoToThePowerOf, "testStringDecMathTwoToThePowerOf");
    doTest(testStringDecMathModTwo, "testStringDecMathModTwo");
    doTest(testStringDecMathDivByUint, "testStringDecMathDivByUint");
    doTest(testStringDecMathToBoolVector, "testStringDecMathToBoolVector");
    doTest(testStringDecMathFromBoolVector, "testStringDecMathFromBoolVector");

    return 0;
}

// ------------------------------------------------------------------------

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

// ------------------------------------------------------------------------

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

// ------------------------------------------------------------------------

bool testStringDecMathAdd() {
    if (StringDecMath::add("0", "0") != "0") return false;
    if (StringDecMath::add("1", "0") != "1") return false;
    if (StringDecMath::add("1", "1") != "2") return false;
    if (StringDecMath::add("9", "1") != "10") return false;
    if (StringDecMath::add("999999", "1") != "1000000") return false;
    if (StringDecMath::add("59327", "34755653") != "34814980") return false;

    return true;
}

// ------------------------------------------------------------------------

bool testStringDecMathTwoToThePowerOf() {
    if (StringDecMath::twoToThePowerOf(0) != "1") return false;
    if (StringDecMath::twoToThePowerOf(1) != "2") return false;
    if (StringDecMath::twoToThePowerOf(2) != "4") return false;
    if (StringDecMath::twoToThePowerOf(3) != "8") return false;
    if (StringDecMath::twoToThePowerOf(3) != "8") return false;
    if (StringDecMath::twoToThePowerOf(1024)
            != "1797693134862315907729305190789024733617976978942306572734"
            "3008115773267580550096313270847732240753602112011387987139335"
            "7658789768814416622492847430639474124377767893424865485276302"
            "2196012460941194530829520850057688381506823424628814739131105"
            "4082723716335051068458629823994724593847971630483535632962422"
            "4137216") return false;

    return true;
}

// ------------------------------------------------------------------------

bool testStringDecMathModTwo() {
    if (StringDecMath::modTwo("0") != 0) return false;
    if (StringDecMath::modTwo("1") != 1) return false;
    if (StringDecMath::modTwo("2") != 0) return false;
    if (StringDecMath::modTwo("3") != 1) return false;
    if (StringDecMath::modTwo("1001") != 1) return false;
    if (StringDecMath::modTwo("1000") != 0) return false;

    return true;
}

// ------------------------------------------------------------------------

bool testStringDecMathDivByUint() {
    if (StringDecMath::divByUint("100", 1) != "100") return false;
    if (StringDecMath::divByUint("100", 2) != "50") return false;
    if (StringDecMath::divByUint("101", 2) != "50") return false;
    if (StringDecMath::divByUint("1", 2) != "0") return false;
    if (StringDecMath::divByUint("0", 2) != "0") return false;
    if (StringDecMath::divByUint("4", 7) != "0") return false;
    if (StringDecMath::divByUint("37", 6) != "6") return false;

    return true;
}

// ------------------------------------------------------------------------

bool testStringDecMathToBoolVector() {
    if (StringDecMath::toBoolVector("0") != std::vector<bool>{ }) return false;
    if (StringDecMath::toBoolVector("1") != std::vector<bool>{ 1 }) return false;
    if (StringDecMath::toBoolVector("2") != std::vector<bool>{ 1, 0 }) return false;
    if (StringDecMath::toBoolVector("3") != std::vector<bool>{ 1, 1 }) return false;
    if (StringDecMath::toBoolVector("4") != std::vector<bool>{ 1, 0, 0 }) return false;
    if (StringDecMath::toBoolVector("8") != std::vector<bool>{ 1, 0, 0, 0 }) return false;
    if (StringDecMath::toBoolVector("29") != std::vector<bool>{ 1, 1, 1, 0, 1 }) return false;
    if (StringDecMath::toBoolVector("255") != std::vector<bool>{ 1, 1, 1, 1, 1, 1, 1, 1}) return false;

    return true;
}

// ------------------------------------------------------------------------

bool testStringDecMathFromBoolVector() {
    if (StringDecMath::fromBoolVector({ }) != "0") return false;
    if (StringDecMath::fromBoolVector({ 0 }) != "0") return false;
    if (StringDecMath::fromBoolVector({ 1 }) != "1") return false;
    if (StringDecMath::fromBoolVector({ 1, 0 }) != "2") return false;
    if (StringDecMath::fromBoolVector({ 1, 1 }) != "3") return false;
    if (StringDecMath::fromBoolVector({ 1, 1, 0 }) != "6") return false;
    if (StringDecMath::fromBoolVector({ 1, 1, 1 }) != "7") return false;
    if (StringDecMath::fromBoolVector({ 1, 1, 1, 1, 1, 1, 1, 1 }) != "255") return false;

    return true;
}

// ------------------------------------------------------------------------

