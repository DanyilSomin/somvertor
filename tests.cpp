#include <iostream>

#include <functional>

#include "bigintutils.h"

bool simple();
bool zerosToBoolVector();
bool zerosFromBoolVector();
bool goodToBoolVectorTest();
bool goodFromBoolVectorTests();
bool badToBoolVectorTests();

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
    ok &= doTest(goodFromBoolVectorTests, "--- goodFromBoolVectorTests");
    ok &= doTest(badToBoolVectorTests, "--- badToBoolVectorTests");

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

bool goodFromBoolVectorTests() {
    bool ok = true;

    auto num = BigInt::fromBoolVector(std::vector<bool>{ 1, 1, 1, 0, 1 },
                                      BigInt::Digits::Bin);
    ok &= num == "11101";

    num = BigInt::fromBoolVector(std::vector<bool>{ 1, 1, 1, 0, 1 },
                                      BigInt::Digits::Dec);
    ok &= num == "29";

    num = BigInt::fromBoolVector(std::vector<bool>{ 1, 1, 1, 0, 1 },
                                      BigInt::Digits::Hex);
    ok &= num == "1D";

    return ok;
}

bool badToBoolVectorTests() {
    bool ok = true;

    try {
        const auto num = BigInt::toBoolVector("012", BigInt::Digits::Bin);
        ok = false;
    }
    catch (...) {
        ok &= true;
    }

    try {
        const auto num = BigInt::toBoolVector("12A", BigInt::Digits::Dec);
        ok = false;
    }
    catch (...) {
        ok &= true;
    }

    try {
        const auto num = BigInt::toBoolVector("0G", BigInt::Digits::Hex);
        ok = false;
    }
    catch (...) {
        ok &= true;
    }

    return ok;

    try {
        const auto num = BigInt::toBoolVector("-010", BigInt::Digits::Bin);
        ok = false;
    }
    catch (...) {
        ok &= true;
    }

    return ok;

    try {
        const auto num = BigInt::toBoolVector("-19", BigInt::Digits::Dec);
        ok = false;
    }
    catch (...) {
        ok &= true;
    }

    return ok;

    try {
        const auto num = BigInt::toBoolVector("-0A", BigInt::Digits::Hex);
        ok = false;
    }
    catch (...) {
        ok &= true;
    }

    return ok;

    try {
        const auto num = BigInt::toBoolVector("0000000", BigInt::Digits::Bin);
        ok = false;
    }
    catch (...) {
        ok &= true;
    }

    return ok;

    try {
        const auto num = BigInt::toBoolVector("99,5", BigInt::Digits::Dec);
        ok = false;
    }
    catch (...) {
        ok &= true;
    }

    return ok;

    try {
        const auto num = BigInt::toBoolVector("0Л", BigInt::Digits::Hex);
        ok = false;
    }
    catch (...) {
        ok &= true;
    }

    return ok;
}
