#include "raster.h"

void drawPixel (Pixel p1) {
    // Find the position in the FB
    int curr_pos = 4 * p1.getX() + 4 * IMAGE_WIDTH * (IMAGE_HEIGHT - p1.getY());
    
    // Color the FB position
    if (p1.getX() < IMAGE_WIDTH && p1.getY() < IMAGE_HEIGHT) {
        FBptr[curr_pos] = p1.getR();
        FBptr[curr_pos + 1] = p1.getG();
        FBptr[curr_pos + 2] = p1.getB();
        FBptr[curr_pos + 3] = p1.getA();
    }
}

int biggerThanScreen (Pixel p1) {
    if (p1.getX() >= IMAGE_WIDTH || p1.getY() >= IMAGE_HEIGHT) return 1;
    return 0;
}

void setNextColor (Pixel p1, Pixel p2, Pixel *p) {
    int dx = p2.getX() - p1.getX();
    int dy = p2.getY() - p1.getY();
    
    if (dy < 0) dy *= -1;
    if (dx < 0) dx *= -1;
    
    if (dx > dy) {
        dx = p2.getX() - p1.getX();
        int currPos = (*p).getX() - p1.getX();
        (*p).setR (p1.getR() + currPos * (p2.getR() - p1.getR())/dx);
        (*p).setG (p1.getG() + currPos * (p2.getG() - p1.getG())/dx);
        (*p).setB (p1.getB() + currPos * (p2.getB() - p1.getB())/dx);
    } else {
        dy = p2.getY() - p1.getY();
        int currPos = (*p).getY() - p1.getY();
        (*p).setR (p1.getR() + currPos * (p2.getR() - p1.getR())/dy);
        (*p).setG (p1.getG() + currPos * (p2.getG() - p1.getG())/dy);
        (*p).setB (p1.getB() + currPos * (p2.getB() - p1.getB())/dy);
    }
}

void drawLine (Pixel p1, Pixel p2) {
    /* Deltas */
    int dx = p2.getX() - p1.getX();
    int dy = p2.getY() - p1.getY();
    
    /* Increments */
    int e = 2 * dy;
    int ne = 2 * (dy - dx);
    int n = -2 * dx;
    int nw = -2 * (dy + dx);
    int w = -2 * dy;
    int sw = -2 * (dy - dx);
    int s = 2 * dx;
    int se = 2 * (dy + dx);
    
    /* Start the navigation pixel and plot it */
    Pixel p = p1;
    drawPixel (p);
    
    /* Determine the octant the line belongs to */
    if (dx > 0 && dy > 0 && dx > dy) {
        /* First octant */
        int d = 2 * dy - dx;
        while (p.getX() < p2.getX()) {
            if (d <= 0) {
                // Line below midpoint
                d += e;
                p.incX();
            } else {
                // Line above midpoint
                d += ne;
                p.incX();
                p.incY();
            }
            setNextColor (p1, p2, &p);
            drawPixel (p);
        }
    } else if (dx > 0 && dy > 0 && dx <= dy) { 
        // Second octant
        int d = dy - 2 * dx;
        while (p.getY() < p2.getY()) {
            if (d > 0) {
                // Line at midpoint's left
                d += n;
                p.incY();
            } else {
                // Line at midpoint's right
                d += ne;
                p.incX();
                p.incY();
            }
            setNextColor (p1, p2, &p);
            drawPixel (p);
        }
    } else if (dx <= 0 && dy > 0 && -dx <= dy) {
        // Third octant
        int d = -dy - 2 * dx;
        while (p.getY() < p2.getY()) {
            if (d <= 0) {
                // Line at midpoint's right
                d += n;
                p.incY();
            } else {
                // Line at midpoint's left
                d += nw;
                p.decX();
                p.incY();
            }
            setNextColor (p1, p2, &p);
            drawPixel (p);
        }
    } else if (dx <= 0 && dy > 0 && -dx > dy) {
        // Fourth octant
        int d = -2 * dy - dx;
        while (p.getX() > p2.getX()) {
            if (d > 0) {
                // Line below midpoint
                d += w;
                p.decX();
            } else {
                // Line above midpoint
                d += nw;
                p.decX();
                p.incY();
            }
            setNextColor (p1, p2, &p);
            drawPixel (p);
        }
    } else if (dx <= 0 && dy <= 0 && -dx > -dy) {
        // Fifth octant
        int d = -2 * dy + dx;
        while (p.getX() > p2.getX()) {
            if (d > 0) {
                // Line below midpoint
                d += sw;
                p.decX();
                p.decY();
            } else {
                // Line above midpoint
                d += w;
                p.decX();
            }
            setNextColor (p1, p2, &p);
            drawPixel (p);
        }
    } else if (dx <= 0 && dy <= 0 && -dx <= -dy) {
        // Sixth octant
        int d = 2 * dx - dy;
        while (p.getY() > p2.getY()) {
            if (d <= 0) {
                // Line at midpoint's left 
                d += sw;
                p.decX();
                p.decY();
            } else {
                // Line at midpoint's right
                d += s;
                p.decY();
            }
            setNextColor (p1, p2, &p);
            drawPixel (p);
        }
    } else if (dx > 0 && dy <= 0 && dx <= -dy) {
        // Seventh octant
        int d = 2 * dy + dx;
        while (p.getY() > p2.getY()) {
            if (d <= 0) {
                // Line at midpoint's left
                d += s;
                p.decY();
            } else {
                // Line at midpoint's right
                d += se;
                p.decY();
                p.incX();
            }
            setNextColor (p1, p2, &p);
            drawPixel (p);
        }
    } else if (dx > 0 && dy <= 0 && dx > -dy) {
        // Eighth octant *******************************************
        int d = 2 * dy + dx;
        while (p.getX() < p2.getX()) {
            if (d < 0) {
                // Line below midpoint
                d += se;
                p.incX();
                p.decY();
            } else {
                // Line at midpoint's right
                d += e;
                p.incX();
            }
            setNextColor (p1, p2, &p);
            drawPixel (p);
        }
    }
}

void drawTriangle (Pixel p1, Pixel p2, Pixel p3) {
    drawLine (p1, p2);
    drawLine (p2, p3);
    drawLine (p3, p1);
}