#include "raytracer.h"

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
  for (unsigned shape_i = 0; shape_i < scene->surfaces.size(); shape_i++) {

    // If there actually is an intersection
    if (scene->surfaces[shape_i]->intersect(view_ray)) {

      // If it's the closest object seen thus far
      if (scene->surfaces[shape_i]->intersectT(view_ray) < t_min) {
        t_min = scene->surfaces[shape_i]->intersectT(view_ray);
        closest_shape = scene->surfaces[shape_i];
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