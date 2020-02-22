#ifndef HW_02_TEST_H
#define HW_02_TEST_H
#include <stdlib.h>

class Test {
protected:
	int failedNum;
	int totalNum;
public:
	Test();
	void check(bool expr, const char *func, const char  *filename, size_t lineNum);
	void showFinalResult();
	virtual void runAllTests() =0;
};

#endif
