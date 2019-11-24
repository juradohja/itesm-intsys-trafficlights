#include "Agent.h";
Agent::Agent(Board * b, int st, int gl, int sz) {

	board = b;

	size = sz;

	start = new Node(st / size, st % size, 0, NULL);
	goal = new Node(gl / size, gl % size, 0, NULL);

	cn = 1.0f;
	cd = 1.414f;
	
	isMoving = true;
}

Agent::~Agent() {
	delete start;
	delete goal;
}

Node * Agent::move(Board * b) {
	board = b;
    Node * newStart;
    
    
    newStart  = nextMove();
    
	if (newStart != NULL) {
		updateDirection(newStart);
		b->board[(start->x * BOARD_SIZE) + start->y] = 0;
		b->board[(newStart->x * BOARD_SIZE) + newStart->y] = 1;
		newStart->parent = NULL;
        printf("Current start x: %d y: %d , goal x: %d, y: %d \nNew updated Start: nx: %d, ny: %d \n", start->x, start->y, goal->x, goal->y, newStart->x, newStart->y);
		start = newStart;
	}
	return start;
}

Node * Agent::nextMove() {
    int nextMoveVal;
    
    if(goal->x == 99) {
        //goal in east
        nextMoveVal = board->rewardToEast[start->x][start->y];
		printf("MDP x: %d, y: %d, dir : %d\n", start->x, start->y, nextMoveVal);
    } else if(goal->y == 0) {
        //goal in south
        nextMoveVal = board->rewardToSouth[start->x][start->y];
    }
    
    Node * nextNode = getNextPossibleNode(nextMoveVal);
    
    return nextNode;
    
}

Node * Agent::getNextPossibleNode(int moveInt) {
    Node * resultNode;
    switch (moveInt) {
        case 0:
            resultNode = this->start;
            break;
        case 3:
            if (start->y < BOARD_SIZE && (board->board[(start->x) * BOARD_SIZE + (start->y + 1)] == 0)){
                resultNode = new Node(start->x, start->y+1, 0, start);
            } else if ((start->x-1 >= 0 && start->y + 1 < BOARD_SIZE) && (board->board[(start->x - 1) * BOARD_SIZE + (start->y + 1)] == 0)) {
                resultNode = new Node(start->x - 1, start->y + 1, 0, start);
            } else if((start->x+1 <BOARD_SIZE && start->y + 1 < BOARD_SIZE) && (board->board[(start->x + 1) * BOARD_SIZE + (start->y + 1)] == 0)) {
                resultNode = new Node(start->x + 1, start->y + 1, 0, start);
            } else {
                resultNode = this->start;
            }
            break;
        case 4:
            if ((start->x-1 >= 0 && start->y + 1 < BOARD_SIZE) && (board->board[(start->x - 1) * BOARD_SIZE + (start->y + 1)] == 0)) {
                resultNode = new Node(start->x - 1, start->y + 1, 0, start);
            } else if(start->y < BOARD_SIZE && (board->board[(start->x) * BOARD_SIZE + (start->y + 1)] == 0)){
                resultNode = new Node(start->x, start->y+1, 0, start);
            } else if(start->x - 1 >= 0  && (board->board[(start->x - 1) * BOARD_SIZE + (start->y)] == 0)) {
                resultNode = new Node(start->x - 1, start->y, 0, start);
            } else {
                resultNode = this->start;
            }
            break;
        case 5:
            if (start->x - 1 >= 0  && (board->board[(start->x - 1) * BOARD_SIZE + (start->y)] == 0)){
                resultNode = new Node(start->x - 1, start->y, 0, start);
            } else if ((start->x-1 >= 0 && start->y + 1 < BOARD_SIZE) && (board->board[(start->x - 1) * BOARD_SIZE + (start->y + 1)] == 0)) {
                resultNode = new Node(start->x - 1, start->y + 1, 0, start);
            } else if((start->x -1 >= 0 && start->y - 1 >= 0) && (board->board[(start->x - 1) * BOARD_SIZE + (start->y - 1)] == 0)){
                resultNode = new Node(start->x - 1, start->y - 1, 0, start);
            } else {
                resultNode = this->start;
            }
            break;
        case 6:
            if((start->x -1 >= 0 && start->y - 1 >= 0) && (board->board[(start->x - 1) * BOARD_SIZE + (start->y - 1)] == 0)){
                resultNode = new Node(start->x - 1, start->y - 1, 0, start);
            } else if (start->x - 1 >= 0  && (board->board[(start->x - 1) * BOARD_SIZE + (start->y)] == 0)){
                resultNode = new Node(start->x - 1, start->y, 0, start);
            } else if (start->y - 1 >=0 && (board->board[(start->x) * BOARD_SIZE + (start->y - 1)] == 0)){
                resultNode = new Node(start->x, start->y - 1, 0, start);
            } else {
                resultNode = this->start;
            }
            break;
        case 7:
            if (start->y - 1 >=0 && (board->board[(start->x) * BOARD_SIZE + (start->y - 1)] == 0)){
                resultNode = new Node(start->x, start->y - 1, 0, start);
            } else if((start->x -1 >= 0 && start->y - 1 >= 0) && (board->board[(start->x - 1) * BOARD_SIZE + (start->y - 1)] == 0)){
                resultNode = new Node(start->x - 1, start->y - 1, 0, start);
            } else if ((start->x + 1 < BOARD_SIZE && start->y - 1 >= 0) &&(board->board[(start->x + 1) * BOARD_SIZE + (start->y - 1)] == 0)){
                resultNode = new Node(start->x + 1, start->y - 1, 0, start);
            } else {
                resultNode = this->start;
            }
            break;
        case 8:
            if ((start->x + 1 < BOARD_SIZE && start->y - 1 >= 0) &&(board->board[(start->x + 1) * BOARD_SIZE + (start->y - 1)] == 0)){
                resultNode = new Node(start->x + 1, start->y - 1, 0, start);
            } else if (start->y - 1 >=0 && (board->board[(start->x) * BOARD_SIZE + (start->y - 1)] == 0)){
                resultNode = new Node(start->x, start->y - 1, 0, start);
            } else if (start->x + 1 <BOARD_SIZE &&(board->board[(start->x + 1) * BOARD_SIZE + (start->y)] == 0)){
                resultNode = new Node(start->x + 1, start->y, 0, start);
            } else {
                resultNode = this->start;
            }
            break;
        case 1:
            if (start->x + 1 <BOARD_SIZE &&(board->board[(start->x + 1) * BOARD_SIZE + (start->y)] == 0)){
                resultNode = new Node(start->x + 1, start->y, 0, start);
            } else if ((start->x + 1 < BOARD_SIZE && start->y - 1 >= 0) &&(board->board[(start->x + 1) * BOARD_SIZE + (start->y - 1)] == 0)){
                resultNode = new Node(start->x + 1, start->y - 1, 0, start);
            } else if ((start->x+1 <BOARD_SIZE && start->y + 1 <BOARD_SIZE) && (board->board[(start->x + 1) * BOARD_SIZE + (start->y + 1)] == 0)){
                resultNode = new Node(start->x + 1, start->y + 1, 0, start);
            } else {
                resultNode = this->start;
            }
            break;
        case 2:
            if ((start->x+1 <BOARD_SIZE && start->y + 1 <BOARD_SIZE) && (board->board[(start->x + 1) * BOARD_SIZE + (start->y + 1)] == 0)){
                resultNode = new Node(start->x + 1, start->y + 1, 0, start);
            } else if (start->x + 1 <BOARD_SIZE &&(board->board[(start->x + 1) * BOARD_SIZE + (start->y)] == 0)){
                resultNode = new Node(start->x + 1, start->y, 0, start);
            } else if (start->y < BOARD_SIZE && (board->board[(start->x) * BOARD_SIZE + (start->y + 1)] == 0)){
                resultNode = new Node(start->x, start->y + 1, 0, start);
            } else {
                resultNode = this->start;
            }
            break;
        default:
            resultNode = this->start;
            break;
    }
    return resultNode;
}

void Agent::updateDirection(Node * newSt) {
	int dispX = newSt->x - start->x;
    int dispY = newSt->y - start->y;
	if (dispX == 0 && dispY == 0) {
		isMoving = false;
	}
	else { isMoving = true; }
    if (dispX == 0 && dispY == 1) {
        curDirection = 0;    // NORTH
    }
    if (dispX == 1 && dispY == 1) {
        curDirection = 1;    // NORTH-EAST
    }
    else if (dispX == 1 && dispY == 0) {
        curDirection = 2;    // EAST
    }
    else if (dispX == 1 && dispY == -1) {
        curDirection = 3;    // SOUTH-EAST
    }
    else if (dispX == 0 && dispY == -1) {
        curDirection = 4;    // SOUTH
    }
    else if (dispX == -1 && dispY == -1) {
        curDirection = 5;    // SOUTH-WEST
    }
    else if (dispX == -1 && dispY == 0) {
        curDirection = 6;    // WEST
    }
    else if (dispX == -1 && dispY == 1) {
        curDirection = 7;    // NORTH-WEST
    }
}

void Agent::draw() {
	glPushMatrix(); {
		glTranslatef(-50, -50, 0);
		glTranslatef(start->x + 0.5, start->y + 0.5, 0.003);
		glRotatef(-45 * curDirection, 0, 0, 1);
        if(!isMoving) {
            glColor3f(1.0, 0.4, 0.2);
        } else {
            glColor3f(0, 0.5, 1.0);
        }
		glBegin(GL_POLYGON); {
			glVertex3f(0, 0.4, 0);
			glVertex3f(0.25, -0.4, 0);
			glVertex3f(-0.25, -0.4, 0);
		} glEnd();
	} glPopMatrix();
}
