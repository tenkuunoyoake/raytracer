#include "matrix.h"

//****************************************************
// Matrix
//****************************************************
    
float Matrix::get_value(int x, int y) {
  return matrix[y * 4 + x];
}

void Matrix::set_value(int x, int y, float value) {
  matrix[y * 4 + x] = value;
}

// Matrix multiply
Matrix Matrix::multiply(Matrix_3D matrix_1, Matrix_3D matrix_2) {
  
  Matrix result = Matrix();
  float value;
  
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      value = 0;
      for (int i = 0; i < 4; i++) {
	for (int j = 0; j < 4; j++) {
	  value += matrix_1.get_value(i, y) * matrix_2.get_value(x, j);
	}
      }
      result.set_value(x, y);
    }
  }
  
  return result;
  
}
  
// Construct translation matrix
Matrix Matrix::translation_matrix(float tx, float ty, float tz) {
  
  Matrix result = Matrix();
  result.set_value(0, 0, 1);
  result.set_value(1, 1, 1);
  result.set_value(2, 2, 1);
  result.set_value(3, 3, 1);
  result.set_value(3, 0, tx);
  result.set_value(3, 1, ty);
  result.set_value(3, 2, tz);
  return result;
  
}
  
// Construct rotation matrix
Matrix Matrix::rotation_matrix(float rx, float ry, float rz) {
  
  Matrix result = Matrix();
  
}
  
// Construct scalar matrix
Matrix Matrix::scalar_matrix(float sx, float sy, float sz) {
  
  Matrix result = Matrix();
  
}

// Construct identity matrix
Matrix Matrix::identity_matrix() {
    
  Matrix result = Matrix();
  result.set_value(0, 0, 1);
  result.set_value(1, 1, 1);
  result.set_value(2, 2, 1);
  result.set_value(3, 3, 1);
  
}

// Constructor (Zero-matrix)
Matrix::Matrix() {
  
  // Initialise matrix to 0
  for (int i = 0; i < 16; i++) {
    matrix[i] = 0;
  }
  
}

