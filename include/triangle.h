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

#ifndef MATERIAL_H
#include <material.h>
#endif

using namespace std;

class Triangle{

	public:
		//declarations
		Matrix transform;
		Material material;
		Vector v1;
		Vector v2;
		Vector v3;
		
		
		//constructors
		Triangle();
		Triangle(Matrix, Vector, Vector, Vector, Material material);

		bool intersect(Ray);
		float intersectT(Ray ray);
		Vector intersectP(Ray);

		Vector getNormal();

};
