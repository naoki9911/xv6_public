#include "pci.h"
#include "defs.h"
#include "types.h"

void pci_init(){
  struct pci_dev pci_test = {1,1,0,0};
  for(int i=0;i<256;i++){
    pci_test.bus_num = i;
    for(int j=0;j<32;j++){
      pci_test.device_num = j;
      pci_access_config(&pci_test);
    }
  }
}
void pci_write_config(uint config){
  asm("mov $0xCF8,%edx");
  asm("mov %0,%%eax": :"m"(config));
  asm("out %eax,%dx");
}

void pci_read_config(uint *config){
  asm("mov $0xCFC,%edx");
  asm("in %dx,%eax");
  asm("mov %%eax,%0":"=m"(*config):);
}

void pci_access_config(struct pci_dev *pci_dev){
  uint config_addr = 0x80000000;
  config_addr += (pci_dev->bus_num & 0xFF)<<16;
  config_addr += (pci_dev->device_num & 0x1F)<<11;
  config_addr += (pci_dev->function_num & 0x7)<<8;
  config_addr += (pci_dev->reg_addr & 0x3F)<<2;
  pci_write_config(config_addr);
  uint config;
  pci_read_config(&config);
  uint device_id = config>>16;
  uint vendor_id = config&0xFF;
  if((config&0xFFFF) != 0xFFFF){
    cprintf("PCI Device found   Bus:0x%x Device Number:0x%x\n",pci_dev->bus_num,pci_dev->device_num);
    cprintf("  Device ID:0x%x  Vendor ID:0x%x\n",device_id,vendor_id);
  }
}
