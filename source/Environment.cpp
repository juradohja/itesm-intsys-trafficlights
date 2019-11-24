#include "Environment.h"

Environment::Environment() {
    board = Board();
    log = nullptr;
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
    glBegin(GL_LINES);
    {
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(20, 0, 0);

        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 20, 0);
    }
    glEnd();


    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    {
        glVertex3f(-50, -10, -0.002);
        glVertex3f(50, -10, -0.002);
        glVertex3f(50, 10, -0.002);
        glVertex3f(-50, 10, -0.002);

        glVertex3f(-10, -50, -0.002);
        glVertex3f(10, -50, -0.002);
        glVertex3f(10, 50, -0.002);
        glVertex3f(-10, 50, -0.002);
    }
    glEnd();


	// SIDES
	glColor3f(1, 0.83, 0.65);
	glBegin(GL_QUADS);
	{
		glVertex3f(-50, 10, -0.001);
		glVertex3f(-50, 8, -0.001);
		glVertex3f(-8, 8, -0.001);
		glVertex3f(-8, 10, -0.001);

		glVertex3f(8, 8, -0.001);
		glVertex3f(49, 8, -0.001);
		glVertex3f(49, 10, -0.001);
		glVertex3f(8, 10, -0.001);

		glVertex3f(-50, -10, -0.001);
		glVertex3f(-50, -8, -0.001);
		glVertex3f(-8, -8, -0.001);
		glVertex3f(-8, -10, -0.001);

		glVertex3f(8, -8, -0.001);
		glVertex3f(49, -8, -0.001);
		glVertex3f(49, -10, -0.001);
		glVertex3f(8, -10, -0.001);



		glVertex3f(-8, -49, -0.001);
		glVertex3f(-10, -49, -0.001);
		glVertex3f(-10, -8, -0.001);
		glVertex3f(-8, -8, -0.001);

		glVertex3f(8, -49, -0.001);
		glVertex3f(10, -49, -0.001);
		glVertex3f(10, -8, -0.001);
		glVertex3f(8, -8, -0.001);

		glVertex3f(-8, 8, -0.001);
		glVertex3f(-10, 8, -0.001);
		glVertex3f(-10, 50, -0.001);
		glVertex3f(-8, 50, -0.001);

		glVertex3f(8, 8, -0.001);
		glVertex3f(10, 8, -0.001);
		glVertex3f(10, 50, -0.001);
		glVertex3f(8, 50, -0.001);

	}
	glEnd();

	// GOALS
	glColor3f(0, 0.7, 0);
	glBegin(GL_QUADS); {
		glVertex3f(-10, -50, -0.001);
		glVertex3f(-10, -49, -0.001);
		glVertex3f(10, -49, -0.001);
		glVertex3f(10, -50, -0.001);

		glVertex3f(50, -10, -0.001);
		glVertex3f(49, -10, -0.001);
		glVertex3f(49, 10, -0.001);
		glVertex3f(50, 10, -0.001);
	}
	glEnd();


	// FINAL WALLS
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_QUADS); {
		glVertex3f(-4, -2, -0.001);
		glVertex3f(-4, 2, -0.001);
		glVertex3f(4, 2, -0.001);
		glVertex3f(4, -2, -0.001);

		glVertex3f(-2, -4, -0.001);
		glVertex3f(2, -4, -0.001);
		glVertex3f(2, 4, -0.001);
		glVertex3f(-2, 4, -0.001);



		glVertex3f(-6, -50, -0.0005);
		glVertex3f(-5, -50, -0.0005);
		glVertex3f(-5, -46, -0.0005);
		glVertex3f(-6, -46, -0.0005);

		glVertex3f(-1, -50, -0.0005);
		glVertex3f(0, -50, -0.0005);
		glVertex3f(0, -46, -0.0005);
		glVertex3f(-1, -46, -0.0005);

		glVertex3f(4, -50, -0.0005);
		glVertex3f(5, -50, -0.0005);
		glVertex3f(5, -46, -0.0005);
		glVertex3f(4, -46, -0.0005);


		glVertex3f(45, -5, -0.0005);
		glVertex3f(50, -5, -0.0005);
		glVertex3f(50, -6, -0.0005);
		glVertex3f(45, -6, -0.0005);

		glVertex3f(45, 0, -0.0005);
		glVertex3f(50, 0, -0.0005);
		glVertex3f(50, 1, -0.0005);
		glVertex3f(45, 1, -0.0005);

		glVertex3f(45, 5, -0.0005);
		glVertex3f(50, 5, -0.0005);
		glVertex3f(50, 6, -0.0005);
		glVertex3f(45, 6, -0.0005);
	}
	glEnd();


    glLineWidth(0.0001);
    glBegin(GL_LINES);
    {
        glColor3f(0.5, 0.5, 0.5);

        for (int i = -50; i <= 50; i++) {
            if (-10 <= i && i <= 10) {
                glVertex3f(i, -50, 0);
                glVertex3f(i, 50, 0);
            } else {
                glVertex3f(i, -10, 0);
                glVertex3f(i, 10, 0);
            }
        }

        for (int i = -50; i <= 50; i++) {
            if (-10 <= i && i <= 10) {
                glVertex3f(-50, i, 0);
                glVertex3f(50, i, 0);
            } else {
                glVertex3f(-10, i, 0);
                glVertex3f(10, i, 0);
            }
        }

    }
    glEnd();
}

void Environment::draw() {
    //printf("DRAWING BOARD WITH SEMAFORES AND CARS \n");
    *log << "DRAWING BOARD WITH SEMAFORES AND CARS \n";
    drawStreetGrid();
    if (lightNS == 2) {
        glBegin(GL_POLYGON);
        {
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
        }
        glEnd();
    }
    if (lightWE == 2) {
        glBegin(GL_POLYGON);
        {
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
        }
        glEnd();
    }
    for (Agent *car : cars) {
        car->draw();
    }
}

bool Environment::touchDown(Agent *value) {
    if (value->goal->x == 99) {
        //goal is in east
        if(value->start->x == 99) {
            return true;
        }
    } else if(value->goal->y == 0) {
        //goal is in south
        if(value->start->y == 0) {
            return true;
        }
    }
    return false;
}

void Environment::update() {
    if (frame == FRAMERATE){
        spawnCar();
        spawnCar();
        spawnCar();
        spawnCar();
        spawnCar();
        activeTime++;
        timeLeft--;
        printf("UPDATE FUNCTION CALLED \n");
        *log << "UPDATE FUNCTION CALLED\n";
        frame = 0;
        // update functions
        // hay que cambiar cuando activeTime >= MAXENTENSION o cuando timeLeft <= 0

        // Llamada a FL System
        if (int(activeTime) % CYCLETIME == 0) {
            calculateTrafficDensities();
            if (lightNS == 2) { // north is active, west is non-active
                timeLeft += fuzzyfy(densN, densW, log);
            } else if (lightWE == 2) { // west is active, north is non-active
                timeLeft += fuzzyfy(densW, densN,log);
            }
            printf("FUZZYFY CALLED with densN: %g, densW: %g, timeLeft: %g \n", densN, densW, timeLeft);
            *log << "FUZZYFY CALLED with densN: %g, densW: %g, timeLeft: %g";
		}
        list<Agent*>::iterator it = cars.begin();
        while(it != cars.end()) {
            if(touchDown(*it)) {
				delete *it;
            } else {
                it++;
            }
        }
		if (activeTime >= MAXEXTENSION || timeLeft <= 0) {
            printf("<==========LIGHT CHANGE==========>\n");
            *log << "<==========LIGHT CHANGE==========>\n";
			if (lightNS == 2) {
				lightNS = 0;
				lightWE = 2;
				for (int i = 40; i < 60; i++) {
					board.board[(i * 100) + 60] = -1;
                    board.board[(i * 100) + 59] = -1;
                    
					board.board[(40 * 100) + i] = 0;
                    board.board[(39 * 100) + i] = 0;
 
				}
                board.board[59 + 59] = 0;
                board.board[60 + 59] = 0;
                
                board.board[40 + 39] = -1;
                board.board[40 + 40] = -1;
			}
			else if (lightWE == 2) {
				lightNS = 2;
				lightWE = 0;
				for (int i = 40; i < 60; i++) {
					board.board[(40 * 100) + i] = -1;
                    board.board[(39 * 100) + i] = -1;

                    board.board[(i * 100) + 60] = 0;
                    board.board[(i * 100) + 59] = 0;
				}
                board.board[59 + 59] = -1;
                board.board[60 + 59] = -1;
                
                board.board[40 + 39] = 0;
                board.board[40 + 40] = 0;
                
			}
			timeLeft = LIGHTBASETIME;
			activeTime = 0;
		}
        
        printf("UPDATING CARS \n");
        *log << "UPDATING CARS";
        int counter = 0;
        for (Agent * car : cars) {
            car->move(&board);
            printf("Car # %d start: sx->%d sy->%d goal: gx->%d gy->%d \n\n", counter, car->start->x, car->start->y, car->goal->x, car->goal->y);
            *log << "Car # %d start: sx->%d sy->%d goal: gx->%d gy->%d \n\n";
            counter++;
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
    uniform_int_distribution<> uni(40, 59);
    Agent *newCar;
    int counter = 0;

    while (counter < 20 && flag) {
        ranInt = uni(rng); // ranInt is par starts in west, else in north
        ranInt2 = uni(rng); // ranInt2 is par goal is south, else east

        if (ranInt % 2 == 0) {
            if (board.board[ranInt] == 0) {
                if (ranInt2 % 2 == 0) {
                    newCar = new Agent(&board, ranInt, ranInt2 * 100, BOARD_SIZE); //start in west and goal in south
                } else {
                    newCar = new Agent(&board, ranInt, ranInt2 + 9900, BOARD_SIZE); // start in west and goal in east
                }
                flag = false;
            }
        } else {
            if (board.board[ranInt * BOARD_SIZE + 99] == 0) {
                if (ranInt2 % 2 == 0) {
                    newCar = new Agent(&board, ranInt * BOARD_SIZE + 99, ranInt2 * 100, BOARD_SIZE); // start in north and goal in south
                } else {
                    newCar = new Agent(&board, ranInt * BOARD_SIZE + 99, ranInt2 + 9900, BOARD_SIZE); // start in north and goal in east
                }
                flag = false;
            }
        }

        counter++;
    }
    printf("SPAWN CAR CALLED ADDED A CAR TO CARS LIST \n");
    *log << "SPAWN CAR CALLED ADDED A CAR TO CARS LIST \n";
    cars.push_back(newCar);
}

void Environment::calculateTrafficDensities() {
    float n = THRESHOLD * 20;
    float cn = 0; // counter north
    float cw = 0; // counter west

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
