#ifndef HW_02_BOARD_H
#define HW_02_BOARD_H

enum game_state_t {
	WIN = 0,
	DRAW = 1,
	GO_NEXT = 2
};

class Board {
public:
	explicit Board(size_t size_);
	~Board();
	bool move(int x, int y, int sign);
	bool canMove(int x, int y) const;
	game_state_t isWin(int x, int y) const;
	char get_cell(int x, int y) const;
	size_t get_size() const;
private:
	size_t size;
	char **board;
	int empty_cell;
};

#endif