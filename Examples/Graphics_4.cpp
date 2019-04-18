#pragma warning(disable:4996)
#include "stdafx.h"			
#include<glut.h>			
#include<stdlib.h>			
#include<time.h>
#include<math.h>
#include<Windows.h>

typedef struct {
	GLfloat pos[4];	// position
	GLfloat amb[4];	// ambient
	GLfloat dif[4];	// diffuse
	GLfloat spe[4];	// specular
} Light;

typedef struct {
	GLfloat amb[4];	// ambient
	GLfloat dif[4];	// diffuse
	GLfloat spe[4];	// specular
	GLfloat shi;    // shininess
} Material;

// Prog 22.
/*
GLfloat vertices[][3] = { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 },
{ -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } };
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.5, 0.5, 0.5);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void polygon(int a, int b, int c, int d)
{
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void spin_cube()
{
	glutPostRedisplay();
}

void keyboard_handler(unsigned char key, int x, int y)
{
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
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog22: 3D gray cube");
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}
*/

// Prog 23.
/*
Light light = {
	{ 3.0, 3.0, 3.0, 1.0 },		// position
	{ 1.0, 1.0, 1.0, 1.0 },		// ambient
	{ 1.0, 1.0, 1.0, 1.0 },		// diffuse
	{ 1.0, 1.0, 1.0, 1.0 },		// specular
};

GLfloat vertices[][3] = { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 },
{ -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } };

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.5, 0.5, 0.5);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);		// Modelview 는 Look at을 통해 변환.
	glLoadIdentity();
	// 항상 Look At 다음에 조정해주어야 한다.
	glLightfv(GL_LIGHT0, GL_POSITION, light.pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light.amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.spe);

	//glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void normal(GLfloat *n)
{
	GLfloat x = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
	if (x > 0.0) for (int i = 0; i<3; i++) n[i] /= x;
}

void polygon(int a, int b, int c, int d)
{
	GLfloat nor[3];

	nor[0] = (vertices[a][0] + vertices[b][0] + vertices[c][0] + vertices[d][0]);
	nor[1] = (vertices[a][1] + vertices[b][1] + vertices[c][1] + vertices[d][1]);
	nor[2] = (vertices[a][2] + vertices[b][2] + vertices[c][2] + vertices[d][2]);
	normal(nor);

	glBegin(GL_POLYGON);
	glNormal3fv(nor);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void spin_cube()
{
	glutPostRedisplay();
}

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'x') light.pos[0] -= 0.1;
	if (key == 'X') light.pos[0] += 0.1;
	if (key == 'y') light.pos[1] -= 0.1;
	if (key == 'Y') light.pos[1] += 0.1;
	if (key == 'z') light.pos[2] -= 0.1;
	if (key == 'Z') light.pos[2] += 0.1;

	if (key == 'a') { for (int i = 0; i<3; i++) light.amb[i] -= 0.1; }
	if (key == 'A') { for (int i = 0; i<3; i++) light.amb[i] += 0.1; }
	if (key == 'd') { for (int i = 0; i<3; i++) light.dif[i] -= 0.1; }
	if (key == 'D') { for (int i = 0; i<3; i++) light.dif[i] += 0.1; }
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLightfv(GL_LIGHT0, GL_POSITION, light.pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light.amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.dif);

	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(0, 4, 7, 3);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(0, 1, 5, 4);

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog23: 3D gray cube with lightening");
	glutIdleFunc(spin_cube);
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}
*/

// Prog 24.

GLfloat vertices[][3] = { { -1.0, -1.0, -1.0 }, { 1.0, -1.0, -1.0 }, { 1.0, 1.0, -1.0 }, { -1.0, 1.0, -1.0 },
{ -1.0, -1.0, 1.0 }, { 1.0, -1.0, 1.0 }, { 1.0, 1.0, 1.0 }, { -1.0, 1.0, 1.0 } };

Light light = {
	{ 3.0, 3.0, 3.0, 1.0 },	// position
	{ 1.0, 1.0, 1.0, 1.0 }, // ambient
	{ 1.0, 1.0, 1.0, 1.0 }, // diffuse
	{ 1.0, 1.0, 1.0, 1.0 }, // specular
};

Material mat0 = {
	{ 0.2, 0.2, 0.2, 1.0 }, // ambient
	{ 1.0, 1.0, 1.0, 1.0 }, // diffuse
	{ 1.0, 1.0, 1.0, 1.0 }, // specular
	{ 100.0 }, // shininess
};

Material mat1 = {
	{ 0.2, 0.0, 0.0, 1.0 }, // ambient
	{ 1.0, 0.0, 0.0, 1.0 }, // diffuse
	{ 1.0, 0.0, 0.0, 1.0 }, // specular
	{ 100.0 }, // shininess
};

Material mat2 = {
	{ 0.0, 0.2, 0.0, 1.0 }, // ambient
	{ 0.0, 1.0, 0.0, 1.0 }, // diffuse
	{ 0.0, 1.0, 0.0, 1.0 }, // specular
	{ 100.0 }, // shininess
};

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-5.0, 5.0, -5.0, 5.0, -10.0, 10.0);
	gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_POSITION, light.pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light.amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.spe);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void normal(GLfloat *n)
{
	GLfloat x = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
	if (x > 0.0) for (int i = 0; i<3; i++) n[i] /= x;
}

void polygon(int a, int b, int c, int d)
{
	GLfloat nor[3];

	nor[0] = (vertices[a][0] + vertices[b][0] + vertices[c][0] + vertices[d][0]);
	nor[1] = (vertices[a][1] + vertices[b][1] + vertices[c][1] + vertices[d][1]);
	nor[2] = (vertices[a][2] + vertices[b][2] + vertices[c][2] + vertices[d][2]);
	normal(nor);

	glBegin(GL_POLYGON);
	glNormal3fv(nor);
	glVertex3fv(vertices[a]);
	glVertex3fv(vertices[b]);
	glVertex3fv(vertices[c]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void cube()
{
	polygon(0, 3, 2, 1);
	polygon(2, 3, 7, 6);
	polygon(0, 4, 7, 3);
	polygon(1, 2, 6, 5);
	polygon(4, 5, 6, 7);
	polygon(0, 1, 5, 4);
}

void spin_cube()
{
	glutPostRedisplay();
}

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'x') light.pos[0] -= 0.1;
	if (key == 'X') light.pos[0] += 0.1;
	if (key == 'y') light.pos[1] -= 0.1;
	if (key == 'Y') light.pos[1] += 0.1;
	if (key == 'z') light.pos[2] -= 0.1;
	if (key == 'Z') light.pos[2] += 0.1;

	if (key == 'a') { for (int i = 0; i<3; i++) light.amb[i] -= 0.1; }
	if (key == 'A') { for (int i = 0; i<3; i++) light.amb[i] += 0.1; }
	if (key == 'd') { for (int i = 0; i<3; i++) light.dif[i] -= 0.1; }
	if (key == 'D') { for (int i = 0; i<3; i++) light.dif[i] += 0.1; }
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat0.amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0.dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat0.spe);
	glMaterialf(GL_FRONT, GL_SHININESS, mat0.shi);
	cube();

	glLoadIdentity();
	glTranslatef(-3.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat1.amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat1.dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat1.spe);
	glMaterialf(GL_FRONT, GL_SHININESS, mat1.shi);
	cube();

	glLoadIdentity();
	glTranslatef(+3.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat2.amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat2.dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat2.spe);
	glMaterialf(GL_FRONT, GL_SHININESS, mat2.shi);
	cube();

	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat0.amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat0.dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat0.spe);
	glMaterialf(GL_FRONT, GL_SHININESS, mat0.shi);
	glTranslatef(light.pos[0], light.pos[1], light.pos[2]);
	glutSolidSphere(0.2, 10, 10);

	glLightfv(GL_LIGHT0, GL_POSITION, light.pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light.amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.dif);

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog24: multiple materials");
	glutIdleFunc(spin_cube);
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}


// Prog 25.
/*
typedef float point[4];
point v[] = { { 0.58, 0.58, 0.58 }, { -0.58, -0.58, 0.58 }, { 0.58, -0.58, -0.58 }, { -0.58, 0.58, -0.58 } };

int n = 4;
int mode = 0;

Light light = {
	{ 0.0, 2.0, 2.0, 1.0 },	// position
	{ 1.0, 1.0, 1.0, 1.0 }, // ambient
	{ 1.0, 1.0, 1.0, 1.0 }, // diffuse
	{ 1.0, 1.0, 1.0, 1.0 }, // specular
};

Material mat = {
	{ 0.2, 0.0, 0.0, 1.0 }, // ambient
	{ 1.0, 1.0, 0.0, 1.0 }, // diffuse
	{ 1.0, 1.0, 0.0, 1.0 }, // specular
	{ 100.0 }, // shininess
};

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glLightfv(GL_LIGHT0, GL_POSITION, light.pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light.amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light.spe);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void normal(GLfloat *n)
{
	GLfloat x = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
	if (x > 0.0) for (int i = 0; i<3; i++) n[i] /= x;
}

void triangle(point a, point b, point c)
{
	if (mode != 2) glShadeModel(GL_FLAT); else glShadeModel(GL_SMOOTH);
	if (mode == 0) glBegin(GL_LINE_LOOP);
	else glBegin(GL_POLYGON);

	glNormal3fv(a); glVertex3fv(a);
	glNormal3fv(b); glVertex3fv(b);
	glNormal3fv(c); glVertex3fv(c);

	glEnd();
}

void divide_triangle(point a, point b, point c, int m)
{
	point v1, v2, v3;
	int j;

	if (m>0)
	{
		for (j = 0; j<3; j++) v1[j] = a[j] + b[j]; normal(v1);
		for (j = 0; j<3; j++) v2[j] = a[j] + c[j]; normal(v2);
		for (j = 0; j<3; j++) v3[j] = b[j] + c[j]; normal(v3);
		divide_triangle(a, v1, v2, m - 1);
		divide_triangle(c, v2, v3, m - 1);
		divide_triangle(b, v3, v1, m - 1);
		divide_triangle(v1, v3, v2, m - 1);
	}
	else triangle(a, b, c);
}

void tetrahedron(int m)
{
	divide_triangle(v[0], v[1], v[2], m);
	divide_triangle(v[3], v[2], v[1], m);
	divide_triangle(v[0], v[3], v[1], m);
	divide_triangle(v[0], v[2], v[3], m);
}

void spin_cube()
{
	glutPostRedisplay();
}

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'x') light.pos[0] -= 0.1;
	if (key == 'X') light.pos[0] += 0.1;
	if (key == 'y') light.pos[1] -= 0.1;
	if (key == 'Y') light.pos[1] += 0.1;
	if (key == 'z') light.pos[2] -= 0.1;
	if (key == 'Z') light.pos[2] += 0.1;

	if (key == 'a') { for (int i = 0; i<3; i++) light.amb[i] -= 0.1; }
	if (key == 'A') { for (int i = 0; i<3; i++) light.amb[i] += 0.1; }
	if (key == 'd') { for (int i = 0; i<3; i++) light.dif[i] -= 0.1; }
	if (key == 'D') { for (int i = 0; i<3; i++) light.dif[i] += 0.1; }

	if (key == 'm') mode = (mode + 1) % 3;

	if (key == 'n') n--;
	if (key == 'N') n++;
	if (n<0) n = 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat.amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat.dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat.spe);
	glMaterialf(GL_FRONT, GL_SHININESS, mat.shi);
	tetrahedron(n);

	glTranslatef(light.pos[0], light.pos[1], light.pos[2]);
	glutSolidSphere(0.1, 10, 10);

	glLightfv(GL_LIGHT0, GL_POSITION, light.pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light.amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.dif);

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog25: sphere");
	glutIdleFunc(spin_cube);
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}
*/