#ifndef BOUNDING_H
#define BOUNDING_H
#endif

#include <vector>

#ifndef RAY_H
#include "ray.h"
#endif

using namespace std;

//*****************************************************************************
// BoundingBox
//*****************************************************************************

class BoundingBox {

  public:
    
    // Declarations
    float x_min;
    float x_max;
    float y_min;
    float y_max;
    float z_min;
    float z_max;

    // Methods
    bool intersect(Ray ray);
    static void print(BoundingBox* bbox);

};