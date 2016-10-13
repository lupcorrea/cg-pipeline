#include "main.h"

void MyGlDraw () {
    
    /* Loader stuff */
    Loader loader;
    loader.loadFile();
    // Triangle list
    printf ("\n");
    for (int i = 0; i < loader.getVertexListSize(); i++) 
        printf ("%d\t%d\t%d\n", loader.getTriangleFrom (i). getValueFrom (0), loader.getTriangleFrom (i). getValueFrom (1), loader.getTriangleFrom (i). getValueFrom (2));
    
    /* Model matrix */
    Matrix model;
    model.setValueAt (0, 0, 4);
    model.setValueAt (1, 1, 4);
    model.setValueAt (2, 2, 4);
    
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
    for (int i = 0; i < 3; i++) norm += cameraUp [i] * zCam [i];
    norm = sqrt (norm);
    double xCam [3];
    if (norm != 0) {
        for (int i = 0; i < 3; i++) xCam [i] = (cameraUp [i] * zCam [i]) / norm;
    } else {
        for (int i = 0; i < 3; i++) xCam [i] = (cameraUp [i] * zCam [i]);
    }
    // Y axis
    norm = 0;
    for (int i = 0; i < 3; i++) norm += zCam [i] * xCam [i];
    norm = sqrt (norm);
    double yCam [3];
    if (norm != 0) {
        for (int i = 0; i < 3; i++) yCam [i] = (zCam [i] * xCam [i]) / norm;
    } else {
        for (int i = 0; i < 3; i++) yCam [i] = (zCam [i] * xCam [i]);
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
    screenS.setValueAt (0, 0, IMAGE_WIDTH / 2);
    screenS.setValueAt (1, 1, IMAGE_HEIGHT / 2);
    // Actual viewport matrix 
    Matrix viewport;
    screenS.multiplyByMatrix (screenT, &viewport);
    
    /* Viewport application */
    for (int i = 0; i < loader.getVertexListSize(); i++) {
        viewport.multiplyByVertex (loader.getVertexAt (i), &vDraft);
        loader.setVertexAt (i, vDraft);
    }
    
    /* Raster every triangle */
    Pixel p1 (0, 0);
    Pixel p2 (0, 0);
    Pixel p3 (0, 0);
    for (int i = 0; i < loader.getTriangleListSize(); i++) {
        p1 = loader.getVertexAt (loader.getTriangleFrom (i).getValueFrom (0) - 1).convertToPixel();
        p2 = loader.getVertexAt (loader.getTriangleFrom (i).getValueFrom (1) - 1).convertToPixel();
        p3 = loader.getVertexAt (loader.getTriangleFrom (i).getValueFrom (2) - 1).convertToPixel();
        drawTriangle (p1, p2, p3);
    }
    
    // Vertex and pixel list
    printf ("\n");
    for (int i = 0; i < loader.getVertexListSize(); i++) {
        printf ("%f\t%f\t%f\t\t\t", loader.getVertexAt (i).getCoordinate (0), loader.getVertexAt (i).getCoordinate (1), loader.getVertexAt (i).getCoordinate (2));
        printf ("%d\t%d\n", loader.getPixelAt (i).getX(), loader.getPixelAt (i).getY());
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

