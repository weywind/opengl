
#include <GL/glut.h>
#include <stdlib.h>
#include<iostream>
#include <gl/GLAUX.H>
#include "geometry.h"
#include "texture.h"

#include <windows.h>

double h = 0;
double r = 0;
double speed = 1;
GLfloat  corner = 0.0;
GLuint texName;
GLuint texName2;
GLuint texName3;
GLuint textureSun;

GLuint flag = 1;
GLUquadricObj* qobj;

const int objCount = 3;

GLuint texture[3] = { 1,2,3 };
void initText(const char** texturepaths)
{
	for (int i = 0; i < objCount; i++) {
		 generateTexture(texturepaths[i],&texture[i]);
	}
}
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); //背景黑色

	{
		GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //光源的位置在世界坐标系圆心，齐次坐标形式
		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //RGBA模式的环境光，为0
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //RGBA模式的漫反射光，全白光
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //RGBA模式下的镜面光 ，全白光
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

		//开启灯光
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清理颜色和深度缓存  
	glColor3f(1.0, 1.0, 1.0); //画笔白色

	glLoadIdentity();  //加载单位矩阵

	gluLookAt(0.0, h, 30, 0.0, h, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
		drawCircle(10, 50);
		drawCircle(15, 50);
		glPushMatrix();
			glRotatef(2 * r * speed, 0, 0, 1);
				{
					//GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //定义材质的环境光颜色，为0
					//GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //定义材质的漫反射光颜色，为0
					//GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色，为0
					//GLfloat sun_mat_emission[] = { 0.8f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射广颜色，为偏红色
					//GLfloat sun_mat_shininess = 0.0f;
					//glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
					//glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
					//glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
					//glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
					//glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);


				GLUquadricObj* quadricSun = drawSphereWithTexture(5, 50, texture[0]);

				
				}
		glPopMatrix();
		glPushMatrix();
			glRotatef(r * speed, 0, 0, 1);
			glTranslatef(10, 0, 0);
			{
				//GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 1.0f, 1.0f };  //定义材质的环境光颜色，骗蓝色
				//GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };  //定义材质的漫反射光颜色，偏蓝色
				//GLfloat earth_mat_specular[] = { 1.0f, 0.0f, 0.0f, 1.0f };   //定义材质的镜面反射光颜色，红色
				//GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //定义材质的辐射光颜色，为0
				//GLfloat earth_mat_shininess = 30.0f;
				//glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
				//glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
				//glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
				//glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
				//glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
				GLUquadricObj* quadricSun = drawSphereWithTexture(3, 50, texture[1]);

			}
		glPopMatrix();
		glPushMatrix();
			glRotatef(0.5*r*speed, 0, 0, 1);
			glTranslatef(0, 15, 0);
			glRotatef(-1 * r * speed, 0, 0, 1);

			GLUquadricObj* quadricSun = drawSphereWithTexture(2, 50, texture[2]);

		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void onKeyPress(unsigned char key, int x, int y) 
{
	switch (key)
	{
	case '+':
		speed += 0.1;
		glutPostRedisplay();
		break;
	case '-':
		speed -= 0.1;
		glutPostRedisplay();

		break;
	default:
		break;
	}
}
void onSpecialKeyPress(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		h += 0.1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		h -= 0.1;
		glutPostRedisplay();

		break;
	default:
		break;
	}
}
void timerProc(int v) {
	//h += 0.1;
	r ++;
	glutPostRedisplay();
	glutTimerFunc(10, timerProc, 10);
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 30);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA |GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(onSpecialKeyPress);
	glutKeyboardFunc(onKeyPress);
	glutTimerFunc(10,timerProc,10);
	//initTexture3();
	const char* texts[objCount] = {
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_sun.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_earth_daymap.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_jupiter.bmp"
	};
	initText(texts);
	glutMainLoop();
	return 0;
}
