#include <raytracer.h>

//*****************************************************************************
// Raytracer
//*****************************************************************************

void Raytracer::trace(Scene* scene, Ray view_ray, int depth, Vector* color) {

  if (depth > max_depth) {
    *color = Vector(0.0, 0.0, 0.0);
    return;
  }

  float t_min = view_ray.t_max;
  char closest_type = 0;

  Triangle closest_triangle;
  Sphere closest_sphere;

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
        closest_triangle = scene->triangles[tri_i];
        closest_type = 1;
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
        closest_sphere = scene->spheres[sphere_i];
        closest_type = 2;
      }

    }

  }

  switch (closest_type) {
    case 0:
      *color = Vector(0.0, 0.0, 0.0);
      break;
    // Triangle was closest object hit
    case 1:
      *color = closest_triangle.material.diffuse;
      break;
    // Sphere was closest object hit
    case 2:
      *color = closest_sphere.material.diffuse;
      break;
  }

}