#include <vector>
#include <iostream>
#include <fstream>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Self-defined

#ifndef MATRIX_H
#include <matrix.h>
#endif

#ifndef CAMERA_H
#include <camera.h>
#endif

#ifndef MATERIAL_H
#include <material.h>
#endif

#ifndef LIGHT_H
#include <light.h>
#endif

#ifndef DIRLIGHT_H
#include <dirlight.h>
#endif

#ifndef POINTLIGHT_H
#include <pointlight.h>
#endif

#ifndef SCENE_H
#include <scene.h>
#endif

//****************************************************
// InputUtils
//****************************************************

class InputUtils {
  
  public:
    
    // Float input helper
    static void parse_float_input(char* input, float* output);
    
    // Camera
    static void parse_camera_input(Scene* scene, char* input, 
	Matrix transform_matrix);
    
    // Objects
    static void parse_sphere_input(Scene* scene, char* input, 
	Matrix transform_matrix, Material material);
    static void parse_triangle_input(Scene* scene, char* input, 
	Matrix transform_matrix, Material material);
    static void parse_obj_input(char* input, Matrix transform_matrix, 
	Material material);
    
    // Lights
    static void parse_ptlight_input(Scene* scene, char* input, 
	Matrix transform_matrix);
    static void parse_dirlight_input(Scene* scene, char* input, 
	Matrix transform_matrix);
    static void parse_amblight_input(Scene* scene, char* input);
    
    // Material
    static void parse_material_input(Material* material, char* input);
    
    // Transforms
    static void parse_tl_transform_input(char* input, Matrix* transform_matrix);
    static void parse_rt_transform_input(char* input, Matrix* transform_matrix);
    static void parse_scl_transform_input(char* input, Matrix* transform_matrix);
    static void parse_idt_transform_input(Matrix* transform_matrix);
  
};