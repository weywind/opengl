#pragma once
#include <gl/glut.h>

void drawCircle(int radius, int slices);
GLUquadricObj* drawSphereWithTexture(int radius, int slices, GLuint textureName);
GLUquadricObj* drawSphere(int radius, int slices);

