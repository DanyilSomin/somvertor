#include <iostream>

#include "bigintutils.h"

bool simple();
bool zerosToBoolVector();
bool zerosFromBoolVector();
bool goodToBoolVectorTest();

bool doTest(std::function<bool()> test, const char *name) {
    bool ok = test();
    std::cout << name << " : " << (ok ? "PASSED" : "FAILED") << '\n';

    return ok;
}

bool allTests() {
    bool ok = true;

    ok &= doTest(simple, "--- simple");
    ok &= doTest(zerosToBoolVector, "--- zerosToBoolVector");
    ok &= doTest(zerosFromBoolVector, "--- zerosFromBoolVector");
    ok &= doTest(goodToBoolVectorTest, "--- goodToBoolVectorTest");

    return ok;
}

int main() {
    doTest(allTests, "------- allTests");
}

// ------------------------------------------------------------------------

bool simple() {
    bool ok = true;

    const auto vec = BigInt::toBoolVector("10", BigInt::Digits::Dec);
    ok &= (vec == std::vector<bool>{ 1, 0, 1, 0 });

    const auto num = BigInt::fromBoolVector(
                std::vector<bool>{ 1, 0, 1, 0 }, BigInt::Digits::Dec);
    ok &= (num == "10");

    return ok;
}

bool zerosToBoolVector() {
    bool ok = true;

    auto vec = BigInt::toBoolVector("0", BigInt::Digits::Bin);
    ok &= (vec == std::vector<bool>{ });

    vec = BigInt::toBoolVector("0", BigInt::Digits::Dec);
    ok &= (vec == std::vector<bool>{ });

    vec = BigInt::toBoolVector("0", BigInt::Digits::Hex);
    ok &= (vec == std::vector<bool>{ });

    vec = BigInt::toBoolVector("00", BigInt::Digits::Bin);
    ok &= (vec == std::vector<bool>{ });

    vec = BigInt::toBoolVector("00", BigInt::Digits::Dec);
    ok &= (vec == std::vector<bool>{ });

    vec = BigInt::toBoolVector("00", BigInt::Digits::Hex);
    ok &= (vec == std::vector<bool>{ });

    vec = BigInt::toBoolVector("000010", BigInt::Digits::Bin);
    ok &= (vec == std::vector<bool>{ 1, 0 });

    vec = BigInt::toBoolVector("000010", BigInt::Digits::Dec);
    ok &= (vec == std::vector<bool>{ 1, 0, 1, 0 });

    vec = BigInt::toBoolVector("000010", BigInt::Digits::Hex);
    ok &= (vec == std::vector<bool>{ 1, 0, 0, 0, 0 });

    return ok;
}

bool zerosFromBoolVector() {
    bool ok = true;

    auto num = BigInt::fromBoolVector(
                std::vector<bool>{ }, BigInt::Digits::Bin);
    ok &= (num == "0");

    num = BigInt::fromBoolVector(
                std::vector<bool>{ }, BigInt::Digits::Dec);
    ok &= (num == "0");

    num = BigInt::fromBoolVector(
                std::vector<bool>{ }, BigInt::Digits::Hex);
    ok &= (num == "0");

    num = BigInt::fromBoolVector(
                std::vector<bool>{ 0, 0, 1, 0 }, BigInt::Digits::Bin);
    ok &= (num == "10");

    num = BigInt::fromBoolVector(
                std::vector<bool>{ 0, 0, 1, 0 }, BigInt::Digits::Dec);
    ok &= (num == "2");

    num = BigInt::fromBoolVector(
                std::vector<bool>{ 0, 1, 1, 1, 1 }, BigInt::Digits::Hex);
    ok &= (num == "F");

    return ok;
}

bool goodToBoolVectorTest() {
    bool ok = true;

    auto vec = BigInt::toBoolVector("1010111101000101010101", BigInt::Digits::Bin);
    ok &= vec == std::vector<bool>{ 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0,
                                    0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 };

    vec = BigInt::toBoolVector("12341234234", BigInt::Digits::Dec);
    ok &= vec == std::vector<bool>{ 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
                                    0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0,
                                    1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0 };

    vec = BigInt::toBoolVector("e12cba34df5", BigInt::Digits::Hex);
    ok &= vec == std::vector<bool>{ 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1,
                                    0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0,
                                    1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1,
                                    1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 };

    return ok;
}
