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
  Vector U = v2 - v1;
  Vector V = v3 - v1;
  vnorm1 = vnorm2 = vnorm3 = Vector::cross(U, V).normalize();

}

Triangle::Triangle(Matrix trans, Vector point1, Vector point2, Vector point3, 
    Vector norm1, Vector norm2, Vector norm3, Vector tc1, Vector tc2,
    Vector tc3, Material mat) {

  material = mat;
  v1 = point1;
  v2 = point2;
  v3 = point3;
  do_transform(trans);
  vnorm1 = norm1.normalize();
  vnorm2 = norm2.normalize();
  vnorm3 = norm3.normalize();
  tcoord1 = tc1;
  tcoord2 = tc2;
  tcoord3 = tc3;

}

Vector Triangle::get_normal(Vector point) {

  Vector U = vnorm2 - vnorm1;
  Vector V = vnorm3 - vnorm1;

  // x = x1 + beta * (x2 - x1) + gamma * (x3 - x1)
  // beta * (x2 - x1) = x - x1 - gamma * (x3 - x1)
  // beta = [(x - x1) + gamma * (x1 - x3)] / (x2 - x1)
  // y = y1 + beta * (y2 - y1) + gamma * (y3 - y1)
  // y - y1 = [(x - x1) + gamma * (x1 - x3)] / (x2 - x1) + gamma * (y3 - y1)
  // gamma * [(x1 - x3) / (x2 - x1) + (y3 - y1)] = (y - y1) - (x1 - x) / (x2 - x1)
  // gamma * [(x1 - x3) + (y3 - y1) * (x2 - x1)] = (y - y1) * (x2 - x1) - (x1 -x)

  float gamma = (v1.x - v3.x) + (v3.y - v1.y) * (v2.x - v1.x);
  if (gamma != 0)
    gamma = ((point.y - v1.y) * (v2.x - v1.x) + (point.x - v1.x)) / gamma;
  float beta = (point.x - v1.x) + gamma * (v1.x - v3.x);
  if (v2.x - v1.x != 0)
    beta = beta / (v2.x - v1.x);

  Vector normal = vnorm1 + beta * U + gamma * V;

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