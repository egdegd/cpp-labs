#include <iostream>
#include "autotest.h"

autotest::autotest() {
    failedNum = 0;
    totalNum = 0;
}

void autotest::check(bool expr, const char *func, const char *filename, size_t lineNum) {
    totalNum++;
    if (!expr) {
        std::cout << "test failed: " << func << " in " << filename << ":" << lineNum << std::endl;
        failedNum++;
    }
}

void autotest::showFinalResult() {
    if (!failedNum) {
        std::cout<< "All test passed." << std::endl;
        return;
    }
    std::cout << "Failed " << failedNum << " of " << totalNum << " tests." << std::endl;
}
