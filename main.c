#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <X11/Xutil.h>
#include <Imlib2.h>

int width, height;
const int FRAME_DELAY = 1000000 / 30; 



int main(int argc, char *argv[]){


  Display *display = XOpenDisplay(NULL);

  int screen = DefaultScreen(display);
  XVisualInfo vinfo;
  if (!XMatchVisualInfo(display, screen, 32, TrueColor, &vinfo)) {
      fprintf(stderr, "No 32-bit visual found. Transparency unsupported.\n");
      XCloseDisplay(display);
      return 1;
   }

  Window root = RootWindow(display, screen);

  Imlib_Image img = imlib_load_image("img/frame001.png");
  if (img) {
    imlib_context_set_image(img);
    width = imlib_image_get_width();
    height = imlib_image_get_height();
    imlib_free_image();
  }


  //set window atributes
  XSetWindowAttributes attrs;
  attrs.colormap = XCreateColormap(display, root, vinfo.visual, AllocNone);


  //set background to this color, this is what makes it transparent or sum
  attrs.background_pixel = 0x00000000; 



  Window window = XCreateWindow(display, root, 100, 100, 400, 300, 0, vinfo.depth, InputOutput, vinfo.visual, CWColormap | CWBorderPixel | CWBackPixel, &attrs);


  Pixmap buffer = XCreatePixmap(display, window, width, height, vinfo.depth);

  GC gc = XCreateGC(display, window, 0, NULL);


  imlib_context_set_display(display);
  imlib_context_set_visual(vinfo.visual);
  imlib_context_set_colormap(attrs.colormap);
  imlib_context_set_drawable(buffer);



  
  XMapWindow(display, window);

  XSelectInput(display, window, ExposureMask | KeyPressMask);
  XStoreName(display, window, "konax11");

  XEvent ev;
  int running = 1;
  int cur_frame = 1;
  char cur_filename[32];
  while (running) {
    while (XPending(display)){
        XNextEvent(display, &ev);
    }
    
      

    XFlush(display);

    sprintf(cur_filename, "img/frame%03d.png", cur_frame);

    img = imlib_load_image(cur_filename);

    if (img) {
        XSetForeground(display, gc, 0x00000000);
        XFillRectangle(display, buffer, gc, 0, 0, width, height);

        imlib_context_set_image(img);
        imlib_render_image_on_drawable(0, 0);
        XCopyArea(display, buffer, window, gc, 0, 0, width, height, 0, 0);
        imlib_free_image();
        img = NULL;
    }
    XFlush(display);
    cur_frame++;
    if (cur_frame > 13){
        cur_frame = 1;
    }
    usleep(FRAME_DELAY);


  }



  
  printf("%d  and %d", height, width);

  XSync(display, False);


  XFreeGC(display, gc);
  XFreePixmap(display, buffer);



  XUnmapWindow(display, window);
  XDestroyWindow(display, window);
  XCloseDisplay(display);
  return EXIT_SUCCESS;
}
