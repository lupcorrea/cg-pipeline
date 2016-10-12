#ifndef _MATRIX_
#define _MATRIX_

#include "vertex.h"

class Matrix {
    double data [DIM] [DIM];
    
    public:
    Matrix ();
    
    void setValueAt (int i, int j, double value);
    double getValueFrom (int i, int j);
    
    void multiplyByVertex (Vertex vIn, Vertex *vOut);
    void multiplyByMatrix (Matrix mIn, Matrix *mOut);
};

#endif