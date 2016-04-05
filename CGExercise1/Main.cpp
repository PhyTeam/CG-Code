#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <sstream>
#include <iomanip>
#include "Mesh.h"
#include "PickTook.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
/* global varible */
void *font = GLUT_BITMAP_8_BY_13;
Mesh donut;
Mesh cylinder;

std::vector<Mesh*> objects;

int mouseX, mouseY;
bool mouseLeftDown, mouseRightDown, mouseMiddleDown;

GLfloat cameraDistance = -2;
GLfloat tx, ty, rotx, roty;

GLfloat dx, dy, dz;

float deltaX, deltaY, deltaZ;

GLfloat phi, delta;
float width = 800, height = 600;

int current_mesh = -1;

/* Project matrix */
glm::mat4x4 project_matrix;
glm::mat4x4 view_matrix;

#define SAFE_DELETE(ptr) if(ptr != nullptr) delete ptr
class Camera {
public:
	glm::vec3* position;
	glm::vec3* up;
	glm::vec3* centre;
	
	Camera(float eyex, float eyey, float eyez, float centrex, float centrey, float centrez) {
		position = new glm::vec3(eyex, eyey, eyez);
		up = new glm::vec3(0, 1, 0);
		centre = new glm::vec3(centrex, centrey, centrez);
	}

	~Camera() {
		SAFE_DELETE(position);
		SAFE_DELETE(up);
		SAFE_DELETE(centre);
	}

	void apply() {
		gluLookAt(position->x, position->y, position->z, centre->x, centre->y, centre->z, up->x, up->y, up->z);
	}

};

// Declare a camera
Camera* mainCamera;

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
	//glFrustum(-aspectRatio, aspectRatio, -1, 1, 1, 100);
	gluPerspective(60.0f, (float)(width) / height, 1.f, 10.f); // FOV, AspectRatio, NearClip, FarClip

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

using namespace glm;

void generateRay(vec3& r, int x, int y) {
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLdouble winX, winY;
	GLdouble winZ0 = 1.0f; GLdouble winZ1 = 10.0f;
	GLdouble posX0, posY0, posZ0;
	GLdouble posX1, posY1, posZ1;
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	winX = (GLdouble)x;
	winY = (GLdouble)viewport[3] - (GLdouble)y;
	glReadBuffer(GL_BACK);
	gluUnProject(winX, winY, winZ0,
		modelview, projection, viewport, &posX0, &posY0, &posZ0);
	gluUnProject(winX, winY, winZ1,
		modelview, projection, viewport, &posX1, &posY1, &posZ1);

	r.x = posX1 - posX0;
	r.y = posY1 - posY0;
	r.z = posZ1 - posZ0;
	vec3 t = glm::normalize(r);
	r = t;
	printf("r = (%f,%f,%f)", r.x, r.y, r.z);
}

void ray_casting(int mouse_x, int mouse_y) {
	// Generate ray
		float x = (2.0f * mouse_x) / width - 1.0f;
		float y = 1.0f - (2.0f * mouse_y) / height;
		float z = 1.0f;

		vec3 ray_nds = vec3(x, y, z);
		vec4 ray_clip = vec4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);

		vec4 ray_eye = glm::inverse(project_matrix) * ray_clip;
		ray_eye = vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);

		vec4 _ray_wor = glm::inverse(view_matrix) * ray_eye;
		vec3 ray_wor = glm::vec3(_ray_wor.x, _ray_wor.y, _ray_wor.z);
		ray_wor = glm::normalize(ray_wor);
		//printf("r = (%f,%f,%f)\n", ray_wor.x, ray_wor.y, ray_wor.z);
	//float x, y;
		vec3 v;
		//generateRay(v, mouse_x, mouse_y);
	x = mouse_x; y = mouse_y;
	static GLint viewport[4];
	static GLdouble modelview[16];
	static GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	GLubyte pixel[3];
	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadBuffer(GL_BACK);
	//read color and depth
	glReadPixels(x, int(winY), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (void *)pixel);
	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection,
		viewport, &posX, &posY, &posZ);
	printf("(%f, %f, %f)\n", posX, posY, posZ);

	// Camara coor
	vec3 O = *mainCamera->position;
	// check
	for (int i = 0; i < objects.size(); i++)
	{
		BoundSphere* bs = objects[i]->getBoundingSphere();
		vec3 C = vec3(objects[i]->position->x, objects[i]->position->y, objects[i]->position->z);
		float r = objects[i]->get_BS_radius();
		float b = glm::dot(ray_wor, (O - C));
		float c = glm::dot(O - C, O - C) - r * r;
		if (b * b - c >= 0) {
			//printf("Collision");
			current_mesh = i;
			printf("Clicked on object : %d\n", i);
			break;
		}
	}
}

void mouseClick_handler(int button, int state, int mouse_x, int mouse_y) {
	mouseX = mouse_x;
	mouseY = mouse_y;

	//pick::mouseClick(button, state, mouse_x, mouse_y);

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			ray_casting(mouse_x, mouse_y);
			mouseLeftDown = true;
		}
		else if (state == GLUT_UP) {
			mouseLeftDown = false;
			current_mesh = -1;
			
		}
	}
}



/* executed when the mouse moves to position ('x', 'y') */
void mouseMotion(int x, int y) {
	//if (mouseLeftDown)
	//{
	//	tx += (x - mouseX);
	//	ty += (y - mouseY);
	//	mouseX = x;
	//	mouseY = y;
	//}
	if (current_mesh == -1) return;

	if (mouseLeftDown) {
		deltaX += (x - mouseX);
		deltaY += (y - mouseY);

		float worldX = (2.0f * deltaX) / width - 1.0f;
		float worldY = -(1.0f - (2.0f * deltaY) / height);
		// Set current mesh position
		Mesh* current = objects[current_mesh];
		float cx = current->position->x, cy = current->position->y,
			cz = current->position->z;

		current->position->set(cx + (x - mouseX) * 0.01f, cy - (y - mouseY) * 0.01f, cz);

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
	// Drawing here
	glMatrixMode(GL_MODELVIEW);
	for (size_t i = 0; i < objects.size(); i++)
	{
		glPushMatrix();
		Point3* position = objects[i]->position;
		glTranslated(position->x, position->y, position->z);
		objects[i]->DrawColor();
		glPopMatrix();
	}
	//pick::display();

	float color4[] = { 1,1,1,1 };
	// Get drawing matrix
	GLfloat mt[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mt);
	view_matrix = glm::transpose(glm::make_mat4x4(mt));
	glGetFloatv(GL_PROJECTION_MATRIX, mt);
	project_matrix = glm::transpose(glm::make_mat4x4(mt));
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
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

	glMatrixMode(GL_PROJECTION);
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
	//gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
	mainCamera->apply();
	
	//glRotatef(tx, 1, 0, 0);
	//glRotatef(ty, 0, 1, 0);

	glPushMatrix();

	// Transform

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
	//donut.CreateDonut(1.0, 0.5);
	cylinder.CreateCube(0.5f);
	donut.CreateModel(2, 1, 0.5, 1);
	donut.CreateSphere(10, 10, 0.25);

	cylinder.CreateSphere(10, 10, 0.5);
	cylinder.position->set(0.5f, .5f, 0);
	BoundSphere* bs = cylinder.getBoundingSphere();
	bs->centre[0] = 0.5f;
	bs->centre[1] = 0.5f;
	objects.push_back(&donut);
	objects.push_back(&cylinder);

	Mesh* ms = new Mesh();
	ms->position->set(-0.5, -0.5, 0);
	ms->CreateSphere(10, 10, 0.6);
	bs = cylinder.getBoundingSphere();
	bs->centre[0] = -0.5f;
	bs->centre[1] = -0.5f;
	objects.push_back(ms);

	ms = new Mesh();
	ms->position->set(-0.5, 0.5, 1);
	ms->CreateSphere(10, 10, 0.2);
	objects.push_back(ms);

	reshape(width, height);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	pick::init();
	// Setup a camera
	mainCamera = new Camera(0, 0, 4, 0, 0, 0);

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
	glutMouseFunc(mouseClick_handler);
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

	// Release memory
	SAFE_DELETE(mainCamera);
	return 0;
}