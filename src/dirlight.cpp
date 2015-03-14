#include "dirlight.h"

DirLight::DirLight() {
  
}

DirLight::DirLight(Vector l_direction, Vector l_color) {
  
  color = l_color;
  // Make sure the things are normalised
  direction = l_direction.normalize();
  
}
