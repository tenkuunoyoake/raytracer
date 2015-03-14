#include <cmath>
#include <limits>
#include <math.h>

#include "sphere.h"

Sphere::Sphere() {

  transform = Matrix::identity_matrix();
  center = Vector(0, 0, 0);
  material = Material();
  radius = 1;
  
}

Sphere::Sphere(Matrix trans, Vector cen, float rad, Material mat) {

  transform = trans;
  center = cen;
  radius = rad;
  material = mat;

}

bool Sphere::intersect(Ray ray) {

  ray = transform_ray(ray);

  Vector pos = ray.position;
  Vector dir = ray.direction;

  float a = Vector::dot(dir, dir);
  float b = 2 * (Vector::dot(dir, pos - center));
  float c = Vector::dot(pos - center, pos - center) - radius * radius;

  float discriminant = b * b - 4 * a * c;

  if (discriminant >= 0)  {

    float t1 = (-b - sqrt(discriminant)) / (2 * a);
    float t2 = (-b + sqrt(discriminant)) / (2 * a);

    if ((t1 >= ray.t_min && t1 <= ray.t_max) || 
        (t2 >= ray.t_min && t2 <= ray.t_max)) {
      return true;
    }

  }

  return false;

}

// Assuming we only care about the first intersection point
Vector Sphere::intersectP(Ray ray) {

  Vector pos = ray.position;
  Vector dir = ray.direction;

  float t = intersectT(ray);

  if (t >= ray.t_min && t <= ray.t_max) {
    // Vector(pos.x + dir.x * t1, pos.y + dir.y * t1, pos.z + dir.z * t1);
    return pos + (t * dir);
  } else {
    return Vector(std::numeric_limits<float>::infinity(), 
        std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
  }

}

float Sphere::intersectT(Ray ray) {

  ray = transform_ray(ray);

  Vector pos = ray.position;
  Vector dir = ray.direction;

  float a = Vector::dot(dir, dir);
  float b = 2 * (Vector::dot(dir, pos - center));
  float c = Vector::dot(pos - center, pos - center) - radius * radius;

  float discriminant = b * b - 4 * a * c;

  if (discriminant >= 0)  {

    float t1 = (-b - sqrt(discriminant)) / (2 * a);
    float t2 = (-b + sqrt(discriminant)) / (2 * a);

    if (t1 >= ray.t_min && t1 <= ray.t_max) {
      return t1;
    } else if (t2 >= ray.t_min && t2 <= ray.t_max) {
      return t2;
    } else {
      return -1;
    }

  }

  return -1;

}

Vector Sphere::get_normal(Vector intersection) {

  intersection = Matrix::transform(transform, intersection);

  Vector normal = (intersection - center) / radius;
  Matrix transpose_inverse = Matrix::transpose(transform);

  return Matrix::transform(transpose_inverse, normal).normalize(); 

}

Ray Sphere::transform_ray(Ray ray) {

  Vector new_position = Matrix::transform(transform, ray.position);
  Vector new_direction = Matrix::transform_dir(transform, ray.direction);
  new_direction = new_direction;

  Ray new_ray = Ray(new_position, new_direction, ray.t_min, ray.t_max);

  return new_ray;

}