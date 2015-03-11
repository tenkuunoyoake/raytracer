#ifndef CAMERA_H
#define CAMERA_H
#endif

#include <cmath>

#ifndef VECTOR_H
#include <vector.h>
#endif

#ifndef MATRIX_H
#include <matrix.h>
#endif

#ifndef RAY_H
#include <ray.h>
#endif

using namespace std;

//****************************************************
// Classes and Methods
//****************************************************

class Camera {
  
  public:
    
    // Declarations
    Vector origin, uLeft, uRight, lLeft, lRight;
    Matrix transform;
    
    // Methods
    void do_transform(Matrix c_transform);
    Ray compute_viewing_ray(int i, int j, int width, int height);
    
    // Constructors
    Camera();
    Camera(Vector, Vector, Vector, Vector, Vector);
};

