#include <raytracer.h>

//*****************************************************************************
// Raytracer
//*****************************************************************************

void Raytracer::trace(Scene* scene, Ray view_ray, int depth, Vector* color) {

  if (depth > max_depth) {
    *color = Vector(0.0, 0.0, 0.0);
    return;
  }

  bool hit = false;
  float t_min = view_ray.t_max;

  Shape* closest_shape;

  // Find first object hit by ray and its surface normal n

  // Set pixel colour to value computed from hit point, light, and n
  // For now, just set it to red.

  // For all triangles in the Scene
  for (unsigned tri_i = 0; tri_i < scene->triangles.size(); tri_i++) {

    // If there actually is an intersection
    if (scene->triangles[tri_i].intersect(view_ray)) {

      // If it's the closest object seen thus far
      if (scene->triangles[tri_i].intersectT(view_ray) < t_min) {
        t_min = scene->triangles[tri_i].intersectT(view_ray);
        closest_shape = &(scene->triangles[tri_i]);
        hit = true;
      }

    }

  }

  // For all spheres in the Scene
  for (unsigned sphere_i = 0; sphere_i < scene->spheres.size(); sphere_i++) {

    // If there actually is an intersection
    if (scene->spheres[sphere_i].intersect(view_ray)) {

      // If it's the closest object seen thus far
      if (scene->spheres[sphere_i].intersectT(view_ray) < t_min) {
        t_min = scene->spheres[sphere_i].intersectT(view_ray);
        closest_shape = &(scene->spheres[sphere_i]);
        hit = true;
      }

    }

  }

  if (!hit) {
    *color = Vector(0.0, 0.0, 0.0);
    return;
  }

  *color = closest_shape->material.diffuse;

}