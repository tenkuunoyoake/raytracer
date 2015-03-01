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
