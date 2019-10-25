#pragma once
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

#include <algorithm>;
#include <iostream>;
#include "NodeList.h";
#include "Node.h";
#include "Board.h";

using namespace std;

class Agent {
public:

	Board * board;

	Node * start;
	Node * goal;
	int size;

	float cn, cd;
	
	int curDirection;

	NodeList * openList;
	NodeList * closedList;
    
	Agent(Board * b, int st, int gl, int sz);
	~Agent();

	Node * aStar();
	Node * move(Board * b);
	NodeList * neighbors(Node * node);
	void updateDirection(Node * newSt);
	void draw();
	float diagonalDistance(Node * node);

};
