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

		// Method Overloads
		bool intersect(Ray);
    Vector intersectP(Ray);
    float intersectT(Ray ray);

		//constructors
		Triangle();
		Triangle(Matrix, Vector, Vector, Vector, Material material);

		Vector getNormal();

};
