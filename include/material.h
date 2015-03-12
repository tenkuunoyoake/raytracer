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
    Vector diffuseC(Vector, Vector, Vector, Vector);
    Vector ambientC(Vector, Vector);
    Vector specularC(Vector, Vector, Vector, Vector, Vector, float);
    
};

