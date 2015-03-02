#include <input.h>

//****************************************************
// Input Helpers
//****************************************************

void InputUtils::parse_float_input(char* input, float* output) {
  
  // Declarations
  int i = 0;
  
  // Strip the header
  input = strtok(NULL, " ");
  
  // Until the end of input is reached
  while (input != NULL) {
    // Translate the input into a float and store in output
    output[i] = atof(input);
    printf("%f\n", output[i]);
    // Hop to the next input
    input = strtok(NULL, " ");
    i++;
  }
  
}

void InputUtils::parse_camera_input(Camera* camera,
    char* input, Matrix transform_matrix) {
  
  // Declarations
  float output[15];
  
  InputUtils::parse_float_input(input, output);
  
  camera->origin = Vector(output[0], output[1], output[2]); 
  camera->uLeft = Vector(output[3], output[4], output[5]);
  camera->uRight = Vector(output[6], output[7], output[8]);
  camera->lLeft = Vector(output[9], output[10], output[11]);
  camera->lRight = Vector(output[12], output[13], output[14]);
  // camera->set_transform(transform_matrix);
  
}

void InputUtils::parse_sphere_input(char* input, Matrix transform_matrix, 
    Material material) {
  
  // Declarations
  float output[4];
  
  InputUtils::parse_float_input(input, output);
  
  /* 
  sphere->center_x = output[0];
  sphere->center_y = output[1];
  sphere->center_z = output[2];
  sphere->radius = output[3]; 
  sphere->set_transform(transform_matrix);
  sphere->set_material(material);
  */
  
  
}

void InputUtils::parse_triangle_input(char* input, Matrix transform_matrix, 
    Material material) {
  
  // Declarations
  float output[9];
  
  InputUtils::parse_float_input(input, output);
  
  /*
  triangle->vertex1.x = output[0];
  triangle->vertex1.y = output[1];
  triangle->vertex1.z = output[2];
  triangle->vertex2.x = output[3];
  triangle->vertex2.y = output[4];
  triangle->vertex2.z = output[5];
  triangle->vertex3.x = output[6];
  triangle->vertex3.y = output[7];
  triangle->vertex3.z = output[8];
  triangle->set_transform(transform_matrix);
  triangle->set_material(material);
  */
  
}

void InputUtils::parse_obj_input(char* input, Matrix transform_matrix, 
    Material material) {

  // Declarations
  int i = 5;
  char filename[256];
  
  while (input[i] != '"' && input[i] != '\0') {
    filename[i - 5] = input[i];
    i++;
  }
  
  filename[i - 5] = '\0';

  /* Load the obj file */
  
  /* 
  obj->set_transform(transform_matrix);
  */
  
  // Just to get rid of a stupid warning
  printf("%s", filename); 
  
}

void InputUtils::parse_ptlight_input(PointLight* ptlight, char* input, 
    Matrix transform_matrix) {
  
  // Declarations
  float output[7];
  
  // Default falloff to 0
  output[6] = 0; 
  
  InputUtils::parse_float_input(input, output);
  
   ptlight->position = Vector(output[0], output[1], output[2]);
   ptlight->color = Vector(output[3], output[4], output[5]);
   ptlight->falloff = output[6];
   ptlight->set_transform(transform_matrix);
  
}

void InputUtils::parse_dirlight_input(DirLight* dirlight, char* input, 
    Matrix transform_matrix) {
  
  // Declarations
  float output[6];
  
  InputUtils::parse_float_input(input, output);
  
  dirlight->direction = Vector(output[0], output[1], output[2]);
  dirlight->color = Vector(output[3], output[4], output[5]);
  dirlight->set_transform(transform_matrix);
  
} 

void InputUtils::parse_amblight_input(Light* amblight, char* input) {
  
  // Declarations
  float output[3];
  
  InputUtils::parse_float_input(input, output);
  
  amblight->color = Vector(output[0], output[1], output[2]);
  
}

void InputUtils::parse_material_input(Material* material, char* input) {
  
  // Declarations
  float output[12];
  InputUtils::parse_float_input(input, output);
  
  material->ambient = Vector(output[0], output[1], output[2]);
  material->diffuse = Vector(output[3], output[4], output[5]);
  material->specular = Vector(output[6], output[7], output[8]);
  material->reflective = Vector(output[9], output[10], output[11]);

}

void InputUtils::parse_tl_transform_input(char* input, Matrix* transform_matrix) {
  
  // Declarations
  float output[3];
  Matrix translation;
  
  InputUtils::parse_float_input(input, output);
  
  /* Create a translation matrix that translates by [x, y, z] */
  translation = Matrix::translation_matrix(output[0], output[1], output[2]);
  
  // Apply that onto the transform matrix
  *transform_matrix = Matrix::multiply(*transform_matrix, translation);
  
}

void InputUtils::parse_rt_transform_input(char* input, Matrix* transform_matrix) {
  
  // Declarations
  float output[3];
  Matrix rotation;
  
  InputUtils::parse_float_input(input, output);
  
  // Create a rotation matrix that rotates by the exponential map [x, y, z]
  rotation = Matrix::rotation_matrix(output[0], output[1], output[2]);

  // Apply that onto the transform matrix
  *transform_matrix = Matrix::multiply(*transform_matrix, rotation);
  
}

void InputUtils::parse_scl_transform_input(char* input, Matrix* transform_matrix) {
  
  // Declarations
  float output[3];
  Matrix scalar;
  
  InputUtils::parse_float_input(input, output);
  
  // Create a scalar matrix that scales to [x, y, z]
  scalar = Matrix::scalar_matrix(output[0], output[1], output[2]);
  
  // Apply that onto the transform matrix
  *transform_matrix = Matrix::multiply(*transform_matrix, scalar);
  
}

void InputUtils::parse_idt_transform_input(Matrix* transform_matrix) {
  
  // Set the matrix back to the identity
  *transform_matrix = Matrix::identity_matrix();
  
}

//****************************************************
// Input Parsing
//****************************************************
/*

void parse_input(char* input) {
  
  // Declarations
  char line[256];
  char header[4];
  char *tokenised_line;
  
  Matrix transform_matrix; 
  Material material;
  
  // Read from the file
  FILE* file = fopen(input, "r");
  
  // Error if file does not exist
  if (file == NULL) {
    printf("File does not exist: %s\n", input);
    return;
  }
  
  // Print out each line
  while (fgets(line, sizeof(line), file)) {
    
    // Grab the header of each line
    strncpy(header, line, 3);
    header[3] = '\0';
    
    // Tokenise the line, and get rid of header
    tokenised_line = strtok(line, " ");
    
    if (strcmp(header, "cam") == 0) {
      InputUtils::parse_camera_input(tokenised_line, transform_matrix);
    } else if (strcmp(header, "sph") == 0) {
      InputUtils::parse_sphere_input(tokenised_line, transform_matrix, 
	  material);
    } else if (strcmp(header, "tri") == 0) {
      InputUtils::parse_triangle_input(tokenised_line, transform_matrix, 
	  material);
    } else if (strcmp(header, "obj") == 0) {
      InputUtils::parse_obj_input(line, transformation_matrix, material);
    } else if (strcmp(header, "ltp") == 0) {
      InputUtils::parse_ptlight_input(tokenised_line, transform_matrix);
    } else if (strcmp(header, "ltd") == 0) {
      InputUtils::parse_dirlight_input(tokenised_line, transform_matrix);
    } else if (strcmp(header, "lta") == 0) {
      InputUtils::parse_amblight_input(tokenised_line);
    } else if (strcmp(header, "mat") == 0) {
      InputUtils::parse_material_input(*material, tokenised_line);
    } else if (strcmp(header, "xft") == 0) {
      InputUtils::parse_tl_transform_input(tokenised_line, *transform_matrix);
    } else if (strcmp(header, "xfr") == 0) {
      InputUtils::parse_rt_transform_input(tokenised_line, *transform_matrix);
    } else if (strcmp(header, "xfs") == 0) {
      InputUtils::parse_scl_transform_input(tokenised_line, *transform_matrix);
    } else if (strcmp(header, "xfz") == 0) {
      InputUtils::parse_idt_transform_input(*transform_matrix);
    }
  }
  
  // Close the file
  fclose(file);
  
}
*/
