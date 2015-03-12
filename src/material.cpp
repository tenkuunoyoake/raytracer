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