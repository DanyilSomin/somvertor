#include <iostream>

#include "bigintutils.h"

bool simple();

bool doTest(std::function<bool()> test, const char *name) {
    bool ok = test();
    std::cout << name << " : " << (ok ? "PASSED" : "FAILED") << '\n';

    return ok;
}

bool allTests() {
    bool ok = true;

    ok &= doTest(simple, "--- simple");

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
