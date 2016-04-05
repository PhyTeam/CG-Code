#include <GL\glut.h>
#ifndef _PICK_H_
#define _PICK_H_
namespace pick {
	void init();
	void display();
	void mouseClick(int button, int state, int x, int y);

}
#endif