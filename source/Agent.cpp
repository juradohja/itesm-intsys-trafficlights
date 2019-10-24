#include "Agent.h";

Agent::Agent(Board * b, int st, int gl, int sz) {

	board = b;

	size = sz;

	start = new Node(st / size, st % size, 0, NULL);
	goal = new Node(gl / size, gl % size, 0, NULL);

	curLocation = new Node(st / size, st % size, 0, NULL);

	//missing logic for setting the direction
	curDirectionIsEast = true;

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

Node * Agent::aStar() {
	start->g = 0;
	start->f = start->g + diagonalDistance(start);
	while (!openList->isEmpty()) {
		Node * cur = openList->peekHead();
		if (cur->x == goal->x && cur->y == goal->y) {
			return cur;
		}
		cur = openList->removeHead();
		closedList->append(cur);
		NodeList *nbList = neighbors(cur);
		while (!nbList->isEmpty()) {
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
		}
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
		if (board->board[(x - 1) * 50 + (y - 1)] != -1) {
			Node * n0 = new Node(x - 1, y - 1, node->g + cd, node);
			neighbors->append(n0);
		}
	}

	// TOP-MIDDLE
	if (x - 1 >= 0) {
		if (board->board[(x - 1) * 50 + (y)] != -1) {
			Node * n1 = new Node(x - 1, y, node->g + cn, node);
			neighbors->append(n1);
		}
	}

	// TOP-RIGHT
	if (x - 1 >= 0 && y + 1 < size) {
		if (board->board[(x - 1) * 50 + (y + 1)] != -1) {
			Node * n2 = new Node(x - 1, y + 1, node->g + cd, node);
			neighbors->append(n2);
		}
	}

	// MIDDLE-RIGHT
	if (y + 1 < size) {
		if (board->board[(x) * 50 + (y + 1)] != -1) {
			Node * n3 = new Node(x, y + 1, node->g + cn, node);
			neighbors->append(n3);
		}
	}

	// BOTTOM-RIGHT
	if (x + 1 < size && y + 1 < size) {
		if (board->board[(x + 1) * 50 + (y + 1)] != -1) {
			Node * n4 = new Node(x + 1, y + 1, node->g + cd, node);
			neighbors->append(n4);
		}
	}

	// BOTTOM-MIDDLE
	if (x + 1 < size) {
		if (board->board[(x + 1) * 50 + (y)] != -1) {
			Node * n5 = new Node(x + 1, y, node->g + cn, node);
			neighbors->append(n5);
		}
	}

	// BOTTOM-LEFT
	if (x + 1 < size && y - 1 >= 0) {
		if (board->board[(x + 1) * 50 + (y - 1)] != -1) {
			Node * n6 = new Node(x + 1, y - 1, node->g + cd, node);
			neighbors->append(n6);
		}
	}

	// MIDDLE-LEFT
	if (y - 1 >= 0) {
		if (board->board[(x) * 50 + (y - 1)] != -1) {
			Node * n7 = new Node(x, y - 1, node->g + cn, node);
			neighbors->append(n7);
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
