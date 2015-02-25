//****************************************************
// Input Helpers
//****************************************************

void parse_float_input(char* input, float* output) {
  
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

void parse_camera_input(char* input) {
  
  // Declarations
  float output[15];
  
  parse_float_input(input, output);
    
  /* 
  camera.eye.x = output[0];
  camera.eye.y = output[1];
  camera.eye.z = output[2];
  camera.ll.x = output[3];
  camera.ll.y = output[4];
  camera.ll.z = output[5];
  camera.lr.x = output[6];
  camera.lr.y = output[7];
  camera.lr.z = output[8];
  camera.ul.x = output[9];
  camera.ul.y = output[10];
  camera.ul.z = output[11];
  camera.ur.x = output[12];
  camera.ur.y = output[13];
  camera.ur.z = output[14]; 
  */
  
}

void parse_sphere_input(char* input) {
  
  // Declarations
  float output[4];
  
  parse_float_input(input, output);
  
  /* 
  sphere.center_x = output[0];
  sphere.center_y = output[1];
  sphere.center_z = output[2];
  sphere.radius = output[3]; 
  */
  
  
}

void parse_triangle_input(char* input) {
  
  // Declarations
  float output[9];
  
  parse_float_input(input, output);
  
  /*
  triangle.vertex1.x = output[0];
  triangle.vertex1.y = output[1];
  triangle.vertex1.z = output[2];
  triangle.vertex2.x = output[3];
  triangle.vertex2.y = output[4];
  triangle.vertex2.z = output[5];
  triangle.vertex3.x = output[6];
  triangle.vertex3.y = output[7];
  triangle.vertex3.z = output[8];
  */
  
}

void parse_obj_input(char* input) {

  int i = 5;
  char* filename;
  
  while (input[i] != '"' && input[i] != '\0') {
    filename[i - 5] = input[i];
    i++;
  }
  
  filename[i - 5] = '\0';
  
  /* Load the obj file */
  
}

void parse_ptlight_input(char* input) {
  
  // Declarations
  float output[7];
  
  // Default falloff to 0
  output[6] = 0; 
  
  parse_float_output(input, output);
  
  /*
   ptlight.x = output[0];
   ptlight.y = output[1];
   ptlight.z = output[2];
   ptlight.color.r = output[3];
   ptlight.color.g = output[4];
   ptlight.color.b = output[5];
   ptlight.falloff = output[6];
  */
  
  /* Need to transform the thing */
  
}

void parse_dirlight_input(char* input) {
  
  // Declarations
  float output[6];
  parse_float_output(input, output);
  
  /*
    dirlight.x = output[0];
    dirlight.y = output[1];
    dirlight.z = output[2];
    dirlight.color.r = output[3];
    dirlight.color.g = output[4];
    dirlight.color.b = output[5];
  */
  
} 

void parse_amblight_input(char* input) {
  
  // Declarations
  float output[3];
  parse_float_output(input, output);
  
  /*
   amblight.color.r = output[0];
   amblight.color.g = output[1];
   amblight.color.b = output[2];
 */
  
}

void parse_material_input(char* input) {
  
  // Declarations
  float output[12];
  parse_float_output(input, output);
  
  /* 
   material.ambient_c.r = output[0];
   material.ambient_c.g = output[1];
   material.ambient_c.b = output[2];
   material.diffuse_c.r = output[3];
   material.diffuse_c.g = output[4];
   material.diffuse_c.b = output[5];
   material.spec_c.r = output[6];
   material.spec_c.g = output[7];
   material.spec_c.b = output[8];
   material.refl_c.r = output[9];
   material.refl_c.r = output[10];
   material.refl_c.r = output[11];
  */

}

void parse_tl_transform_input(char* input) {
  
  // Declarations
  float output[3];
  parse_float_output(input, output);
  
  /* Create a translation matrix that translates by [x, y, z] */
  
}

void parse_rt_transform_input(char* input) {
  
  // Declarations
  float output[3];
  parse_float_output(input, output);
  
  /* Create a rotation matrix that rotates by [x, y, z] degrees */
  
}

void parse_scl_transform_input(char* input) {
  
  // Declarations
  float output[3];
  parse_float_output(input, output);
  
  /* Create a scalar matrix that scales to [x, y, z] */
  
}

void parse_idt_transform_input() {
  
  /* Set the matrix back to the identity */
  
}

//****************************************************
// Input Parsing
//****************************************************

void parse_input(char* input) {
  
  // Declarations
  char line[256];
  char header[4];
  char *tokenised_line;
  
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
      parse_camera_input(tokenised_line);
    } else if (strcmp(header, "sph") == 0) {
      parse_sphere_input(tokenised_line);
    } else if (strcmp(header, "tri") == 0) {
      parse_triangle_input(tokenised_line);
    } else if (strcmp(header, "obj") == 0) {
      parse_obj_input(line);
    } else if (strcmp(header, "ltp") == 0) {
      parse_ptlight_input(tokenised_line);
    } else if (strcmp(header, "ltd") == 0) {
      parse_dirlight_input(tokenised_line);
    } else if (strcmp(header, "lta") == 0) {
      parse_amblight_input(tokenised_line);
    } else if (strcmp(header, "mat") == 0) {
      parse_material_input(tokenised_line);
    } else if (strcmp(header, "xft") == 0) {
      parse_tl_transform_input(tokenised_line);
    } else if (strcmp(header, "xfr") == 0) {
      parse_rt_transform_input(tokenised_line);
    } else if (strcmp(header, "xfs") == 0) {
      parse_scl_transform_input(tokenised_line);
    } else if (strcmp(header, "xfz") == 0) {
      parse_idt_transform_input();
    }
  }
  
  // Close the file
  fclose(file);
  
}