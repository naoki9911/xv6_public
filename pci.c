#include "pci.h"
#include "defs.h"
#include "types.h"

void pci_init(){
  uint data;
  for(int i=0;i<256;i++){
    for(int j=0;j<32;j++){
      for(int k=0;k<8;k++){
      pci_access_config(i,j,k,0,&data);
      if((data&0xFFFF) != 0xFFFF){
        pci_init_device(i,j,k);
      }
      }
    }
  }
}

void pci_write_config(uint config){
  asm("mov $0xCF8,%%edx\n\t"
      "mov %0,%%eax\n\t"
      "out %%eax,%%dx\n\t"
      : :"r"(config));
}

uint pci_read_config(){
  uint data;
  asm("mov $0xCFC,%%edx\n\t"
      "in %%dx,%%eax\n\t"
      "mov %%eax,%0"
      :"=m"(data):);
  cprintf("");
  return data;
}

void pci_test(){
  uint data = 0x80001804;
  pci_write_config(data);
}

void pci_access_config(uint bus_num,uint device_num,uint function_num,uint reg_addr,uint *data){
  uint config_addr = ((bus_num & 0xFF)<<16) | ((device_num & 0x1F)<<11) | ((function_num & 0x7)<<8) |
    (reg_addr & 0xFC) | 0x80000000;
  pci_write_config(config_addr);
  *data = pci_read_config();
}

void pci_init_device(uint bus_num,uint device_num,uint function_num){
  uint data;
  cprintf("PCI Device Found Bus:0x%x Device:0x%x Function:%x\n",bus_num,device_num,function_num);
  pci_access_config(bus_num,device_num,function_num,0,&data);
  uint device_id = data>>16;
  uint vendor_id = data&0xFFFF;
  data = 0;
  cprintf("  Device ID:0x%x  Vendor ID:0x%x\n",device_id,vendor_id);
  pci_access_config(bus_num,device_num,function_num,0x4,&data);
  cprintf("  Status:0x%x  Command:0x%x\n",data>>16,data&0xFFFF);
  pci_access_config(bus_num,device_num,function_num,0x8,&data);
  cprintf("  Base Class:0x%x  Sub Class:0x%x  Interface:0x%x  Revision ID:0x%x\n",
      data>>24,(data>>16)&0xFF,(data>>8)&0xFF,data&0xFF);
  pci_access_config(bus_num,device_num,function_num,0x10,&data);
  if(data != 0) cprintf("  BAR0:%x\n",data);
  pci_access_config(bus_num,device_num,function_num,0x14,&data);
  if(data != 0) cprintf("  BAR1:%x\n",data);
  pci_access_config(bus_num,device_num,function_num,0x18,&data);
  if(data != 0) cprintf("  BAR2:%x\n",data);
  pci_access_config(bus_num,device_num,function_num,0x1C,&data);
  if(data != 0) cprintf("  BAR3:%x\n",data);
  pci_access_config(bus_num,device_num,function_num,0x20,&data);
  if(data != 0) cprintf("  BAR4:%x\n",data);
}
