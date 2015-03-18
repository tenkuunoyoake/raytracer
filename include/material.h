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
    bool refract;
    static const bool alwaysRf = true;
    float phong_e;
    static const float glassIndex = 1.52;
    static const float airIndex = 1.0;
    
    // Constructors
    
    Material();
    Material(Vector ka, Vector kd, Vector ks, Vector kr, float phong_e, bool refract);

    Vector diffuse_c(Vector, Vector, Vector);
    Vector ambient_c(Vector);
    Vector specular_c(Vector, Vector, Vector, Vector);
    
};

