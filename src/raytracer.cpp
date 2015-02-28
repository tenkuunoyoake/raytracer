#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Self-defined

#include <matrix.h>

#ifndef _INCLUDE_VECTOR_H
#define _INCLUDE_VECTOR_H
#include <vector.h>
#endif
// #include <camera.h>

using namespace std;

//****************************************************
// Global Variables
//****************************************************
int image_width;
int image_height;

void matrix_test() {
 
  Matrix zero = Matrix();
  Matrix identity = Matrix::identity_matrix();
  
  Matrix inverse_input = Matrix();
  inverse_input.set_value(0, 0, 2);
  inverse_input.set_value(1, 0, -6);
  inverse_input.set_value(2, 0, 3);
  inverse_input.set_value(3, 0, 1);
  inverse_input.set_value(0, 1, 6);
  inverse_input.set_value(1, 1, 3);
  inverse_input.set_value(2, 1, 2);
  inverse_input.set_value(3, 1, 1);
  inverse_input.set_value(0, 2, -3);
  inverse_input.set_value(1, 2, 2);
  inverse_input.set_value(2, 2, 6);
  inverse_input.set_value(3, 2, 1);
  inverse_input.set_value(0, 3, 0);
  inverse_input.set_value(1, 3, 0);
  inverse_input.set_value(2, 3, 0);
  inverse_input.set_value(3, 3, 1);
  Matrix inverse_output = Matrix::inverse(inverse_input);
  
  Matrix::print(zero);
  Matrix::print(identity);
  Matrix::print(inverse_input);
  Matrix::print(inverse_output);
  Matrix::print(Matrix::multiply(inverse_input, identity));
  Matrix::print(inverse_input);
  
}

void transform_test() {
 
  Matrix::print(Matrix::scalar_matrix(2, 2, 2));
  Matrix::print(Matrix::rotation_matrix(90 / sqrt(2), 0, 90 / sqrt(2)));
  
}

int main(int argc, char *argv[]) {
  
  // matrix_test();
  transform_test();
  
  /*
  Vector a = Vector(1.0, 2.0, 3.0);
  Vector b = Vector(4.0, 5.0, 6.0);
  Vector c = a + b;
  Vector d = b - a;
  Vector e = a * 2;
  Vector f = 3 * b;
  Vector g = a / 4;
  Vector h = b.normalize();

  cout << a.x << " " << a.y << " " << a.z << endl;
  cout << b.x << " " << b.y << " " << b.z << endl;
  cout << c.x << " " << c.y << " " << c.z << endl;
  cout << d.x << " " << d.y << " " << d.z << endl;
  cout << e.x << " " << e.y << " " << e.z << endl;
  cout << f.x << " " << f.y << " " << f.z << endl;
  cout << g.x << " " << g.y << " " << g.z << endl;
  cout << h.x << " " << h.y << " " << h.z << endl;
  cout << (float) b.len() << endl;
  cout << (float) h.len() << endl;
  */
  
  // Camera c = Camera(a, a, a, a, a);
  return 0;
}
