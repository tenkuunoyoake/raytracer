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
#include <vector.h>
#include <camera.h>

using namespace std;


//****************************************************
// Global Variables
//****************************************************
int image_width;
int image_height;

int main(int argc, char *argv[]) {
  Vector a = Vector(1.0, 1.0, 1.0); //test
  Camera c = Camera(a, a, a, a, a);
  return 0;
}