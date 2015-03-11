#include "camera.h"

//*****************************************************************************
// Camera
//*****************************************************************************

Camera::Camera(){
  
  origin = Vector();
  uLeft = Vector();
  uRight = Vector();
  lLeft = Vector();
  lRight = Vector();
  
}

Camera::Camera(Vector e, Vector lL, Vector lR, Vector uL, Vector uR){
  
  origin = e;
  uLeft = uL;
  uRight = uR;
  lLeft = lL;
  lRight = lR;

}

Ray Camera::compute_viewing_ray(int i, int j, int width, int height) {
  
  // Declarations
  Ray result;
  
  // Set view-up equal to y-axis
  Vector view_up = Vector(0, 1, 0); 
  
  // Center of interest is (roughly) the intersection between two lines
  // created by the midpoints of each of the edges of the quadrilateral
  
  Vector left_center = (uLeft + lLeft) / 2;
  Vector right_center = (uRight + lRight) / 2;
  Vector top_center = (uRight + uLeft) / 2;
  Vector bottom_center = (lRight + lLeft) / 2;
  
  // Direction of two rays
  Vector lr_dir = (right_center - left_center).normalize();
  Vector tb_dir = (top_center - bottom_center).normalize();
        
  // s = [(n . m) * (B - A) . n + (A - B) . m] / [1 - (m . n)^2]
  //   = [ Term1 . n + Term2 . m ] / [ 1 - (m . n)^2 ]
  Vector term_1 = (top_center - left_center) * (Vector::dot(lr_dir, tb_dir)); 
  Vector term_2 = left_center - top_center;
  
  float intersect_t = Vector::dot(term_1, lr_dir) + Vector::dot(term_2, tb_dir); 
  intersect_t = intersect_t / (1 - pow(Vector::dot(tb_dir, lr_dir), 2));
  
  // Should be the correct center of interest
  Vector coi = top_center + tb_dir * intersect_t;
  
  // d is the distance from the center of interest to the eye
  float d = (coi - origin).len();
  
  // View direction
  Vector w_dir = (coi - origin).normalize();
  
  Vector u_dir = Vector::cross(view_up, w_dir);
  Vector v_dir = Vector::cross(w_dir, u_dir);
  
  // Change of basis
  Matrix coord_matrix = Matrix::coordinate_matrix(u_dir, v_dir, w_dir);
  
  Vector transformed_origin = Matrix::transform(coord_matrix, origin);
  Vector transformed_lRight = Matrix::transform(coord_matrix, lRight);
  Vector transformed_uLeft = Matrix::transform(coord_matrix, uLeft);
  Vector transformed_uRight = Matrix::transform(coord_matrix, uRight);
  
  float left = (transformed_uLeft - transformed_origin).x;
  float right = (transformed_uRight - transformed_origin).x;
  float top = (transformed_uRight - transformed_origin).y;
  float bottom = (transformed_lRight - transformed_origin).y;
  
  // Compute u, v
  float u = left + (right - left) * (i + 0.5) / width;
  float v = bottom + (top - bottom) * (j + 0.5) / height;
  
  result.direction = u * u_dir + v * v_dir + d * w_dir;
  result.position = origin;
  
  return result;
}

void Camera::do_transform(Matrix c_transform) {

  origin = Matrix::transform(c_transform, origin);
  lLeft = Matrix::transform(c_transform, lLeft);
  lRight = Matrix::transform(c_transform, lRight);
  uLeft = Matrix::transform(c_transform, uLeft);
  uRight = Matrix::transform(c_transform, uRight);
  
}