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

bool Raytracer::shadow_ray(Scene* scene, Ray ray, Shape* shape) {

  Shape* surface = scene->bbox_tree->intersect_object(ray, shape);
  return (surface != NULL);

}

void Raytracer::shine_dir_lights(Shape* shape, Vector *color, Scene* scene, 
    Material material, Vector surface, Vector viewer, Vector normal) {

  // Iterate through directional lights
  for (unsigned i = 0; i < scene->dir_lights.size(); i++) {

    // Get current directional light
    DirLight dir_light = scene->dir_lights[i];
    // Have direction of light->surface, want direction of surface->light
    Vector light_direction = -1 * dir_light.direction;

    // Dodge shadows
    Ray light_ray = Ray(surface, light_direction, 0, 10000);

    if (shadow_ray(scene, light_ray, shape)) {
      continue;
    }

    Vector diffuse_color = material.diffuse_c(dir_light.color, light_direction, 
        normal);
    Vector specular_color = material.specular_c(dir_light.color, 
        light_direction, viewer, normal);

    *color = *color + diffuse_color + specular_color;

  }

}

void Raytracer::shine_point_lights(Shape *shape, Vector *color, Scene* scene, 
    Material material, Vector surface, Vector viewer, Vector normal) {

  // Iterate through point lights
  for (unsigned i = 0; i < scene->point_lights.size(); i++) {

    PointLight point_light = scene->point_lights[i];

    Vector light_direction = point_light.position - surface;
    float light_distance = light_direction.len();

    light_direction = light_direction.normalize();

    // Dodge shadows
    Ray light_ray = Ray(surface, light_direction, 0, 10000);

    if (shadow_ray(scene, light_ray, shape)) {
      continue;
    }

    Vector diffuse_color = material.diffuse_c(point_light.color, light_direction, 
        normal);
    Vector specular_color = material.specular_c(point_light.color, 
        light_direction, viewer, normal);

    switch (point_light.falloff) {
      case 1:
        diffuse_color = diffuse_color / light_distance;
        specular_color = specular_color / light_distance;
        break;
      case 2:
        diffuse_color = diffuse_color / (light_distance * light_distance);
        specular_color = specular_color / (light_distance * light_distance);
        break;
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

void Raytracer::trace(Scene* scene, Ray view_ray, int depth, Vector* color,
    Shape* last_shape) {

  if (depth > max_depth) {
    *color = Vector(0.0, 0.0, 0.0);
    return;
  }
  
  Shape* closest_shape = scene->bbox_tree->intersect_object(view_ray, last_shape);

  if (closest_shape == NULL) {
    *color = Vector();
    return;
  }

  Vector intersect = closest_shape->intersectP(view_ray);
  Vector normal = closest_shape->get_normal(intersect); 

  Vector viewer = view_ray.position - intersect;
  viewer = viewer.normalize();

  shine_dir_lights(closest_shape, color, scene, closest_shape->material,
    intersect, viewer, normal);
  shine_point_lights(closest_shape, color, scene, closest_shape->material, 
      intersect, viewer, normal);

  if (depth < 1) {
    shine_ambient_lights(color, scene, closest_shape->material);
  }

   // Do the reflection thing
  if (!(closest_shape->material.refract &&
      closest_shape->material.reflective.x) > 0 || 
      closest_shape->material.reflective.y > 0 ||
      closest_shape->material.reflective.z > 0) {

    Vector reflec_color;

    float normal_scale = Vector::dot(view_ray.direction, normal) * 2;
    Vector reflection = view_ray.direction - (normal * normal_scale); 

    Ray reflec_ray = Ray(intersect, reflection, 0, 10000);

    trace(scene, reflec_ray, depth + 1, &reflec_color, closest_shape);
    reflec_color = Vector::point_multiply(closest_shape->material.reflective, 
        reflec_color);

    *color = *color + reflec_color;
  }

  // Do the refraction thing
  if(closest_shape->material.refract){
    Vector dir = view_ray.direction.normalize();
    float dn = Vector::dot(dir, normal);
    bool skipR = false;
    Vector kvector;
    float c;
    Ray refracted;
    if(dn < 0) {
      refracted = refract(dir, normal, closest_shape->material.glassIndex, closest_shape->material, intersect); //returns t
      c = -1.0*dn;
      kvector = Vector(1,1,1);
      //printf("%f\n", closest_shape->material.glassIndex);
    }
    else {
      Vector partial = Vector(0.2, 0.2, 0.2);
      //Vector::print(partial);
      kvector = Vector(expf(partial.x), expf(partial.y), expf(partial.z));
      if(canRefract(dir, -1.0*normal, 1/closest_shape->material.glassIndex, closest_shape->material)) {
        refracted = refract(dir, -1.0*normal, 1/closest_shape->material.glassIndex, closest_shape->material, intersect);
        c = Vector::dot(refracted.direction.normalize(), normal);
      }
      else{
        Vector d_color = Vector(0,0,0);
        trace(scene, view_ray, depth + 1, &d_color, closest_shape);
        *color = *color + Vector::point_multiply(kvector, d_color);
        skipR = true;
      }
    }
    if(!skipR){
      float R0 = pow((closest_shape->material.glassIndex - 1), 2) / pow((closest_shape->material.glassIndex + 1), 2);
      float Rk = R0 + (1-R0)*pow(1-c, 5);
      Vector d_color = Vector(0,0,0);
      trace(scene, view_ray, depth + 1, &d_color, closest_shape);
      Vector r_color = Vector(0,0,0);
      trace(scene, refracted, depth + 1, &r_color, closest_shape);
      Vector part1 = Vector::point_multiply(kvector, d_color);
      Vector part2 = Vector::point_multiply(kvector, r_color);
      *color = *color + Rk*part1 + (1-Rk)*part2;
    }
   




  }

  color->clamp();

}

bool Raytracer::canRefract(Vector direction, Vector normal, float ind, Material material) {
  float n = 1/ind;
  Vector norm = normal;
  Vector D =  direction;
  float cos1 = -1*Vector::dot(D, norm); // -(n dot d)
  float cos2 = 1.0 - n*n*(1 -cos1*cos1); //that thing under the root
  return cos2 > 0.0;
}

Ray Raytracer::refract(Vector direction, Vector normal, float ind, Material material, Vector intersect) {
     //do refract
    float n = 1/ind;
    float cos1 = Vector::dot(direction, normal); // n dot d)
    float cos2 = 1.0 - n*n*(1 -cos1*cos1); //that thing under the root
    if(cos2 > 0.0){
      Vector part1 = direction - cos1*normal;
      Vector newD = n*part1 - sqrt(cos2) * normal;
      Ray refract_ray = Ray(intersect, newD, 0, 10000);
      return refract_ray;
    }
    return Ray(intersect, direction, 0, 10000);
}