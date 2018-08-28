#include "pci.h"
#include "defs.h"
#include "types.h"

void pci_init(){
  uint data;
  for(int i=0;i<1;i++){
    for(int j=0;j<4;j++){
      data=0xFFFF;
      pci_access_config(i,j,0,0,&data);
      if((data&0xFFFF) != 0xFFFF){
        pci_init_device(i,j,0);
      }
    }
  }
}

void pci_write_config(uint config){
  asm("mov $0xCF8,%edx");
  asm("movl %0,%%eax": :"m"(config));
  asm("out %eax,%dx");
  cprintf("");
}

void pci_read_config(uint *config){
  asm("xor %eax,%eax");
  asm("mov $0xCFC,%edx");
  asm("in %dx,%eax");
  asm("movl %%eax,%0":"=m"(*config):);
}

void pci_test(){
  uint data = 0x80001804;
  pci_write_config(data);
}

void pci_access_config(uint bus_num,uint device_num,uint function_num,uint reg_addr,uint *data){
  uint config_addr = ((bus_num & 0xFF)<<16) | ((device_num & 0x1F)<<11) | (function_num & 0x7<<8) |
    (reg_addr & 0xFC) | 0x80000000;
  pci_write_config(config_addr);
  uint res;
  pci_read_config(&res);
  *data = res;
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
  cprintf("  Status:0x%x  Command:%x\n",data>>16,data&0xFFFF);
  pci_access_config(bus_num,device_num,function_num,0x8,&data);
  cprintf("  Base Class:0x%x  Sub Class:%x  Interface:%x  Revision ID:%x\n",
      data>>24,(data>>16)&0xFF,(data>>8)&0xFF,data&0xFF);
  pci_access_config(bus_num,device_num,function_num,0x10,&data);
  cprintf("  BAR0:%x\n",data);
  pci_access_config(bus_num,device_num,function_num,0x14,&data);
  cprintf("  BAR1:%x\n",data);
}
