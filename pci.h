#ifndef PCI_H_
#define PCI_H_
#include "types.h"
struct pci_dev {
  uchar bus_num;
  uchar device_num;
  uchar function_num;
  uchar reg_addr;
};

void pci_write_config(uint config);
void pci_read_config(uint *config);
void pci_access_config(uint bus_num,uint device_num,uint function_num,uint reg_addr,uint *data);
void pci_init();
void pci_init_device(uint bus_num,uint device_num,uint function_num);
void pci_test();
#endif
