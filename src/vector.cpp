#include "vector.h"

//****************************************************
// Vector
//****************************************************

float Vector::len() {
  return sqrt(x * x + y * y + z * z);
}

Vector Vector::normalize() {

  float length = len();

  if (length < 1e-10)
    return Vector(x, y, z);
  
  return Vector(x / length, y / length, z / length);

}

Vector Vector::cross(Vector a, Vector b) {
 
  Vector result;
  
  result.x = a.y * b.z - a.z * b.y;
  result.y = a.z * b.x - a.x * b.z;
  result.z = a.x * b.y - a.y * b.x;
  
  return result;
  
}

float Vector::dot(Vector a, Vector b) {
 
  return a.x * b.x + a.y * b.y + a.z * b.z;
  
}

Vector Vector::point_multiply(Vector a, Vector b) {

  Vector result;

  result.x = a.x * b.x;
  result.y = a.y * b.y;
  result.z = a.z * b.z;

  return result;

}

void Vector::clamp() {

  if (x > 1) {
    x = 1;
  }

  if (y > 1) { 
    y = 1; 
  }

  if (z > 1) {
    z = 1;
  }

}

void Vector::print(Vector v) {
  
  printf("(%f, %f, %f)\n", v.x, v.y, v.z);
  
}

Vector& Vector::operator+=(const Vector& rhs) {
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  return *this;
}

Vector& Vector::operator-=(const Vector& rhs) {
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;
  return *this;
}

Vector& Vector::operator*=(const float scalar) {
  x *= scalar;
  y *= scalar;
  z *= scalar;
  return *this;
}

Vector& Vector::operator/=(const float scalar) {
  x /= scalar;
  y /= scalar;
  z /= scalar;
  return *this;
}

// Default Constructor
Vector::Vector() {
  x = 0;
  y = 0;
  z = 0;
}

// Shorthand
Vector::Vector(float a, float b, float c) {
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
  Vector result = Vector(rhs.x, rhs.y, rhs.z);
  return result *= scalar;
}

Vector operator/(Vector lhs, const float scalar) {
  return lhs /= scalar;
}