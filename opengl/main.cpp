
#include <GL/glut.h>
#include <stdlib.h>
#include<iostream>
#include "geometry.h"
double h = 0;
double r = 0;
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); //������ɫ

	{
		GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //��Դ��λ������������ϵԲ�ģ����������ʽ
		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //RGBAģʽ�Ļ����⣬Ϊ0
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //RGBAģʽ��������⣬ȫ�׹�
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //RGBAģʽ�µľ���� ��ȫ�׹�
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

		//�����ƹ�
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //������ɫ����Ȼ���  
	glColor3f(1.0, 1.0, 1.0); //���ʰ�ɫ

	glLoadIdentity();  //���ص�λ����

	gluLookAt(0.0, h, 30, 0.0, h, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
		drawCircle(10, 50);
		drawCircle(15, 50);
		glPushMatrix();
			glRotatef(2 * r, 0, 0, 1);
				{
					GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //������ʵĻ�������ɫ��Ϊ0
					GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //������ʵ����������ɫ��Ϊ0
					GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //������ʵľ��淴�����ɫ��Ϊ0
					GLfloat sun_mat_emission[] = { 0.8f, 0.0f, 0.0f, 1.0f };   //������ʵķ������ɫ��Ϊƫ��ɫ
					GLfloat sun_mat_shininess = 0.0f;
					glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
					glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
					glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
					glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
					glutWireSphere(5, 20, 20);
				}
		glPopMatrix();
		glPushMatrix();
			glRotatef(r, 0, 0, 1);
			glTranslatef(10, 0, 0);
			{
				GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 1.0f, 1.0f };  //������ʵĻ�������ɫ��ƭ��ɫ
				GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };  //������ʵ����������ɫ��ƫ��ɫ
				GLfloat earth_mat_specular[] = { 1.0f, 0.0f, 0.0f, 1.0f };   //������ʵľ��淴�����ɫ����ɫ
				GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   //������ʵķ������ɫ��Ϊ0
				GLfloat earth_mat_shininess = 30.0f;
				glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
				glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
				glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
				glutSolidSphere(1, 20, 20);

			}
		glPopMatrix();
		glPushMatrix();
			glRotatef(0.5*r, 0, 0, 1);
			glTranslatef(0, 15, 0);
			glRotatef(-1 * r, 0, 0, 1);

			glutWireSphere(2, 20, 20);
		glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void onKeyPress(int key, int x, int y) 
{
	switch (key)
	{
	case GLUT_KEY_UP:
		h+=0.1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		h-=0.1;
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
	glutSpecialFunc(onKeyPress);
	glutTimerFunc(10,timerProc,10);
	glutMainLoop();
	return 0;
}