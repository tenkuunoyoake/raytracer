#include "sampler.h"

using namespace std;

//*****************************************************************************
// Sampler
//*****************************************************************************

void Sampler::get_points(vector<Vector>* points, Camera* camera, int i, int j, int width, int height) {

  // ASSUMING A FLAT VIEWING PLANE (IE NOT CURVED)

  // Find coords of center of pixel in viewing plane
  Vector left = camera->uLeft + (camera->lLeft - camera->uLeft) * (j + 0.5f) / height;
  Vector right = camera->uRight + (camera->lRight - camera->uRight) * (j + 0.5f) / height;
  Vector result = left + (right - left) * (i + 0.5f) / width;

  points->push_back(result);

}