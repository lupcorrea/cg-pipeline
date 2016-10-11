#include "main.h"

void MyGlDraw () {
	
}

int main (int argc, char **argv) {
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	DrawFunc = MyGlDraw;	

	glutMainLoop();

	return 0;
}

