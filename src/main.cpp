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

int image_width = 1000;
int image_height = 1000;

int Raytracer::max_depth = 2;

// Samples n x n points
int Sampler::samples = 1; 

char output_filename[] = "output-00.png";

Scene scene;

//****************************************************
// Input Parsing
//****************************************************

void parse_input(char* input) {
  
  // Read from the file
  FILE* file = fopen(input, "r");
  
  // Error if file does not exist
  if (file == NULL) {
    cerr << "File does not exist: " << input << endl;
    exit(EXIT_FAILURE);
  }

  // Assuming input name is of the format "input-nn"
  output_filename[7] = input[6];
  output_filename[8] = input[7];

  // Declarations
  char line[256];
  char *tokenised_line;
  int linecount = 1;
  
  Matrix transform_matrix = Matrix::identity_matrix(); 
  Material material;
  
  // Print out each line
  while (fgets(line, sizeof(line), file)) {
    
    // Tokenise the line, starting at header
    tokenised_line = strtok(line, " \n\t\r");

    if (tokenised_line == NULL) {
      // Do nothing
    } else if (strcmp(tokenised_line, "cam") == 0) {
      InputUtils::parse_camera_input(&scene, tokenised_line, 
          transform_matrix, linecount);
    } else if (strcmp(tokenised_line, "sph") == 0) {
      InputUtils::parse_sphere_input(&scene, tokenised_line, transform_matrix, 
          material, linecount);
    } else if (strcmp(tokenised_line, "tri") == 0) {
      InputUtils::parse_triangle_input(&scene, tokenised_line, transform_matrix, 
          material, linecount);
    } else if (strcmp(tokenised_line, "obj") == 0) {
      InputUtils::parse_obj_input(&scene, tokenised_line, transform_matrix,
          material, linecount);
    } else if (strcmp(tokenised_line, "ltp") == 0) {
      InputUtils::parse_ptlight_input(&scene, tokenised_line,
          transform_matrix, linecount);
    } else if (strcmp(tokenised_line, "ltd") == 0) {
      InputUtils::parse_dirlight_input(&scene, tokenised_line, 
          transform_matrix, linecount);
    } else if (strcmp(tokenised_line, "lta") == 0) {
      InputUtils::parse_amblight_input(&scene, tokenised_line, linecount);
    } else if (strcmp(tokenised_line, "mat") == 0) {
      InputUtils::parse_material_input(&material, tokenised_line, linecount);
    } else if (strcmp(tokenised_line, "xft") == 0) {
      InputUtils::parse_tl_transform_input(tokenised_line, &transform_matrix,
          linecount);
    } else if (strcmp(tokenised_line, "xfr") == 0) {
      InputUtils::parse_rt_transform_input(tokenised_line, &transform_matrix,
          linecount);
    } else if (strcmp(tokenised_line, "xfs") == 0) {
      InputUtils::parse_scl_transform_input(tokenised_line, &transform_matrix,
          linecount);
    } else if (strcmp(tokenised_line, "xfz") == 0) {
      InputUtils::parse_idt_transform_input(tokenised_line, &transform_matrix,
          linecount);
    } else if (strcmp(tokenised_line, "als") == 0) {
      InputUtils::parse_antialias_input(tokenised_line, linecount);
    } else if (strcmp(tokenised_line, "rfc") == 0) {
      InputUtils::parse_refract_input(&material, tokenised_line, linecount);
    } else {
        cerr << "Command \"" << tokenised_line << "\" unrecognized. Line " <<
            linecount << " ignored." << endl;
    }

    linecount++;
    
  }
  
  // Close the file
  fclose(file);
  
}

int main(int argc, char *argv[]) {
  
  if (argc == 2) {
    parse_input(argv[1]);
  } else {
    cerr << "Error: Incorrect input" << endl;
    exit(EXIT_FAILURE);
  }
  
  // Film is the class that writes to the image
  scene.film = Film(image_width, image_height);
  scene.film.output = output_filename;
  
  // Intersection acceleration
  scene.bbox_tree = new BoundingTree(scene.surfaces, NULL, 0, true);

  // Main Loop
  scene.render();
  
  // Once the scene has been rendered, free everything to make sure there are 
  // no memory leaks
  scene.dispose();

  return 0;
  
}
