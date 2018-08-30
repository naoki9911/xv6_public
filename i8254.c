#include "i8254.h"
#include "pci.h"
#include "defs.h"
#include "memlayout.h"
#include "defs.h"

uint base_addr;
uchar mac_addr[6] = {0};
void i8254_init(struct pci_dev *dev){
  uint cmd_reg;
  //Enable Bus Master and Disable Interrupts
  pci_access_config(dev->bus_num,dev->device_num,dev->function_num,0x04,&cmd_reg);
  cmd_reg = cmd_reg | PCI_CMD_BUS_MASTER | PCI_CMD_INTR_DISABLE;
  pci_write_config_register(dev->bus_num,dev->device_num,dev->function_num,0x04,cmd_reg);
  
  base_addr = PCI_P2V(dev->bar0);
  uint *ctrl = (uint *)base_addr;
  //Disable Interrupts
  uint *imc = (uint *)(base_addr+0xD8);
  *imc = 0xFFFFFFFF;
  
  //Reset NIC
  *ctrl = *ctrl | I8254_CTRL_RST;

  //Disable Interrupts again
  *imc = 0xFFFFFFFF;

  //Enable Link
  *ctrl |= I8254_CTRL_SLU;
  
  //General Configuration
  *ctrl &= (~I8254_CTRL_PHY_RST | ~I8254_CTRL_VME | ~I8254_CTRL_ILOS);
  cprintf("E1000 General Configuration Done\n");

  i8254_init_recv();
}

void i8254_init_recv(){
  
  uint data_l = i8254_read_eeprom(0x0);
  mac_addr[0] = data_l&0xFF;
  mac_addr[1] = data_l>>8;
  uint data_m = i8254_read_eeprom(0x1);
  mac_addr[2] = data_m&0xFF;
  mac_addr[3] = data_m>>8;
  uint data_h = i8254_read_eeprom(0x2);
  mac_addr[4] = data_h&0xFF;
  mac_addr[5] = data_h>>8;
  
  cprintf("MAC Address %x:%x:%x:%x:%x:%x\n",
      mac_addr[0],
      mac_addr[1],
      mac_addr[2],
      mac_addr[3],
      mac_addr[4],
      mac_addr[5]);

  uint *ral = (uint *)(base_addr + 0x5400);
  uint *rah = (uint *)(base_addr + 0x5404);

  *ral = (data_l | (data_m << 16));
  *rah = (data_h | I8254_RAH_AS_DEST | I8254_RAH_AV);

  uint *mta = (uint *)(base_addr + 0x5200);
  for(int i=0;i<128;i++){
    mta[i] = 0;
  }

  uint *ims = (uint *)(base_addr + 0xD0);
  *ims = (I8254_IMS_RXT0 | I8254_IMS_RXDMT0 | I8254_IMS_RXSEQ | I8254_IMS_LSC);

  uint recv_desc_addr = (uint)kalloc();
  uint *rdbal = (uint *)(base_addr + 0x2800);
  uint *rdbah = (uint *)(base_addr + 0x2804);
  uint *rdlen = (uint *)(base_addr + 0x2808);
  uint *rdh = (uint *)(base_addr + 0x2810);
  uint *rdt = (uint *)(base_addr + 0x2818);

  *rdbal = recv_desc_addr;
  *rdbah = 0;
  *rdlen = sizeof(struct i8254_recv_desc)*I8254_RECV_DESC_NUM;
  *rdh = 0;
  *rdt = I8254_RECV_DESC_NUM;

  struct i8254_recv_desc *recv_desc = (struct i8254_recv_desc *)recv_desc_addr;
  for(int i=0;i<I8254_RECV_DESC_NUM;i++){
    recv_desc[i].len = 0;
    recv_desc[i].chk_sum = 0;
    recv_desc[i].status = 0;
    recv_desc[i].errors = 0;
    recv_desc[i].special = 0;
  }

  for(int i=0;i<(I8254_RECV_DESC_NUM)/2;i++){
    uint buf_addr = (uint)kalloc();
    if(buf_addr == 0){
      cprintf("failed to allocate buffer area\n");
      break;
    }
    recv_desc[i].buf_addr = buf_addr;
    recv_desc[i+1].buf_addr = buf_addr + 0x800;

  }

  uint *rctl = (uint *)(base_addr + 0x100);
  *rctl |= I8254_RCTL_EN;
  cprintf("E1000 Recieve Initialize Done\n");
}

uint i8254_read_eeprom(uint addr){
  uint *eerd = (uint *)(base_addr + 0x14);
  *eerd = (((addr & 0xFF) << 8) | 1);
  while(1){
    cprintf("");
    volatile uint data = *eerd;
    if((data & (1<<4)) != 0){
      break;
    }
  }

  return (*eerd >> 16) & 0xFFFF;
}
