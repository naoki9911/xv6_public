#ifndef GRAPHIC_H_
#define GRAPHIC_H_

struct graphic_config {
  long long frame_base;
  long long frame_size;
  long long horizontal_resolution;
  long long vertical_resolution;
  long long pixels_per_scan_line;
};

void graphic_init();
void graphic_draw_box();
void graphic_draw_pixel(int x,int y);

#define VRAMBASE 0x80000000
#define VRAMSIZE 0x1D5000

#endif
