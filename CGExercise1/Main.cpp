#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <sstream>
#include <iomanip>
#include "Mesh.h"
/* global varible */
void *font = GLUT_BITMAP_8_BY_13;
Mesh donut;

int mouseX, mouseY;
bool mouseLeftDown, mouseRightDown, mouseMiddleDown;

GLfloat cameraDistance = -2;
GLfloat tx, ty, rotx, roty;

GLfloat dx, dy, dz;
GLfloat phi, delta;

/* process menu option 'op' */
void menu(int op) {

	switch (op) {
	case 'Q':
	case 'q':
		exit(0);
	}
}

/* executed when a regular key is pressed */
void keyboardDown(unsigned char key, int x, int y) {

	switch (key) {
	case 'Q':
	case 'q':
	case  27:   // ESC
		exit(0);
	case 'a': case 'A':
		dx -= 0.1;
		break;
	case 'd':case 'D':
		dx += 0.1; break;
	case 's': case 'S':
		dy -= 0.1; break;
	case 'w': case 'W':
		dy += 0.1; break;
	case 'z': case 'Z':
		phi += 0.5; break;
	case 'x': case 'X':
		delta += 0.5; break;
	}
	glutPostRedisplay();
}

/* executed when a regular key is released */
void keyboardUp(unsigned char key, int x, int y) {

}

/* executed when a special key is pressed */
void keyboardSpecialDown(int k, int x, int y) {

}

/* executed when a special key is released */
void keyboardSpecialUp(int k, int x, int y) {

}

/* reshaped window */
void reshape(int width, int height) {

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	//GLfloat fieldOfView = 90.0f;
	//glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	//const float fHalfSize = 2;
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	////gluPerspective(fieldOfView, (GLfloat)width / (GLfloat)height, 0.1, 500.0);
	////glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	// set viewport to be the entire window
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	// set perspective viewing frustum
	float aspectRatio = (float)width / height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-aspectRatio, aspectRatio, -1, 1, 0.1, 100);
	gluPerspective(60.0f, (float)(width) / height, 1.0f, 1000.0f); // FOV, AspectRatio, NearClip, FarClip

														  // switch to modelview matrix in order to set scene
	glMatrixMode(GL_MODELVIEW);
}

/* executed when button 'button' is put into state 'state' at screen position ('x', 'y') */
void mouseClick(int button, int state, int x, int y) {
	mouseX = x;
	mouseY = y;

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseLeftDown = true;
		}
		else if (state == GLUT_UP)
			mouseLeftDown = false;
	}

	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseRightDown = true;
		}
		else if (state == GLUT_UP)
			mouseRightDown = false;
	}

	else if (button == GLUT_MIDDLE_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseMiddleDown = true;
		}
		else if (state == GLUT_UP)
			mouseMiddleDown = false;
	}
}

/* executed when the mouse moves to position ('x', 'y') */
void mouseMotion(int x, int y) {
	if (mouseLeftDown)
	{
		tx += (x - mouseX);
		ty += (y - mouseY);
		mouseX = x;
		mouseY = y;
	}
	if (mouseRightDown)
	{
		cameraDistance += (y - mouseY) * 0.2f;
		mouseY = y;
	}

	glutPostRedisplay();
}

/* struct vertex */
class Vertex3D {
public:
	GLfloat x;
	GLfloat y;
	GLfloat z;
public:
	Vertex3D() :
		x(0.0f), y(0.0f), z(0.0f) {}
	Vertex3D(GLfloat _x, GLfloat _y, GLfloat _z)
		: x(_x), y(_y), z(_z)
	{}

};

///////////////////////////////////////////////////////////////////////////////
// write 2d text using GLUT
// The projection matrix must be set to orthogonal before call this function.
///////////////////////////////////////////////////////////////////////////////
void drawString(const char *str, int x, int y, float color[4], void *font)
{
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
	glDisable(GL_LIGHTING);     // need to disable lighting for proper text color

	glColor4fv(color);          // set text color
	glRasterPos2i(x, y);        // place text position

								// loop all characters in the string
	while (*str)
	{
		glutBitmapCharacter(font, *str);
		++str;
	}

	glEnable(GL_LIGHTING);
	glPopAttrib();
}

/* render the scene */
void draw() {
	glColor3ub(255, 255, 0);

	// Create a sphere
	donut.DrawColor();
	/* render the scene here */

	float color4[] = { 1,1,1,1 };
	GLfloat mt[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mt);
	
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Draw info
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);

	std::stringstream ss;
	ss << std::fixed << std::setprecision(3);
	int i = 0;
	for (i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ss << mt[i  + j * 4] << " ";
		}
		drawString(ss.str().c_str(), 10, 100 - 30 * i, color4, font);
		ss.str("");
	}
	drawString("GL_MODELMATRIX", 10, 100 + 30, color4, font);

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


/* display callback function */
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Z-buffer

	// Set the camera orientation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);

	// Rotate and zoom the camera. This order give you maya-like control
	glTranslatef(0, 0, cameraDistance);
	//glTranslatef(tx, ty, 0);
	glRotatef(tx, 1, 0, 0);
	glRotatef(ty, 0, 1, 0);

	glPushMatrix();

	// Transform
	glTranslatef(dx, dy, dz);
	glRotatef(phi, 0, 1, 0);
	glRotatef(delta, 0, 0, 1);
	draw();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

/* executed when program is idle */
void idle() {

}

/* initialize OpenGL settings */
void initGL(int width, int height) {
	// Create a mesh
	donut.CreateDonut(1.0, 0.5);

	reshape(width, height);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

/* initialize GLUT settings, register callbacks, enter main loop */
int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Perspective's GLUT Template");

	// register glut call backs
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(keyboardSpecialDown);
	glutSpecialUpFunc(keyboardSpecialUp);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	//glutIdleFunc(idle);
	glutIgnoreKeyRepeat(true); // ignore keys held down

							   // create a sub menu 
	int subMenu = glutCreateMenu(menu);
	glutAddMenuEntry("Do nothing", 0);
	glutAddMenuEntry("Really Quit", 'q');

	// create main "right click" menu
	//glutCreateMenu(menu);
	//glutAddSubMenu("Sub Menu", subMenu);
	//glutAddMenuEntry("Quit", 'q');
	//glutAttachMenu(GLUT_RIGHT_BUTTON);

	initGL(800, 600);

	glutMainLoop();
	return 0;
}