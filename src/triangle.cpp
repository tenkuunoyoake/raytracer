#include <triangle.h>
#include <cmath>
#include <limits>
#include <math.h>

Triangle::Triangle(){
	transform = Matrix::identity_matrix();
	color = Vector(0, 0, 0);
	v1 = Vector(1, 0, 0);
	v2 = Vector(0, 1, 0);
	v3 = Vector(0, 0, 1);
}

Triangle::Triangle(Matrix trans, Vector col, Vector point1, Vector point2, Vector point3){
	transform = trans;
	color = col;
	v1 = point1;
	v2 = point2;
	v3 = point3;
}

Vector Triangle::getNormal(){
	Vector U = v2-v1;
	Vector V = v3-v1;
	float nx = U.y*V.z - U.z*V.y;
	float ny = U.z*V.x - U.x*V.z;
	float nz = U.x*V.y - U.y*V.x;
	return Vector(nx, ny, nz);
}

Vector Triangle::getNormalisedNormal(){
	Vector U = v2-v1;
	Vector V = v3-v1;
	float nx = U.y*V.z - U.z*V.y;
	float ny = U.z*V.x - U.x*V.z;
	float nz = U.x*V.y - U.y*V.x;
	float mag = abs(nx) + abs(ny) + abs(nz);
	return Vector(nx/mag, ny/mag, nz/mag);
}

bool Triangle::intersect(Ray ray){
	Vector pos = ray.position;
	Vector dir = ray.direction;
	float min = ray.t_min;
	float max = ray.t_max;
	Vector e1 = v2-v1;
	Vector e2 = v3-v1;
	Vector s = pos-v1;
	Vector p = Vector::cross(dir, e2);
	Vector q = Vector::cross(s, e1);
	float a = Vector::dot(p, e1);
	if(a == 0){
		return false;
	}
	float beta = (1/a)*(Vector::dot(s,p));
	float gamma = (1/a)*(Vector::dot(dir,q));
	float t = (1/a)*(Vector::dot(e2,q));
	printf("Somethign cool: %f\n", t);
	if(beta < 0.0 || gamma < 0 || beta > 1 || gamma > 1 || beta + gamma > 1 || t > max || t < min){
		return false;
	}
	else{
		return true;
	}
}

Vector Triangle::intersectP(Ray ray){
	Vector pos = ray.position;
	Vector dir = ray.direction;
	float min = ray.t_min;
	float max = ray.t_max;
	Vector e1 = v2-v1;
	Vector e2 = v3-v1;
	Vector s = pos-v1;
	Vector p = Vector::cross(dir, e2);
	Vector q = Vector::cross(s, e1);
	float a = Vector::dot(p, e1);
	if(a == 0){
		printf("This shouldn't be printing check if you passed ur things right.");
		return Vector(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
	}
	float t = (1/a)*(Vector::dot(e2,q));
	if(t >= min && t <= max){
		return Vector(pos.x + dir.x*t, pos.y + dir.y*t, pos.z + dir.z*t);
	}
	else{
		return Vector(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
	}
}