#ifndef HW_02_VIEW_H
#define HW_02_VIEW_H
#include "Board.h"

class View {
public:
	explicit View(Board &board, bool silent_);
	void showBoard() const;
	void doGameCycle();
private:
	Board *b;
	int cur_player;
	bool silent;

};

#endif