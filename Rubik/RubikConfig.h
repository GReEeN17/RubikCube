#ifndef RUBIKCUBE_RUBIKCONFIG_H
#define RUBIKCUBE_RUBIKCONFIG_H

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <OpenGL/OpenGL.h>
#include <GLUT//glut.h>
#include <fstream>
#define GLEW_STATIC
using namespace std;

ifstream inputStream("/Users/azelen/Desktop/Уник/2 семестр/RubikCube/input.txt");
ofstream outputStream("/Users/azelen/Desktop/Уник/2 семестр/RubikCube/output.txt");

enum Colors {
    yellow = 0xFFFF00,
    white = 0xFFFFFF,
    blue = 0x0000FF,
    green = 0x00FF00,
    orange = 0xFF6600,
    red = 0xFF0000,
};

const int ROTATE_SPEED_STEP = 10, ROTATE_START_VALUE = 30;
GLfloat CUBE_SIZE = 12;

// Projection of the angle of rotation  on the axis
int xRot = 25, yRot = -45;

// Translation by Z axis
GLfloat translateZ = -35;

#endif //RUBIKCUBE_RUBIKCONFIG_H
