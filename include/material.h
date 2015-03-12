#ifndef MATERIAL_H
#define MATERIAL_H
#endif

#ifndef VECTOR_H
#include "vector.h"
#endif

//****************************************************
// Material
//****************************************************

class Material {

  public:
    
    // Public Instance Variables
    
    Vector ambient;
    Vector diffuse;
    Vector specular;
    Vector reflective;
    
    // Constructors
    
    Material();
    Material(Vector ka, Vector kd, Vector ks, Vector kr);
    
};

