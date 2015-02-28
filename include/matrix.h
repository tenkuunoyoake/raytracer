#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <math.h>

#ifndef _INCLUDE_VECTOR_H
#define _INCLUDE_VECTOR_H
#include <vector.h>
#endif

#ifndef PI
#define PI 3.14159265
#endif

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
    
    // Given input matrix and scalar, returns the scaled matrix
    static Matrix scaled_matrix(Matrix input, float scalar);
    
    // Matrix addition
    static Matrix add(Matrix matrix_1, Matrix matrix_2);
    
    // Matrix multiply
    static Matrix multiply(Matrix matrix_1, Matrix matrix_2);
    
    // Vector multiply
    static Vector transform(Matrix matrix, Vector vector);
    
    // Determinant
    static float determinant(Matrix input);
    
    // Transpose
    static Matrix transpose(Matrix input);
    
    // Inverse
    static Matrix inverse(Matrix input);
    
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