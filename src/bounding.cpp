#include "bounding.h"

using namespace std;

//*****************************************************************************
// BoundingBox
//*****************************************************************************

bool BoundingBox::intersect(Ray ray) {

  float t_min;
  float t_max;

  float a = 1 / ray.direction.x;
  float b = 1 / ray.direction.y;
  float c = 1 / ray.direction.z;

  float tx_min = (x_min - ray.position.x) * a;
  float tx_max = (x_max - ray.position.x) * a;
  float ty_min = (y_min - ray.position.y) * b;
  float ty_max = (y_max - ray.position.y) * b;
  float tz_min = (z_min - ray.position.z) * c;
  float tz_max = (z_max - ray.position.z) * c;

  t_min = max(min(tx_min, tx_max), min(ty_min, ty_max));
  t_min = max(t_min, min(tz_min, tz_max));

  t_max = min(max(tx_min, tx_max), max(ty_min, ty_max));
  t_max = min(t_max, max(tz_min, tz_max));

  if (t_min < 0) {
    return false;
  }

  if (t_min > t_max) {
    return false;
  }

  return true;

}