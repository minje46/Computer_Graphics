#pragma warning(disable:4996)
//#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"			
#include<glut.h>			
#include<stdlib.h>			
#include<time.h>
#include<math.h>

// Prog 06
/*
static int delay = 1;
static float x[3], y[3];
static float xinc[3], yinc[3];
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);
	glClear(GL_COLOR_BUFFER_BIT);

	srand(time(0));
	for (int i = 0; i < 3; i++)
	{
		x[i] = rand() % 50;
		y[i] = rand() % 50; 
		xinc[i] = (float)((rand() % 50) - 25) / 250;
		yinc[i] = (float)((rand() % 50) - 25) / 250;
	}
	for (int i = 0; i < 3; i++)
	{
		printf("%f %f\n", x[i], y[i]);
		printf("%f %f", xinc[i], yinc[i]);
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);		// 새로 그릴 때 마다, 화면을 지워준다.
	glColor3f(x[0] / 50.0, y[0] / 50.0, 0.0);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 3; i++)
		glVertex2f(x[i],y[i]);
	glEnd();
	glFlush();

	for (int j = 0; j < 3; j++)
	{
		x[j] += xinc[j]; y[j] += yinc[j];
		if (x[j]<0 || x[j]>50) { x[j] -= xinc[j]; xinc[j] *= -1; }
		if (y[j]<0 || y[j]>50) { y[j] -= yinc[j]; yinc[j] *= -1; }
	}
}

void timer(int t)
{
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog06: Bouncing triangles");
	glutDisplayFunc(display);
	glutTimerFunc(delay, timer, 0);

	init();
	glutMainLoop();

	return 0;
}
*/

// Prog 07 ~ 08
/*
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(0.0, 50.0, 0.0, 50.0, -50.0, 50.0);
	glClear(GL_DEPTH_TEST);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 앞면
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(15, 15, 35); glVertex3f(35, 15, 35);
	glVertex3f(35, 35, 35); glVertex3f(15, 35, 35);
	glEnd();
	//뒷면
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(20, 20, 15); glVertex3f(40, 20, 15); 
	glVertex3f(40, 40, 15); glVertex3f(20, 40, 15);
	glEnd();
	// 천장
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(20, 40, 15); glVertex3f(40, 40, 15); 
	glVertex3f(35, 35, 35); glVertex3f(15, 35, 35);
	glEnd();
	// 바닥
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(15, 15, 35); glVertex3f(35, 15, 35);
	glVertex3f(40, 20, 15); glVertex3f(20, 20, 15);
	glEnd();
	//오른쪽 side
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(35, 35, 35); glVertex3f(40, 40, 15); 
	glVertex3f(40, 20, 15); glVertex3f(35, 15, 35);
	glEnd();
	// 왼쪽 side
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(15, 35, 35); glVertex3f(15, 15, 35); 
	glVertex3f(20, 20, 15); glVertex3f(20, 40, 15);
	glEnd();

	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog08: hidden surface removal");
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}
*/

// Prog 09		// 이해 몬함.
/*
#define PI 3.141592
#define Radian PI / 180;
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// 기능이 뭔가여?
}

void display()
{	
	float first, next, theta;
	float x, y, z;
	float rad = 80.0 * Radian;					// 이 계산은 왜?

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, 1.0);
	z = sin(rad);								// 원뿔은 꼭지점에서 이동 안해야 하는거 아니야?
	for (int i = -180; i <= 180; i += 10)		// 왜 10도 씩만 증가해?
	{
		glColor3f(fabs((float)i) / 180, 0.0, 0.0);
		theta = i * Radian;						
		x = sin(theta) * cos(rad);				// 왜 sin 과 cos에 쎄타 값을 다르게 하는거야?
		y = cos(theta) * cos(rad);
		glVertex3f(x, y, z);					// 여기서 x와 y는 각 삼각형의 밑변의 좌표가 되는거야?
	}
	glEnd();
	
	glClear(GL_COLOR_BUFFER_BIT);				// 이 기능이 정확히 뭐야?
	for (int i = -80; i <= 80; i += 10)			// 여기서도 왜 10도씩 변화해?
	{
		first = i * Radian;						// 이거 squard 네 개의 점 중에 첫 꼭지점
		next = (i + 20) * Radian;				// 이건 뒤의 꼭지점 맞아?
		glBegin(GL_QUAD_STRIP);
		for (int j = -180; j <= 180; j += 10)	// 10도씩...?
		{
			glColor3f(fabs((float)j) / 180, 0.0, 0.0);
			theta = j * Radian;					
			x = (float)sin(theta) * cos(first);	
			y = (float)cos(theta) * cos(first);
			z = sin(first);
			glVertex3f(x, y, z);				// Squard면 네개의 점 필요한거 아니야? 그릴때?

			x = (float)sin(theta) * cos(next);	// 이 과정은 뒤의 꼭지점을 위한 계산 같아보이는데....맞나..?
			y = (float)cos(theta) * cos(next);
			z = sin(first);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
	
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0.0, 0.0, -1.0);
	z = sin(rad);
	for (int i = -180; i <= 180; i += 10)
	{
		glColor3f(fabs((float)i) / 180, 0.0, 0.0);
		theta = i * Radian;
		x = sin(theta) * cos(rad);
		y = cos(theta) * cos(rad);
		glVertex3f(x, y, z);
	}
	glEnd();

	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);			// 기능이 뭔가여?
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);							// 기능이 뭔가여?
	glutCreateWindow("Prog09: Sphere");
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}
*/

// Prog 10 (그림 접고 펼치기)		// 이해 몬함.
/*
#define PI 3.141592
#define Radian PI / 180
static double theta = 0;
static double thetanic = 5;
static int delay = 100;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glOrtho(0.0, 416.0, 0.0, 240.0, -500.0, 500.0);
	glPointSize(8);
}

void display()
{
	//read data
	static unsigned char buf[240][416];
	FILE *fpt;
	errno_t err;
	err = fopen_s(&fpt, "testo.y", "rb");
	if (err == 0)
	{
		printf("Open to file success.\n");
		fread(buf, 416 * 240, sizeof(char), fpt);
		fclose(fpt);

		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_POINTS);

		for (int y = 0; y < 240; y++)
		{
			for (int x = 0; x < 416; x++)
			{
				GLfloat c = (GLfloat)buf[y][x] / 255;
				GLfloat z = (GLfloat)x*sin(theta * Radian);
				GLfloat xp = (GLfloat)x*cos(theta * Radian);
				GLfloat yp = 239 - (GLfloat)y;

				glColor3f(c, c, c);
				glVertex3f(xp, yp, z);
			}
		}
		glEnd();
		glFlush();
	}
	else
		printf("There is some error during opening file. \n");
}

void timer(int t)
{
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);

	theta += thetanic;
	if (theta <= 0 || theta > 80)
	{
		theta -= thetanic;
		thetanic = -thetanic;
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Prog 10 : Image in 3D");
	glutDisplayFunc(display);
	glutTimerFunc(delay, timer, 0);

	init();
	glutMainLoop();
	return 0;
}
*/

// Prog 11 (정육면체 Y축 회전)
/*
#define PI 3.141592
#define Radian PI / 180
static int delay = 10;
float angle = 0;

void init()
{
	srand(time(0));
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);
	glClear(GL_DEPTH_TEST);
}

void display()
{
	GLfloat v[8][3] = { { 15, 15, 35 }, { 35, 15, 35 }, { 35, 35, 35 }, { 15, 35, 35 }, { 40, 20, 15 }, { 20, 20, 15 }, { 40, 40, 15 }, { 20, 40, 15 } };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < 8; i++)
	{
		v[i][0] = (cos(angle *Radian)*v[i][0]) + (sin(angle*Radian) * v[i][0]);
		v[i][1] = v[i][1];
		v[i][2] = (-sin(angle * Radian)*v[i][2]) + (cos(angle * Radian)*v[i][2]);
	}

	// 앞면
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[0]); glVertex3fv(v[1]);
	glVertex3fv(v[2]); glVertex3fv(v[3]);
	glEnd();
	//뒷면
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[0]); glVertex3fv(v[1]);
	glVertex3fv(v[4]); glVertex3fv(v[5]);
	glEnd();
	// 천장
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[5]); glVertex3fv(v[4]);
	glVertex3fv(v[6]); glVertex3fv(v[7]);
	glEnd();
	// 바닥
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[7]); glVertex3fv(v[6]);
	glVertex3fv(v[2]); glVertex3fv(v[3]);
	glEnd();
	//오른쪽 side
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[0]); glVertex3fv(v[5]);
	glVertex3fv(v[7]); glVertex3fv(v[3]);
	glEnd();
	// 왼쪽 side
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[1]); glVertex3fv(v[4]);
	glVertex3fv(v[6]); glVertex3fv(v[2]);
	glEnd();
	
	if (angle <= 360)
		angle++;
	else
		angle = 0;

	printf("%f %f %f %f \n", angle, v[0][0], v[0][1], v[0][2]);
	glFlush();
}

void timer(int t)
{
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog08: hidden surface removal");
	glutDisplayFunc(display);
	glutTimerFunc(delay, timer, 0);

	init();
	glutMainLoop();

	return 0;
}
*/

// Prog 12 (원점 회전)
/*
#define PI 3.141592
#define Radian PI / 180
static int delay = 10;
float angle = 0;

void init()
{
	srand(time(0));
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);
	glClear(GL_DEPTH_TEST);
}

void display()
{
	GLfloat v[8][3] = { { 15, 15, 35 }, { 35, 15, 35 }, { 35, 35, 35 }, { 15, 35, 35 }, { 40, 20, 15 }, { 20, 20, 15 }, { 40, 40, 15 }, { 20, 40, 15 } };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 8; i++)
	{
		v[i][0] = v[i][0] -25;
		v[i][1] = v[i][1] - 25;
		v[i][2] = v[i][2] - 25;
	}

	for (int i = 0; i < 8; i++)
	{
		v[i][0] = (cos(angle *Radian)*v[i][0]) + (sin(angle*Radian) * v[i][0]);
		v[i][1] = v[i][1];
		v[i][2] = (-sin(angle * Radian)*v[i][2]) + (cos(angle * Radian)*v[i][2]);
	}

	// 앞면
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[0]); glVertex3fv(v[1]);
	glVertex3fv(v[2]); glVertex3fv(v[3]);
	glEnd();
	//뒷면
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[0]); glVertex3fv(v[1]);
	glVertex3fv(v[4]); glVertex3fv(v[5]);
	glEnd();
	// 천장
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[5]); glVertex3fv(v[4]);
	glVertex3fv(v[6]); glVertex3fv(v[7]);
	glEnd();
	// 바닥
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[7]); glVertex3fv(v[6]);
	glVertex3fv(v[2]); glVertex3fv(v[3]);
	glEnd();
	//오른쪽 side
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[0]); glVertex3fv(v[5]);
	glVertex3fv(v[7]); glVertex3fv(v[3]);
	glEnd();
	// 왼쪽 side
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[1]); glVertex3fv(v[4]);
	glVertex3fv(v[6]); glVertex3fv(v[2]);
	glEnd();

	if (angle <= 360)
		angle++;
	else
		angle = 0;

	printf("%f %f %f %f \n", angle, v[0][0], v[0][1], v[0][2]);
	glFlush();
}

void timer(int t)
{
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog08: hidden surface removal");
	glutDisplayFunc(display);
	glutTimerFunc(delay, timer, 0);

	init();
	glutMainLoop();

	return 0;
}
*/

// Prog 13
/*
#define PI 3.141592
#define Radian PI / 180
static int delay = 10;
float angle = 0;
double scalar = 0.1;
double sd = -0.01;

void init()
{
	srand(time(0));
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-30.0, 30.0, -30.0, 30.0, -30.0, 30.0);
	glClear(GL_DEPTH_TEST);
}

void display()
{
	GLfloat v[8][3] = { { 15, 15, 35 }, { 35, 15, 35 }, { 35, 35, 35 }, { 15, 35, 35 }, { 40, 20, 15 }, { 20, 20, 15 }, { 40, 40, 15 }, { 20, 40, 15 } };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < 8; i++)
	{
		v[i][0] = (v[i][0] - 25) * scalar;
		v[i][1] = (v[i][1] - 25) * scalar;
		v[i][2] = (v[i][2] - 25) * scalar;
	}

	for (int i = 0; i < 8; i++)
	{
		v[i][0] = (cos(angle *Radian)*v[i][0]) + (sin(angle*Radian) * v[i][0]);
		v[i][1] = v[i][1];
		v[i][2] = (-sin(angle * Radian)*v[i][2]) + (cos(angle * Radian)*v[i][2]);
	}

	// 앞면
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[0]); glVertex3fv(v[1]);
	glVertex3fv(v[2]); glVertex3fv(v[3]);
	glEnd();
	//뒷면
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[0]); glVertex3fv(v[1]);
	glVertex3fv(v[4]); glVertex3fv(v[5]);
	glEnd();
	// 천장
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[5]); glVertex3fv(v[4]);
	glVertex3fv(v[6]); glVertex3fv(v[7]);
	glEnd();
	// 바닥
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[7]); glVertex3fv(v[6]);
	glVertex3fv(v[2]); glVertex3fv(v[3]);
	glEnd();
	//오른쪽 side
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[0]); glVertex3fv(v[5]);
	glVertex3fv(v[7]); glVertex3fv(v[3]);
	glEnd();
	// 왼쪽 side
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[1]); glVertex3fv(v[4]);
	glVertex3fv(v[6]); glVertex3fv(v[2]);
	glEnd();

	if (angle <= 360)
		angle++;
	else
		angle = 0;

	scalar = scalar + sd;

	if (scalar <= 0.1 || scalar > 1.0)
	{
		sd = -sd;
		scalar = scalar + sd;
	}

	printf("%f %f %f %f \n", angle, v[0][0], v[0][1], v[0][2]);
	glFlush();
}

void timer(int t)
{
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog08: hidden surface removal");
	glutDisplayFunc(display);
	glutTimerFunc(delay, timer, 0);

	init();
	glutMainLoop();

	return 0;
}
*/