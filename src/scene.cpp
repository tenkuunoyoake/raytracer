#include <scene.h>

using namespace std;

//*****************************************************************************
// Scene
//*****************************************************************************

void Scene::add_sphere(Sphere sphere) {

  spheres.push_back(sphere);

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

      Ray view_ray;
      view_ray.position = camera.origin;
      
      // Compute viewing ray
      Sampler::get_points(&view_points, &camera, i, j, film.width, film.height);

      while (!view_points.empty()) {

        view_ray.direction = view_points.back() - camera.origin;
        view_ray.t_min = 0;
        // Should NOT be infinity (for some reason)
        view_ray.t_max = 10000; 

        // Find first object hit by ray and its surface normal n

        // Set pixel colour to value computed from hit point, light, and n
        // For now, just set it to red.
        for (unsigned sphere_i = 0; sphere_i < spheres.size(); sphere_i++) {

          // Really, should only choose the one with the lowest t-value
          if (spheres[sphere_i].intersect(view_ray)) {
            film.set_pixel(i, j, Vector(1.0, 0.0, 0.0));
          } else {
            film.set_pixel(i, j, Vector(0.0, 0.0, 0.0));
          }

        }

        view_points.pop_back();

      }

    }
  }
  
  film.write_to_image();

}

void Scene::dispose() {
 
  film.dispose();
  
}