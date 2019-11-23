#include "Board.h";

Board::Board() {
	setWalls();
	
}

Board::~Board(){}

void Board::setWalls() {
	srand(time(0));
	for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++) {
		int x = i % BOARD_SIZE;
		int y = i / BOARD_SIZE;
		if ((x < 40 && y < 40) ||
			(x >= 60 && y < 40) ||
			(x < 40 && y >= 60) ||
			(x >= 60 && y >= 60)) {
			board[i] = -1;
		}
	}
}