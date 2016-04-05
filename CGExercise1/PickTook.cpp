#include "PickTook.h"
#include <stdio.h>

GLenum RenderMode;
int MouseX, MouseY;
#define PICK_TOL 10
#define BUFFER_SIZE 1024
GLuint PickBuffer[BUFFER_SIZE];

void pick::init()
{
	glSelectBuffer(BUFFER_SIZE, PickBuffer);
}

void pick::display()
{
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int viewport[4];
	// Get current viewport
	glGetIntegerv(GL_VIEWPORT, viewport);
	int window_height = glutGet(GLUT_WINDOW_HEIGHT);
	int window_width = glutGet(GLUT_WINDOW_WIDTH);
	if (RenderMode == GL_SELECT) {
		gluPickMatrix((GLdouble)MouseX, (GLdouble)(viewport[3] - MouseY), PICK_TOL, PICK_TOL, viewport);
	}
	// Init project matrix
	gluPerspective(60.0f, (float)(window_width) / window_height, 1.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip
	gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
	// Initialize name buffers
	if (RenderMode == GL_SELECT) {
		glInitNames();
		glPushName(0xffffffff);
	}
	// Render
	glLoadName(1);
	glutSolidSphere(1.0f, 30, 30);
	glLoadName(2);
	glTranslated(0.5, 0.5, 0);
	glutSolidCube(0.6f);
	glPopMatrix();
}

void pick::mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		MouseX = x;
		MouseY = y;
	}
	RenderMode = GL_SELECT;
	glRenderMode(RenderMode);
	display();
	// Restore render mode
	RenderMode = GL_RENDER;
	GLint NHits = glRenderMode(RenderMode);
	int i, index;
	for ( i = 0, index = 0; i < NHits; i++)
	{
		GLuint nitems = PickBuffer[index++];
		GLuint zmin = PickBuffer[index++];
		GLuint zmax = PickBuffer[index++];
		int j;
		for (j = 0; j < nitems; j++) {
			GLuint item = PickBuffer[index++];
			printf("Pick %d\n", item);
		}
	}
}
