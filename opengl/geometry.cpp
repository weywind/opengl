#include "geometry.h"
#include <cmath>
#define PI 3.1415926f
void drawCircle(GLfloat radius, int slices)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < slices; i++)
	{
		glVertex2f(radius * cos(2 * PI * i / slices), radius * sin(2 * PI * i / slices));   //定义顶点
	}
	glEnd();
}
GLUquadricObj* drawSphere(GLfloat radius, int slices)
{
	GLUquadricObj* qobj;// 创建一个二次曲面(二次曲面的创建GLUquadricObj* qobj;qobj = gluNewQuadric();)
	qobj = gluNewQuadric();
	gluSphere(qobj, radius, slices, slices);
	return qobj;
}
GLUquadricObj* drawDisk(GLfloat radius, int drawStyle, int slices, GLfloat width )
{

	GLUquadricObj* qobj;// 创建一个二次曲面(二次曲面的创建GLUquadricObj* qobj;qobj = gluNewQuadric();)
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, drawStyle);
	glDisable(GL_TEXTURE_2D);
	gluDisk(qobj, radius, radius + width, slices, slices);
	return qobj;
}
GLUquadricObj* drawDiskWithTexture(GLfloat radius, GLuint textureName, int drawStyle, GLfloat width, int slices)
{
	GLUquadricObj* qobj;// 创建一个二次曲面(二次曲面的创建GLUquadricObj* qobj;qobj = gluNewQuadric();)
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, drawStyle);
	glBindTexture(GL_TEXTURE_2D, textureName);
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(qobj, GL_TRUE);//纹理函数
	gluDisk(qobj, radius, radius + width, slices, slices);
	return qobj;
}
GLUquadricObj* drawSphereWithTexture(GLfloat radius, int slices, GLuint textureName,int drawStyle)
{
	GLUquadricObj* qobj;// 创建一个二次曲面(二次曲面的创建GLUquadricObj* qobj;qobj = gluNewQuadric();)

	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, drawStyle);
	glBindTexture(GL_TEXTURE_2D, textureName);
	glEnable(GL_TEXTURE_2D);
	gluQuadricTexture(qobj, GL_TRUE);//纹理函数
	gluSphere(qobj, radius, slices, slices);
	return qobj;
}
void drawRect(GLfloat width, GLfloat length) {
	glBegin(GL_POLYGON);
	glVertex2f(-width / 2, length / 2);
	glVertex2f(width / 2, length / 2);
	glVertex2f(width / 2, -length / 2);
	glVertex2f(-width / 2,- length / 2);
	glEnd();
}
void drawFlag() {
	glBegin(GL_QUADS);
	glVertex3f(-0.75, 0.5, 0.5);
	glVertex3f(0.75, 0.5, 0.5);
	glVertex3f(0.75, -0.5, 0.5);
	glVertex3f(-0.75, -0.5, 0.5);
	glEnd();
	//绘制星星
	glColor3f(1.0, 1.0, 0.0);
	GLfloat px[5] = { -1.5 / 3,-0.75 / 3,-0.75 / 5,-0.75 / 5,-0.75 / 3 };
	GLfloat py[5] = { 0.25,0.4,0.3,0.15,0.05 };
	GLfloat vx[5] = { -1.5 / 3 };
	GLfloat vy[5] = {0.4};
	//计算其余四星的顶点
	for (int i = 1; i < 5; i++) {
		vx[i] = px[i]-0.05*cos(atan((py[0] - py[i]) / (px[0] - px[i])));
		vy[i] = py[i]-0.05*sin(atan((py[0] - py[i]) / (px[0] - px[i])));
	}
	//绘制
	DrawStar(px[0], py[0], vx[0], vy[0], 0);
	DrawStar(px[1], py[1], vx[1], vy[1], 1);
	DrawStar(px[2], py[2], vx[2], vy[2], 1);
	DrawStar(px[3], py[3], vx[3], vy[3], 1);
	DrawStar(px[4], py[4], vx[4], vy[4], 1);

}
void DrawStar(GLfloat px, GLfloat py, GLfloat vx, GLfloat vy, int flag)
{
	glBegin(GL_TRIANGLE_FAN);//绘制一系列三角形
	GLfloat vtx[12], vty[12];
	vtx[0] = px;
	vty[0] = py;
	vtx[1] = vx;
	vty[1] = vy;
	GLfloat length1 = sqrt((px - vx) * (px - vx) + (py - vy) * (py - vy));
	GLfloat length2 = length1 * sin(0.1 * PI) / sin(126.0 / 180 * PI);
	//计算剩下的所有顶点
	double init = atan((vty[1] - vty[0]) / (vtx[1] - vtx[0]));
	if (flag)
		init = init - PI;
	for (int i = 2; i < 12; i++) {
		init = init - 0.2 * PI;
		if (i % 2 == 0) {//内顶点
			vtx[i] = length2 * cos(init) + vtx[0];
			vty[i] = length2 * sin(init) + vty[0];
		}
		else {//外顶点
			vtx[i] = length1 * cos(init) + vtx[0];
			vty[i] = length1 * sin(init) + vty[0];
		}
	}
	for (int i = 0; i < 12; i++) //设置顶点
		glVertex3f(vtx[i], vty[i], 0.5);
	glEnd();
}
