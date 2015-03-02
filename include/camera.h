#ifndef CAMERA_H
#define CAMERA_H
#endif

#ifndef VECTOR_H
#include <vector.h>
#endif

using namespace std;

//****************************************************
// Classes and Methods
//****************************************************
class Camera {     
	public:
		Vector origin, uLeft, uRight, lLeft, lRight;
		Camera();
		Camera(Vector, Vector, Vector, Vector, Vector);
};

