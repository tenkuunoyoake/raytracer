#include "dirlight.h"

DirLight::DirLight() {
 
  transform = Matrix::identity_matrix();
  
}

DirLight::DirLight(Vector l_direction, Vector l_color) {
  
  color = l_color;
  // Make sure the things are normalised
  direction = l_direction.normalize();
  transform = Matrix::identity_matrix();
  
}
