#pragma warning(disable:4996)
#include "stdafx.h"			
#include<glut.h>			
#include<stdlib.h>			
#include<time.h>
#include<math.h>
#include<Windows.h>

// Solar System.

static int delay = 1;
static float Day = 0, timeEarth = 0, dayMoon = 0;

void init()
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();

glClearColor(0.0, 0.0, 0.0, 0.0);
//glClearColor(1.0, 1.0, 1.0, 1.0);
glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
glEnable(GL_DEPTH_TEST);

glMatrixMode(GL_MODELVIEW);
}

void display()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glLoadIdentity();

glColor3f(1.0, 0.3, 0.3);
glutWireSphere(0.2, 20, 16);

glPushMatrix();
glRotatef((GLfloat)Day, 0.0, 1.0, 0.0); // 지구 공전
glTranslatef(0.7, 0.0, 0.0);

glPushMatrix();
glRotatef((GLfloat)timeEarth, 0.0, 1.0, 0.0); // 지구 자전
glRotatef((GLfloat)23.44, 23.44, 23.44, 0.0); // 자전축 기울이기(안됨)
glColor3f(0.5, 0.6, 0.7);
glutWireSphere(0.1, 10, 8);
glPopMatrix();

glPushMatrix();
glRotatef((GLfloat)dayMoon, 0.0, 1.0, 0.0); // 달 공전
glTranslatef(0.2, 0.0, 0.0);
glColor3f(0.9, 0.8, 0.2);
glutWireSphere(0.04, 10, 8);
glPopMatrix();
glPopMatrix();

dayMoon = dayMoon + (360.0 / (27.3 * 24.0));
timeEarth = timeEarth + (360.0 / 24.0);
Day = Day + (360.0 / (365.0 * 24.0));

glutSwapBuffers();
}

void timer(int t)
{
glutPostRedisplay();
glutTimerFunc(delay, timer, t);
}

int main(int argc, char* argv[])
{
glutInit(&argc, (char**)argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(500, 500);
glutCreateWindow("Solar system");
glutDisplayFunc(display);
glutTimerFunc(delay, timer, 0);

init();
glutMainLoop();
return 0;
}


/*
static int Day = 0, Time = 0;



void MyDisplay()

{

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();



	//태양

	glColor3f(1.0, 0.3, 0.3);

	glutWireSphere(0.2, 20, 16);



	//행렬스택이용

	//옆에서는 보는 경우(Y축 회전)

	glPushMatrix();

	//지구

	glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);

	glTranslatef(0.7, 0.0, 0.0);

	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);

	//달

	glColor3f(0.5, 0.6, 0.7);

	glutWireSphere(0.1, 10, 8);

	glPushMatrix();

	glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);

	glTranslatef(0.2, 0.0, 0.0);

	glColor3f(0.9, 0.8, 0.2);

	glutWireSphere(0.04, 10, 8);

	glPopMatrix();

	glPopMatrix();



	//옆에서는 보는 경우(Z축 회전)

	//glPushMatrix();

	// //지구

	// glRotatef((GLfloat) Day, 0.0, 0.0, 1.0);

	// glTranslatef(0.7, 0.0, 0.0);

	// glRotatef((GLfloat) Time, 0.0, 0.0, 1.0);

	// //달

	// glColor3f(0.5, 0.6, 0.7);

	// glutWireSphere(0.1, 10, 8);

	// glPushMatrix();

	//  glRotatef((GLfloat)Time, 0.0, 0.0, 1.0);

	//  glTranslatef(0.2, 0.0, 0.0);

	//  glColor3f(0.9, 0.8, 0.2);

	//  glutWireSphere(0.04, 10, 8);

	// glPopMatrix();

	//glPopMatrix();



	glutSwapBuffers();

}



//d:지구가 공전, t:지구가 자전

void MyKeyboard(unsigned char key, int x, int y)

{

	switch (key)

	{

	case 'd':

		Day = (Day + 10) % 360;

		glutPostRedisplay();

		break;



	case 't':

		Time = (Time + 5) % 360;

		glutPostRedisplay();

		break;

	}

}



//타이머를 이용한 자동회전

void MyTimer(int Value)

{

	Day = (Day + 10) % 360;

	Time = (Time + 5) % 360;



	glutPostRedisplay();

	glutTimerFunc(40, MyTimer, 1);

}





int main(int argc, char** argv)

{

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(300, 300);

	glutInitWindowPosition(0, 0);

	glutCreateWindow("OpenGL Sample Drawing");

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(MyDisplay);

	glutKeyboardFunc(MyKeyboard);

	//타이머함수 사용

	//glutTimerFunc(30, MyTimer, 1);

	glutMainLoop();



	return 0;

}
*/