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
#include <matrix.h>
#endif

#ifndef VECTOR_H
#include <vector.h>
#endif

#include <input.h>

#ifndef CAMERA_H
#include <camera.h>
#endif

#ifndef FILM_H
#include <film.h>
#endif

#ifndef SCENE_H
#include <scene.h>
#endif

using namespace std;

//****************************************************
// Global Variables
//****************************************************

int image_width = 255;
int image_height = 255;

// Lol, and stuff...
char output_filename[14] = {'o', 'u', 't', 'p', 'u', 't', '-', '0', '0', '.',
    'p', 'n', 'g', '\0'};

Scene scene;

//****************************************************
// Test Functions
//****************************************************

void matrix_test() {
 
  Matrix zero = Matrix();
  Matrix identity = Matrix::identity_matrix();
  
  Matrix inverse_input = Matrix();
  inverse_input.set_value(0, 0, 2);
  inverse_input.set_value(1, 0, -6);
  inverse_input.set_value(2, 0, 3);
  inverse_input.set_value(3, 0, 1);
  inverse_input.set_value(0, 1, 6);
  inverse_input.set_value(1, 1, 3);
  inverse_input.set_value(2, 1, 2);
  inverse_input.set_value(3, 1, 1);
  inverse_input.set_value(0, 2, -3);
  inverse_input.set_value(1, 2, 2);
  inverse_input.set_value(2, 2, 6);
  inverse_input.set_value(3, 2, 1);
  inverse_input.set_value(0, 3, 0);
  inverse_input.set_value(1, 3, 0);
  inverse_input.set_value(2, 3, 0);
  inverse_input.set_value(3, 3, 1);
  Matrix inverse_output = Matrix::inverse(inverse_input);
  
  Matrix::print(zero);
  Matrix::print(identity);
  Matrix::print(inverse_input);
  Matrix::print(inverse_output);
  Matrix::print(Matrix::multiply(inverse_input, identity));
  Matrix::print(inverse_input);
  
}

void transform_test() {
 
  Matrix scalar = Matrix::scalar_matrix(2, 2, 2);
  Matrix translation = Matrix::translation_matrix(2, 3, 4);
  Matrix rotation = Matrix::rotation_matrix(90 / sqrt(2), 0, 90 / sqrt(2));
  
  // Rotate -> translate -> scale
  Matrix composite = Matrix::multiply(translation, scalar);
  composite = Matrix::multiply(composite, rotation);
  
  Matrix::print(scalar);
  Matrix::print(translation);
  Matrix::print(rotation);
  Matrix::print(composite);
  
  Vector::print(Matrix::transform(composite, Vector(0, 0, 1)));
  
}

void vector_test() {
 
  Vector a = Vector(1.0, 2.0, 3.0);
  Vector b = Vector(4.0, 5.0, 6.0);
  Vector c = a + b;
  Vector d = b - a;
  Vector e = a * 2;
  Vector f = 3 * b;
  Vector g = a / 4;
  Vector h = b.normalize();

  cout << a.x << " " << a.y << " " << a.z << endl;
  cout << b.x << " " << b.y << " " << b.z << endl;
  cout << c.x << " " << c.y << " " << c.z << endl;
  cout << d.x << " " << d.y << " " << d.z << endl;
  cout << e.x << " " << e.y << " " << e.z << endl;
  cout << f.x << " " << f.y << " " << f.z << endl;
  cout << g.x << " " << g.y << " " << g.z << endl;
  cout << h.x << " " << h.y << " " << h.z << endl;
  cout << (float) b.len() << endl;
  cout << (float) h.len() << endl;
  
}

void camera_test(){
  Vector a = Vector(1.0, 2.0, 3.0);
  Vector b = Vector(4.0, 5.0, 6.0);
  Vector c = a + b;
  Vector d = b - a;
  Vector e = a * 2;
  Camera zeroCam = Camera();
  Camera cam = Camera(a, b, c, d, e);
  printf("kek\n");
  Vector::print(a);
  Vector::print(b);
  Vector::print(c);
  Vector::print(d);
  Vector::print(e);
  printf("ayy lmao\n");
  Vector::print(cam.origin);
  Vector::print(cam.lLeft);
  Vector::print(cam.lRight);
  Vector::print(cam.uLeft);
  Vector::print(cam.uRight);
  printf("lots of zeros\n");
  Vector::print(zeroCam.origin);
}

void scene_test() {
  
  // Film is the class that writes to the image
  scene.film = Film(image_width, image_height);
  scene.film.output = output_filename;
  
  // Main Loop
  scene.render();
  
  // Once the scene has been rendered, free everything to make sure there are 
  // no memory leaks
  scene.dispose();
  
}

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
  
  // matrix_test();
  //transform_test();
  // vector_test();
  // camera_test();
  
  if (argc == 2) {
    parse_input(argv[1]);
  } else {
    printf("Error: Incorrect input");
    exit(EXIT_FAILURE);
  }
  
  scene_test();
  
  // Camera c = Camera(a, a, a, a, a);
  return 0;
  
}
