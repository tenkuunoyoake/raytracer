#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//****************************************************
// Classes and Methods
//****************************************************
class Camera {     
	public:
		Vector origin, uLeft, uRight, lLeft, lRight = Vector(0.0, 0.0, 0.0);
		Camera();
		Camera(Vector, Vector, Vector, Vector, Vector);

};

Camera::Camera(Vector e, Vector lL, Vector lR, Vector uL, Vector uR){
	origin = e;
	uLeft = uL;
	uRight = uR;
	lLeft = lL;
	lRight = lR;
}
