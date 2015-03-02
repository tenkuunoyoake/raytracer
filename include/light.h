#ifndef LIGHT_H
#define LIGHT_H
#endif

#ifndef RAY_H
#include <ray.h>
#endif

#ifndef VECTOR_H
#include <vector.h>
#endif

#ifndef MATRIX_H
#include <matrix.h>
#endif

//*****************************************************************************
// Light
//*****************************************************************************

class Light {
    
  public:
    
    // Members
    Vector color;
    Matrix transform;
    
    // Methods
    void generate_light_ray(Ray* light_ray, Vector *light_colour);
    void set_transform(Matrix l_transform);
    
    // Constructors
    Light();
    
};
