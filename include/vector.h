#ifndef VECTOR_H
#define VECTOR_H
#endif

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#include <cmath>
#include <math.h>
#include <stdio.h>

//****************************************************
// Vector
//****************************************************
class Vector {                                        // note: vectors are simply [x,y,z]
  public:                                             // so things like points and colors use Vector

    float x, y, z;

    Vector (float, float, float);
    float len();
    Vector normalize();

    Vector& operator+=(const Vector&);
    Vector& operator-=(const Vector&);
    Vector& operator*=(const float);
    Vector& operator/=(const float);
    
    static void print(Vector v);
};

Vector operator+(Vector, const Vector&);
Vector operator-(Vector, const Vector&);
Vector operator*(Vector, const float);
Vector operator*(const float, Vector&);
Vector operator/(Vector, const float);