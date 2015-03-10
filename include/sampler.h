#ifndef SAMPLER_H
#define SAMPLER_H
#endif

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

    static Vector get_point(Camera* camera, int i, int j, int width, int height);

};