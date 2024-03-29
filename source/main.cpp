/*
 * A01336424 | Kai Kawasaki Ueda
 * A01336435 | Sergio Ugalde Marcano
 * A01336656 | José Alberto Jurado Hernández
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

void displayText(int x, int y, vector<char> txt);

void printBoard() {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			printf("%d ", b.board[(i*100)+j]);
		}
		printf("\n");
	}
	printf("\n");
}

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
	printBoard();


   // printf("akjhfjk sdhfjkhdjsfhjkds hfklj dsah");
    myfile.open("log1.txt");
    env = Environment();
    myfile << "Please writr this text to a file.\n this text is written using C++\n";
    myfile << "Writing\n";
    env.log = &myfile;
  //  printf("akjhfjk sdhfjkhdjsfhjkds hfklj dsah");

}

void display()							// Called for each frame (about 60 times per second).
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);				// Clear color and depth buffers.
	glLoadIdentity();												// Reset 3D view matrix.
	gluLookAt(-30.0, 0.0, 140.0,										// Where the camera is.
		      -30.0, 0.0, 0.0,										// To where the camera points at.
		      0.0, 1.0, 0.0);										// "UP" vector.
    
    string remainingTime = " Remaining Semaphore Time: "+to_string(env.timeLeft);
    vector<char> vremainingTime(remainingTime.begin(), remainingTime.end());
    displayText(30,70, vremainingTime);
    
    string tda = " "+env.fuzzlogic.TDAarr;
    vector<char> vtda(tda.begin(), tda.end());
    displayText(30,90,vtda);
    
    string tdna = " "+env.fuzzlogic.TDNAarr;
    vector<char> vtdna(tdna.begin(), tdna.end());
    displayText(30,110,vtdna);
    
    string ext = " "+env.fuzzlogic.EXTarr;
    vector<char> vext(ext.begin(), ext.end());
    displayText(30,130,vext);
    
    string tdn = " #cars in N: "+to_string(env.carNumN)+" TDN: "+ to_string(env.densN);
    vector<char> vtdn(tdn.begin(), tdn.end());
    displayText(30,150,vtdn);
    
    string tde = " #cars in W: "+to_string(env.carNumW)+" TDW: "+ to_string(env.densW);
    vector<char> vtde(tde.begin(), tde.end());
    displayText(30,170,vtde);
    
    string tc = " Total car #: "+ to_string(env.cars.size());
    vector<char> vtc(tc.begin(), tc.end());
    displayText(30,190,vtc);
    
    string tis = " Iterations for MDP-SouthAsGoal: 350";
    vector<char> vtis(tis.begin(), tis.end());
    displayText(30,210,vtis);
    
    string tie = " Iterations for MDP-EastAsGoal: 332";
    vector<char> vtie(tie.begin(), tie.end());
    displayText(30,230,vtie);
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
	glutInitWindowSize(1300, 750);
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

void displayText( int x, int y, vector<char> txt )
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
            
            for(const char &c: txt )
            {
                glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, c );
                
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
