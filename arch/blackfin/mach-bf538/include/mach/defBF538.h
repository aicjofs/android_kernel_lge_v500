/*
 * Copyright 2008-2010 Analog Devices Inc.
 *
 * Licensed under the ADI BSD license or the GPL-2 (or later)
 */

#ifndef _DEF_BF538_H
#define _DEF_BF538_H

/*                                                   */
#define	PLL_CTL			0xFFC00000	/*                               */
#define	PLL_DIV			0xFFC00004	/*                              */
#define	VR_CTL			0xFFC00008	/*                                             */
#define	PLL_STAT		0xFFC0000C	/*                              */
#define	PLL_LOCKCNT		0xFFC00010	/*                                  */
#define	CHIPID			0xFFC00014	/*                  */

/*              */
#define CHIPID_VERSION         0xF0000000
#define CHIPID_FAMILY          0x0FFFF000
#define CHIPID_MANUFACTURE     0x00000FFE

/*                                                       */
#define	SWRST			0xFFC00100  /*                                  */
#define	SYSCR			0xFFC00104  /*                              */
#define	SIC_RVECT		0xFFC00108
#define	SIC_IMASK0		0xFFC0010C  /*                         */
#define	SIC_IAR0		0xFFC00110  /*                                 */
#define	SIC_IAR1		0xFFC00114  /*                                 */
#define	SIC_IAR2		0xFFC00118  /*                                 */
#define	SIC_IAR3			0xFFC0011C	/*                                 */
#define	SIC_ISR0			0xFFC00120  /*                           */
#define	SIC_IWR0			0xFFC00124  /*                           */
#define	SIC_IMASK1			0xFFC00128	/*                           */
#define	SIC_ISR1			0xFFC0012C	/*                             */
#define	SIC_IWR1			0xFFC00130	/*                             */
#define	SIC_IAR4			0xFFC00134	/*                                 */
#define	SIC_IAR5			0xFFC00138	/*                                 */
#define	SIC_IAR6			0xFFC0013C	/*                                 */


/*                                          */
#define	WDOG_CTL	0xFFC00200  /*                           */
#define	WDOG_CNT	0xFFC00204  /*                         */
#define	WDOG_STAT	0xFFC00208  /*                          */


/*                                           */
#define	RTC_STAT	0xFFC00300  /*                     */
#define	RTC_ICTL	0xFFC00304  /*                                */
#define	RTC_ISTAT	0xFFC00308  /*                               */
#define	RTC_SWCNT	0xFFC0030C  /*                              */
#define	RTC_ALARM	0xFFC00310  /*                         */
#define	RTC_FAST	0xFFC00314  /*                               */
#define	RTC_PREN		0xFFC00314  /*                                                 */


/*                                            */
#define	UART0_THR	      0xFFC00400  /*                           */
#define	UART0_RBR	      0xFFC00400  /*                         */
#define	UART0_DLL	      0xFFC00400  /*                          */
#define	UART0_IER	      0xFFC00404  /*                           */
#define	UART0_DLH	      0xFFC00404  /*                           */
#define	UART0_IIR	      0xFFC00408  /*                                   */
#define	UART0_LCR	      0xFFC0040C  /*                       */
#define	UART0_MCR			 0xFFC00410  /*                        */
#define	UART0_LSR	      0xFFC00414  /*                      */
#define	UART0_SCR	      0xFFC0041C  /*                      */
#define	UART0_GCTL		     0xFFC00424	 /*                         */


/*                                           */

#define	SPI0_CTL			0xFFC00500  /*                       */
#define	SPI0_FLG			0xFFC00504  /*                    */
#define	SPI0_STAT			0xFFC00508  /*                      */
#define	SPI0_TDBR			0xFFC0050C  /*                                    */
#define	SPI0_RDBR			0xFFC00510  /*                                   */
#define	SPI0_BAUD			0xFFC00514  /*                         */
#define	SPI0_SHADOW			0xFFC00518  /*                           */
#define SPI0_REGBASE			SPI0_CTL


/*                                                   */
#define	TIMER0_CONFIG			0xFFC00600     /*                                */
#define	TIMER0_COUNTER				0xFFC00604     /*                          */
#define	TIMER0_PERIOD			0xFFC00608     /*                         */
#define	TIMER0_WIDTH			0xFFC0060C     /*                        */

#define	TIMER1_CONFIG			0xFFC00610	/*                                   */
#define	TIMER1_COUNTER			0xFFC00614	/*                                */
#define	TIMER1_PERIOD			0xFFC00618	/*                               */
#define	TIMER1_WIDTH			0xFFC0061C	/*                              */

#define	TIMER2_CONFIG			0xFFC00620	/*                                  */
#define	TIMER2_COUNTER			0xFFC00624	/*                              */
#define	TIMER2_PERIOD			0xFFC00628	/*                             */
#define	TIMER2_WIDTH			0xFFC0062C	/*                            */

#define	TIMER_ENABLE				0xFFC00640	/*                       */
#define	TIMER_DISABLE				0xFFC00644	/*                        */
#define	TIMER_STATUS				0xFFC00648	/*                       */


/*                                              */
#define	FIO_FLAG_D				0xFFC00700  /*                                             */
#define	FIO_FLAG_C			0xFFC00704  /*                                            */
#define	FIO_FLAG_S			0xFFC00708  /*                                          */
#define	FIO_FLAG_T					0xFFC0070C  /*                                            */
#define	FIO_MASKA_D			0xFFC00710  /*                                               */
#define	FIO_MASKA_C			0xFFC00714  /*                                        */
#define	FIO_MASKA_S			0xFFC00718  /*                                      */
#define	FIO_MASKA_T			0xFFC0071C  /*                                         */
#define	FIO_MASKB_D			0xFFC00720  /*                                               */
#define	FIO_MASKB_C			0xFFC00724  /*                                        */
#define	FIO_MASKB_S			0xFFC00728  /*                                      */
#define	FIO_MASKB_T			0xFFC0072C  /*                                         */
#define	FIO_DIR				0xFFC00730  /*                                    */
#define	FIO_POLAR			0xFFC00734  /*                               */
#define	FIO_EDGE			0xFFC00738  /*                                  */
#define	FIO_BOTH			0xFFC0073C  /*                                 */
#define	FIO_INEN					0xFFC00740  /*                             */


/*                                             */
#define	SPORT0_TCR1				0xFFC00800  /*                                          */
#define	SPORT0_TCR2				0xFFC00804  /*                                          */
#define	SPORT0_TCLKDIV			0xFFC00808  /*                               */
#define	SPORT0_TFSDIV			0xFFC0080C  /*                                    */
#define	SPORT0_TX			0xFFC00810  /*                         */
#define	SPORT0_RX			0xFFC00818  /*                         */
#define	SPORT0_RCR1				0xFFC00820  /*                                          */
#define	SPORT0_RCR2				0xFFC00824  /*                                          */
#define	SPORT0_RCLKDIV			0xFFC00828  /*                              */
#define	SPORT0_RFSDIV			0xFFC0082C  /*                                   */
#define	SPORT0_STAT			0xFFC00830  /*                        */
#define	SPORT0_CHNL			0xFFC00834  /*                                 */
#define	SPORT0_MCMC1			0xFFC00838  /*                                               */
#define	SPORT0_MCMC2			0xFFC0083C  /*                                               */
#define	SPORT0_MTCS0			0xFFC00840  /*                                                 */
#define	SPORT0_MTCS1			0xFFC00844  /*                                                 */
#define	SPORT0_MTCS2			0xFFC00848  /*                                                 */
#define	SPORT0_MTCS3			0xFFC0084C  /*                                                 */
#define	SPORT0_MRCS0			0xFFC00850  /*                                                */
#define	SPORT0_MRCS1			0xFFC00854  /*                                                */
#define	SPORT0_MRCS2			0xFFC00858  /*                                                */
#define	SPORT0_MRCS3			0xFFC0085C  /*                                                */


/*                                             */
#define	SPORT1_TCR1				0xFFC00900  /*                                          */
#define	SPORT1_TCR2				0xFFC00904  /*                                          */
#define	SPORT1_TCLKDIV			0xFFC00908  /*                               */
#define	SPORT1_TFSDIV			0xFFC0090C  /*                                    */
#define	SPORT1_TX			0xFFC00910  /*                         */
#define	SPORT1_RX			0xFFC00918  /*                         */
#define	SPORT1_RCR1				0xFFC00920  /*                                          */
#define	SPORT1_RCR2				0xFFC00924  /*                                          */
#define	SPORT1_RCLKDIV			0xFFC00928  /*                              */
#define	SPORT1_RFSDIV			0xFFC0092C  /*                                   */
#define	SPORT1_STAT			0xFFC00930  /*                        */
#define	SPORT1_CHNL			0xFFC00934  /*                                 */
#define	SPORT1_MCMC1			0xFFC00938  /*                                               */
#define	SPORT1_MCMC2			0xFFC0093C  /*                                               */
#define	SPORT1_MTCS0			0xFFC00940  /*                                                 */
#define	SPORT1_MTCS1			0xFFC00944  /*                                                 */
#define	SPORT1_MTCS2			0xFFC00948  /*                                                 */
#define	SPORT1_MTCS3			0xFFC0094C  /*                                                 */
#define	SPORT1_MRCS0			0xFFC00950  /*                                                */
#define	SPORT1_MRCS1			0xFFC00954  /*                                                */
#define	SPORT1_MRCS2			0xFFC00958  /*                                                */
#define	SPORT1_MRCS3			0xFFC0095C  /*                                                */


/*                                                       */
/*                                 */
#define	EBIU_AMGCTL			0xFFC00A00  /*                                             */
#define	EBIU_AMBCTL0		0xFFC00A04  /*                                             */
#define	EBIU_AMBCTL1		0xFFC00A08  /*                                             */

/*                  */
#define	EBIU_SDGCTL			0xFFC00A10  /*                               */
#define	EBIU_SDBCTL			0xFFC00A14  /*                             */
#define	EBIU_SDRRC			0xFFC00A18  /*                                     */
#define	EBIU_SDSTAT			0xFFC00A1C  /*                       */



/*                                                                      */

#define	DMAC0_TC_PER			0xFFC00B0C	/*                                                   */
#define	DMAC0_TC_CNT			0xFFC00B10	/*                                                          */



/*                                                   */

#define	DMA0_NEXT_DESC_PTR		0xFFC00C00	/*                                                */
#define	DMA0_START_ADDR			0xFFC00C04	/*                                      */
#define	DMA0_CONFIG				0xFFC00C08	/*                                      */
#define	DMA0_X_COUNT			0xFFC00C10	/*                                */
#define	DMA0_X_MODIFY			0xFFC00C14	/*                                 */
#define	DMA0_Y_COUNT			0xFFC00C18	/*                                */
#define	DMA0_Y_MODIFY			0xFFC00C1C	/*                                 */
#define	DMA0_CURR_DESC_PTR		0xFFC00C20	/*                                                   */
#define	DMA0_CURR_ADDR			0xFFC00C24	/*                                        */
#define	DMA0_IRQ_STATUS			0xFFC00C28	/*                                         */
#define	DMA0_PERIPHERAL_MAP		0xFFC00C2C	/*                                       */
#define	DMA0_CURR_X_COUNT		0xFFC00C30	/*                                        */
#define	DMA0_CURR_Y_COUNT		0xFFC00C38	/*                                        */

#define	DMA1_NEXT_DESC_PTR		0xFFC00C40	/*                                                */
#define	DMA1_START_ADDR			0xFFC00C44	/*                                      */
#define	DMA1_CONFIG				0xFFC00C48	/*                                      */
#define	DMA1_X_COUNT			0xFFC00C50	/*                                */
#define	DMA1_X_MODIFY			0xFFC00C54	/*                                 */
#define	DMA1_Y_COUNT			0xFFC00C58	/*                                */
#define	DMA1_Y_MODIFY			0xFFC00C5C	/*                                 */
#define	DMA1_CURR_DESC_PTR		0xFFC00C60	/*                                                   */
#define	DMA1_CURR_ADDR			0xFFC00C64	/*                                        */
#define	DMA1_IRQ_STATUS			0xFFC00C68	/*                                         */
#define	DMA1_PERIPHERAL_MAP		0xFFC00C6C	/*                                       */
#define	DMA1_CURR_X_COUNT		0xFFC00C70	/*                                        */
#define	DMA1_CURR_Y_COUNT		0xFFC00C78	/*                                        */

#define	DMA2_NEXT_DESC_PTR		0xFFC00C80	/*                                                */
#define	DMA2_START_ADDR			0xFFC00C84	/*                                      */
#define	DMA2_CONFIG				0xFFC00C88	/*                                      */
#define	DMA2_X_COUNT			0xFFC00C90	/*                                */
#define	DMA2_X_MODIFY			0xFFC00C94	/*                                 */
#define	DMA2_Y_COUNT			0xFFC00C98	/*                                */
#define	DMA2_Y_MODIFY			0xFFC00C9C	/*                                 */
#define	DMA2_CURR_DESC_PTR		0xFFC00CA0	/*                                                   */
#define	DMA2_CURR_ADDR			0xFFC00CA4	/*                                        */
#define	DMA2_IRQ_STATUS			0xFFC00CA8	/*                                         */
#define	DMA2_PERIPHERAL_MAP		0xFFC00CAC	/*                                       */
#define	DMA2_CURR_X_COUNT		0xFFC00CB0	/*                                        */
#define	DMA2_CURR_Y_COUNT		0xFFC00CB8	/*                                        */

#define	DMA3_NEXT_DESC_PTR		0xFFC00CC0	/*                                                */
#define	DMA3_START_ADDR			0xFFC00CC4	/*                                      */
#define	DMA3_CONFIG				0xFFC00CC8	/*                                      */
#define	DMA3_X_COUNT			0xFFC00CD0	/*                                */
#define	DMA3_X_MODIFY			0xFFC00CD4	/*                                 */
#define	DMA3_Y_COUNT			0xFFC00CD8	/*                                */
#define	DMA3_Y_MODIFY			0xFFC00CDC	/*                                 */
#define	DMA3_CURR_DESC_PTR		0xFFC00CE0	/*                                                   */
#define	DMA3_CURR_ADDR			0xFFC00CE4	/*                                        */
#define	DMA3_IRQ_STATUS			0xFFC00CE8	/*                                         */
#define	DMA3_PERIPHERAL_MAP		0xFFC00CEC	/*                                       */
#define	DMA3_CURR_X_COUNT		0xFFC00CF0	/*                                        */
#define	DMA3_CURR_Y_COUNT		0xFFC00CF8	/*                                        */

#define	DMA4_NEXT_DESC_PTR		0xFFC00D00	/*                                                */
#define	DMA4_START_ADDR			0xFFC00D04	/*                                      */
#define	DMA4_CONFIG				0xFFC00D08	/*                                      */
#define	DMA4_X_COUNT			0xFFC00D10	/*                                */
#define	DMA4_X_MODIFY			0xFFC00D14	/*                                 */
#define	DMA4_Y_COUNT			0xFFC00D18	/*                                */
#define	DMA4_Y_MODIFY			0xFFC00D1C	/*                                 */
#define	DMA4_CURR_DESC_PTR		0xFFC00D20	/*                                                   */
#define	DMA4_CURR_ADDR			0xFFC00D24	/*                                        */
#define	DMA4_IRQ_STATUS			0xFFC00D28	/*                                         */
#define	DMA4_PERIPHERAL_MAP		0xFFC00D2C	/*                                       */
#define	DMA4_CURR_X_COUNT		0xFFC00D30	/*                                        */
#define	DMA4_CURR_Y_COUNT		0xFFC00D38	/*                                        */

#define	DMA5_NEXT_DESC_PTR		0xFFC00D40	/*                                                */
#define	DMA5_START_ADDR			0xFFC00D44	/*                                      */
#define	DMA5_CONFIG				0xFFC00D48	/*                                      */
#define	DMA5_X_COUNT			0xFFC00D50	/*                                */
#define	DMA5_X_MODIFY			0xFFC00D54	/*                                 */
#define	DMA5_Y_COUNT			0xFFC00D58	/*                                */
#define	DMA5_Y_MODIFY			0xFFC00D5C	/*                                 */
#define	DMA5_CURR_DESC_PTR		0xFFC00D60	/*                                                   */
#define	DMA5_CURR_ADDR			0xFFC00D64	/*                                        */
#define	DMA5_IRQ_STATUS			0xFFC00D68	/*                                         */
#define	DMA5_PERIPHERAL_MAP		0xFFC00D6C	/*                                       */
#define	DMA5_CURR_X_COUNT		0xFFC00D70	/*                                        */
#define	DMA5_CURR_Y_COUNT		0xFFC00D78	/*                                        */

#define	DMA6_NEXT_DESC_PTR		0xFFC00D80	/*                                                */
#define	DMA6_START_ADDR			0xFFC00D84	/*                                      */
#define	DMA6_CONFIG				0xFFC00D88	/*                                      */
#define	DMA6_X_COUNT			0xFFC00D90	/*                                */
#define	DMA6_X_MODIFY			0xFFC00D94	/*                                 */
#define	DMA6_Y_COUNT			0xFFC00D98	/*                                */
#define	DMA6_Y_MODIFY			0xFFC00D9C	/*                                 */
#define	DMA6_CURR_DESC_PTR		0xFFC00DA0	/*                                                   */
#define	DMA6_CURR_ADDR			0xFFC00DA4	/*                                        */
#define	DMA6_IRQ_STATUS			0xFFC00DA8	/*                                         */
#define	DMA6_PERIPHERAL_MAP		0xFFC00DAC	/*                                       */
#define	DMA6_CURR_X_COUNT		0xFFC00DB0	/*                                        */
#define	DMA6_CURR_Y_COUNT		0xFFC00DB8	/*                                        */

#define	DMA7_NEXT_DESC_PTR		0xFFC00DC0	/*                                                */
#define	DMA7_START_ADDR			0xFFC00DC4	/*                                      */
#define	DMA7_CONFIG				0xFFC00DC8	/*                                      */
#define	DMA7_X_COUNT			0xFFC00DD0	/*                                */
#define	DMA7_X_MODIFY			0xFFC00DD4	/*                                 */
#define	DMA7_Y_COUNT			0xFFC00DD8	/*                                */
#define	DMA7_Y_MODIFY			0xFFC00DDC	/*                                 */
#define	DMA7_CURR_DESC_PTR		0xFFC00DE0	/*                                                   */
#define	DMA7_CURR_ADDR			0xFFC00DE4	/*                                        */
#define	DMA7_IRQ_STATUS			0xFFC00DE8	/*                                         */
#define	DMA7_PERIPHERAL_MAP		0xFFC00DEC	/*                                       */
#define	DMA7_CURR_X_COUNT		0xFFC00DF0	/*                                        */
#define	DMA7_CURR_Y_COUNT		0xFFC00DF8	/*                                        */

#define	MDMA_D0_NEXT_DESC_PTR	0xFFC00E00	/*                                                               */
#define	MDMA_D0_START_ADDR		0xFFC00E04	/*                                                     */
#define	MDMA_D0_CONFIG			0xFFC00E08	/*                                                     */
#define	MDMA_D0_X_COUNT		0xFFC00E10	/*                                               */
#define	MDMA_D0_X_MODIFY		0xFFC00E14	/*                                                */
#define	MDMA_D0_Y_COUNT		0xFFC00E18	/*                                               */
#define	MDMA_D0_Y_MODIFY		0xFFC00E1C	/*                                                */
#define	MDMA_D0_CURR_DESC_PTR	0xFFC00E20	/*                                                                  */
#define	MDMA_D0_CURR_ADDR		0xFFC00E24	/*                                                       */
#define	MDMA_D0_IRQ_STATUS		0xFFC00E28	/*                                                        */
#define	MDMA_D0_PERIPHERAL_MAP	0xFFC00E2C	/*                                                      */
#define	MDMA_D0_CURR_X_COUNT	0xFFC00E30	/*                                                       */
#define	MDMA_D0_CURR_Y_COUNT	0xFFC00E38	/*                                                       */

#define	MDMA_S0_NEXT_DESC_PTR	0xFFC00E40	/*                                                          */
#define	MDMA_S0_START_ADDR		0xFFC00E44	/*                                                */
#define	MDMA_S0_CONFIG			0xFFC00E48	/*                                                */
#define	MDMA_S0_X_COUNT		0xFFC00E50	/*                                          */
#define	MDMA_S0_X_MODIFY		0xFFC00E54	/*                                           */
#define	MDMA_S0_Y_COUNT		0xFFC00E58	/*                                          */
#define	MDMA_S0_Y_MODIFY		0xFFC00E5C	/*                                           */
#define	MDMA_S0_CURR_DESC_PTR	0xFFC00E60	/*                                                             */
#define	MDMA_S0_CURR_ADDR		0xFFC00E64	/*                                                  */
#define	MDMA_S0_IRQ_STATUS		0xFFC00E68	/*                                                   */
#define	MDMA_S0_PERIPHERAL_MAP	0xFFC00E6C	/*                                                 */
#define	MDMA_S0_CURR_X_COUNT	0xFFC00E70	/*                                                  */
#define	MDMA_S0_CURR_Y_COUNT	0xFFC00E78	/*                                                  */

#define	MDMA_D1_NEXT_DESC_PTR	0xFFC00E80	/*                                                               */
#define	MDMA_D1_START_ADDR		0xFFC00E84	/*                                                     */
#define	MDMA_D1_CONFIG			0xFFC00E88	/*                                                     */
#define	MDMA_D1_X_COUNT		0xFFC00E90	/*                                               */
#define	MDMA_D1_X_MODIFY		0xFFC00E94	/*                                                */
#define	MDMA_D1_Y_COUNT		0xFFC00E98	/*                                               */
#define	MDMA_D1_Y_MODIFY		0xFFC00E9C	/*                                                */
#define	MDMA_D1_CURR_DESC_PTR	0xFFC00EA0	/*                                                                  */
#define	MDMA_D1_CURR_ADDR		0xFFC00EA4	/*                                                       */
#define	MDMA_D1_IRQ_STATUS		0xFFC00EA8	/*                                                        */
#define	MDMA_D1_PERIPHERAL_MAP	0xFFC00EAC	/*                                                      */
#define	MDMA_D1_CURR_X_COUNT	0xFFC00EB0	/*                                                       */
#define	MDMA_D1_CURR_Y_COUNT	0xFFC00EB8	/*                                                       */

#define	MDMA_S1_NEXT_DESC_PTR	0xFFC00EC0	/*                                                          */
#define	MDMA_S1_START_ADDR		0xFFC00EC4	/*                                                */
#define	MDMA_S1_CONFIG			0xFFC00EC8	/*                                                */
#define	MDMA_S1_X_COUNT		0xFFC00ED0	/*                                          */
#define	MDMA_S1_X_MODIFY		0xFFC00ED4	/*                                           */
#define	MDMA_S1_Y_COUNT		0xFFC00ED8	/*                                          */
#define	MDMA_S1_Y_MODIFY		0xFFC00EDC	/*                                           */
#define	MDMA_S1_CURR_DESC_PTR	0xFFC00EE0	/*                                                             */
#define	MDMA_S1_CURR_ADDR		0xFFC00EE4	/*                                                  */
#define	MDMA_S1_IRQ_STATUS		0xFFC00EE8	/*                                                   */
#define	MDMA_S1_PERIPHERAL_MAP	0xFFC00EEC	/*                                                 */
#define	MDMA_S1_CURR_X_COUNT	0xFFC00EF0	/*                                                  */
#define	MDMA_S1_CURR_Y_COUNT	0xFFC00EF8	/*                                                  */


/*                                                               */
#define	PPI_CONTROL			0xFFC01000	/*                      */
#define	PPI_STATUS			0xFFC01004	/*                     */
#define	PPI_COUNT			0xFFC01008	/*                             */
#define	PPI_DELAY			0xFFC0100C	/*                          */
#define	PPI_FRAME			0xFFC01010	/*                           */


/*                                                   */
#define	TWI0_CLKDIV			0xFFC01400	/*                               */
#define	TWI0_CONTROL		0xFFC01404	/*                                              */
#define	TWI0_SLAVE_CTL		0xFFC01408	/*                             */
#define	TWI0_SLAVE_STAT		0xFFC0140C	/*                            */
#define	TWI0_SLAVE_ADDR		0xFFC01410	/*                             */
#define	TWI0_MASTER_CTL	0xFFC01414	/*                              */
#define	TWI0_MASTER_STAT	0xFFC01418	/*                             */
#define	TWI0_MASTER_ADDR	0xFFC0141C	/*                              */
#define	TWI0_INT_STAT		0xFFC01420	/*                                */
#define	TWI0_INT_MASK		0xFFC01424	/*                                     */
#define	TWI0_FIFO_CTL		0xFFC01428	/*                       */
#define	TWI0_FIFO_STAT		0xFFC0142C	/*                      */
#define	TWI0_XMT_DATA8		0xFFC01480	/*                                         */
#define	TWI0_XMT_DATA16		0xFFC01484	/*                                         */
#define	TWI0_RCV_DATA8		0xFFC01488	/*                                        */
#define	TWI0_RCV_DATA16		0xFFC0148C	/*                                        */

#define TWI0_REGBASE		TWI0_CLKDIV

/*                                               */
#define	TWI0_PRESCALE	 TWI0_CONTROL
#define	TWI0_INT_SRC	 TWI0_INT_STAT
#define	TWI0_INT_ENABLE	 TWI0_INT_MASK


/*                                                   */

/*                            */
#define PORTCIO_FER			0xFFC01500	/*                                        */
#define PORTCIO				0xFFC01510	/*                               */
#define PORTCIO_CLEAR			0xFFC01520	/*                                */
#define PORTCIO_SET			0xFFC01530	/*                              */
#define PORTCIO_TOGGLE			0xFFC01540	/*                                 */
#define PORTCIO_DIR			0xFFC01550	/*                                    */
#define PORTCIO_INEN			0xFFC01560	/*                                       */

/*                            */
#define PORTDIO_FER			0xFFC01504	/*                                        */
#define PORTDIO				0xFFC01514	/*                               */
#define PORTDIO_CLEAR			0xFFC01524	/*                                */
#define PORTDIO_SET			0xFFC01534	/*                              */
#define PORTDIO_TOGGLE			0xFFC01544	/*                                 */
#define PORTDIO_DIR			0xFFC01554	/*                                    */
#define PORTDIO_INEN			0xFFC01564	/*                                       */

/*                            */
#define PORTEIO_FER			0xFFC01508	/*                                        */
#define PORTEIO				0xFFC01518	/*                               */
#define PORTEIO_CLEAR			0xFFC01528	/*                                */
#define PORTEIO_SET			0xFFC01538	/*                              */
#define PORTEIO_TOGGLE			0xFFC01548	/*                                 */
#define PORTEIO_DIR			0xFFC01558	/*                                    */
#define PORTEIO_INEN			0xFFC01568	/*                                       */

/*                                                                      */

#define	DMAC1_TC_PER			0xFFC01B0C	/*                                                   */
#define	DMAC1_TC_CNT			0xFFC01B10	/*                                                          */



/*                                                   */
#define	DMA8_NEXT_DESC_PTR		0xFFC01C00	/*                                                */
#define	DMA8_START_ADDR			0xFFC01C04	/*                                      */
#define	DMA8_CONFIG				0xFFC01C08	/*                                      */
#define	DMA8_X_COUNT			0xFFC01C10	/*                                */
#define	DMA8_X_MODIFY			0xFFC01C14	/*                                 */
#define	DMA8_Y_COUNT			0xFFC01C18	/*                                */
#define	DMA8_Y_MODIFY			0xFFC01C1C	/*                                 */
#define	DMA8_CURR_DESC_PTR		0xFFC01C20	/*                                                   */
#define	DMA8_CURR_ADDR			0xFFC01C24	/*                                        */
#define	DMA8_IRQ_STATUS			0xFFC01C28	/*                                         */
#define	DMA8_PERIPHERAL_MAP		0xFFC01C2C	/*                                       */
#define	DMA8_CURR_X_COUNT		0xFFC01C30	/*                                        */
#define	DMA8_CURR_Y_COUNT		0xFFC01C38	/*                                        */

#define	DMA9_NEXT_DESC_PTR		0xFFC01C40	/*                                                */
#define	DMA9_START_ADDR			0xFFC01C44	/*                                      */
#define	DMA9_CONFIG				0xFFC01C48	/*                                      */
#define	DMA9_X_COUNT			0xFFC01C50	/*                                */
#define	DMA9_X_MODIFY			0xFFC01C54	/*                                 */
#define	DMA9_Y_COUNT			0xFFC01C58	/*                                */
#define	DMA9_Y_MODIFY			0xFFC01C5C	/*                                 */
#define	DMA9_CURR_DESC_PTR		0xFFC01C60	/*                                                   */
#define	DMA9_CURR_ADDR			0xFFC01C64	/*                                        */
#define	DMA9_IRQ_STATUS			0xFFC01C68	/*                                         */
#define	DMA9_PERIPHERAL_MAP		0xFFC01C6C	/*                                       */
#define	DMA9_CURR_X_COUNT		0xFFC01C70	/*                                        */
#define	DMA9_CURR_Y_COUNT		0xFFC01C78	/*                                        */

#define	DMA10_NEXT_DESC_PTR		0xFFC01C80	/*                                                 */
#define	DMA10_START_ADDR		0xFFC01C84	/*                                       */
#define	DMA10_CONFIG			0xFFC01C88	/*                                       */
#define	DMA10_X_COUNT			0xFFC01C90	/*                                 */
#define	DMA10_X_MODIFY			0xFFC01C94	/*                                  */
#define	DMA10_Y_COUNT			0xFFC01C98	/*                                 */
#define	DMA10_Y_MODIFY			0xFFC01C9C	/*                                  */
#define	DMA10_CURR_DESC_PTR		0xFFC01CA0	/*                                                    */
#define	DMA10_CURR_ADDR			0xFFC01CA4	/*                                         */
#define	DMA10_IRQ_STATUS		0xFFC01CA8	/*                                          */
#define	DMA10_PERIPHERAL_MAP	0xFFC01CAC	/*                                        */
#define	DMA10_CURR_X_COUNT		0xFFC01CB0	/*                                         */
#define	DMA10_CURR_Y_COUNT		0xFFC01CB8	/*                                         */

#define	DMA11_NEXT_DESC_PTR		0xFFC01CC0	/*                                                 */
#define	DMA11_START_ADDR		0xFFC01CC4	/*                                       */
#define	DMA11_CONFIG			0xFFC01CC8	/*                                       */
#define	DMA11_X_COUNT			0xFFC01CD0	/*                                 */
#define	DMA11_X_MODIFY			0xFFC01CD4	/*                                  */
#define	DMA11_Y_COUNT			0xFFC01CD8	/*                                 */
#define	DMA11_Y_MODIFY			0xFFC01CDC	/*                                  */
#define	DMA11_CURR_DESC_PTR		0xFFC01CE0	/*                                                    */
#define	DMA11_CURR_ADDR			0xFFC01CE4	/*                                         */
#define	DMA11_IRQ_STATUS		0xFFC01CE8	/*                                          */
#define	DMA11_PERIPHERAL_MAP	0xFFC01CEC	/*                                        */
#define	DMA11_CURR_X_COUNT		0xFFC01CF0	/*                                         */
#define	DMA11_CURR_Y_COUNT		0xFFC01CF8	/*                                         */

#define	DMA12_NEXT_DESC_PTR		0xFFC01D00	/*                                                 */
#define	DMA12_START_ADDR		0xFFC01D04	/*                                       */
#define	DMA12_CONFIG			0xFFC01D08	/*                                       */
#define	DMA12_X_COUNT			0xFFC01D10	/*                                 */
#define	DMA12_X_MODIFY			0xFFC01D14	/*                                  */
#define	DMA12_Y_COUNT			0xFFC01D18	/*                                 */
#define	DMA12_Y_MODIFY			0xFFC01D1C	/*                                  */
#define	DMA12_CURR_DESC_PTR		0xFFC01D20	/*                                                    */
#define	DMA12_CURR_ADDR			0xFFC01D24	/*                                         */
#define	DMA12_IRQ_STATUS		0xFFC01D28	/*                                          */
#define	DMA12_PERIPHERAL_MAP	0xFFC01D2C	/*                                        */
#define	DMA12_CURR_X_COUNT		0xFFC01D30	/*                                         */
#define	DMA12_CURR_Y_COUNT		0xFFC01D38	/*                                         */

#define	DMA13_NEXT_DESC_PTR		0xFFC01D40	/*                                                 */
#define	DMA13_START_ADDR		0xFFC01D44	/*                                       */
#define	DMA13_CONFIG			0xFFC01D48	/*                                       */
#define	DMA13_X_COUNT			0xFFC01D50	/*                                 */
#define	DMA13_X_MODIFY			0xFFC01D54	/*                                  */
#define	DMA13_Y_COUNT			0xFFC01D58	/*                                 */
#define	DMA13_Y_MODIFY			0xFFC01D5C	/*                                  */
#define	DMA13_CURR_DESC_PTR		0xFFC01D60	/*                                                    */
#define	DMA13_CURR_ADDR			0xFFC01D64	/*                                         */
#define	DMA13_IRQ_STATUS		0xFFC01D68	/*                                          */
#define	DMA13_PERIPHERAL_MAP	0xFFC01D6C	/*                                        */
#define	DMA13_CURR_X_COUNT		0xFFC01D70	/*                                         */
#define	DMA13_CURR_Y_COUNT		0xFFC01D78	/*                                         */

#define	DMA14_NEXT_DESC_PTR		0xFFC01D80	/*                                                 */
#define	DMA14_START_ADDR		0xFFC01D84	/*                                       */
#define	DMA14_CONFIG			0xFFC01D88	/*                                       */
#define	DMA14_X_COUNT			0xFFC01D90	/*                                 */
#define	DMA14_X_MODIFY			0xFFC01D94	/*                                  */
#define	DMA14_Y_COUNT			0xFFC01D98	/*                                 */
#define	DMA14_Y_MODIFY			0xFFC01D9C	/*                                  */
#define	DMA14_CURR_DESC_PTR		0xFFC01DA0	/*                                                    */
#define	DMA14_CURR_ADDR			0xFFC01DA4	/*                                         */
#define	DMA14_IRQ_STATUS		0xFFC01DA8	/*                                          */
#define	DMA14_PERIPHERAL_MAP	0xFFC01DAC	/*                                        */
#define	DMA14_CURR_X_COUNT		0xFFC01DB0	/*                                         */
#define	DMA14_CURR_Y_COUNT		0xFFC01DB8	/*                                         */

#define	DMA15_NEXT_DESC_PTR		0xFFC01DC0	/*                                                 */
#define	DMA15_START_ADDR		0xFFC01DC4	/*                                       */
#define	DMA15_CONFIG			0xFFC01DC8	/*                                       */
#define	DMA15_X_COUNT			0xFFC01DD0	/*                                 */
#define	DMA15_X_MODIFY			0xFFC01DD4	/*                                  */
#define	DMA15_Y_COUNT			0xFFC01DD8	/*                                 */
#define	DMA15_Y_MODIFY			0xFFC01DDC	/*                                  */
#define	DMA15_CURR_DESC_PTR		0xFFC01DE0	/*                                                    */
#define	DMA15_CURR_ADDR			0xFFC01DE4	/*                                         */
#define	DMA15_IRQ_STATUS		0xFFC01DE8	/*                                          */
#define	DMA15_PERIPHERAL_MAP	0xFFC01DEC	/*                                        */
#define	DMA15_CURR_X_COUNT		0xFFC01DF0	/*                                         */
#define	DMA15_CURR_Y_COUNT		0xFFC01DF8	/*                                         */

#define	DMA16_NEXT_DESC_PTR		0xFFC01E00	/*                                                 */
#define	DMA16_START_ADDR		0xFFC01E04	/*                                       */
#define	DMA16_CONFIG			0xFFC01E08	/*                                       */
#define	DMA16_X_COUNT			0xFFC01E10	/*                                 */
#define	DMA16_X_MODIFY			0xFFC01E14	/*                                  */
#define	DMA16_Y_COUNT			0xFFC01E18	/*                                 */
#define	DMA16_Y_MODIFY			0xFFC01E1C	/*                                  */
#define	DMA16_CURR_DESC_PTR		0xFFC01E20	/*                                                    */
#define	DMA16_CURR_ADDR			0xFFC01E24	/*                                         */
#define	DMA16_IRQ_STATUS		0xFFC01E28	/*                                          */
#define	DMA16_PERIPHERAL_MAP	0xFFC01E2C	/*                                        */
#define	DMA16_CURR_X_COUNT		0xFFC01E30	/*                                         */
#define	DMA16_CURR_Y_COUNT		0xFFC01E38	/*                                         */

#define	DMA17_NEXT_DESC_PTR		0xFFC01E40	/*                                                 */
#define	DMA17_START_ADDR		0xFFC01E44	/*                                       */
#define	DMA17_CONFIG			0xFFC01E48	/*                                       */
#define	DMA17_X_COUNT			0xFFC01E50	/*                                 */
#define	DMA17_X_MODIFY			0xFFC01E54	/*                                  */
#define	DMA17_Y_COUNT			0xFFC01E58	/*                                 */
#define	DMA17_Y_MODIFY			0xFFC01E5C	/*                                  */
#define	DMA17_CURR_DESC_PTR		0xFFC01E60	/*                                                    */
#define	DMA17_CURR_ADDR			0xFFC01E64	/*                                         */
#define	DMA17_IRQ_STATUS		0xFFC01E68	/*                                          */
#define	DMA17_PERIPHERAL_MAP	0xFFC01E6C	/*                                        */
#define	DMA17_CURR_X_COUNT		0xFFC01E70	/*                                         */
#define	DMA17_CURR_Y_COUNT		0xFFC01E78	/*                                         */

#define	DMA18_NEXT_DESC_PTR		0xFFC01E80	/*                                                 */
#define	DMA18_START_ADDR		0xFFC01E84	/*                                       */
#define	DMA18_CONFIG			0xFFC01E88	/*                                       */
#define	DMA18_X_COUNT			0xFFC01E90	/*                                 */
#define	DMA18_X_MODIFY			0xFFC01E94	/*                                  */
#define	DMA18_Y_COUNT			0xFFC01E98	/*                                 */
#define	DMA18_Y_MODIFY			0xFFC01E9C	/*                                  */
#define	DMA18_CURR_DESC_PTR		0xFFC01EA0	/*                                                    */
#define	DMA18_CURR_ADDR			0xFFC01EA4	/*                                         */
#define	DMA18_IRQ_STATUS		0xFFC01EA8	/*                                          */
#define	DMA18_PERIPHERAL_MAP	0xFFC01EAC	/*                                        */
#define	DMA18_CURR_X_COUNT		0xFFC01EB0	/*                                         */
#define	DMA18_CURR_Y_COUNT		0xFFC01EB8	/*                                         */

#define	DMA19_NEXT_DESC_PTR		0xFFC01EC0	/*                                                 */
#define	DMA19_START_ADDR		0xFFC01EC4	/*                                       */
#define	DMA19_CONFIG			0xFFC01EC8	/*                                       */
#define	DMA19_X_COUNT			0xFFC01ED0	/*                                 */
#define	DMA19_X_MODIFY			0xFFC01ED4	/*                                  */
#define	DMA19_Y_COUNT			0xFFC01ED8	/*                                 */
#define	DMA19_Y_MODIFY			0xFFC01EDC	/*                                  */
#define	DMA19_CURR_DESC_PTR		0xFFC01EE0	/*                                                    */
#define	DMA19_CURR_ADDR			0xFFC01EE4	/*                                         */
#define	DMA19_IRQ_STATUS		0xFFC01EE8	/*                                          */
#define	DMA19_PERIPHERAL_MAP	0xFFC01EEC	/*                                        */
#define	DMA19_CURR_X_COUNT		0xFFC01EF0	/*                                         */
#define	DMA19_CURR_Y_COUNT		0xFFC01EF8	/*                                         */

#define	MDMA_D2_NEXT_DESC_PTR	0xFFC01F00	/*                                                               */
#define	MDMA_D2_START_ADDR		0xFFC01F04	/*                                                     */
#define	MDMA_D2_CONFIG			0xFFC01F08	/*                                                     */
#define	MDMA_D2_X_COUNT		0xFFC01F10	/*                                               */
#define	MDMA_D2_X_MODIFY		0xFFC01F14	/*                                                */
#define	MDMA_D2_Y_COUNT		0xFFC01F18	/*                                               */
#define	MDMA_D2_Y_MODIFY		0xFFC01F1C	/*                                                */
#define	MDMA_D2_CURR_DESC_PTR	0xFFC01F20	/*                                                                  */
#define	MDMA_D2_CURR_ADDR		0xFFC01F24	/*                                                       */
#define	MDMA_D2_IRQ_STATUS		0xFFC01F28	/*                                                        */
#define	MDMA_D2_PERIPHERAL_MAP	0xFFC01F2C	/*                                                      */
#define	MDMA_D2_CURR_X_COUNT	0xFFC01F30	/*                                                       */
#define	MDMA_D2_CURR_Y_COUNT	0xFFC01F38	/*                                                       */

#define	MDMA_S2_NEXT_DESC_PTR	0xFFC01F40	/*                                                          */
#define	MDMA_S2_START_ADDR		0xFFC01F44	/*                                                */
#define	MDMA_S2_CONFIG			0xFFC01F48	/*                                                */
#define	MDMA_S2_X_COUNT		0xFFC01F50	/*                                          */
#define	MDMA_S2_X_MODIFY		0xFFC01F54	/*                                           */
#define	MDMA_S2_Y_COUNT		0xFFC01F58	/*                                          */
#define	MDMA_S2_Y_MODIFY		0xFFC01F5C	/*                                           */
#define	MDMA_S2_CURR_DESC_PTR	0xFFC01F60	/*                                                             */
#define	MDMA_S2_CURR_ADDR		0xFFC01F64	/*                                                  */
#define	MDMA_S2_IRQ_STATUS		0xFFC01F68	/*                                                   */
#define	MDMA_S2_PERIPHERAL_MAP	0xFFC01F6C	/*                                                 */
#define	MDMA_S2_CURR_X_COUNT	0xFFC01F70	/*                                                  */
#define	MDMA_S2_CURR_Y_COUNT	0xFFC01F78	/*                                                  */

#define	MDMA_D3_NEXT_DESC_PTR	0xFFC01F80	/*                                                               */
#define	MDMA_D3_START_ADDR		0xFFC01F84	/*                                                     */
#define	MDMA_D3_CONFIG			0xFFC01F88	/*                                                     */
#define	MDMA_D3_X_COUNT		0xFFC01F90	/*                                               */
#define	MDMA_D3_X_MODIFY		0xFFC01F94	/*                                                */
#define	MDMA_D3_Y_COUNT		0xFFC01F98	/*                                               */
#define	MDMA_D3_Y_MODIFY		0xFFC01F9C	/*                                                */
#define	MDMA_D3_CURR_DESC_PTR	0xFFC01FA0	/*                                                                  */
#define	MDMA_D3_CURR_ADDR		0xFFC01FA4	/*                                                       */
#define	MDMA_D3_IRQ_STATUS		0xFFC01FA8	/*                                                        */
#define	MDMA_D3_PERIPHERAL_MAP	0xFFC01FAC	/*                                                      */
#define	MDMA_D3_CURR_X_COUNT	0xFFC01FB0	/*                                                       */
#define	MDMA_D3_CURR_Y_COUNT	0xFFC01FB8	/*                                                       */

#define	MDMA_S3_NEXT_DESC_PTR	0xFFC01FC0	/*                                                          */
#define	MDMA_S3_START_ADDR		0xFFC01FC4	/*                                                */
#define	MDMA_S3_CONFIG			0xFFC01FC8	/*                                                */
#define	MDMA_S3_X_COUNT		0xFFC01FD0	/*                                          */
#define	MDMA_S3_X_MODIFY		0xFFC01FD4	/*                                           */
#define	MDMA_S3_Y_COUNT		0xFFC01FD8	/*                                          */
#define	MDMA_S3_Y_MODIFY		0xFFC01FDC	/*                                           */
#define	MDMA_S3_CURR_DESC_PTR	0xFFC01FE0	/*                                                             */
#define	MDMA_S3_CURR_ADDR		0xFFC01FE4	/*                                                  */
#define	MDMA_S3_IRQ_STATUS		0xFFC01FE8	/*                                                   */
#define	MDMA_S3_PERIPHERAL_MAP	0xFFC01FEC	/*                                                 */
#define	MDMA_S3_CURR_X_COUNT	0xFFC01FF0	/*                                                  */
#define	MDMA_S3_CURR_Y_COUNT	0xFFC01FF8	/*                                                  */


/*                                              */
#define	UART1_THR			0xFFC02000	/*                           */
#define	UART1_RBR			0xFFC02000	/*                         */
#define	UART1_DLL			0xFFC02000	/*                          */
#define	UART1_IER			0xFFC02004	/*                           */
#define	UART1_DLH			0xFFC02004	/*                           */
#define	UART1_IIR			0xFFC02008	/*                                   */
#define	UART1_LCR			0xFFC0200C	/*                       */
#define	UART1_MCR			0xFFC02010	/*                        */
#define	UART1_LSR			0xFFC02014	/*                      */
#define	UART1_SCR			0xFFC0201C	/*                      */
#define	UART1_GCTL			0xFFC02024	/*                         */


/*                                              */
#define	UART2_THR			0xFFC02100	/*                           */
#define	UART2_RBR			0xFFC02100	/*                         */
#define	UART2_DLL			0xFFC02100	/*                          */
#define	UART2_IER			0xFFC02104	/*                           */
#define	UART2_DLH			0xFFC02104	/*                           */
#define	UART2_IIR			0xFFC02108	/*                                   */
#define	UART2_LCR			0xFFC0210C	/*                       */
#define	UART2_MCR			0xFFC02110	/*                        */
#define	UART2_LSR			0xFFC02114	/*                      */
#define	UART2_SCR			0xFFC0211C	/*                      */
#define	UART2_GCTL			0xFFC02124	/*                         */


/*                                                   */
#define	TWI1_CLKDIV			0xFFC02200	/*                               */
#define	TWI1_CONTROL		0xFFC02204	/*                                              */
#define	TWI1_SLAVE_CTL		0xFFC02208	/*                             */
#define	TWI1_SLAVE_STAT		0xFFC0220C	/*                            */
#define	TWI1_SLAVE_ADDR		0xFFC02210	/*                             */
#define	TWI1_MASTER_CTL	0xFFC02214	/*                              */
#define	TWI1_MASTER_STAT	0xFFC02218	/*                             */
#define	TWI1_MASTER_ADDR	0xFFC0221C	/*                              */
#define	TWI1_INT_STAT		0xFFC02220	/*                                */
#define	TWI1_INT_MASK		0xFFC02224	/*                                     */
#define	TWI1_FIFO_CTL		0xFFC02228	/*                       */
#define	TWI1_FIFO_STAT		0xFFC0222C	/*                      */
#define	TWI1_XMT_DATA8		0xFFC02280	/*                                         */
#define	TWI1_XMT_DATA16		0xFFC02284	/*                                         */
#define	TWI1_RCV_DATA8		0xFFC02288	/*                                        */
#define	TWI1_RCV_DATA16		0xFFC0228C	/*                                        */
#define TWI1_REGBASE		TWI1_CLKDIV


/*                                               */
#define	TWI1_PRESCALE	  TWI1_CONTROL
#define	TWI1_INT_SRC	  TWI1_INT_STAT
#define	TWI1_INT_ENABLE	  TWI1_INT_MASK


/*                                             */
#define	SPI1_CTL			0xFFC02300  /*                       */
#define	SPI1_FLG			0xFFC02304  /*                    */
#define	SPI1_STAT			0xFFC02308  /*                      */
#define	SPI1_TDBR			0xFFC0230C  /*                                    */
#define	SPI1_RDBR			0xFFC02310  /*                                   */
#define	SPI1_BAUD			0xFFC02314  /*                         */
#define	SPI1_SHADOW			0xFFC02318  /*                           */
#define SPI1_REGBASE			SPI1_CTL

/*                                             */
#define	SPI2_CTL			0xFFC02400  /*                       */
#define	SPI2_FLG			0xFFC02404  /*                    */
#define	SPI2_STAT			0xFFC02408  /*                      */
#define	SPI2_TDBR			0xFFC0240C  /*                                    */
#define	SPI2_RDBR			0xFFC02410  /*                                   */
#define	SPI2_BAUD			0xFFC02414  /*                         */
#define	SPI2_SHADOW			0xFFC02418  /*                           */
#define SPI2_REGBASE			SPI2_CTL

/*                                                 */
#define	SPORT2_TCR1			0xFFC02500	/*                                          */
#define	SPORT2_TCR2			0xFFC02504	/*                                          */
#define	SPORT2_TCLKDIV		0xFFC02508	/*                               */
#define	SPORT2_TFSDIV		0xFFC0250C	/*                                    */
#define	SPORT2_TX			0xFFC02510	/*                         */
#define	SPORT2_RX			0xFFC02518	/*                         */
#define	SPORT2_RCR1			0xFFC02520	/*                                          */
#define	SPORT2_RCR2			0xFFC02524	/*                                          */
#define	SPORT2_RCLKDIV		0xFFC02528	/*                              */
#define	SPORT2_RFSDIV		0xFFC0252C	/*                                   */
#define	SPORT2_STAT			0xFFC02530	/*                        */
#define	SPORT2_CHNL			0xFFC02534	/*                                 */
#define	SPORT2_MCMC1		0xFFC02538	/*                                               */
#define	SPORT2_MCMC2		0xFFC0253C	/*                                               */
#define	SPORT2_MTCS0		0xFFC02540	/*                                                 */
#define	SPORT2_MTCS1		0xFFC02544	/*                                                 */
#define	SPORT2_MTCS2		0xFFC02548	/*                                                 */
#define	SPORT2_MTCS3		0xFFC0254C	/*                                                 */
#define	SPORT2_MRCS0		0xFFC02550	/*                                                */
#define	SPORT2_MRCS1		0xFFC02554	/*                                                */
#define	SPORT2_MRCS2		0xFFC02558	/*                                                */
#define	SPORT2_MRCS3		0xFFC0255C	/*                                                */


/*                                                 */
#define	SPORT3_TCR1			0xFFC02600	/*                                          */
#define	SPORT3_TCR2			0xFFC02604	/*                                          */
#define	SPORT3_TCLKDIV		0xFFC02608	/*                               */
#define	SPORT3_TFSDIV		0xFFC0260C	/*                                    */
#define	SPORT3_TX			0xFFC02610	/*                         */
#define	SPORT3_RX			0xFFC02618	/*                         */
#define	SPORT3_RCR1			0xFFC02620	/*                                          */
#define	SPORT3_RCR2			0xFFC02624	/*                                          */
#define	SPORT3_RCLKDIV		0xFFC02628	/*                              */
#define	SPORT3_RFSDIV		0xFFC0262C	/*                                   */
#define	SPORT3_STAT			0xFFC02630	/*                        */
#define	SPORT3_CHNL			0xFFC02634	/*                                 */
#define	SPORT3_MCMC1		0xFFC02638	/*                                               */
#define	SPORT3_MCMC2		0xFFC0263C	/*                                               */
#define	SPORT3_MTCS0		0xFFC02640	/*                                                 */
#define	SPORT3_MTCS1		0xFFC02644	/*                                                 */
#define	SPORT3_MTCS2		0xFFC02648	/*                                                 */
#define	SPORT3_MTCS3		0xFFC0264C	/*                                                 */
#define	SPORT3_MRCS0		0xFFC02650	/*                                                */
#define	SPORT3_MRCS1		0xFFC02654	/*                                                */
#define	SPORT3_MRCS2		0xFFC02658	/*                                                */
#define	SPORT3_MRCS3		0xFFC0265C	/*                                                */


/*                                               */
/*                               */
#define	CAN_MC1				0xFFC02A00	/*                       */
#define	CAN_MD1				0xFFC02A04	/*                         */
#define	CAN_TRS1			0xFFC02A08	/*                            */
#define	CAN_TRR1			0xFFC02A0C	/*                              */
#define	CAN_TA1				0xFFC02A10	/*                            */
#define	CAN_AA1				0xFFC02A14	/*                                  */
#define	CAN_RMP1			0xFFC02A18	/*                               */
#define	CAN_RML1			0xFFC02A1C	/*                            */
#define	CAN_MBTIF1			0xFFC02A20	/*                                       */
#define	CAN_MBRIF1			0xFFC02A24	/*                                       */
#define	CAN_MBIM1			0xFFC02A28	/*                              */
#define	CAN_RFH1			0xFFC02A2C	/*                             */
#define	CAN_OPSS1			0xFFC02A30	/*                                                 */

/*                                */
#define	CAN_MC2				0xFFC02A40	/*                       */
#define	CAN_MD2				0xFFC02A44	/*                         */
#define	CAN_TRS2			0xFFC02A48	/*                            */
#define	CAN_TRR2			0xFFC02A4C	/*                              */
#define	CAN_TA2				0xFFC02A50	/*                            */
#define	CAN_AA2				0xFFC02A54	/*                                  */
#define	CAN_RMP2			0xFFC02A58	/*                               */
#define	CAN_RML2			0xFFC02A5C	/*                            */
#define	CAN_MBTIF2			0xFFC02A60	/*                                       */
#define	CAN_MBRIF2			0xFFC02A64	/*                                       */
#define	CAN_MBIM2			0xFFC02A68	/*                              */
#define	CAN_RFH2			0xFFC02A6C	/*                             */
#define	CAN_OPSS2			0xFFC02A70	/*                                                 */

#define	CAN_CLOCK			0xFFC02A80	/*                                     */
#define	CAN_TIMING			0xFFC02A84	/*                                     */

#define	CAN_DEBUG			0xFFC02A88	/*                  */
/*                                              */
#define	CAN_CNF		 CAN_DEBUG

#define	CAN_STATUS			0xFFC02A8C	/*                        */
#define	CAN_CEC				0xFFC02A90	/*                        */
#define	CAN_GIS				0xFFC02A94	/*                                  */
#define	CAN_GIM				0xFFC02A98	/*                                */
#define	CAN_GIF				0xFFC02A9C	/*                                */
#define	CAN_CONTROL			0xFFC02AA0	/*                         */
#define	CAN_INTR			0xFFC02AA4	/*                            */
#define	CAN_MBTD			0xFFC02AAC	/*                                   */
#define	CAN_EWR				0xFFC02AB0	/*                            */
#define	CAN_ESR				0xFFC02AB4	/*                       */
#define	CAN_UCCNT			0xFFC02AC4	/*                    */
#define	CAN_UCRC			0xFFC02AC8	/*                                           */
#define	CAN_UCCNF			0xFFC02ACC	/*                                          */

/*                               */
#define	CAN_AM00L			0xFFC02B00	/*                               */
#define	CAN_AM00H			0xFFC02B04	/*                                */
#define	CAN_AM01L			0xFFC02B08	/*                               */
#define	CAN_AM01H			0xFFC02B0C	/*                                */
#define	CAN_AM02L			0xFFC02B10	/*                               */
#define	CAN_AM02H			0xFFC02B14	/*                                */
#define	CAN_AM03L			0xFFC02B18	/*                               */
#define	CAN_AM03H			0xFFC02B1C	/*                                */
#define	CAN_AM04L			0xFFC02B20	/*                               */
#define	CAN_AM04H			0xFFC02B24	/*                                */
#define	CAN_AM05L			0xFFC02B28	/*                               */
#define	CAN_AM05H			0xFFC02B2C	/*                                */
#define	CAN_AM06L			0xFFC02B30	/*                               */
#define	CAN_AM06H			0xFFC02B34	/*                                */
#define	CAN_AM07L			0xFFC02B38	/*                               */
#define	CAN_AM07H			0xFFC02B3C	/*                                */
#define	CAN_AM08L			0xFFC02B40	/*                               */
#define	CAN_AM08H			0xFFC02B44	/*                                */
#define	CAN_AM09L			0xFFC02B48	/*                               */
#define	CAN_AM09H			0xFFC02B4C	/*                                */
#define	CAN_AM10L			0xFFC02B50	/*                                */
#define	CAN_AM10H			0xFFC02B54	/*                                 */
#define	CAN_AM11L			0xFFC02B58	/*                                */
#define	CAN_AM11H			0xFFC02B5C	/*                                 */
#define	CAN_AM12L			0xFFC02B60	/*                                */
#define	CAN_AM12H			0xFFC02B64	/*                                 */
#define	CAN_AM13L			0xFFC02B68	/*                                */
#define	CAN_AM13H			0xFFC02B6C	/*                                 */
#define	CAN_AM14L			0xFFC02B70	/*                                */
#define	CAN_AM14H			0xFFC02B74	/*                                 */
#define	CAN_AM15L			0xFFC02B78	/*                                */
#define	CAN_AM15H			0xFFC02B7C	/*                                 */

#define	CAN_AM16L			0xFFC02B80	/*                                */
#define	CAN_AM16H			0xFFC02B84	/*                                 */
#define	CAN_AM17L			0xFFC02B88	/*                                */
#define	CAN_AM17H			0xFFC02B8C	/*                                 */
#define	CAN_AM18L			0xFFC02B90	/*                                */
#define	CAN_AM18H			0xFFC02B94	/*                                 */
#define	CAN_AM19L			0xFFC02B98	/*                                */
#define	CAN_AM19H			0xFFC02B9C	/*                                 */
#define	CAN_AM20L			0xFFC02BA0	/*                                */
#define	CAN_AM20H			0xFFC02BA4	/*                                 */
#define	CAN_AM21L			0xFFC02BA8	/*                                */
#define	CAN_AM21H			0xFFC02BAC	/*                                 */
#define	CAN_AM22L			0xFFC02BB0	/*                                */
#define	CAN_AM22H			0xFFC02BB4	/*                                 */
#define	CAN_AM23L			0xFFC02BB8	/*                                */
#define	CAN_AM23H			0xFFC02BBC	/*                                 */
#define	CAN_AM24L			0xFFC02BC0	/*                                */
#define	CAN_AM24H			0xFFC02BC4	/*                                 */
#define	CAN_AM25L			0xFFC02BC8	/*                                */
#define	CAN_AM25H			0xFFC02BCC	/*                                 */
#define	CAN_AM26L			0xFFC02BD0	/*                                */
#define	CAN_AM26H			0xFFC02BD4	/*                                 */
#define	CAN_AM27L			0xFFC02BD8	/*                                */
#define	CAN_AM27H			0xFFC02BDC	/*                                 */
#define	CAN_AM28L			0xFFC02BE0	/*                                */
#define	CAN_AM28H			0xFFC02BE4	/*                                 */
#define	CAN_AM29L			0xFFC02BE8	/*                                */
#define	CAN_AM29H			0xFFC02BEC	/*                                 */
#define	CAN_AM30L			0xFFC02BF0	/*                                */
#define	CAN_AM30H			0xFFC02BF4	/*                                 */
#define	CAN_AM31L			0xFFC02BF8	/*                                */
#define	CAN_AM31H			0xFFC02BFC	/*                                 */

/*                            */
#define	CAN_AM_L(x)			(CAN_AM00L+((x)*0x8))
#define	CAN_AM_H(x)			(CAN_AM00H+((x)*0x8))

/*                            */
#define	CAN_MB00_DATA0		0xFFC02C00	/*                                       */
#define	CAN_MB00_DATA1		0xFFC02C04	/*                                        */
#define	CAN_MB00_DATA2		0xFFC02C08	/*                                        */
#define	CAN_MB00_DATA3		0xFFC02C0C	/*                                        */
#define	CAN_MB00_LENGTH		0xFFC02C10	/*                                     */
#define	CAN_MB00_TIMESTAMP	0xFFC02C14	/*                                     */
#define	CAN_MB00_ID0		0xFFC02C18	/*                                   */
#define	CAN_MB00_ID1		0xFFC02C1C	/*                                    */

#define	CAN_MB01_DATA0		0xFFC02C20	/*                                       */
#define	CAN_MB01_DATA1		0xFFC02C24	/*                                        */
#define	CAN_MB01_DATA2		0xFFC02C28	/*                                        */
#define	CAN_MB01_DATA3		0xFFC02C2C	/*                                        */
#define	CAN_MB01_LENGTH		0xFFC02C30	/*                                     */
#define	CAN_MB01_TIMESTAMP	0xFFC02C34	/*                                     */
#define	CAN_MB01_ID0		0xFFC02C38	/*                                   */
#define	CAN_MB01_ID1		0xFFC02C3C	/*                                    */

#define	CAN_MB02_DATA0		0xFFC02C40	/*                                       */
#define	CAN_MB02_DATA1		0xFFC02C44	/*                                        */
#define	CAN_MB02_DATA2		0xFFC02C48	/*                                        */
#define	CAN_MB02_DATA3		0xFFC02C4C	/*                                        */
#define	CAN_MB02_LENGTH		0xFFC02C50	/*                                     */
#define	CAN_MB02_TIMESTAMP	0xFFC02C54	/*                                     */
#define	CAN_MB02_ID0		0xFFC02C58	/*                                   */
#define	CAN_MB02_ID1		0xFFC02C5C	/*                                    */

#define	CAN_MB03_DATA0		0xFFC02C60	/*                                       */
#define	CAN_MB03_DATA1		0xFFC02C64	/*                                        */
#define	CAN_MB03_DATA2		0xFFC02C68	/*                                        */
#define	CAN_MB03_DATA3		0xFFC02C6C	/*                                        */
#define	CAN_MB03_LENGTH		0xFFC02C70	/*                                     */
#define	CAN_MB03_TIMESTAMP	0xFFC02C74	/*                                     */
#define	CAN_MB03_ID0		0xFFC02C78	/*                                   */
#define	CAN_MB03_ID1		0xFFC02C7C	/*                                    */

#define	CAN_MB04_DATA0		0xFFC02C80	/*                                       */
#define	CAN_MB04_DATA1		0xFFC02C84	/*                                        */
#define	CAN_MB04_DATA2		0xFFC02C88	/*                                        */
#define	CAN_MB04_DATA3		0xFFC02C8C	/*                                        */
#define	CAN_MB04_LENGTH		0xFFC02C90	/*                                     */
#define	CAN_MB04_TIMESTAMP	0xFFC02C94	/*                                     */
#define	CAN_MB04_ID0		0xFFC02C98	/*                                   */
#define	CAN_MB04_ID1		0xFFC02C9C	/*                                    */

#define	CAN_MB05_DATA0		0xFFC02CA0	/*                                       */
#define	CAN_MB05_DATA1		0xFFC02CA4	/*                                        */
#define	CAN_MB05_DATA2		0xFFC02CA8	/*                                        */
#define	CAN_MB05_DATA3		0xFFC02CAC	/*                                        */
#define	CAN_MB05_LENGTH		0xFFC02CB0	/*                                     */
#define	CAN_MB05_TIMESTAMP	0xFFC02CB4	/*                                     */
#define	CAN_MB05_ID0		0xFFC02CB8	/*                                   */
#define	CAN_MB05_ID1		0xFFC02CBC	/*                                    */

#define	CAN_MB06_DATA0		0xFFC02CC0	/*                                       */
#define	CAN_MB06_DATA1		0xFFC02CC4	/*                                        */
#define	CAN_MB06_DATA2		0xFFC02CC8	/*                                        */
#define	CAN_MB06_DATA3		0xFFC02CCC	/*                                        */
#define	CAN_MB06_LENGTH		0xFFC02CD0	/*                                     */
#define	CAN_MB06_TIMESTAMP	0xFFC02CD4	/*                                     */
#define	CAN_MB06_ID0		0xFFC02CD8	/*                                   */
#define	CAN_MB06_ID1		0xFFC02CDC	/*                                    */

#define	CAN_MB07_DATA0		0xFFC02CE0	/*                                       */
#define	CAN_MB07_DATA1		0xFFC02CE4	/*                                        */
#define	CAN_MB07_DATA2		0xFFC02CE8	/*                                        */
#define	CAN_MB07_DATA3		0xFFC02CEC	/*                                        */
#define	CAN_MB07_LENGTH		0xFFC02CF0	/*                                     */
#define	CAN_MB07_TIMESTAMP	0xFFC02CF4	/*                                     */
#define	CAN_MB07_ID0		0xFFC02CF8	/*                                   */
#define	CAN_MB07_ID1		0xFFC02CFC	/*                                    */

#define	CAN_MB08_DATA0		0xFFC02D00	/*                                       */
#define	CAN_MB08_DATA1		0xFFC02D04	/*                                        */
#define	CAN_MB08_DATA2		0xFFC02D08	/*                                        */
#define	CAN_MB08_DATA3		0xFFC02D0C	/*                                        */
#define	CAN_MB08_LENGTH		0xFFC02D10	/*                                     */
#define	CAN_MB08_TIMESTAMP	0xFFC02D14	/*                                     */
#define	CAN_MB08_ID0		0xFFC02D18	/*                                   */
#define	CAN_MB08_ID1		0xFFC02D1C	/*                                    */

#define	CAN_MB09_DATA0		0xFFC02D20	/*                                       */
#define	CAN_MB09_DATA1		0xFFC02D24	/*                                        */
#define	CAN_MB09_DATA2		0xFFC02D28	/*                                        */
#define	CAN_MB09_DATA3		0xFFC02D2C	/*                                        */
#define	CAN_MB09_LENGTH		0xFFC02D30	/*                                     */
#define	CAN_MB09_TIMESTAMP	0xFFC02D34	/*                                     */
#define	CAN_MB09_ID0		0xFFC02D38	/*                                   */
#define	CAN_MB09_ID1		0xFFC02D3C	/*                                    */

#define	CAN_MB10_DATA0		0xFFC02D40	/*                                        */
#define	CAN_MB10_DATA1		0xFFC02D44	/*                                         */
#define	CAN_MB10_DATA2		0xFFC02D48	/*                                         */
#define	CAN_MB10_DATA3		0xFFC02D4C	/*                                         */
#define	CAN_MB10_LENGTH		0xFFC02D50	/*                                      */
#define	CAN_MB10_TIMESTAMP	0xFFC02D54	/*                                      */
#define	CAN_MB10_ID0		0xFFC02D58	/*                                    */
#define	CAN_MB10_ID1		0xFFC02D5C	/*                                     */

#define	CAN_MB11_DATA0		0xFFC02D60	/*                                        */
#define	CAN_MB11_DATA1		0xFFC02D64	/*                                         */
#define	CAN_MB11_DATA2		0xFFC02D68	/*                                         */
#define	CAN_MB11_DATA3		0xFFC02D6C	/*                                         */
#define	CAN_MB11_LENGTH		0xFFC02D70	/*                                      */
#define	CAN_MB11_TIMESTAMP	0xFFC02D74	/*                                      */
#define	CAN_MB11_ID0		0xFFC02D78	/*                                    */
#define	CAN_MB11_ID1		0xFFC02D7C	/*                                     */

#define	CAN_MB12_DATA0		0xFFC02D80	/*                                        */
#define	CAN_MB12_DATA1		0xFFC02D84	/*                                         */
#define	CAN_MB12_DATA2		0xFFC02D88	/*                                         */
#define	CAN_MB12_DATA3		0xFFC02D8C	/*                                         */
#define	CAN_MB12_LENGTH		0xFFC02D90	/*                                      */
#define	CAN_MB12_TIMESTAMP	0xFFC02D94	/*                                      */
#define	CAN_MB12_ID0		0xFFC02D98	/*                                    */
#define	CAN_MB12_ID1		0xFFC02D9C	/*                                     */

#define	CAN_MB13_DATA0		0xFFC02DA0	/*                                        */
#define	CAN_MB13_DATA1		0xFFC02DA4	/*                                         */
#define	CAN_MB13_DATA2		0xFFC02DA8	/*                                         */
#define	CAN_MB13_DATA3		0xFFC02DAC	/*                                         */
#define	CAN_MB13_LENGTH		0xFFC02DB0	/*                                      */
#define	CAN_MB13_TIMESTAMP	0xFFC02DB4	/*                                      */
#define	CAN_MB13_ID0		0xFFC02DB8	/*                                    */
#define	CAN_MB13_ID1		0xFFC02DBC	/*                                     */

#define	CAN_MB14_DATA0		0xFFC02DC0	/*                                        */
#define	CAN_MB14_DATA1		0xFFC02DC4	/*                                         */
#define	CAN_MB14_DATA2		0xFFC02DC8	/*                                         */
#define	CAN_MB14_DATA3		0xFFC02DCC	/*                                         */
#define	CAN_MB14_LENGTH		0xFFC02DD0	/*                                      */
#define	CAN_MB14_TIMESTAMP	0xFFC02DD4	/*                                      */
#define	CAN_MB14_ID0		0xFFC02DD8	/*                                    */
#define	CAN_MB14_ID1		0xFFC02DDC	/*                                     */

#define	CAN_MB15_DATA0		0xFFC02DE0	/*                                        */
#define	CAN_MB15_DATA1		0xFFC02DE4	/*                                         */
#define	CAN_MB15_DATA2		0xFFC02DE8	/*                                         */
#define	CAN_MB15_DATA3		0xFFC02DEC	/*                                         */
#define	CAN_MB15_LENGTH		0xFFC02DF0	/*                                      */
#define	CAN_MB15_TIMESTAMP	0xFFC02DF4	/*                                      */
#define	CAN_MB15_ID0		0xFFC02DF8	/*                                    */
#define	CAN_MB15_ID1		0xFFC02DFC	/*                                     */

#define	CAN_MB16_DATA0		0xFFC02E00	/*                                        */
#define	CAN_MB16_DATA1		0xFFC02E04	/*                                         */
#define	CAN_MB16_DATA2		0xFFC02E08	/*                                         */
#define	CAN_MB16_DATA3		0xFFC02E0C	/*                                         */
#define	CAN_MB16_LENGTH		0xFFC02E10	/*                                      */
#define	CAN_MB16_TIMESTAMP	0xFFC02E14	/*                                      */
#define	CAN_MB16_ID0		0xFFC02E18	/*                                    */
#define	CAN_MB16_ID1		0xFFC02E1C	/*                                     */

#define	CAN_MB17_DATA0		0xFFC02E20	/*                                        */
#define	CAN_MB17_DATA1		0xFFC02E24	/*                                         */
#define	CAN_MB17_DATA2		0xFFC02E28	/*                                         */
#define	CAN_MB17_DATA3		0xFFC02E2C	/*                                         */
#define	CAN_MB17_LENGTH		0xFFC02E30	/*                                      */
#define	CAN_MB17_TIMESTAMP	0xFFC02E34	/*                                      */
#define	CAN_MB17_ID0		0xFFC02E38	/*                                    */
#define	CAN_MB17_ID1		0xFFC02E3C	/*                                     */

#define	CAN_MB18_DATA0		0xFFC02E40	/*                                        */
#define	CAN_MB18_DATA1		0xFFC02E44	/*                                         */
#define	CAN_MB18_DATA2		0xFFC02E48	/*                                         */
#define	CAN_MB18_DATA3		0xFFC02E4C	/*                                         */
#define	CAN_MB18_LENGTH		0xFFC02E50	/*                                      */
#define	CAN_MB18_TIMESTAMP	0xFFC02E54	/*                                      */
#define	CAN_MB18_ID0		0xFFC02E58	/*                                    */
#define	CAN_MB18_ID1		0xFFC02E5C	/*                                     */

#define	CAN_MB19_DATA0		0xFFC02E60	/*                                        */
#define	CAN_MB19_DATA1		0xFFC02E64	/*                                         */
#define	CAN_MB19_DATA2		0xFFC02E68	/*                                         */
#define	CAN_MB19_DATA3		0xFFC02E6C	/*                                         */
#define	CAN_MB19_LENGTH		0xFFC02E70	/*                                      */
#define	CAN_MB19_TIMESTAMP	0xFFC02E74	/*                                      */
#define	CAN_MB19_ID0		0xFFC02E78	/*                                    */
#define	CAN_MB19_ID1		0xFFC02E7C	/*                                     */

#define	CAN_MB20_DATA0		0xFFC02E80	/*                                        */
#define	CAN_MB20_DATA1		0xFFC02E84	/*                                         */
#define	CAN_MB20_DATA2		0xFFC02E88	/*                                         */
#define	CAN_MB20_DATA3		0xFFC02E8C	/*                                         */
#define	CAN_MB20_LENGTH		0xFFC02E90	/*                                      */
#define	CAN_MB20_TIMESTAMP	0xFFC02E94	/*                                      */
#define	CAN_MB20_ID0		0xFFC02E98	/*                                    */
#define	CAN_MB20_ID1		0xFFC02E9C	/*                                     */

#define	CAN_MB21_DATA0		0xFFC02EA0	/*                                        */
#define	CAN_MB21_DATA1		0xFFC02EA4	/*                                         */
#define	CAN_MB21_DATA2		0xFFC02EA8	/*                                         */
#define	CAN_MB21_DATA3		0xFFC02EAC	/*                                         */
#define	CAN_MB21_LENGTH		0xFFC02EB0	/*                                      */
#define	CAN_MB21_TIMESTAMP	0xFFC02EB4	/*                                      */
#define	CAN_MB21_ID0		0xFFC02EB8	/*                                    */
#define	CAN_MB21_ID1		0xFFC02EBC	/*                                     */

#define	CAN_MB22_DATA0		0xFFC02EC0	/*                                        */
#define	CAN_MB22_DATA1		0xFFC02EC4	/*                                         */
#define	CAN_MB22_DATA2		0xFFC02EC8	/*                                         */
#define	CAN_MB22_DATA3		0xFFC02ECC	/*                                         */
#define	CAN_MB22_LENGTH		0xFFC02ED0	/*                                      */
#define	CAN_MB22_TIMESTAMP	0xFFC02ED4	/*                                      */
#define	CAN_MB22_ID0		0xFFC02ED8	/*                                    */
#define	CAN_MB22_ID1		0xFFC02EDC	/*                                     */

#define	CAN_MB23_DATA0		0xFFC02EE0	/*                                        */
#define	CAN_MB23_DATA1		0xFFC02EE4	/*                                         */
#define	CAN_MB23_DATA2		0xFFC02EE8	/*                                         */
#define	CAN_MB23_DATA3		0xFFC02EEC	/*                                         */
#define	CAN_MB23_LENGTH		0xFFC02EF0	/*                                      */
#define	CAN_MB23_TIMESTAMP	0xFFC02EF4	/*                                      */
#define	CAN_MB23_ID0		0xFFC02EF8	/*                                    */
#define	CAN_MB23_ID1		0xFFC02EFC	/*                                     */

#define	CAN_MB24_DATA0		0xFFC02F00	/*                                        */
#define	CAN_MB24_DATA1		0xFFC02F04	/*                                         */
#define	CAN_MB24_DATA2		0xFFC02F08	/*                                         */
#define	CAN_MB24_DATA3		0xFFC02F0C	/*                                         */
#define	CAN_MB24_LENGTH		0xFFC02F10	/*                                      */
#define	CAN_MB24_TIMESTAMP	0xFFC02F14	/*                                      */
#define	CAN_MB24_ID0		0xFFC02F18	/*                                    */
#define	CAN_MB24_ID1		0xFFC02F1C	/*                                     */

#define	CAN_MB25_DATA0		0xFFC02F20	/*                                        */
#define	CAN_MB25_DATA1		0xFFC02F24	/*                                         */
#define	CAN_MB25_DATA2		0xFFC02F28	/*                                         */
#define	CAN_MB25_DATA3		0xFFC02F2C	/*                                         */
#define	CAN_MB25_LENGTH		0xFFC02F30	/*                                      */
#define	CAN_MB25_TIMESTAMP	0xFFC02F34	/*                                      */
#define	CAN_MB25_ID0		0xFFC02F38	/*                                    */
#define	CAN_MB25_ID1		0xFFC02F3C	/*                                     */

#define	CAN_MB26_DATA0		0xFFC02F40	/*                                        */
#define	CAN_MB26_DATA1		0xFFC02F44	/*                                         */
#define	CAN_MB26_DATA2		0xFFC02F48	/*                                         */
#define	CAN_MB26_DATA3		0xFFC02F4C	/*                                         */
#define	CAN_MB26_LENGTH		0xFFC02F50	/*                                      */
#define	CAN_MB26_TIMESTAMP	0xFFC02F54	/*                                      */
#define	CAN_MB26_ID0		0xFFC02F58	/*                                    */
#define	CAN_MB26_ID1		0xFFC02F5C	/*                                     */

#define	CAN_MB27_DATA0		0xFFC02F60	/*                                        */
#define	CAN_MB27_DATA1		0xFFC02F64	/*                                         */
#define	CAN_MB27_DATA2		0xFFC02F68	/*                                         */
#define	CAN_MB27_DATA3		0xFFC02F6C	/*                                         */
#define	CAN_MB27_LENGTH		0xFFC02F70	/*                                      */
#define	CAN_MB27_TIMESTAMP	0xFFC02F74	/*                                      */
#define	CAN_MB27_ID0		0xFFC02F78	/*                                    */
#define	CAN_MB27_ID1		0xFFC02F7C	/*                                     */

#define	CAN_MB28_DATA0		0xFFC02F80	/*                                        */
#define	CAN_MB28_DATA1		0xFFC02F84	/*                                         */
#define	CAN_MB28_DATA2		0xFFC02F88	/*                                         */
#define	CAN_MB28_DATA3		0xFFC02F8C	/*                                         */
#define	CAN_MB28_LENGTH		0xFFC02F90	/*                                      */
#define	CAN_MB28_TIMESTAMP	0xFFC02F94	/*                                      */
#define	CAN_MB28_ID0		0xFFC02F98	/*                                    */
#define	CAN_MB28_ID1		0xFFC02F9C	/*                                     */

#define	CAN_MB29_DATA0		0xFFC02FA0	/*                                        */
#define	CAN_MB29_DATA1		0xFFC02FA4	/*                                         */
#define	CAN_MB29_DATA2		0xFFC02FA8	/*                                         */
#define	CAN_MB29_DATA3		0xFFC02FAC	/*                                         */
#define	CAN_MB29_LENGTH		0xFFC02FB0	/*                                      */
#define	CAN_MB29_TIMESTAMP	0xFFC02FB4	/*                                      */
#define	CAN_MB29_ID0		0xFFC02FB8	/*                                    */
#define	CAN_MB29_ID1		0xFFC02FBC	/*                                     */

#define	CAN_MB30_DATA0		0xFFC02FC0	/*                                        */
#define	CAN_MB30_DATA1		0xFFC02FC4	/*                                         */
#define	CAN_MB30_DATA2		0xFFC02FC8	/*                                         */
#define	CAN_MB30_DATA3		0xFFC02FCC	/*                                         */
#define	CAN_MB30_LENGTH		0xFFC02FD0	/*                                      */
#define	CAN_MB30_TIMESTAMP	0xFFC02FD4	/*                                      */
#define	CAN_MB30_ID0		0xFFC02FD8	/*                                    */
#define	CAN_MB30_ID1		0xFFC02FDC	/*                                     */

#define	CAN_MB31_DATA0		0xFFC02FE0	/*                                        */
#define	CAN_MB31_DATA1		0xFFC02FE4	/*                                         */
#define	CAN_MB31_DATA2		0xFFC02FE8	/*                                         */
#define	CAN_MB31_DATA3		0xFFC02FEC	/*                                         */
#define	CAN_MB31_LENGTH		0xFFC02FF0	/*                                      */
#define	CAN_MB31_TIMESTAMP	0xFFC02FF4	/*                                      */
#define	CAN_MB31_ID0		0xFFC02FF8	/*                                    */
#define	CAN_MB31_ID1		0xFFC02FFC	/*                                     */

/*                         */
#define	CAN_MB_ID1(x)		(CAN_MB00_ID1+((x)*0x20))
#define	CAN_MB_ID0(x)		(CAN_MB00_ID0+((x)*0x20))
#define	CAN_MB_TIMESTAMP(x)	(CAN_MB00_TIMESTAMP+((x)*0x20))
#define	CAN_MB_LENGTH(x)	(CAN_MB00_LENGTH+((x)*0x20))
#define	CAN_MB_DATA3(x)		(CAN_MB00_DATA3+((x)*0x20))
#define	CAN_MB_DATA2(x)		(CAN_MB00_DATA2+((x)*0x20))
#define	CAN_MB_DATA1(x)		(CAN_MB00_DATA1+((x)*0x20))
#define	CAN_MB_DATA0(x)		(CAN_MB00_DATA0+((x)*0x20))


/*                                                                                   */
/*                                     */
/*                                                                               */

/*            */
#define	SYSTEM_RESET	0x0007	/*                                   */
#define	DOUBLE_FAULT	0x0008	/*                                */
#define	RESET_DOUBLE	0x2000	/*                                         */
#define	RESET_WDOG		0x4000	/*                                      */
#define	RESET_SOFTWARE	0x8000	/*                                            */

/*                          */
#define	BMODE			0x0006	/*                                                    */
#define	NOBOOT			0x0010	/*                                                */


/*                                                                    */

/*                                                     */
#define	PLL_WAKEUP_IRQ		0x00000001	/*                              */
#define	DMAC0_ERR_IRQ		0x00000002	/*                                          */
#define	PPI_ERR_IRQ		0x00000004	/*                             */
#define	SPORT0_ERR_IRQ		0x00000008	/*                                */
#define	SPORT1_ERR_IRQ		0x00000010	/*                                */
#define	SPI0_ERR_IRQ		0x00000020	/*                              */
#define	UART0_ERR_IRQ		0x00000040	/*                               */
#define	RTC_IRQ			0x00000080	/*                                   */
#define	DMA0_IRQ		0x00000100	/*                                       */
#define	DMA1_IRQ		0x00000200	/*                                             */
#define	DMA2_IRQ		0x00000400	/*                                             */
#define	DMA3_IRQ		0x00000800	/*                                             */
#define	DMA4_IRQ		0x00001000	/*                                             */
#define	DMA5_IRQ		0x00002000	/*                                       */
#define	DMA6_IRQ		0x00004000	/*                                           */
#define	DMA7_IRQ		0x00008000	/*                                           */
#define	TIMER0_IRQ		0x00010000	/*                           */
#define	TIMER1_IRQ		0x00020000	/*                           */
#define	TIMER2_IRQ		0x00040000	/*                           */
#define	PFA_IRQ			0x00080000	/*                                       */
#define	PFB_IRQ			0x00100000	/*                                       */
#define	MDMA0_0_IRQ		0x00200000	/*                                    */
#define	MDMA0_1_IRQ		0x00400000	/*                                    */
#define	WDOG_IRQ		0x00800000	/*                                           */
#define	DMAC1_ERR_IRQ		0x01000000	/*                                          */
#define	SPORT2_ERR_IRQ		0x02000000	/*                                */
#define	SPORT3_ERR_IRQ		0x04000000	/*                                */
#define	MXVR_SD_IRQ		0x08000000	/*                                         */
#define	SPI1_ERR_IRQ		0x10000000	/*                              */
#define	SPI2_ERR_IRQ		0x20000000	/*                              */
#define	UART1_ERR_IRQ		0x40000000	/*                               */
#define	UART2_ERR_IRQ		0x80000000	/*                               */

/*                                               */
#define	DMA0_ERR_IRQ		DMAC0_ERR_IRQ
#define	DMA1_ERR_IRQ		DMAC1_ERR_IRQ


/*                                                      */
#define	CAN_ERR_IRQ			0x00000001	/*                             */
#define	DMA8_IRQ			0x00000002	/*                                             */
#define	DMA9_IRQ			0x00000004	/*                                             */
#define	DMA10_IRQ			0x00000008	/*                                              */
#define	DMA11_IRQ			0x00000010	/*                                              */
#define	DMA12_IRQ			0x00000020	/*                                  */
#define	DMA13_IRQ			0x00000040	/*                                  */
#define	DMA14_IRQ			0x00000080	/*                                         */
#define	DMA15_IRQ			0x00000100	/*                                         */
#define	DMA16_IRQ			0x00000200	/*                                             */
#define	DMA17_IRQ			0x00000400	/*                                             */
#define	DMA18_IRQ			0x00000800	/*                                             */
#define	DMA19_IRQ			0x00001000	/*                                             */
#define	TWI0_IRQ			0x00002000	/*                        */
#define	TWI1_IRQ			0x00004000	/*                        */
#define	CAN_RX_IRQ			0x00008000	/*                               */
#define	CAN_TX_IRQ			0x00010000	/*                                */
#define	MDMA1_0_IRQ			0x00020000	/*                                    */
#define	MDMA1_1_IRQ			0x00040000	/*                                    */
#define	MXVR_STAT_IRQ			0x00080000	/*                               */
#define	MXVR_CM_IRQ			0x00100000	/*                                        */
#define	MXVR_AP_IRQ			0x00200000	/*                                    */

/*                                               */
#define	MDMA0_IRQ		MDMA1_0_IRQ
#define	MDMA1_IRQ		MDMA1_1_IRQ

#ifdef _MISRA_RULES
#define	_MF15 0xFu
#define	_MF7 7u
#else
#define	_MF15 0xF
#define	_MF7 7
#endif /*              */

/*                             */
#define	SIC_UNMASK_ALL	0x00000000					/*                                  */
#define	SIC_MASK_ALL	0xFFFFFFFF					/*                                */
#ifdef _MISRA_RULES
#define	SIC_MASK(x)		(1 << ((x)&0x1Fu))					/*                              */
#define	SIC_UNMASK(x)	(0xFFFFFFFFu ^ (1 << ((x)&0x1Fu)))	/*                                */
#else
#define	SIC_MASK(x)		(1 << ((x)&0x1F))					/*                              */
#define	SIC_UNMASK(x)	(0xFFFFFFFF ^ (1 << ((x)&0x1F)))	/*                                */
#endif /*              */

/*                           */
#define	IWR_DISABLE_ALL	0x00000000					/*                                */
#define	IWR_ENABLE_ALL	0xFFFFFFFF					/*                               */
#ifdef _MISRA_RULES
#define	IWR_ENABLE(x)	(1 << ((x)&0x1Fu))					/*                             */
#define	IWR_DISABLE(x)	(0xFFFFFFFFu ^ (1 << ((x)&0x1Fu)))	/*                              */
#else
#define	IWR_ENABLE(x)	(1 << ((x)&0x1F))					/*                             */
#define	IWR_DISABLE(x)	(0xFFFFFFFF ^ (1 << ((x)&0x1F)))	/*                              */
#endif /*              */

/*                                                                          */
/*                          */
#define	PORT_EN		0x0001	/*                  */
#define	PORT_DIR	0x0002	/*                        */
#define	XFR_TYPE	0x000C	/*                    */
#define	PORT_CFG	0x0030	/*                        */
#define	FLD_SEL		0x0040	/*                         */
#define	PACK_EN		0x0080	/*                  */
/*                                                                                    */
#define	SKIP_EN		0x0200	/*                         */
#define	SKIP_EO		0x0400	/*                            */
#define	DLENGTH		0x3800	/*                  */
#define	DLEN_8		0x0	     /*                                 */
#define	DLEN_10		0x0800		/*                       */
#define	DLEN_11		0x1000		/*                       */
#define	DLEN_12		0x1800		/*                       */
#define	DLEN_13		0x2000		/*                       */
#define	DLEN_14		0x2800		/*                       */
#define	DLEN_15		0x3000		/*                       */
#define	DLEN_16		0x3800		/*                       */
#ifdef _MISRA_RULES
#define	DLEN(x)		((((x)-9u) & 0x07u) << 11)  /*                                              */
#else
#define	DLEN(x)		((((x)-9) & 0x07) << 11)  /*                                              */
#endif /*              */
#define	POL			0xC000	/*                             */
#define	POLC		0x4000		/*                    */
#define	POLS		0x8000		/*                         */


/*                           */
#define	FLD			0x0400	/*                   */
#define	FT_ERR		0x0800	/*                   */
#define	OVR			0x1000	/*                     */
#define	UNDR		0x2000	/*                     */
#define	ERR_DET		0x4000	/*                          */
#define	ERR_NCOR	0x8000	/*                               */


/*                                                         */

/*                                                   */

#define	CTYPE			0x0040	/*                            */
#define	CTYPE_P			0x6		/*                                         */
#define	PCAP8			0x0080	/*                                 */
#define	PCAP16			0x0100	/*                                */
#define	PCAP32			0x0200	/*                                */
#define	PCAPWR			0x0400	/*                               */
#define	PCAPRD			0x0800	/*                              */
#define	PMAP			0xF000	/*                          */

/*                                     */
#define	PMAP_PPI		0x0000	/*                   */
#define	PMAP_SPORT0RX	0x1000	/*                         */
#define	PMAP_SPORT0TX	0x2000	/*                          */
#define	PMAP_SPORT1RX	0x3000	/*                         */
#define	PMAP_SPORT1TX	0x4000	/*                          */
#define	PMAP_SPI0		0x5000	/*              */
#define	PMAP_UART0RX		0x6000	/*                       */
#define	PMAP_UART0TX		0x7000	/*                        */

/*                                     */
#define	PMAP_SPORT2RX	    0x0000  /*                         */
#define	PMAP_SPORT2TX	    0x1000  /*                          */
#define	PMAP_SPORT3RX	    0x2000  /*                         */
#define	PMAP_SPORT3TX	    0x3000  /*                          */
#define	PMAP_SPI1	    0x6000  /*               */
#define	PMAP_SPI2	    0x7000  /*               */
#define	PMAP_UART1RX	    0x8000  /*                        */
#define	PMAP_UART1TX	    0x9000  /*                         */
#define	PMAP_UART2RX	    0xA000  /*                        */
#define	PMAP_UART2TX	    0xB000  /*                         */


/*                                                                  */
/*                           */
/*                       */
#define	TIMEN0			0x0001	/*                */
#define	TIMEN1			0x0002	/*                */
#define	TIMEN2			0x0004	/*                */

#define	TIMEN0_P		0x00
#define	TIMEN1_P		0x01
#define	TIMEN2_P		0x02

/*                        */
#define	TIMDIS0			0x0001	/*                 */
#define	TIMDIS1			0x0002	/*                 */
#define	TIMDIS2			0x0004	/*                 */

#define	TIMDIS0_P		0x00
#define	TIMDIS1_P		0x01
#define	TIMDIS2_P		0x02

/*                       */
#define	TIMIL0			0x0001	/*                   */
#define	TIMIL1			0x0002	/*                   */
#define	TIMIL2			0x0004	/*                   */
#define	TOVF_ERR0		0x0010	/*                          */
#define	TOVF_ERR1		0x0020	/*                          */
#define	TOVF_ERR2		0x0040	/*                          */
#define	TRUN0			0x1000	/*                             */
#define	TRUN1			0x2000	/*                             */
#define	TRUN2			0x4000	/*                             */

#define	TIMIL0_P		0x00
#define	TIMIL1_P		0x01
#define	TIMIL2_P		0x02
#define	TOVF_ERR0_P		0x04
#define	TOVF_ERR1_P		0x05
#define	TOVF_ERR2_P		0x06
#define	TRUN0_P			0x0C
#define	TRUN1_P			0x0D
#define	TRUN2_P			0x0E

/*                                                                       */
#define	TOVL_ERR0		TOVF_ERR0
#define	TOVL_ERR1		TOVF_ERR1
#define	TOVL_ERR2		TOVF_ERR2
#define	TOVL_ERR0_P		TOVF_ERR0_P
#define	TOVL_ERR1_P	TOVF_ERR1_P
#define	TOVL_ERR2_P	TOVF_ERR2_P

/*                         */
#define	PWM_OUT			0x0001
#define	WDTH_CAP		0x0002
#define	EXT_CLK			0x0003
#define	PULSE_HI		0x0004
#define	PERIOD_CNT		0x0008
#define	IRQ_ENA			0x0010
#define	TIN_SEL			0x0020
#define	OUT_DIS			0x0040
#define	CLK_SEL			0x0080
#define	TOGGLE_HI		0x0100
#define	EMU_RUN			0x0200
#ifdef _MISRA_RULES
#define	ERR_TYP(x)		(((x) &	0x03u) << 14)
#else
#define	ERR_TYP(x)		(((x) &	0x03) << 14)
#endif /*              */

#define	TMODE_P0		0x00
#define	TMODE_P1		0x01
#define	PULSE_HI_P		0x02
#define	PERIOD_CNT_P	0x03
#define	IRQ_ENA_P		0x04
#define	TIN_SEL_P		0x05
#define	OUT_DIS_P		0x06
#define	CLK_SEL_P		0x07
#define	TOGGLE_HI_P		0x08
#define	EMU_RUN_P		0x09
#define	ERR_TYP_P0		0x0E
#define	ERR_TYP_P1		0x0F

/*                                                                           */
/*                   */
#define	AMCKEN		0x0001	/*               */
#define	AMBEN_NONE	0x0000	/*                    */
#define	AMBEN_B0	0x0002	/*                                        */
#define	AMBEN_B0_B1	0x0004	/*                                             */
#define	AMBEN_B0_B1_B2	0x0006	/*                                              */
#define	AMBEN_ALL	0x0008	/*                                                       */
#define	CDPRIO		0x0100	/*                                                  */

/*                           */
#define	AMCKEN_P		0x0000	/*               */
#define	AMBEN_P0		0x0001	/*                                                                            */
#define	AMBEN_P1		0x0002	/*                                                                               */
#define	AMBEN_P2		0x0003	/*                                                                           */

/*                    */
#define	B0RDYEN			0x00000001  /*                                        */
#define	B0RDYPOL		0x00000002  /*                                                     */
#define	B0TT_1			0x00000004  /*                                                     */
#define	B0TT_2			0x00000008  /*                                                      */
#define	B0TT_3			0x0000000C  /*                                                      */
#define	B0TT_4			0x00000000  /*                                                      */
#define	B0ST_1			0x00000010  /*                                                                    */
#define	B0ST_2			0x00000020  /*                                                                     */
#define	B0ST_3			0x00000030  /*                                                                     */
#define	B0ST_4			0x00000000  /*                                                                     */
#define	B0HT_1			0x00000040  /*                                                                         */
#define	B0HT_2			0x00000080  /*                                                                          */
#define	B0HT_3			0x000000C0  /*                                                                          */
#define	B0HT_0			0x00000000  /*                                                                          */
#define	B0RAT_1			0x00000100  /*                                   */
#define	B0RAT_2			0x00000200  /*                                    */
#define	B0RAT_3			0x00000300  /*                                    */
#define	B0RAT_4			0x00000400  /*                                    */
#define	B0RAT_5			0x00000500  /*                                    */
#define	B0RAT_6			0x00000600  /*                                    */
#define	B0RAT_7			0x00000700  /*                                    */
#define	B0RAT_8			0x00000800  /*                                    */
#define	B0RAT_9			0x00000900  /*                                    */
#define	B0RAT_10		0x00000A00  /*                                     */
#define	B0RAT_11		0x00000B00  /*                                     */
#define	B0RAT_12		0x00000C00  /*                                     */
#define	B0RAT_13		0x00000D00  /*                                     */
#define	B0RAT_14		0x00000E00  /*                                     */
#define	B0RAT_15		0x00000F00  /*                                     */
#define	B0WAT_1			0x00001000  /*                                    */
#define	B0WAT_2			0x00002000  /*                                     */
#define	B0WAT_3			0x00003000  /*                                     */
#define	B0WAT_4			0x00004000  /*                                     */
#define	B0WAT_5			0x00005000  /*                                     */
#define	B0WAT_6			0x00006000  /*                                     */
#define	B0WAT_7			0x00007000  /*                                     */
#define	B0WAT_8			0x00008000  /*                                     */
#define	B0WAT_9			0x00009000  /*                                     */
#define	B0WAT_10		0x0000A000  /*                                      */
#define	B0WAT_11		0x0000B000  /*                                      */
#define	B0WAT_12		0x0000C000  /*                                      */
#define	B0WAT_13		0x0000D000  /*                                      */
#define	B0WAT_14		0x0000E000  /*                                      */
#define	B0WAT_15		0x0000F000  /*                                      */
#define	B1RDYEN			0x00010000  /*                                        */
#define	B1RDYPOL		0x00020000  /*                                                     */
#define	B1TT_1			0x00040000  /*                                                     */
#define	B1TT_2			0x00080000  /*                                                      */
#define	B1TT_3			0x000C0000  /*                                                      */
#define	B1TT_4			0x00000000  /*                                                      */
#define	B1ST_1			0x00100000  /*                                                                         */
#define	B1ST_2			0x00200000  /*                                                                          */
#define	B1ST_3			0x00300000  /*                                                                          */
#define	B1ST_4			0x00000000  /*                                                                          */
#define	B1HT_1			0x00400000  /*                                                                            */
#define	B1HT_2			0x00800000  /*                                                                             */
#define	B1HT_3			0x00C00000  /*                                                                             */
#define	B1HT_0			0x00000000  /*                                                                             */
#define	B1RAT_1			0x01000000  /*                                   */
#define	B1RAT_2			0x02000000  /*                                    */
#define	B1RAT_3			0x03000000  /*                                    */
#define	B1RAT_4			0x04000000  /*                                    */
#define	B1RAT_5			0x05000000  /*                                    */
#define	B1RAT_6			0x06000000  /*                                    */
#define	B1RAT_7			0x07000000  /*                                    */
#define	B1RAT_8			0x08000000  /*                                    */
#define	B1RAT_9			0x09000000  /*                                    */
#define	B1RAT_10		0x0A000000  /*                                     */
#define	B1RAT_11		0x0B000000  /*                                     */
#define	B1RAT_12		0x0C000000  /*                                     */
#define	B1RAT_13		0x0D000000  /*                                     */
#define	B1RAT_14		0x0E000000  /*                                     */
#define	B1RAT_15		0x0F000000  /*                                     */
#define	B1WAT_1			0x10000000 /*                                    */
#define	B1WAT_2			0x20000000  /*                                     */
#define	B1WAT_3			0x30000000  /*                                     */
#define	B1WAT_4			0x40000000  /*                                     */
#define	B1WAT_5			0x50000000  /*                                     */
#define	B1WAT_6			0x60000000  /*                                     */
#define	B1WAT_7			0x70000000  /*                                     */
#define	B1WAT_8			0x80000000  /*                                     */
#define	B1WAT_9			0x90000000  /*                                     */
#define	B1WAT_10		0xA0000000  /*                                      */
#define	B1WAT_11		0xB0000000  /*                                      */
#define	B1WAT_12		0xC0000000  /*                                      */
#define	B1WAT_13		0xD0000000  /*                                      */
#define	B1WAT_14		0xE0000000  /*                                      */
#define	B1WAT_15		0xF0000000  /*                                      */

/*                    */
#define	B2RDYEN			0x00000001  /*                                        */
#define	B2RDYPOL		0x00000002  /*                                                     */
#define	B2TT_1			0x00000004  /*                                                     */
#define	B2TT_2			0x00000008  /*                                                      */
#define	B2TT_3			0x0000000C  /*                                                      */
#define	B2TT_4			0x00000000  /*                                                      */
#define	B2ST_1			0x00000010  /*                                                                         */
#define	B2ST_2			0x00000020  /*                                                                          */
#define	B2ST_3			0x00000030  /*                                                                          */
#define	B2ST_4			0x00000000  /*                                                                          */
#define	B2HT_1			0x00000040  /*                                                                            */
#define	B2HT_2			0x00000080  /*                                                                             */
#define	B2HT_3			0x000000C0  /*                                                                             */
#define	B2HT_0			0x00000000  /*                                                                             */
#define	B2RAT_1			0x00000100  /*                                   */
#define	B2RAT_2			0x00000200  /*                                    */
#define	B2RAT_3			0x00000300  /*                                    */
#define	B2RAT_4			0x00000400  /*                                    */
#define	B2RAT_5			0x00000500  /*                                    */
#define	B2RAT_6			0x00000600  /*                                    */
#define	B2RAT_7			0x00000700  /*                                    */
#define	B2RAT_8			0x00000800  /*                                    */
#define	B2RAT_9			0x00000900  /*                                    */
#define	B2RAT_10		0x00000A00  /*                                     */
#define	B2RAT_11		0x00000B00  /*                                     */
#define	B2RAT_12		0x00000C00  /*                                     */
#define	B2RAT_13		0x00000D00  /*                                     */
#define	B2RAT_14		0x00000E00  /*                                     */
#define	B2RAT_15		0x00000F00  /*                                     */
#define	B2WAT_1			0x00001000  /*                                    */
#define	B2WAT_2			0x00002000  /*                                     */
#define	B2WAT_3			0x00003000  /*                                     */
#define	B2WAT_4			0x00004000  /*                                     */
#define	B2WAT_5			0x00005000  /*                                     */
#define	B2WAT_6			0x00006000  /*                                     */
#define	B2WAT_7			0x00007000  /*                                     */
#define	B2WAT_8			0x00008000  /*                                     */
#define	B2WAT_9			0x00009000  /*                                     */
#define	B2WAT_10		0x0000A000  /*                                      */
#define	B2WAT_11		0x0000B000  /*                                      */
#define	B2WAT_12		0x0000C000  /*                                      */
#define	B2WAT_13		0x0000D000  /*                                      */
#define	B2WAT_14		0x0000E000  /*                                      */
#define	B2WAT_15		0x0000F000  /*                                      */
#define	B3RDYEN			0x00010000  /*                                        */
#define	B3RDYPOL		0x00020000  /*                                                     */
#define	B3TT_1			0x00040000  /*                                                     */
#define	B3TT_2			0x00080000  /*                                                      */
#define	B3TT_3			0x000C0000  /*                                                      */
#define	B3TT_4			0x00000000  /*                                                      */
#define	B3ST_1			0x00100000  /*                                                                         */
#define	B3ST_2			0x00200000  /*                                                                          */
#define	B3ST_3			0x00300000  /*                                                                          */
#define	B3ST_4			0x00000000  /*                                                                          */
#define	B3HT_1			0x00400000  /*                                                                            */
#define	B3HT_2			0x00800000  /*                                                                             */
#define	B3HT_3			0x00C00000  /*                                                                             */
#define	B3HT_0			0x00000000  /*                                                                             */
#define	B3RAT_1			0x01000000 /*                                   */
#define	B3RAT_2			0x02000000  /*                                    */
#define	B3RAT_3			0x03000000  /*                                    */
#define	B3RAT_4			0x04000000  /*                                    */
#define	B3RAT_5			0x05000000  /*                                    */
#define	B3RAT_6			0x06000000  /*                                    */
#define	B3RAT_7			0x07000000  /*                                    */
#define	B3RAT_8			0x08000000  /*                                    */
#define	B3RAT_9			0x09000000  /*                                    */
#define	B3RAT_10		0x0A000000  /*                                     */
#define	B3RAT_11		0x0B000000  /*                                     */
#define	B3RAT_12		0x0C000000  /*                                     */
#define	B3RAT_13		0x0D000000  /*                                     */
#define	B3RAT_14		0x0E000000  /*                                     */
#define	B3RAT_15		0x0F000000  /*                                     */
#define	B3WAT_1			0x10000000 /*                                    */
#define	B3WAT_2			0x20000000  /*                                     */
#define	B3WAT_3			0x30000000  /*                                     */
#define	B3WAT_4			0x40000000  /*                                     */
#define	B3WAT_5			0x50000000  /*                                     */
#define	B3WAT_6			0x60000000  /*                                     */
#define	B3WAT_7			0x70000000  /*                                     */
#define	B3WAT_8			0x80000000  /*                                     */
#define	B3WAT_9			0x90000000  /*                                     */
#define	B3WAT_10		0xA0000000  /*                                      */
#define	B3WAT_11		0xB0000000  /*                                      */
#define	B3WAT_12		0xC0000000  /*                                      */
#define	B3WAT_13		0xD0000000  /*                                      */
#define	B3WAT_14		0xE0000000  /*                                      */
#define	B3WAT_15		0xF0000000  /*                                      */

/*                                                                             */
/*                   */
#define	SCTLE			0x00000001 /*                                               */
#define	CL_2			0x00000008 /*                              */
#define	CL_3			0x0000000C /*                              */
#define	PFE				0x00000010 /*                       */
#define	PFP				0x00000020 /*                                         */
#define	PASR_ALL		0x00000000	/*                                             */
#define	PASR_B0_B1		0x00000010	/*                                                   */
#define	PASR_B0			0x00000020	/*                                                */
#define	TRAS_1			0x00000040 /*                      */
#define	TRAS_2			0x00000080 /*                       */
#define	TRAS_3			0x000000C0 /*                       */
#define	TRAS_4			0x00000100 /*                       */
#define	TRAS_5			0x00000140 /*                       */
#define	TRAS_6			0x00000180 /*                       */
#define	TRAS_7			0x000001C0 /*                       */
#define	TRAS_8			0x00000200 /*                       */
#define	TRAS_9			0x00000240 /*                       */
#define	TRAS_10			0x00000280 /*                        */
#define	TRAS_11			0x000002C0 /*                        */
#define	TRAS_12			0x00000300 /*                        */
#define	TRAS_13			0x00000340 /*                        */
#define	TRAS_14			0x00000380 /*                        */
#define	TRAS_15			0x000003C0 /*                        */
#define	TRP_1			0x00000800 /*                     */
#define	TRP_2			0x00001000 /*                      */
#define	TRP_3			0x00001800 /*                      */
#define	TRP_4			0x00002000 /*                      */
#define	TRP_5			0x00002800 /*                      */
#define	TRP_6			0x00003000 /*                      */
#define	TRP_7			0x00003800 /*                      */
#define	TRCD_1			0x00008000 /*                      */
#define	TRCD_2			0x00010000 /*                       */
#define	TRCD_3			0x00018000 /*                       */
#define	TRCD_4			0x00020000 /*                       */
#define	TRCD_5			0x00028000 /*                       */
#define	TRCD_6			0x00030000 /*                       */
#define	TRCD_7			0x00038000 /*                       */
#define	TWR_1			0x00080000 /*                     */
#define	TWR_2			0x00100000 /*                      */
#define	TWR_3			0x00180000 /*                      */
#define	PUPSD			0x00200000 /*                     */
#define	PSM				0x00400000 /*                                                                              */
#define	PSS				0x00800000 /*                                                     */
#define	SRFS			0x01000000 /*                               */
#define	EBUFE			0x02000000 /*                                  */
#define	FBBRW			0x04000000 /*                                     */
#define	EMREN			0x10000000 /*                               */
#define	TCSR			0x20000000 /*                                              */
#define	CDDBG			0x40000000 /*                                          */

/*                   */
#define	EBE				0x00000001 /*                            */
#define	EBSZ_16			0x00000000 /*                                 */
#define	EBSZ_32			0x00000002 /*                                 */
#define	EBSZ_64			0x00000004 /*                                 */
#define	EBSZ_128		0x00000006 /*                                  */
#define	EBSZ_256		0x00000008 /*                                  */
#define	EBSZ_512		0x0000000A /*                                  */
#define	EBCAW_8			0x00000000 /*                                                   */
#define	EBCAW_9			0x00000010 /*                                                   */
#define	EBCAW_10		0x00000020 /*                                                   */
#define	EBCAW_11		0x00000030 /*                                                   */

/*                   */
#define	SDCI			0x00000001 /*                          */
#define	SDSRA			0x00000002 /*                                    */
#define	SDPUA			0x00000004 /*                        */
#define	SDRS			0x00000008 /*                         */
#define	SDEASE			0x00000010 /*                                     */
#define	BGSTAT			0x00000020 /*             */


/*                                                                               */
/*                                                                 */
#ifdef _MISRA_RULES
#define	CLKLOW(x)	((x) & 0xFFu)		/*                           */
#define	CLKHI(y)	(((y)&0xFFu)<<0x8)	/*                              */
#else
#define	CLKLOW(x)	((x) & 0xFF)		/*                           */
#define	CLKHI(y)	(((y)&0xFF)<<0x8)	/*                              */
#endif /*              */

/*                             */
#define	PRESCALE	0x007F		/*                                           */
#define	TWI_ENA		0x0080		/*              */
#define	SCCB		0x0200		/*                           */

/*                               */
#define	SEN			0x0001		/*                */
#define	SADD_LEN	0x0002		/*                      */
#define	STDVAL		0x0004		/*                           */
#define	NAK			0x0008		/*                                              */
#define	GEN			0x0010		/*                                       */

/*                               */
#define	SDIR		0x0001		/*                                              */
#define	GCALL		0x0002		/*                        */

/*                              */
#define	MEN			0x0001		/*                    */
#define	MADD_LEN	0x0002		/*                       */
#define	MDIR		0x0004		/*                                    */
#define	FAST		0x0008		/*                            */
#define	STOP		0x0010		/*                      */
#define	RSTART		0x0020		/*                                          */
#define	DCNT		0x3FC0		/*                        */
#define	SDAOVR		0x4000		/*                      */
#define	SCLOVR		0x8000		/*                       */

/*                               */
#define	MPROG		0x0001		/*                             */
#define	LOSTARB		0x0002		/*                                           */
#define	ANAK		0x0004		/*                          */
#define	DNAK		0x0008		/*                       */
#define	BUFRDERR	0x0010		/*                   */
#define	BUFWRERR	0x0020		/*                    */
#define	SDASEN		0x0040		/*                   */
#define	SCLSEN		0x0080		/*                    */
#define	BUSBUSY		0x0100		/*                    */

/*                                        */
#define	SINIT		0x0001		/*                          */
#define	SCOMP		0x0002		/*                         */
#define	SERR		0x0004		/*                      */
#define	SOVF		0x0008		/*                */
#define	MCOMP		0x0010		/*                          */
#define	MERR		0x0020		/*                       */
#define	XMTSERV		0x0040		/*                       */
#define	RCVSERV		0x0080		/*                      */

/*                          */
#define	XMTFLUSH	0x0001		/*                       */
#define	RCVFLUSH	0x0002		/*                      */
#define	XMTINTLEN	0x0004		/*                                  */
#define	RCVINTLEN	0x0008		/*                                 */

/*                              */
#define	XMTSTAT		0x0003		/*                      */
#define	XMT_EMPTY	0x0000		/*                      */
#define	XMT_HALF	0x0001		/*                                    */
#define	XMT_FULL	0x0003		/*                                        */

#define	RCVSTAT		0x000C		/*                     */
#define	RCV_EMPTY	0x0000		/*                     */
#define	RCV_HALF	0x0004		/*                                  */
#define	RCV_FULL	0x000C		/*                                      */

#endif
