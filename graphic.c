#include "graphic.h"
#include "mp_uefi.h"
#include "memlayout.h"

struct graphic_config graphic_conf;
unsigned char *frame;
void graphic_init(){
  frame = (unsigned char *)(DEVSPACE - VRAMSIZE);
  
  for(long i=0;i<VRAMSIZE;i++){
    if(i%3 == 1){
      *(frame+i) = 0xFF;
    }else{
      *(frame+i) = 0x00;
    }
  }
}

void graphic_draw_box(){


}

void graphic_draw_pixel(int x,int y){


}
