#ifndef CAMERA_H
#define CAMERA_H
#endif

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
    
    // Constructors
    Camera();
    Camera(Vector, Vector, Vector, Vector, Vector);
};

