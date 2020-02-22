#include <stdio.h>
#include "View.h"
#include "Board.h"

View::View(Board &board, bool silent_) {
	b = &board;
	cur_player = 0;
	silent = silent_;
}

void View::showBoard() const {
	for (int i = 0; i < b->get_size(); i++) {
		for (int j = 0; j < b->get_size(); j++) {
			printf("%c", b->get_cell(i, j));
		}
		printf("\n");
	}
}

void View::doGameCycle() {
	int x = -1, y = -1;
	char cur_pl = 'O';
	while (b->isWin(x, y) == GO_NEXT) {
		if (!silent) {
			showBoard();
		}
		printf("%c move: ", cur_pl);
		scanf("%d %d", &x, &y);
		if (x == -1 && y == -1) {
			return;
		}
		while (!b->move(x, y, cur_player)) {
			printf("Bad move!\n");
			printf("%c move: ", cur_pl);
			scanf("%d%d", &x, &y);
			if (x == -1 && y == -1) {
				return;
			}
		}
		if (!silent) {
			printf("\n");
		}
		cur_player ^= 1;
		if (cur_player) {
			cur_pl = 'X';
		} else {
			cur_pl = 'O';
		}
	}
	cur_player ^= 1;
	if (cur_player) {
		cur_pl = 'X';
	} else {
		cur_pl = 'O';
	}
	showBoard();
	if (b->isWin(x, y) == DRAW) {
		printf("Draw.\n");
		return;
	}
	printf("%c wins!\n", cur_pl);
	return;
}
