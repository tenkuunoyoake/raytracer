#ifndef FILM_H
#define FILM_H
#endif

#include <stdlib.h>
#include <math.h>

#include <lodepng.h>

#ifndef VECTOR_H
#include <vector.h>
#endif

//*****************************************************************************
// Film
//*****************************************************************************

class Film {
  
  public:
      
    // Declarations
    int width;
    int height;
    char* output;
    
    // Methods
    void set_pixel(int x, int y, Vector color);
    void write_to_image();
    void dispose();
    
    // Constructor
    Film();
    Film(int image_width, int image_height);
    
  private:
    
    unsigned char* image;
  
};