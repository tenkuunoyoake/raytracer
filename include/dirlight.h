#ifndef LIGHT_H
#include <light.h>
#endif

#ifndef VECTOR_H
#include <vector.h>
#endif

//*****************************************************************************
// DirLight
//*****************************************************************************

class DirLight: public Light {

  public:
    
    Vector direction;
    DirLight(Vector color, Vector direction);
    
};