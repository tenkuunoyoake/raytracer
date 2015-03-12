#include "film.h"

//*****************************************************************************
// Film
//*****************************************************************************

void Film::set_pixel(int x, int y, Vector color) {
  
  image[4 * (y * width + x) + 0] = (unsigned char) round(color.x * 255);
  image[4 * (y * width + x) + 1] = (unsigned char) round(color.y * 255);
  image[4 * (y * width + x) + 2] = (unsigned char) round(color.z * 255);
  image[4 * (y * width + x) + 3] = 255;
  
}

void Film::write_to_image() {
  
  unsigned error = lodepng_encode32_file(output, image, width, height);
 
  if (error) {
    printf("Lodepng error: %u: %s\n", error, lodepng_error_text(error));
    exit(EXIT_FAILURE);
  }
  
}

void Film::dispose() {
 
  if (width > 0 && height > 0) {
    free(image);
  }
  
}

// Constructors

Film::Film() {
 
  width = 0;
  height = 0;
  
}

Film::Film(int image_width, int image_height) {
 
  width = image_width;
  height = image_height;
  
  image = (unsigned char*) malloc(image_width * image_height * 4);
  
}