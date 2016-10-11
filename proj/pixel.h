#ifndef _PIXEL_H_
#define _PIXEL_H_

#include "definitions.h"

class Pixel {
    int x;
    int y;
    int r;
    int g;
    int b;
    int a;
    
    public:
        Pixel (int mx, int my, int mr=255, int mg=255, int mb=255, int ma=255) :
            x (mx),
            y (my),
            r (mr),
            g (mg),
            b (mb),
            a (ma)
            {}
    
        int getX () { return x; }
        int getY () { return y; }
        int getR () { return r; }
        int getG () { return g; }
        int getB () { return b; }
        int getA () { return a; }
        void setR (int mr) { r = mr; }
        void setG (int mg) { g = mg; }
        void setB (int mb) { b = mb; }
        void setA (int ma) { a = ma; }
        void setX (int a) { x = a; }
        void setY (int a) { y = a; }
        void incX () { x++; }
        void incY () { y++; }
        void decX () { x--; }
        void decY () { y--; }
};

#endif