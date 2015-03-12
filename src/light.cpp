#include "light.h"

//*****************************************************************************
// Light
//*****************************************************************************

Light::Light() {
 
  color = Vector(0, 0, 0);
  transform = Matrix::identity_matrix();
  
}

// This should take in a local geometry object, and spit out a light ray
void Light::generate_light_ray(Ray* light_ray, Vector *light_color) {
  
}

void Light::set_transform(Matrix l_transform) {
  
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      transform.set_value(i, j, l_transform.get_value(i, j));
    }
  }
  
}