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

  Ray new_ray = Ray(new_position, new_direction, ray.t_min, ray.t_max);

  return new_ray;

}

// Ugly, but it works for ellipses so lol and stuff
void Sphere::compute_bounding_box() {

  Matrix regular_transform = Matrix::inverse(transform);

  // To clean things up a little
  float temp1;
  float temp2;

  Vector v1 = Vector(center.x - radius, center.y - radius, center.z - radius);
  Vector v2 = Vector(center.x - radius, center.y - radius, center.z + radius);
  Vector v3 = Vector(center.x - radius, center.y + radius, center.z - radius);
  Vector v4 = Vector(center.x - radius, center.y + radius, center.z + radius);
  Vector v5 = Vector(center.x + radius, center.y - radius, center.z - radius);
  Vector v6 = Vector(center.x + radius, center.y - radius, center.z + radius);
  Vector v7 = Vector(center.x + radius, center.y + radius, center.z - radius);
  Vector v8 = Vector(center.x + radius, center.y + radius, center.z + radius);

  v1 = Matrix::transform(regular_transform, v1);
  v2 = Matrix::transform(regular_transform, v2);
  v3 = Matrix::transform(regular_transform, v3);
  v4 = Matrix::transform(regular_transform, v4);
  v5 = Matrix::transform(regular_transform, v5);
  v6 = Matrix::transform(regular_transform, v6);
  v7 = Matrix::transform(regular_transform, v7);
  v8 = Matrix::transform(regular_transform, v8);

  temp1 = min(min(min(v1.x, v2.x), v3.x), v4.x);
  temp2 = min(min(min(v5.x, v6.x), v7.x), v8.x);
  bbox.x_min = min(temp1, temp2);

  temp1 = max(max(max(v1.x, v2.x), v3.x), v4.x);
  temp2 = max(max(max(v5.x, v6.x), v7.x), v8.x);
  bbox.x_max = max(temp1, temp2);

  temp1 = min(min(min(v1.y, v2.y), v3.y), v4.y);
  temp2 = min(min(min(v5.y, v6.y), v7.y), v8.y);
  bbox.y_min = min(temp1, temp2);

  temp1 = max(max(max(v1.y, v2.y), v3.y), v4.y);
  temp2 = max(max(max(v5.y, v6.y), v7.y), v8.y);
  bbox.y_max = max(temp1, temp2);

  temp1 = min(min(min(v1.z, v2.z), v3.z), v4.z);
  temp2 = min(min(min(v5.z, v6.z), v7.z), v8.z);
  bbox.z_min = min(temp1, temp2);

  temp1 = max(max(max(v1.z, v2.z), v3.z), v4.z);
  temp2 = max(max(max(v5.z, v6.z), v7.z), v8.z);
  bbox.z_max = max(temp1, temp2);

}