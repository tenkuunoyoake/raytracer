#ifndef SAMPLER_H
#define SAMPLER_H
#endif

#include <vector>

#ifndef CAMERA_H
#include <camera.h>
#endif

#ifndef VECTOR_H
#include <vector.h>
#endif

//****************************************************
// Classes and Methods
//****************************************************

class Sampler {

public:

    static void get_points(vector<Vector>* points, Camera* camera, int i, int j, int width, int height);

};