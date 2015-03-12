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

#ifndef MATERIAL_H
#include <material.h>
#endif

using namespace std;

//*****************************************************************************
// Sphere
//*****************************************************************************

class Sphere {

	public:
		//declarations
		Vector center;
		float radius;

		Matrix transform;
		Material material;

		//constructors
		Sphere();
		Sphere(Matrix, Vector, float, Material material);

		bool intersect(Ray);
		Vector intersectP(Ray);
		float intersectT(Ray ray);

};
