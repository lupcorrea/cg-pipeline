#ifndef _LOADER_
#define _LOADER_

#include <vector>

#include <fstream>
#include <sstream>
#include <string>

#include "pixel.h"
#include "vertex.h"
#include "triangle.h"

class Loader {
    std::vector <Vertex> vertexList;
    std::vector <Triangle> triangleList;
    
    public:
    /* File loader methods */
    void loadFile();
    
    /* Vertex list methods */
    Vertex getVertexAt (int position);
    Pixel getPixelAt (int position);
    int getVertexListSize();
    
    /* Triang list methods */
    Triangle getTriangleFrom (int position);
    int getTriangleListSize();
    
};

#endif