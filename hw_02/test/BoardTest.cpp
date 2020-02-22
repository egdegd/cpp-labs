#include "BoardTest.h"
#include "Board.h"

#define DO_CHECK(EXPR) check(EXPR, __FUNCTION__, __FILE__, __LINE__)


void BoardTest::testMove1() {
	Board b(10);
	b.move(0, 0, 1);
	DO_CHECK(!b.canMove(0, 0));
}

void BoardTest::testMove2() {
	Board b(10);
	b.move(0, 0, 1);
	DO_CHECK(b.canMove(1, 1));
}

void BoardTest::testMove3() {
	Board b(8);
	DO_CHECK(!b.canMove(8, 5));
}

void BoardTest::testIsWin1() {
	Board b(10);
	b.move(0, 0, 1);
	b.move(0, 1, 1);
	b.move(1, 0, 1);
	b.move(4, 5, 0);
	b.move(5, 5, 0);
	DO_CHECK(b.isWin(5,5) == GO_NEXT);
}

void BoardTest::testIsWin2() {
	Board b(10);
	b.move(0, 0, 0);
	b.move(0, 1, 1);
	b.move(1, 0, 0);
	b.move(1, 1, 1);
	b.move(2, 0, 0);
	b.move(9, 9, 1);
	b.move(3, 0, 0);
	b.move(5, 4, 1);
	b.move(4, 0, 0);
	DO_CHECK(b.isWin(4,0) == WIN);
}

void BoardTest::testIsWin3() {
	Board b(10);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (i % 2 == 0) {
				if (j % 4 == 0 || j % 4 == 1) {
					b.move(i, j, 0);
				} else {
					b.move(i, j, 1);
				}
			} else {
				if (j % 4 == 0 || j % 4 == 1) {
					b.move(i, j, 1);
				} else {
					b.move(i, j, 0);
				}
			}
		}
	}
	DO_CHECK(b.isWin(9,9) == DRAW);
}

void BoardTest::testIsWin4() {
	Board b(10);
	b.move(6, 7, 0);
	b.move(3, 4, 1);
	b.move(1, 0, 0);
	b.move(3, 5, 1);
	b.move(2, 0, 0);
	b.move(3, 6, 1);
	b.move(3, 0, 0);
	b.move(3, 7, 1);
	b.move(4, 0, 0);
	b.move(3, 8, 1);
	DO_CHECK(b.isWin(3, 8) == WIN);
}

void BoardTest::testIsWin5() {
	Board b(10);
	b.move(1, 2, 0);
	b.move(2, 3, 0);
	b.move(3, 4, 0);
	b.move(4, 5, 0);
	b.move(5, 6, 0);
	DO_CHECK(b.isWin(5, 6) == WIN);
}

void BoardTest::testIsWin6() {
	Board b(10);
	b.move(9, 9, 1);
	b.move(8, 8, 1);
	b.move(7, 7, 1);
	b.move(6, 6, 1);
	b.move(5, 5, 1);
	DO_CHECK(b.isWin(5, 5) == WIN);
}

void BoardTest::testIsWin7() {
	Board b(10);
	b.move(4, 7, 1);
	b.move(5, 6, 1);
	b.move(6, 5, 1);
	b.move(3, 8, 1);
	b.move(2, 9, 1);
	DO_CHECK(b.isWin(2, 9) == WIN);
}

void BoardTest::testGet_size1() {
	Board b(10);
	DO_CHECK(b.get_size() == 10);
}

void BoardTest::testGet_size2() {
	Board b(1);
	DO_CHECK(b.get_size() == 1);
}

void BoardTest::testGet_size3() {
	Board b(123);
	DO_CHECK(b.get_size() == 123);
}

void BoardTest::testGet_cell1() {
	Board b(10);
	b.move(0, 0, 1);
	DO_CHECK(b.get_cell(0, 0) == 'X');
}

void BoardTest::testGet_cell2() {
	Board b(10);
	b.move(0, 0, 1);
	b.move(5, 9, 0);
	DO_CHECK(b.get_cell(5, 9) == 'O');
}

void BoardTest::testGet_cell3() {
	Board b(10);
	DO_CHECK(b.get_cell(7, 1) == '.');
}

void BoardTest::runAllTests() {
	testMove1();
	testMove2();
	testMove3();
	testIsWin1();
	testIsWin2();
	testIsWin3();
	testIsWin4();
	testIsWin5();
	testIsWin6();
	testIsWin7();
	testGet_size1();
	testGet_size2();
	testGet_size3();
	testGet_cell1();
	testGet_cell2();
	testGet_cell3();
}