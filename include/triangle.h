#ifndef TRIANGLE_H
#define TRIANGLE_H
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

class Triangle{
	public:
		//declarations
		Matrix transform;
		Vector color;
		Vector v1;
		Vector v2;
		Vector v3;
		
		
		//constructors
		Triangle();
		Triangle(Matrix, Vector, Vector, Vector, Vector);

		bool intersect(Ray);
		Vector getNormal();
		Vector intersectP(Ray);
		Vector getNormalisedNormal();

};
