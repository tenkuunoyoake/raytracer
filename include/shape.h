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

#ifndef BOUNDING_H
#include "bounding.h"
#endif

using namespace std;

//*****************************************************************************
// Shape
//*****************************************************************************

class Shape {

  public:

    Matrix transform;
    Material material;

    BoundingBox bbox;

    virtual bool intersect(Ray) =0;
    virtual Vector intersectP(Ray) =0;
    virtual float intersectT(Ray ray) =0;
    virtual Vector get_normal(Vector intersection) =0;
    virtual void compute_bounding_box() =0;

};
