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
  
  for (int j = 0; j < film.height; j++) {
    for (int i = 0; i < film.width; i++) {
     
      // Looks cool for now
      film.set_pixel(i, j, Vector(i / 255.0, j / 255.0, 0.0));
      
    }
  }
  
  film.write_to_image();
  
}

void Scene::dispose() {
 
  film.dispose();
  
}