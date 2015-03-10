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
  
  // For each pixel do:
  for (int j = 0; j < film.height; j++) {
    for (int i = 0; i < film.width; i++) {
      
      // Compute viewing ray
      // Might be buggy..?
      Ray view_ray = camera.compute_viewing_ray(i, j, film.width, film.height);
      
      if (i == 0 && j == 0) {
	      Ray::print(view_ray);
      }
      
      // Find first object hit by ray and its surface normal n
      
      // Set pixel colour to value computed from hit point, light, and n
     
      // Looks cool for now
      film.set_pixel(i, j, Vector(i / 255.0, j / 255.0, 0.0));
      
    }
  }
  
  film.write_to_image();
  
}

void Scene::dispose() {
 
  film.dispose();
  
}