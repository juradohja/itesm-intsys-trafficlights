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

	for (int y = 0; y < 5; y++) {
		board[44 * BOARD_SIZE + y] = -1;
		board[49 * BOARD_SIZE + y] = -1;
		board[54 * BOARD_SIZE + y] = -1;
	}

	for (int x = 95; x < 100; x++) {
		board[x * BOARD_SIZE + 44] = -1;
		board[x * BOARD_SIZE + 49] = -1;
		board[x * BOARD_SIZE + 54] = -1;
	}

}