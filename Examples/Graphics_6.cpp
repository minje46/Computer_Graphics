#pragma warning(disable:4996)
#include "stdafx.h"			
#include<glut.h>			
#include<stdlib.h>			
#include<time.h>
#include<math.h>
#include<Windows.h>
#include <memory.h>

// Prog31.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
/*
// ---------------------------------------------------------------------------------------------
// Type definition
// ---------------------------------------------------------------------------------------------

typedef struct _object
{
	GLfloat*        vertices;    // vertex array
	GLfloat*        colors;      // color array
	GLubyte*        indices;     // index
	int             nums;        // number of vertices

	GLfloat         theta[3];    // rotation parameter (x, y, z)
	GLfloat         trans[3];		 // translation parameter

	struct _object* next;
	struct _object* child;
} Object;

typedef struct _viewer
{
	GLfloat         eye[3];  // viewer position
	GLfloat         at[3];  // center
	GLfloat         up[3];  // up direction
} Viewer;

// ---------------------------------------------------------------------------------------------
// Data
// ---------------------------------------------------------------------------------------------

// array 1 (box)
GLfloat vertices1[][3] = { { -0.6, -1.0, -0.05 }, { 0.6, -1.0, -0.05 }, { 0.6, 1.0, -0.05 }, { -0.6, 1.0, -0.05 },
{ -0.6, -1.0, 0.05 }, { 0.6, -1.0, 0.05 }, { 0.6, 1.0, 0.05 }, { -0.6, 1.0, 0.05 } };
GLfloat colors1[][4] = { { 0.0, 0.0, 0.0, 0.5 }, { 1.0, 0.0, 0.0, 0.5 }, { 1.0, 1.0, 0.0, 0.5 }, { 0.0, 1.0, 0.0, 0.5 },
{ 0.0, 0.0, 1.0, 0.5 }, { 1.0, 0.0, 1.0, 0.5 }, { 1.0, 1.0, 1.0, 0.5 }, { 0.0, 1.0, 1.0, 0.5 } };
GLubyte texflag[] = { 1, 0, 0, 0, 1, 0 };
GLubyte indices1[] = { 0, 3, 2, 1, 2, 3, 7, 6, 0, 4, 7, 3, 1, 2, 6, 5, 4, 5, 6, 7, 0, 1, 5, 4 };

// ---------------------------------------------------------------------------------------------
// Objects
// ---------------------------------------------------------------------------------------------

Object box;
Viewer v;

// ---------------------------------------------------------------------------------------------
// Functions
// ---------------------------------------------------------------------------------------------

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-1.5, 1.5, -1.5, 1.5, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void spin()
{
	glutPostRedisplay();
}

void polygon(Object* p, int index)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i<4; i++)
	{
		glColor4fv(&p->colors[p->indices[index * 4 + i] * 4]);
		glVertex3fv(&p->vertices[p->indices[index * 4 + i] * 3]);
	}
	glEnd();
}

void cube(Object* p)
{
	for (int i = 0; i<6; i++)
	{
		polygon(p, i);
	}
}

// ---------------------------------------------------------------------------------------------
// I/O
// ---------------------------------------------------------------------------------------------

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'x') v.eye[0] -= 0.1; if (key == 'X') v.eye[0] += 0.1;
	if (key == 'y') v.eye[1] -= 0.1; if (key == 'Y') v.eye[1] += 0.1;
	if (key == 'z') v.eye[2] -= 0.1; if (key == 'Z') v.eye[2] += 0.1;
}

void draw(Object* p)
{
	// store matrix
	glPushMatrix();

	// transformation
	glTranslatef(p->trans[0], p->trans[1], p->trans[2]);
	glRotatef(p->theta[0], 1.0, 0.0, 0.0);
	glRotatef(p->theta[1], 0.0, 1.0, 0.0);
	glRotatef(p->theta[2], 0.0, 0.0, 1.0);

	// draw myself
	cube(p);

	// draw children
	if (p->child) draw(p->child);

	// restore matrix
	glPopMatrix();

	// draw siblings
	if (p->next) draw(p->next);
}

void display()
{
	// clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// setup viewer
	glLoadIdentity();
	gluLookAt(v.eye[0], v.eye[1], v.eye[2], v.at[0], v.at[1], v.at[2], v.up[0], v.up[1], v.up[2]);

	// draw
	draw(&box);

	// flush & swap buffers
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	// GLUT initialization
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog31");

	// call-back functions
	glutIdleFunc(spin);
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	// object initialization
	box.vertices = &vertices1[0][0];
	box.colors = &colors1[0][0];
	box.indices = &indices1[0];
	box.nums = 24;

	box.theta[0] = box.theta[1] = box.theta[2] = 0;
	box.trans[0] = box.trans[1] = box.trans[2] = 0;
	box.next = 0;
	box.child = 0;

	// initialize viewer
	v.eye[0] = 1.0; v.eye[1] = 1.0; v.eye[2] = 1.0;
	v.at[0] = 0.0; v.at[1] = 0.0; v.at[2] = 0.0;
	v.up[0] = 0.0; v.up[1] = 1.0; v.up[2] = 0.0;

	init();
	glutMainLoop();

	return 0;
}
*/


// Prog. 34
/*
// ---------------------------------------------------------------------------------------------
// Type definition
// ---------------------------------------------------------------------------------------------

#pragma pack(1)
typedef struct _bmphdr
{
	char id[2];										// bmp id = 'B''M'
	int  size;                    // total size
	char reserved1[2];
	char reserved2[2];
	int  offset;                  // starting offset

	unsigned int   header_sz;
	int            width;
	int            height;
	unsigned short nplanes;
	unsigned short bitspp;
	unsigned int   compress_type;
	unsigned int   bmp_bytesz;
	int            hres;
	int            vres;
	unsigned int   ncolors;
	unsigned int   nimpcolors;

} BMPHdr;
#pragma pack(0)

typedef struct _texture
{
	GLubyte*        rgb;					// rgb array
	int             width;				// width
	int             height;				// height
} Texture;

typedef struct _object
{
	GLfloat*        vertices;			// vertex array
	GLfloat*        colors;				// color array
	GLubyte*        indices;			// index
	int             nums;					// number of vertices

	Texture*        tex;					// texture
	GLubyte*        texflag;			// texture flags
	GLfloat*        texcoord;			// texture coordinate

	GLfloat         theta[3];			// rotation parameter (x, y, z)
	GLfloat         trans[3];			// translation parameter

	struct _object* next;
	struct _object* child;
} Object;

typedef struct _viewer
{
	GLfloat         eye[3];  // viewer position
	GLfloat         at[3];  // center
	GLfloat         up[3];  // up direction
} Viewer;

// ---------------------------------------------------------------------------------------------
// Data
// ---------------------------------------------------------------------------------------------

// array 1 (box)
GLfloat vertices1[][3] = { { -0.6, -1.0, -0.05 }, { 0.6, -1.0, -0.05 }, { 0.6, 1.0, -0.05 }, { -0.6, 1.0, -0.05 },
{ -0.6, -1.0, 0.05 }, { 0.6, -1.0, 0.05 }, { 0.6, 1.0, 0.05 }, { -0.6, 1.0, 0.05 } };
GLfloat colors1[][4] = { { 0.0, 0.0, 0.0, 0.5 }, { 0.0, 0.0, 0.0, 0.5 }, { 0.0, 0.0, 0.0, 0.5 }, { 0.0, 0.0, 0.0, 0.5 },
{ 0.0, 0.0, 0.0, 0.5 }, { 0.0, 0.0, 0.0, 0.5 }, { 0.0, 0.0, 0.0, 0.5 }, { 0.0, 0.0, 0.0, 0.5 } };

GLfloat texcoord[][4][2] = { { { 510.0, 435.0 }, { 510.0, 24.0 }, { 289.0, 24.0 }, { 289.0, 435.0 } },
{ { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 }, { 0.0, 0.0 } },
{ { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 }, { 0.0, 0.0 } },
{ { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 }, { 0.0, 0.0 } },
{ { 33.0, 435.0 }, { 250.0, 435.0 }, { 250.0, 24.0 }, { 33.0, 24.0 } },
{ { 0.0, 1.0 }, { 1.0, 1.0 }, { 1.0, 0.0 }, { 0.0, 0.0 } } };

GLubyte texflag[] = { 1, 0, 0, 0, 1, 0 };
GLubyte indices1[] = { 0, 3, 2, 1, 2, 3, 7, 6, 0, 4, 7, 3, 1, 2, 6, 5, 4, 5, 6, 7, 0, 1, 5, 4 };

// ---------------------------------------------------------------------------------------------
// Objects
// ---------------------------------------------------------------------------------------------

Object  box;
Viewer  v;
Texture background;

// ---------------------------------------------------------------------------------------------
// Functions
// ---------------------------------------------------------------------------------------------

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void spin()
{
	glutPostRedisplay();
}

void polygon(Object* p, int index)
{
	if (p->texflag[index])
	{
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_POLYGON);
		for (int i = 0; i<4; i++)
		{
			glColor4f(1, 1, 1, 0);
			glTexCoord2f(p->texcoord[index * 8 + i * 2] / p->tex->width, (1.0 - p->texcoord[index * 8 + i * 2 + 1] / p->tex->height));
			glVertex3fv(&p->vertices[p->indices[index * 4 + i] * 3]);
		}
		glEnd();
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_POLYGON);
		for (int i = 0; i<4; i++)
		{
			glColor4fv(&p->colors[p->indices[index * 4 + i] * 4]);
			glVertex3fv(&p->vertices[p->indices[index * 4 + i] * 3]);
		}
		glEnd();
	}
}

void cube(Object* p)
{
	for (int i = 0; i<6; i++)
	{
		polygon(p, i);
	}
}

void texture_create(Texture* p, int w, int h)
{
	p->rgb = (GLubyte*)malloc(sizeof(GLubyte)*w*h * 3);
	p->width = w;
	p->height = h;
	memset(p->rgb, 0, sizeof(GLubyte)*w*h * 3);
}

void texture_load_bmp(Texture* p, char* fname)
{
	BMPHdr bmphdr;
	FILE*  fpt;
	int   margin, i;

	fopen_s(&fpt, fname, "rb");
	if (fpt == NULL) exit(1);
	fread(&bmphdr, sizeof(BMPHdr), 1, fpt);

	// create texture
	texture_create(p, bmphdr.width, bmphdr.height);

	// move to data position
	fseek(fpt, bmphdr.offset, 0);

	// compute margin (for 32-bit alignment)
	margin = 4 - ((bmphdr.width * 3) % 4); if (margin == 4) margin = 0;

	// read pixels
	for (i = 0; i<bmphdr.height; i++)
	{
		fread(&p->rgb[i*bmphdr.width * 3], sizeof(GLubyte), bmphdr.width * 3, fpt);
		if (margin) fseek(fpt, margin, 1);
	}

	fclose(fpt);

	// swap r & b
	int temp;
	for (int i = 0; i<p->width*p->height * 3; i += 3)
	{
		temp = p->rgb[i];
		p->rgb[i] = p->rgb[i + 2];
		p->rgb[i + 2] = temp;
	}
}

void texture_destroy(Texture* p)
{
	free(p->rgb);
}

void texture_checkerboard(Texture* p, int px, int py)
{
	for (int y = 0; y<p->height; y++)
	{
		for (int x = 0; x<p->width; x++)
		{
			if (((x / px) + (y / px)) % 2)
			{
				p->rgb[(x + y*p->width) * 3 + 0] = 255;
				p->rgb[(x + y*p->width) * 3 + 1] = 0;
				p->rgb[(x + y*p->width) * 3 + 2] = 0;
			}
			else
			{
				p->rgb[(x + y*p->width) * 3 + 0] = 0;
				p->rgb[(x + y*p->width) * 3 + 1] = 0;
				p->rgb[(x + y*p->width) * 3 + 2] = 255;
			}
		}
	}
}

// ---------------------------------------------------------------------------------------------
// I/O
// ---------------------------------------------------------------------------------------------

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'x') v.eye[0] -= 0.1; if (key == 'X') v.eye[0] += 0.1;
	if (key == 'y') v.eye[1] -= 0.1; if (key == 'Y') v.eye[1] += 0.1;
	if (key == 'z') v.eye[2] -= 0.1; if (key == 'Z') v.eye[2] += 0.1;
}

void draw(Object* p)
{
	// store matrix
	glPushMatrix();

	// transformation
	glTranslatef(p->trans[0], p->trans[1], p->trans[2]);
	glRotatef(p->theta[0], 1.0, 0.0, 0.0);
	glRotatef(p->theta[1], 0.0, 1.0, 0.0);
	glRotatef(p->theta[2], 0.0, 0.0, 1.0);

	// draw myself
	cube(p);

	// draw children
	if (p->child) draw(p->child);

	// restore matrix
	glPopMatrix();

	// draw siblings
	if (p->next) draw(p->next);
}

void display()
{
	// clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// setup viewer
	glLoadIdentity();
	gluLookAt(v.eye[0], v.eye[1], v.eye[2], v.at[0], v.at[1], v.at[2], v.up[0], v.up[1], v.up[2]);

	// draw
	draw(&box);

	// draw background
	glLoadIdentity();
	glRasterPos3f(-2.0, -2.0, -8.0);

	glPixelZoom((GLfloat)glutGet(GLUT_WINDOW_WIDTH) / background.width, (GLfloat)glutGet(GLUT_WINDOW_HEIGHT) / background.height);
	glDrawPixels(background.width, background.height, GL_RGB, GL_UNSIGNED_BYTE, background.rgb);

	// flush & swap buffers
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	// GLUT initialization
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog31");

	// call-back functions
	glutIdleFunc(spin);
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	// texture initialization
	glEnable(GL_TEXTURE_2D);

	Texture tex;
	texture_load_bmp(&tex, "phone.bmp");

	// load background
	texture_load_bmp(&background, "background.bmp");

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex.width, tex.height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex.rgb);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// object initialization
	box.vertices = &vertices1[0][0];
	box.colors = &colors1[0][0];
	box.indices = &indices1[0];
	box.nums = 24;

	box.tex = &tex;
	box.texflag = &texflag[0];
	box.texcoord = &texcoord[0][0][0];

	box.theta[0] = box.theta[1] = box.theta[2] = 0;
	box.trans[0] = box.trans[1] = box.trans[2] = 0;
	box.next = 0;
	box.child = 0;

	// initialize viewer
	v.eye[0] = 1.0; v.eye[1] = 1.0; v.eye[2] = 1.0;
	v.at[0] = 0.0; v.at[1] = 0.0; v.at[2] = 0.0;
	v.up[0] = 0.0; v.up[1] = 1.0; v.up[2] = 0.0;

	init();
	glutMainLoop();

	// free texture
	texture_destroy(&tex);
	texture_destroy(&background);

	return 0;
}
*/

// Prog35.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.

// ---------------------------------------------------------------------------------------------
// Type definition
// ---------------------------------------------------------------------------------------------

typedef struct _action
{
	char    type;                // 'R' or 'T' or 'N' or 'F'
	int     duration;            // how long?
	GLfloat param[3];            // parameters
} Action;

typedef struct _object
{
	GLfloat*        vertices;    // vertex array
	GLfloat*        colors;      // color array
	GLubyte*        indices;     // index
	int             nums;        // number of vertices
	GLfloat         theta[3];    // rotation parameter (x, y, z)
	GLfloat         trans[3];		 // translation parameter

	Action*         action;
	int             action_idx;
	int             action_counter;

	struct _object* next;
	struct _object* child;
} Object;

typedef struct _viewer
{
	GLfloat         eye[3];    // viewer position
	GLfloat         at[3];    // center
	GLfloat         up[3];    // up direction
} Viewer;

// ---------------------------------------------------------------------------------------------
// Data
// ---------------------------------------------------------------------------------------------

// array 1 (top)
GLfloat vertices1[][3] = { { -0.2, -1.0, -0.2 }, { 0.2, -1.0, -0.2 }, { 0.2, 1.0, -0.2 }, { -0.2, 1.0, -0.2 },
{ -0.2, -1.0, 0.2 }, { 0.2, -1.0, 0.2 }, { 0.2, 1.0, 0.2 }, { -0.2, 1.0, 0.2 } };
GLfloat colors1[][3] = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },
{ 0.0, 0.0, 1.0 }, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 } };
GLubyte indices1[] = { 0, 3, 2, 1, 2, 3, 7, 6, 0, 4, 7, 3, 1, 2, 6, 5, 4, 5, 6, 7, 0, 1, 5, 4 };

// array 2 (sb1, sb2)
GLfloat vertices2[][3] = { { -0.8, -0.1, -0.1 }, { 0.8, -0.1, -0.1 }, { 0.8, 0.1, -0.1 }, { -0.8, 0.1, -0.1 },
{ -0.8, -0.1, 0.1 }, { 0.8, -0.1, 0.1 }, { 0.8, 0.1, 0.1 }, { -0.8, 0.1, 0.1 } };
GLfloat colors2[][3] = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },
{ 0.0, 0.0, 1.0 }, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 } };
GLubyte indices2[] = { 0, 3, 2, 1, 2, 3, 7, 6, 0, 4, 7, 3, 1, 2, 6, 5, 4, 5, 6, 7, 0, 1, 5, 4 };

// array 2 (sb3)
GLfloat vertices3[][3] = { { -0.1, -0.4, -0.1 }, { 0.1, -0.4, -0.1 }, { 0.1, 0.4, -0.1 }, { -0.1, 0.4, -0.1 },
{ -0.1, -0.4, 0.1 }, { 0.1, -0.4, 0.1 }, { 0.1, 0.4, 0.1 }, { -0.1, 0.4, 0.1 } };
GLfloat colors3[][3] = { { 0.0, 0.0, 0.0 }, { 1.0, 0.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },
{ 0.0, 0.0, 1.0 }, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 } };
GLubyte indices3[] = { 0, 3, 2, 1, 2, 3, 7, 6, 0, 4, 7, 3, 1, 2, 6, 5, 4, 5, 6, 7, 0, 1, 5, 4 };

// actions
Action action1[] = {
	{ 'T', 30, -0.5, 0, 0 },
	{ 'T', 30, +0.5, 0, 0 },
	{ 'R', 60, 0, 720, 0 },
	{ 'N', 180, 0, 0, 0 },
	{ 'R', 30, 0, 0, 30 },
	{ 'R', 60, 0, 720, 0 },
	{ 'F', 0, 0, 0, 0 }
};

Action action2[] = {
	{ 'N', 120, 0, 0, 0 },
	{ 'R', 60, 0, 720, 0 },
	{ 'N', 150, 0, 0, 0 },
	{ 'R', 60, 0, 720, 0 },
	{ 'F', 0, 0, 0, 0 }
};

Action action3[] = {
	{ 'N', 180, 0, 0, 0 },
	{ 'R', 60, 0, -720, 0 },
	{ 'N', 90, 0, 0, 0 },
	{ 'R', 60, 0, 720, 0 },
	{ 'F', 0, 0, 0, 0 }
};

Action action4[] = {
	{ 'N', 240, 0, 0, 0 },
	{ 'R', 60, 720, 0, 0 },
	{ 'N', 30, 0, 0, 0 },
	{ 'R', 60, 0, 720, 0 },
	{ 'F', 0, 0, 0, 0 }
};

// ---------------------------------------------------------------------------------------------
// Objects
// ---------------------------------------------------------------------------------------------

Object top, sb1, sb2, sb3;
Viewer v;

int    play = 0;

// ---------------------------------------------------------------------------------------------
// Functions
// ---------------------------------------------------------------------------------------------

void init()
{
	Sleep(100.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init_object()
{
	// object initialization
	top.vertices = &vertices1[0][0];
	top.colors = &colors1[0][0];
	top.indices = &indices1[0];
	top.nums = 24;
	top.theta[0] = top.theta[1] = top.theta[2] = 0;
	top.trans[0] = top.trans[1] = top.trans[2] = 0;

	top.action = &action1[0];
	top.action_idx = 0;
	top.action_counter = 0;

	top.next = 0;
	top.child = &sb1;

	sb1.vertices = &vertices2[0][0];
	sb1.colors = &colors2[0][0];
	sb1.indices = &indices2[0];
	sb1.nums = 24;
	sb1.theta[0] = sb1.theta[1] = sb1.theta[2] = 0;
	sb1.trans[0] = 0;
	sb1.trans[1] = 1.0;
	sb1.trans[2] = 0;

	sb1.action = &action2[0];
	sb1.action_idx = 0;
	sb1.action_counter = 0;

	sb1.next = &sb2;
	sb1.child = 0;

	sb2.vertices = &vertices2[0][0];
	sb2.colors = &colors2[0][0];
	sb2.indices = &indices2[0];
	sb2.nums = 24;
	sb2.theta[0] = sb1.theta[1] = sb1.theta[2] = 0;
	sb2.trans[0] = 0;
	sb2.trans[1] = -1.0;
	sb2.trans[2] = 0;

	sb2.action = &action3[0];
	sb2.action_idx = 0;
	sb2.action_counter = 0;

	sb2.next = 0;
	sb2.child = &sb3;

	sb3.vertices = &vertices3[0][0];
	sb3.colors = &colors3[0][0];
	sb3.indices = &indices3[0];
	sb3.nums = 24;
	sb3.theta[0] = sb3.theta[1] = sb3.theta[2] = 0;
	sb3.trans[0] = 0.8;
	sb3.trans[1] = 0;
	sb3.trans[2] = 0;

	sb3.action = &action4[0];
	sb3.action_idx = 0;
	sb3.action_counter = 0;

	sb3.next = 0;
	sb3.child = 0;
}

void spin()
{
	glutPostRedisplay();
}

// ---------------------------------------------------------------------------------------------
// I/O
// ---------------------------------------------------------------------------------------------

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'x') v.eye[0] -= 0.1; if (key == 'X') v.eye[0] += 0.1;
	if (key == 'y') v.eye[1] -= 0.1; if (key == 'Y') v.eye[1] += 0.1;
	if (key == 'z') v.eye[2] -= 0.1; if (key == 'Z') v.eye[2] += 0.1;
	if (key == 'p') play = 1 - play;
	if (key == 'r')
	{
		play = 0;
		init_object();
	}
}

GLfloat clip(GLfloat x)
{
	if (x < 0) return x + 360.0;
	if (x > 360.0) return x - 360.0;
	return x;
}

void action(Object* p)
{
	if (p->action == 0) return;
	if (p->action[p->action_idx].type == 'F')
	{
		p->action_idx = 0;
		p->action_counter = 0;
		return;
	}
	if (p->action[p->action_idx].type == 'R')
	{
		for (int i = 0; i<3; i++)
			p->theta[i] = clip(p->theta[i] + p->action[p->action_idx].param[i] / p->action[p->action_idx].duration);
		p->action_counter++;
	}
	if (p->action[p->action_idx].type == 'T')
	{
		for (int i = 0; i<3; i++)
			p->trans[i] += p->action[p->action_idx].param[i] / p->action[p->action_idx].duration;
		p->action_counter++;
	}
	if (p->action[p->action_idx].type == 'N')
	{
		p->action_counter++;
	}
	if (p->action_counter >= p->action[p->action_idx].duration)
	{
		p->action_idx++;
		p->action_counter = 0;
	}
}

void draw(Object* p)
{
	// store matrix
	glPushMatrix();

	// transformation
	glTranslatef(p->trans[0], p->trans[1], p->trans[2]);
	glRotatef(p->theta[0], 1.0, 0.0, 0.0);
	glRotatef(p->theta[1], 0.0, 1.0, 0.0);
	glRotatef(p->theta[2], 0.0, 0.0, 1.0);

	// draw
	glVertexPointer(3, GL_FLOAT, 0, p->vertices);
	glColorPointer(3, GL_FLOAT, 0, p->colors);
	glDrawElements(GL_QUADS, p->nums, GL_UNSIGNED_BYTE, p->indices);

	// apply action
	if (play) action(p);

	// draw children
	if (p->child) draw(p->child);

	// restore matrix
	glPopMatrix();

	// draw siblings
	if (p->next) draw(p->next);
}

void display()
{
	// clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// setup viewer
	glLoadIdentity();
	gluLookAt(v.eye[0], v.eye[1], v.eye[2], v.at[0], v.at[1], v.at[2], v.up[0], v.up[1], v.up[2]);

	// draw
	draw(&top);

	// flush & swap buffers
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	// GLUT initialization
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog35: scripts");

	// call-back functions
	glutIdleFunc(spin);
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	// enable color/vertex array
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	// initialize object
	init_object();

	// initialize viewer
	v.eye[0] = 0.0; v.eye[1] = 0.0; v.eye[2] = 1.0;
	v.at[0] = 0.0; v.at[1] = 0.0; v.at[2] = 0.0;
	v.up[0] = 0.0; v.up[1] = 1.0; v.up[2] = 0.0;

	init();
	glutMainLoop();

	return 0;
}
