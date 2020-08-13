#pragma once
#include <gl/glut.h>

void drawCircle(GLfloat radius, int slices);
GLUquadricObj* drawSphereWithTexture(GLfloat radius, int slices, GLuint textureName,int drawStyle);
GLUquadricObj* drawSphere(GLfloat radius, int slices);
GLUquadricObj* drawDisk(GLfloat radius, int drawStyle,int slices = 100, GLfloat width=0.2);
GLUquadricObj* drawDiskWithTexture(GLfloat radius, GLuint textureName, int drawStyle, GLfloat width , int slices = 100);