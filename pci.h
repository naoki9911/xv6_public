#ifndef PCI_H_
#define PCI_H_
#include "types.h"
struct pci_dev {
  uchar bus_num;
  uchar device_num;
  uchar function_num;
  uchar reg_addr;
};

void pci_access_config(struct pci_dev *pci_dev);
void pci_init();
#endif
