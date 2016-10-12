#include "vertex.h"

Pixel Vertex::convertToPixel() {
    double a, b;
    
    if (modf (data[0], &a) > 0.5) a++;
    if (modf (data[1], &b) > 0.5) b++;
    
    Pixel p (a, b);
    return p;
}