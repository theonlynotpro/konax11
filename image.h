#ifndef IMAGE_H
#define IMAGE_H

#include <png.h>

typedef struct {
  int width;
  int height;
  png_byte color_type;
  png_byte bit_depth;
  png_bytep *row_pointers;
} Image;


Image *image_load_png(const char *filename);
void image_free(Image *image);
#endif // IMAGE_H

