#ifndef _VERTEX_
#define _VERTEX_

#include "pixel.h"
#include "math.h"

class Vertex {
    double data [DIM];
    
    public:
    /* WARNING: For 3D spaces only! */
    Vertex (double a, double b, double c) {
        data [0] = a;
        data [1] = b;
        data [2] = c;
    }
    
    double getCoordinate (int position) { return data [position]; }
    void setCoordinate (int position, double value) { data [position] = value; }
    
    Pixel convertToPixel();
};

#endif