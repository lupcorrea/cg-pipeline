#include "matrix.h"

Matrix::Matrix () {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (i == j) data [i][j] = 1;
            else data [i][j] = 0;
        }
    }
}
    
void Matrix::setValueAt (int i, int j, double value) {
    data [i][j] = value;
}
double Matrix::getValueFrom (int i, int j) {
    return data [i][j];
}
    
void Matrix::multiplyByVertex (Vertex vIn, Vertex *vOut) {
    double temp;
    
    for (int i = 0; i < DIM; i++) {
        temp = 0;
        for (int j = 0; j < DIM; j++) {
            temp += data [i][j] * vIn.getCoordinate (j);
        }
        (*vOut).setCoordinate (i, temp);
    }
}

void Matrix::multiplyByMatrix (Matrix mIn, Matrix *mOut) {
    double temp;
    
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            temp = 0;
            for (int k = 0; k < DIM; k++) temp += data [i][k] * mIn.getValueFrom (k, j);
            (*mOut).setValueAt (i, j, temp);
        }
    }
}