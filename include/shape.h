#ifndef SHAPE_H
#define SHAPE_H
#endif

#ifndef RAY_H
#include "ray.h"
#endif

#ifndef MATRIX_H
#include "matrix.h"
#endif

#ifndef MATERIAL_H
#include "material.h"
#endif

using namespace std;

//*****************************************************************************
// Shape
//*****************************************************************************

class Shape {

  public:

    Matrix transform;
    Material material;

    virtual bool intersect(Ray) =0;
    virtual Vector intersectP(Ray) =0;
    virtual float intersectT(Ray ray) =0;

};
