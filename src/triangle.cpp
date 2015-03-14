#include <cmath>
#include <limits>
#include <math.h>

#include "triangle.h"

Triangle::Triangle() {

  transform = Matrix::identity_matrix();
  material = Material();
  v1 = Vector(1, 0, 0);
  v2 = Vector(0, 1, 0);
  v3 = Vector(0, 0, 1);

}

Triangle::Triangle(Matrix trans, Vector point1, Vector point2, Vector point3, 
    Material mat) {

  transform = trans;
  material = mat;
  v1 = point1;
  v2 = point2;
  v3 = point3;

}

Vector Triangle::get_normal(Vector intersection) {

  Vector U = v2 - v1;
  Vector V = v3 - v1;

  return Vector::cross(U, V).normalize();

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

  // the actual thing
  Vector e1 = v2-v1;
  Vector e2 = v3-v1;
  Vector p = Vector::cross(dir, e2);
  float a = Vector::dot(p, e1);

  if(a > -0.00001 && a < 0.00001) return false;

  float f = 1/a;

  Vector s = pos-v1;
  float beta = f * Vector::dot(s, p);

  if(beta < 0 || beta > 1.0) return false;

  Vector q = Vector::cross(s, e1);
  float gamma = f * Vector::dot(dir, q);

  if(gamma < 0.0 || beta + gamma > 1.0) return false;

  float t = f * Vector::dot(e2, q);

  if(t < min || t > max) return false;

  return true;

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

  return (1 / a) * (Vector::dot(e2, q));

}