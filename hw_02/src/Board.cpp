#include <stdlib.h>
#include <algorithm>
#include "Board.h"


Board::Board(size_t size_) {
	size = size_;
	empty_cell = (int)size * (int)size;
	board = new char*[size];
	for (size_t i = 0; i < size; i++) {
		board[i] = new char[size];
	}
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			board[i][j] = '.';
		}
	}
}

Board::~Board() {
	for (size_t i = 0; i < size; i++) {
		delete[] board[i];
	}
	delete[] board;
}


bool Board::canMove(int x, int y) const {
	return x >= 0 && x < size && y >= 0 && y < size && (board[x][y] == '.');
}

bool Board::move(int x, int y, int sign) {
	if (!canMove(x, y)) {
		return false;
	}
	if (sign == 0) {
		board[x][y] = 'O';
		empty_cell--;
		return true;
	}
	board[x][y] = 'X';
	empty_cell--;
	return true;
}

game_state_t Board::isWin(int x, int y) const {
	if (x == -1 || y == -1) {
		return GO_NEXT;
	}
	if (empty_cell == 0) {
		return DRAW;
	}
	int x_start = std::max(0, x - 4);
	int y_start = std::max(0, y - 4);
	int x_finish = std::min((int)size - 1, x + 4);
	int y_finish = std::min((int)size - 1, y + 4);

	for (int i = x_start; i <= x_finish - 4; i++) {
		if (board[i][y] == board[i+1][y] && board[i+1][y]  == board[i+2][y] && board[i+2][y] == board[i+3][y] && board[i+3][y] == board[i+4][y]) {
			return WIN;
		}
	}


	for (int i = y_start; i <= y_finish - 4; i++) {
		if (board[x][i] == board[x][i+1] && board[x][i+1] == board[x][i+2] && board[x][i+2] == board[x][i+3] && board[x][i+3] == board[x][i+4]) {
			return WIN;
		}
	}
	int count = 0;
	int start = std::min(std::min(x,y),4);
	int finish = std::min((int)size - std::max(x,y) - 1, 4);
	for (int k = 0; k < finish + start; k++) {
		if (board[x - start + k][y - start + k] == board[x - start + k + 1][y - start + k + 1]) {
			count ++;
			if (count == 4) {
				return WIN;
			}
		} else {
			count = 0;
		}
	}
	count = 0;
	start = std::min(std::min(y, (int)size - x - 1), 4);
	finish = std::min(std::min(x, (int)size - y - 1), 4);
	for (int k = 0; k < start + finish; k++) {
		if (board[x + start - k][y - start + k] == board[x + start - k - 1][y - start + k + 1]) {
			count++;
			if (count == 4) {
				return WIN;
			}
		} else {
			count = 0;
		}
	}

	return GO_NEXT;
}

size_t Board::get_size() const {
	return size;
}

char Board::get_cell(int x, int y) const {
	return board[x][y];
}