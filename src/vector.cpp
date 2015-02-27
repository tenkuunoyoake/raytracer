#include "vector.h"

//****************************************************
// Vector
//****************************************************

Vector::Vector (float a, float b, float c) {
  x = a;
  y = b;
  z = c;
}

int Vector::len() {
  return sqrt(x * x + y * y + z * z);
}

Vector Vector::normalize() {
  float len = sqrt(x * x + y * y + z * z);
  if (len < 1e-10)
    return Vector(x, y, z);
  return Vector(x / len, y / len, z / len);
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