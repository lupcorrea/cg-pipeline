#ifndef _TRIANGLE_
#define _TRIANGLE_

class Triangle {
    int data [3];
    
    public:
    void setValueAt (int position, int value) { data [position] = value; }
    int getValueFrom (int position) { return data [position]; }
};

#endif