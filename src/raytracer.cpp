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
// #include <vector.h>
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
  
}

int main(int argc, char *argv[]) {
  matrix_test();
  // Vector a = Vector(1.0, 1.0, 1.0); //test
  // Camera c = Camera(a, a, a, a, a);
  return 0;
}