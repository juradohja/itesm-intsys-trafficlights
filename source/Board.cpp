#include "Board.h";

Board::Board() {
	setWalls();
}

Board::~Board(){}

void Board::setWalls() {
	srand(time(0));
	int n = 500 + (rand() % (800 - 500)) + 1;
	for (int i = 0; i < n; i++) {
		int x = (rand() % 2500);
		board[x] = -1;
	}
}