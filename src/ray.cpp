#include <ray.h>

Ray::Ray() {
  
  position = Vector(0, 0, 0);
  direction = Vector(0, 0, 0);
  t_min = 0;
  t_max = 0;
  
}

Ray::Ray(Vector pos, Vector dir, float min, float max) {
  
  position = pos;
  direction = dir;
  t_min = min;
  t_max = max;
  
}