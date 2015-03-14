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
    float phong_e;
    
    // Constructors
    
    Material();
    Material(Vector ka, Vector kd, Vector ks, Vector kr, float phong_e);

    //methods
    // Vector reflection_v(Vector direction, Vector normal);
    Vector diffuse_c(Vector, Vector, Vector);
    Vector ambient_c(Vector);
    Vector specular_c(Vector, Vector, Vector, Vector);
    
};

