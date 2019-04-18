#pragma warning(disable:4996)
#include "stdafx.h"			
#include<glut.h>			
#include<stdlib.h>			
#include<time.h>
#include<math.h>
#include<Windows.h>

// Prog 14.
/*
#define PI 3.141592
#define Radian PI / 180

GLfloat vertices[][3] = { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 },
{ -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } };

GLfloat colors[][3] = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },
{ 0.0, 0.0, 1.0 }, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 } };

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	glClear(GL_DEPTH_TEST);
}

void polygon(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glVertex3fv(vertices[a]);
	glColor3fv(colors[b]);
	glVertex3fv(vertices[b]);
	glColor3fv(colors[c]);
	glVertex3fv(vertices[c]);
	glColor3fv(colors[d]);
	glVertex3fv(vertices[d]);

	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(0, 4, 7, 3);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(0, 1, 5, 4);
	
	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog14: Color cube");
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}
*/

// Prog 15.
/*
static GLfloat theta = 0.0;
GLfloat vertices[][3] = { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 },
{ -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } };

GLfloat colors[][3] = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },
{ 0.0, 0.0, 1.0 }, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 } };

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
}

void polygon(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glVertex3fv(vertices[a]);
	glColor3fv(colors[b]);
	glVertex3fv(vertices[b]);
	glColor3fv(colors[c]);
	glVertex3fv(vertices[c]);
	glColor3fv(colors[d]);
	glVertex3fv(vertices[d]);

	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glRotatef(theta, 0.0, 1.0, 0.0);		//y축으로 회전.
	
	// theta 값에 의해서 변형이 된 것이기에.. 밑의 좌표들은 변형되었다.
	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(0, 4, 7, 3);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(0, 1, 5, 4);

	glFlush();
}

void spin_cube()
{
	theta += 0.5;

	if (theta > 360.0)
		theta -= 360.0;
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog15: color cube w Transformation");
	glutIdleFunc(spin_cube);
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}
*/

// Prog 16.
/*
static GLfloat theta = 0.0;
GLfloat vertices[][3] = { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 },
{ -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } };

GLfloat colors[][3] = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },
{ 0.0, 0.0, 1.0 }, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 } };

void init()
{
	Sleep(1000);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glRotatef(theta, 0.0, 1.0, 0.0);		//y축으로 회전.

	GLubyte indices[] = { 0, 3, 2, 1, 2, 3, 7, 6, 0, 4, 7, 3, 1, 2, 6, 5, 4, 5, 6, 7, 0, 1, 5, 4 };

	for (int i = 0; i < 6; i++)
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &indices[4 * i]);

	glFlush();
	glutSwapBuffers();
}

void spin_cube()
{
	theta += 2.0;

	if (theta > 360.0)
		theta -= 360.0;
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog16: Smooth rendering");
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);		//3개씩 읽어야한다(x,y,z)
	glColorPointer(3, GL_FLOAT, 0, colors);			// 자료형은 float
	glutIdleFunc(spin_cube);
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}
*/

// Prog 17.
/*
static GLfloat theta = 0.0;
static GLfloat scale = 0.5;
int axis = 1;
GLfloat vertices[][3] = { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 },
{ -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } };

GLfloat colors[][3] = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },
{ 0.0, 0.0, 1.0 }, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 } };

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glScalef(scale, scale, scale);

	if (axis == 0)
		glRotatef(theta, 0.0, 1.0, 0.0);
	else if (axis == 1)
		glRotatef(theta, 0.0, 0.0, 1.0);
	else if (axis == 2)
		glRotatef(theta, 1.0, 0.0, 0.0);

	GLubyte indices[] = { 0, 3, 2, 1, 2, 3, 7, 6, 0, 4, 7, 3, 1, 2, 6, 5, 4, 5, 6, 7, 0, 1, 5, 4 };

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);

	glFlush();
	glutSwapBuffers();
}

void spin_cube()
{
	theta += 0.08;

	if (theta > 360.0)
		theta -= 360.0;
	glutPostRedisplay();
}

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'u')
		scale += 0.01;
	if (key == 'd')
		scale -= 0.01;

	if (scale < 0.1)
		scale = 0.1;
	if (scale > 1.4)
		scale = 1.4;
}

void mouse_handler(int btn, int state, int x, int y)
{
	if (btn = GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		axis = 0;
	if (btn = GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		axis = 1;
	if (btn = GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		axis = 2;
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog17: Interactivity");
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);		//3개씩 읽어야한다(x,y,z)
	glColorPointer(3, GL_FLOAT, 0, colors);			// 자료형은 float
	glutIdleFunc(spin_cube);
	glutKeyboardFunc(keyboard_handler);
	glutMouseFunc(mouse_handler);
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}
*/

// Prog 19.
/*
static GLfloat theta = 0.0;
static GLfloat scale = 0.5;
int axis = 1;
GLfloat vertices[][3] = { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 },
{ -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } };
GLfloat colors[][3] = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },
{ 0.0, 0.0, 1.0 }, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 } };
double axis_x = 1.0, axis_y = 1.0, axis_z = 1.0;

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(axis_x, axis_y, axis_z, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0); // change to model view

	if (axis == 0)
		glRotatef(theta, 0.0, 1.0, 0.0);
	else if (axis == 1)
		glRotatef(theta, 0.0, 0.0, 1.0);
	else if (axis == 2)
		glRotatef(theta, 1.0, 0.0, 0.0);

	GLubyte indices[] = { 0, 3, 2, 1, 2, 3, 7, 6, 0, 4, 7, 3, 1, 2, 6, 5, 4, 5, 6, 7, 0, 1, 5, 4 };
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'x') axis_x = axis_x - 0.1;
	if (key == 'X') axis_x = axis_x + 0.1;
	if (key == 'y') axis_y = axis_y - 0.1;
	if (key == 'Y') axis_y = axis_y + 0.1;
	if (key == 'z') axis_z = axis_z - 0.1;
	if (key == 'Z') axis_z = axis_z + 0.1;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog19: Moving Camera");
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);		//3개씩 읽어야한다(x,y,z)
	glColorPointer(3, GL_FLOAT, 0, colors);			// 자료형은 float
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}
*/

// Prog 20.
static GLfloat theta = 0.0;
static GLfloat scale = 0.5;
int axis = 1;
GLfloat vertices[][3] = { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 },
{ -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } };
GLfloat colors[][3] = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },
{ 0.0, 0.0, 1.0 }, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 } };
double axis_x = 3.0, axis_y = 3.0, axis_z = 3.0;
int camera = 0;
float fact;

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	//glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
//	glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 20.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (camera % 2 == 0){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
		glMatrixMode(GL_MODELVIEW);
		fact = 1.0;
	}
	else if (camera % 2 == 1){
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//glFrustum( -2.0, 2.0, -2.0, 2.0, 2.0, 20.0 );
		gluPerspective(85.0, 1.0, 2.0, 20.0);
		glMatrixMode(GL_MODELVIEW);
		fact = 2.0;
	}
	glLoadIdentity();
	gluLookAt(axis_x, axis_y, axis_z, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0); // change to model view

	if (axis == 0)
		glRotatef(theta, 0.0, 1.0, 0.0);
	else if (axis == 1)
		glRotatef(theta, 0.0, 0.0, 1.0);
	else if (axis == 2)
		glRotatef(theta, 1.0, 0.0, 0.0);

	GLubyte indices[] = { 0, 3, 2, 1, 2, 3, 7, 6, 0, 4, 7, 3, 1, 2, 6, 5, 4, 5, 6, 7, 0, 1, 5, 4 };
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);

	glFlush();
	glutSwapBuffers();
}

void spin_cube()
{
	theta += 0.08;

	if (theta > 360.0)
		theta -= 360.0;
	glutPostRedisplay();
}

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'x') axis_x = axis_x - 0.1;
	if (key == 'X') axis_x = axis_x + 0.1;
	if (key == 'y') axis_y = axis_y - 0.1;
	if (key == 'Y') axis_y = axis_y + 0.1;
	if (key == 'z') axis_z = axis_z - 0.1;
	if (key == 'Z') axis_z = axis_z + 0.1;
	if (key == 'p') camera += 1;
	if (scale < 0.1) scale = 0.1;
	if (scale > 1.4) scale = 1.4;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog20: Perspective projection");
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);		//3개씩 읽어야한다(x,y,z)
	glColorPointer(3, GL_FLOAT, 0, colors);			// 자료형은 float
	glutIdleFunc(spin_cube);
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}
