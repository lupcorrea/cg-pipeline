#include "loader.h"

/* File loader methods */
void Loader::loadFile() {
    std::ifstream file (FILENAME);
    std::string line;
    
    /* Skip metadata */
    std::getline (file, line);
    std::getline (file, line);
    std::getline (file, line);
    
    while (std::getline (file, line)) {
        std::istringstream stream (line);
        char v;
        double a, b, c;
        
        if (stream >> v >> a >> b >> c) {
            if (v == 'v') {
                Vertex vIn (a, b, c);
                vertexList.push_back (vIn);
            } else if (v == 'f') {
                Triangle t;
                t.setValueAt (0, a); t.setValueAt (1, b); t.setValueAt (2, c); 
                triangleList.push_back (t);
            }
        }
    }
}
    
/* Vertex list methods */
Vertex Loader::getVertexAt (int position) {
    return vertexList [position];
}
Pixel Loader::getPixelAt (int position) {
    return vertexList [position].convertToPixel();
}
int Loader::getVertexListSize() {
    return vertexList.size();
}
    
/* Triang list methods */
Triangle Loader::getTriangleFrom (int position) {
    return triangleList [position];
}
int Loader::getTriangleListSize() {
    return triangleList.size();
}