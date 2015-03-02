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
    
    Vector position;
    PointLight(Vector color, Vector position);
    
};