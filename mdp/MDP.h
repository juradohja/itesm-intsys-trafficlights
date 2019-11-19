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

#define BOARD_SIZE 102
#define REAL_BOARD_SIZE 100

class MDP {
public:
	// Allowed moves:
	// 0 -> Stay
	// 1 -> Up
	// 2 -> UpRight
	// 3 -> Right
	// 4 -> DownRight
	// 5 -> Down
	// 6 -> DownLeft
	// 7 -> Left
	// 8 -> UpLeft
	
	int optimalRules[BOARD_SIZE][BOARD_SIZE] = {{}};
	int nextRules[BOARD_SIZE][BOARD_SIZE] = {{}};

	float originalvalueGrid[BOARD_SIZE][BOARD_SIZE] = {{}};
	float valueGrid[BOARD_SIZE][BOARD_SIZE] = {{}};
	float nextValueGrid[BOARD_SIZE][BOARD_SIZE] = {{}};

	float gamma;
    
	MDP(float rewards[][BOARD_SIZE], float gammaValue);
	~MDP();

	bool didConverge();
	void doMDP();

};