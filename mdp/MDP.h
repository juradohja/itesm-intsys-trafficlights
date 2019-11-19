// Sergio Ugalde Marcano A01336435
// Alberto Jurado A01336656
// Kai Kawasaki Ueda A01336424
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
#include <limits>;
using namespace std;

#define BOARD_SIZE_X 17
#define BOARD_SIZE_Y 12

class MDP {
public:
	// Allowed moves:
	// 0 -> Stay
	// 1 -> Right
	// 2 -> UpRight
	// 3 -> up
	// 4 -> UpLeft
	// 5 -> Left
	// 6 -> DownLeft
	// 7 -> Down
	// 8 -> DownRight
	
	int optimalRules[BOARD_SIZE_X][BOARD_SIZE_Y] = {{}};
	int nextRules[BOARD_SIZE_X][BOARD_SIZE_Y] = {{}};

	float originalvalueGrid[BOARD_SIZE_X][BOARD_SIZE_Y] = {{}};
	float valueGrid[BOARD_SIZE_X][BOARD_SIZE_Y] = {{}};
	float nextValueGrid[BOARD_SIZE_X][BOARD_SIZE_Y] = {{}};

	float gamma;
    
	MDP(float rewards[][BOARD_SIZE_Y], float gammaValue);
	~MDP();

	bool didConverge();
	void doMDP();

};