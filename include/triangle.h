#ifndef TRIANGLE_H
#define TRIANGLE_H
#endif

#ifndef SHAPE_H
#include "shape.h"
#endif

#ifndef VECTOR_H
#include "vector.h"
#endif

using namespace std;

class Triangle : public Shape {

  public:
    //declarations
    Vector v1;
    Vector v2;
    Vector v3;
    Vector vnorm1;
    Vector vnorm2;
    Vector vnorm3;
    Vector tcoord1;
    Vector tcoord2;
    Vector tcoord3;

    // Method Overloads
    bool intersect(Ray);
    Vector intersectP(Ray);
    float intersectT(Ray ray);
    Vector get_normal(Vector intersection);

    void do_transform(Matrix matrix);

    //constructors
    Triangle();
    Triangle(Matrix, Vector, Vector, Vector, Material);
    Triangle(Matrix, Vector, Vector, Vector, Vector, Vector, Vector,
        Vector, Vector, Vector, Material);

};
