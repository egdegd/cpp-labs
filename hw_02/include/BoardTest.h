#ifndef HW_02_BOARDTEST_H
#define HW_02_BOARDTEST_H

#include "Test.h"

class BoardTest: public Test {
public:
	void testMove1();
	void testMove2();
	void testMove3();
	void testIsWin1();
	void testIsWin2();
	void testIsWin3();
	void testIsWin4();
	void testIsWin5();
	void testIsWin6();
	void testIsWin7();
	void testGet_size1();
	void testGet_size2();
	void testGet_size3();
	void testGet_cell1();
	void testGet_cell2();
	void testGet_cell3();
	void runAllTests();
};


#endif
