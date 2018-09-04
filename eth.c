#include "pkts_hdr.h"
#include "arp.h"
#include "types.h"
#include "eth.h"
#include "defs.h"

void eth_proc(uint buffer_addr){
  struct eth_pkt *eth_pkt = (struct eth_pkt *)buffer_addr;
  uint pkt_addr = buffer_addr+sizeof(struct eth_pkt);
  if(eth_pkt->type[0] == 0x08 && eth_pkt->type[1] == 0x06){
    cprintf("arp packet");
    arp_proc(pkt_addr);
  }else if(eth_pkt->type[0] == 0x08 && eth_pkt->type[1] == 0x00){
    cprintf("ipv4 packet");
  }else{
    cprintf("ETH TYPE:0x%x\n",eth_pkt->type);
  }
}

