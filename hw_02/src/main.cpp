#include <iostream>
#include <string.h>
#include "Board.h"
#include "View.h"

int main(int argc, char **argv) {
	Board b(10);
	bool silent = false;
	if (argc > 1) {
		if (!strcmp(argv[1], "silent")) {
			silent = true;
		}
	}
	View v(b, silent);
	v.doGameCycle();
	return 0;
}