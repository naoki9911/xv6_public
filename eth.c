#include "pkts_hdr.h"
#include "arp.h"
#include "types.h"
#include "eth.h"
#include "defs.h"
#include "ipv4.h"
void eth_proc(uint buffer_addr){
  struct eth_pkt *eth_pkt = (struct eth_pkt *)buffer_addr;
  uint pkt_addr = buffer_addr+sizeof(struct eth_pkt);
  if(eth_pkt->type[0] == 0x08 && eth_pkt->type[1] == 0x06){
    arp_proc(pkt_addr);
  }else if(eth_pkt->type[0] == 0x08 && eth_pkt->type[1] == 0x00){
    ipv4_proc(pkt_addr);
  }else{
  }
}

