#include <scene.h>

using namespace std;

//*****************************************************************************
// Scene
//*****************************************************************************

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
  
  /*
  int noise = 1; // Temp
  Ray* view_rays = (Ray*) malloc(noise * sizeof(Ray));
  */

  // For each pixel do:
  for (int j = 0; j < film.height; j++) {
    for (int i = 0; i < film.width; i++) {

      // Not sure which one to use... probably Elbert's for now since it 
      // seems more stable for correct inputs

      /*
      camera.compute_viewing_rays(view_rays, noise, i, j, film.width,
          film.height);
      */

      Ray view_ray;
      view_ray.position = camera.origin;
      
      // Compute viewing ray
      Sampler::get_points(&view_points, &camera, i, j, film.width, film.height);

      while (!view_points.empty()) {
        view_ray.direction = view_points.back() - camera.origin;
        view_points.pop_back();
      }

      // Find first object hit by ray and its surface normal n
      
      // Set pixel colour to value computed from hit point, light, and n

      // Looks cool for now
      film.set_pixel(i, j, Vector(i / 255.0, j / 255.0, 0.0));

    }
  }
  
  film.write_to_image();

  //free(view_rays);

}

void Scene::dispose() {
 
  film.dispose();
  
}