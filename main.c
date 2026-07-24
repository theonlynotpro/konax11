#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <X11/Xutil.h>


int main(int argc, char *argv[]){


  Display* display = XOpenDisplay(NULL);

  int screen = DefaultScreen(display);
  Window window = XCreateSimpleWindow(display, DefaultRootWindow(display),
                                      0, 0, 720, 480, 0,
                                      BlackPixel(display, screen),
                                      BlackPixel(display, screen));

  XMapWindow(display, window);
  XFlush(display);

  sleep(2);



  printf("%p\n", (void*)display);

  XUnmapWindow(display, window);
  XDestroyWindow(display, window);
  XCloseDisplay(display);
  return EXIT_SUCCESS;
}
