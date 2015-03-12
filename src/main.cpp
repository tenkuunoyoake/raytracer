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

// Self-defined

#ifndef MATRIX_H
#include "matrix.h"
#endif

#ifndef VECTOR_H
#include "vector.h"
#endif

#ifndef SPHERE_H
#include "sphere.h"
#endif

#ifndef TRIANGLE_H
#include "triangle.h"
#endif

#ifndef CAMERA_H
#include "camera.h"
#endif

#ifndef FILM_H
#include "film.h"
#endif

#ifndef SCENE_H
#include "scene.h"
#endif

#ifndef INPUT_H
#include "input.h"
#endif

#ifndef RAYTRACER_H
#include "raytracer.h"
#endif

using namespace std;

//****************************************************
// Global Variables
//****************************************************

int image_width = 300;
int image_height = 300;

int Raytracer::max_depth = 5;

// Lol, and stuff...
char output_filename[14] = {'o', 'u', 't', 'p', 'u', 't', '-', '0', '0', '.',
    'p', 'n', 'g', '\0'};

Scene scene;

//****************************************************
// Input Parsing
//****************************************************

void parse_input(char* input) {
  
  // Declarations
  char line[256];
  char header[4];
  char *tokenised_line;
  
  Matrix transform_matrix = Matrix::identity_matrix(); 
  Material material;
  
  // Read from the file
  FILE* file = fopen(input, "r");
  
  // Error if file does not exist
  if (file == NULL) {
    printf("File does not exist: %s\n", input);
    return;
  }
  
  output_filename[7] = input[6];
  output_filename[8] = input[7];
  
  // Print out each line
  while (fgets(line, sizeof(line), file)) {
    
    // Grab the header of each line
    strncpy(header, line, 3);
    header[3] = '\0';
    
    // Tokenise the line, and get rid of header
    tokenised_line = strtok(line, " ");
    
    if (strcmp(header, "cam") == 0) {
      InputUtils::parse_camera_input(&scene, tokenised_line, 
	      transform_matrix);
    } else if (strcmp(header, "sph") == 0) {
      InputUtils::parse_sphere_input(&scene, tokenised_line, transform_matrix, 
	        material);
    } else if (strcmp(header, "tri") == 0) {
      InputUtils::parse_triangle_input(&scene, tokenised_line, transform_matrix, 
	        material);
    } else if (strcmp(header, "obj") == 0) {
      InputUtils::parse_obj_input(line, transform_matrix, material);
    } else if (strcmp(header, "ltp") == 0) {
      InputUtils::parse_ptlight_input(&scene, tokenised_line, transform_matrix);
    } else if (strcmp(header, "ltd") == 0) {
      InputUtils::parse_dirlight_input(&scene, tokenised_line, 
	        transform_matrix);
    } else if (strcmp(header, "lta") == 0) {
      InputUtils::parse_amblight_input(&scene, tokenised_line);
    } else if (strcmp(header, "mat") == 0) {
      InputUtils::parse_material_input(&material, tokenised_line);
    } else if (strcmp(header, "xft") == 0) {
      InputUtils::parse_tl_transform_input(tokenised_line, &transform_matrix);
    } else if (strcmp(header, "xfr") == 0) {
      InputUtils::parse_rt_transform_input(tokenised_line, &transform_matrix);
    } else if (strcmp(header, "xfs") == 0) {
      InputUtils::parse_scl_transform_input(tokenised_line, &transform_matrix);
    } else if (strcmp(header, "xfz") == 0) {
      InputUtils::parse_idt_transform_input(&transform_matrix);
    }
    
  }
  
  // Close the file
  fclose(file);
  
}

int main(int argc, char *argv[]) {
  
  if (argc == 2) {
    parse_input(argv[1]);
  } else {
    printf("Error: Incorrect input");
    exit(EXIT_FAILURE);
  }
  
  // Film is the class that writes to the image
  scene.film = Film(image_width, image_height);
  scene.film.output = output_filename;
  
  // Main Loop
  scene.render();
  
  // Once the scene has been rendered, free everything to make sure there are 
  // no memory leaks
  scene.dispose();

  return 0;
  
}
