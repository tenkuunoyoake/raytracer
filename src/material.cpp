#include "material.h"

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