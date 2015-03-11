#include <camera.h>

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

void Camera::initialise_image_plane() {

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
  
  intersect_t = Vector::dot(term_1, lr_dir) + Vector::dot(term_2, tb_dir); 
  intersect_t = intersect_t / (1 - pow(Vector::dot(tb_dir, lr_dir), 2));
  
  // Should be the correct center of interest
  coi = top_center + tb_dir * intersect_t;

  // d is the distance from the center of interest to the eye
  distance = (coi - origin).len();
  
  // View direction
  w_dir = (origin - coi).normalize();
  Vector view_dir = (coi - origin).normalize();
  
  u_dir = Vector::cross(view_up, view_dir);
  v_dir = Vector::cross(view_dir, u_dir);
  
  // Change of basis
  Matrix coord_matrix = Matrix::coordinate_matrix(u_dir, v_dir, w_dir);
  
  Vector transformed_origin = Matrix::transform(coord_matrix, origin);
  Vector transformed_lRight = Matrix::transform(coord_matrix, lRight);
  Vector transformed_uLeft = Matrix::transform(coord_matrix, uLeft);
  Vector transformed_uRight = Matrix::transform(coord_matrix, uRight);
  
  c_left = (transformed_uLeft - transformed_origin).x;
  c_right = (transformed_uRight - transformed_origin).x;
  c_top = (transformed_uRight - transformed_origin).y;
  c_bottom = (transformed_lRight - transformed_origin).y;

}

void Camera::compute_viewing_rays(Ray* results, int noise, int i, int j, int width, int height) {
  
  // Compute u, v
  for (int bucket = 0; bucket < noise; bucket++) {

    float u = c_left + (c_right - c_left) * (i + 0.5) / width;
    float v = c_bottom + (c_top - c_bottom) * (j + 0.5) / height;

    results[bucket].direction = u * u_dir - v * v_dir - distance * w_dir;
    results[bucket].position = origin;

  }
  
}

void Camera::do_transform(Matrix c_transform) {

  origin = Matrix::transform(c_transform, origin);
  lLeft = Matrix::transform(c_transform, lLeft);
  lRight = Matrix::transform(c_transform, lRight);
  uLeft = Matrix::transform(c_transform, uLeft);
  uRight = Matrix::transform(c_transform, uRight);
  
}