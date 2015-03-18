#include "scene.h"

#ifndef RAYTRACER_H
#include "raytracer.h"
#endif

//*****************************************************************************
// Scene
//*****************************************************************************

void Scene::add_surface(Shape* surface) {

  surfaces.push_back(surface);

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
  #pragma omp parallel for
  for (int j = 0; j < film.height; j++) {
    for (int i = 0; i < film.width; i++) {
      
      vector<Vector> view_points;

      Vector pixel_color;
      Vector final_color;

      Ray view_ray;
      view_ray.position = camera.origin;
      
      // Compute viewing ray
      Sampler::get_points(&view_points, &camera, i, j, film.width, film.height);

      while (!view_points.empty()) {

        view_ray.direction = (view_points.back() - camera.origin);
        view_ray.t_min = 0;
        view_ray.t_max = 10000; 

        Raytracer::trace(this, view_ray, 0, &pixel_color, NULL);

        final_color = final_color + pixel_color;
        
        // Make sure to reset the colour of the pixel
        pixel_color = Vector();

        view_points.pop_back();

      }

      final_color = final_color / (Sampler::samples * Sampler::samples);
      film.set_pixel(i, j, final_color);

    }
  }
  
  film.write_to_image();

}

vector<Shape*> Scene::sort_shapes(vector<Shape*> shapes, int axis) {

  vector<Shape*> result(shapes);

  // Base case
  if (shapes.size() <= 1) {
    return result;
  }

  vector<Shape*> left_list;
  vector<Shape*> right_list;

  // Choose a pivot item v from I

  unsigned pivot_i = rand() % shapes.size();
  Shape* pivot = shapes[pivot_i];

  for (unsigned i = 0; i < shapes.size(); i++) {

    if (i == pivot_i) {
      continue;
    }

    // Partition I into two unsorted lists I1 and I2.

    switch(axis) {

      case 0:
        if (shapes[i]->bbox.x_max < pivot->bbox.x_max) {
          left_list.push_back(shapes[i]);
        } else {
          right_list.push_back(shapes[i]);
        }
        break;

      case 1:
        if (shapes[i]->bbox.y_max < pivot->bbox.y_max) {
          left_list.push_back(shapes[i]);
        } else {
          right_list.push_back(shapes[i]);
        }
        break;

      case 2:
        if (shapes[i]->bbox.z_max < pivot->bbox.z_max) {
          left_list.push_back(shapes[i]);
        } else {
          right_list.push_back(shapes[i]);
        }
        break;

    }

  }

  // Sort left and right lists recursively

  left_list = sort_shapes(left_list, axis);
  right_list = sort_shapes(right_list, axis);

  // Concatenate S1, v, and S2 together, yielding a sorted list S.

  for (unsigned i = 0; i < shapes.size(); i++) {
    if (i < left_list.size()) {
      result[i] = left_list[i];
    } else if (i == left_list.size()) {
      result[i] = pivot;
    } else {
      result[i] = right_list[i - left_list.size() - 1];
    }
  }

  return result;

}

void Scene::create_bbox_tree() {

  // Still a WIP

  /*

  vector<Shape*> x_sorted;
  vector<Shape*> y_sorted;
  vector<Shape*> z_sorted;

  x_sorted = sort_shapes(surfaces, 0);
  y_sorted = sort_shapes(surfaces, 1);
  z_sorted = sort_shapes(surfaces, 2);

  printf("X Sorted:\n");
  for (unsigned i = 0; i < surfaces.size(); i++) {

    printf("%f\n", x_sorted[i]->bbox.x_max);

  }

  printf("Y Sorted:\n");
  for (unsigned i = 0; i < surfaces.size(); i++) {

    printf("%f\n", y_sorted[i]->bbox.y_max);
    
  }

  printf("Z Sorted:\n");
  for (unsigned i = 0; i < surfaces.size(); i++) {

    printf("%f\n", z_sorted[i]->bbox.z_max);
    
  }

  */


}

void Scene::dispose() {
 
  film.dispose();
  
}