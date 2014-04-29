/* Copyright (c) 2011, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __ASM_ARCH_MSM_IRQS_8930_H
#define __ASM_ARCH_MSM_IRQS_8930_H

/*                            */

/*                                                         
                                             
                                             */

#define GIC_PPI_START 16
#define GIC_SPI_START 32

#define INT_VGIC				(GIC_PPI_START + 0)
#define INT_DEBUG_TIMER_EXP			(GIC_PPI_START + 1)
#define INT_GP_TIMER_EXP			(GIC_PPI_START + 2)
#define INT_GP_TIMER2_EXP			(GIC_PPI_START + 3)
#define WDT0_ACCSCSSNBARK_INT			(GIC_PPI_START + 4)
#define WDT1_ACCSCSSNBARK_INT			(GIC_PPI_START + 5)
#define AVS_SVICINT				(GIC_PPI_START + 6)
#define AVS_SVICINTSWDONE			(GIC_PPI_START + 7)
#define CPU_DBGCPUXCOMMRXFULL			(GIC_PPI_START + 8)
#define CPU_DBGCPUXCOMMTXEMPTY			(GIC_PPI_START + 9)
#define INT_ARMQC_PERFMON			(GIC_PPI_START + 10)
#define SC_AVSCPUXDOWN				(GIC_PPI_START + 11)
#define SC_AVSCPUXUP				(GIC_PPI_START + 12)
#define SC_SICCPUXACGIRPTREQ			(GIC_PPI_START + 13)
#define SC_SICCPUXEXTFAULTIRPTREQ		(GIC_PPI_START + 14)
/*                  */

#define APCC_QGICACGIRPTREQ			(GIC_SPI_START + 0)
#define APCC_QGICL2PERFMONIRPTREQ		(GIC_SPI_START + 1)
#define SC_SICL2PERFMONIRPTREQ			APCC_QGICL2PERFMONIRPTREQ
#define APCC_QGICL2IRPTREQ			(GIC_SPI_START + 2)
#define APCC_QGICMPUIRPTREQ			(GIC_SPI_START + 3)
#define TLMM_MSM_DIR_CONN_IRQ_0			(GIC_SPI_START + 4)
#define TLMM_MSM_DIR_CONN_IRQ_1			(GIC_SPI_START + 5)
#define TLMM_MSM_DIR_CONN_IRQ_2			(GIC_SPI_START + 6)
#define TLMM_MSM_DIR_CONN_IRQ_3			(GIC_SPI_START + 7)
#define TLMM_MSM_DIR_CONN_IRQ_4			(GIC_SPI_START + 8)
#define TLMM_MSM_DIR_CONN_IRQ_5			(GIC_SPI_START + 9)
#define TLMM_MSM_DIR_CONN_IRQ_6			(GIC_SPI_START + 10)
#define TLMM_MSM_DIR_CONN_IRQ_7			(GIC_SPI_START + 11)
#define TLMM_MSM_DIR_CONN_IRQ_8			(GIC_SPI_START + 12)
#define TLMM_MSM_DIR_CONN_IRQ_9			(GIC_SPI_START + 13)
#define PM8921_SEC_IRQ_103			(GIC_SPI_START + 14)
#define PM8018_SEC_IRQ_106			(GIC_SPI_START + 15)
#define TLMM_MSM_SUMMARY_IRQ			(GIC_SPI_START + 16)
#define SPDM_RT_1_IRQ				(GIC_SPI_START + 17)
#define SPDM_DIAG_IRQ				(GIC_SPI_START + 18)
#define RPM_APCC_CPU0_GP_HIGH_IRQ		(GIC_SPI_START + 19)
#define RPM_APCC_CPU0_GP_MEDIUM_IRQ		(GIC_SPI_START + 20)
#define RPM_APCC_CPU0_GP_LOW_IRQ		(GIC_SPI_START + 21)
#define RPM_APCC_CPU0_WAKE_UP_IRQ		(GIC_SPI_START + 22)
#define RPM_APCC_CPU1_GP_HIGH_IRQ		(GIC_SPI_START + 23)
#define RPM_APCC_CPU1_GP_MEDIUM_IRQ		(GIC_SPI_START + 24)
#define RPM_APCC_CPU1_GP_LOW_IRQ		(GIC_SPI_START + 25)
#define RPM_APCC_CPU1_WAKE_UP_IRQ		(GIC_SPI_START + 26)
#define SSBI2_2_SC_CPU0_SECURE_IRQ		(GIC_SPI_START + 27)
#define SSBI2_2_SC_CPU0_NON_SECURE_IRQ		(GIC_SPI_START + 28)
#define SSBI2_1_SC_CPU0_SECURE_IRQ		(GIC_SPI_START + 29)
#define SSBI2_1_SC_CPU0_NON_SECURE_IRQ		(GIC_SPI_START + 30)
#define MSMC_SC_SEC_CE_IRQ			(GIC_SPI_START + 31)
#define MSMC_SC_PRI_CE_IRQ			(GIC_SPI_START + 32)
#define SLIMBUS0_CORE_EE1_IRQ			(GIC_SPI_START + 33)
#define SLIMBUS0_BAM_EE1_IRQ			(GIC_SPI_START + 34)
#define Q6FW_WDOG_EXPIRED_IRQ			(GIC_SPI_START + 35)
#define Q6SW_WDOG_EXPIRED_IRQ			(GIC_SPI_START + 36)
#define MSS_TO_APPS_IRQ_0			(GIC_SPI_START + 37)
#define MSS_TO_APPS_IRQ_1			(GIC_SPI_START + 38)
#define MSS_TO_APPS_IRQ_2			(GIC_SPI_START + 39)
#define MSS_TO_APPS_IRQ_3			(GIC_SPI_START + 40)
#define MSS_TO_APPS_IRQ_4			(GIC_SPI_START + 41)
#define MSS_TO_APPS_IRQ_5			(GIC_SPI_START + 42)
#define MSS_TO_APPS_IRQ_6			(GIC_SPI_START + 43)
#define MSS_TO_APPS_IRQ_7			(GIC_SPI_START + 44)
#define MSS_TO_APPS_IRQ_8			(GIC_SPI_START + 45)
#define MSS_TO_APPS_IRQ_9			(GIC_SPI_START + 46)
#define VPE_IRQ					(GIC_SPI_START + 47)
#define VFE_IRQ					(GIC_SPI_START + 48)
#define VCODEC_IRQ				(GIC_SPI_START + 49)
/*                      */
#define SMMU_VPE_CB_SC_SECURE_IRQ		(GIC_SPI_START + 51)
#define SMMU_VPE_CB_SC_NON_SECURE_IRQ		(GIC_SPI_START + 52)
#define SMMU_VFE_CB_SC_SECURE_IRQ		(GIC_SPI_START + 53)
#define SMMU_VFE_CB_SC_NON_SECURE_IRQ		(GIC_SPI_START + 54)
#define SMMU_VCODEC_B_CB_SC_SECURE_IRQ		(GIC_SPI_START + 55)
#define SMMU_VCODEC_B_CB_SC_NON_SECURE_IRQ	(GIC_SPI_START + 56)
#define SMMU_VCODEC_A_CB_SC_SECURE_IRQ		(GIC_SPI_START + 57)
#define SMMU_VCODEC_A_CB_SC_NON_SECURE_IRQ	(GIC_SPI_START + 58)
#define SMMU_ROT_CB_SC_SECURE_IRQ		(GIC_SPI_START + 59)
#define SMMU_ROT_CB_SC_NON_SECURE_IRQ		(GIC_SPI_START + 60)
#define SMMU_MDP1_CB_SC_SECURE_IRQ		(GIC_SPI_START + 61)
#define SMMU_MDP1_CB_SC_NON_SECURE_IRQ		(GIC_SPI_START + 62)
#define SMMU_MDP0_CB_SC_SECURE_IRQ		(GIC_SPI_START + 63)
#define SMMU_MDP0_CB_SC_NON_SECURE_IRQ		(GIC_SPI_START + 64)
/*                      */
/*                      */
#define SMMU_IJPEG_CB_SC_SECURE_IRQ		(GIC_SPI_START + 67)
#define SMMU_IJPEG_CB_SC_NON_SECURE_IRQ		(GIC_SPI_START + 68)
#define SMMU_GFX3D_CB_SC_SECURE_IRQ		(GIC_SPI_START + 69)
#define SMMU_GFX3D_CB_SC_NON_SECURE_IRQ		(GIC_SPI_START + 70)
/*                      */
/*                      */
#define ROT_IRQ					(GIC_SPI_START + 73)
#define MMSS_FABRIC_IRQ				(GIC_SPI_START + 74)
#define MDP_IRQ					(GIC_SPI_START + 75)
/*                      */
#define JPEG_IRQ				(GIC_SPI_START + 77)
#define MMSS_IMEM_IRQ				(GIC_SPI_START + 78)
#define HDMI_IRQ				(GIC_SPI_START + 79)
#define GFX3D_IRQ				(GIC_SPI_START + 80)
/*                      */
#define DSI1_IRQ				(GIC_SPI_START + 82)
#define CSI_1_IRQ				(GIC_SPI_START + 83)
#define CSI_0_IRQ				(GIC_SPI_START + 84)
#define LPASS_SCSS_AUDIO_IF_OUT0_IRQ		(GIC_SPI_START + 85)
#define LPASS_SCSS_MIDI_IRQ			(GIC_SPI_START + 86)
#define LPASS_Q6SS_WDOG_EXPIRED			(GIC_SPI_START + 87)
#define LPASS_SCSS_GP_LOW_IRQ			(GIC_SPI_START + 88)
#define LPASS_SCSS_GP_MEDIUM_IRQ		(GIC_SPI_START + 89)
#define LPASS_SCSS_GP_HIGH_IRQ			(GIC_SPI_START + 90)
#define TOP_IMEM_IRQ				(GIC_SPI_START + 91)
#define FABRIC_SYS_IRQ				(GIC_SPI_START + 92)
#define FABRIC_APPS_IRQ				(GIC_SPI_START + 93)
#define USB1_HS_BAM_IRQ				(GIC_SPI_START + 94)
#define SDC4_BAM_IRQ				(GIC_SPI_START + 95)
#define SDC3_BAM_IRQ				(GIC_SPI_START + 96)
#define SDC2_BAM_IRQ				(GIC_SPI_START + 97)
#define SDC1_BAM_IRQ				(GIC_SPI_START + 98)
#define FABRIC_SPS_IRQ				(GIC_SPI_START + 99)
#define USB1_HS_IRQ				(GIC_SPI_START + 100)
#define SDC4_IRQ_0				(GIC_SPI_START + 101)
#define SDC3_IRQ_0				(GIC_SPI_START + 102)
#define SDC2_IRQ_0				(GIC_SPI_START + 103)
#define SDC1_IRQ_0				(GIC_SPI_START + 104)
#define SPS_BAM_DMA_IRQ				(GIC_SPI_START + 105)
#define SPS_SEC_VIOL_IRQ			(GIC_SPI_START + 106)
#define SPS_MTI_0				(GIC_SPI_START + 107)
#define SPS_MTI_1				(GIC_SPI_START + 108)
#define SPS_MTI_2				(GIC_SPI_START + 109)
#define SPS_MTI_3				(GIC_SPI_START + 110)
#define GPS_PPS_OUT				(GIC_SPI_START + 111)
/*                       */
/*                       */
/*                       */
/*                       */
#define TLMM_MSM_DIR_CONN_IRQ_11		(GIC_SPI_START + 116)
#define TLMM_MSM_DIR_CONN_IRQ_10		(GIC_SPI_START + 117)
#define BAM_DMA1				(GIC_SPI_START + 118)
#define BAM_DMA2				(GIC_SPI_START + 119)
#define SDC1_IRQ				(GIC_SPI_START + 120)
#define SDC2_IRQ				(GIC_SPI_START + 121)
#define SDC3_IRQ				(GIC_SPI_START + 122)
#define SPS_MTI_16				(GIC_SPI_START + 123)
#define SPS_MTI_17				(GIC_SPI_START + 124)
#define SPS_MTI_18				(GIC_SPI_START + 125)
#define SPS_MTI_19				(GIC_SPI_START + 126)
#define SPS_MTI_20				(GIC_SPI_START + 127)
#define SPS_MTI_21				(GIC_SPI_START + 128)
#define SPS_MTI_22				(GIC_SPI_START + 129)
#define SPS_MTI_23				(GIC_SPI_START + 130)
#define SPS_MTI_24				(GIC_SPI_START + 131)
#define SPS_MTI_25				(GIC_SPI_START + 132)
#define SPS_MTI_26				(GIC_SPI_START + 133)
#define SPS_MTI_27				(GIC_SPI_START + 134)
#define SPS_MTI_28				(GIC_SPI_START + 135)
#define SPS_MTI_29				(GIC_SPI_START + 136)
#define SPS_MTI_30				(GIC_SPI_START + 137)
#define SPS_MTI_31				(GIC_SPI_START + 138)
#define CSIPHY_4LN_IRQ				(GIC_SPI_START + 139)
#define MSM8930_CSIPHY_2LN_IRQ			(GIC_SPI_START + 140)
#define USB2_IRQ				(GIC_SPI_START + 141)
#define USB1_IRQ				(GIC_SPI_START + 142)
#define TSSC_SSBI_IRQ				(GIC_SPI_START + 143)
#define TSSC_SAMPLE_IRQ				(GIC_SPI_START + 144)
#define TSSC_PENUP_IRQ				(GIC_SPI_START + 145)
#define MSM8930_GSBI1_UARTDM_IRQ		(GIC_SPI_START + 146)
#define MSM8930_GSBI1_QUP_IRQ			(GIC_SPI_START + 147)
#define MSM8930_GSBI2_UARTDM_IRQ		(GIC_SPI_START + 148)
#define MSM8930_GSBI2_QUP_IRQ		        (GIC_SPI_START + 149)
#define GSBI3_UARTDM_IRQ			(GIC_SPI_START + 150)
#define GSBI3_QUP_IRQ				(GIC_SPI_START + 151)
#define GSBI4_UARTDM_IRQ			(GIC_SPI_START + 152)
#define GSBI4_QUP_IRQ				(GIC_SPI_START + 153)
#define GSBI5_UARTDM_IRQ			(GIC_SPI_START + 154)
#define GSBI5_QUP_IRQ				(GIC_SPI_START + 155)
#define GSBI6_UARTDM_IRQ			(GIC_SPI_START + 156)
#define GSBI6_QUP_IRQ				(GIC_SPI_START + 157)
#define GSBI7_UARTDM_IRQ			(GIC_SPI_START + 158)
#define GSBI7_QUP_IRQ				(GIC_SPI_START + 159)
#define GSBI8_UARTDM_IRQ			(GIC_SPI_START + 160)
#define GSBI8_QUP_IRQ				(GIC_SPI_START + 161)
#define TSIF_TSPP_IRQ				(GIC_SPI_START + 162)
#define TSIF_BAM_IRQ				(GIC_SPI_START + 163)
#define TSIF2_IRQ				(GIC_SPI_START + 164)
#define TSIF1_IRQ				(GIC_SPI_START + 165)
/*                       */
#define ISPIF_IRQ				(GIC_SPI_START + 167)
#define MSMC_SC_SEC_TMR_IRQ			(GIC_SPI_START + 168)
#define MSMC_SC_SEC_WDOG_BARK_IRQ		(GIC_SPI_START + 169)
#define ADM_0_SCSS_0_IRQ			(GIC_SPI_START + 170)
#define ADM_0_SCSS_1_IRQ			(GIC_SPI_START + 171)
#define ADM_0_SCSS_2_IRQ			(GIC_SPI_START + 172)
#define ADM_0_SCSS_3_IRQ			(GIC_SPI_START + 173)
#define CC_SCSS_WDT1CPU1BITEEXPIRED		(GIC_SPI_START + 174)
#define CC_SCSS_WDT1CPU0BITEEXPIRED		(GIC_SPI_START + 175)
#define CC_SCSS_WDT0CPU1BITEEXPIRED		(GIC_SPI_START + 176)
#define CC_SCSS_WDT0CPU0BITEEXPIRED		(GIC_SPI_START + 177)
#define TSENS_UPPER_LOWER_INT			(GIC_SPI_START + 178)
#define SSBI2_2_SC_CPU1_SECURE_INT		(GIC_SPI_START + 179)
#define SSBI2_2_SC_CPU1_NON_SECURE_INT		(GIC_SPI_START + 180)
#define SSBI2_1_SC_CPU1_SECURE_INT		(GIC_SPI_START + 181)
#define SSBI2_1_SC_CPU1_NON_SECURE_INT		(GIC_SPI_START + 182)
#define XPU_SUMMARY_IRQ				(GIC_SPI_START + 183)
#define BUS_EXCEPTION_SUMMARY_IRQ		(GIC_SPI_START + 184)
#define HSDDRX_EBI1CH0_IRQ			(GIC_SPI_START + 185)
/*                       */
#define SDC5_BAM_IRQ				(GIC_SPI_START + 187)
#define SDC5_IRQ_0				(GIC_SPI_START + 188)
#define GSBI9_UARTDM_IRQ			(GIC_SPI_START + 189)
#define GSBI9_QUP_IRQ				(GIC_SPI_START + 190)
#define GSBI10_UARTDM_IRQ			(GIC_SPI_START + 191)
#define GSBI10_QUP_IRQ				(GIC_SPI_START + 192)
#define GSBI11_UARTDM_IRQ			(GIC_SPI_START + 193)
#define GSBI11_QUP_IRQ				(GIC_SPI_START + 194)
#define GSBI12_UARTDM_IRQ			(GIC_SPI_START + 195)
#define GSBI12_QUP_IRQ				(GIC_SPI_START + 196)
#define RIVA_APSS_LTECOEX_IRQ			(GIC_SPI_START + 197)
#define RIVA_APSS_SPARE_IRQ			(GIC_SPI_START + 198)
#define RIVA_APSS_WDOG_BITE_RESET_RDY_IRQ	(GIC_SPI_START + 199)
#define RIVA_APSS_RESET_DONE_IRQ		(GIC_SPI_START + 200)
#define RIVA_APSS_ASIC_IRQ			(GIC_SPI_START + 201)
#define RIVA_APPS_WLAN_RX_DATA_AVAIL_IRQ	(GIC_SPI_START + 202)
#define RIVA_APPS_WLAN_DATA_XFER_DONE_IRQ	(GIC_SPI_START + 203)
#define RIVA_APPS_WLAN_SMSM_IRQ			(GIC_SPI_START + 204)
#define RIVA_APPS_LOG_CTRL_IRQ			(GIC_SPI_START + 205)
#define RIVA_APPS_FM_CTRL_IRQ			(GIC_SPI_START + 206)
#define RIVA_APPS_HCI_IRQ			(GIC_SPI_START + 207)
#define RIVA_APPS_WLAN_CTRL_IRQ			(GIC_SPI_START + 208)
#define A2_BAM_IRQ				(GIC_SPI_START + 209)
/*                       */
/*                       */
/*                       */
#define PPSS_WDOG_TIMER_IRQ			(GIC_SPI_START + 213)
#define SPS_SLIMBUS_CORE_EE0_IRQ		(GIC_SPI_START + 214)
#define SPS_SLIMBUS_BAM_EE0_IRQ			(GIC_SPI_START + 215)
#define QDSS_ETB_IRQ				(GIC_SPI_START + 216)
#define QDSS_CTI2KPSS_CPU1_IRQ			(GIC_SPI_START + 217)
#define QDSS_CTI2KPSS_CPU0_IRQ			(GIC_SPI_START + 218)
#define TLMM_MSM_DIR_CONN_IRQ_16		(GIC_SPI_START + 219)
#define TLMM_MSM_DIR_CONN_IRQ_17		(GIC_SPI_START + 220)
#define TLMM_MSM_DIR_CONN_IRQ_18		(GIC_SPI_START + 221)
#define TLMM_MSM_DIR_CONN_IRQ_19		(GIC_SPI_START + 222)
#define TLMM_MSM_DIR_CONN_IRQ_20		(GIC_SPI_START + 223)
#define TLMM_MSM_DIR_CONN_IRQ_21		(GIC_SPI_START + 224)
#define PM8921_SEC_IRQ_104			(GIC_SPI_START + 225)
#define PM8018_SEC_IRQ_107			(GIC_SPI_START + 226)
#define USB_HSIC_IRQ				(GIC_SPI_START + 229)
#define CE2_BAM_XPU_IRQ				(GIC_SPI_START + 230)
#define CE1_BAM_XPU_IRQ				(GIC_SPI_START + 231)
#define GFX3D_VBIF_IRPT				(GIC_SPI_START + 232)
#define RBIF_IRQ_0				(GIC_SPI_START + 233)
#define RBIF_IRQ_1				(GIC_SPI_START + 234)
#define RBIF_IRQ_2				(GIC_SPI_START + 235)

/*                                  */
#define INT_ADM_AARM				ADM_0_SCSS_0_IRQ

/*                     */
#define INT_A9_M2A_0		(GIC_SPI_START + 37) /*                 */
#define INT_A9_M2A_5		(GIC_SPI_START + 38) /*                 */
#define INT_ADSP_A11		LPASS_SCSS_GP_HIGH_IRQ
#define INT_ADSP_A11_SMSM	LPASS_SCSS_GP_MEDIUM_IRQ
#define INT_DSPS_A11		SPS_MTI_31
#define INT_DSPS_A11_SMSM	SPS_MTI_30
#define INT_WCNSS_A11		RIVA_APSS_SPARE_IRQ
#define INT_WCNSS_A11_SMSM	RIVA_APPS_WLAN_SMSM_IRQ

#endif

