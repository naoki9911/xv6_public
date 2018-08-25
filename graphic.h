#ifndef GRAPHIC_H_
#define GRAPHIC_H_
#include "types.h"
#include "memlayout.h"

struct graphic_config {
  long long frame_base;
  long long frame_size;
  long long horizontal_resolution;
  long long vertical_resolution;
  long long pixels_per_scan_line;
};

struct graphic_pixel {
  uchar blue;
  uchar green;
  uchar red;
  uchar black;
};

void graphic_init();
void graphic_draw_box();
void graphic_draw_pixel(int x,int y,struct graphic_pixel *);
void graphic_scroll_up(int height);

#define VRAMBASE 0x80000000
#define VRAMSIZE 0x1D5000
#define VRAMBASE_MAPPED (DEVSPACE-VRAMSIZE)
#define HORIZONTAL_PIXELS 800
#define VERTICAL_PIXELS 600
#define PIXELS_PER_LINE 800

#endif
