#include "Environment.h"

Environment::Environment() {
	board = Board();
	board.setWalls();

	frameRate = 30;
	frame = 0;

	lightNS = 2;
	lightWE = 0;
}

Environment::~Environment() {

}

void Environment::drawStreetGrid() {
	glBegin(GL_LINES); {
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(20, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 20, 0);
	} glEnd();



	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS); {
		glVertex3f(-50, -10, -0.002);
		glVertex3f(50, -10, -0.002);
		glVertex3f(50, 10, -0.002);
		glVertex3f(-50, 10, -0.002);

		glVertex3f(-10, -50, -0.002);
		glVertex3f(10, -50, -0.002);
		glVertex3f(10, 50, -0.002);
		glVertex3f(-10, 50, -0.002);
	} glEnd();

	glLineWidth(0.0001);
	glBegin(GL_LINES);
	{
		glColor3f(0.8,0.8,0.8);

		for (int i = -50; i <= 50; i++) {
			if (-10 <= i && i <= 10) {
				glVertex3f(i, -50, 0);
				glVertex3f(i, 50, 0);
			}
			else {
				glVertex3f(i, -10, 0);
				glVertex3f(i, 10, 0);
			}
		}

		for (int i = -50; i <= 50; i++) {
			if (-10 <= i && i <= 10) {
				glVertex3f(-50, i, 0);
				glVertex3f(50, i, 0);
			}
			else {
				glVertex3f(-10, i, 0);
				glVertex3f(10, i, 0);
			}
		}

	} glEnd();
}

void Environment::draw() {
	drawStreetGrid();
}

void Environment::update() {
	if (frame == 30) {
		// update functions
	}
	else {
		frame++;
	}
}

void Environment::spawnCar() {
	
	bool flag = true;
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<> uni(40,59);
    Agent * newCar;
    
	while(flag){
		ranInt = uni(rng); // ranInt is par starts in north, else in west
		ranInt2 = uni(rng); // ranInt2 is par goal is south, else east

		if(ranInt % 2 == 0) {
			if (board.board[ranInt] == 0) {
				if( ranInt2 % 2 == 0) {
					newCar = new Agent(&board, ranInt, ranInt2+9900, BOARD_SIZE);
				} else {
					newCar = new Agent(&board, ranInt, 100*ranInt2+99, BOARD_SIZE);
				}
				flag = false;
			}
		} else {
			if (board.board[ranInt*BOARD_SIZE] == 0) {
				if( ranInt2 % 2 == 0) {
					newCar = new Agent(&board, ranInt*BOARD_SIZE, ranInt2+9900, BOARD_SIZE);
				} else {
					newCar = new Agent(&board, ranInt*BOARD_SIZE, BOARD_SIZE*ranInt2+99, BOARD_SIZE);
				}
				flag = false;
			}
		}
	}
    cars.push_back(newCar);
	
}





