#include "main.h"

void MyGlDraw () {
    
    /* Loader stuff */
    Loader loader;
    loader.loadFile();
    /* Triangle list
    printf ("\n");
    for (int i = 0; i < loader.getVertexListSize(); i++) 
        printf ("%d\t%d\t%d\n", loader.getTriangleFrom (i). getValueFrom (0), loader.getTriangleFrom (i). getValueFrom (1), loader.getTriangleFrom (i). getValueFrom (2));
    
    /* Model matrix */
    Matrix model;
    model.setValueAt (0, 0, 1);
    model.setValueAt (1, 1, 1);
    model.setValueAt (2, 2, 1);
    
    /* Camera parameters */
    double cameraPos [] = {0, 0, 5};
    double cameraUp [] = {0, 1, 0};
    double cameraLookAt [] = {0, 0, 0};
    
    /* Orthonormal system */
    // Z axis
    double norm (0);
    for (int i = 0; i < 3; i++) norm += pow(cameraPos [i] - cameraLookAt [i], 2) ;
    norm = sqrt (norm);
    double zCam [3];
    if (norm != 0) {
        for (int i = 0; i < 3; i++) zCam [i] = (cameraPos [i] - cameraLookAt [i]) / norm;
    } else {
        for (int i = 0; i < 3; i++) zCam [i] = (cameraPos [i] - cameraLookAt [i]);
    }
    // X axis
    norm = 0;
    double xCam [3];
    xCam [0] = (cameraUp [1] * zCam [2]) - (cameraUp [2] * zCam [1]); norm += (xCam [0] * xCam [0]);
    xCam [1] = (cameraUp [2] * zCam [1]) - (cameraUp [1] * zCam [2]); norm += (xCam [1] * xCam [1]);
    xCam [2] = (cameraUp [0] * zCam [1]) - (cameraUp [1] * zCam [0]); norm += (xCam [2] * xCam [2]);
    norm = sqrt (norm);
    if (norm != 0) {
        for (int i = 0; i < 3; i++) xCam [i] /= norm;
    }
    // Y axis
    norm = 0;
    double yCam [3];
    yCam [0] = (zCam [1] * xCam [2]) - (zCam [2] * xCam [1]); norm += (yCam [0] * yCam [0]);
    yCam [1] = (zCam [2] * xCam [1]) - (zCam [1] * xCam [2]); norm += (yCam [1] * yCam [1]);
    yCam [2] = (zCam [0] * xCam [1]) - (zCam [1] * xCam [0]); norm += (yCam [2] * yCam [2]);
    norm = sqrt (norm);
    if (norm != 0) {
        for (int i = 0; i < 3; i++) yCam [i] /= norm;
    }
    
    /* View matrix */
    Matrix bt, t, view;
    // Transposed base
    for (int j = 0; j < DIM-1; j++) bt.setValueAt (0, j, xCam [j]);
    for (int j = 0; j < DIM-1; j++) bt.setValueAt (1, j, yCam [j]);
    for (int j = 0; j < DIM-1; j++) bt.setValueAt (2, j, zCam [j]);
    // Translation matrix
    for (int i = 0; i < DIM-1; i++) t.setValueAt (i, 3, -cameraPos [i]);
    // Actual view matrix
    bt.multiplyByMatrix (t, &view);
    
    /* Modelview matrix */
    Matrix modelview;
    view.multiplyByMatrix (model, &modelview);
    
    /* Projection matrix */
    double d (1);
    Matrix projection;
    projection.setValueAt (3, 2, -1 / d);
    
    /* Modelviewprojection matrix */
    Matrix modelviewprojection;
    projection.multiplyByMatrix (modelview, &modelviewprojection);
    
    /* Modelviewprojection application */
    Vertex vDraft (0, 0, 0);
    for (int i = 0; i < loader.getVertexListSize(); i++) {
        vDraft = loader.getVertexAt (i);
        modelviewprojection.multiplyByVertex (loader.getVertexAt (i), &vDraft);
        loader.setVertexAt (i, vDraft);
    }
    
    /* Homogenization */
    for (int i = 0; i < loader.getVertexListSize(); i++) {
        for (int j = 0; j < DIM; j++) vDraft.setCoordinate (j, loader.getVertexAt (i).getCoordinate (j) / loader.getVertexAt (i).getCoordinate (3));
        loader.setVertexAt (i, vDraft);
    }
    
    /* Viewport matrix */
    // Translation
    Matrix screenT;
    screenT.setValueAt (0, 3, 1);
    screenT.setValueAt (1, 3, 1);
    // Scale
    Matrix screenS;
    screenS.setValueAt (0, 0, 10);
    screenS.setValueAt (1, 1, 10);
    // Actual viewport matrix 
    Matrix viewport;
    screenS.multiplyByMatrix (screenT, &viewport);
    
    /* Viewport application */
    for (int i = 0; i < loader.getVertexListSize(); i++) {
        vDraft = loader.getVertexAt (i);
        viewport.multiplyByVertex (loader.getVertexAt (i), &vDraft);
        loader.setVertexAt (i, vDraft);
    }
    
    /* Vertex and pixel list */
    printf ("\n");
    for (int i = 0; i < loader.getVertexListSize(); i++) {
        printf ("%f\t%f\t%f\t\t\t", loader.getVertexAt (i).getCoordinate (0), loader.getVertexAt (i).getCoordinate (1), loader.getVertexAt (i).getCoordinate (2));
        printf ("%d\t%d\n", loader.getPixelAt (i).getX(), loader.getPixelAt (i).getY());
    }
    
    /* Raster every triangle */
    Pixel p1 (0, 0);
    Pixel p2 (0, 0);
    Pixel p3 (0, 0);
    for (int i = 0; i < loader.getTriangleListSize(); i++) {
        p1 = loader.getVertexAt (loader.getTriangleFrom (i).getValueFrom (0) - 1).convertToPixel();     
        p2 = loader.getVertexAt (loader.getTriangleFrom (i).getValueFrom (1) - 1).convertToPixel();
        p3 = loader.getVertexAt (loader.getTriangleFrom (i).getValueFrom (2) - 1).convertToPixel();
        // printf ("%d %d\t%d %d\t%d %d\n", p1.getX(), p1.getY(), p2.getX(), p2.getY(), p3.getX(), p3.getY());
        //if (!biggerThanScreen (p1) && !biggerThanScreen (p2) && !biggerThanScreen (p3)) 
        drawTriangle (p1, p2, p3);
    }
}

int main (int argc, char **argv) {
    InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	DrawFunc = MyGlDraw;	

	glutMainLoop();

	return 0;
}

