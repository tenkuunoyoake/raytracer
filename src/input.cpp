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
  
  parse_float_input(input, output);
  
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
  
  parse_float_input(input, output);

  sphere->center = Vector(output[0], output[1], output[2]);
  sphere->radius = output[3]; 
  sphere->transform = Matrix::inverse(transform_matrix);
  sphere->material = material;

  scene->add_surface(sphere);
  
}

void InputUtils::parse_triangle_input(Scene* scene, char* input, 
    Matrix transform_matrix, Material material) {
  
  // Declarations
  float output[9];
  Triangle* triangle;
  
  parse_float_input(input, output);
  
  Vector point1 = Vector(output[0], output[1], output[2]);
  Vector point2 = Vector(output[3], output[4], output[5]);
  Vector point3 = Vector(output[6], output[7], output[8]);

  // Check direction of normal in relation to camera
  point1 = Matrix::transform(transform_matrix, point1);
  point2 = Matrix::transform(transform_matrix, point2);
  point3 = Matrix::transform(transform_matrix, point3);
  Vector U = point2 - point1;
  Vector V = point3 - point1;
  Vector normal = Vector::cross(U, V);
  Vector view = (point1 + point2 + point3) / 3 - scene->camera.origin;
  if (Vector::dot(normal, view) > 0) {
    triangle = new Triangle(Matrix::identity_matrix(), point1, point3, point2, -1*normal, material);
  } else {
    triangle = new Triangle(Matrix::identity_matrix(), point1, point2, point3, normal, material);
  }

  scene->add_surface(triangle);
  
}

void InputUtils::parse_obj_input(Scene* scene, char* input,
    Matrix transform_matrix, Material material) {

  // Declarations
  input = strtok(NULL, " ");

  // Load the obj file
  FILE* file = fopen(input, "r");
  
  // Error if file does not exist
  if (file == NULL) {
    cerr << ".obj file does not exist: " << input << endl;
    return;
  }

  // More declarations
  int linecount = 1;
  char line[256];
  char *tokenised_line;
  float output[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  vector<Vector> vertices;
  vector<Vector> vnormals;
  vector<Vector> texture_coords;

  // Create offset and provide "nonexistent" coordinate
  vertices.push_back(Vector(0, 0, 0));
  vnormals.push_back(Vector(0, 0, 0));
  texture_coords.push_back(Vector(0, 0, 0));

  while (fgets(line, sizeof(line), file)) {
    
    // Tokenise the line, and get rid of header
    tokenised_line = strtok(line, " ");
    
    if (strcmp(tokenised_line, "v") == 0) {

      InputUtils::parse_float_input(tokenised_line, output);
      Vector vertex = Vector(output[0], output[1], output[2]);
      vertices.push_back(vertex);
    
    } else if (strcmp(tokenised_line, "vn") == 0) {
      
      InputUtils::parse_float_input(tokenised_line, output);
      Vector normal = Vector(output[0], output[1], output[2]);
      vnormals.push_back(normal);
    
    } else if (strcmp(tokenised_line, "f") == 0) {

      int vertnum[3] = {0, 0, 0};
      int vnormnum[3] = {0, 0, 0};
      int tcoordnum[3] = {0, 0, 0};

      int success = InputUtils::parse_face_input(tokenised_line, vertnum, vnormnum, 
          tcoordnum, linecount);
      if (success != 0) {
        linecount++;
        continue;
      }

      Triangle* triangle;
      
      try {

        Vector point1 = vertices.at(vertnum[0]);
        Vector point2 = vertices.at(vertnum[1]);
        Vector point3 = vertices.at(vertnum[2]);
        Vector coord1 = texture_coords.at(tcoordnum[0]);
        Vector coord2 = texture_coords.at(tcoordnum[1]);
        Vector coord3 = texture_coords.at(tcoordnum[2]);

        if (vnormnum[0] == 0 && vnormnum[1] == 0 && vnormnum[2] == 0) {
          // Check direction of normal in relation to camera
          point1 = Matrix::transform(transform_matrix, point1);
          point2 = Matrix::transform(transform_matrix, point2);
          point3 = Matrix::transform(transform_matrix, point3);
          Vector U = point2 - point1;
          Vector V = point3 - point1;
          Vector normal = Vector::cross(U, V);
          Vector view = (point1 + point2 + point3) / 3 - scene->camera.origin;
          if (Vector::dot(normal, view) > 0) {
            triangle = new Triangle(Matrix::identity_matrix(), point1, point3, point2, -1*normal, material);
          } else {
            triangle = new Triangle(Matrix::identity_matrix(), point1, point2, point3, normal, material);
          }
          triangle->tcoord1 = coord1;
          triangle->tcoord2 = coord2;
          triangle->tcoord3 = coord3;
        } else {
          Vector norm1 = vnormals.at(vnormnum[0]);
          Vector norm2 = vnormals.at(vnormnum[1]);
          Vector norm3 = vnormals.at(vnormnum[2]);
          triangle = new Triangle(transform_matrix, point1, point2, point3,
              norm1, norm2, norm3, coord1, coord2, coord3, material);
        }

      } catch (const std::out_of_range& e) {
        cerr << "Line " << linecount << " of .obj file does not contain valid parameters. Line ignored." << endl;
        linecount++;
        continue;
      }

      scene->add_surface(triangle);

    } else if (strcmp(tokenised_line, "vt") == 0) {
      
      InputUtils::parse_float_input(tokenised_line, output);
      Vector tcoord = Vector(output[0], output[1], 0);
      texture_coords.push_back(tcoord);
    
    } else if (tokenised_line[0] == '#') {
      linecount++;
      continue;
    } else {
      cerr << "Command \"" << tokenised_line << "\" unrecognized. Line " <<
          linecount << " of .obj file ignored." << endl;
    }

    linecount++;
    
  }

  // Close the file
  fclose(file);
  
}

int InputUtils::parse_face_input(char* input, int* vertnum, int* vnormnum,
    int* tcoordnum, int linecount) {

  // Declarations
  int i = 0;
  
  // Strip the header
  input = strtok(NULL, " ");
  
  // Until the end of input is reached
  while (input != NULL) {

    // Can only support exactly 3 vertices
    if (i >= 3) {
      cerr << "Line " << linecount << " of .obj file has extra parameters, which were ignored." << endl;
      break;
    }

    // Extract vertex from input
    if (!isdigit(input[0])) {
      cerr << "Line " << linecount << " of .obj file was not formatted correctly, and was ignored." << endl;
      return 1;
    }
    vertnum[i] = atoi(input);

    // Attempt to extract tcoord
    if (strchr(input, '/') != NULL) {
      input = strpbrk(input, "/") + 1;
      tcoordnum[i] = atoi(input);
    }

    // Attempt to extract vnorm
    if (strchr(input, '/') != NULL) {
      input = strpbrk(input, "/") + 1;
      vnormnum[i] = atoi(input);
    }
    
    // Hop to the next input
    input = strtok(NULL, " ");
    i++;
  }

  // Can only support exactly 3 vertices
  if (i < 3) {
    cerr << "Line " << linecount << " of .obj file does not contain enough parameters, and was ignored." << endl;
    return 1;
  }

  return 0;

}

void InputUtils::parse_ptlight_input(Scene* scene, char* input, 
    Matrix transform_matrix) {
  
  // Declarations
  PointLight ptlight;
  float output[7];
  
  // Default falloff to 0
  output[6] = 0; 
  
  parse_float_input(input, output);
  
  ptlight.position = Vector(output[0], output[1], output[2]);
  ptlight.position = Matrix::transform(transform_matrix, ptlight.position);
  ptlight.color = Vector(output[3], output[4], output[5]);
  ptlight.falloff = (int) output[6];
  
  scene->add_point_light(ptlight);
  
}

void InputUtils::parse_dirlight_input(Scene* scene, char* input, 
    Matrix transform_matrix) {

  // Declarations
  DirLight dirlight;
  float output[6];
  
  parse_float_input(input, output);
  
  dirlight.direction = Vector(output[0], output[1], output[2]);
  dirlight.direction = dirlight.direction.normalize();
  dirlight.direction = Matrix::transform_dir(transform_matrix, 
      dirlight.direction);
  dirlight.color = Vector(output[3], output[4], output[5]);

  scene->add_dir_light(dirlight);
  
} 

void InputUtils::parse_amblight_input(Scene* scene, char* input) {
  
  // Declarations
  Light amblight;
  float output[3];
  
  parse_float_input(input, output);
  
  amblight.color = Vector(output[0], output[1], output[2]);
  scene->add_ambient_light(amblight);
  
}

void InputUtils::parse_material_input(Material* material, char* input) {
  
  // Declarations
  float output[13];
  parse_float_input(input, output);
  
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
  
  parse_float_input(input, output);
  
  /* Create a translation matrix that translates by [x, y, z] */
  translation = Matrix::translation_matrix(output[0], output[1], output[2]);
  // Apply that onto the transform matrix
  *transform_matrix = Matrix::multiply(*transform_matrix, translation);
  
}

void InputUtils::parse_rt_transform_input(char* input, Matrix* transform_matrix) {
  
  // Declarations
  float output[3];
  Matrix rotation;
  
  parse_float_input(input, output);
  
  // Create a rotation matrix that rotates by the exponential map [x, y, z]
  rotation = Matrix::rotation_matrix(output[0], output[1], output[2]);

  // Apply that onto the transform matrix
  *transform_matrix = Matrix::multiply(*transform_matrix, rotation);
  
}

void InputUtils::parse_scl_transform_input(char* input, Matrix* transform_matrix) {
  
  // Declarations
  float output[3];
  Matrix scalar;
  
  parse_float_input(input, output);
  
  // Create a scalar matrix that scales to [x, y, z]
  scalar = Matrix::scalar_matrix(output[0], output[1], output[2]);
  
  // Apply that onto the transform matrix
  *transform_matrix = Matrix::multiply(*transform_matrix, scalar);
  
}

void InputUtils::parse_idt_transform_input(Matrix* transform_matrix) {
  
  // Set the matrix back to the identity
  *transform_matrix = Matrix::identity_matrix();
  
}

void InputUtils::parse_antialias_input(char* input) {

  float output[1];
  
  parse_float_input(input, output);

  Sampler::samples = (int) output[0];

}
