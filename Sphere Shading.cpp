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
	GLfloat x = sqrt((n[0] * n[0]) + (n[1] * n[1]) + (n[2] * n[2]));
	
	if (x > 0.0) 
		for (int i = 0; i<3; i++) 
			n[i] /= x;
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

void Small_Triangle(point a, point b, point c, int m)
{
	point v1, v2, v3;
	int j;

	if (m>0)
	{
		for (j = 0; j<3; j++) v1[j] = a[j] + b[j]; normal(v1);
		for (j = 0; j<3; j++) v2[j] = a[j] + c[j]; normal(v2);
		for (j = 0; j<3; j++) v3[j] = b[j] + c[j]; normal(v3);
		Small_Triangle(a, v1, v2, m - 1);
		Small_Triangle(c, v2, v3, m - 1);
		Small_Triangle(b, v3, v1, m - 1);
		Small_Triangle(v1, v3, v2, m - 1);
	}
	else triangle(a, b, c);
}

void Make_Triangle(int m)
{
	Small_Triangle(v[0], v[1], v[2], m);
	Small_Triangle(v[3], v[2], v[1], m);
	Small_Triangle(v[0], v[3], v[1], m);
	Small_Triangle(v[0], v[2], v[3], m);
}

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'x') 
		light.pos[0] -= 0.1;
	if (key == 'X') 
		light.pos[0] += 0.1;
	if (key == 'y') 
		light.pos[1] -= 0.1;
	if (key == 'Y') 
		light.pos[1] += 0.1;
	if (key == 'z') 
		light.pos[2] -= 0.1;
	if (key == 'Z') 
		light.pos[2] += 0.1;

	if (key == 'a') 
		for (int i = 0; i<3; i++)
			light.amb[i] -= 0.1; 
	if (key == 'A')  
		for (int i = 0; i<3; i++) 
			light.amb[i] += 0.1; 
	if (key == 'd')  
		for (int i = 0; i<3; i++) 
			light.dif[i] -= 0.1; 
	if (key == 'D')  
		for (int i = 0; i<3; i++) 
			light.dif[i] += 0.1; 

	if (n < 0)
		n = 0;
	if (key == 'n')
		n--;
	if (key == 'N')
		n++;

	if (key == 'm') 
		mode = (mode + 1) % 3;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat.amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat.dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat.spe);
	glMaterialf(GL_FRONT, GL_SHININESS, mat.shi);
	Make_Triangle(n);

	glTranslatef(light.pos[0], light.pos[1], light.pos[2]);
	glutSolidSphere(0.1, 10, 10);

	glLightfv(GL_LIGHT0, GL_POSITION, light.pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light.amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light.dif);

	glFlush();
	glutSwapBuffers();
}

void replay()
{
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog25: Sphere Shading");
	glutIdleFunc(replay);
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	init();
	glutMainLoop();

	return 0;
}
