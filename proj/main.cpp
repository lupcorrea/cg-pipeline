#include "main.h"

void MyGlDraw () {
	
}

int main (int argc, char **argv) {
    Loader loader;
    loader.loadFile();
    
    printf ("\n");
    for (int i = 0; i < loader.getVertexListSize(); i++) {
        printf ("%f\t%f\t%f\t\t\t", loader.getVertexAt (i).getCoordinate (0), loader.getVertexAt (i).getCoordinate (1), loader.getVertexAt (i).getCoordinate (2));
        printf ("%d\t%d\n", loader.getPixelAt (i).getX(), loader.getPixelAt (i).getY());
    }
    
    printf ("\n");
    for (int i = 0; i < loader.getVertexListSize(); i++) 
        printf ("%d\t%d\t%d\n", loader.getTriangleFrom (i). getValueFrom (0), loader.getTriangleFrom (i). getValueFrom (1), loader.getTriangleFrom (i). getValueFrom (2));
        
    
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	DrawFunc = MyGlDraw;	

	glutMainLoop();

	return 0;
}

