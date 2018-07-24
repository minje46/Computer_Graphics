#include "stdafx.h"
#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include <glut.h>
#include <string.h>
#include "ImageProc.h"

// ---------------------------------------------------------------------------------------------
// Globals
// ---------------------------------------------------------------------------------------------

ImageProc g_cImg;
int g_qunt_step = 1;
int level = 1;
int bmenu = 1;

// ---------------------------------------------------------------------------------------------
// Initialize & Idle
// ---------------------------------------------------------------------------------------------

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle()
{
	glutPostRedisplay();
}

// ---------------------------------------------------------------------------------------------
// I/O
// ---------------------------------------------------------------------------------------------

void Sprint(double x, double y, char *st) {
	int l, i;

	l = strlen(st);
	glRasterPos3f(x, y, -7.0);
	for (i = 0; i < l; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);
	}
}

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 't') bmenu *= -1;
	if (key == 'o') { g_qunt_step = 0; level = 1; g_cImg.loadFromBMP("input.bmp"); glutReshapeWindow(g_cImg.getWidth(), g_cImg.getHeight()); }
	if (key == 'c') { g_cImg.contrastStretch(); }
	if (key == 'z') { g_cImg.gammaCorrection(); }
	if (key == 'h') { g_cImg.histoEqual(); }
	if (key == 'g') g_cImg.convertToGray();
	if (key == 'p') g_cImg.convertToSepia();
	if (key == 'l') g_cImg.samplingBy2();
	if (key == 'q') { g_qunt_step += 1; if (g_qunt_step < 1) g_qunt_step = 1; g_cImg.quantization(g_qunt_step); }
	if (key == 'm') { g_cImg.mirroring(); }
	if (key == 'e') { g_cImg.embossing(); }
	if (key == 'b') { g_cImg.bluring(); }
	if (key == 's') { g_cImg.sharpening(); }
	if (key == 'x') { g_cImg.noise(); }
	if (key == 'a') { g_cImg.gaussian(); }
	if (key == 'v') { g_cImg.median(); }
	if (key == 'k') { g_cImg.kuwahara(); }
	if (key == 'n') { g_cImg.kmeans(); }
	if (key == 'u') { g_cImg.upScale(); glutReshapeWindow(g_cImg.getWidth(), g_cImg.getHeight()); }
	if (key == 'd') { g_cImg.downScale(); glutReshapeWindow(g_cImg.getWidth(), g_cImg.getHeight()); }
	if (key == 'r') { g_cImg.rotation(30.0); }
	if (key == 'i') { g_cImg.HSItoRGB(); }
}

// ---------------------------------------------------------------------------------------------
// Display
// ---------------------------------------------------------------------------------------------

void display()
{
	// clear background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw background
	glLoadIdentity();
	glRasterPos3f(-2.0, -2.0, -8.0);

	glPixelZoom((GLfloat)glutGet(GLUT_WINDOW_WIDTH) / g_cImg.getWidth(), (GLfloat)glutGet(GLUT_WINDOW_HEIGHT) / g_cImg.getHeight());
	glDrawPixels(g_cImg.getWidth(), g_cImg.getHeight(), GL_RGB, GL_UNSIGNED_BYTE, g_cImg.getRGB());

	if (bmenu == 1) {
		char st[50] = "t : toggle menu";
		Sprint(-1.95, -0.5, st);
		strcpy(st, "g : convert Gray");
		Sprint(-1.95, -0.65, st);
		strcpy(st, "p : convert Sepia");
		Sprint(-1.95, -0.8, st);
		strcpy(st, "s : Sampling by 2");
		Sprint(-1.95, -0.95, st);
		strcpy(st, "q : Quantization");
		Sprint(-1.95, -1.1, st);
		strcpy(st, "m : Mirroring");
		Sprint(-1.95, -1.25, st);
		strcpy(st, "k : Kuwahara");
		Sprint(-1.95, -1.4, st);
		strcpy(st, "h : HSI to RGB");
		Sprint(-1.95, -1.55, st);
		strcpy(st, "n : Kmeans");
		Sprint(-1.95, -1.7, st);
	}

	// flush & swap buffers
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{

	// load background
	g_cImg.loadFromBMP("input.bmp");

	// GLUT initialization
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(g_cImg.getWidth(), g_cImg.getHeight());
	glutCreateWindow("HW4");

	// call-back functions
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	// texture initialization
	glEnable(GL_TEXTURE_2D);

	// initialize & run
	init();
	glutMainLoop();

	return 0;
}