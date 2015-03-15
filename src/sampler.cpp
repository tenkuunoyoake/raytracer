#include "sampler.h"

using namespace std;

//*****************************************************************************
// Sampler
//*****************************************************************************

void Sampler::get_points(vector<Vector>* points, Camera* camera, int i, int j, int width, int height) {

  // ASSUMING A FLAT VIEWING PLANE (IE NOT CURVED)

  // Find coords of center of pixel in viewing plane

  // Declarations

  Vector left;
  Vector right;
  Vector result;

  // Generate x * y random samples 

  for (int y = 0; y < samples; y++) {
    for (int x = 0; x < samples; x++) {

      float off_x = (x + (((float) rand()) / RAND_MAX)) / samples;
      float off_y = (y + (((float) rand()) / RAND_MAX)) / samples; 

      left = camera->uLeft + (camera->lLeft - camera->uLeft) * (j + off_y) / height;
      right = camera->uRight + (camera->lRight - camera->uRight) * (j + off_y) / height;
      result = left + (right - left) * (i + off_x) / width;

      points->push_back(result);

    }
  }  

}