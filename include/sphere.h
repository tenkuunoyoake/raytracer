#ifndef SPHERE_H
#define SPHERE_H
#endif

#ifndef VECTOR_H
#include <vector.h>
#endif

#ifndef MATRIX_H
#include <matrix.h>
#endif

#ifndef RAY_H
#include <ray.h>
#endif


class Sphere{
	public:
		//declarations
		Matrix transform;
		Vector center;
		Vector color;
		float radius;
		//constructors
		Sphere();
		Sphere(Matrix, Vector, Vector, float);

		bool intersect(Ray);
		Vector intersectP(Ray);

};
