#ifndef CAMERA_H
#define CAMERA_H
#endif

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

