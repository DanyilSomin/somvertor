#include "tests.h"

#include <iostream>

#include "dectests.h"

bool doTest(std::function<bool()> test, const char *name)
{
    bool ok = test();
    std::cout << name << " : " << (ok ? "PASSED" : "FAILED") << '\n';

    return ok;
}

bool allTests() {
    bool ok = true;

    ok &= doTest(decTests, "--- decTests");

    return ok;
}

int main() {
    doTest(allTests, "------- allTests");
}
