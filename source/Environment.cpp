#include "Environment.h"

Environment::Environment() {
	board = Board();
	board.setWalls();

	frame = 0;

	lightNS = 2;
	lightWE = 0;

	activeTime = 0.0;
	timeLeft = LIGHTBASETIME;
	densN = 0;
	densW = 0;
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
	if (lightNS == 2) {
		glBegin(GL_POLYGON); {
			glColor3f(0, 1, 0);
			glVertex3f(-10, 10, 0.001);
			glVertex3f(10, 10, 0.001);
			glVertex3f(10, 11, 0.001);
			glVertex3f(-10, 11, 0.001);

			glColor3f(1, 0, 0);
			glVertex3f(-10, 10, 0.001);
			glVertex3f(-11, 10, 0.001);
			glVertex3f(-11, -10, 0.001);
			glVertex3f(-10, -10, 0.001);
		} glEnd();
	}
	if (lightWE == 2) {
		glBegin(GL_POLYGON); {
			glColor3f(1, 0, 0);
			glVertex3f(-10, 10, 0.001);
			glVertex3f(10, 10, 0.001);
			glVertex3f(10, 11, 0.001);
			glVertex3f(-10, 11, 0.001);

			glColor3f(0, 1, 0);
			glVertex3f(-10, 10, 0.001);
			glVertex3f(-11, 10, 0.001);
			glVertex3f(-11, -10, 0.001);
			glVertex3f(-10, -10, 0.001);
		} glEnd();
	}
	for each (Agent * car in cars)
	{
		car->draw();
		printf("Drawing car");
	}
}

void Environment::update() {
	if (frame == FRAMERATE) {
		frame = 0;
		// update functions
		// hay que cambiar cuando activeTime >= MAXENTENSION o cuando timeLeft <= 0
		
		// Llamada a FL System
		if (int(activeTime) % CYCLETIME == 0) {
			
			calculateTrafficDensities();
			if (lightNS == 2) { // north is active, west is non-active
				timeLeft += fuzzyfy(densN, densW);
			}
			else if (lightWE == 2) { // west is active, north is non-active
				timeLeft += fuzzyfy(densW, densN);
			}
		}
		for each (Agent * car in cars) {
			car->move(&board);
		}
		spawnCar();
		activeTime++;
		timeLeft--;
		if (activeTime >= MAXEXTENSION || timeLeft <= 0) {
			if (lightNS == 2) {
				lightNS = 0;
				lightWE = 2;
				for (int i = 40; i < 60; i++) {
					board.board[(i * 100) + 40] = -1;
					board.board[(39 * 100) + i] = 0;
				}
			}
			else if (lightWE == 2) {
				lightNS = 2;
				lightWE = 0;
				for (int i = 40; i < 60; i++) {
					board.board[(39 * 100) + i] = -1;
					board.board[(i * 100) + 40] = 0;
				}
			}
			timeLeft = LIGHTBASETIME;
			activeTime = 0;
		}
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
	int counter = 0;
    
	while(counter < 20 && flag){
		ranInt = uni(rng); // ranInt is par starts in west, else in north
		ranInt2 = uni(rng); // ranInt2 is par goal is south, else east

		if(ranInt % 2 == 0) {
			if (board.board[ranInt] == 0) {
				if( ranInt2 % 2 == 0) {
					newCar = new Agent(&board, ranInt, ranInt2*100, BOARD_SIZE);
				} else {
					newCar = new Agent(&board, ranInt, ranInt2+9900, BOARD_SIZE);
				}
				flag = false;
			}
		} else {
			if (board.board[ranInt*BOARD_SIZE+99] == 0) {
				if( ranInt2 % 2 == 0) {
					newCar = new Agent(&board, ranInt*BOARD_SIZE+99, ranInt2*100, BOARD_SIZE);
				} else {
					newCar = new Agent(&board, ranInt*BOARD_SIZE+99, ranInt2+9900, BOARD_SIZE);
				}
				flag = false;
			}
		}

		counter++;
	}
    cars.push_back(newCar);
	
}



void Environment::calculateTrafficDensities() {
	int n = THRESHOLD * 20;
	int cn = 0; // counter north
	int cw = 0; // counter west

	// Calculating density for west
	for (int i = 40 - THRESHOLD; i < 40; i++) {
		for (int j = 40; j < 60; j++) {
			if (board.board[(i * 100) + j] == 1) {
				cw++;
			}
		}
	}
	densW = cw / n;

	// Calculating density for north
	for (int j = 40 - THRESHOLD; j < 40; j++) {
		for (int i = 40; i < 60; i++) {
			if (board.board[(i * 100) + j] == 1) {
				cn++;
			}
		}
	}
	densN = cn / n;
}



