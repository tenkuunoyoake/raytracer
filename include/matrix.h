#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <math.h>

//****************************************************
// Matrix
//****************************************************

class Matrix {

  public:
    
    float matrix[16];
    
    float get_value(int x, int y);
      
    void set_value(int x, int y, float value);
    
    // Scale
    void scale(float scalar);
    
    // Determinant
    static float determinant(Matrix input);
    
    // Transpose
    static Matrix transpose(Matrix input);
    
    // Inverse
    static Matrix inverse(Matrix input);
    
    // Matrix multiply
    static Matrix multiply(Matrix matrix_1, Matrix matrix_2); 
    
    // Construct translation matrix
    static Matrix translation_matrix(float tx, float ty, float tz);
    
    // Construct rotation matrix
    static Matrix rotation_matrix(float rx, float ry, float rz);
    
    // Construct scalar matrix
    static Matrix scalar_matrix(float sx, float sy, float sz);
    
    // Construct identity matrix
    static Matrix identity_matrix();
    
    static void print(Matrix input);
    
    // Constructor class
    Matrix();

};