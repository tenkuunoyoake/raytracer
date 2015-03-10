#include <sampler.h>

using namespace std;

//*****************************************************************************
// Sampler
//*****************************************************************************

Vector Sampler::get_Point(Camera* camera, int i, int j, int width, int height) {

  // ASSUMING A FLAT VIEWING PLANE (IE NOT CURVED)

  // Find coords of center of pixel in viewing plane
  Vector left = camera.uLeft + ((float) j + 0.5) * (camera.lLeft - camera.uLeft) / height;
  Vector right = camera.uRight + ((float) j + 0.5) * (camera.lRight - camera.uRight) / height;
  Vector result = left + ((float) i + 0.5) * (right - left);

  return result;

}