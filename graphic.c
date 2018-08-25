#include "graphic.h"
#include "mp_uefi.h"
#include "memlayout.h"

/*
 * i%4 = 0 : blue
 * i%4 = 1 : green
 * i%4 = 2 : red
 * i%4 = 3 : black
 */
struct graphic_config graphic_conf;
unsigned char *frame;
void graphic_init(){
  frame = (unsigned char *)(VRAMBASE_MAPPED);
  
  /*for(long i=0;i<VRAMSIZE;i++){
    if(i%4 != 3){
      *(frame+i) = 0xFF;
    }else{
      *(frame+i) = 0x00;
    }
  }*/
}

void graphic_draw_box(){


}

void graphic_draw_pixel(int x,int y,struct graphic_pixel * buffer){
  int pixel_addr = (sizeof(struct graphic_pixel))*(y*HORIZONTAL_PIXELS + x);
  struct graphic_pixel *pixel = (struct graphic_pixel *)(VRAMBASE_MAPPED + pixel_addr);
  pixel->blue = buffer->blue;
  pixel->green = buffer->green;
  pixel->red = buffer->red;
}

void graphic_scroll_up(int height){

}
