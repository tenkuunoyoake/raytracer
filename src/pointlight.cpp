#include <pointlight.h>

//*****************************************************************************
// PointLight
//*****************************************************************************

PointLight::PointLight(Vector l_color, Vector l_position, int l_falloff) {
 
  color = l_color;
  position = l_position;
  falloff = l_falloff;
  transform = Matrix::identity_matrix();
  
}
