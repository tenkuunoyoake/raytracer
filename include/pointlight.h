#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#endif

#ifndef LIGHT_H
#include <light.h>
#endif

#ifndef VECTOR_H
#include <vector.h>
#endif

//*****************************************************************************
// PointLight
//*****************************************************************************

class PointLight: public Light {

  public:
    
    // Members
    int falloff;
    Vector position;
    
    // Constructors
    PointLight();
    PointLight(Vector color, Vector position, int falloff);
    
};