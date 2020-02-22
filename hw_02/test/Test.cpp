#include "Test.h"
#include <stdio.h>

Test::Test() {
	failedNum = 0;
	totalNum = 0;
}

void Test::showFinalResult() {
	if (!failedNum) {
		printf("All test passed.\n");
		return;
	}
	printf("Failed %d of %d tests.\n", failedNum, totalNum);
}

void Test::check(bool expr, const char *func, const char  *filename, size_t lineNum) {
	totalNum++;
	if (!expr) {
		printf("test failed: %s in %s:%lu\n", func, filename, lineNum);
		failedNum++;
	}
}