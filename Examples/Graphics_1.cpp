// Graphics_1.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
#pragma warning(disable:4996)
#include "stdafx.h"			// �ڵ����� ����Ǵ� ���ε�. (�������� ������ ���� ������Ͽ� ����)
#include<glut.h>			// header file �� �������� ��, �ڵ����� ã���ִµ�, glut �տ� gl �̶�� �ٿ����� ���� gl �̶�� ������
#include<stdlib.h>			// ������ �׷��� �ȴ�. Directory(���) �� ���ϴ� �� ����.
#include<time.h>

// Prog 01
/*
void init();
void display();
int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);		// glutInit - Program �� �ʱ�ȭ �����ִ� function. (parameter �� ������)
	glutInitWindowSize(500, 500);		// glutInitWindowSize - 500 pixel Size�� �����ִ� function.
	glutCreateWindow("Prog01 : first OpenGL program");		// glutCreateWindow - ����â(Windowâ) ���� �̸��� �������ִ� function.
	glutDisplayFunc(display);			// glutDisplayFunc - display ���� ������ ���ֶ�� �Ѱ��ִ� ��.

	init();
	glutMainLoop();						// ���� Queue �� Loop �� ���鼭 User �� Action �� �°� ��������ֱ� ���� �Լ�.

	return 0;
}

void init() 
{
	glClearColor(1.0, 1.0, 1.0, 1.0);		// Parameter ������ Window �� Clear ���ش�. (R,G,B A�� ����) 
	glColor3f(1.0, 0.0, 0.0);				// �׸��� ���� ���� ���Ѵ�. (ex. �׿� ���� ������ ĥ�ϵ�)
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);		// ��ǥ�� Parameter �� �����ش�. (�� ��, ���� ����� �ƴϴ�. ũ�⿡ ���� ����Ǵ°��� �� �� �ִ�.)
}
// Window Size �� Size �� �����ϰ� 0.0 ~ 50.50 �̱⿡, Window â�� ����� Ű��� ������ Point �� Ȯ���� �� �ִ� ��.
void display()								// Window â�� �׸��� �׸���, ���� ������ �κ�.
{
	glClear(GL_COLOR_BUFFER_BIT);			// Buffer �� ���� �ִ� ��. 
	glBegin(GL_POINTS);						// Parameter �� ������ ���� �����ִµ�, ����� Points ������ �׸��ڴٴ� ��.

	for (double f = 10; f < 40; f += 0.1)	// f�� 300�� �ݺ��ϸ鼭, 4���� ���� ����ִ� ��.
	{	
		glVertex2f(f, 10); glVertex2f(f, 40);	// Parameter �� 2D �� ��ǥ�� �����ִ� ��. ���� ������ ���� ������ �׸���.
		glVertex2f(10, f); glVertex2f(40, f);	// ������ ������ �������� ������ �׸� ��.
	}

	glEnd();								// End�� ���ؼ� �� �׷ȴٴ� ���� ��Ÿ��.
	glFlush();								// OpenGL�� �Ѱ� �Ѱ��� �� ó���� �ϴ� ���� �ƴ�, �ѹ��� ��� 1200���� ���� �׸��� ���� �ϱ⿡ 
}											// Flush�� ����Ǹ� �ѹ��� ���� ���� �������ش�.				
*/

// Prog 02
/*
static int delay = 100;

void init()
{
	srand(time(0));
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void display()
{
	int x1, y1, x2, y2, r, g, b;

	x1 = rand() % 50;
	y1 = rand() % 50;
	x2 = rand() % 50;
	y2 = rand() % 50;
	r = rand() % 256;
	g = rand() % 256;
	b = rand() % 256;

	glColor3f((GLfloat)r / 255, (GLfloat)g / 255, (GLfloat)b / 255);

	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glEnd();
	glFlush();
}

void timer(int t)
{
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog_02 : Random Boxes");
	glutDisplayFunc(display);
	glutTimerFunc(delay, timer, 0);

	init();
	glutMainLoop();

	return 0;
}
*/

// Prog 03		// �� ��輱���� ������ �����Ǵ� ������...!

static int delay = 1;	// �ӵ��� �����̶�µ�, ���⼭ �ӵ� �����ϴ°� ������?
GLfloat x, y, x_sign, y_sign;
void init()
{
	srand(time(0));
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);
	glClear(GL_COLOR_BUFFER_BIT);
	x = rand() % 51; y = rand() % 51;
	x_sign = (float)((rand() % 21) - 11) / 100;
	y_sign = (float)((rand() % 21) - 11) / 100;
	printf("%f %f\n", x, y);
	printf("%f %f", x_sign, y_sign);
}

void display()
{
	glColor3f(x / 50, y / 50, 0);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	x += x_sign; y += y_sign;
	if (x < 0 || x > 50)
	{
		x -= x_sign;
		x_sign *= -1;
	}
	if (y < 0 || y > 50)
	{
		y -= y_sign;
		y_sign *= -1;
	}
	glEnd();						
	glFlush();
}

void timer(int t)
{
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog_03 : Bouncing pixel");
	glutDisplayFunc(display);
	glutTimerFunc(delay, timer, 0);

	init();
	glutMainLoop();
	return 0;
}

// Prog 4
/*
GLfloat point[3][2] = {{ 0, 0}, {25, 50}, { 50, 0 }};
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void DrawTriangle(GLfloat *a, GLfloat *b, GLfloat *c, int N)
{
	glColor3f(1.0, 1.0, 1.0);
	if (N == 0)
		return;
	
	GLfloat mid[3][2] = { { (*a + *b) / 2, (*(a + 1) + *(b + 1)) / 2 },
	{ (*a + *c) / 2, (*(a + 1) + *(c + 1)) / 2 },
	{ (*b + *c) / 2, (*(b + 1) + *(c + 1)) / 2 } };
	glVertex2fv(mid[0]); glVertex2fv(mid[1]); glVertex2fv(mid[2]);

	DrawTriangle(a, mid[0], mid[1], N - 1);
	DrawTriangle(b, mid[0], mid[2], N - 1);
	DrawTriangle(c, mid[1], mid[2], N - 1);
}

void display()
{
	glBegin(GL_TRIANGLES);
	glVertex2fv(point[0]); glVertex2fv(point[1]); glVertex2fv(point[2]);
	DrawTriangle(point[0], point[1], point[2], 5);
	glEnd();
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog_04 : Recursive Triangles");
	glutDisplayFunc(display);

	init();
	glutMainLoop();
	return 0;
}
*/