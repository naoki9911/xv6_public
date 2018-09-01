#ifndef PKTS_HDR_H
#define PKTS_HDR_H
#include "types.h"

#define PKT_SIZE 1600
#define ETH_TYPE_ARP 0x0806

struct eth_pkt {
//  uchar pre_amb[8];
  uchar dst_mac[6];
  uchar src_mac[6];
  ushort type;
};

struct arp_pkt {
  ushort hrd_type;
  ushort pro_type;
  ushort hrd_len;
  ushort pro_len;
  ushort op;
  uchar src_mac[6];
  uchar src_ip[4];
  uchar dst_mac[6];
  uchar dst_ip[6];
};

#define ETH_TYPE_IPV4 0x0800

const static uchar my_ip[4] = {192,168,1,37};
const static uchar my_mac[6] = {0xf4,0x8c,0x50,0x30,0xda,0x4a};
#endif
