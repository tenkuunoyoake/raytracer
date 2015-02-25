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

using namespace std;

//****************************************************
// Classes and Methods
//****************************************************
class Vector {                                        // note: vectors are simply [x,y,z]
  public:                                             // so things like points and colors use Vector
    float x, y, z;
    Vector (float, float, float);
    Vector& operator+=(const Vector& rhs) {
      x += rhs.x;
      y += rhs.y;
      z += rhs.z;
      return *this;
    }
    Vector& operator-=(const Vector& rhs) {
      x -= rhs.x;
      y -= rhs.y;
      z -= rhs.z;
      return *this;
    }
    Vector& operator*=(const float scalar) {
      x *= scalar;
      y *= scalar;
      z *= scalar;
      return *this;
    }
    Vector& operator/=(const float scalar) {
      x /= scalar;
      y /= scalar;
      z /= scalar;
      return *this;
    }
    
};

Vector::Vector (float a, float b, float c) {
  x = a;
  y = b;
  z = c;
}

Vector operator+(Vector lhs, const Vector& rhs) {
  return lhs += rhs;
}

Vector operator-(Vector lhs, const Vector& rhs) {
  return lhs -= rhs;
}

Vector operator*(Vector lhs, const float scalar) {
  return lhs *= scalar;
}

Vector operator*(const float scalar, Vector& rhs) {
  return rhs *= scalar;
}

Vector operator/(Vector lhs, const float scalar) {
  return lhs /= scalar;
}

Vector operator/(const float scalar, Vector& rhs) {
  return rhs /= scalar;
}

//****************************************************
// Global Variables
//****************************************************
int image_width;
int image_height;

int main(int argc, char *argv[]) {
  return 0;
}