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