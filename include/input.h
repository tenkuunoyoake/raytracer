#ifndef INPUT_H
#define INPUT_H
#endif

#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Self-defined

#ifndef MATRIX_H
#include "matrix.h"
#endif

#ifndef CAMERA_H
#include "camera.h"
#endif

#ifndef MATERIAL_H
#include "material.h"
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

#ifndef SCENE_H
#include "scene.h"
#endif

#ifndef SAMPLER_H
#include "sampler.h"
#endif

#ifndef VECTOR_H
#include "vector.h"
#endif

//****************************************************
// InputUtils
//****************************************************

class InputUtils {
  
  public:
    
    // Float input helper
    static int parse_float_input(char* input, float* output,
    int size, int linecount);
    
    // Camera
    static void parse_camera_input(Scene* scene, char* input, 
	Matrix transform_matrix, int linecount);
    
    // Objects
    static void parse_sphere_input(Scene* scene, char* input, 
	Matrix transform_matrix, Material material, int linecount);
    static void parse_triangle_input(Scene* scene, char* input, 
	Matrix transform_matrix, Material material, int linecount);
    static void parse_obj_input(Scene* scene, char* input,
    Matrix transform_matrix, Material material, int linecount);
    static int parse_face_input(char* input, int* vertnum,
    int* vnormnum, int* tcoordnum, int size, int linecount);
    
    // Lights
    static void parse_ptlight_input(Scene* scene, char* input, 
	Matrix transform_matrix, int linecount);
    static void parse_dirlight_input(Scene* scene, char* input, 
	Matrix transform_matrix, int linecount);
    static void parse_amblight_input(Scene* scene, char* input,
    int linecount);
    
    // Material
    static void parse_material_input(Material* material, char* input,
    int linecount);
    
    // Transforms
    static void parse_tl_transform_input(char* input, Matrix* transform_matrix,
    int linecount);
    static void parse_rt_transform_input(char* input, Matrix* transform_matrix,
    int linecount);
    static void parse_scl_transform_input(char* input, Matrix* transform_matrix,
    int linecount);
    static void parse_idt_transform_input(char* input, Matrix* transform_matrix,
    int linecount);

    // Distributed Ray Tracing
    static void parse_antialias_input(char* input, int linecount);
    static void parse_refract_input(Material* material, char* input,
    int linecount);
  
};