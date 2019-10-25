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

#define MIN_TRAFFIC_DEN 0.0f
#define MAX_TRAFFIC_DEN 4.0f
#define MIN_EXT -2.0f
#define MAX_EXT 2.0f

#define EXT_RM -2.0f
#define EXT_RL -1.0f
#define EXT_Z 0.0f
#define EXT_L 1.0f
#define EXT_M 2.0f

#include <array>
using namespace std;

array<float, 5> fuzzyfyData(float td);

array<float, 5> fuzzyfyRules(array<float, 5> tda, array<float, 5> tdna);

float defuzzyfy(array<float, 5> ext);

float fuzzyfy(float tda, float tdna);