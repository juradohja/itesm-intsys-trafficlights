#include "Agent.h";
Agent::Agent(Board * b, int st, int gl, int sz) {

	board = b;

	size = sz;

	start = new Node(st / size, st % size, 0, NULL);
	goal = new Node(gl / size, gl % size, 0, NULL);

	//missing logic for setting the direction

	openList = new NodeList();
	closedList = new NodeList();

	cn = 1.0f;
	cd = 1.414f;
	
	openList->head = start;
	openList->tail = openList->head;
    
}

Agent::~Agent() {
	delete start;
	delete goal;
	delete openList;
	delete closedList;
}

Node * Agent::move(Board * b) {
	board = b;
	Node * newStart = aStar();
	if (newStart != NULL) {
		updateDirection(newStart);
		b->board[(start->x * 100) + start->y] = 0;
		b->board[(newStart->x * 100) + newStart->y] = 1;
		newStart->parent = NULL;
        printf("Current start x: %d y: %d , goal x: %d, y: %d \nNew updated Start: nx: %d, ny: %d \n", start->x, start->y, goal->x, goal->y, newStart->x, newStart->y);
		start = newStart;
		openList->head = start;
		openList->tail = openList->head;
	}
	return start;
}

Node * Agent::aStar() {
	start->g = 0;
	start->f = start->g + diagonalDistance(start);
	if (!openList->isEmpty()) {
		Node * cur = openList->peekHead();
		if (cur->x == goal->x && cur->y == goal->y) {
			return cur;
		}
		cur = openList->removeHead();
		closedList->append(cur);
		NodeList *nbList = neighbors(cur);
		if (!nbList->isEmpty()) { //segun yo con cambiar el while por un if
            Node * neighbor = nbList->removeHead();
			
			if (!closedList->isInList(neighbor)) {
				neighbor->f = neighbor->g + diagonalDistance(neighbor);
				if (!openList->isInList(neighbor)) {
					openList->addSorted(neighbor);
				}
				else {
					Node * openNb = openList->getNode(neighbor);
					if (neighbor->g < openNb->g) {
						openNb->g = neighbor->g;
						openNb->parent = neighbor->parent;
					}
				}
			}
            return neighbor;
			
		}
		//aqui regresar el node cur o el que sigue en remove head creo para solo regresar un nodo...
		delete nbList;
	}
	printf("ERROR: A solution doesn't exist.\n");
	return nullptr;
}

NodeList * Agent::neighbors(Node * node) {
	NodeList * neighbors = new NodeList();
	int x = node->x;
	int y = node->y;
	
	// TOP-LEFT
	if (x - 1 >= 0 && y - 1 >= 0) {
		if (board->board[(x - 1) * BOARD_SIZE + (y - 1)] == 0) {
			Node * n0 = new Node(x - 1, y - 1, node->g + cd, node);
			neighbors->addSorted(n0);
		}
	}

	// TOP-MIDDLE
	if (x - 1 >= 0) {
		if (board->board[(x - 1) * BOARD_SIZE + (y)] == 0) {
			Node * n1 = new Node(x - 1, y, node->g + cn, node);
			neighbors->addSorted(n1);
		}
	}

	// TOP-RIGHT
	if (x - 1 >= 0 && y + 1 < size) {
		if (board->board[(x - 1) * BOARD_SIZE + (y + 1)] == 0) {
			Node * n2 = new Node(x - 1, y + 1, node->g + cd, node);
			neighbors->addSorted(n2);
		}
	}

	// MIDDLE-RIGHT
	if (y + 1 < size) {
		if (board->board[(x) * BOARD_SIZE + (y + 1)] == 0) {
			Node * n3 = new Node(x, y + 1, node->g + cn, node);
			neighbors->addSorted(n3);
		}
	}

	// BOTTOM-RIGHT
	if (x + 1 < size && y + 1 < size) {
		if (board->board[(x + 1) * BOARD_SIZE + (y + 1)] == 0) {
			Node * n4 = new Node(x + 1, y + 1, node->g + cd, node);
			neighbors->addSorted(n4);
		}
	}

	// BOTTOM-MIDDLE
	if (x + 1 < size) {
		if (board->board[(x + 1) * BOARD_SIZE + (y)] == 0) {
			Node * n5 = new Node(x + 1, y, node->g + cn, node);
			neighbors->addSorted(n5);
		}
	}

	// BOTTOM-LEFT
	if (x + 1 < size && y - 1 >= 0) {
		if (board->board[(x + 1) * BOARD_SIZE + (y - 1)] == 0) {
			Node * n6 = new Node(x + 1, y - 1, node->g + cd, node);
			neighbors->addSorted(n6);
		}
	}

	// MIDDLE-LEFT
	if (y - 1 >= 0) {
		if (board->board[(x) * BOARD_SIZE + (y - 1)] == 0) {
			Node * n7 = new Node(x, y - 1, node->g + cn, node);
			neighbors->addSorted(n7);
		}
	}

	return neighbors;
}

float Agent::diagonalDistance(Node * node) {
	float dmax = max(abs(node->x - goal->x), abs(node->y - goal->y));
	float dmin = min(abs(node->x - goal->x), abs(node->y - goal->y));
	float h = cd * dmin + cn * (dmax - dmin);
	return h;
}

void Agent::updateDirection(Node * newSt) {
	int dispX = newSt->x - start->x;
	int dispY = newSt->y - start->y;
	if (dispX == 0 && dispY == 1) {
		curDirection = 0;	// NORTH
	}
	if (dispX == 1 && dispY == 1) {
		curDirection = 1;	// NORTH-EAST
	}
	else if (dispX == 1 && dispY == 0) {
		curDirection = 2;	// EAST
	}
	else if (dispX == 1 && dispY == -1) {
		curDirection = 3;	// SOUTH-EAST
	}
	else if (dispX == 0 && dispY == -1) {
		curDirection = 4;	// SOUTH
	}
	else if (dispX == -1 && dispY == -1) {
		curDirection = 5;	// SOUTH-WEST
	}
	else if (dispX == -1 && dispY == 0) {
		curDirection = 6;	// WEST
	}
	else if (dispX == -1 && dispY == 1) {
		curDirection = 7;	// NORTH-WEST
	}
}

void Agent::draw() {
	glPushMatrix(); {
		glTranslatef(-50, -50, 0);
		glTranslatef(start->x + 0.5, start->y + 0.5, 0.003);
		glRotatef(45 * curDirection, 0, 0, 1);
		glColor3f(0, 0, 0.8);	
		glBegin(GL_POLYGON); {
			glVertex3f(0, 0.4, 0);
			glVertex3f(0.25, -0.4, 0);
			glVertex3f(-0.25, -0.4, 0);
		} glEnd();
	} glPopMatrix();
}
