/*
 * A01336424 | Kai Kawasaki Ueda
 * A01336435 | Sergio Ugalde Marcano
 * A01336656 | José Alberto Jurado Hernández
 *
 * TC2011. Intelligent Systems Course.
 */

/*
	Problem Formulation:
	Initial state: Three agents in a random square on the left-most column
		of a 50x50 board, with 500-800 walls, and a random goal square in the
		right-most column.
	Action: Move the agent to any adjacent square (horizontally, vertically,
		or diagonally) that is not a wall and moves the agent closer to the
		goal.
	Transition Model: the agent is moved to an adjacent square that is not a
		wall and moves the agent closer to the goal.
	Goal Test: the agent has reached the goal through a valid route.
	Path cost: 1 for each non-diagonal step; 1.414 for each diagonal step.
*/

/*
	Environment:
	Fully observable: the agent knows perfectly where the goal is and can
		detect adjacent walls.
	Deterministic: the next state of the environment will completely be defined
		by the actions taken by the agents.
	Episodic: 
	Static: the environment doesn't change while the agent is deciding where
		to move to.
	Discrete: time only exists as a function of the steps taken by the agent.
	Known: the agent has complete understanding of the consequences of its
		actions in the environment.

*/

/*
	INSTRUCTIONS: Press keys 1-3 to see the path taken by the three different
	agents.
*/

#ifdef __APPLE__
// For XCode only: New C++ terminal project. Build phases->Compile with libraries: add OpenGL and GLUT
// Import this whole code into a new C++ file (main.cpp, for example). Then run.
// Reference: https://en.wikibooks.org/wiki/OpenGL_Programming/Installation/Mac
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#endif
#ifdef _WIN32
// For VS on Windows only: Download CG_Demo.zip. UNZIP FIRST. Double click on CG_Demo/CG_Demo.sln
// Run
	#include "freeglut.h"
#endif
#ifdef __unix__
// For Linux users only: g++ CG_Demo.cpp -lglut -lGL -o CG_Demo
// ./CG_Demo
// Reference: https://www.linuxjournal.com/content/introduction-opengl-programming
	#include "GL/freeglut.h"
	#include "GL/gl.h"
#endif

#include <stdio.h>
#include <math.h>
#include "Board.h"
#include "Agent.h"
#include "Environment.h"

using namespace std;

Board b;
Agent * red, * green, * blue;
Node * redList, *greenList, *blueList;
Environment env;
int activeAgent;

void printBoard() {
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			printf("%d ", b.board[(i*50)+j]);
		}
		printf("\n");
	}
	printf("\n");
}

void printPath(Node * head) {
	Node * cur = head;
	while (cur != NULL) {
		printf("(%d, %d)\n", cur->x, cur->y);
		cur = cur->parent;
	}
}

void drawBoard(Board * b) {
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS); {
		glVertex3f(0, 0, -0.002);
		glVertex3f(0, 50, -0.002);
		glVertex3f(50, 50, -0.002);
		glVertex3f(50, 0, -0.002);
	} glEnd();

	glColor3f(0.15, 0.15, 0.15);
	glBegin(GL_QUADS); {
		for (int i = 0; i < 2500; i++) {
			if (b->board[i] == -1) {
				glVertex3f((i / 50), (i % 50), 0.001);
				glVertex3f((i / 50), (i % 50) + 1, 0.001);
				glVertex3f((i / 50) + 1, (i % 50) + 1, 0.001);
				glVertex3f((i / 50) + 1, (i % 50), 0.001);
			}
		}
	} glEnd();

	glLineWidth(1.0);
	glBegin(GL_LINES);
	{
		glColor3f(1, 1, 1);
		for (int i = 0; i <= 50; i++) {
			glVertex3f(0, i, 0);
			glVertex3f(50, i, 0);
		}
		for (int i = 0; i <= 50; i++) {
			glVertex3f(i, 0, 0);
			glVertex3f(i, 50, 0);
		}
	} glEnd();
}

void drawPath(Node * head, float r, float g, float b) {
	Node * cur = head;
	glColor3f(r, g, b);
	while (cur != NULL) {
		glPushMatrix(); {
			glTranslatef(cur->x + 0.5, cur->y + 0.5, 0.01);
			glutSolidSphere(0.3, 20, 20);
		} glPopMatrix();
		cur = cur->parent;
	}
}

void init() // FOR GLUT LOOP
{
	glEnable(GL_DEPTH_TEST);			// Enable check for close and far objects.
	glClearColor(0.0, 0.0, 0.0, 0.0);	// Clear the color state.
	glMatrixMode(GL_MODELVIEW);			// Go to 3D mode.
	glLoadIdentity();					// Reset 3D view matrix.

	b = Board();
	// printBoard();

	env = Environment();

	int redStart;
	do {
		redStart = rand() % 50;
	} while (b.board[redStart] == -1);

	int greenStart;
	do {
		greenStart = rand() % 50;
	} while (b.board[greenStart] == -1 || greenStart == redStart);

	int blueStart;
	do {
		blueStart = rand() % 50;
	} while (b.board[blueStart] == -1 || blueStart == redStart || blueStart == greenStart);

	int goal;
	do {
		goal = 2450 + (rand() % 50);
	} while (b.board[goal] == -1);

	red = new Agent(&b, redStart, goal, 50);
	green = new Agent(&b, greenStart, goal, 50);
	blue = new Agent(&b, blueStart, goal, 50);

	redList = red->aStar();
	greenList = green->aStar();
	blueList = blue->aStar();

	activeAgent = 1;

	// printPath(redList);
}

void display()							// Called for each frame (about 60 times per second).
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clear color and depth buffers.
	glLoadIdentity();												// Reset 3D view matrix.
	gluLookAt(0.0, 0.0, 140.0,										// Where the camera is.
		      0.0, 0.0, 0.0,										// To where the camera points at.
		      0.0, 1.0, 0.0);										// "UP" vector.
	/*
	drawBoard(&b);
	switch (activeAgent) {
	case 1:
		drawPath(redList, 1, 0, 0);
		break;
	case 2:
		drawPath(greenList, 0, 1, 0);
		break;
	case 3:
		drawPath(blueList, 0, 0, 1);
		break;
	}
	*/
	env.draw();
	glutSwapBuffers();												// Swap the hidden and visible buffers.
}

void idle()															// Called when drawing is finished.
{
	glutPostRedisplay();											// Display again.
}

void reshape(int x, int y)											// Called when the window geometry changes.
{
	glMatrixMode(GL_PROJECTION);									// Go to 2D mode.
	glLoadIdentity();												// Reset the 2D matrix.
	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 200.0);		// Configure the camera lens aperture.
	glMatrixMode(GL_MODELVIEW);										// Go to 3D mode.
	glViewport(0, 0, x, y);											// Configure the camera frame dimensions.
	display();
}

void changeAgent(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		activeAgent = 1;
		break;
	case '2':
		activeAgent = 2;
		break;
	case '3':
		activeAgent = 3;
		break;
	}
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);											// Init GLUT with command line parameters.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);		// Use 2 buffers (hidden and visible). Use the depth buffer. Use 3 color channels.
	glutInitWindowSize(750, 750);
	glutCreateWindow("CG first program");
	
	init();
	glutKeyboardFunc(changeAgent);
	glutReshapeFunc(reshape);										// Reshape CALLBACK function.
	glutDisplayFunc(display);										// Display CALLBACK function.
	glutIdleFunc(idle);												// Idle CALLBACK function.
	glutMainLoop();													// Begin graphics program.
	return 0;														// ANSI C requires a return value.
}
