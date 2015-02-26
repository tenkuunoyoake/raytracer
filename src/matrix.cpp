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

void Matrix::scale(float scalar) {
  
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      set_value(i, j, scalar * get_value(i, j));
    }
  }
  
}

float Matrix::determinant(Matrix input) {
  
  // Declarations
  float temp;
  float a;
  float b;
  float c;
  float d;
  float e;
  float f;
  float g;
  float h;
  float i;
	
  float result = 0;
  
  for (int k = 0; k < 4; k++) {
    temp = 0;
    // Lol, and stuff...
    switch(k) {
      case 0:
	a = input.get_value(1, 1);
	b = input.get_value(2, 1);
	c = input.get_value(3, 1);
	d = input.get_value(1, 2);
	e = input.get_value(2, 2);
	f = input.get_value(3, 2);
	g = input.get_value(1, 3);
	h = input.get_value(2, 3);
	i = input.get_value(3, 3);
	break;
      case 1:
	a = input.get_value(0, 1);
	b = input.get_value(2, 1);
	c = input.get_value(3, 1);
	d = input.get_value(0, 2);
	e = input.get_value(2, 2);
	f = input.get_value(3, 2);
	g = input.get_value(0, 3);
	h = input.get_value(2, 3);
	i = input.get_value(3, 3);
	break;
      case 2:
	a = input.get_value(0, 1);
	b = input.get_value(1, 1);
	c = input.get_value(3, 1);
	d = input.get_value(0, 2);
	e = input.get_value(1, 2);
	f = input.get_value(3, 2);
	g = input.get_value(0, 3);
	h = input.get_value(1, 3);
	i = input.get_value(3, 3);
	break;
      case 3:
	a = input.get_value(0, 1);
	b = input.get_value(1, 1);
	c = input.get_value(2, 1);
	d = input.get_value(0, 2);
	e = input.get_value(1, 2);
	f = input.get_value(2, 2);
	g = input.get_value(0, 3);
	h = input.get_value(1, 3);
	i = input.get_value(2, 3);
	break;
    }
    temp = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
    temp *= input.get_value(k, 0);
    if (k % 2 == 1) {
      temp = -temp;
    }
    result += temp;
  }
  
  return result;
  
}

Matrix Matrix::transpose(Matrix input) {
 
  // Declarations
  Matrix result = Matrix();
  
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      result.set_value(i, j, input.get_value(j, i));
    }
  }
  
  return result;
  
}
    
// Method assumes that the matrix has an inverse
Matrix Matrix::inverse(Matrix input) {
  
  Matrix result = Matrix();
  
  float a11 = input.get_value(0, 0);
  float a12 = input.get_value(1, 0);
  float a13 = input.get_value(2, 0);
  float a14 = input.get_value(3, 0);
  float a21 = input.get_value(0, 1);
  float a22 = input.get_value(1, 1);
  float a23 = input.get_value(2, 1);
  float a24 = input.get_value(3, 1);
  float a31 = input.get_value(0, 2);
  float a32 = input.get_value(1, 2);
  float a33 = input.get_value(2, 2);
  float a34 = input.get_value(3, 2);
  float a41 = input.get_value(0, 3);
  float a42 = input.get_value(1, 3);
  float a43 = input.get_value(2, 3);
  float a44 = input.get_value(3, 3);
  
  // Here we go...
  float b11 = a22 * a33 * a44 + a23 * a34 * a42 + a24 * a32 * a43 -
	      a22 * a34 * a43 - a23 * a32 * a44 - a24 * a33 * a42;
  
  float b12 = a12 * a34 * a43 + a13 * a32 * a44 + a14 * a33 * a42 -
	      a12 * a33 * a44 - a13 * a34 * a42 - a14 * a32 * a43;
  
  float b13 = a12 * a23 * a44 + a13 * a24 * a42 + a14 * a22 * a43 -
	      a12 * a24 * a43 - a13 * a22 * a44 - a14 * a23 * a42;
  
  float b14 = a12 * a24 * a33 + a13 * a22 * a34 + a14 * a23 * a32 -
	      a12 * a23 * a34 - a13 * a24 * a32 - a14 * a22 * a33;
  
  float b21 = a21 * a34 * a43 + a23 * a31 * a44 + a24 * a33 * a41 -
	      a21 * a33 * a44 - a23 * a34 * a41 - a24 * a31 * a43;
  
  float b22 = a11 * a33 * a44 + a13 * a34 * a41 + a14 * a31 * a43 -
	      a11 * a34 * a43 - a13 * a31 * a44 - a14 * a33 * a41;
  
  float b23 = a11 * a24 * a43 + a13 * a21 * a44 + a14 * a23 * a41 -
	      a11 * a23 * a44 - a13 * a24 * a41 - a14 * a21 * a43;
  
  float b24 = a11 * a23 * a34 + a13 * a24 * a31 + a14 * a21 * a33 -
	      a11 * a24 * a33 - a13 * a21 * a34 - a14 * a23 * a31;
  
  float b31 = a21 * a32 * a44 + a22 * a34 * a41 + a24 * a31 * a42 -
	      a21 * a34 * a42 - a22 * a31 * a44 - a24 * a32 * a41;
  
  float b32 = a11 * a34 * a42 + a12 * a31 * a44 + a14 * a32 * a41 -
	      a11 * a32 * a44 - a12 * a34 * a41 - a14 * a31 * a42;
  
  float b33 = a11 * a22 * a44 + a12 * a24 * a41 + a14 * a21 * a42 -
	      a11 * a24 * a42 - a12 * a21 * a44 - a14 * a22 * a41;
  
  float b34 = a11 * a24 * a32 + a12 * a21 * a34 + a14 * a22 * a31 -
	      a11 * a22 * a34 - a12 * a24 * a31 - a14 * a21 * a32;
  
  float b41 = a21 * a33 * a42 + a22 * a31 * a43 + a23 * a32 * a41 -
	      a21 * a32 * a43 - a22 * a33 * a41 - a23 * a31 * a42;
  
  float b42 = a11 * a32 * a43 + a12 * a33 * a41 + a13 * a31 * a42 -
	      a11 * a33 * a42 - a12 * a31 * a43 - a13 * a32 * a41;
  
  float b43 = a11 * a23 * a42 + a12 * a21 * a43 + a13 * a22 * a41 -
	      a11 * a22 * a43 - a12 * a23 * a41 - a13 * a21 * a42;
  
  float b44 = a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32 -
	      a11 * a23 * a32 - a12 * a21 * a33 - a13 * a22 * a31;
  
  result.set_value(0, 0, b11);
  result.set_value(1, 0, b12);
  result.set_value(2, 0, b13);
  result.set_value(3, 0, b14);
  result.set_value(0, 1, b21);
  result.set_value(1, 1, b22);
  result.set_value(2, 1, b23);
  result.set_value(3, 1, b24);
  result.set_value(0, 2, b31);
  result.set_value(1, 2, b32);
  result.set_value(2, 2, b33);
  result.set_value(3, 2, b34);
  result.set_value(0, 3, b41);
  result.set_value(1, 3, b42);
  result.set_value(2, 3, b43);
  result.set_value(3, 3, b44);
  
  result.scale(1.0f / Matrix::determinant(input));
  
  return result;
  
}

// Matrix multiply
Matrix Matrix::multiply(Matrix matrix_1, Matrix matrix_2) {
  
  // Declarations
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
      result.set_value(x, y, value);
    }
  }
  
  return result;
  
}
  
// Construct translation matrix
Matrix Matrix::translation_matrix(float tx, float ty, float tz) {
  
  // Declarations
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
  
  // Declarations
  Matrix result = Matrix();
  
  return result;
  
}
  
// Construct scalar matrix
Matrix Matrix::scalar_matrix(float sx, float sy, float sz) {
  
  Matrix result = Matrix();
  
  return result;
  
}

// Construct identity matrix
Matrix Matrix::identity_matrix() {
    
  // Declarations
  Matrix result = Matrix();
  
  result.set_value(0, 0, 1);
  result.set_value(1, 1, 1);
  result.set_value(2, 2, 1);
  result.set_value(3, 3, 1);
  
  return result;
  
}

void Matrix::print(Matrix input) {
  
  for (int y = 0; y < 4; y++) {
    printf("[");
    for (int x = 0; x < 4; x++) {
      printf("%f", input.get_value(x, y));
      if (x < 3) {
	printf(" ");
      }
    }
    printf("]\n");
  }
  printf("\n");
  
}

// Constructor (Zero-matrix)
Matrix::Matrix() {
  
  // Initialise matrix to 0
  for (int i = 0; i < 16; i++) {
    matrix[i] = 0;
  }
  
}