#include "ipv4.h"
#include "defs.h"
#include "i8254.h"
#include "arp.h"
#include "ipv4.h"
#include "types.h"

extern uchar mac_addr[6];
extern uchar my_ip[4];

int ip_id = -1;
void ipv4_proc(uint buffer_addr){
  struct ipv4_pkt *ipv4_p = (struct ipv4_pkt *)(buffer_addr);
  if(ip_id != ipv4_p->id){
    cprintf("IPv4 ID:0x%x\n",ipv4_p->id);
    ip_id = ipv4_p->id;
  }
}
