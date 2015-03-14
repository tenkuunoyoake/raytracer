#ifndef RAYTRACER_H
#define RAYTRACER_H
#endif

#ifndef VECTOR_H
#include "vector.h"
#endif

#ifndef RAY_H
#include "ray.h"
#endif

#ifndef LIGHT_H
#include "light.h"
#endif

#ifndef DIRLIGHT_H
#include "dirlight.h"
#endif

#ifndef POINTLIGHT_H
#include "pointlight.h"
#endif

#ifndef SPHERE_H
#include "sphere.h"
#endif

#ifndef TRIANGLE_H
#include "triangle.h"
#endif

#ifndef SCENE_H
#include "scene.h"
#endif

using namespace std;

//*****************************************************************************
// Raytracer
//*****************************************************************************

class Raytracer {

  public:
    // Declarations
    static int max_depth; 

    // Methods
    static bool shadow_ray(Scene* scene, Ray ray);
    static void shine_dir_lights(Vector *color, Scene *scene, 
        Material material, Vector surface, Vector viewer, Vector normal);
    static void shine_point_lights(Vector *color, Scene* scene, 
        Material material, Vector surface, Vector viewer, Vector normal);
    static void shine_ambient_lights(Vector *color, Scene* scene, 
      Material material);

    static void trace(Scene* scene, Ray ray, int depth, Vector* color);

};