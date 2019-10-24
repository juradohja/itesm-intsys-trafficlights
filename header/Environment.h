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

#include <list>
#include <iterator>

#include "Agent.h"
#include "Board.h"

class Environment {
public:

	Board board; // tamaño 100x100, revisar detalles en Board.h
	// estados de semáforo: 0 = rojo, 1 = amarillo, 2 = verde
	int lightNS;
	int lightWE;
	int frameRate; // cada cuántos frames se va a updatear
	int frame; // contador de frames
	list<Agent> cars;

	Environment();
	~Environment();

	void draw();
	void update();
	void drawStreetGrid(); // se dibujan calles
	void changeLights(); // cambio de estado de semáforos
	void checkState(); // llamada a sistema FL
	void spawnCar();
};