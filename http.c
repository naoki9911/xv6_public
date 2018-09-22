#include "http.h"
#include "defs.h"
#include "types.h"


void http_proc(uint recv, uint recv_size, uint send, uint *send_size){
  int len;
  len = http_strcpy((char *)send,"HTTP/1.0 200 OK \r\n",0);
  if(len%2 != 0){
    char *payload = (char *)send;
    payload[len] = 0;
    len++;
  }
  *send_size = len;
}

int http_strcpy(char *dst,const char *src,int start_index){
  int i = 0;
  while(src[i]){
    dst[start_index+i] = src[i];
    i++;
  }
  return i;
}
