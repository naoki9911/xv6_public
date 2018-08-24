#include "graphic.h"
#include "font_bin.h"
#include "font.h"


struct graphic_pixel black_pixel = {0x0,0x0,0x0,0x0};
struct graphic_pixel white_pixel = {0xFF,0xFF,0xFF,0x0};
void font_render(int x,int y,int index){
  int bin;
  for(int i=0;i<30;i++){
    for(int j=14;j>-1;j--){
      bin = (font_bin[index][i])&(1 << j);
      if(bin == (1 << j)){
        graphic_draw_pixel(x+(14-j),y+i,&white_pixel);
      } else {
        graphic_draw_pixel(x+(14-j),y+i,&black_pixel);
      }
    }
  }
}

void font_hello(void){
  font_render(2,2,39);
  font_render(17,2,68);
  font_render(32,2,75);
  font_render(47,2,75);
  font_render(62,2,78);
  font_render(77,2,54);
  font_render(92,2,78);
  font_render(107,2,81);
  font_render(122,2,75);
  font_render(137,2,67);

}
