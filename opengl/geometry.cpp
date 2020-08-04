#include "geometry.h"
#include <cmath>
#define PI 3.1415926f
void drawCircle(int radius, int slices)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < slices; i++)
	{
		glVertex2f(radius * cos(2 * PI * i / slices), radius * sin(2 * PI * i / slices));   //定义顶点
	}
	glEnd();
}

GLUquadricObj* drawSphere(int radius, int slices)
{
	GLUquadricObj* qobj;// 创建一个二次曲面(二次曲面的创建GLUquadricObj* qobj;qobj = gluNewQuadric();)
	qobj = gluNewQuadric();
	gluSphere(qobj, radius, slices, slices);
	return qobj;
}
GLUquadricObj* drawSphereWithTexture(int radius, int slices, GLuint textureName)
{
	GLUquadricObj* qobj;// 创建一个二次曲面(二次曲面的创建GLUquadricObj* qobj;qobj = gluNewQuadric();)

	qobj = gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, textureName);
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(qobj, GL_TRUE);//纹理函数
	gluSphere(qobj, radius, slices, slices);
	return qobj;
}
