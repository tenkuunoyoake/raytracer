#include "raytracer.h"

//*****************************************************************************
// Raytracer
//*****************************************************************************

Vector Raytracer::reflection_v(Vector direction, Vector normal) {

  Vector reflection;    
  Vector scaled_normal;

  reflection = -1 * direction;

  float normal_scalar = 2 * Vector::dot(direction, normal);

  reflection = reflection + (normal * normal_scalar); 
  reflection = reflection.normalize();

  return reflection;

}

bool Raytracer::shadow_ray(Scene* scene, Ray ray) {

  for (unsigned i = 0; i < scene->surfaces.size(); i++) {
    if (scene->surfaces[i]->intersect(ray)) {
      return true;
    }
  }

  return false;

}

void Raytracer::shine_dir_lights(Vector *color, Scene* scene, Material material, 
    Vector surface, Vector viewer, Vector normal) {

  // Iterate through directional lights
  for (unsigned i = 0; i < scene->dir_lights.size(); i++) {

    // Get current directional light
    DirLight dir_light = scene->dir_lights[i];
    // Have direction of light->surface, want direction of surface->light
    Vector light_direction = -1 * dir_light.direction;

    // Dodge shadows
    Ray light_ray = Ray(surface, light_direction, 0.001, 10000);

    if (shadow_ray(scene, light_ray)) {
      continue;
    }

    Vector diffuse_color = material.diffuse_c(dir_light.color, light_direction, 
        normal);
    Vector specular_color = material.specular_c(dir_light.color, 
        light_direction, viewer, normal);

    *color = *color + diffuse_color + specular_color;

  }

}

void Raytracer::shine_point_lights(Vector *color, Scene* scene, 
    Material material, Vector surface, Vector viewer, Vector normal) {

  // Iterate through point lights
  for (unsigned i = 0; i < scene->point_lights.size(); i++) {

    PointLight point_light = scene->point_lights[i];

    Vector light_direction = point_light.position - surface;
    light_direction = light_direction.normalize();

    light_direction = -1 * light_direction;

    // Dodge shadows
    Ray light_ray = Ray(surface, light_direction, 0.001, 10000);

    if (shadow_ray(scene, light_ray)) {
      continue;
    }

    Vector diffuse_color = material.diffuse_c(point_light.color, light_direction, 
        normal);
    Vector specular_color = material.specular_c(point_light.color, 
        light_direction, viewer, normal);

    if (diffuse_color.x != 0 || diffuse_color.y > 0.0001 || diffuse_color.z > 0.0001) {
      Vector::print(diffuse_color);
    }

    *color = *color + diffuse_color + specular_color;

  }
        
}

void Raytracer::shine_ambient_lights(Vector *color, Scene* scene, 
    Material material) {
 
  // Iterate through ambient lights
  for (unsigned i = 0; i < scene->ambient_lights.size(); i++) {
    Light ambient_light = scene->ambient_lights[i];
    *color = *color + material.ambient_c(ambient_light.color);
  }
  
}

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

  Vector intersect = closest_shape->intersectP(view_ray);
  Vector normal = closest_shape->get_normal(intersect); 

  Vector viewer = view_ray.position - intersect;
  viewer = viewer.normalize();

  shine_dir_lights(color, scene, closest_shape->material, intersect, viewer, 
      normal);
  shine_point_lights(color, scene, closest_shape->material, intersect, viewer,
      normal);
  shine_ambient_lights(color, scene, closest_shape->material);

   // Do the reflection thing
  if (closest_shape->material.reflective.x > 0 || 
      closest_shape->material.reflective.y > 0 ||
      closest_shape->material.reflective.z > 0) {

    Vector reflec_color;

    float normal_scale = Vector::dot(view_ray.direction, normal) * 2;
    Vector reflection = view_ray.direction - (normal * normal_scale); 

    Ray reflec_ray = Ray(intersect, reflection, 0.01, 10000);

    trace(scene, reflec_ray, depth + 1, &reflec_color);
    reflec_color = Vector::point_multiply(closest_shape->material.reflective, 
        reflec_color);

    *color = *color + reflec_color;

  }

  color->clamp();

}