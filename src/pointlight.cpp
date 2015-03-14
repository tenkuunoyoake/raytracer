
#include "pointlight.h"

//*****************************************************************************
// PointLight
//*****************************************************************************

PointLight::PointLight() {
  
}

PointLight::PointLight(Vector l_position, Vector l_color, int l_falloff) {
 
  color = l_color;
  position = l_position;
  falloff = l_falloff;
  
}
