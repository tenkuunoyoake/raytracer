#include <cmath>
#include <limits>
#include <math.h>

#include "triangle.h"

Triangle::Triangle() {

  transform = Matrix::identity_matrix();
  material = Material();
  v1 = Vector(0, 0, 0);
  v2 = Vector(0, 0, 0);
  v3 = Vector(0, 0, 0);
  vnorm1 = Vector(0, 0, 0);
  vnorm2 = Vector(0, 0, 0);
  vnorm3 = Vector(0, 0, 0);
  tcoord1 = Vector(0, 0, 0);
  tcoord2 = Vector(0, 0, 0);
  tcoord3 = Vector(0, 0, 0);
  U = Vector(0, 0, 0);
  V = Vector(0, 0, 0);
  d00 = d01 = d11 = inv_denom = 0;

}

Triangle::Triangle(Matrix trans, Vector point1, Vector point2, Vector point3, 
    Material mat) {

  material = mat;
  v1 = point1;
  v2 = point2;
  v3 = point3;
  do_transform(trans);
  tcoord1 = Vector(0, 0, 0);
  tcoord2 = Vector(0, 0, 0);
  tcoord3 = Vector(0, 0, 0);
  U = v2 - v1;
  V = v3 - v1;
  vnorm1 = vnorm2 = vnorm3 = Vector::cross(U, V).normalize();
  d00 = Vector::dot(U, U);
  d01 = Vector::dot(U, V);
  d11 = Vector::dot(V, V);
  inv_denom = 1 / (d00 * d11 - d01 * d01);

}

Triangle::Triangle(Matrix trans, Vector point1, Vector point2, Vector point3, 
    Vector norm1, Vector norm2, Vector norm3, Vector tc1, Vector tc2,
    Vector tc3, Material mat) {

  material = mat;
  v1 = point1;
  v2 = point2;
  v3 = point3;
  do_transform(trans);
  U = v2 - v1;
  V = v3 - v1;
  vnorm1 = norm1.normalize();
  vnorm2 = norm2.normalize();
  vnorm3 = norm3.normalize();
  tcoord1 = tc1;
  tcoord2 = tc2;
  tcoord3 = tc3;
  d00 = Vector::dot(U, U);
  d01 = Vector::dot(U, V);
  d11 = Vector::dot(V, V);
  inv_denom = 1 / (d00 * d11 - d01 * d01);

}

Vector Triangle::getNormal(Vector point) {

  // Get barycentric coordinates
  Vector W = point - v1;
  float d20 = Vector::dot(W, U);
  float d21 = Vector::dot(W, V);
  float v = (d11 * d20 - d01 * d21) * inv_denom;
  float w = (d00 * d21 - d01 * d20) * inv_denom;
  float u = 1 - v - w;

  Vector normal = u * vnorm1 + v * vnorm2 + w * vnorm3;

  return normal.normalize();

}

void Triangle::do_transform(Matrix c_transform) {

  v1 = Matrix::transform(c_transform, v1);
  v2 = Matrix::transform(c_transform, v2);
  v3 = Matrix::transform(c_transform, v3);
  
}

bool Triangle::intersect(Ray ray){

  Vector pos = ray.position;
  Vector dir = ray.direction;

  float min = ray.t_min;
  float max = ray.t_max;

  Vector e1 = v2-v1;
  Vector e2 = v3-v1;

  Vector s = pos-v1;
  Vector p = Vector::cross(dir, e2);
  Vector q = Vector::cross(s, e1);

  float a = Vector::dot(p, e1);

  if(a == 0) {
    return false;
  }

  float beta = (1 / a) * Vector::dot(s, p);
  float gamma = (1 / a) * Vector::dot(dir, q);
  float t = (1 / a) * Vector::dot(e2, q);

  // beta < 0 || gamma < 0 || beta > 1 || gamma > 1 || beta + gamma > 1 
  if (beta < 0 || gamma < 0 || beta + gamma > 1 || t > max || t < min) {
    return false;
  } else {
    return true;
  }

}

Vector Triangle::intersectP(Ray ray) {

  Vector pos = ray.position;
  Vector dir = ray.direction;

  float min = ray.t_min;
  float max = ray.t_max;

  float t = intersectT(ray);

  if (t >= min && t <= max) {
    return pos + (t * dir);
  } else {
    return Vector(numeric_limits<float>::infinity(), 
        numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
  }

}

float Triangle::intersectT(Ray ray) {

  Vector pos = ray.position;
  Vector dir = ray.direction;

  Vector e1 = v2 - v1;
  Vector e2 = v3 - v1;

  Vector s = pos - v1;
  Vector p = Vector::cross(dir, e2);
  Vector q = Vector::cross(s, e1);

  float a = Vector::dot(p, e1);

  if (a == 0) {
    printf("This shouldn't be printing check if you passed ur things right.");
    return -1;
  }

  return (1 / a) * (Vector::dot(e2, q));

}