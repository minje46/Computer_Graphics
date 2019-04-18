// Graphics_1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
#pragma warning(disable:4996)
#include "stdafx.h"			// 자동으로 저장되는 것인듯. (그전까지 만들어논 것을 헤더파일에 저장)
#include<glut.h>			// header file 을 설정해줄 때, 자동으로 찾아주는데, glut 앞에 gl 이라고 붙여놓는 것은 gl 이라는 폴더를
#include<stdlib.h>			// 때문에 그렇게 된다. Directory(경로) 를 뜻하는 것 같음.
#include<time.h>

// Prog 01
/*
void init();
void display();
int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);		// glutInit - Program 을 초기화 시켜주는 function. (parameter 는 고정값)
	glutInitWindowSize(500, 500);		// glutInitWindowSize - 500 pixel Size를 정해주는 function.
	glutCreateWindow("Prog01 : first OpenGL program");		// glutCreateWindow - 실행창(Window창) 줄의 이름을 설정해주는 function.
	glutDisplayFunc(display);			// glutDisplayFunc - display 에게 관리를 해주라고 넘겨주는 것.

	init();
	glutMainLoop();						// 실행 Queue 를 Loop 로 돌면서 User 의 Action 에 맞게 실행시켜주기 위한 함수.

	return 0;
}

void init() 
{
	glClearColor(1.0, 1.0, 1.0, 1.0);		// Parameter 값으로 Window 를 Clear 해준다. (R,G,B A의 순서) 
	glColor3f(1.0, 0.0, 0.0);				// 그리기 전에 색을 정한다. (ex. 붓에 색을 묻히고 칠하듯)
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);		// 좌표를 Parameter 로 던져준다. (이 때, 고정 사이즈가 아니다. 크기에 따라 변경되는것을 볼 수 있다.)
}
// Window Size 는 Size 에 무관하게 0.0 ~ 50.50 이기에, Window 창의 사이즈를 키우면 눈으로 Point 를 확인할 수 있는 것.
void display()								// Window 창의 그림을 그릴때, 내부 내용의 부분.
{
	glClear(GL_COLOR_BUFFER_BIT);			// Buffer 를 지워 주는 것. 
	glBegin(GL_POINTS);						// Parameter 로 시작할 것을 보내주는데, 현재는 Points 점으로 그리겠다는 것.

	for (double f = 10; f < 40; f += 0.1)	// f가 300번 반복하면서, 4개의 점을 찍어주는 것.
	{	
		glVertex2f(f, 10); glVertex2f(f, 40);	// Parameter 로 2D 의 좌표를 던져주는 것. 밑의 직선과 위의 직선을 그린것.
		glVertex2f(10, f); glVertex2f(40, f);	// 왼쪽의 직선과 오른쪽의 직선을 그린 것.
	}

	glEnd();								// End를 통해서 다 그렸다는 것을 나타냄.
	glFlush();								// OpenGL은 한개 한개씩 일 처리를 하는 것이 아닌, 한번에 모든 1200개의 점을 그리는 일을 하기에 
}											// Flush가 선언되면 한번에 쌓인 일을 실행해준다.				
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

// Prog 03		// 각 경계선에서 꼭짓점 생략되는 문제점...!

static int delay = 1;	// 속도도 랜덤이라는데, 여기서 속도 제어하는거 같은데?
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