#include <scene.h>

#ifndef RAYTRACER_H
#include <raytracer.h>
#endif

//*****************************************************************************
// Scene
//*****************************************************************************

void Scene::add_sphere(Sphere sphere) {

  spheres.push_back(sphere);

}

void Scene::add_triangle(Triangle triangle) {

  triangles.push_back(triangle);

}

void Scene::add_dir_light(DirLight dir_light) {
  
  dir_lights.push_back(dir_light);
  
}

void Scene::add_point_light(PointLight point_light) {
  
  point_lights.push_back(point_light);
  
}

void Scene::add_ambient_light(Light ambient_light) {
 
  ambient_lights.push_back(ambient_light);
  
}

void Scene::render() {

  // For each pixel do:
  for (int j = 0; j < film.height; j++) {
    for (int i = 0; i < film.width; i++) {
      
      Vector pixel_color;

      Ray view_ray;
      view_ray.position = camera.origin;
      
      // Compute viewing ray
      Sampler::get_points(&view_points, &camera, i, j, film.width, film.height);

      while (!view_points.empty()) {

        view_ray.direction = view_points.back() - camera.origin;
        view_ray.t_min = 0;
        view_ray.t_max = 10000; 

        Raytracer::trace(this, view_ray, 0, &pixel_color);

        film.set_pixel(i, j, pixel_color);
        view_points.pop_back();

      }

    }
  }
  
  film.write_to_image();

}

void Scene::dispose() {
 
  film.dispose();
  
}