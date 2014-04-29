/*
 * Copyright (c) 2006-2008 Nick Kossifidis <mickflemm@gmail.com>
 * Copyright (c) 2004-2008 Reyk Floeter <reyk@openbsd.org>
 * Copyright (c) 2007-2008 Michael Taylor <mike.taylor@apprion.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

/*
 * Register values for Atheros 5210/5211/5212 cards from OpenBSD's ar5k
 * maintained by Reyk Floeter
 *
 * I tried to document those registers by looking at ar5k code, some
 * 802.11 (802.11e mostly) papers and by reading various public available
 * Atheros presentations and papers like these:
 *
 * 5210 - http://nova.stanford.edu/~bbaas/ps/isscc2002_slides.pdf
 *
 * 5211 - http://www.hotchips.org/archives/hc14/3_Tue/16_mcfarland.pdf
 *
 * This file also contains register values found on a memory dump of
 * Atheros's ART program (Atheros Radio Test), on ath9k, on legacy-hal
 * released by Atheros and on various debug messages found on the net.
 */

#include "../reg.h"

/*                         */

/*
                                 
                                                      
                                    
 */
#define AR5K_NOQCU_TXDP0	0x0000		/*                */
#define AR5K_NOQCU_TXDP1	0x0004		/*                   */

/*
                       
 */
#define	AR5K_CR		0x0008			/*                  */
#define AR5K_CR_TXE0	0x00000001	/*                               */
#define AR5K_CR_TXE1	0x00000002	/*                               */
#define	AR5K_CR_RXE	0x00000004	/*           */
#define AR5K_CR_TXD0	0x00000008	/*                                */
#define AR5K_CR_TXD1	0x00000010	/*                                */
#define	AR5K_CR_RXD	0x00000020	/*            */
#define	AR5K_CR_SWI	0x00000040	/*                    */

/*
                                 
 */
#define	AR5K_RXDP	0x000c

/*
                                    
 */
#define	AR5K_CFG		0x0014			/*                  */
#define	AR5K_CFG_SWTD		0x00000001	/*                                                */
#define	AR5K_CFG_SWTB		0x00000002	/*                     */
#define	AR5K_CFG_SWRD		0x00000004	/*                         */
#define	AR5K_CFG_SWRB		0x00000008	/*                     */
#define	AR5K_CFG_SWRG		0x00000010	/*                           */
#define AR5K_CFG_IBSS		0x00000020	/*                       */
#define AR5K_CFG_PHY_OK		0x00000100	/*         */
#define AR5K_CFG_EEBS		0x00000200	/*                */
#define	AR5K_CFG_CLKGD		0x00000400	/*                                     */
#define AR5K_CFG_TXCNT		0x00007800	/*                           */
#define AR5K_CFG_TXCNT_S	11
#define AR5K_CFG_TXFSTAT	0x00008000	/*                            */
#define AR5K_CFG_TXFSTRT	0x00010000	/*        */
#define	AR5K_CFG_PCI_THRES	0x00060000	/*                                    */
#define	AR5K_CFG_PCI_THRES_S	17

/*
                            
 */
#define AR5K_IER		0x0024		/*                  */
#define AR5K_IER_DISABLE	0x00000000	/*                         */
#define AR5K_IER_ENABLE		0x00000001	/*                        */


/*
                                            
                                          
 */

/*
                                 
 */
#define AR5K_BCR		0x0028		/*                  */
#define AR5K_BCR_AP		0x00000000	/*         */
#define AR5K_BCR_ADHOC		0x00000001	/*             */
#define AR5K_BCR_BDMAE		0x00000002	/*            */
#define AR5K_BCR_TQ1FV		0x00000004	/*                            */
#define AR5K_BCR_TQ1V		0x00000008	/*                               */
#define AR5K_BCR_BCGET		0x00000010

/*
                                     
 */
#define AR5K_RTSD0		0x0028		/*                  */
#define	AR5K_RTSD0_6		0x000000ff	/*                           */
#define	AR5K_RTSD0_6_S		0		/*                            */
#define	AR5K_RTSD0_9		0x0000ff00	/*    */
#define	AR5K_RTSD0_9_S		8
#define	AR5K_RTSD0_12		0x00ff0000	/*     */
#define	AR5K_RTSD0_12_S		16
#define	AR5K_RTSD0_18		0xff000000	/*     */
#define	AR5K_RTSD0_18_S		24


/*
                                           
                                           
 */

/*
                                
  
                                                                           
                                                                           
                                                                              
                                                                              
                                                                              
                                                                   
 */
#define AR5K_BSR		0x002c			/*                  */
#define AR5K_BSR_BDLYSW		0x00000001	/*                     */
#define AR5K_BSR_BDLYDMA	0x00000002	/*                      */
#define AR5K_BSR_TXQ1F		0x00000004	/*                           */
#define AR5K_BSR_ATIMDLY	0x00000008	/*                */
#define AR5K_BSR_SNPADHOC	0x00000100	/*                     */
#define AR5K_BSR_SNPBDMAE	0x00000200	/*                        */
#define AR5K_BSR_SNPTQ1FV	0x00000400	/*                                    */
#define AR5K_BSR_SNPTQ1V	0x00000800	/*                                       */
#define AR5K_BSR_SNAPSHOTSVALID	0x00001000	/*                             */
#define AR5K_BSR_SWBA_CNT	0x00ff0000

/*
                                      
 */
#define AR5K_RTSD1		0x002c			/*                  */
#define	AR5K_RTSD1_24		0x000000ff	/*      */
#define	AR5K_RTSD1_24_S		0
#define	AR5K_RTSD1_36		0x0000ff00	/*      */
#define	AR5K_RTSD1_36_S		8
#define	AR5K_RTSD1_48		0x00ff0000	/*      */
#define	AR5K_RTSD1_48_S		16
#define	AR5K_RTSD1_54		0xff000000	/*      */
#define	AR5K_RTSD1_54_S		24


/*
                                  
 */
#define AR5K_TXCFG			0x0030			/*                  */
#define AR5K_TXCFG_SDMAMR		0x00000007	/*                 */
#define AR5K_TXCFG_SDMAMR_S		0
#define AR5K_TXCFG_B_MODE		0x00000008	/*                                   */
#define AR5K_TXCFG_TXFSTP		0x00000008	/*                         */
#define AR5K_TXCFG_TXFULL		0x000003f0	/*                       */
#define AR5K_TXCFG_TXFULL_S		4
#define AR5K_TXCFG_TXFULL_0B		0x00000000
#define AR5K_TXCFG_TXFULL_64B		0x00000010
#define AR5K_TXCFG_TXFULL_128B		0x00000020
#define AR5K_TXCFG_TXFULL_192B		0x00000030
#define AR5K_TXCFG_TXFULL_256B		0x00000040
#define AR5K_TXCFG_TXCONT_EN		0x00000080
#define AR5K_TXCFG_DMASIZE		0x00000100	/*                                  */
#define AR5K_TXCFG_JUMBO_DESC_EN	0x00000400	/*                                     */
#define AR5K_TXCFG_ADHOC_BCN_ATIM	0x00000800	/*                          */
#define AR5K_TXCFG_ATIM_WINDOW_DEF_DIS	0x00001000	/*                                   */
#define AR5K_TXCFG_RTSRND		0x00001000	/*         */
#define AR5K_TXCFG_FRMPAD_DIS		0x00002000	/*         */
#define AR5K_TXCFG_RDY_CBR_DIS		0x00004000	/*                                */
#define AR5K_TXCFG_JUMBO_FRM_MODE	0x00008000	/*                          */
#define	AR5K_TXCFG_DCU_DBL_BUF_DIS	0x00008000	/*                                 */
#define AR5K_TXCFG_DCU_CACHING_DIS	0x00010000	/*                     */

/*
                                 
 */
#define AR5K_RXCFG		0x0034			/*                  */
#define AR5K_RXCFG_SDMAMW	0x00000007	/*                  */
#define AR5K_RXCFG_SDMAMW_S	0
#define AR5K_RXCFG_ZLFDMA	0x00000008	/*                              */
#define	AR5K_RXCFG_DEF_ANTENNA	0x00000010	/*                     */
#define AR5K_RXCFG_JUMBO_RXE	0x00000020	/*                                     */
#define AR5K_RXCFG_JUMBO_WRAP	0x00000040	/*                           */
#define AR5K_RXCFG_SLE_ENTRY	0x00000080	/*                    */

/*
                                                 
                         
 */
#define AR5K_RXJLA		0x0038

/*
                       
 */
#define AR5K_MIBC		0x0040			/*                  */
#define AR5K_MIBC_COW		0x00000001	/*                          */
#define AR5K_MIBC_FMC		0x00000002	/*                      */
#define AR5K_MIBC_CMC		0x00000004	/*                     */
#define AR5K_MIBC_MCS		0x00000008	/*                                   */

/*
                            
 */
#define AR5K_TOPS		0x0044
#define	AR5K_TOPS_M		0x0000ffff

/*
                                               
 */
#define AR5K_RXNOFRM		0x0048
#define	AR5K_RXNOFRM_M		0x000003ff

/*
                                            
 */
#define AR5K_TXNOFRM		0x004c
#define	AR5K_TXNOFRM_M		0x000003ff
#define	AR5K_TXNOFRM_QCU	0x000ffc00
#define	AR5K_TXNOFRM_QCU_S	10

/*
                                     
 */
#define AR5K_RPGTO		0x0050
#define AR5K_RPGTO_M		0x000003ff

/*
                                     
 */
#define AR5K_RFCNT		0x0054
#define AR5K_RFCNT_M		0x0000001f	/*             */
#define AR5K_RFCNT_RFCL		0x0000000f	/*        */

/*
                         
                
 */
#define AR5K_MISC		0x0058			/*                  */
#define	AR5K_MISC_DMA_OBS_M	0x000001e0
#define	AR5K_MISC_DMA_OBS_S	5
#define	AR5K_MISC_MISC_OBS_M	0x00000e00
#define	AR5K_MISC_MISC_OBS_S	9
#define	AR5K_MISC_MAC_OBS_LSB_M	0x00007000
#define	AR5K_MISC_MAC_OBS_LSB_S	12
#define	AR5K_MISC_MAC_OBS_MSB_M	0x00038000
#define	AR5K_MISC_MAC_OBS_MSB_S	15
#define AR5K_MISC_LED_DECAY	0x001c0000	/*        */
#define AR5K_MISC_LED_BLINK	0x00e00000	/*        */

/*
                                       
                
 */
#define	AR5K_QCUDCU_CLKGT	0x005c			/*                      */
#define	AR5K_QCUDCU_CLKGT_QCU	0x0000ffff	/*                    */
#define	AR5K_QCUDCU_CLKGT_DCU	0x07ff0000	/*                    */

/*
                             
  
                                                     
                                                           
                                                                   
                                                  
  
                                                              
                                                                       
               
 */
#define AR5K_ISR		0x001c			/*                         */
#define AR5K_PISR		0x0080			/*                          */
#define AR5K_ISR_RXOK		0x00000001	/*                             */
#define AR5K_ISR_RXDESC		0x00000002	/*                       */
#define AR5K_ISR_RXERR		0x00000004	/*               */
#define AR5K_ISR_RXNOFRM	0x00000008	/*                                     */
#define AR5K_ISR_RXEOL		0x00000010	/*                     */
#define AR5K_ISR_RXORN		0x00000020	/*                      */
#define AR5K_ISR_TXOK		0x00000040	/*                                */
#define AR5K_ISR_TXDESC		0x00000080	/*                       */
#define AR5K_ISR_TXERR		0x00000100	/*                */
#define AR5K_ISR_TXNOFRM	0x00000200	/*                                        
                                                    
                                                    
                                               */
#define AR5K_ISR_TXEOL		0x00000400	/*                     */
#define AR5K_ISR_TXURN		0x00000800	/*                        */
#define AR5K_ISR_MIB		0x00001000	/*                     */
#define AR5K_ISR_SWI		0x00002000	/*                    */
#define AR5K_ISR_RXPHY		0x00004000	/*           */
#define AR5K_ISR_RXKCM		0x00008000	/*                   */
#define AR5K_ISR_SWBA		0x00010000	/*                       */
#define AR5K_ISR_BRSSI		0x00020000	/*                                 */
#define AR5K_ISR_BMISS		0x00040000	/*               */
#define AR5K_ISR_HIUERR		0x00080000	/*                                  
                                                */
#define AR5K_ISR_BNR		0x00100000	/*                          */
#define AR5K_ISR_MCABT		0x00100000	/*                           */
#define AR5K_ISR_RXCHIRP	0x00200000	/*                        */
#define AR5K_ISR_SSERR		0x00200000	/*                              */
#define AR5K_ISR_DPERR		0x00400000	/*                         */
#define AR5K_ISR_RXDOPPLER	0x00400000	/*                                */
#define AR5K_ISR_TIM		0x00800000	/*         */
#define AR5K_ISR_BCNMISC	0x00800000	/*                              
                                                      
                                                      */
#define AR5K_ISR_GPIO		0x01000000	/*                */
#define AR5K_ISR_QCBRORN	0x02000000	/*                         */
#define AR5K_ISR_QCBRURN	0x04000000	/*                          */
#define AR5K_ISR_QTRIG		0x08000000	/*                                */

#define	AR5K_ISR_BITS_FROM_SISRS	(AR5K_ISR_TXOK | AR5K_ISR_TXDESC |\
					AR5K_ISR_TXERR | AR5K_ISR_TXEOL |\
					AR5K_ISR_TXURN | AR5K_ISR_HIUERR |\
					AR5K_ISR_BCNMISC | AR5K_ISR_QCBRORN |\
					AR5K_ISR_QCBRURN | AR5K_ISR_QTRIG)

/*
                                             
  
                                                        
               
 */
#define AR5K_SISR0		0x0084			/*                          */
#define AR5K_SISR0_QCU_TXOK	0x000003ff	/*                   */
#define AR5K_SISR0_QCU_TXOK_S	0
#define AR5K_SISR0_QCU_TXDESC	0x03ff0000	/*                     */
#define AR5K_SISR0_QCU_TXDESC_S	16

#define AR5K_SISR1		0x0088			/*                          */
#define AR5K_SISR1_QCU_TXERR	0x000003ff	/*                    */
#define AR5K_SISR1_QCU_TXERR_S	0
#define AR5K_SISR1_QCU_TXEOL	0x03ff0000	/*                    */
#define AR5K_SISR1_QCU_TXEOL_S	16

#define AR5K_SISR2		0x008c			/*                          */
#define AR5K_SISR2_QCU_TXURN	0x000003ff	/*                    */
#define	AR5K_SISR2_QCU_TXURN_S	0
#define	AR5K_SISR2_MCABT	0x00010000	/*                    */
#define	AR5K_SISR2_SSERR	0x00020000	/*                       */
#define	AR5K_SISR2_DPERR	0x00040000	/*                  */
#define	AR5K_SISR2_TIM		0x01000000	/*         */
#define	AR5K_SISR2_CAB_END	0x02000000	/*         */
#define	AR5K_SISR2_DTIM_SYNC	0x04000000	/*                        */
#define	AR5K_SISR2_BCN_TIMEOUT	0x08000000	/*                        */
#define	AR5K_SISR2_CAB_TIMEOUT	0x10000000	/*                     */
#define	AR5K_SISR2_DTIM		0x20000000	/*         */
#define	AR5K_SISR2_TSFOOR	0x80000000	/*                  */

#define AR5K_SISR3		0x0090			/*                          */
#define AR5K_SISR3_QCBRORN	0x000003ff	/*                  */
#define AR5K_SISR3_QCBRORN_S	0
#define AR5K_SISR3_QCBRURN	0x03ff0000	/*                  */
#define AR5K_SISR3_QCBRURN_S	16

#define AR5K_SISR4		0x0094			/*                          */
#define AR5K_SISR4_QTRIG	0x000003ff	/*                */
#define AR5K_SISR4_QTRIG_S	0

/*
                                                           
 */
#define AR5K_RAC_PISR		0x00c0		/*                     */
#define AR5K_RAC_SISR0		0x00c4		/*                      */
#define AR5K_RAC_SISR1		0x00c8		/*                      */
#define AR5K_RAC_SISR2		0x00cc		/*                      */
#define AR5K_RAC_SISR3		0x00d0		/*                      */
#define AR5K_RAC_SISR4		0x00d4		/*                      */

/*
                           
  
                                                                         
                                                                                
 */
#define	AR5K_IMR		0x0020			/*                         */
#define AR5K_PIMR		0x00a0			/*                          */
#define AR5K_IMR_RXOK		0x00000001	/*                            */
#define AR5K_IMR_RXDESC		0x00000002	/*                      */
#define AR5K_IMR_RXERR		0x00000004	/*              */
#define AR5K_IMR_RXNOFRM	0x00000008	/*                                    */
#define AR5K_IMR_RXEOL		0x00000010	/*                    */
#define AR5K_IMR_RXORN		0x00000020	/*                     */
#define AR5K_IMR_TXOK		0x00000040	/*                               */
#define AR5K_IMR_TXDESC		0x00000080	/*                      */
#define AR5K_IMR_TXERR		0x00000100	/*               */
#define AR5K_IMR_TXNOFRM	0x00000200	/*                                        */
#define AR5K_IMR_TXEOL		0x00000400	/*                    */
#define AR5K_IMR_TXURN		0x00000800	/*                       */
#define AR5K_IMR_MIB		0x00001000	/*                    */
#define AR5K_IMR_SWI		0x00002000	/*                    */
#define AR5K_IMR_RXPHY		0x00004000	/*          */
#define AR5K_IMR_RXKCM		0x00008000	/*                   */
#define AR5K_IMR_SWBA		0x00010000	/*                      */
#define AR5K_IMR_BRSSI		0x00020000	/*                                 */
#define AR5K_IMR_BMISS		0x00040000	/*              */
#define AR5K_IMR_HIUERR		0x00080000	/*                                   */
#define AR5K_IMR_BNR		0x00100000	/*                          */
#define AR5K_IMR_MCABT		0x00100000	/*                           */
#define AR5K_IMR_RXCHIRP	0x00200000	/*                       */
#define AR5K_IMR_SSERR		0x00200000	/*                              */
#define AR5K_IMR_DPERR		0x00400000	/*                          */
#define AR5K_IMR_RXDOPPLER	0x00400000	/*                                */
#define AR5K_IMR_TIM		0x00800000	/*         */
#define AR5K_IMR_BCNMISC	0x00800000	/*                                              
                                                   */
#define AR5K_IMR_GPIO		0x01000000	/*               */
#define AR5K_IMR_QCBRORN	0x02000000	/*                             */
#define AR5K_IMR_QCBRURN	0x04000000	/*                              */
#define AR5K_IMR_QTRIG		0x08000000	/*                                */

/*
                                                     
 */
#define AR5K_SIMR0		0x00a4			/*                          */
#define AR5K_SIMR0_QCU_TXOK	0x000003ff	/*                   */
#define AR5K_SIMR0_QCU_TXOK_S	0
#define AR5K_SIMR0_QCU_TXDESC	0x03ff0000	/*                     */
#define AR5K_SIMR0_QCU_TXDESC_S	16

#define AR5K_SIMR1		0x00a8			/*                          */
#define AR5K_SIMR1_QCU_TXERR	0x000003ff	/*                    */
#define AR5K_SIMR1_QCU_TXERR_S	0
#define AR5K_SIMR1_QCU_TXEOL	0x03ff0000	/*                    */
#define AR5K_SIMR1_QCU_TXEOL_S	16

#define AR5K_SIMR2		0x00ac			/*                          */
#define AR5K_SIMR2_QCU_TXURN	0x000003ff	/*                    */
#define AR5K_SIMR2_QCU_TXURN_S	0
#define	AR5K_SIMR2_MCABT	0x00010000	/*                    */
#define	AR5K_SIMR2_SSERR	0x00020000	/*                       */
#define	AR5K_SIMR2_DPERR	0x00040000	/*                  */
#define	AR5K_SIMR2_TIM		0x01000000	/*         */
#define	AR5K_SIMR2_CAB_END	0x02000000	/*         */
#define	AR5K_SIMR2_DTIM_SYNC	0x04000000	/*                        */
#define	AR5K_SIMR2_BCN_TIMEOUT	0x08000000	/*                        */
#define	AR5K_SIMR2_CAB_TIMEOUT	0x10000000	/*                     */
#define	AR5K_SIMR2_DTIM		0x20000000	/*         */
#define	AR5K_SIMR2_TSFOOR	0x80000000	/*             */

#define AR5K_SIMR3		0x00b0			/*                          */
#define AR5K_SIMR3_QCBRORN	0x000003ff	/*                  */
#define AR5K_SIMR3_QCBRORN_S	0
#define AR5K_SIMR3_QCBRURN	0x03ff0000	/*                  */
#define AR5K_SIMR3_QCBRURN_S	16

#define AR5K_SIMR4		0x00b4			/*                          */
#define AR5K_SIMR4_QTRIG	0x000003ff	/*                */
#define AR5K_SIMR4_QTRIG_S	0

/*
                          
              
 */

/*
                                       
 */
#define AR5K_DCM_ADDR		0x0400		/*                                   */
#define AR5K_DCM_DATA		0x0404		/*                        */

/*
                                                    
 */
#define	AR5K_WOW_PCFG			0x0410			/*                  */
#define	AR5K_WOW_PCFG_PAT_MATCH_EN	0x00000001	/*                      */
#define	AR5K_WOW_PCFG_LONG_FRAME_POL	0x00000002	/*                   */
#define	AR5K_WOW_PCFG_WOBMISS		0x00000004	/*                           */
#define	AR5K_WOW_PCFG_PAT_0_EN		0x00000100	/*                  */
#define	AR5K_WOW_PCFG_PAT_1_EN		0x00000200	/*                  */
#define	AR5K_WOW_PCFG_PAT_2_EN		0x00000400	/*                  */
#define	AR5K_WOW_PCFG_PAT_3_EN		0x00000800	/*                  */
#define	AR5K_WOW_PCFG_PAT_4_EN		0x00001000	/*                  */
#define	AR5K_WOW_PCFG_PAT_5_EN		0x00002000	/*                  */

/*
                                                      
 */
#define	AR5K_WOW_PAT_IDX	0x0414

/*
                                                 
 */
#define	AR5K_WOW_PAT_DATA	0x0418			/*                  */
#define	AR5K_WOW_PAT_DATA_0_3_V	0x00000001	/*                    */
#define	AR5K_WOW_PAT_DATA_1_4_V	0x00000100	/*                    */
#define	AR5K_WOW_PAT_DATA_2_5_V	0x00010000	/*                    */
#define	AR5K_WOW_PAT_DATA_0_3_M	0x01000000	/*                   */
#define	AR5K_WOW_PAT_DATA_1_4_M	0x04000000	/*                   */
#define	AR5K_WOW_PAT_DATA_2_5_M	0x10000000	/*                   */

/*
                                                
 */
#define AR5K_DCCFG		0x0420			/*                  */
#define AR5K_DCCFG_GLOBAL_EN	0x00000001	/*                                    */
#define AR5K_DCCFG_BYPASS_EN	0x00000002	/*                      */
#define AR5K_DCCFG_BCAST_EN	0x00000004	/*                                       */
#define AR5K_DCCFG_MCAST_EN	0x00000008	/*                                       */

/*
                                              
 */
#define AR5K_CCFG		0x0600			/*                  */
#define	AR5K_CCFG_WINDOW_SIZE	0x00000007	/*                         */
#define	AR5K_CCFG_CPC_EN	0x00000008	/*                             */

#define AR5K_CCFG_CCU		0x0604			/*                  */
#define AR5K_CCFG_CCU_CUP_EN	0x00000001	/*                    */
#define AR5K_CCFG_CCU_CREDIT	0x00000002	/*                    */
#define AR5K_CCFG_CCU_CD_THRES	0x00000080	/*                                      */
#define AR5K_CCFG_CCU_CUP_LCNT	0x00010000	/*                          */
#define	AR5K_CCFG_CCU_INIT	0x00100200	/*                            */

/*
                                                    
 */
#define AR5K_CPC0		0x0610		/*                                   */
#define AR5K_CPC1		0x0614		/*                                  */
#define AR5K_CPC2		0x0618		/*                                   */
#define AR5K_CPC3		0x061c		/*                                   */
#define AR5K_CPCOVF		0x0620		/*                                  */


/*
                                             
  
                                                             
                                                                  
                                                               
                                                                       
                                                                      
                                                                     
                                                                       
                                                                         
                                                                      
                                                                        
 */

/*
                                     
 */
#define	AR5K_QUEUE_REG(_r, _q)		(((_q) << 2) + _r)
#define AR5K_QCU_GLOBAL_READ(_r, _q)	(AR5K_REG_READ(_r) & (1 << _q))
#define AR5K_QCU_GLOBAL_WRITE(_r, _q)	AR5K_REG_WRITE(_r, (1 << _q))

/*
                                            
 */
#define AR5K_QCU_TXDP_BASE	0x0800		/*                                */
#define AR5K_QUEUE_TXDP(_q)	AR5K_QUEUE_REG(AR5K_QCU_TXDP_BASE, _q)

/*
                               
 */
#define AR5K_QCU_TXE		0x0840
#define AR5K_ENABLE_QUEUE(_q)	AR5K_QCU_GLOBAL_WRITE(AR5K_QCU_TXE, _q)
#define AR5K_QUEUE_ENABLED(_q)	AR5K_QCU_GLOBAL_READ(AR5K_QCU_TXE, _q)

/*
                                
 */
#define AR5K_QCU_TXD		0x0880
#define AR5K_DISABLE_QUEUE(_q)	AR5K_QCU_GLOBAL_WRITE(AR5K_QCU_TXD, _q)
#define AR5K_QUEUE_DISABLED(_q)	AR5K_QCU_GLOBAL_READ(AR5K_QCU_TXD, _q)

/*
                                                
 */
#define	AR5K_QCU_CBRCFG_BASE		0x08c0	/*                                  */
#define	AR5K_QCU_CBRCFG_INTVAL		0x00ffffff	/*                   */
#define AR5K_QCU_CBRCFG_INTVAL_S	0
#define	AR5K_QCU_CBRCFG_ORN_THRES	0xff000000	/*                            */
#define AR5K_QCU_CBRCFG_ORN_THRES_S	24
#define	AR5K_QUEUE_CBRCFG(_q)		AR5K_QUEUE_REG(AR5K_QCU_CBRCFG_BASE, _q)

/*
                                         
 */
#define	AR5K_QCU_RDYTIMECFG_BASE	0x0900	/*                                      */
#define	AR5K_QCU_RDYTIMECFG_INTVAL	0x00ffffff	/*                          */
#define AR5K_QCU_RDYTIMECFG_INTVAL_S	0
#define	AR5K_QCU_RDYTIMECFG_ENABLE	0x01000000	/*                        */
#define AR5K_QUEUE_RDYTIMECFG(_q)	AR5K_QUEUE_REG(AR5K_QCU_RDYTIMECFG_BASE, _q)

/*
                                 
 */
#define	AR5K_QCU_ONESHOTARM_SET		0x0940	/*                                              */
#define	AR5K_QCU_ONESHOTARM_SET_M	0x0000ffff

/*
                                   
 */
#define	AR5K_QCU_ONESHOTARM_CLEAR	0x0980	/*                                                */
#define	AR5K_QCU_ONESHOTARM_CLEAR_M	0x0000ffff

/*
                     
 */
#define AR5K_QCU_MISC_BASE		0x09c0			/*                               */
#define	AR5K_QCU_MISC_FRSHED_M		0x0000000f	/*                       */
#define	AR5K_QCU_MISC_FRSHED_ASAP		0	/*      */
#define	AR5K_QCU_MISC_FRSHED_CBR		1	/*                   */
#define	AR5K_QCU_MISC_FRSHED_DBA_GT		2	/*                        */
#define	AR5K_QCU_MISC_FRSHED_TIM_GT		3	/*            */
#define	AR5K_QCU_MISC_FRSHED_BCN_SENT_GT	4	/*                   */
#define	AR5K_QCU_MISC_ONESHOT_ENABLE	0x00000010	/*                */
#define	AR5K_QCU_MISC_CBREXP_DIS	0x00000020	/*                                            */
#define	AR5K_QCU_MISC_CBREXP_BCN_DIS	0x00000040	/*                                            */
#define	AR5K_QCU_MISC_BCN_ENABLE	0x00000080	/*                   */
#define	AR5K_QCU_MISC_CBR_THRES_ENABLE	0x00000100	/*                               */
#define	AR5K_QCU_MISC_RDY_VEOL_POLICY	0x00000200	/*                                        */
#define	AR5K_QCU_MISC_CBR_RESET_CNT	0x00000400	/*                               */
#define	AR5K_QCU_MISC_DCU_EARLY		0x00000800	/*                       */
#define AR5K_QCU_MISC_DCU_CMP_EN	0x00001000	/*                          */
#define AR5K_QUEUE_MISC(_q)		AR5K_QUEUE_REG(AR5K_QCU_MISC_BASE, _q)


/*
                       
 */
#define AR5K_QCU_STS_BASE	0x0a00			/*                               */
#define	AR5K_QCU_STS_FRMPENDCNT	0x00000003	/*                        */
#define	AR5K_QCU_STS_CBREXPCNT	0x0000ff00	/*                     */
#define	AR5K_QUEUE_STATUS(_q)	AR5K_QUEUE_REG(AR5K_QCU_STS_BASE, _q)

/*
                                   
 */
#define AR5K_QCU_RDYTIMESHDN	0x0a40
#define AR5K_QCU_RDYTIMESHDN_M	0x000003ff

/*
                                                
 */
#define AR5K_QCU_CBB_SELECT	0x0b00
#define AR5K_QCU_CBB_ADDR	0x0b04
#define AR5K_QCU_CBB_ADDR_S	9

/*
                                                        
                
 */
#define AR5K_QCU_CBCFG		0x0b08



/*
                                                             
                    
  
                                                                    
                                                           
                                                                      
                                                                      
                                                                    
                                                                    
                                                                       
                                                                          
                                                          
  
 */

/*
                         
 */
#define AR5K_DCU_QCUMASK_BASE	0x1000		/*                                      */
#define AR5K_DCU_QCUMASK_M	0x000003ff
#define AR5K_QUEUE_QCUMASK(_q)	AR5K_QUEUE_REG(AR5K_DCU_QCUMASK_BASE, _q)

/*
                                                
 */
#define AR5K_DCU_LCL_IFS_BASE		0x1040			/*                                      */
#define	AR5K_DCU_LCL_IFS_CW_MIN	        0x000003ff	/*                           */
#define	AR5K_DCU_LCL_IFS_CW_MIN_S	0
#define	AR5K_DCU_LCL_IFS_CW_MAX	        0x000ffc00	/*                           */
#define	AR5K_DCU_LCL_IFS_CW_MAX_S	10
#define	AR5K_DCU_LCL_IFS_AIFS		0x0ff00000	/*                             */
#define	AR5K_DCU_LCL_IFS_AIFS_S		20
#define	AR5K_DCU_LCL_IFS_AIFS_MAX	0xfc		/*                                           */
#define	AR5K_QUEUE_DFS_LOCAL_IFS(_q)	AR5K_QUEUE_REG(AR5K_DCU_LCL_IFS_BASE, _q)

/*
                            
                                           
 */
#define AR5K_DCU_RETRY_LMT_BASE		0x1080			/*                                        */
#define AR5K_DCU_RETRY_LMT_RTS		0x0000000f	/*                                                                                      */
#define AR5K_DCU_RETRY_LMT_RTS_S	0
#define AR5K_DCU_RETRY_LMT_STA_RTS	0x00003f00	/*                                             */
#define AR5K_DCU_RETRY_LMT_STA_RTS_S	8
#define AR5K_DCU_RETRY_LMT_STA_DATA	0x000fc000	/*                                               */
#define AR5K_DCU_RETRY_LMT_STA_DATA_S	14
#define	AR5K_QUEUE_DFS_RETRY_LIMIT(_q)	AR5K_QUEUE_REG(AR5K_DCU_RETRY_LMT_BASE, _q)

/*
                             
 */
#define AR5K_DCU_CHAN_TIME_BASE		0x10c0			/*                                        */
#define	AR5K_DCU_CHAN_TIME_DUR		0x000fffff	/*                       */
#define	AR5K_DCU_CHAN_TIME_DUR_S	0
#define	AR5K_DCU_CHAN_TIME_ENABLE	0x00100000	/*                     */
#define AR5K_QUEUE_DFS_CHANNEL_TIME(_q)	AR5K_QUEUE_REG(AR5K_DCU_CHAN_TIME_BASE, _q)

/*
                             
  
                                             
                                                                
                                                               
                                                                             
                                                               
                                                                   
                                                        
                                                 
 */
#define AR5K_DCU_MISC_BASE		0x1100			/*                                   */
#define	AR5K_DCU_MISC_BACKOFF		0x0000003f	/*                            */
#define	AR5K_DCU_MISC_ETS_RTS_POL	0x00000040	/*                           
                                     
                        */
#define AR5K_DCU_MISC_ETS_CW_POL	0x00000080	/*                           
                       */
#define	AR5K_DCU_MISC_FRAG_WAIT		0x00000100	/*                        */
#define AR5K_DCU_MISC_BACKOFF_FRAG	0x00000200	/*                               */
#define	AR5K_DCU_MISC_HCFPOLL_ENABLE	0x00000800	/*                  */
#define	AR5K_DCU_MISC_BACKOFF_PERSIST	0x00001000	/*                    */
#define	AR5K_DCU_MISC_FRMPRFTCH_ENABLE	0x00002000	/*                        */
#define	AR5K_DCU_MISC_VIRTCOL		0x0000c000	/*                                */
#define	AR5K_DCU_MISC_VIRTCOL_NORMAL	0
#define	AR5K_DCU_MISC_VIRTCOL_IGNORE	1
#define	AR5K_DCU_MISC_BCN_ENABLE	0x00010000	/*                   */
#define	AR5K_DCU_MISC_ARBLOCK_CTL	0x00060000	/*                              */
#define	AR5K_DCU_MISC_ARBLOCK_CTL_S	17
#define	AR5K_DCU_MISC_ARBLOCK_CTL_NONE		0	/*                    */
#define	AR5K_DCU_MISC_ARBLOCK_CTL_INTFRM	1	/*                     */
#define	AR5K_DCU_MISC_ARBLOCK_CTL_GLOBAL	2	/*                */
#define	AR5K_DCU_MISC_ARBLOCK_IGNORE	0x00080000	/*                        */
#define	AR5K_DCU_MISC_SEQ_NUM_INCR_DIS	0x00100000	/*                                   */
#define	AR5K_DCU_MISC_POST_FR_BKOFF_DIS	0x00200000	/*                            */
#define	AR5K_DCU_MISC_VIRT_COLL_POLICY	0x00400000	/*                             */
#define	AR5K_DCU_MISC_BLOWN_IFS_POLICY	0x00800000	/*                      */
#define	AR5K_DCU_MISC_SEQNUM_CTL	0x01000000	/*                             */
#define AR5K_QUEUE_DFS_MISC(_q)		AR5K_QUEUE_REG(AR5K_DCU_MISC_BASE, _q)

/*
                                      
 */
#define AR5K_DCU_SEQNUM_BASE		0x1140
#define	AR5K_DCU_SEQNUM_M		0x00000fff
#define	AR5K_QUEUE_DCU_SEQNUM(_q)	AR5K_QUEUE_REG(AR5K_DCU_SEQNUM_BASE, _q)

/*
                               
 */
#define AR5K_DCU_GBL_IFS_SIFS	0x1030
#define AR5K_DCU_GBL_IFS_SIFS_M	0x0000ffff

/*
                                        
 */
#define AR5K_DCU_GBL_IFS_SLOT	0x1070
#define AR5K_DCU_GBL_IFS_SLOT_M	0x0000ffff

/*
                               
 */
#define AR5K_DCU_GBL_IFS_EIFS	0x10b0
#define AR5K_DCU_GBL_IFS_EIFS_M	0x0000ffff

/*
                               
  
                                                 
                                             
                    
  
                                                 
                                                         
 */
#define AR5K_DCU_GBL_IFS_MISC			0x10f0			/*                  */
#define	AR5K_DCU_GBL_IFS_MISC_LFSR_SLICE	0x00000007	/*                   */
#define	AR5K_DCU_GBL_IFS_MISC_TURBO_MODE	0x00000008	/*            */
#define	AR5K_DCU_GBL_IFS_MISC_SIFS_DUR_USEC	0x000003f0	/*                    */
#define	AR5K_DCU_GBL_IFS_MISC_SIFS_DUR_USEC_S	4
#define	AR5K_DCU_GBL_IFS_MISC_USEC_DUR		0x000ffc00	/*                    */
#define	AR5K_DCU_GBL_IFS_MISC_USEC_DUR_S	10
#define	AR5K_DCU_GBL_IFS_MISC_DCU_ARB_DELAY	0x00300000	/*                        */
#define AR5K_DCU_GBL_IFS_MISC_SIFS_CNT_RST	0x00400000	/*                           */
#define AR5K_DCU_GBL_IFS_MISC_AIFS_CNT_RST	0x00800000	/*                           */
#define AR5K_DCU_GBL_IFS_MISC_RND_LFSR_SL_DIS	0x01000000	/*                           */

/*
                                      
 */
#define AR5K_DCU_FP			0x1230			/*                  */
#define AR5K_DCU_FP_NOBURST_DCU_EN	0x00000001	/*                                      */
#define AR5K_DCU_FP_NOBURST_EN		0x00000010	/*                               */
#define AR5K_DCU_FP_BURST_DCU_EN	0x00000020	/*                                  */

/*
                                             
 */
#define AR5K_DCU_TXP		0x1270			/*                  */
#define	AR5K_DCU_TXP_M		0x000003ff	/*               */
#define	AR5K_DCU_TXP_STATUS	0x00010000	/*                 */

/*
                                           
                                           
                                                   
 */
#define AR5K_DCU_TX_FILTER_0_BASE	0x1038
#define	AR5K_DCU_TX_FILTER_0(_n)	(AR5K_DCU_TX_FILTER_0_BASE + (_n * 64))

/*
                                           
 */
#define AR5K_DCU_TX_FILTER_1_BASE	0x103c
#define	AR5K_DCU_TX_FILTER_1(_n)	(AR5K_DCU_TX_FILTER_1_BASE + (_n * 64))

/*
                                     
 */
#define AR5K_DCU_TX_FILTER_CLR	0x143c

/*
                                   
 */
#define AR5K_DCU_TX_FILTER_SET	0x147c

/*
                         
 */
#define AR5K_RESET_CTL		0x4000			/*                  */
#define AR5K_RESET_CTL_PCU	0x00000001	/*                             */
#define AR5K_RESET_CTL_DMA	0x00000002	/*                          */
#define	AR5K_RESET_CTL_BASEBAND	0x00000002	/*                        */
#define AR5K_RESET_CTL_MAC	0x00000004	/*                                   */
#define AR5K_RESET_CTL_PHY	0x00000008	/*                  */
#define AR5K_RESET_CTL_PCI	0x00000010	/*                                 */

/*
                         
 */
#define AR5K_SLEEP_CTL			0x4004			/*                  */
#define AR5K_SLEEP_CTL_SLDUR		0x0000ffff	/*                     */
#define AR5K_SLEEP_CTL_SLDUR_S		0
#define AR5K_SLEEP_CTL_SLE		0x00030000	/*                   */
#define AR5K_SLEEP_CTL_SLE_S		16
#define AR5K_SLEEP_CTL_SLE_WAKE		0x00000000	/*                  */
#define AR5K_SLEEP_CTL_SLE_SLP		0x00010000	/*                  */
#define AR5K_SLEEP_CTL_SLE_ALLOW	0x00020000	/*                     */
#define AR5K_SLEEP_CTL_SLE_UNITS	0x00000008	/*         */
#define AR5K_SLEEP_CTL_DUR_TIM_POL	0x00040000	/*                              */
#define AR5K_SLEEP_CTL_DUR_WRITE_POL	0x00080000	/*                             */
#define AR5K_SLEEP_CTL_SLE_POL		0x00100000	/*                   */

/*
                             
 */
#define AR5K_INTPEND	0x4008
#define AR5K_INTPEND_M	0x00000001

/*
                       
 */
#define AR5K_SFR	0x400c
#define AR5K_SFR_EN	0x00000001

/*
                             
                      
 */
#define AR5K_PCICFG			0x4010			/*                  */
#define AR5K_PCICFG_EEAE		0x00000001	/*                             */
#define AR5K_PCICFG_SLEEP_CLOCK_EN	0x00000002	/*                    */
#define AR5K_PCICFG_CLKRUNEN		0x00000004	/*                       */
#define AR5K_PCICFG_EESIZE		0x00000018	/*                              */
#define AR5K_PCICFG_EESIZE_S		3
#define AR5K_PCICFG_EESIZE_4K		0		/*    */
#define AR5K_PCICFG_EESIZE_8K		1		/*    */
#define AR5K_PCICFG_EESIZE_16K		2		/*     */
#define AR5K_PCICFG_EESIZE_FAIL		3		/*                            */
#define AR5K_PCICFG_LED			0x00000060	/*                    */
#define AR5K_PCICFG_LED_NONE		0x00000000	/*                 */
#define AR5K_PCICFG_LED_PEND		0x00000020	/*                     */
#define AR5K_PCICFG_LED_ASSOC		0x00000040	/*            */
#define	AR5K_PCICFG_BUS_SEL		0x00000380	/*                                   */
#define AR5K_PCICFG_CBEFIX_DIS		0x00000400	/*                 */
#define AR5K_PCICFG_SL_INTEN		0x00000800	/*                               */
#define AR5K_PCICFG_LED_BCTL		0x00001000	/*                      */
#define AR5K_PCICFG_RETRY_FIX		0x00001000	/*                           */
#define AR5K_PCICFG_SL_INPEN		0x00002000	/*                                   */
#define AR5K_PCICFG_SPWR_DN		0x00010000	/*                       */
#define AR5K_PCICFG_LEDMODE		0x000e0000	/*                 */
#define AR5K_PCICFG_LEDMODE_PROP	0x00000000	/*                                   */
#define AR5K_PCICFG_LEDMODE_PROM	0x00020000	/*                                             */
#define AR5K_PCICFG_LEDMODE_PWR		0x00040000	/*                                       */
#define AR5K_PCICFG_LEDMODE_RAND	0x00060000	/*                             */
#define AR5K_PCICFG_LEDBLINK		0x00700000	/*                */
#define AR5K_PCICFG_LEDBLINK_S		20
#define AR5K_PCICFG_LEDSLOW		0x00800000	/*                                */
#define AR5K_PCICFG_LEDSTATE				\
	(AR5K_PCICFG_LED | AR5K_PCICFG_LEDMODE |	\
	AR5K_PCICFG_LEDBLINK | AR5K_PCICFG_LEDSLOW)
#define	AR5K_PCICFG_SLEEP_CLOCK_RATE	0x03000000	/*                  */
#define	AR5K_PCICFG_SLEEP_CLOCK_RATE_S	24

/*
                                                         
  
                                                        
                                       
  
                                                         
                         
                                                         
                                                         
                          
  
                                                 
                                         
                                                            
 */
#define AR5K_NUM_GPIO	6

#define AR5K_GPIOCR		0x4014				/*                  */
#define AR5K_GPIOCR_INT_ENA	0x00008000		/*                       */
#define AR5K_GPIOCR_INT_SELL	0x00000000		/*                                    */
#define AR5K_GPIOCR_INT_SELH	0x00010000		/*                                     */
#define AR5K_GPIOCR_IN(n)	(0 << ((n) * 2))	/*                  */
#define AR5K_GPIOCR_OUT0(n)	(1 << ((n) * 2))	/*                  */
#define AR5K_GPIOCR_OUT1(n)	(2 << ((n) * 2))	/*                  */
#define AR5K_GPIOCR_OUT(n)	(3 << ((n) * 2))	/*                  */
#define AR5K_GPIOCR_INT_SEL(n)	((n) << 12)		/*                          */

/*
                                                             
 */
#define AR5K_GPIODO	0x4018

/*
                                                            
 */
#define AR5K_GPIODI	0x401c
#define AR5K_GPIODI_M	0x0000002f

/*
                            
 */
#define AR5K_SREV		0x4020			/*                  */
#define AR5K_SREV_REV		0x0000000f	/*                   */
#define AR5K_SREV_REV_S		0
#define AR5K_SREV_VER		0x000000ff	/*                  */
#define AR5K_SREV_VER_S		4

/*
                             
 */
#define	AR5K_TXEPOST	0x4028

/*
                 
 */
#define	AR5K_QCU_SLEEP_MASK	0x402c

/*                                           
                                                 
                                  */

/*
                                   
                                   
 */
#define AR5K_5414_CBCFG		0x4068
#define AR5K_5414_CBCFG_BUF_DIS	0x10	/*                */

/*
                                       
                              
 */
#define	AR5K_PCIE_PM_CTL		0x4068			/*                  */
/*           */
#define	AR5K_PCIE_PM_CTL_L1_WHEN_D2	0x00000001	/*                          
                                    */
#define	AR5K_PCIE_PM_CTL_L0_L0S_CLEAR	0x00000002	/*                           */
#define	AR5K_PCIE_PM_CTL_L0_L0S_EN	0x00000004	/*                          */
#define	AR5K_PCIE_PM_CTL_LDRESET_EN	0x00000008	/*                            
            */
/*                  */
#define	AR5K_PCIE_PM_CTL_PME_EN		0x00000010	/*            */
#define	AR5K_PCIE_PM_CTL_AUX_PWR_DET	0x00000020	/*                  */
#define	AR5K_PCIE_PM_CTL_PME_CLEAR	0x00000040	/*           */
#define	AR5K_PCIE_PM_CTL_PSM_D0		0x00000080
#define	AR5K_PCIE_PM_CTL_PSM_D1		0x00000100
#define	AR5K_PCIE_PM_CTL_PSM_D2		0x00000200
#define	AR5K_PCIE_PM_CTL_PSM_D3		0x00000400

/*
                                   
 */
#define	AR5K_PCIE_WAEN	0x407c

/*
                                
            
 */
#define	AR5K_PCIE_SERDES	0x4080
#define	AR5K_PCIE_SERDES_RESET	0x4084

/*                        */

/*
                          
  
                                                
                                               
                                              
                                             
                         
  
                                             
                                                 
                                             
                                          
                                        
  
                                          
                                                       
                                          
                                        
  
                                              
                                                 
                                                      
                                          
                                                        
                                          
                                     
                                                   
                                          
  
                                                      
                                             
                                                                
  
 */
#define AR5K_EEPROM_BASE	0x6000

/*
                       
 */
#define AR5K_EEPROM_DATA_5211	0x6004
#define AR5K_EEPROM_DATA_5210	0x6800
#define	AR5K_EEPROM_DATA	(ah->ah_version == AR5K_AR5210 ? \
				AR5K_EEPROM_DATA_5210 : AR5K_EEPROM_DATA_5211)

/*
                          
 */
#define AR5K_EEPROM_CMD		0x6008			/*                  */
#define AR5K_EEPROM_CMD_READ	0x00000001	/*             */
#define AR5K_EEPROM_CMD_WRITE	0x00000002	/*              */
#define AR5K_EEPROM_CMD_RESET	0x00000004	/*              */

/*
                         
 */
#define AR5K_EEPROM_STAT_5210	0x6c00			/*                         */
#define AR5K_EEPROM_STAT_5211	0x600c			/*                          */
#define	AR5K_EEPROM_STATUS	(ah->ah_version == AR5K_AR5210 ? \
				AR5K_EEPROM_STAT_5210 : AR5K_EEPROM_STAT_5211)
#define AR5K_EEPROM_STAT_RDERR	0x00000001	/*                    */
#define AR5K_EEPROM_STAT_RDDONE	0x00000002	/*                        */
#define AR5K_EEPROM_STAT_WRERR	0x00000004	/*                     */
#define AR5K_EEPROM_STAT_WRDONE	0x00000008	/*                         */

/*
                         
 */
#define AR5K_EEPROM_CFG			0x6010			/*                  */
#define AR5K_EEPROM_CFG_SIZE		0x00000003		/*                             */
#define AR5K_EEPROM_CFG_SIZE_AUTO	0
#define AR5K_EEPROM_CFG_SIZE_4KBIT	1
#define AR5K_EEPROM_CFG_SIZE_8KBIT	2
#define AR5K_EEPROM_CFG_SIZE_16KBIT	3
#define AR5K_EEPROM_CFG_WR_WAIT_DIS	0x00000004	/*                    */
#define AR5K_EEPROM_CFG_CLK_RATE	0x00000018	/*            */
#define AR5K_EEPROM_CFG_CLK_RATE_S		3
#define AR5K_EEPROM_CFG_CLK_RATE_156KHZ	0
#define AR5K_EEPROM_CFG_CLK_RATE_312KHZ	1
#define AR5K_EEPROM_CFG_CLK_RATE_625KHZ	2
#define AR5K_EEPROM_CFG_PROT_KEY	0x00ffff00      /*                */
#define AR5K_EEPROM_CFG_PROT_KEY_S	8
#define AR5K_EEPROM_CFG_LIND_EN		0x01000000	/*                             */


/*
                                   
                        
 */

/*
                                        
 */
/*
                                            
                                        
 */
#define AR5K_PCU_MIN	0x8000
#define AR5K_PCU_MAX	0x8fff

/*
                                                           
 */
#define AR5K_STA_ID0		0x8000
#define	AR5K_STA_ID0_ARRD_L32	0xffffffff

/*
                                                                           
 */
#define AR5K_STA_ID1			0x8004			/*                  */
#define	AR5K_STA_ID1_ADDR_U16		0x0000ffff	/*                              */
#define AR5K_STA_ID1_AP			0x00010000	/*             */
#define AR5K_STA_ID1_ADHOC		0x00020000	/*                 */
#define AR5K_STA_ID1_PWR_SV		0x00040000	/*                      */
#define AR5K_STA_ID1_NO_KEYSRCH		0x00080000	/*               */
#define AR5K_STA_ID1_NO_PSPOLL		0x00100000	/*                              */
#define AR5K_STA_ID1_PCF_5211		0x00100000	/*                       */
#define AR5K_STA_ID1_PCF_5210		0x00200000	/*                     */
#define	AR5K_STA_ID1_PCF		(ah->ah_version == AR5K_AR5210 ? \
					AR5K_STA_ID1_PCF_5210 : AR5K_STA_ID1_PCF_5211)
#define AR5K_STA_ID1_DEFAULT_ANTENNA	0x00200000	/*                     */
#define AR5K_STA_ID1_DESC_ANTENNA	0x00400000	/*                                */
#define AR5K_STA_ID1_RTS_DEF_ANTENNA	0x00800000	/*                             */
#define AR5K_STA_ID1_ACKCTS_6MB		0x01000000	/*                                                                                   */
#define AR5K_STA_ID1_BASE_RATE_11B	0x02000000	/*                                                                     */
#define AR5K_STA_ID1_SELFGEN_DEF_ANT	0x04000000	/*                                            */
#define AR5K_STA_ID1_CRYPT_MIC_EN	0x08000000	/*            */
#define AR5K_STA_ID1_KEYSRCH_MODE	0x10000000	/*                              */
#define AR5K_STA_ID1_PRESERVE_SEQ_NUM	0x20000000	/*                          */
#define AR5K_STA_ID1_CBCIV_ENDIAN	0x40000000	/*     */
#define AR5K_STA_ID1_KEYSRCH_MCAST	0x80000000	/*                                      */

#define	AR5K_STA_ID1_ANTENNA_SETTINGS	(AR5K_STA_ID1_DEFAULT_ANTENNA | \
					AR5K_STA_ID1_DESC_ANTENNA | \
					AR5K_STA_ID1_RTS_DEF_ANTENNA | \
					AR5K_STA_ID1_SELFGEN_DEF_ANT)

/*
                                                   
 */
#define AR5K_BSS_ID0	0x8008

/*
                                                       
  
                      
 */
#define AR5K_BSS_ID1		0x800c
#define AR5K_BSS_ID1_AID	0xffff0000
#define AR5K_BSS_ID1_AID_S	16

/*
                             
 */
#define AR5K_SLOT_TIME	0x8010

/*
                           
 */
#define AR5K_TIME_OUT		0x8014			/*                  */
#define AR5K_TIME_OUT_ACK	0x00001fff	/*                  */
#define AR5K_TIME_OUT_ACK_S	0
#define AR5K_TIME_OUT_CTS	0x1fff0000	/*                  */
#define AR5K_TIME_OUT_CTS_S	16

/*
                          
 */
#define AR5K_RSSI_THR			0x8018		/*                  */
#define AR5K_RSSI_THR_M			0x000000ff	/*                                 */
#define AR5K_RSSI_THR_BMISS_5210	0x00000700	/*                                         */
#define AR5K_RSSI_THR_BMISS_5210_S	8
#define AR5K_RSSI_THR_BMISS_5211	0x0000ff00	/*                                          */
#define AR5K_RSSI_THR_BMISS_5211_S	8
#define	AR5K_RSSI_THR_BMISS		(ah->ah_version == AR5K_AR5210 ? \
					AR5K_RSSI_THR_BMISS_5210 : AR5K_RSSI_THR_BMISS_5211)
#define	AR5K_RSSI_THR_BMISS_S		8

/*
                                                          
                                                          
                                                            
                                                              
                                                       
 */

/*
                       
  
                                                                 
 */
#define AR5K_NODCU_RETRY_LMT		0x801c			/*                  */
#define AR5K_NODCU_RETRY_LMT_SH_RETRY	0x0000000f	/*                        */
#define AR5K_NODCU_RETRY_LMT_SH_RETRY_S	0
#define AR5K_NODCU_RETRY_LMT_LG_RETRY	0x000000f0	/*                 */
#define AR5K_NODCU_RETRY_LMT_LG_RETRY_S	4
#define AR5K_NODCU_RETRY_LMT_SSH_RETRY	0x00003f00	/*                                */
#define AR5K_NODCU_RETRY_LMT_SSH_RETRY_S	8
#define AR5K_NODCU_RETRY_LMT_SLG_RETRY	0x000fc000	/*                               */
#define AR5K_NODCU_RETRY_LMT_SLG_RETRY_S	14
#define AR5K_NODCU_RETRY_LMT_CW_MIN	0x3ff00000	/*                                */
#define AR5K_NODCU_RETRY_LMT_CW_MIN_S	20

/*
                            
 */
#define AR5K_USEC_5210			0x8020			/*                         */
#define AR5K_USEC_5211			0x801c			/*                          */
#define AR5K_USEC			(ah->ah_version == AR5K_AR5210 ? \
					AR5K_USEC_5210 : AR5K_USEC_5211)
#define AR5K_USEC_1			0x0000007f	/*                      */
#define AR5K_USEC_1_S			0
#define AR5K_USEC_32			0x00003f80	/*                                           */
#define AR5K_USEC_32_S			7
#define AR5K_USEC_TX_LATENCY_5211	0x007fc000
#define AR5K_USEC_TX_LATENCY_5211_S	14
#define AR5K_USEC_RX_LATENCY_5211	0x1f800000
#define AR5K_USEC_RX_LATENCY_5211_S	23
#define AR5K_USEC_TX_LATENCY_5210	0x000fc000	/*               */
#define AR5K_USEC_TX_LATENCY_5210_S	14
#define AR5K_USEC_RX_LATENCY_5210	0x03f00000	/*               */
#define AR5K_USEC_RX_LATENCY_5210_S	20

/*
                              
 */
#define AR5K_BEACON_5210	0x8024			/*                        */
#define AR5K_BEACON_5211	0x8020			/*                         */
#define AR5K_BEACON		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_BEACON_5210 : AR5K_BEACON_5211)
#define AR5K_BEACON_PERIOD	0x0000ffff	/*                        */
#define AR5K_BEACON_PERIOD_S	0
#define AR5K_BEACON_TIM		0x007f0000	/*                     */
#define AR5K_BEACON_TIM_S	16
#define AR5K_BEACON_ENABLE	0x00800000	/*                */
#define AR5K_BEACON_RESET_TSF	0x01000000	/*                 */

/*
                      
 */
#define AR5K_CFP_PERIOD_5210	0x8028
#define AR5K_CFP_PERIOD_5211	0x8024
#define AR5K_CFP_PERIOD		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_CFP_PERIOD_5210 : AR5K_CFP_PERIOD_5211)

/*
                            
 */
#define AR5K_TIMER0_5210	0x802c
#define AR5K_TIMER0_5211	0x8028
#define AR5K_TIMER0		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_TIMER0_5210 : AR5K_TIMER0_5211)

/*
                                 
 */
#define AR5K_TIMER1_5210	0x8030
#define AR5K_TIMER1_5211	0x802c
#define AR5K_TIMER1		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_TIMER1_5210 : AR5K_TIMER1_5211)

/*
                                      
 */
#define AR5K_TIMER2_5210	0x8034
#define AR5K_TIMER2_5211	0x8030
#define AR5K_TIMER2		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_TIMER2_5210 : AR5K_TIMER2_5211)

/*
                                 
 */
#define AR5K_TIMER3_5210	0x8038
#define AR5K_TIMER3_5211	0x8034
#define AR5K_TIMER3		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_TIMER3_5210 : AR5K_TIMER3_5211)


/*
                                                
 */
#define AR5K_IFS0		0x8040
#define AR5K_IFS0_SIFS		0x000007ff
#define AR5K_IFS0_SIFS_S	0
#define AR5K_IFS0_DIFS		0x007ff800
#define AR5K_IFS0_DIFS_S	11

/*
                                                 
 */
#define AR5K_IFS1		0x8044
#define AR5K_IFS1_PIFS		0x00000fff
#define AR5K_IFS1_PIFS_S	0
#define AR5K_IFS1_EIFS		0x03fff000
#define AR5K_IFS1_EIFS_S	12
#define AR5K_IFS1_CS_EN		0x04000000
#define AR5K_IFS1_CS_EN_S	26

/*
                        
 */
#define AR5K_CFP_DUR_5210	0x8048
#define AR5K_CFP_DUR_5211	0x8038
#define AR5K_CFP_DUR		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_CFP_DUR_5210 : AR5K_CFP_DUR_5211)

/*
                          
 */
#define AR5K_RX_FILTER_5210	0x804c			/*                         */
#define AR5K_RX_FILTER_5211	0x803c			/*                          */
#define AR5K_RX_FILTER		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_RX_FILTER_5210 : AR5K_RX_FILTER_5211)
#define	AR5K_RX_FILTER_UCAST	0x00000001	/*                             */
#define	AR5K_RX_FILTER_MCAST	0x00000002	/*                               */
#define	AR5K_RX_FILTER_BCAST	0x00000004	/*                               */
#define	AR5K_RX_FILTER_CONTROL	0x00000008	/*                             */
#define	AR5K_RX_FILTER_BEACON	0x00000010	/*                            */
#define	AR5K_RX_FILTER_PROM	0x00000020	/*                      */
#define	AR5K_RX_FILTER_XRPOLL	0x00000040	/*                                    */
#define	AR5K_RX_FILTER_PROBEREQ 0x00000080	/*                                     */
#define	AR5K_RX_FILTER_PHYERR_5212	0x00000100	/*                                 */
#define	AR5K_RX_FILTER_RADARERR_5212	0x00000200	/*                                       */
#define AR5K_RX_FILTER_PHYERR_5211	0x00000040	/*        */
#define AR5K_RX_FILTER_RADARERR_5211	0x00000080	/*        */
#define AR5K_RX_FILTER_PHYERR  \
	((ah->ah_version == AR5K_AR5211 ? \
	AR5K_RX_FILTER_PHYERR_5211 : AR5K_RX_FILTER_PHYERR_5212))
#define        AR5K_RX_FILTER_RADARERR \
	((ah->ah_version == AR5K_AR5211 ? \
	AR5K_RX_FILTER_RADARERR_5211 : AR5K_RX_FILTER_RADARERR_5212))

/*
                                            
 */
#define AR5K_MCAST_FILTER0_5210	0x8050
#define AR5K_MCAST_FILTER0_5211	0x8040
#define AR5K_MCAST_FILTER0	(ah->ah_version == AR5K_AR5210 ? \
				AR5K_MCAST_FILTER0_5210 : AR5K_MCAST_FILTER0_5211)

/*
                                             
 */
#define AR5K_MCAST_FILTER1_5210	0x8054
#define AR5K_MCAST_FILTER1_5211	0x8044
#define AR5K_MCAST_FILTER1	(ah->ah_version == AR5K_AR5210 ? \
				AR5K_MCAST_FILTER1_5210 : AR5K_MCAST_FILTER1_5211)


/*
                                                
 */
#define AR5K_TX_MASK0	0x8058

/*
                                                 
 */
#define AR5K_TX_MASK1	0x805c

/*
                             
 */
#define AR5K_CLR_TMASK	0x8060

/*
                                                      
 */
#define AR5K_TRIG_LVL	0x8064


/*
                          
  
                                 
 */
#define AR5K_DIAG_SW_5210		0x8068			/*                         */
#define AR5K_DIAG_SW_5211		0x8048			/*                          */
#define AR5K_DIAG_SW			(ah->ah_version == AR5K_AR5210 ? \
					AR5K_DIAG_SW_5210 : AR5K_DIAG_SW_5211)
#define AR5K_DIAG_SW_DIS_WEP_ACK	0x00000001	/*                                    */
#define AR5K_DIAG_SW_DIS_ACK		0x00000002	/*              */
#define AR5K_DIAG_SW_DIS_CTS		0x00000004	/*              */
#define AR5K_DIAG_SW_DIS_ENC		0x00000008	/*                       */
#define AR5K_DIAG_SW_DIS_DEC		0x00000010	/*                       */
#define AR5K_DIAG_SW_DIS_TX_5210	0x00000020	/*                         */
#define AR5K_DIAG_SW_DIS_RX_5210	0x00000040	/*                 */
#define AR5K_DIAG_SW_DIS_RX_5211	0x00000020
#define	AR5K_DIAG_SW_DIS_RX		(ah->ah_version == AR5K_AR5210 ? \
					AR5K_DIAG_SW_DIS_RX_5210 : AR5K_DIAG_SW_DIS_RX_5211)
#define AR5K_DIAG_SW_LOOP_BACK_5210	0x00000080	/*                                                       */
#define AR5K_DIAG_SW_LOOP_BACK_5211	0x00000040
#define AR5K_DIAG_SW_LOOP_BACK		(ah->ah_version == AR5K_AR5210 ? \
					AR5K_DIAG_SW_LOOP_BACK_5210 : AR5K_DIAG_SW_LOOP_BACK_5211)
#define AR5K_DIAG_SW_CORR_FCS_5210	0x00000100	/*                         */
#define AR5K_DIAG_SW_CORR_FCS_5211	0x00000080
#define AR5K_DIAG_SW_CORR_FCS		(ah->ah_version == AR5K_AR5210 ? \
					AR5K_DIAG_SW_CORR_FCS_5210 : AR5K_DIAG_SW_CORR_FCS_5211)
#define AR5K_DIAG_SW_CHAN_INFO_5210	0x00000200	/*                                                                     */
#define AR5K_DIAG_SW_CHAN_INFO_5211	0x00000100
#define AR5K_DIAG_SW_CHAN_INFO		(ah->ah_version == AR5K_AR5210 ? \
					AR5K_DIAG_SW_CHAN_INFO_5210 : AR5K_DIAG_SW_CHAN_INFO_5211)
#define AR5K_DIAG_SW_EN_SCRAM_SEED_5210	0x00000400	/*                             */
#define AR5K_DIAG_SW_EN_SCRAM_SEED_5211	0x00000200
#define AR5K_DIAG_SW_EN_SCRAM_SEED	(ah->ah_version == AR5K_AR5210 ? \
					AR5K_DIAG_SW_EN_SCRAM_SEED_5210 : AR5K_DIAG_SW_EN_SCRAM_SEED_5211)
#define AR5K_DIAG_SW_ECO_ENABLE		0x00000400	/*         */
#define AR5K_DIAG_SW_SCVRAM_SEED	0x0003f800	/*        */
#define AR5K_DIAG_SW_SCRAM_SEED_M	0x0001fc00	/*                     */
#define AR5K_DIAG_SW_SCRAM_SEED_S	10
#define AR5K_DIAG_SW_DIS_SEQ_INC_5210	0x00040000	/*                                    */
#define AR5K_DIAG_SW_FRAME_NV0_5210	0x00080000
#define AR5K_DIAG_SW_FRAME_NV0_5211	0x00020000	/*                                           */
#define	AR5K_DIAG_SW_FRAME_NV0		(ah->ah_version == AR5K_AR5210 ? \
					AR5K_DIAG_SW_FRAME_NV0_5210 : AR5K_DIAG_SW_FRAME_NV0_5211)
#define AR5K_DIAG_SW_OBSPT_M		0x000c0000	/*                              */
#define AR5K_DIAG_SW_OBSPT_S		18
#define AR5K_DIAG_SW_RX_CLEAR_HIGH	0x00100000	/*                      */
#define AR5K_DIAG_SW_IGNORE_CARR_SENSE	0x00200000	/*                              */
#define AR5K_DIAG_SW_CHANNEL_IDLE_HIGH	0x00400000	/*                         */
#define AR5K_DIAG_SW_PHEAR_ME		0x00800000	/*     */

/*
                                       
 */
#define AR5K_TSF_L32_5210	0x806c
#define AR5K_TSF_L32_5211	0x804c
#define	AR5K_TSF_L32		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_TSF_L32_5210 : AR5K_TSF_L32_5211)

/*
                                        
 */
#define AR5K_TSF_U32_5210	0x8070
#define AR5K_TSF_U32_5211	0x8050
#define	AR5K_TSF_U32		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_TSF_U32_5210 : AR5K_TSF_U32_5211)

/*
                                             
 */
#define AR5K_LAST_TSTP	0x8080

/*
                              
 */
#define AR5K_ADDAC_TEST			0x8054			/*                  */
#define AR5K_ADDAC_TEST_TXCONT		0x00000001	/*                    */
#define AR5K_ADDAC_TEST_TST_MODE	0x00000002	/*           */
#define AR5K_ADDAC_TEST_LOOP_EN		0x00000004	/*             */
#define AR5K_ADDAC_TEST_LOOP_LEN	0x00000008	/*                     */
#define AR5K_ADDAC_TEST_USE_U8		0x00004000	/*                  */
#define AR5K_ADDAC_TEST_MSB		0x00008000	/*              */
#define AR5K_ADDAC_TEST_TRIG_SEL	0x00010000	/*                */
#define AR5K_ADDAC_TEST_TRIG_PTY	0x00020000	/*                  */
#define AR5K_ADDAC_TEST_RXCONT		0x00040000	/*                    */
#define AR5K_ADDAC_TEST_CAPTURE		0x00080000	/*               */
#define AR5K_ADDAC_TEST_TST_ARM		0x00100000	/*                           */

/*
                                   
 */
#define AR5K_DEFAULT_ANTENNA	0x8058

/*
                                              
                
 */
#define AR5K_FRAME_CTL_QOSM	0x805c

/*
                                
 */
#define AR5K_SEQ_MASK	0x8060

/*
                              
 */
#define AR5K_RETRY_CNT		0x8084			/*                         */
#define AR5K_RETRY_CNT_SSH	0x0000003f	/*                               */
#define AR5K_RETRY_CNT_SLG	0x00000fc0	/*                              */

/*
                                  
 */
#define AR5K_BACKOFF		0x8088			/*                         */
#define AR5K_BACKOFF_CW		0x000003ff	/*                               */
#define AR5K_BACKOFF_CNT	0x03ff0000	/*                   */



/*
                         
 */
#define AR5K_NAV_5210		0x808c
#define AR5K_NAV_5211		0x8084
#define	AR5K_NAV		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_NAV_5210 : AR5K_NAV_5211)

/*
                
  
                                                                  
                                                                
 */

/*
                            
 */
#define AR5K_RTS_OK_5210	0x8090
#define AR5K_RTS_OK_5211	0x8088
#define	AR5K_RTS_OK		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_RTS_OK_5210 : AR5K_RTS_OK_5211)

/*
                            
 */
#define AR5K_RTS_FAIL_5210	0x8094
#define AR5K_RTS_FAIL_5211	0x808c
#define	AR5K_RTS_FAIL		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_RTS_FAIL_5210 : AR5K_RTS_FAIL_5211)

/*
                            
 */
#define AR5K_ACK_FAIL_5210	0x8098
#define AR5K_ACK_FAIL_5211	0x8090
#define	AR5K_ACK_FAIL		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_ACK_FAIL_5210 : AR5K_ACK_FAIL_5211)

/*
                            
 */
#define AR5K_FCS_FAIL_5210	0x809c
#define AR5K_FCS_FAIL_5211	0x8094
#define	AR5K_FCS_FAIL		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_FCS_FAIL_5210 : AR5K_FCS_FAIL_5211)

/*
                        
 */
#define AR5K_BEACON_CNT_5210	0x80a0
#define AR5K_BEACON_CNT_5211	0x8098
#define	AR5K_BEACON_CNT		(ah->ah_version == AR5K_AR5210 ? \
				AR5K_BEACON_CNT_5210 : AR5K_BEACON_CNT_5211)


/*                                 */

/*
                                  
 */
#define AR5K_TPC			0x80e8
#define AR5K_TPC_ACK			0x0000003f	/*            */
#define AR5K_TPC_ACK_S			0
#define AR5K_TPC_CTS			0x00003f00	/*            */
#define AR5K_TPC_CTS_S			8
#define AR5K_TPC_CHIRP			0x003f0000	/*              */
#define AR5K_TPC_CHIRP_S		16
#define AR5K_TPC_DOPPLER		0x0f000000	/*                    */
#define AR5K_TPC_DOPPLER_S		24

/*
                                    
 */
#define AR5K_XRMODE			0x80c0			/*                  */
#define	AR5K_XRMODE_POLL_TYPE_M		0x0000003f	/*                        */
#define	AR5K_XRMODE_POLL_TYPE_S		0
#define	AR5K_XRMODE_POLL_SUBTYPE_M	0x0000003c	/*                           */
#define	AR5K_XRMODE_POLL_SUBTYPE_S	2
#define	AR5K_XRMODE_POLL_WAIT_ALL	0x00000080	/*               */
#define	AR5K_XRMODE_SIFS_DELAY		0x000fff00	/*                     */
#define	AR5K_XRMODE_FRAME_HOLD_M	0xfff00000	/*                         */
#define	AR5K_XRMODE_FRAME_HOLD_S	20

/*
                    
 */
#define AR5K_XRDELAY			0x80c4			/*                  */
#define AR5K_XRDELAY_SLOT_DELAY_M	0x0000ffff	/*                     */
#define AR5K_XRDELAY_SLOT_DELAY_S	0
#define AR5K_XRDELAY_CHIRP_DELAY_M	0xffff0000	/*                           */
#define AR5K_XRDELAY_CHIRP_DELAY_S	16

/*
                      
 */
#define AR5K_XRTIMEOUT			0x80c8			/*                  */
#define AR5K_XRTIMEOUT_CHIRP_M		0x0000ffff	/*                        */
#define AR5K_XRTIMEOUT_CHIRP_S		0
#define AR5K_XRTIMEOUT_POLL_M		0xffff0000	/*                       */
#define AR5K_XRTIMEOUT_POLL_S		16

/*
                    
 */
#define AR5K_XRCHIRP			0x80cc			/*                  */
#define AR5K_XRCHIRP_SEND		0x00000001	/*            */
#define AR5K_XRCHIRP_GAP		0xffff0000	/*                        */

/*
                    
 */
#define AR5K_XRSTOMP			0x80d0			/*                  */
#define AR5K_XRSTOMP_TX			0x00000001	/*              */
#define AR5K_XRSTOMP_RX			0x00000002	/*              */
#define AR5K_XRSTOMP_TX_RSSI		0x00000004	/*                   */
#define AR5K_XRSTOMP_TX_BSSID		0x00000008	/*                    */
#define AR5K_XRSTOMP_DATA		0x00000010	/*               */
#define AR5K_XRSTOMP_RSSI_THRES		0x0000ff00	/*                            */

/*
                                
 */
#define AR5K_SLEEP0			0x80d4			/*                  */
#define AR5K_SLEEP0_NEXT_DTIM		0x0007ffff	/*                        */
#define AR5K_SLEEP0_NEXT_DTIM_S		0
#define AR5K_SLEEP0_ASSUME_DTIM		0x00080000	/*             */
#define AR5K_SLEEP0_ENH_SLEEP_EN	0x00100000	/*                               */
#define AR5K_SLEEP0_CABTO		0xff000000	/*                       */
#define AR5K_SLEEP0_CABTO_S		24

/*
                                 
 */
#define AR5K_SLEEP1			0x80d8			/*                  */
#define AR5K_SLEEP1_NEXT_TIM		0x0007ffff	/*                       */
#define AR5K_SLEEP1_NEXT_TIM_S		0
#define AR5K_SLEEP1_BEACON_TO		0xff000000	/*                          */
#define AR5K_SLEEP1_BEACON_TO_S		24

/*
                                
 */
#define AR5K_SLEEP2			0x80dc			/*                  */
#define AR5K_SLEEP2_TIM_PER		0x0000ffff	/*                         */
#define AR5K_SLEEP2_TIM_PER_S		0
#define AR5K_SLEEP2_DTIM_PER		0xffff0000	/*                          */
#define AR5K_SLEEP2_DTIM_PER_S		16

/*
                                  
  
                                     
  
 */
#define AR5K_TXPC			0x80e8			/*                  */
#define AR5K_TXPC_ACK_M			0x0000003f	/*              */
#define AR5K_TXPC_ACK_S			0
#define AR5K_TXPC_CTS_M			0x00003f00	/*              */
#define AR5K_TXPC_CTS_S			8
#define AR5K_TXPC_CHIRP_M		0x003f0000	/*                */
#define AR5K_TXPC_CHIRP_S		16
#define AR5K_TXPC_DOPPLER		0x0f000000	/*                        */
#define AR5K_TXPC_DOPPLER_S		24

/*
                          
  
                                                                             
                            
                                                                            
                                                                               
                                                                         
 */
#define AR5K_PROFCNT_TX			0x80ec	/*          */
#define AR5K_PROFCNT_RX			0x80f0	/*          */
#define AR5K_PROFCNT_RXCLR		0x80f4	/*            */
#define AR5K_PROFCNT_CYCLE		0x80f8	/*               */

/*
                                 
 */
#define AR5K_QUIET_CTL1			0x80fc			/*                  */
#define AR5K_QUIET_CTL1_NEXT_QT_TSF	0x0000ffff	/*                            */
#define AR5K_QUIET_CTL1_NEXT_QT_TSF_S	0
#define AR5K_QUIET_CTL1_QT_EN		0x00010000	/*                     */
#define AR5K_QUIET_CTL1_ACK_CTS_EN	0x00020000	/*                                  */

#define AR5K_QUIET_CTL2			0x8100			/*                  */
#define AR5K_QUIET_CTL2_QT_PER		0x0000ffff	/*                                   */
#define AR5K_QUIET_CTL2_QT_PER_S	0
#define AR5K_QUIET_CTL2_QT_DUR		0xffff0000	/*                                */
#define AR5K_QUIET_CTL2_QT_DUR_S	16

/*
                         
 */
#define AR5K_TSF_PARM			0x8104			/*                  */
#define AR5K_TSF_PARM_INC		0x000000ff	/*                        */
#define AR5K_TSF_PARM_INC_S		0

/*
                   
 */
#define AR5K_QOS_NOACK			0x8108			/*                  */
#define AR5K_QOS_NOACK_2BIT_VALUES	0x0000000f	/*     */
#define AR5K_QOS_NOACK_2BIT_VALUES_S	0
#define AR5K_QOS_NOACK_BIT_OFFSET	0x00000070	/*     */
#define AR5K_QOS_NOACK_BIT_OFFSET_S	4
#define AR5K_QOS_NOACK_BYTE_OFFSET	0x00000180	/*     */
#define AR5K_QOS_NOACK_BYTE_OFFSET_S	7

/*
                            
 */
#define AR5K_PHY_ERR_FIL		0x810c
#define AR5K_PHY_ERR_FIL_RADAR		0x00000020	/*              */
#define AR5K_PHY_ERR_FIL_OFDM		0x00020000	/*                         */
#define AR5K_PHY_ERR_FIL_CCK		0x02000000	/*                        */

/*
                      
 */
#define AR5K_XRLAT_TX		0x8110

/*
                    
 */
#define AR5K_ACKSIFS		0x8114			/*                  */
#define AR5K_ACKSIFS_INC	0x00000000	/*                            */

/*
                               
 */
#define	AR5K_MIC_QOS_CTL		0x8118			/*                  */
#define	AR5K_MIC_QOS_CTL_OFF(_n)	(1 << (_n * 2))
#define	AR5K_MIC_QOS_CTL_MQ_EN		0x00010000	/*                */

/*
                              
 */
#define	AR5K_MIC_QOS_SEL		0x811c
#define	AR5K_MIC_QOS_SEL_OFF(_n)	(1 << (_n * 4))

/*
                                 
 */
#define	AR5K_MISC_MODE			0x8120			/*                  */
#define	AR5K_MISC_MODE_FBSSID_MATCH	0x00000001	/*                   */
#define	AR5K_MISC_MODE_ACKSIFS_MEM	0x00000002	/*                     */
#define	AR5K_MISC_MODE_COMBINED_MIC	0x00000004	/*                   */
/*           */

/*
                      
 */
#define	AR5K_OFDM_FIL_CNT		0x8124

/*
                     
 */
#define	AR5K_CCK_FIL_CNT		0x8128

/*
                                                      
 */
#define	AR5K_PHYERR_CNT1		0x812c
#define	AR5K_PHYERR_CNT1_MASK		0x8130

#define	AR5K_PHYERR_CNT2		0x8134
#define	AR5K_PHYERR_CNT2_MASK		0x8138

/*                                                                     */
#define ATH5K_PHYERR_CNT_MAX		0x00c00000

/*
                             
 */
#define	AR5K_TSF_THRES			0x813c

/*
                                   
                         
 */

/*
                                              
 */
#define	AR5K_RATE_ACKSIFS_BASE		0x8680			/*                  */
#define	AR5K_RATE_ACKSIFS(_n)		(AR5K_RATE_ACKSIFS_BSE + ((_n) << 2))
#define	AR5K_RATE_ACKSIFS_NORMAL	0x00000001	/*                     */
#define	AR5K_RATE_ACKSIFS_TURBO		0x00000400	/*                    */

/*
                                              
 */
#define AR5K_RATE_DUR_BASE		0x8700
#define AR5K_RATE_DUR(_n)		(AR5K_RATE_DUR_BASE + ((_n) << 2))

/*
                           
                                          
 */
#define AR5K_RATE2DB_BASE		0x87c0
#define AR5K_RATE2DB(_n)		(AR5K_RATE2DB_BASE + ((_n) << 2))

/*
                           
                                          
 */
#define AR5K_DB2RATE_BASE		0x87e0
#define AR5K_DB2RATE(_n)		(AR5K_DB2RATE_BASE + ((_n) << 2))

/*              */

#define AR5K_KEYTABLE_SIZE_5210		64
#define AR5K_KEYTABLE_SIZE_5211		128

/*                   */

/*
                      
 */
#define	AR5K_PHY_BASE			0x9800
#define	AR5K_PHY(_n)			(AR5K_PHY_BASE + ((_n) << 2))

/*
                                 
 */
#define	AR5K_PHY_TST2			0x9800			/*                  */
#define AR5K_PHY_TST2_TRIG_SEL		0x00000007	/*                   */
#define AR5K_PHY_TST2_TRIG		0x00000010	/*             */
#define AR5K_PHY_TST2_CBUS_MODE		0x00000060	/*                  */
#define AR5K_PHY_TST2_CLK32		0x00000400	/*                                   */
#define AR5K_PHY_TST2_CHANCOR_DUMP_EN	0x00000800	/*                         */
#define AR5K_PHY_TST2_EVEN_CHANCOR_DUMP	0x00001000	/*                       */
#define AR5K_PHY_TST2_RFSILENT_EN	0x00002000	/*                 */
#define AR5K_PHY_TST2_ALT_RFDATA	0x00004000	/*                                    */
#define AR5K_PHY_TST2_MINI_OBS_EN	0x00008000	/*                     */
#define AR5K_PHY_TST2_RX2_IS_RX5_INV	0x00010000	/*                                            */
#define AR5K_PHY_TST2_SLOW_CLK160	0x00020000	/*                 */
#define AR5K_PHY_TST2_AGC_OBS_SEL_3	0x00040000	/*                      */
#define AR5K_PHY_TST2_BBB_OBS_SEL	0x00080000	/*                         */
#define AR5K_PHY_TST2_ADC_OBS_SEL	0x00800000	/*                          */
#define AR5K_PHY_TST2_RX_CLR_SEL	0x08000000	/*                     */
#define AR5K_PHY_TST2_FORCE_AGC_CLR	0x10000000	/*                     */
#define AR5K_PHY_SHIFT_2GHZ		0x00004007	/*                            */
#define AR5K_PHY_SHIFT_5GHZ		0x00000007	/*                                      */

/*
                                                                 
  
                                                      
                                                      
                                                      
                                                         
                                                         
                                           
 */
#define	AR5K_PHY_TURBO			0x9804			/*                  */
#define	AR5K_PHY_TURBO_MODE		0x00000001	/*                   */
#define	AR5K_PHY_TURBO_SHORT		0x00000002	/*                                 */
#define	AR5K_PHY_TURBO_MIMO		0x00000004	/*                    */

/*
                               
              
 */
#define	AR5K_PHY_AGC			0x9808			/*                  */
#define	AR5K_PHY_TST1			0x9808
#define	AR5K_PHY_AGC_DISABLE		0x08000000	/*                      */
#define	AR5K_PHY_TST1_TXHOLD		0x00003800	/*                 */
#define	AR5K_PHY_TST1_TXSRC_SRC		0x00000002	/*                     */
#define	AR5K_PHY_TST1_TXSRC_SRC_S	1
#define	AR5K_PHY_TST1_TXSRC_ALT		0x00000080	/*                        */
#define	AR5K_PHY_TST1_TXSRC_ALT_S	7


/*
                                
 */
#define	AR5K_PHY_TIMING_3		0x9814
#define	AR5K_PHY_TIMING_3_DSC_MAN	0xfffe0000
#define	AR5K_PHY_TIMING_3_DSC_MAN_S	17
#define	AR5K_PHY_TIMING_3_DSC_EXP	0x0001e000
#define	AR5K_PHY_TIMING_3_DSC_EXP_S	13

/*
                             
 */
#define	AR5K_PHY_CHIP_ID		0x9818

/*
                          
 */
#define	AR5K_PHY_ACT			0x981c			/*                  */
#define	AR5K_PHY_ACT_ENABLE		0x00000001	/*              */
#define	AR5K_PHY_ACT_DISABLE		0x00000002	/*                */

/*
                           
 */
#define AR5K_PHY_RF_CTL2		0x9824			/*                  */
#define	AR5K_PHY_RF_CTL2_TXF2TXD_START	0x0000000f	/*                           */
#define	AR5K_PHY_RF_CTL2_TXF2TXD_START_S	0

#define AR5K_PHY_RF_CTL3		0x9828			/*                  */
#define AR5K_PHY_RF_CTL3_TXE2XLNA_ON	0x0000ff00	/*                   */
#define	AR5K_PHY_RF_CTL3_TXE2XLNA_ON_S	8

#define	AR5K_PHY_ADC_CTL			0x982c
#define	AR5K_PHY_ADC_CTL_INBUFGAIN_OFF		0x00000003
#define	AR5K_PHY_ADC_CTL_INBUFGAIN_OFF_S	0
#define	AR5K_PHY_ADC_CTL_PWD_DAC_OFF		0x00002000
#define	AR5K_PHY_ADC_CTL_PWD_BAND_GAP_OFF	0x00004000
#define	AR5K_PHY_ADC_CTL_PWD_ADC_OFF		0x00008000
#define	AR5K_PHY_ADC_CTL_INBUFGAIN_ON		0x00030000
#define	AR5K_PHY_ADC_CTL_INBUFGAIN_ON_S		16

#define AR5K_PHY_RF_CTL4		0x9834			/*                  */
#define AR5K_PHY_RF_CTL4_TXF2XPA_A_ON	0x00000001	/*                              */
#define AR5K_PHY_RF_CTL4_TXF2XPA_B_ON	0x00000100	/*                              */
#define	AR5K_PHY_RF_CTL4_TXE2XPA_A_OFF	0x00010000	/*                             */
#define AR5K_PHY_RF_CTL4_TXE2XPA_B_OFF	0x01000000	/*                             */

/*
                                 
                                  
 */
#define	AR5K_PHY_PA_CTL			0x9838			/*                  */
#define	AR5K_PHY_PA_CTL_XPA_A_HI	0x00000001	/*                */
#define	AR5K_PHY_PA_CTL_XPA_B_HI	0x00000002	/*                */
#define	AR5K_PHY_PA_CTL_XPA_A_EN	0x00000004	/*              */
#define	AR5K_PHY_PA_CTL_XPA_B_EN	0x00000008	/*              */

/*
                        
 */
#define AR5K_PHY_SETTLING		0x9844			/*                  */
#define	AR5K_PHY_SETTLING_AGC		0x0000007f	/*                   */
#define	AR5K_PHY_SETTLING_AGC_S		0
#define	AR5K_PHY_SETTLING_SWITCH	0x00003f80	/*                      */
#define	AR5K_PHY_SETTLING_SWITCH_S	7

/*
                     
 */
#define AR5K_PHY_GAIN			0x9848			/*                  */
#define	AR5K_PHY_GAIN_TXRX_ATTEN	0x0003f000	/*                   */
#define	AR5K_PHY_GAIN_TXRX_ATTEN_S	12
#define	AR5K_PHY_GAIN_TXRX_RF_MAX	0x007c0000
#define	AR5K_PHY_GAIN_TXRX_RF_MAX_S	18

#define	AR5K_PHY_GAIN_OFFSET		0x984c			/*                  */
#define	AR5K_PHY_GAIN_OFFSET_RXTX_FLAG	0x00020000	/*                */

/*
                                
                                   
 */
#define AR5K_PHY_DESIRED_SIZE		0x9850			/*                  */
#define	AR5K_PHY_DESIRED_SIZE_ADC	0x000000ff	/*                  */
#define	AR5K_PHY_DESIRED_SIZE_ADC_S	0
#define	AR5K_PHY_DESIRED_SIZE_PGA	0x0000ff00	/*                  */
#define	AR5K_PHY_DESIRED_SIZE_PGA_S	8
#define	AR5K_PHY_DESIRED_SIZE_TOT	0x0ff00000	/*                    */
#define	AR5K_PHY_DESIRED_SIZE_TOT_S	20

/*
                      
                                   
 */
#define	AR5K_PHY_SIG			0x9858			/*                  */
#define	AR5K_PHY_SIG_FIRSTEP		0x0003f000	/*         */
#define	AR5K_PHY_SIG_FIRSTEP_S		12
#define	AR5K_PHY_SIG_FIRPWR		0x03fc0000	/*       */
#define	AR5K_PHY_SIG_FIRPWR_S		18

/*
                                      
                                   
 */
#define	AR5K_PHY_AGCCOARSE		0x985c			/*                  */
#define	AR5K_PHY_AGCCOARSE_LO		0x00007f80	/*                */
#define	AR5K_PHY_AGCCOARSE_LO_S		7
#define	AR5K_PHY_AGCCOARSE_HI		0x003f8000	/*                 */
#define	AR5K_PHY_AGCCOARSE_HI_S		15

/*
                               
 */
#define	AR5K_PHY_AGCCTL			0x9860			/*                  */
#define	AR5K_PHY_AGCCTL_CAL		0x00000001	/*                        */
#define	AR5K_PHY_AGCCTL_NF		0x00000002	/*                                */
#define	AR5K_PHY_AGCCTL_OFDM_DIV_DIS	0x00000008	/*                                         */
#define	AR5K_PHY_AGCCTL_NF_EN		0x00008000	/*                                     */
#define	AR5K_PHY_AGCTL_FLTR_CAL		0x00010000	/*                              */
#define	AR5K_PHY_AGCCTL_NF_NOUPDATE	0x00020000	/*                               */

/*
                                                                   
 */
#define AR5K_PHY_NF			0x9864			/*                  */
#define AR5K_PHY_NF_M			0x000001ff	/*                                                   */
#define AR5K_PHY_NF_SVAL(_n)           (((_n) & AR5K_PHY_NF_M) | (1 << 9))
#define	AR5K_PHY_NF_THRESH62		0x0007f000	/*                                     */
#define	AR5K_PHY_NF_THRESH62_S		12
#define	AR5K_PHY_NF_MINCCA_PWR		0x0ff80000	/*                                                                 */
#define	AR5K_PHY_NF_MINCCA_PWR_S	19

/*
                                     
 */
#define	AR5K_PHY_ADCSAT			0x9868
#define	AR5K_PHY_ADCSAT_ICNT		0x0001f800
#define	AR5K_PHY_ADCSAT_ICNT_S		11
#define	AR5K_PHY_ADCSAT_THR		0x000007e0
#define	AR5K_PHY_ADCSAT_THR_S		5

/*
                                                                   
 */

/*                 */
#define AR5K_PHY_WEAK_OFDM_HIGH_THR		0x9868
#define AR5K_PHY_WEAK_OFDM_HIGH_THR_M2_COUNT	0x0000001f
#define AR5K_PHY_WEAK_OFDM_HIGH_THR_M2_COUNT_S	0
#define AR5K_PHY_WEAK_OFDM_HIGH_THR_M1		0x00fe0000
#define AR5K_PHY_WEAK_OFDM_HIGH_THR_M1_S	17
#define AR5K_PHY_WEAK_OFDM_HIGH_THR_M2		0x7f000000
#define AR5K_PHY_WEAK_OFDM_HIGH_THR_M2_S	24

/*                */
#define AR5K_PHY_WEAK_OFDM_LOW_THR		0x986c
#define AR5K_PHY_WEAK_OFDM_LOW_THR_SELFCOR_EN	0x00000001
#define AR5K_PHY_WEAK_OFDM_LOW_THR_M2_COUNT	0x00003f00
#define AR5K_PHY_WEAK_OFDM_LOW_THR_M2_COUNT_S	8
#define AR5K_PHY_WEAK_OFDM_LOW_THR_M1		0x001fc000
#define AR5K_PHY_WEAK_OFDM_LOW_THR_M1_S		14
#define AR5K_PHY_WEAK_OFDM_LOW_THR_M2		0x0fe00000
#define AR5K_PHY_WEAK_OFDM_LOW_THR_M2_S		21


/*
                              
 */
#define AR5K_PHY_SCR			0x9870

#define AR5K_PHY_SLMT			0x9874
#define AR5K_PHY_SLMT_32MHZ		0x0000007f

#define AR5K_PHY_SCAL			0x9878
#define AR5K_PHY_SCAL_32MHZ		0x0000000e
#define	AR5K_PHY_SCAL_32MHZ_5311	0x00000008
#define	AR5K_PHY_SCAL_32MHZ_2417	0x0000000a
#define	AR5K_PHY_SCAL_32MHZ_HB63	0x00000032

/*
                                               
 */
#define	AR5K_PHY_PLL			0x987c
#define	AR5K_PHY_PLL_20MHZ		0x00000013	/*                   */
/*                    */
#define	AR5K_PHY_PLL_40MHZ_5211		0x00000018
#define	AR5K_PHY_PLL_40MHZ_5212		0x000000aa
#define	AR5K_PHY_PLL_40MHZ_5413		0x00000004
#define	AR5K_PHY_PLL_40MHZ		(ah->ah_version == AR5K_AR5211 ? \
					AR5K_PHY_PLL_40MHZ_5211 : AR5K_PHY_PLL_40MHZ_5212)
/*                      */
#define	AR5K_PHY_PLL_44MHZ_5211		0x00000019
#define	AR5K_PHY_PLL_44MHZ_5212		0x000000ab
#define	AR5K_PHY_PLL_44MHZ		(ah->ah_version == AR5K_AR5211 ? \
					AR5K_PHY_PLL_44MHZ_5211 : AR5K_PHY_PLL_44MHZ_5212)

#define AR5K_PHY_PLL_RF5111		0x00000000
#define AR5K_PHY_PLL_RF5112		0x00000040
#define	AR5K_PHY_PLL_HALF_RATE		0x00000100
#define	AR5K_PHY_PLL_QUARTER_RATE	0x00000200

/*
                     
  
                                                                    
                                                                      
                                                                       
                                                                               
 */

#define AR5K_RF_BUFFER			0x989c
#define AR5K_RF_BUFFER_CONTROL_0	0x98c0	/*                 */
#define AR5K_RF_BUFFER_CONTROL_1	0x98c4	/*                */
#define AR5K_RF_BUFFER_CONTROL_2	0x98cc	/*                */

#define AR5K_RF_BUFFER_CONTROL_3	0x98d0	/*                */
						/*                     */
						/*                            */

#define AR5K_RF_BUFFER_CONTROL_4	0x98d4  /*                           */
						/*                      */
						/*                */
						/*                                */

#define AR5K_RF_BUFFER_CONTROL_5	0x98d8	/*                */
						/*                                */
						/*                 */
						/*                */

#define AR5K_RF_BUFFER_CONTROL_6	0x98dc	/*                */

/*
                               
 */
#define AR5K_PHY_RFSTG			0x98d4
#define AR5K_PHY_RFSTG_DISABLE		0x00000021

/*
                
 */
#define	AR5K_PHY_BIN_MASK_1	0x9900
#define	AR5K_PHY_BIN_MASK_2	0x9904
#define	AR5K_PHY_BIN_MASK_3	0x9908

#define	AR5K_PHY_BIN_MASK_CTL		0x990c
#define	AR5K_PHY_BIN_MASK_CTL_MASK_4	0x00003fff
#define	AR5K_PHY_BIN_MASK_CTL_MASK_4_S	0
#define	AR5K_PHY_BIN_MASK_CTL_RATE	0xff000000
#define	AR5K_PHY_BIN_MASK_CTL_RATE_S	24

/*
                               
 */
#define AR5K_PHY_ANT_CTL		0x9910			/*                  */
#define	AR5K_PHY_ANT_CTL_TXRX_EN	0x00000001	/*                  */
#define	AR5K_PHY_ANT_CTL_SECTORED_ANT	0x00000004	/*                  */
#define	AR5K_PHY_ANT_CTL_HITUNE5	0x00000008	/*             */
#define	AR5K_PHY_ANT_CTL_SWTABLE_IDLE	0x000003f0	/*                       */
#define	AR5K_PHY_ANT_CTL_SWTABLE_IDLE_S	4

/*
                                      
 */
#define	AR5K_PHY_RX_DELAY		0x9914			/*                  */
#define	AR5K_PHY_RX_DELAY_M		0x00003fff	/*                                                */

/*
                                        
 */
#define	AR5K_PHY_MAX_RX_LEN		0x991c

/*
                        
                                                     
 */
#define	AR5K_PHY_IQ			0x9920			/*                  */
#define	AR5K_PHY_IQ_CORR_Q_Q_COFF	0x0000001f	/*                            */
#define	AR5K_PHY_IQ_CORR_Q_Q_COFF_S	0
#define	AR5K_PHY_IQ_CORR_Q_I_COFF	0x000007e0	/*                            */
#define	AR5K_PHY_IQ_CORR_Q_I_COFF_S	5
#define	AR5K_PHY_IQ_CORR_ENABLE		0x00000800	/*                       */
#define	AR5K_PHY_IQ_CAL_NUM_LOG_MAX	0x0000f000	/*                                             */
#define	AR5K_PHY_IQ_CAL_NUM_LOG_MAX_S	12
#define	AR5K_PHY_IQ_RUN			0x00010000	/*                     */
#define	AR5K_PHY_IQ_USE_PT_DF		0x00020000	/*                        */
#define	AR5K_PHY_IQ_EARLY_TRIG_THR	0x00200000	/*                                     */
#define	AR5K_PHY_IQ_PILOT_MASK_EN	0x10000000	/*                       */
#define	AR5K_PHY_IQ_CHAN_MASK_EN	0x20000000	/*                         */
#define	AR5K_PHY_IQ_SPUR_FILT_EN	0x40000000	/*                    */
#define	AR5K_PHY_IQ_SPUR_RSSI_EN	0x80000000	/*                  */

/*
                        
                                                    
                                           
 */
#define	AR5K_PHY_OFDM_SELFCORR			0x9924			/*                  */
#define	AR5K_PHY_OFDM_SELFCORR_CYPWR_THR1_EN	0x00000001	/*                          */
#define	AR5K_PHY_OFDM_SELFCORR_CYPWR_THR1	0x000000fe	/*                                  */
#define	AR5K_PHY_OFDM_SELFCORR_CYPWR_THR1_S	1
#define	AR5K_PHY_OFDM_SELFCORR_CYPWR_THR3	0x00000100	/*                                     */
#define	AR5K_PHY_OFDM_SELFCORR_RSSI_1ATHR_EN	0x00008000	/*                              */
#define	AR5K_PHY_OFDM_SELFCORR_RSSI_1ATHR	0x00010000	/*                               */
#define	AR5K_PHY_OFDM_SELFCORR_LSCTHR_HIRSSI	0x00800000	/*                               */

/*
                               
 */
#define	AR5K_PHY_WARM_RESET		0x9928

/*
                            
 */
#define AR5K_PHY_CTL			0x992c			/*                  */
#define	AR5K_PHY_CTL_RX_DRAIN_RATE	0x00000001	/*                   */
#define	AR5K_PHY_CTL_LATE_TX_SIG_SYM	0x00000002	/*                           */
#define	AR5K_PHY_CTL_GEN_SCRAMBLER	0x00000004	/*                    */
#define	AR5K_PHY_CTL_TX_ANT_SEL		0x00000008	/*                   */
#define	AR5K_PHY_CTL_TX_ANT_STATIC	0x00000010	/*                   */
#define	AR5K_PHY_CTL_RX_ANT_SEL		0x00000020	/*                   */
#define	AR5K_PHY_CTL_RX_ANT_STATIC	0x00000040	/*                   */
#define	AR5K_PHY_CTL_LOW_FREQ_SLE_EN	0x00000080	/*                       */

/*
                                  
 */
#define	AR5K_PHY_PAPD_PROBE		0x9930
#define	AR5K_PHY_PAPD_PROBE_SH_HI_PAR	0x00000001
#define	AR5K_PHY_PAPD_PROBE_PCDAC_BIAS	0x00000002
#define	AR5K_PHY_PAPD_PROBE_COMP_GAIN	0x00000040
#define	AR5K_PHY_PAPD_PROBE_TXPOWER	0x00007e00
#define	AR5K_PHY_PAPD_PROBE_TXPOWER_S	9
#define	AR5K_PHY_PAPD_PROBE_TX_NEXT	0x00008000
#define	AR5K_PHY_PAPD_PROBE_PREDIST_EN	0x00010000
#define	AR5K_PHY_PAPD_PROBE_TYPE	0x01800000	/*         */
#define	AR5K_PHY_PAPD_PROBE_TYPE_S	23
#define	AR5K_PHY_PAPD_PROBE_TYPE_OFDM	0
#define	AR5K_PHY_PAPD_PROBE_TYPE_XR	1
#define	AR5K_PHY_PAPD_PROBE_TYPE_CCK	2
#define	AR5K_PHY_PAPD_PROBE_GAINF	0xfe000000
#define	AR5K_PHY_PAPD_PROBE_GAINF_S	25
#define	AR5K_PHY_PAPD_PROBE_INI_5111	0x00004883	/*         */
#define	AR5K_PHY_PAPD_PROBE_INI_5112	0x00004882	/*         */

/*
                                      
 */
#define	AR5K_PHY_TXPOWER_RATE1			0x9934
#define	AR5K_PHY_TXPOWER_RATE2			0x9938
#define	AR5K_PHY_TXPOWER_RATE_MAX		0x993c
#define	AR5K_PHY_TXPOWER_RATE_MAX_TPC_ENABLE	0x00000040
#define	AR5K_PHY_TXPOWER_RATE3			0xa234
#define	AR5K_PHY_TXPOWER_RATE4			0xa238

/*
                                     
 */
#define	AR5K_PHY_FRAME_CTL_5210		0x9804
#define	AR5K_PHY_FRAME_CTL_5211		0x9944
#define	AR5K_PHY_FRAME_CTL		(ah->ah_version == AR5K_AR5210 ? \
					AR5K_PHY_FRAME_CTL_5210 : AR5K_PHY_FRAME_CTL_5211)
/*             */
#define	AR5K_PHY_FRAME_CTL_WIN_LEN	0x00000003	/*                         */
#define	AR5K_PHY_FRAME_CTL_WIN_LEN_S	0
#define	AR5K_PHY_FRAME_CTL_TX_CLIP	0x00000038	/*                      */
#define	AR5K_PHY_FRAME_CTL_TX_CLIP_S	3
#define	AR5K_PHY_FRAME_CTL_PREP_CHINFO	0x00010000	/*                   */
#define	AR5K_PHY_FRAME_CTL_EMU		0x80000000
#define	AR5K_PHY_FRAME_CTL_EMU_S	31
/*                 */
#define	AR5K_PHY_FRAME_CTL_TIMING_ERR	0x01000000	/*                  */
#define	AR5K_PHY_FRAME_CTL_PARITY_ERR	0x02000000	/*              */
#define	AR5K_PHY_FRAME_CTL_ILLRATE_ERR	0x04000000	/*              */
#define	AR5K_PHY_FRAME_CTL_ILLLEN_ERR	0x08000000	/*                */
#define	AR5K_PHY_FRAME_CTL_SERVICE_ERR	0x20000000
#define	AR5K_PHY_FRAME_CTL_TXURN_ERR	0x40000000	/*             */
#define AR5K_PHY_FRAME_CTL_INI	\
			(AR5K_PHY_FRAME_CTL_SERVICE_ERR | \
			 AR5K_PHY_FRAME_CTL_TXURN_ERR | \
			 AR5K_PHY_FRAME_CTL_ILLLEN_ERR | \
			 AR5K_PHY_FRAME_CTL_ILLRATE_ERR | \
			 AR5K_PHY_FRAME_CTL_PARITY_ERR | \
			 AR5K_PHY_FRAME_CTL_TIMING_ERR)

/*
                                            
 */
#define	AR5K_PHY_TX_PWR_ADJ			0x994c
#define	AR5K_PHY_TX_PWR_ADJ_CCK_GAIN_DELTA	0x00000fc0
#define	AR5K_PHY_TX_PWR_ADJ_CCK_GAIN_DELTA_S	6
#define	AR5K_PHY_TX_PWR_ADJ_CCK_PCDAC_INDEX	0x00fc0000
#define	AR5K_PHY_TX_PWR_ADJ_CCK_PCDAC_INDEX_S	18

/*
                                       
 */
#define	AR5K_PHY_RADAR			0x9954
#define	AR5K_PHY_RADAR_ENABLE		0x00000001
#define	AR5K_PHY_RADAR_DISABLE		0x00000000
#define AR5K_PHY_RADAR_INBANDTHR	0x0000003e	/*                 
                                    
                 */
#define AR5K_PHY_RADAR_INBANDTHR_S	1

#define AR5K_PHY_RADAR_PRSSI_THR	0x00000fc0	/*                         
                                
                     */
#define AR5K_PHY_RADAR_PRSSI_THR_S	6

#define AR5K_PHY_RADAR_PHEIGHT_THR	0x0003f000	/*                       
                                
                     */
#define AR5K_PHY_RADAR_PHEIGHT_THR_S	12

#define AR5K_PHY_RADAR_RSSI_THR		0x00fc0000	/*                          
                                
                     */
#define AR5K_PHY_RADAR_RSSI_THR_S	18

#define AR5K_PHY_RADAR_FIRPWR_THR	0x7f000000	/*                        
                                  
                                   
                                  */
#define AR5K_PHY_RADAR_FIRPWR_THRS	24

/*
                                     
 */
#define AR5K_PHY_ANT_SWITCH_TABLE_0	0x9960
#define AR5K_PHY_ANT_SWITCH_TABLE_1	0x9964

/*
                            
 */
#define AR5K_PHY_NFTHRES		0x9968

/*
                                  
 */
#define AR5K_PHY_SIGMA_DELTA		0x996C
#define AR5K_PHY_SIGMA_DELTA_ADC_SEL	0x00000003
#define AR5K_PHY_SIGMA_DELTA_ADC_SEL_S	0
#define AR5K_PHY_SIGMA_DELTA_FILT2	0x000000f8
#define AR5K_PHY_SIGMA_DELTA_FILT2_S	3
#define AR5K_PHY_SIGMA_DELTA_FILT1	0x00001f00
#define AR5K_PHY_SIGMA_DELTA_FILT1_S	8
#define AR5K_PHY_SIGMA_DELTA_ADC_CLIP	0x01ffe000
#define AR5K_PHY_SIGMA_DELTA_ADC_CLIP_S	13

/*
                                  
 */
#define AR5K_PHY_RESTART		0x9970		/*         */
#define AR5K_PHY_RESTART_DIV_GC		0x001c0000	/*                             */
#define AR5K_PHY_RESTART_DIV_GC_S	18

/*
                                                                    
 */
#define AR5K_PHY_RFBUS_REQ		0x997C
#define AR5K_PHY_RFBUS_REQ_REQUEST	0x00000001

/*
                            
 */
#define AR5K_PHY_TIMING_7		0x9980
#define AR5K_PHY_TIMING_8		0x9984
#define AR5K_PHY_TIMING_8_PILOT_MASK_2		0x000fffff
#define AR5K_PHY_TIMING_8_PILOT_MASK_2_S	0

#define AR5K_PHY_BIN_MASK2_1		0x9988
#define AR5K_PHY_BIN_MASK2_2		0x998c
#define AR5K_PHY_BIN_MASK2_3		0x9990

#define AR5K_PHY_BIN_MASK2_4		0x9994
#define AR5K_PHY_BIN_MASK2_4_MASK_4	0x00003fff
#define AR5K_PHY_BIN_MASK2_4_MASK_4_S	0

#define AR5K_PHY_TIMING_9			0x9998
#define AR5K_PHY_TIMING_10			0x999c
#define AR5K_PHY_TIMING_10_PILOT_MASK_2		0x000fffff
#define AR5K_PHY_TIMING_10_PILOT_MASK_2_S	0

/*
                          
 */
#define AR5K_PHY_TIMING_11			0x99a0		/*                  */
#define AR5K_PHY_TIMING_11_SPUR_DELTA_PHASE	0x000fffff	/*                  */
#define AR5K_PHY_TIMING_11_SPUR_DELTA_PHASE_S	0
#define AR5K_PHY_TIMING_11_SPUR_FREQ_SD		0x3ff00000	/*                  */
#define AR5K_PHY_TIMING_11_SPUR_FREQ_SD_S	20
#define AR5K_PHY_TIMING_11_USE_SPUR_IN_AGC	0x40000000	/*                             */
#define AR5K_PHY_TIMING_11_USE_SPUR_IN_SELFCOR	0x80000000	/*                                     */

/*
              
 */
#define	AR5K_BB_GAIN_BASE		0x9b00	/*                                            */
#define AR5K_BB_GAIN(_n)		(AR5K_BB_GAIN_BASE + ((_n) << 2))
#define	AR5K_RF_GAIN_BASE		0x9a00	/*                                      */
#define AR5K_RF_GAIN(_n)		(AR5K_RF_GAIN_BASE + ((_n) << 2))

/*
                                                    
 */
#define	AR5K_PHY_IQRES_CAL_PWR_I	0x9c10	/*                         */
#define	AR5K_PHY_IQRES_CAL_PWR_Q	0x9c14	/*                            */
#define	AR5K_PHY_IQRES_CAL_CORR		0x9c18	/*                 */

/*
                                    
 */
#define	AR5K_PHY_CURRENT_RSSI	0x9c1c

/*
                            
 */
#define	AR5K_PHY_RFBUS_GRANT	0x9c20
#define	AR5K_PHY_RFBUS_GRANT_OK	0x00000001

/*
                        
 */
#define	AR5K_PHY_ADC_TEST	0x9c24
#define	AR5K_PHY_ADC_TEST_I	0x00000001
#define	AR5K_PHY_ADC_TEST_Q	0x00000200

/*
                        
 */
#define	AR5K_PHY_DAC_TEST	0x9c28
#define	AR5K_PHY_DAC_TEST_I	0x00000001
#define	AR5K_PHY_DAC_TEST_Q	0x00000200

/*
                        
 */
#define	AR5K_PHY_PTAT		0x9c2c

/*
                                       
 */
#define	AR5K_PHY_BAD_TX_RATE	0x9c30

/*
                                  
 */
#define	AR5K_PHY_SPUR_PWR	0x9c34			/*                  */
#define	AR5K_PHY_SPUR_PWR_I	0x00000001	/*                                   */
#define	AR5K_PHY_SPUR_PWR_Q	0x00000100	/*                                   */
#define	AR5K_PHY_SPUR_PWR_FILT	0x00010000	/*                                 */

/*
                                          
 */
#define	AR5K_PHY_CHAN_STATUS		0x9c38
#define	AR5K_PHY_CHAN_STATUS_BT_ACT	0x00000001
#define	AR5K_PHY_CHAN_STATUS_RX_CLR_RAW	0x00000002
#define	AR5K_PHY_CHAN_STATUS_RX_CLR_MAC	0x00000004
#define	AR5K_PHY_CHAN_STATUS_RX_CLR_PAP	0x00000008

/*
                             
 */
#define	AR5K_PHY_HEAVY_CLIP_ENABLE	0x99e0

/*
                                    
 */
#define AR5K_PHY_SCLOCK			0x99f0
#define AR5K_PHY_SCLOCK_32MHZ		0x0000000c
#define AR5K_PHY_SDELAY			0x99f4
#define AR5K_PHY_SDELAY_32MHZ		0x000000ff
#define AR5K_PHY_SPENDING		0x99f8


/*
                                
                
 */
#define	AR5K_PHY_PAPD_I_BASE	0xa000
#define	AR5K_PHY_PAPD_I(_n)	(AR5K_PHY_PAPD_I_BASE + ((_n) << 2))

/*
                           
 */
#define	AR5K_PHY_PCDAC_TXPOWER_BASE	0xa180
#define	AR5K_PHY_PCDAC_TXPOWER(_n)	(AR5K_PHY_PCDAC_TXPOWER_BASE + ((_n) << 2))

/*
                            
 */
#define	AR5K_PHY_MODE			0x0a200			/*                  */
#define	AR5K_PHY_MODE_MOD		0x00000001	/*                    */
#define AR5K_PHY_MODE_MOD_OFDM		0
#define AR5K_PHY_MODE_MOD_CCK		1
#define AR5K_PHY_MODE_FREQ		0x00000002	/*               */
#define	AR5K_PHY_MODE_FREQ_5GHZ		0
#define	AR5K_PHY_MODE_FREQ_2GHZ		2
#define AR5K_PHY_MODE_MOD_DYN		0x00000004	/*                                      */
#define AR5K_PHY_MODE_RAD		0x00000008	/*         */
#define AR5K_PHY_MODE_RAD_RF5111	0
#define AR5K_PHY_MODE_RAD_RF5112	8
#define AR5K_PHY_MODE_XR		0x00000010	/*                        */
#define	AR5K_PHY_MODE_HALF_RATE		0x00000020	/*                         */
#define	AR5K_PHY_MODE_QUARTER_RATE	0x00000040	/*                           */

/*
                                                
 */
#define AR5K_PHY_CCKTXCTL		0xa204
#define AR5K_PHY_CCKTXCTL_WORLD		0x00000000
#define AR5K_PHY_CCKTXCTL_JAPAN		0x00000010
#define	AR5K_PHY_CCKTXCTL_SCRAMBLER_DIS	0x00000001
#define	AR5K_PHY_CCKTXCTK_DAC_SCALE	0x00000004

/*
                                                                  
 */
#define AR5K_PHY_CCK_CROSSCORR			0xa208
#define AR5K_PHY_CCK_CROSSCORR_WEAK_SIG_THR	0x0000003f
#define AR5K_PHY_CCK_CROSSCORR_WEAK_SIG_THR_S	0

/*                                                       */
#define	AR5K_PHY_FAST_ANT_DIV		0xa208
#define	AR5K_PHY_FAST_ANT_DIV_EN	0x00002000

/*
                                 
 */
#define	AR5K_PHY_GAIN_2GHZ			0xa20c
#define	AR5K_PHY_GAIN_2GHZ_MARGIN_TXRX		0x00fc0000
#define	AR5K_PHY_GAIN_2GHZ_MARGIN_TXRX_S	18
#define	AR5K_PHY_GAIN_2GHZ_INI_5111		0x6480416c

#define	AR5K_PHY_CCK_RX_CTL_4			0xa21c
#define	AR5K_PHY_CCK_RX_CTL_4_FREQ_EST_SHORT	0x01f80000
#define	AR5K_PHY_CCK_RX_CTL_4_FREQ_EST_SHORT_S	19

#define	AR5K_PHY_DAG_CCK_CTL			0xa228
#define	AR5K_PHY_DAG_CCK_CTL_EN_RSSI_THR	0x00000200
#define	AR5K_PHY_DAG_CCK_CTL_RSSI_THR		0x0001fc00
#define	AR5K_PHY_DAG_CCK_CTL_RSSI_THR_S		10

#define	AR5K_PHY_FAST_ADC	0xa24c

#define	AR5K_PHY_BLUETOOTH	0xa254

/*
                                  
          
 */
#define	AR5K_PHY_TPC_RG1		0xa258
#define	AR5K_PHY_TPC_RG1_NUM_PD_GAIN	0x0000c000
#define	AR5K_PHY_TPC_RG1_NUM_PD_GAIN_S	14
#define AR5K_PHY_TPC_RG1_PDGAIN_1	0x00030000
#define AR5K_PHY_TPC_RG1_PDGAIN_1_S	16
#define AR5K_PHY_TPC_RG1_PDGAIN_2	0x000c0000
#define AR5K_PHY_TPC_RG1_PDGAIN_2_S	18
#define AR5K_PHY_TPC_RG1_PDGAIN_3	0x00300000
#define AR5K_PHY_TPC_RG1_PDGAIN_3_S	20

#define	AR5K_PHY_TPC_RG5			0xa26C
#define	AR5K_PHY_TPC_RG5_PD_GAIN_OVERLAP	0x0000000F
#define	AR5K_PHY_TPC_RG5_PD_GAIN_OVERLAP_S	0
#define	AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_1	0x000003F0
#define	AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_1_S	4
#define	AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_2	0x0000FC00
#define	AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_2_S	10
#define	AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_3	0x003F0000
#define	AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_3_S	16
#define	AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_4	0x0FC00000
#define	AR5K_PHY_TPC_RG5_PD_GAIN_BOUNDARY_4_S	22

/*
                           
 */
#define AR5K_PHY_PDADC_TXPOWER_BASE	0xa280
#define	AR5K_PHY_PDADC_TXPOWER(_n)	(AR5K_PHY_PDADC_TXPOWER_BASE + ((_n) << 2))

/*
                               
 */
#define AR5K_AR5312_RESET		0xbc003020
#define AR5K_AR5312_RESET_BB0_COLD	0x00000004
#define AR5K_AR5312_RESET_BB1_COLD	0x00000200
#define AR5K_AR5312_RESET_WMAC0		0x00002000
#define AR5K_AR5312_RESET_BB0_WARM	0x00004000
#define AR5K_AR5312_RESET_WMAC1		0x00020000
#define AR5K_AR5312_RESET_BB1_WARM	0x00040000

#define AR5K_AR5312_ENABLE		0xbc003080
#define AR5K_AR5312_ENABLE_WLAN0    0x00000001
#define AR5K_AR5312_ENABLE_WLAN1    0x00000008

#define AR5K_AR2315_RESET		0xb1000004
#define AR5K_AR2315_RESET_WMAC		0x00000001
#define AR5K_AR2315_RESET_BB_WARM	0x00000002

#define AR5K_AR2315_AHB_ARB_CTL		0xb1000008
#define AR5K_AR2315_AHB_ARB_CTL_WLAN	0x00000002

#define AR5K_AR2315_BYTESWAP	0xb100000c
#define AR5K_AR2315_BYTESWAP_WMAC	0x00000002
