#ifndef __ARCH_ARM_MACH_OMAP2_PRM_REGBITS_24XX_H
#define __ARCH_ARM_MACH_OMAP2_PRM_REGBITS_24XX_H

/*
 * OMAP24XX Power/Reset Management register bits
 *
 * Copyright (C) 2007 Texas Instruments, Inc.
 * Copyright (C) 2007 Nokia Corporation
 *
 * Written by Paul Walmsley
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include "prm2xxx_3xxx.h"

/*                               */

/*                                                                      */
#define OMAP24XX_VOLTTRANS_ST_MASK			(1 << 2)
#define OMAP24XX_WKUP2_ST_MASK				(1 << 1)
#define OMAP24XX_WKUP1_ST_MASK				(1 << 0)

/*                                                                      */
#define OMAP24XX_VOLTTRANS_EN_MASK			(1 << 2)
#define OMAP24XX_WKUP2_EN_MASK				(1 << 1)
#define OMAP24XX_WKUP1_EN_MASK				(1 << 0)

/*                                                                    */
#define OMAP24XX_EN_MPU_SHIFT				1
#define OMAP24XX_EN_MPU_MASK				(1 << 1)
#define OMAP24XX_EN_CORE_SHIFT 				0
#define OMAP24XX_EN_CORE_MASK				(1 << 0)

/*
                                                                     
              
 */
#define OMAP24XX_MEMONSTATE_SHIFT			10
#define OMAP24XX_MEMONSTATE_MASK			(0x3 << 10)
#define OMAP24XX_MEMRETSTATE_MASK			(1 << 3)

/*                                                               */
#define OMAP24XX_FORCESTATE_MASK			(1 << 18)

/*
                                                               
                            
 */
#define OMAP24XX_CLKACTIVITY_MASK			(1 << 19)

/*                                                          */
#define OMAP24XX_LASTSTATEENTERED_SHIFT			4
#define OMAP24XX_LASTSTATEENTERED_MASK			(0x3 << 4)

/*                                             */
#define OMAP2430_MEMSTATEST_SHIFT			10
#define OMAP2430_MEMSTATEST_MASK			(0x3 << 10)

/*                                                         */
#define OMAP24XX_POWERSTATEST_SHIFT			0
#define OMAP24XX_POWERSTATEST_MASK			(0x3 << 0)


/*                                */

/*               */
#define OMAP24XX_REV_SHIFT				0
#define OMAP24XX_REV_MASK				(0xff << 0)

/*                */
#define OMAP24XX_AUTOIDLE_MASK				(1 << 0)

/*                                  */
#define OMAP2430_DPLL_RECAL_ST_MASK			(1 << 6)
#define OMAP24XX_TRANSITION_ST_MASK			(1 << 5)
#define OMAP24XX_EVGENOFF_ST_MASK			(1 << 4)
#define OMAP24XX_EVGENON_ST_MASK			(1 << 3)

/*                                  */
#define OMAP2430_DPLL_RECAL_EN_MASK			(1 << 6)
#define OMAP24XX_TRANSITION_EN_MASK			(1 << 5)
#define OMAP24XX_EVGENOFF_EN_MASK			(1 << 4)
#define OMAP24XX_EVGENON_EN_MASK			(1 << 3)

/*               */
#define OMAP24XX_AUTO_EXTVOLT_MASK			(1 << 15)
#define OMAP24XX_FORCE_EXTVOLT_MASK			(1 << 14)
#define OMAP24XX_SETOFF_LEVEL_SHIFT			12
#define OMAP24XX_SETOFF_LEVEL_MASK			(0x3 << 12)
#define OMAP24XX_MEMRETCTRL_MASK			(1 << 8)
#define OMAP24XX_SETRET_LEVEL_SHIFT			6
#define OMAP24XX_SETRET_LEVEL_MASK			(0x3 << 6)
#define OMAP24XX_VOLT_LEVEL_SHIFT			0
#define OMAP24XX_VOLT_LEVEL_MASK			(0x3 << 0)

/*             */
#define OMAP24XX_ST_VOLTLEVEL_SHIFT			0
#define OMAP24XX_ST_VOLTLEVEL_MASK			(0x3 << 0)

/*                                */

/*                  */
#define OMAP2420_CLKOUT2_EN_SHIFT			15
#define OMAP2420_CLKOUT2_EN_MASK			(1 << 15)
#define OMAP2420_CLKOUT2_DIV_SHIFT			11
#define OMAP2420_CLKOUT2_DIV_MASK			(0x7 << 11)
#define OMAP2420_CLKOUT2_SOURCE_SHIFT			8
#define OMAP2420_CLKOUT2_SOURCE_MASK			(0x3 << 8)
#define OMAP24XX_CLKOUT_EN_SHIFT			7
#define OMAP24XX_CLKOUT_EN_MASK				(1 << 7)
#define OMAP24XX_CLKOUT_DIV_SHIFT			3
#define OMAP24XX_CLKOUT_DIV_MASK			(0x7 << 3)
#define OMAP24XX_CLKOUT_SOURCE_SHIFT			0
#define OMAP24XX_CLKOUT_SOURCE_MASK			(0x3 << 0)

/*                   */
#define OMAP24XX_EMULATION_EN_SHIFT			0
#define OMAP24XX_EMULATION_EN_MASK			(1 << 0)

/*                  */
#define OMAP24XX_VALID_CONFIG_MASK			(1 << 0)

/*                    */
#define OMAP24XX_CONFIG_STATUS_MASK			(1 << 0)

/*                              */

/*                              */

/*              */
#define OMAP2420_CLKOUT2_POL_MASK			(1 << 10)
#define OMAP24XX_CLKOUT_POL_MASK			(1 << 9)
#define OMAP24XX_CLKREQ_POL_MASK			(1 << 8)
#define OMAP2430_USE_POWEROK_MASK			(1 << 2)
#define OMAP2430_POWEROK_POL_MASK			(1 << 1)
#define OMAP24XX_EXTVOL_POL_MASK			(1 << 0)

/*                            */
/*                                                    */

/*                            */
#define OMAP2430_PM_WKDEP_MPU_EN_MDM_SHIFT		5
#define OMAP2430_PM_WKDEP_MPU_EN_MDM_MASK		(1 << 5)
#define OMAP24XX_PM_WKDEP_MPU_EN_DSP_SHIFT		2
#define OMAP24XX_PM_WKDEP_MPU_EN_DSP_MASK		(1 << 2)

/*                                */

/*                                  */

/*                                   */

/*                               */
#define OMAP2430_FORCESTATE_MASK			(1 << 18)

/*                             */
/*                                                                 */

/*                             */

/*                             */

/*                            */

/*                             */

/*                            */
#define OMAP2430_PM_WKDEP_CORE_EN_MDM_MASK		(1 << 5)
#define OMAP24XX_PM_WKDEP_CORE_EN_GFX_MASK		(1 << 3)
#define OMAP24XX_PM_WKDEP_CORE_EN_DSP_MASK		(1 << 2)

/*                                */
#define OMAP24XX_MEMORYCHANGE_MASK			(1 << 20)
#define OMAP24XX_MEM3ONSTATE_SHIFT			14
#define OMAP24XX_MEM3ONSTATE_MASK			(0x3 << 14)
#define OMAP24XX_MEM2ONSTATE_SHIFT			12
#define OMAP24XX_MEM2ONSTATE_MASK			(0x3 << 12)
#define OMAP24XX_MEM1ONSTATE_SHIFT			10
#define OMAP24XX_MEM1ONSTATE_MASK			(0x3 << 10)
#define OMAP24XX_MEM3RETSTATE_MASK			(1 << 5)
#define OMAP24XX_MEM2RETSTATE_MASK			(1 << 4)
#define OMAP24XX_MEM1RETSTATE_MASK			(1 << 3)

/*                              */
#define OMAP24XX_MEM3STATEST_SHIFT			14
#define OMAP24XX_MEM3STATEST_MASK			(0x3 << 14)
#define OMAP24XX_MEM2STATEST_SHIFT			12
#define OMAP24XX_MEM2STATEST_MASK			(0x3 << 12)
#define OMAP24XX_MEM1STATEST_SHIFT			10
#define OMAP24XX_MEM1STATEST_MASK			(0x3 << 10)

/*                */
#define OMAP24XX_GFX_RST_MASK				(1 << 0)

/*                            */
#define OMAP24XX_GFX_SW_RST_MASK			(1 << 4)

/*                               */

/*                            */
/*                                      */

/*                               */

/*                               */

/*                             */
/*                                                                          */
#define OMAP24XX_EXTWMPU_RST_MASK			(1 << 6)
#define OMAP24XX_SECU_WD_RST_MASK			(1 << 5)
#define OMAP24XX_MPU_WD_RST_MASK			(1 << 4)
#define OMAP24XX_SECU_VIOL_RST_MASK			(1 << 3)

/*                            */

/*                            */

/*                */
#define OMAP2420_RST_IVA_MASK				(1 << 8)
#define OMAP24XX_RST2_DSP_MASK				(1 << 1)
#define OMAP24XX_RST1_DSP_MASK				(1 << 0)

/*                            */
/*                                            */
#define OMAP2420_IVA_SW_RST_MASK			(1 << 8)
#define OMAP24XX_DSP_SW_RST2_MASK			(1 << 5)
#define OMAP24XX_DSP_SW_RST1_MASK			(1 << 4)

/*                            */

/*                               */
/*                                    */
#define OMAP2420_MEMIONSTATE_SHIFT			12
#define OMAP2420_MEMIONSTATE_MASK			(0x3 << 12)
#define OMAP2420_MEMIRETSTATE_MASK			(1 << 4)

/*                             */
/*                         */
#define OMAP2420_MEMISTATEST_SHIFT			12
#define OMAP2420_MEMISTATEST_MASK			(0x3 << 12)

/*                                  */

/*                                  */

/*                */
/*           */
#define OMAP2430_PWRON1_MDM_MASK			(1 << 1)
#define OMAP2430_RST1_MDM_MASK				(1 << 0)

/*                            */
/*           */
#define OMAP2430_MDM_SECU_VIOL_MASK			(1 << 6)
#define OMAP2430_MDM_SW_PWRON1_MASK			(1 << 5)
#define OMAP2430_MDM_SW_RST1_MASK			(1 << 4)

/*             */
/*           */
#define OMAP2430_PM_WKEN_MDM_EN_MDM_MASK		(1 << 0)

/*                           */
/*           */

/*                            */
/*           */

/*                               */
/*           */
#define OMAP2430_KILLDOMAINWKUP_MASK			(1 << 19)

/*                             */
/*           */

/*                    */
/*           */

/*                    */
/*           */

#endif
