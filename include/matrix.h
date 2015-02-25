#include <stdlib.h>
#include <cmath>
#include <math.h>

//****************************************************
// Matrix
//****************************************************

class Matrix {

  public:
    
    float matrix[16];
    
    float get_value(int x, int y);
      
    void set_value(float value, int x, int y);
    
    // Matrix multiply
    static Matrix multiply(Matrix_3D matrix_1, Matrix_3D matrix_2); 
    
    // Construct translation matrix
    static Matrix translation_matrix(float tx, float ty, float tz);
    
    // Construct rotation matrix
    static Matrix rotation_matrix(float rx, float ry, float rz);
    
    // Construct scalar matrix
    static Matrix scalar_matrix(float sx, float sy, float sz);
    
    // Constructor class
    Matrix();

};
