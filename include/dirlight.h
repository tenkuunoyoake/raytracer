#ifndef DIRLIGHT_H
#define DIRLIGHT_H
#endif

#ifndef VECTOR_H
#include "vector.h"
#endif

#ifndef LIGHT_H
#include "light.h"
#endif

//*****************************************************************************
// DirLight
//*****************************************************************************

class DirLight: public Light {

  public:
    
    // Declarations
    Vector direction;
    
    // Constructors
    DirLight();
    DirLight(Vector direction, Vector color);
    
};