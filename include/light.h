#ifndef LIGHT_H
#define LIGHT_H
#endif

#ifndef RAY_H
#include <ray.h>
#endif

#ifndef VECTOR_H
#include <vector.h>
#endif

//*****************************************************************************
// Light
//*****************************************************************************

class Light {
    
  public:
    
    Vector color;
    void generateLightRay();
    
};
