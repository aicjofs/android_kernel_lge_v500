/*
                                 
  
                        
 */
#include <asm/io.h>
#include <asm/reboot.h>
#include <asm/sni.h>

/*
                                                          
                                                                   
                                                          
 */
static inline void kb_wait(void)
{
	int i;

	for (i = 0; i < 0x10000; i++)
		if ((inb_p(0x64) & 0x02) == 0)
			break;
}

/*                                                  */
void sni_machine_restart(char *command)
{
	int i, j;

	/*                                                          
                               */
	local_irq_disable();
	for (;;) {
		for (i = 0; i < 100; i++) {
			kb_wait();
			for (j = 0; j < 100000 ; j++)
				/*         */;
			outb_p(0xfe, 0x64);	 /*                 */
		}
	}
}

void sni_machine_power_off(void)
{
	*(volatile unsigned char *)PCIMT_CSWCSM = 0xfd;
}
