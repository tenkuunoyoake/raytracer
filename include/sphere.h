#ifndef SPHERE_H
#define SPHERE_H
#endif

#ifndef VECTOR_H
#include "vector.h"
#endif

#ifndef SHAPE_H
#include "shape.h"
#endif

using namespace std;

//*****************************************************************************
// Sphere
//*****************************************************************************

class Sphere : public Shape {

	public:
		//declarations
		Vector center;
		float radius;

		// Method overloads
		bool intersect(Ray);
    Vector intersectP(Ray);
    float intersectT(Ray ray);

		//constructors
		Sphere();
		Sphere(Matrix, Vector, float, Material material);

};
