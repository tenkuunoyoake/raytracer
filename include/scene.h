#ifndef SCENE_H
#define SCENE_H
#endif

#include <iostream>
#include <vector>

#ifndef VECTOR_H
#include "vector.h"
#endif

#ifndef CAMERA_H
#include "camera.h"
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

#ifndef FILM_H
#include "film.h"
#endif

#ifndef SAMPLER_H
#include "sampler.h"
#endif

#ifndef SPHERE_H
#include "sphere.h"
#endif

#ifndef TRIANGLE_H
#include "triangle.h"
#endif

using namespace std;

//*****************************************************************************
// Scene
//*****************************************************************************

class Scene {

  public:
    
    // Declarations

    Camera camera;
    Film film;

    vector<DirLight> dir_lights;
    vector<PointLight> point_lights;
    vector<Light> ambient_lights;
    vector<Vector> view_points;
    vector<Shape*> surfaces;
    
    // Methods

    void add_surface(Shape* surface);
    void add_dir_light(DirLight dir_light);
    void add_point_light(PointLight point_light);
    void add_ambient_light(Light ambient_light);
   
    void render();
    
    // Destructor
    
    void dispose();
    
};