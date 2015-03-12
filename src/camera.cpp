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

void Camera::do_transform(Matrix c_transform) {

  origin = Matrix::transform(c_transform, origin);
  lLeft = Matrix::transform(c_transform, lLeft);
  lRight = Matrix::transform(c_transform, lRight);
  uLeft = Matrix::transform(c_transform, uLeft);
  uRight = Matrix::transform(c_transform, uRight);
  
}