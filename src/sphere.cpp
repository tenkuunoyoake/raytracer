#include <sphere.h>
#include <cmath>
#include <limits>
#include <math.h>

Sphere::Sphere(){
	transform = Matrix::identity_matrix();
	center = Vector(0, 0, 0);
	color = Vector(0, 0, 0);
	radius = 1;
}

Sphere::Sphere(Matrix trans, Vector cen, Vector col, float rad){
	transform = trans;
	center = cen;
	color = col;
	radius = rad;
}

bool Sphere::intersect(Ray ray){
	Vector pos = ray.position;
	Vector dir = ray.direction;
	float min = ray.t_min;
	float max = ray.t_max;
	float a = pow(dir.x, 2) + pow(dir.y, 2) + pow(dir.z, 2);
	float b = 2*(pos.x - center.x)*dir.x + 2*(pos.y - center.y)*dir.y + 2*(pos.z - center.z)*dir.z;
	float c = pow(pos.x - center.x, 2) + pow(pos.y - center.y, 2) + pow(pos.z - center.z, 2) - radius*radius;

	float discriminant = b*b - 4*a*c;
	float t1 = (-1*b - sqrt(discriminant))/(2*a);
	float t2 = (-1*b + sqrt(discriminant))/(2*a);
	
	if(t1 > max || t1 < min || t2 > max || t2 < min){
		return false;
	}
	if(discriminant >= 0) { 
		return true;
	} else{
		return false;
	}
}

Vector Sphere::intersectP(Ray ray){
	Vector pos = ray.position;
	Vector dir = ray.direction;
	float min = ray.t_min;
	float max = ray.t_max;
	float a = pow(dir.x, 2) + pow(dir.y, 2) + pow(dir.z, 2);
	float b = 2*(pos.x - center.x)*dir.x + 2*(pos.y - center.y)*dir.y + 2*(pos.z - center.z)*dir.z;
	float c = pow(pos.x - center.x, 2) + pow(pos.y - center.y, 2) + pow(pos.z - center.z, 2) - radius*radius;

	printf("Sometang a: %f\n", a);
	printf("Sometang b: %f\n", b);
	printf("Sometang c: %f\n", c);
	printf("Sometang rad: %f\n", radius);
	float discriminant = b*b - 4*a*c;
	printf("Sometang discrim: %f\n", discriminant);
	if(discriminant >= 0){
		float t1 = (-1*b - sqrt(discriminant))/(2*a);
		float t2 = (-1*b + sqrt(discriminant))/(2*a);
		printf("Sometang t1: %f\n", t1);
		printf("Sometang t2: %f\n", t2);

		if(t1 >= min && t1 <= max){
			return Vector(pos.x + dir.x*t1, pos.y + dir.y*t1, pos.z + dir.z*t1);
		}
		else if(t2 >= min && t2 <= max){
			return Vector(pos.x + dir.x*t2, pos.y + dir.y*t2, pos.z + dir.z*t2);
		}
		else{
			//if nothing works within the t range just return infinity lol
			return Vector(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
		}
	}
	else{
		printf("This shouldn't be printing check if you passed ur things right.\n");
		return Vector(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
	}
}
