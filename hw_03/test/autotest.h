#ifndef HW_03_AUTOTEST_H
#define HW_03_AUTOTEST_H

#include <stdlib.h>

class autotest {
protected:
    int failedNum;
    int totalNum;
public:
    autotest();
    void check(bool expr, const char *func, const char  *filename, size_t lineNum);
    void showFinalResult();
    virtual void runAllTests() = 0;
};

#endif
