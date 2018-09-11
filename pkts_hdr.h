#ifndef PKTS_HDR_H
#define PKTS_HDR_H
#include "types.h"

#define PKT_SIZE 1600
#define ETH_TYPE_ARP_HOST 0x0806
#define ETH_TYPE_ARP_NET 0x0608

struct __attribute__((packed)) eth_pkt {
//  uchar pre_amb[8];
  uchar dst_mac[6];
  uchar src_mac[6];
  uchar type[2];
};

struct __attribute__((packed)) arp_pkt {
  ushort hrd_type;
  ushort pro_type;
  uchar hrd_len;
  uchar pro_len;
  ushort op;
  uchar src_mac[6];
  uchar src_ip[4];
  uchar dst_mac[6];
  uchar dst_ip[6];
};

struct __attribute__((packed)) ipv4_pkt {
  uchar ver;
  uchar srv_type;
  ushort total_len;
  ushort id;
  ushort fragment;
  uchar src_ip[4];
  uchar dst_ip[4];  
  uchar option[3];
  uchar padding;
};


#define ETH_TYPE_IPV4_HOST 0x0800
#define ETH_TYPE_IPV4_NET 0x0008

#endif
