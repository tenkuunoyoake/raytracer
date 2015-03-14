#include "material.h"

#include <algorithm>

using namespace std;

//****************************************************
// Material
//****************************************************

Material::Material() {
  
  ambient = Vector(0, 0, 0);
  diffuse = Vector(0, 0, 0);
  specular = Vector(0, 0, 0);
  reflective = Vector(0, 0, 0);
  phong_e = 0.0f;
  
}

Material::Material(Vector ka, Vector kd, Vector ks, Vector kr, float pe) {
 
  ambient = ka;
  diffuse = kd;
  specular = ks;
  reflective = kr;
  phong_e = pe;
  
}

Vector Material::diffuse_c(Vector color, Vector light, Vector normal) {

  float similarity = Vector::dot(light, normal) / (light.len() * normal.len());

  if (similarity < 0) {
    return Vector();
  }

  float result = Vector::dot(light, normal);
  Vector final = Vector::point_multiply(diffuse, color) * result; 
  return final;

}

Vector Material::ambient_c(Vector color) {

  return Vector::point_multiply(ambient, color);

}

/*

Vector Material::reflection_v(Vector direction, Vector normal) {

  Vector reflection;    
  Vector scaled_normal;

  reflection = -1 * direction;

  float normal_scalar = 2 * Vector::dot(direction, normal);

  reflection = reflection + (normal * normal_scalar); 
  reflection = reflection.normalize();

  return reflection;

}

Vector Material::specular_c(Vector light_color, Vector light_direction,
    Vector viewer, Vector normal) {

  // C = Ks * I * (r . v) ^ p

  Vector reflection = reflection_v(light_direction, normal);

  float intensity = 0;

  if (Vector::dot(normal, light_direction) >= 0.0f) {
    intensity = max(0.0f, Vector::dot(viewer, reflection));
    intensity = pow(intensity, phong_e);
  }

  return Vector::point_multiply(specular, light_color) * intensity;

}

*/

Vector Material::specular_c(Vector color, Vector light, Vector viewer, 
    Vector normal) {

  float dbl = 2.0 * Vector::dot(light, normal); 
  Vector r = dbl * normal;
  Vector rb = r + -1 * light;

  float similarity = (Vector::dot(rb, viewer)) / (rb.len() * viewer.len());

  if (similarity < 0) {
    return Vector();
  } 

  float rbv = Vector::dot(rb, viewer);
  rbv = pow(rbv, phong_e);

  Vector final = Vector::point_multiply(specular, color);
  final = final * rbv;

 return final;

}