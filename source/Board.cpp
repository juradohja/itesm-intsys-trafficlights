#include "Board.h";

Board::Board() {
	setWalls();
}

Board::~Board(){}

void Board::setWalls() {
	srand(time(0));
	for (int i = 0; i < 10000; i++) {
		int x = i % 100;
		int y = i / 100;
		if ((x < 40 && y < 40) ||
			(x >= 60 && y < 40) ||
			(x < 40 && y >= 60) ||
			(x >= 60 && y >= 60)) {
			board[i] = -1;
		}
	}

}