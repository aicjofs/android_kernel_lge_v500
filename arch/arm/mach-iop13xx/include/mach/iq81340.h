#ifndef _IQ81340_H_
#define _IQ81340_H_

#define IQ81340_PCE_BAR0    IOP13XX_PBI_LOWER_MEM_RA
#define IQ81340_PCE_BAR1    (IQ81340_PCE_BAR0 + 0x02000000)

#define IQ81340_FLASHBASE   IQ81340_PCE_BAR0	/*       */

#define IQ81340_PCE_BAR1_OFFSET(a) (IQ81340_PCE_BAR1 + (a))

#define IQ81340_PRD_CODE    IQ81340_PCE_BAR1_OFFSET(0)
#define IQ81340_BRD_STEP    IQ81340_PCE_BAR1_OFFSET(0x10000)
#define IQ81340_CPLD_REV    IQ81340_PCE_BAR1_OFFSET(0x20000)
#define IQ81340_LED	     IQ81340_PCE_BAR1_OFFSET(0x30000)
#define IQ81340_LHEX	     IQ81340_PCE_BAR1_OFFSET(0x40000)
#define IQ81340_RHEX	     IQ81340_PCE_BAR1_OFFSET(0x50000)
#define IQ81340_BUZZER	     IQ81340_PCE_BAR1_OFFSET(0x60000)
#define IQ81340_32K_NVRAM   IQ81340_PCE_BAR1_OFFSET(0x70000)
#define IQ81340_256K_NVRAM  IQ81340_PCE_BAR1_OFFSET(0x80000)
#define IQ81340_ROTARY_SW   IQ81340_PCE_BAR1_OFFSET(0xd0000)
#define IQ81340_BATT_STAT   IQ81340_PCE_BAR1_OFFSET(0xf0000)
#define IQ81340_CMP_FLSH    IQ81340_PCE_BAR1_OFFSET(0x1000000) /*      */

#define PBI_CF_IDE_BASE     (IQ81340_CMP_FLSH)
#define PBI_CF_BAR_ADDR     (IOP13XX_PBI_BAR1)


#endif	/*             */
