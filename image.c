#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <Imlib2.h>

//copy and pasted code idgaf
Image *image_load_png(const char *filename){
  FILE *fp = fopen(filename, "rb");
  if (!fp){
    return NULL;
  }
  Image *image = malloc(sizeof(Image));

}
