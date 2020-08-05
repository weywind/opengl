
#include <GL/glut.h>
#include <stdlib.h>
#include<iostream>
#include <gl/GLAUX.H>
#include "geometry.h"
#include "texture.h"

#include <windows.h>
double h = 0;
double r = 0;
double speed = 0.5;
GLfloat  corner = 0.0;
GLuint texName;
GLuint texName2;
GLuint texName3;
GLuint textureSun;
double orbital_radius[8] = {6.5,9.5,13,16,22,30,40,50};
GLuint flag = 1;
GLUquadricObj* qobj;

GLfloat radius[9] = { 1,0.2,0.3,
0.4,0.15,0.7,
0.65,0.45,0.48 };

const int objCount = 9;

GLuint texture[9] = { 1,2,3 ,4,5,6,7,8,9};

int drawStyle = GLU_FILL;
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

	gluLookAt(0.0, -h, 50, 0.0, 0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
		//drawCircle(10, 50);
		//drawCircle(15, 50);
		for (int i = 0; i < 10; i++) {
			drawDisk(orbital_radius[i]);
		}
		glPushMatrix();
			glRotatef(2 * r * speed, 0, 0, 1);
				{
					GLUquadricObj* quadricSun = drawSphereWithTexture(radius[0] * 5, 50, texture[0], drawStyle);
					std::cout << radius[0] * 5;
				}
		glPopMatrix();
		glPushMatrix();
			glRotatef(r * speed, 0, 0, 1);
			glTranslatef(orbital_radius[0], 0, 0);
			{
				GLUquadricObj* quadricSun = drawSphereWithTexture(radius[1] * 5, 50, texture[1], drawStyle);
			}
		glPopMatrix();
		glPushMatrix();
		glRotatef(r * speed, 0, 0, 1);

		glTranslatef(orbital_radius[1], 0, 0);
		{
			GLUquadricObj* quadricSun = drawSphereWithTexture(radius[2] * 5, 50, texture[2], drawStyle);
		}
		glPopMatrix();


		glPushMatrix();
		glRotatef(r * speed, 0, 0, 1);
		glTranslatef(orbital_radius[2], 0, 0);
		{
			GLUquadricObj* quadricSun = drawSphereWithTexture(radius[3] * 5, 50, texture[3], drawStyle);
		}
		glPopMatrix();

		glPushMatrix();
		glRotatef(r * speed, 0, 0, 1);
		glTranslatef(orbital_radius[3], 0, 0);
		{
			GLUquadricObj* quadricSun = drawSphereWithTexture(radius[4] * 5, 50, texture[4], drawStyle);
		}
		glPopMatrix();
		glPushMatrix();
		glRotatef(r * speed, 0, 0, 1);
		glTranslatef(orbital_radius[4], 0, 0);
		{
			GLUquadricObj* quadricSun = drawSphereWithTexture(radius[5] * 5, 50, texture[5], drawStyle);
		}
		glPopMatrix();
		glPushMatrix();
		glRotatef(r * speed, 0, 0, 1);
		glTranslatef(orbital_radius[5], 0, 0);
		{
			GLUquadricObj* quadricSun = drawSphereWithTexture(radius[6] * 5, 50, texture[6], drawStyle);
			drawDisk(radius[6] * 5 + 1, 100, 0.2);

		}
		glPopMatrix();

		glPushMatrix();
		glRotatef(r * speed, 0, 0, 1);
		glTranslatef(orbital_radius[6], 0, 0);
		{
			GLUquadricObj* quadricSun = drawSphereWithTexture(radius[7] * 5, 50, texture[7], drawStyle);
		}
		glPopMatrix();
		glPushMatrix();
			glRotatef(0.5*r*speed, 0, 0, 1);
			glTranslatef(0, orbital_radius[7], 0);
			glRotatef(-1 * r * speed, 0, 0, 1);
			GLUquadricObj* quadricSun = drawSphereWithTexture(radius[8] * 5, 50, texture[8], drawStyle);

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
		h += 1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		h -= 1;
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
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 150);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void fillOption(GLint selectedOption)//菜单消息响应函数
{
	switch (selectedOption)
	{
	case 1:
		drawStyle = GLU_FILL;//同色填充
		break;
	case 2:
		drawStyle = GLU_LINE;//顶点颜色插值
		break;
	default:
		break;
	}
	glutPostRedisplay();//消息响应后必须被重绘
}
void OnContextMenu(HWND hWnd, LPARAM lParam)
{
	HMENU hPopup = CreatePopupMenu();
	static int flag = 0;

	AppendMenu(hPopup, MF_STRING | (flag ? MF_CHECKED : 0), 1001, "选择");
	AppendMenu(hPopup, MF_SEPARATOR, 0, "");
	AppendMenu(hPopup, MF_STRING, 1002, "右键2");

	switch (TrackPopupMenu(hPopup, TPM_RETURNCMD, LOWORD(lParam), HIWORD(lParam), 0, hWnd, NULL))
	{
	case 1001:
		flag = !flag;
		break;
	case 1002:
		MessageBox(hWnd, "右键2", "信息", MB_OK);
		break;

	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("123");
	glutDisplayFunc(display);
	init();
	glutReshapeFunc(reshape);
	glutSpecialFunc(onSpecialKeyPress);
	glutKeyboardFunc(onKeyPress);
	glutTimerFunc(10,timerProc,10);
	//initTexture3();
	const char* texts[objCount] = {
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_sun.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_mercury.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_venus_surface.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_earth_daymap.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_mars.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_jupiter.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_saturn.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\2k_uranus.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\2k_neptune.bmp"
	};
	initText(texts);

	//glutCreateSubWindow(mainWindow, 100, 100, 100, 100);
	//glutDisplayFunc(display);
	glutCreateMenu(fillOption);//创建菜单并绑定回调函数
	glutAddMenuEntry("fill", 1);//第一个菜单项
	glutAddMenuEntry("line", 2);//第二个菜单
	glutAttachMenu(GLUT_RIGHT_BUTTON);//指定鼠标右键来弹出菜单项

	glutMainLoop();
	return 0;
}
