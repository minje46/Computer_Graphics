#pragma warning(disable:4996)
#include "stdafx.h"			
#include<glut.h>			
#include<stdlib.h>			
#include<time.h>
#include<math.h>
#include<Windows.h>

// Lab 1 - 1 <Various viewpoint of teapot projection>
/*
int Width = 500, Height = 500;
void init() 
{
	glMatrixMode(GL_PROJECTION);	//glMatrix is porcess to choose which matrix is used in PIpeline.
	glLoadIdentity();		// Initialize the matrix which is using now.

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 5.0);
	glEnable(GL_DEPTH_TEST);
	
	//glMatrixMode(GL_MODELVIEW);	//glMatrix is porcess to choose which matrix is used in PIpeline.
	//glLoadIdentity();		// Initialize the matrix which is using now.
}

void display() 
{
	glColor3f(0.3, 0.3, 0.7);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Front of Teapot
	glViewport(0, 0, Width / 2, Height / 2);	// Adjust the area where something is showed.
	glPushMatrix();		// Push present matrix to stack.
	gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);		// Adjust view point of camera being able to see the whole of teaopt.
	glutWireTeapot(1.0);	// Draw a teapot.
	glPopMatrix();		// Pop present matrix from stack.
	
	// Side of Teapot
	glViewport(Width / 2, 0, Width / 2, Height / 2);	// (x,y)´Â view portÀÇ ¿ÞÂÊ ¾Æ·¡ÁÂÇ¥.
	glPushMatrix();
	gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glutWireTeapot(1.0);
	glPopMatrix();

	// Ceiling of Teapot
	glViewport(0, Height / 2, Width / 2, Height / 2);	//(width, height)´Â Æø°ú ³ôÀÌÁÂÇ¥.
	glPushMatrix();
	gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
	glutWireTeapot(1.0);
	glPopMatrix();
	
	// Another view point of Teapot
	glViewport(Width / 2, Height / 2, Width / 2, Height / 2);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(30, 1.0, 3.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glutWireTeapot(1.0);
	glPopMatrix();
	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Various viewpoint of teapot projection");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
*/

// Lab 1 - 2 <Move teapot>
#define PI 3.141592
int delay = 1;

GLfloat new_x[2], new_y[2], new_z[2];
GLfloat p1[3] = { 0, 0, 0 }, p2[3] = { 0, 0, 1 }, p3[2];		// Initialize coordinate		
GLfloat theta[2] = { 0, 0 }, axis = 1;

void init() 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.3, 0.3, 0.7);
	glFrustum(-1, 1, -1, 1, 1, 20);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
}

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(p1[0], p1[1], p1[2], p2[0], p2[1], axis* p2[2], 0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 0, 2);
	glutWireTeapot(0.5);
	glPopMatrix();
	glPushMatrix();

	glFlush();
}

void keyboard_handler(unsigned char keyboard, int x, int y) 
{
	if (keyboard == 'w') 
	{
		p1[0] += 0.01*sin((theta[0] * PI) / 180);
		p1[2] += 0.01*cos((theta[0] * PI) / 180);
		p2[0] += 0.01*sin((theta[0] * PI) / 180);
		p2[2] += 0.01*cos((theta[0] * PI) / 180);
	}

	if (keyboard == 'a') 
	{
		p1[0] += 0.01*sin(((theta[0] + 90) * PI) / 180);
		p1[2] += 0.01*cos(((theta[0] + 90)  * PI) / 180);
		p2[0] += 0.01*sin(((theta[0] + 90)  * PI) / 180);
		p2[2] += 0.01*cos(((theta[0] + 90)  * PI) / 180);
	}

	if (keyboard == 's') 
	{
		p1[0] -= 0.01*sin((theta[0] * PI) / 180);
		p1[2] -= 0.01*cos((theta[0] * PI) / 180);
		p2[0] -= 0.01*sin((theta[0] * PI) / 180);
		p2[2] -= 0.01*cos((theta[0] * PI) / 180);
	}

	if (keyboard == 'd') 
	{
		p1[0] -= 0.01*sin(((theta[0] + 90)  * PI) / 180);
		p1[2] -= 0.01*cos(((theta[0] + 90)  * PI) / 180);
		p2[0] -= 0.01*sin(((theta[0] + 90)  * PI) / 180);
		p2[2] -= 0.01*cos(((theta[0] + 90)  * PI) / 180);
	}
}

void mouse_handler(int keyboard, int state, int x, int y) 
{
	if (keyboard == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		new_x[0] = x;
		new_y[0] = y;
	}

	if (keyboard == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
		new_x[1] = x;
		new_y[1] = y;
	
		p3[0] = (new_x[0] - new_x[1]) / 500;
		p3[1] = (new_y[0] - new_y[1]) / 500;
		
		theta[0] += p3[0] * 30;
		theta[1] += p3[1] * 30;

		if (theta[0]>360) theta[0] -= 360;
		if (theta[1]>360) theta[1] -= 360;
		if (theta[0]<-360) theta[0] += 360;
		if (theta[1]<-360) theta[1] += 360;

		p2[0] = p1[0] + sin((theta[0] * PI) / 180);
		p2[1] = p1[1] + sin((theta[1] * PI) / 180);
		p2[2] = p1[2] + cos(((360 - theta[0]) * PI) / 180);
	}
}

void repeatition(int t)
{
	glutPostRedisplay();
	glutTimerFunc(delay, repeatition, t);
}

int main(int argc, char* argv[]) 
{
	void repeatition(int);
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Moving Teapot like FPS games ");
	glutTimerFunc(delay, repeatition, 0);
	glutKeyboardFunc(keyboard_handler);
	glutMouseFunc(mouse_handler);
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}