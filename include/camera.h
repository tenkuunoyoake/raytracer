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

    float intersect_t;
    Vector coi;

    float distance; 

    float c_left;
    float c_right;
    float c_top;
    float c_bottom;

    Vector u_dir;
    Vector v_dir;
    Vector w_dir;

    // Methods
    void initialise_image_plane();
    void do_transform(Matrix c_transform);
    void compute_viewing_rays(Ray* rays, int rays_size, int i, int j, 
        int width, int height);
    
    // Constructors
    Camera();
    Camera(Vector, Vector, Vector, Vector, Vector);
};

