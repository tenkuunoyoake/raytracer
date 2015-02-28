#include <vector.h>

//****************************************************
// Vector
//****************************************************

Vector::Vector (float a, float b, float c) {
  x = a;
  y = b;
  z = c;
}

float Vector::len() {
  return sqrt(x * x + y * y + z * z);
}

Vector Vector::normalize() {
  float length = len();
  if (length < 1e-10)
    return Vector(x, y, z);
  return Vector(x / length, y / length, z / length);
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