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
#include <random>
#include <fstream>
#include <iostream>

#include "Agent.h"
#include "Board.h"
#include "FuzzyLogic.h"


#define FRAMERATE 10 // cada cu�ntos frames se va a updatear
#define CYCLETIME 3 // cada cu�ntos segundos virtuales se llamar� el FL system
#define THRESHOLD 15 // threshold para tomar en cuenta densidad
#define LIGHTBASETIME 15 // tiempo base del sem�foro
#define MAXEXTENSION 40 // el sem�foro no puede estar activo m�s all� de este tiempo
#define YELLOWTIME 10 // tiempo que el sem�foro estar� en estado amarillo

class Environment {
public:

	Board board; // tama�o 100x100, revisar detalles en Board.h
	ofstream *log;
	// estados de sem�foro: 0 = rojo, 1 = amarillo, 2 = verde
	int lightNS;
	int lightWE;
	int frame; // contador de frames
	list<Agent *> cars;
	int ranInt;
	int ranInt2;
	float densN; // densidad north
	float densW; // densidad west
	float activeTime; // tiempo que lleva activo el sem�foro activo
	float timeLeft; // tiempo que le queda al sem�foro
    
    
	Environment();
	~Environment();
    
    bool touchDown(Agent* value);
	void draw();
	void update();
	void drawStreetGrid(); // se dibujan calles
	void changeLights(); // cambio de estado de sem�foros
	void checkState(); // llamada a sistema FL
	void spawnCar(); // crea y agrega a un coche
	void calculateTrafficDensities();

};
