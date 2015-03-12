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

Vector Material::diffuseC(Vector factor, Vector color, Vector light, 
              Vector normal){
  float similarity = (Vector::dot(light, normal))/(Vector::mag(light)*Vector::mag(normal));
  if(similarity < 0) return Vector(0.0, 0.0, 0.0);
  float result = Vector::dot(light, normal);
  Vector final = Vector(factor.x*color.x, factor.y*color.y, factor.z*color.z); //I_d*k_d
  final*=result;
  return final;
}

Vector Material::ambientC(Vector factor, Vector color){
  return Vector(factor.x*color.x, factor.y*color.y, factor.z*color.z);
}

Vector Material::specularC(Vector factor, Vector color, Vector light,
              Vector viewer, Vector normal, float power){
  float dbl = 2.0*Vector::dot(light, normal); //2*(I DOT n)
  Vector r = dbl*normal; //2*(I DOT n)*n
  Vector rb = r + -1.0*light;
  float rbv = Vector::dot(rb, viewer);
  rbv = pow(rbv, power);
  Vector final = Vector(factor.x*color.x, factor.y*color.y, factor.z*color.z);
  final*=rbv;
  float similarity = (Vector::dot(rb, viewer))/(Vector::mag(rb)*Vector::mag(viewer));
  if(similarity < 0) return Vector(0.0, 0.0, 0.0);
  return final;
}