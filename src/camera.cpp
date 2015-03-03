#include "camera.h"

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

void Camera::set_transform(Matrix c_transform) {
  
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      transform.set_value(i, j, c_transform.get_value(i, j));
    }
  }
  
}