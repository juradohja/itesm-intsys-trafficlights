/*
 * A01336424 | Kai Kawasaki Ueda
 * A01336435 | Sergio Ugalde Marcano
 * A01336656 | Jos� Alberto Jurado Hern�ndez
 *
 * TC2011. Intelligent Systems Course.
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
#include <fstream>
#include <iostream>
#include "Board.h"
#include "Agent.h"
#include "Environment.h"
#include <string>

using namespace std;

ofstream myfile;


Board b;
Agent * red, * green, * blue;
Node * redList, *greenList, *blueList;
Environment env;
int activeAgent;

long frames;
long times;
long timebase;
float fps;
char bufferFPS[11];

void displayText(int x, int y, char* txt);

void printBoard() {
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			printf("%d ", b.board[(i*50)+j]);
		}
		printf("\n");
	}
	printf("\n");
}
/*
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
*/
void init() // FOR GLUT LOOP
{
	glEnable(GL_DEPTH_TEST);			// Enable check for close and far objects.
	glClearColor(0.0, 0.0, 0.0, 0.0);	// Clear the color state.
	glMatrixMode(GL_MODELVIEW);			// Go to 3D mode.
	glLoadIdentity();					// Reset 3D view matrix.
    frames = 0;
    times = 0;
    timebase = 0;
    fps = 0.0f;
    
	b = Board();
	// printBoard();


    printf("akjhfjk sdhfjkhdjsfhjkds hfklj dsah");
    myfile.open("log1.txt");
    env = Environment();
    myfile << "Please writr this text to a file.\n this text is written using C++\n";
    myfile << "Writing\n";
    env.log = &myfile;
    printf("akjhfjk sdhfjkhdjsfhjkds hfklj dsah");
    
    /*
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
     */

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
    displayText(30,50,bufferFPS);
    
    string remainingTime = " Remaining Semaphore Time: "+to_string(env.timeLeft);
    int num1 = remainingTime.size()+1;
    char remainingTimeChar[num1];
    remainingTime.copy(remainingTimeChar, remainingTime.size()+1);
    remainingTimeChar[remainingTime.size()] = '\0';
    displayText(30,70, remainingTimeChar);
    
    string tda = env.fuzzlogic.TDAarr;
    int num2 = tda.size()+1;
    char tdaChar[num2];
    tda.copy(tdaChar,tda.size()+1);
    tdaChar[tda.size()] = '\0';
    displayText(30,90,tdaChar);
    
    string tdna = env.fuzzlogic.TDNAarr;
    int num3 = tdna.size()+1;
    char tdnaChar[num3];
    tdna.copy(tdnaChar,tdna.size()+1);
    tdnaChar[tdna.size()] = '\0';
    displayText(30,110,tdnaChar);
    
    string ext = env.fuzzlogic.EXTarr;
    int num4 = ext.size()+1;
    char extChar[num4];
    ext.copy(extChar,ext.size()+1);
    extChar[ext.size()] = '\0';
    displayText(30,130,extChar);
    
    string tdn = " #cars in N: "+to_string(env.carNumN)+" TDN: "+ to_string(env.densN);
    int num5 = tdn.size()+1;
    char tdnChar[num5];
    tdn.copy(tdnChar,tdn.size()+1);
    tdnChar[tdn.size()] = '\0';
    displayText(30,150,tdnChar);
    
    string tde = " #cars in W: "+to_string(env.carNumW)+" TDW: "+ to_string(env.densW);
    int num6 = tde.size()+1;
    char tdeChar[num6];
    tde.copy(tdeChar,tde.size()+1);
    tdeChar[tde.size()] = '\0';
    displayText(30,170,tdeChar);
    
    string tc = " Total car #: "+ to_string(env.cars.size());
    int num7 = tc.size()+1;
    char tcChar[num7];
    tc.copy(tcChar,tc.size()+1);
    tcChar[tc.size()] = '\0';
    displayText(30,190,tcChar);
    displayText(30,210," Iterations for MDP-SouthAsGoal: 350");
    displayText(30,230," Iterations for MDP-EastAsGoal: 332");
	env.draw();
	glutSwapBuffers();												// Swap the hidden and visible buffers.
}

void idle()															// Called when drawing is finished.
{
    frames++;
    times = glutGet( GLUT_ELAPSED_TIME );
    if( times - timebase > 1000 )
    {
        fps = frames * 1000.0f / (times - timebase);
        sprintf( bufferFPS, "FPS:%4.2f\n", fps);
        timebase = times;
        frames = 0;
    }
	env.update();
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
    myfile.close();
	return 0;														// ANSI C requires a return value.
}

void displayText( int x, int y, char* txt )
{
    GLboolean lighting;
    GLint viewportCoords[4];
    glColor3f( 0.0, 1.0, 0.0 );
    glGetBooleanv( GL_LIGHTING, &lighting       );
    glGetIntegerv( GL_VIEWPORT, viewportCoords );
    if( lighting )
    {
        glDisable( GL_LIGHTING );
    }
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
        glLoadIdentity();
        gluOrtho2D( 0.0, viewportCoords[2], 0.0, viewportCoords[3] );
        glMatrixMode( GL_MODELVIEW );
        glPushMatrix();
            glLoadIdentity();
            glRasterPos2i( x, viewportCoords[3] - y );
            while( *txt )
            {
                glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *txt );
                txt++;
            }
        glPopMatrix();
        glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );

    if( lighting )
    {
        glEnable( GL_LIGHTING );
    }
}
