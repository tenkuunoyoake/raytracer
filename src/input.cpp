#include "input.h"

//****************************************************
// Input Module
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
    // Hop to the next input
    input = strtok(NULL, " ");
    i++;
  }
  
}

void InputUtils::parse_camera_input(Scene* scene, char* input, 
    Matrix transform_matrix) {
  
  // Declarations
  Camera camera;
  float output[15];
  
  InputUtils::parse_float_input(input, output);
  
  camera.origin = Vector(output[0], output[1], output[2]); 
  camera.lLeft = Vector(output[3], output[4], output[5]);
  camera.lRight = Vector(output[6], output[7], output[8]);
  camera.uLeft = Vector(output[9], output[10], output[11]);
  camera.uRight = Vector(output[12], output[13], output[14]);

  camera.do_transform(transform_matrix);

  scene->camera = camera;
  
}

void InputUtils::parse_sphere_input(Scene* scene, char* input, 
    Matrix transform_matrix, Material material) {
  
  // Declarations

  Sphere* sphere = new Sphere;
  float output[4];
  
  InputUtils::parse_float_input(input, output);
  
  sphere->center = Vector(output[0], output[1], output[2]);
  sphere->radius = output[3]; 
  sphere->transform = transform_matrix;
  sphere->material = material;

  scene->add_surface(sphere);
  
}

void InputUtils::parse_triangle_input(Scene* scene, char* input, 
    Matrix transform_matrix, Material material) {
  
  // Declarations

  Triangle* triangle = new Triangle;
  float output[9];
  
  InputUtils::parse_float_input(input, output);
  
  triangle->v1 = Vector(output[0], output[1], output[2]);
  triangle->v2 = Vector(output[3], output[4], output[5]);
  triangle->v3 = Vector(output[6], output[7], output[8]);
  triangle->material = material;

  triangle->do_transform(transform_matrix);

  scene->add_surface(triangle);
  
}

void InputUtils::parse_obj_input(Scene* scene, char* input,
    Matrix transform_matrix, Material material) {

  // Declarations
  int i = 5;
  int linecount = 1;
  char filename[256];
  char line[256];
  char *tokenised_line;
  float output[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  vector<Vector> vertices;
  vector<Vector> vnormals;
  vector<Vector> texture_coords;
  
  while (input[i] != '"' && input[i] != '\0') {
    filename[i - 5] = input[i];
    i++;
  }
  
  filename[i - 5] = '\0';

  /* Load the obj file */
  FILE* file = fopen(filename, "r");
  
  // Error if file does not exist
  if (file == NULL) {
    cerr << "File does not exist: " << filename << endl;
    return;
  }

  while (fgets(line, sizeof(line), file)) {
    
    // Tokenise the line, and get rid of header
    tokenised_line = strtok(line, " ");
    
    if (strcmp(tokenised_line[0], "v") == 0) {
      InputUtils::parse_float_input(tokenised_line, output);
      Vector vertex = Vector(output[0], output[1], output[2]);
      vertices.push_back(vertex);
    } else if (strcmp(tokenised_line[0], "vn") == 0) {
      InputUtils::parse_float_input(tokenised_line, output);
      Vector normal = Vector(output[0], output[1], output[2]);
      vnormals.push_back(normal);
    } else if (strcmp(tokenised_line[0], "f") == 0) {
      int vertnum[3];
      int vnormnum[3];
      int tcoordnum[3];
      InputUtils::parse_face_input(tokenised_line, vertnum, vnormnum, 
          tcoordnum);
    } else if (strcmp(tokenised_line[0], "vt") == 0) {
      InputUtils::parse_float_input(tokenised_line, output);
      Vector tcoord = Vector(output[0], output[1]);
      texture_coords.push_back(tcoord);
    } else {
      cerr << "Command \"" << tokenised_line[0] << "\" unrecognized. Line " <<
          linecount << " ignored." << endl;
    }

    linecount++;
    
  }
  
  /* 
  obj->set_transform(transform_matrix);
  */
  
  // Just to get rid of a stupid warning
  printf("%s", filename); 
  
}

void InputUtils::parse_face_input(char* input, int* vertnum, int* vnormnum
    int* tcoordnum) {

}

void InputUtils::parse_ptlight_input(Scene* scene, char* input, 
    Matrix transform_matrix) {
  
  // Declarations
  PointLight ptlight;
  float output[7];
  
  // Default falloff to 0
  output[6] = 0; 
  
  InputUtils::parse_float_input(input, output);
  
  ptlight.position = Vector(output[0], output[1], output[2]);
  ptlight.color = Vector(output[3], output[4], output[5]);
  ptlight.falloff = output[6];
  ptlight.set_transform(transform_matrix);
  
  scene->add_point_light(ptlight);
  
}

void InputUtils::parse_dirlight_input(Scene* scene, char* input, 
    Matrix transform_matrix) {
  
  // Declarations
  DirLight dirlight;
  float output[6];
  
  InputUtils::parse_float_input(input, output);
  
  dirlight.direction = Vector(output[0], output[1], output[2]);
  dirlight.direction = dirlight.direction.normalize();
  dirlight.color = Vector(output[3], output[4], output[5]);
  dirlight.set_transform(transform_matrix);
  scene->add_dir_light(dirlight);
  
} 

void InputUtils::parse_amblight_input(Scene* scene, char* input) {
  
  // Declarations
  Light amblight;
  float output[3];
  
  InputUtils::parse_float_input(input, output);
  
  amblight.color = Vector(output[0], output[1], output[2]);
  scene->add_ambient_light(amblight);
  
}

void InputUtils::parse_material_input(Material* material, char* input) {
  
  // Declarations
  float output[13];
  InputUtils::parse_float_input(input, output);
  
  material->ambient = Vector(output[0], output[1], output[2]);
  material->diffuse = Vector(output[3], output[4], output[5]);
  material->specular = Vector(output[6], output[7], output[8]);
  material->reflective = Vector(output[10], output[11], output[12]);
  material->phong_e = output[9];

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
