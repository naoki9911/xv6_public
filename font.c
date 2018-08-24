#include "graphic.h"
#include "font_bin.h"
#include "font.h"


struct graphic_pixel black_pixel = {0x0,0x0,0x0,0x0};
struct graphic_pixel white_pixel = {0xFF,0xFF,0xFF,0x0};
void font_render(int x,int y,int index){
  int bin;
  for(int i=0;i<30;i++){
    for(int j=14;j>-1;j--){
      bin = (font_bin[index-0x20][i])&(1 << j);
      if(bin == (1 << j)){
        graphic_draw_pixel(x+(14-j),y+i,&white_pixel);
      } else {
        graphic_draw_pixel(x+(14-j),y+i,&black_pixel);
      }
    }
  }
}

void font_hello(void){
  font_render(2,2,'H');
  font_render(17,2,'e');
  font_render(32,2,'l');
  font_render(47,2,'l');
  font_render(62,2,'o');
  font_render(77,2,' ');
  font_render(92,2,'W');
  font_render(107,2,'o');
  font_render(122,2,'r');
  font_render(137,2,'l');
  font_render(152,2,'d');

  font_render(2,32,'H');
  font_render(17,32,'e');
  font_render(32,32,'l');
  font_render(47,32,'l');
  font_render(62,32,'o');
  font_render(77,32,' ');
  font_render(92,32,'X');
  font_render(107,32,'V');
  font_render(122,32,'6');
  font_render(137,32,'_');
  font_render(152,32,'U');
  font_render(167,32,'E');
  font_render(182,32,'F');
  font_render(197,32,'I');
}

void font_render_string(char *string,int row){
  int i = 0;
  while(string[i] && i < 52){
    font_render(i*15+2,row*30,string[i]);
    i++;
  }
}
