/*
 * arch/arm/mach-orion5x/include/mach/orion5x.h
 *
 * Generic definitions of Orion SoC flavors:
 *  Orion-1, Orion-VoIP, Orion-NAS, Orion-2, and Orion-1-90.
 *
 * Maintainer: Tzachi Perelstein <tzachi@marvell.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __ASM_ARCH_ORION5X_H
#define __ASM_ARCH_ORION5X_H

/*                                                                            
                     
  
       
                          
                         
                                                  
                                        
                          
                         
                                              
                                      
                                     
                                     
                                         
  
                   
                                                    
                                      
                                     
                                                               
                                                                            */
#define ORION5X_REGS_PHYS_BASE		0xf1000000
#define ORION5X_REGS_VIRT_BASE		0xfdd00000
#define ORION5X_REGS_SIZE		SZ_1M

#define ORION5X_PCIE_IO_PHYS_BASE	0xf2000000
#define ORION5X_PCIE_IO_VIRT_BASE	0xfde00000
#define ORION5X_PCIE_IO_BUS_BASE	0x00000000
#define ORION5X_PCIE_IO_SIZE		SZ_1M

#define ORION5X_PCI_IO_PHYS_BASE	0xf2100000
#define ORION5X_PCI_IO_VIRT_BASE	0xfdf00000
#define ORION5X_PCI_IO_BUS_BASE		0x00100000
#define ORION5X_PCI_IO_SIZE		SZ_1M

#define ORION5X_SRAM_PHYS_BASE		(0xf2200000)
#define ORION5X_SRAM_SIZE		SZ_8K

/*                                     */
#define ORION5X_PCIE_WA_PHYS_BASE	0xf0000000
#define ORION5X_PCIE_WA_VIRT_BASE	0xfe000000
#define ORION5X_PCIE_WA_SIZE		SZ_16M

#define ORION5X_PCIE_MEM_PHYS_BASE	0xe0000000
#define ORION5X_PCIE_MEM_SIZE		SZ_128M

#define ORION5X_PCI_MEM_PHYS_BASE	0xe8000000
#define ORION5X_PCI_MEM_SIZE		SZ_128M

/*                                                                              
                      
                                                                              */

#define ORION5X_DDR_VIRT_BASE		(ORION5X_REGS_VIRT_BASE | 0x00000)
#define  ORION5X_DDR_WINDOW_CPU_BASE    (ORION5X_DDR_VIRT_BASE | 0x1500)
#define ORION5X_DEV_BUS_PHYS_BASE	(ORION5X_REGS_PHYS_BASE | 0x10000)
#define ORION5X_DEV_BUS_VIRT_BASE	(ORION5X_REGS_VIRT_BASE | 0x10000)
#define ORION5X_DEV_BUS_REG(x)		(ORION5X_DEV_BUS_VIRT_BASE | (x))
#define  GPIO_VIRT_BASE			ORION5X_DEV_BUS_REG(0x0100)
#define  SPI_PHYS_BASE			(ORION5X_DEV_BUS_PHYS_BASE | 0x0600)
#define  I2C_PHYS_BASE			(ORION5X_DEV_BUS_PHYS_BASE | 0x1000)
#define  UART0_PHYS_BASE		(ORION5X_DEV_BUS_PHYS_BASE | 0x2000)
#define  UART0_VIRT_BASE		(ORION5X_DEV_BUS_VIRT_BASE | 0x2000)
#define  UART1_PHYS_BASE		(ORION5X_DEV_BUS_PHYS_BASE | 0x2100)
#define  UART1_VIRT_BASE		(ORION5X_DEV_BUS_VIRT_BASE | 0x2100)

#define ORION5X_BRIDGE_VIRT_BASE	(ORION5X_REGS_VIRT_BASE | 0x20000)

#define ORION5X_PCI_VIRT_BASE		(ORION5X_REGS_VIRT_BASE | 0x30000)

#define ORION5X_PCIE_VIRT_BASE		(ORION5X_REGS_VIRT_BASE | 0x40000)

#define ORION5X_USB0_PHYS_BASE		(ORION5X_REGS_PHYS_BASE | 0x50000)
#define ORION5X_USB0_VIRT_BASE		(ORION5X_REGS_VIRT_BASE | 0x50000)

#define ORION5X_XOR_PHYS_BASE		(ORION5X_REGS_PHYS_BASE | 0x60900)
#define ORION5X_XOR_VIRT_BASE		(ORION5X_REGS_VIRT_BASE | 0x60900)

#define ORION5X_ETH_PHYS_BASE		(ORION5X_REGS_PHYS_BASE | 0x70000)
#define ORION5X_ETH_VIRT_BASE		(ORION5X_REGS_VIRT_BASE | 0x70000)

#define ORION5X_SATA_PHYS_BASE		(ORION5X_REGS_PHYS_BASE | 0x80000)
#define ORION5X_SATA_VIRT_BASE		(ORION5X_REGS_VIRT_BASE | 0x80000)

#define ORION5X_CRYPTO_PHYS_BASE	(ORION5X_REGS_PHYS_BASE | 0x90000)

#define ORION5X_USB1_PHYS_BASE		(ORION5X_REGS_PHYS_BASE | 0xa0000)
#define ORION5X_USB1_VIRT_BASE		(ORION5X_REGS_VIRT_BASE | 0xa0000)

/*                                                                              
                       
                                                                              */
#define MPP_0_7_CTRL		ORION5X_DEV_BUS_REG(0x000)
#define MPP_8_15_CTRL		ORION5X_DEV_BUS_REG(0x004)
#define MPP_16_19_CTRL		ORION5X_DEV_BUS_REG(0x050)
#define MPP_DEV_CTRL		ORION5X_DEV_BUS_REG(0x008)
#define MPP_RESET_SAMPLE	ORION5X_DEV_BUS_REG(0x010)
#define DEV_BANK_0_PARAM	ORION5X_DEV_BUS_REG(0x45c)
#define DEV_BANK_1_PARAM	ORION5X_DEV_BUS_REG(0x460)
#define DEV_BANK_2_PARAM	ORION5X_DEV_BUS_REG(0x464)
#define DEV_BANK_BOOT_PARAM	ORION5X_DEV_BUS_REG(0x46c)
#define DEV_BUS_CTRL		ORION5X_DEV_BUS_REG(0x4c0)
#define DEV_BUS_INT_CAUSE	ORION5X_DEV_BUS_REG(0x4d0)
#define DEV_BUS_INT_MASK	ORION5X_DEV_BUS_REG(0x4d4)

/*                                                                              
                                
                                                                              */
/*                                             */
#define MV88F5181_DEV_ID	0x5181
#define MV88F5181_REV_B1	3
#define MV88F5181L_REV_A0	8
#define MV88F5181L_REV_A1	9
/*                     */
#define MV88F5182_DEV_ID	0x5182
#define MV88F5182_REV_A2	2
/*                   */
#define MV88F5281_DEV_ID	0x5281
#define MV88F5281_REV_D0	4
#define MV88F5281_REV_D1	5
#define MV88F5281_REV_D2	6
/*                      */
#define MV88F6183_DEV_ID	0x6183
#define MV88F6183_REV_B0	3

#endif
