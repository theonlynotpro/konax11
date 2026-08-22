#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <X11/Xutil.h>
#include <png.h>

#include "image.h"


int main(int argc, char *argv[]){

  printf("%s\n", PNG_LIBPNG_VER_STRING);
  Display *display = XOpenDisplay(NULL);

  int screen = DefaultScreen(display);
  Window window = XCreateSimpleWindow(display, DefaultRootWindow(display),
                                      0, 0, 720, 480, 0,
                                      BlackPixel(display, screen),
                                      BlackPixel(display, screen));

  XMapWindow(display, window);
  XFlush(display);

  Image *image t= image_load_png("image.png");

  sleep(2);




  XUnmapWindow(display, window);
  XDestroyWindow(display, window);
  XCloseDisplay(display);
  return EXIT_SUCCESS;
}
