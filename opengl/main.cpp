
#include <GL/glut.h>
#include <stdlib.h>
#include<iostream>
#include <gl/GLAUX.H>
#include "geometry.h"
#include "texture.h"

#include <windows.h>
GLfloat h = 30;
GLfloat r = 0;
GLfloat speed = 0.5;
GLfloat  corner = 0.0;
GLuint texName;
GLuint texName2;
GLuint texName3;
GLuint textureSun;
GLfloat orbital_radius[8] = {6.5,9.5,13,16,22,30,40,50};
GLuint flag = 1;
GLUquadricObj* qobj;

GLfloat radius[9] = { 1.f,0.2f,0.3f,
0.4f,0.15f,0.7f,
0.65f,0.45f,0.48f };

const int objCount = 9;

GLuint texture[11] = { 1,2,3 ,4,5,6,7,8,9,10,11};

GLfloat revolutionPeriod[] = {
	90 / 365.0f,
	225 / 365.0f,
	1.0f,
	686 / 365.0f,
	12.0f,
	30.0f,
	84.0f,
	165.0f
};
GLfloat rotationPeriod[] = {
	25 / 365.0f,
	58/365.0f,
	243/365.9f,
	23.9/24/365.f,
	24.6/24/365.f,
	9.9/24/365.f,
	10.67/24/365.f,
	15.6/24/365.f,
	18.4/24/365.f
};
int drawStyle = GLU_FILL;
int currentStar = 0;

void initText(const char** texturepaths)
{
	for (int i = 0; i < 11; i++) {
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
void displaySingle() {
	glColor3f(1.0, 1.0, 1.0); //画笔白色
	glLoadIdentity();  //加载单位矩阵
	gluLookAt(0.0, -50, 50, 0.0, 0, 0.0, 0.0, 1.0, 0.0);

	if (currentStar == 7) {
		glRotatef(r * speed, 0, 0, 1);
		drawDiskWithTexture(25, texture[objCount+1],drawStyle,5,100);

	}
	else if(currentStar == 3)
	{
		glRotatef( r * speed, 0, 0, -1);
	}
	else if (currentStar == 4)
	{
		const GLdouble nodes[] = {
			0,0,
			0,5,
			5,5,
			5,0
		};

		glPushMatrix();
		//glTranslatef(0, 20,0);
		glLoadIdentity();
		glTranslatef(0, 20,-50);
		glDisable(GL_LIGHTING);
		glColor3f(1,0,0);
		//glRectf(-10, -7.5, 10, 7.5);
		glScaled(10, 10, 1);
		drawFlag();
		glEnable(GL_LIGHTING);
		glPopMatrix();
		glPushMatrix();
			glRotatef(r * speed/21, 0, 0, 1);
			glTranslatef(50, 0, 0);
			GLUquadricObj* quadricSun2 = drawSphereWithTexture(15.0/11.0*3.0f, 50, texture[objCount], drawStyle);
		glPopMatrix();
		glRotatef(r * speed, 0, 0, 1);
	}
	else if (currentStar == 8)
	{
		glRotatef(r * speed, 1, 0, 0);
	}
	else {
		glRotatef(r * speed, 0, 0, 1);
	}
	
	GLUquadricObj* quadricSun = drawSphereWithTexture(15, 50, texture[currentStar - 1], drawStyle);

	glutSwapBuffers();
}
void displayAll() {


	gluLookAt(0.0, -h, 50, 0.0, 0, 0.0, 0.0, 1.0, 0.0);

	glPushMatrix();
	for (int i = 1; i < 10; i++) {
		drawDisk(orbital_radius[i-1], drawStyle);
	}
	glPushMatrix();
	glRotatef(r * speed/rotationPeriod[0], 0, 0, 1);
	{
		GLUquadricObj* quadricSun = drawSphereWithTexture(radius[0] * 5, 50, texture[0], drawStyle);
	}
	glPopMatrix();

	for (int i = 0; i < 8; i++) {
		glPushMatrix();
		glRotatef(r * speed/revolutionPeriod[i], 0, 0, 1);
		glTranslatef(orbital_radius[i], 0, 0);
		{
			glPushMatrix();
			if (i == 1) {
				glRotated(-r * speed / rotationPeriod[i + 1], 0, 0, 1);
			}
			else if (i == 5) {
				drawDisk(radius[i] * 5 + 1.f, drawStyle, 100, 0.2);
				glRotated(r * speed / rotationPeriod[i + 1], 0, 0, 1);

			}
			else if (i == 6) {
				glRotated(r * speed / rotationPeriod[i + 1], 0, 1, 0);

			}
			else {
				glRotated(r * speed / rotationPeriod[i + 1], 0, 0, 1);

			}
			GLUquadricObj* quadricSun = drawSphereWithTexture(radius[i+1] * 5, 50, texture[i+1], drawStyle);
		}
		glPopMatrix();
	}
	/*glPushMatrix();
	glRotatef(r * speed*, 0, 0, 1);
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
		glRotatef(r * speed, 0, 0, 1);
		GLUquadricObj* quadricSun = drawSphereWithTexture(radius[5] * 5, 50, texture[5], drawStyle);
	}
	glPopMatrix();
	glPushMatrix();
	glRotatef(r * speed, 0, 0, 1);
	glTranslatef(orbital_radius[5], 0, 0);
	{
		GLUquadricObj* quadricSun = drawSphereWithTexture(radius[6] * 5, 50, texture[6], drawStyle);
		drawDisk(radius[6] * 5 + 1, drawStyle, 100, 0.2);

	}
	glPopMatrix();

	glPushMatrix();
	glRotatef(r * speed, 0, 0, 1);
	glTranslatef(orbital_radius[6], 0, 0);
	{
		GLUquadricObj* quadricSun = drawSphereWithTexture(radius[7] * 5, 50, texture[7], drawStyle);
	}
	glPopMatrix();*/
	//glPushMatrix();
	//glRotatef(0.5 * r * speed, 0, 0, 1);
	//glTranslatef(0, orbital_radius[7], 0);
	//glRotatef(-1 * r * speed, 0, 0, 1);
	//GLUquadricObj* quadricSun = drawSphereWithTexture(radius[8] * 5, 50, texture[8], drawStyle);

	//glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清理颜色和深度缓存  
	glColor3f(1.0, 1.0, 1.0); //画笔白色
	glLoadIdentity();  //加载单位矩阵
	if (currentStar != 0) {
		displaySingle();
	}
	else {
		displayAll();
	}
	
}

void onKeyPress(unsigned char key, int x, int y) 
{
	switch (key)
	{
	case '+':
		speed += 0.1f;
		glutPostRedisplay();
		break;
	case '-':
		speed -= 0.1f;
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
		h += 1.f;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		h -= 1.f;
		glutPostRedisplay();

		break;
	case 1:
		speed/=2.f;
		break;
	case 2:
		speed*=2.f;
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
	std::cout << selectedOption;
	//switch (selectedOption)
	//{
	//case 1:
	//	drawStyle = GLU_FILL;//同色填充
	//	break;
	//case 2:
	//	drawStyle = GLU_LINE;//顶点颜色插值
	//	break;
	//default:
	//	break;
	//}
	//glutPostRedisplay();//消息响应后必须被重绘
}
void handleLine(int selected) {
	drawStyle = GLU_LINE;
	currentStar = selected;
	glutPostRedisplay();//消息响应后必须被重绘
}
void handleFill(int selected) {
	drawStyle = GLU_FILL;
	currentStar = selected;
	glutPostRedisplay();//消息响应后必须被重绘
}
void handleSpeed(int selected) {
	switch (selected)
	{
	case 0:
		speed *= 2;
		break;
	case 1:
		speed /= 2;
		break;
	default:
		break;
	}
	glutPostRedisplay();//消息响应后必须被重绘
}
void attachMenu() {

	GLint fillMenu = glutCreateMenu(handleFill);
	glutAddMenuEntry("all", 0);
	glutAddMenuEntry("sun", 1);
	glutAddMenuEntry("mercury", 2);
	glutAddMenuEntry("venus", 3);
	glutAddMenuEntry("earth", 4);
	glutAddMenuEntry("mars", 5);
	glutAddMenuEntry("jupiter", 6);
	glutAddMenuEntry("saturn", 7);
	glutAddMenuEntry("uranus", 8);
	glutAddMenuEntry("neptune", 9);
	GLint lineMenu = glutCreateMenu(handleLine);
	glutAddMenuEntry("all", 0);
	glutAddMenuEntry("sun", 1);
	glutAddMenuEntry("mercury", 2);
	glutAddMenuEntry("venus", 3);
	glutAddMenuEntry("earth", 4);
	glutAddMenuEntry("mars", 5);
	glutAddMenuEntry("jupiter", 6);
	glutAddMenuEntry("saturn", 7);
	glutAddMenuEntry("uranus", 8);
	glutAddMenuEntry("neptune", 9);
	GLint speedMenu = glutCreateMenu(handleSpeed);
	glutAddMenuEntry("speed up", 0);
	glutAddMenuEntry("speed down", 1);

	GLint menu = glutCreateMenu(fillOption);
	glutAddSubMenu("Fill", fillMenu);
	glutAddSubMenu("Line", lineMenu);
	glutAddSubMenu("Speed", speedMenu);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
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
	const char* texts[objCount+2] = {
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_sun.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_mercury.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_venus_surface.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_earth_daymap.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_mars.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_jupiter.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_saturn.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\2k_uranus.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\2k_neptune.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_moon.bmp",
		"C:\\Users\\weywi\\Desktop\\texture_bmp\\8k_saturn_ring_alpha.bmp"
	};
	initText(texts);

	//glutCreateSubWindow(mainWindow, 100, 100, 100, 100);
	//glutDisplayFunc(display);
	//glutCreateMenu(fillOption);//创建菜单并绑定回调函数
	//glutAddMenuEntry("fill", 1);//第一个菜单项
	//glutAddMenuEntry("line", 2);//第二个菜单
	//glutAttachMenu(GLUT_RIGHT_BUTTON);//指定鼠标右键来弹出菜单项
	attachMenu();
	glutMainLoop();
	return 0;
}
