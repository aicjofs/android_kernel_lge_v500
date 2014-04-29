/*
 * wm8400 private definitions.
 *
 * Copyright 2008 Wolfson Microelectronics plc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __LINUX_MFD_WM8400_PRIV_H
#define __LINUX_MFD_WM8400_PRIV_H

#include <linux/mfd/wm8400.h>
#include <linux/mutex.h>
#include <linux/platform_device.h>

struct regmap;

#define WM8400_REGISTER_COUNT 0x55

struct wm8400 {
	struct device *dev;

	struct mutex io_lock;
	struct regmap *regmap;

	u16 reg_cache[WM8400_REGISTER_COUNT];

	struct platform_device regulators[6];
};

/*
                   
 */
#define WM8400_RESET_ID                         0x00
#define WM8400_ID                               0x01
#define WM8400_POWER_MANAGEMENT_1               0x02
#define WM8400_POWER_MANAGEMENT_2               0x03
#define WM8400_POWER_MANAGEMENT_3               0x04
#define WM8400_AUDIO_INTERFACE_1                0x05
#define WM8400_AUDIO_INTERFACE_2                0x06
#define WM8400_CLOCKING_1                       0x07
#define WM8400_CLOCKING_2                       0x08
#define WM8400_AUDIO_INTERFACE_3                0x09
#define WM8400_AUDIO_INTERFACE_4                0x0A
#define WM8400_DAC_CTRL                         0x0B
#define WM8400_LEFT_DAC_DIGITAL_VOLUME          0x0C
#define WM8400_RIGHT_DAC_DIGITAL_VOLUME         0x0D
#define WM8400_DIGITAL_SIDE_TONE                0x0E
#define WM8400_ADC_CTRL                         0x0F
#define WM8400_LEFT_ADC_DIGITAL_VOLUME          0x10
#define WM8400_RIGHT_ADC_DIGITAL_VOLUME         0x11
#define WM8400_GPIO_CTRL_1                      0x12
#define WM8400_GPIO1_GPIO2                      0x13
#define WM8400_GPIO3_GPIO4                      0x14
#define WM8400_GPIO5_GPIO6                      0x15
#define WM8400_GPIOCTRL_2                       0x16
#define WM8400_GPIO_POL                         0x17
#define WM8400_LEFT_LINE_INPUT_1_2_VOLUME       0x18
#define WM8400_LEFT_LINE_INPUT_3_4_VOLUME       0x19
#define WM8400_RIGHT_LINE_INPUT_1_2_VOLUME      0x1A
#define WM8400_RIGHT_LINE_INPUT_3_4_VOLUME      0x1B
#define WM8400_LEFT_OUTPUT_VOLUME               0x1C
#define WM8400_RIGHT_OUTPUT_VOLUME              0x1D
#define WM8400_LINE_OUTPUTS_VOLUME              0x1E
#define WM8400_OUT3_4_VOLUME                    0x1F
#define WM8400_LEFT_OPGA_VOLUME                 0x20
#define WM8400_RIGHT_OPGA_VOLUME                0x21
#define WM8400_SPEAKER_VOLUME                   0x22
#define WM8400_CLASSD1                          0x23
#define WM8400_CLASSD3                          0x25
#define WM8400_INPUT_MIXER1                     0x27
#define WM8400_INPUT_MIXER2                     0x28
#define WM8400_INPUT_MIXER3                     0x29
#define WM8400_INPUT_MIXER4                     0x2A
#define WM8400_INPUT_MIXER5                     0x2B
#define WM8400_INPUT_MIXER6                     0x2C
#define WM8400_OUTPUT_MIXER1                    0x2D
#define WM8400_OUTPUT_MIXER2                    0x2E
#define WM8400_OUTPUT_MIXER3                    0x2F
#define WM8400_OUTPUT_MIXER4                    0x30
#define WM8400_OUTPUT_MIXER5                    0x31
#define WM8400_OUTPUT_MIXER6                    0x32
#define WM8400_OUT3_4_MIXER                     0x33
#define WM8400_LINE_MIXER1                      0x34
#define WM8400_LINE_MIXER2                      0x35
#define WM8400_SPEAKER_MIXER                    0x36
#define WM8400_ADDITIONAL_CONTROL               0x37
#define WM8400_ANTIPOP1                         0x38
#define WM8400_ANTIPOP2                         0x39
#define WM8400_MICBIAS                          0x3A
#define WM8400_FLL_CONTROL_1                    0x3C
#define WM8400_FLL_CONTROL_2                    0x3D
#define WM8400_FLL_CONTROL_3                    0x3E
#define WM8400_FLL_CONTROL_4                    0x3F
#define WM8400_LDO1_CONTROL                     0x41
#define WM8400_LDO2_CONTROL                     0x42
#define WM8400_LDO3_CONTROL                     0x43
#define WM8400_LDO4_CONTROL                     0x44
#define WM8400_DCDC1_CONTROL_1                  0x46
#define WM8400_DCDC1_CONTROL_2                  0x47
#define WM8400_DCDC2_CONTROL_1                  0x48
#define WM8400_DCDC2_CONTROL_2                  0x49
#define WM8400_INTERFACE                        0x4B
#define WM8400_PM_GENERAL                       0x4C
#define WM8400_PM_SHUTDOWN_CONTROL              0x4E
#define WM8400_INTERRUPT_STATUS_1               0x4F
#define WM8400_INTERRUPT_STATUS_1_MASK          0x50
#define WM8400_INTERRUPT_LEVELS                 0x51
#define WM8400_SHUTDOWN_REASON                  0x52
#define WM8400_LINE_CIRCUITS                    0x54

/*
                     
 */

/*
                       
 */
#define WM8400_SW_RESET_CHIP_ID_MASK            0xFFFF  /*                           */
#define WM8400_SW_RESET_CHIP_ID_SHIFT                0  /*                           */
#define WM8400_SW_RESET_CHIP_ID_WIDTH               16  /*                           */

/*
                 
 */
#define WM8400_CHIP_REV_MASK                    0x7000  /*                    */
#define WM8400_CHIP_REV_SHIFT                       12  /*                    */
#define WM8400_CHIP_REV_WIDTH                        3  /*                    */

/*
                           
 */
#define WM8400_IRQ                              0x1000  /*     */
#define WM8400_IRQ_MASK                         0x1000  /*     */
#define WM8400_IRQ_SHIFT                            12  /*     */
#define WM8400_IRQ_WIDTH                             1  /*     */
#define WM8400_TEMPOK                           0x0800  /*        */
#define WM8400_TEMPOK_MASK                      0x0800  /*        */
#define WM8400_TEMPOK_SHIFT                         11  /*        */
#define WM8400_TEMPOK_WIDTH                          1  /*        */
#define WM8400_MIC1SHRT                         0x0400  /*          */
#define WM8400_MIC1SHRT_MASK                    0x0400  /*          */
#define WM8400_MIC1SHRT_SHIFT                       10  /*          */
#define WM8400_MIC1SHRT_WIDTH                        1  /*          */
#define WM8400_MIC1DET                          0x0200  /*         */
#define WM8400_MIC1DET_MASK                     0x0200  /*         */
#define WM8400_MIC1DET_SHIFT                         9  /*         */
#define WM8400_MIC1DET_WIDTH                         1  /*         */
#define WM8400_FLL_LCK                          0x0100  /*         */
#define WM8400_FLL_LCK_MASK                     0x0100  /*         */
#define WM8400_FLL_LCK_SHIFT                         8  /*         */
#define WM8400_FLL_LCK_WIDTH                         1  /*         */
#define WM8400_GPIO_STATUS_MASK                 0x00FF  /*                     */
#define WM8400_GPIO_STATUS_SHIFT                     0  /*                     */
#define WM8400_GPIO_STATUS_WIDTH                     8  /*                     */

/*
                             
 */
#define WM8400_GPIO2_DEB_ENA                    0x8000  /*               */
#define WM8400_GPIO2_DEB_ENA_MASK               0x8000  /*               */
#define WM8400_GPIO2_DEB_ENA_SHIFT                  15  /*               */
#define WM8400_GPIO2_DEB_ENA_WIDTH                   1  /*               */
#define WM8400_GPIO2_IRQ_ENA                    0x4000  /*               */
#define WM8400_GPIO2_IRQ_ENA_MASK               0x4000  /*               */
#define WM8400_GPIO2_IRQ_ENA_SHIFT                  14  /*               */
#define WM8400_GPIO2_IRQ_ENA_WIDTH                   1  /*               */
#define WM8400_GPIO2_PU                         0x2000  /*          */
#define WM8400_GPIO2_PU_MASK                    0x2000  /*          */
#define WM8400_GPIO2_PU_SHIFT                       13  /*          */
#define WM8400_GPIO2_PU_WIDTH                        1  /*          */
#define WM8400_GPIO2_PD                         0x1000  /*          */
#define WM8400_GPIO2_PD_MASK                    0x1000  /*          */
#define WM8400_GPIO2_PD_SHIFT                       12  /*          */
#define WM8400_GPIO2_PD_WIDTH                        1  /*          */
#define WM8400_GPIO2_SEL_MASK                   0x0F00  /*                    */
#define WM8400_GPIO2_SEL_SHIFT                       8  /*                    */
#define WM8400_GPIO2_SEL_WIDTH                       4  /*                    */
#define WM8400_GPIO1_DEB_ENA                    0x0080  /*               */
#define WM8400_GPIO1_DEB_ENA_MASK               0x0080  /*               */
#define WM8400_GPIO1_DEB_ENA_SHIFT                   7  /*               */
#define WM8400_GPIO1_DEB_ENA_WIDTH                   1  /*               */
#define WM8400_GPIO1_IRQ_ENA                    0x0040  /*               */
#define WM8400_GPIO1_IRQ_ENA_MASK               0x0040  /*               */
#define WM8400_GPIO1_IRQ_ENA_SHIFT                   6  /*               */
#define WM8400_GPIO1_IRQ_ENA_WIDTH                   1  /*               */
#define WM8400_GPIO1_PU                         0x0020  /*          */
#define WM8400_GPIO1_PU_MASK                    0x0020  /*          */
#define WM8400_GPIO1_PU_SHIFT                        5  /*          */
#define WM8400_GPIO1_PU_WIDTH                        1  /*          */
#define WM8400_GPIO1_PD                         0x0010  /*          */
#define WM8400_GPIO1_PD_MASK                    0x0010  /*          */
#define WM8400_GPIO1_PD_SHIFT                        4  /*          */
#define WM8400_GPIO1_PD_WIDTH                        1  /*          */
#define WM8400_GPIO1_SEL_MASK                   0x000F  /*                   */
#define WM8400_GPIO1_SEL_SHIFT                       0  /*                   */
#define WM8400_GPIO1_SEL_WIDTH                       4  /*                   */

/*
                             
 */
#define WM8400_GPIO4_DEB_ENA                    0x8000  /*               */
#define WM8400_GPIO4_DEB_ENA_MASK               0x8000  /*               */
#define WM8400_GPIO4_DEB_ENA_SHIFT                  15  /*               */
#define WM8400_GPIO4_DEB_ENA_WIDTH                   1  /*               */
#define WM8400_GPIO4_IRQ_ENA                    0x4000  /*               */
#define WM8400_GPIO4_IRQ_ENA_MASK               0x4000  /*               */
#define WM8400_GPIO4_IRQ_ENA_SHIFT                  14  /*               */
#define WM8400_GPIO4_IRQ_ENA_WIDTH                   1  /*               */
#define WM8400_GPIO4_PU                         0x2000  /*          */
#define WM8400_GPIO4_PU_MASK                    0x2000  /*          */
#define WM8400_GPIO4_PU_SHIFT                       13  /*          */
#define WM8400_GPIO4_PU_WIDTH                        1  /*          */
#define WM8400_GPIO4_PD                         0x1000  /*          */
#define WM8400_GPIO4_PD_MASK                    0x1000  /*          */
#define WM8400_GPIO4_PD_SHIFT                       12  /*          */
#define WM8400_GPIO4_PD_WIDTH                        1  /*          */
#define WM8400_GPIO4_SEL_MASK                   0x0F00  /*                    */
#define WM8400_GPIO4_SEL_SHIFT                       8  /*                    */
#define WM8400_GPIO4_SEL_WIDTH                       4  /*                    */
#define WM8400_GPIO3_DEB_ENA                    0x0080  /*               */
#define WM8400_GPIO3_DEB_ENA_MASK               0x0080  /*               */
#define WM8400_GPIO3_DEB_ENA_SHIFT                   7  /*               */
#define WM8400_GPIO3_DEB_ENA_WIDTH                   1  /*               */
#define WM8400_GPIO3_IRQ_ENA                    0x0040  /*               */
#define WM8400_GPIO3_IRQ_ENA_MASK               0x0040  /*               */
#define WM8400_GPIO3_IRQ_ENA_SHIFT                   6  /*               */
#define WM8400_GPIO3_IRQ_ENA_WIDTH                   1  /*               */
#define WM8400_GPIO3_PU                         0x0020  /*          */
#define WM8400_GPIO3_PU_MASK                    0x0020  /*          */
#define WM8400_GPIO3_PU_SHIFT                        5  /*          */
#define WM8400_GPIO3_PU_WIDTH                        1  /*          */
#define WM8400_GPIO3_PD                         0x0010  /*          */
#define WM8400_GPIO3_PD_MASK                    0x0010  /*          */
#define WM8400_GPIO3_PD_SHIFT                        4  /*          */
#define WM8400_GPIO3_PD_WIDTH                        1  /*          */
#define WM8400_GPIO3_SEL_MASK                   0x000F  /*                   */
#define WM8400_GPIO3_SEL_SHIFT                       0  /*                   */
#define WM8400_GPIO3_SEL_WIDTH                       4  /*                   */

/*
                             
 */
#define WM8400_GPIO6_DEB_ENA                    0x8000  /*               */
#define WM8400_GPIO6_DEB_ENA_MASK               0x8000  /*               */
#define WM8400_GPIO6_DEB_ENA_SHIFT                  15  /*               */
#define WM8400_GPIO6_DEB_ENA_WIDTH                   1  /*               */
#define WM8400_GPIO6_IRQ_ENA                    0x4000  /*               */
#define WM8400_GPIO6_IRQ_ENA_MASK               0x4000  /*               */
#define WM8400_GPIO6_IRQ_ENA_SHIFT                  14  /*               */
#define WM8400_GPIO6_IRQ_ENA_WIDTH                   1  /*               */
#define WM8400_GPIO6_PU                         0x2000  /*          */
#define WM8400_GPIO6_PU_MASK                    0x2000  /*          */
#define WM8400_GPIO6_PU_SHIFT                       13  /*          */
#define WM8400_GPIO6_PU_WIDTH                        1  /*          */
#define WM8400_GPIO6_PD                         0x1000  /*          */
#define WM8400_GPIO6_PD_MASK                    0x1000  /*          */
#define WM8400_GPIO6_PD_SHIFT                       12  /*          */
#define WM8400_GPIO6_PD_WIDTH                        1  /*          */
#define WM8400_GPIO6_SEL_MASK                   0x0F00  /*                    */
#define WM8400_GPIO6_SEL_SHIFT                       8  /*                    */
#define WM8400_GPIO6_SEL_WIDTH                       4  /*                    */
#define WM8400_GPIO5_DEB_ENA                    0x0080  /*               */
#define WM8400_GPIO5_DEB_ENA_MASK               0x0080  /*               */
#define WM8400_GPIO5_DEB_ENA_SHIFT                   7  /*               */
#define WM8400_GPIO5_DEB_ENA_WIDTH                   1  /*               */
#define WM8400_GPIO5_IRQ_ENA                    0x0040  /*               */
#define WM8400_GPIO5_IRQ_ENA_MASK               0x0040  /*               */
#define WM8400_GPIO5_IRQ_ENA_SHIFT                   6  /*               */
#define WM8400_GPIO5_IRQ_ENA_WIDTH                   1  /*               */
#define WM8400_GPIO5_PU                         0x0020  /*          */
#define WM8400_GPIO5_PU_MASK                    0x0020  /*          */
#define WM8400_GPIO5_PU_SHIFT                        5  /*          */
#define WM8400_GPIO5_PU_WIDTH                        1  /*          */
#define WM8400_GPIO5_PD                         0x0010  /*          */
#define WM8400_GPIO5_PD_MASK                    0x0010  /*          */
#define WM8400_GPIO5_PD_SHIFT                        4  /*          */
#define WM8400_GPIO5_PD_WIDTH                        1  /*          */
#define WM8400_GPIO5_SEL_MASK                   0x000F  /*                   */
#define WM8400_GPIO5_SEL_SHIFT                       0  /*                   */
#define WM8400_GPIO5_SEL_WIDTH                       4  /*                   */

/*
                          
 */
#define WM8400_TEMPOK_IRQ_ENA                   0x0800  /*                */
#define WM8400_TEMPOK_IRQ_ENA_MASK              0x0800  /*                */
#define WM8400_TEMPOK_IRQ_ENA_SHIFT                 11  /*                */
#define WM8400_TEMPOK_IRQ_ENA_WIDTH                  1  /*                */
#define WM8400_MIC1SHRT_IRQ_ENA                 0x0400  /*                  */
#define WM8400_MIC1SHRT_IRQ_ENA_MASK            0x0400  /*                  */
#define WM8400_MIC1SHRT_IRQ_ENA_SHIFT               10  /*                  */
#define WM8400_MIC1SHRT_IRQ_ENA_WIDTH                1  /*                  */
#define WM8400_MIC1DET_IRQ_ENA                  0x0200  /*                 */
#define WM8400_MIC1DET_IRQ_ENA_MASK             0x0200  /*                 */
#define WM8400_MIC1DET_IRQ_ENA_SHIFT                 9  /*                 */
#define WM8400_MIC1DET_IRQ_ENA_WIDTH                 1  /*                 */
#define WM8400_FLL_LCK_IRQ_ENA                  0x0100  /*                 */
#define WM8400_FLL_LCK_IRQ_ENA_MASK             0x0100  /*                 */
#define WM8400_FLL_LCK_IRQ_ENA_SHIFT                 8  /*                 */
#define WM8400_FLL_LCK_IRQ_ENA_WIDTH                 1  /*                 */
#define WM8400_GPI8_DEB_ENA                     0x0080  /*              */
#define WM8400_GPI8_DEB_ENA_MASK                0x0080  /*              */
#define WM8400_GPI8_DEB_ENA_SHIFT                    7  /*              */
#define WM8400_GPI8_DEB_ENA_WIDTH                    1  /*              */
#define WM8400_GPI8_IRQ_ENA                     0x0040  /*              */
#define WM8400_GPI8_IRQ_ENA_MASK                0x0040  /*              */
#define WM8400_GPI8_IRQ_ENA_SHIFT                    6  /*              */
#define WM8400_GPI8_IRQ_ENA_WIDTH                    1  /*              */
#define WM8400_GPI8_ENA                         0x0010  /*          */
#define WM8400_GPI8_ENA_MASK                    0x0010  /*          */
#define WM8400_GPI8_ENA_SHIFT                        4  /*          */
#define WM8400_GPI8_ENA_WIDTH                        1  /*          */
#define WM8400_GPI7_DEB_ENA                     0x0008  /*              */
#define WM8400_GPI7_DEB_ENA_MASK                0x0008  /*              */
#define WM8400_GPI7_DEB_ENA_SHIFT                    3  /*              */
#define WM8400_GPI7_DEB_ENA_WIDTH                    1  /*              */
#define WM8400_GPI7_IRQ_ENA                     0x0004  /*              */
#define WM8400_GPI7_IRQ_ENA_MASK                0x0004  /*              */
#define WM8400_GPI7_IRQ_ENA_SHIFT                    2  /*              */
#define WM8400_GPI7_IRQ_ENA_WIDTH                    1  /*              */
#define WM8400_GPI7_ENA                         0x0001  /*          */
#define WM8400_GPI7_ENA_MASK                    0x0001  /*          */
#define WM8400_GPI7_ENA_SHIFT                        0  /*          */
#define WM8400_GPI7_ENA_WIDTH                        1  /*          */

/*
                        
 */
#define WM8400_IRQ_INV                          0x1000  /*         */
#define WM8400_IRQ_INV_MASK                     0x1000  /*         */
#define WM8400_IRQ_INV_SHIFT                        12  /*         */
#define WM8400_IRQ_INV_WIDTH                         1  /*         */
#define WM8400_TEMPOK_POL                       0x0800  /*            */
#define WM8400_TEMPOK_POL_MASK                  0x0800  /*            */
#define WM8400_TEMPOK_POL_SHIFT                     11  /*            */
#define WM8400_TEMPOK_POL_WIDTH                      1  /*            */
#define WM8400_MIC1SHRT_POL                     0x0400  /*              */
#define WM8400_MIC1SHRT_POL_MASK                0x0400  /*              */
#define WM8400_MIC1SHRT_POL_SHIFT                   10  /*              */
#define WM8400_MIC1SHRT_POL_WIDTH                    1  /*              */
#define WM8400_MIC1DET_POL                      0x0200  /*             */
#define WM8400_MIC1DET_POL_MASK                 0x0200  /*             */
#define WM8400_MIC1DET_POL_SHIFT                     9  /*             */
#define WM8400_MIC1DET_POL_WIDTH                     1  /*             */
#define WM8400_FLL_LCK_POL                      0x0100  /*             */
#define WM8400_FLL_LCK_POL_MASK                 0x0100  /*             */
#define WM8400_FLL_LCK_POL_SHIFT                     8  /*             */
#define WM8400_FLL_LCK_POL_WIDTH                     1  /*             */
#define WM8400_GPIO_POL_MASK                    0x00FF  /*                  */
#define WM8400_GPIO_POL_SHIFT                        0  /*                  */
#define WM8400_GPIO_POL_WIDTH                        8  /*                  */

/*
                             
 */
#define WM8400_LDO1_ENA                         0x8000  /*          */
#define WM8400_LDO1_ENA_MASK                    0x8000  /*          */
#define WM8400_LDO1_ENA_SHIFT                       15  /*          */
#define WM8400_LDO1_ENA_WIDTH                        1  /*          */
#define WM8400_LDO1_SWI                         0x4000  /*          */
#define WM8400_LDO1_SWI_MASK                    0x4000  /*          */
#define WM8400_LDO1_SWI_SHIFT                       14  /*          */
#define WM8400_LDO1_SWI_WIDTH                        1  /*          */
#define WM8400_LDO1_OPFLT                       0x1000  /*            */
#define WM8400_LDO1_OPFLT_MASK                  0x1000  /*            */
#define WM8400_LDO1_OPFLT_SHIFT                     12  /*            */
#define WM8400_LDO1_OPFLT_WIDTH                      1  /*            */
#define WM8400_LDO1_ERRACT                      0x0800  /*             */
#define WM8400_LDO1_ERRACT_MASK                 0x0800  /*             */
#define WM8400_LDO1_ERRACT_SHIFT                    11  /*             */
#define WM8400_LDO1_ERRACT_WIDTH                     1  /*             */
#define WM8400_LDO1_HIB_MODE                    0x0400  /*               */
#define WM8400_LDO1_HIB_MODE_MASK               0x0400  /*               */
#define WM8400_LDO1_HIB_MODE_SHIFT                  10  /*               */
#define WM8400_LDO1_HIB_MODE_WIDTH                   1  /*               */
#define WM8400_LDO1_VIMG_MASK                   0x03E0  /*                   */
#define WM8400_LDO1_VIMG_SHIFT                       5  /*                   */
#define WM8400_LDO1_VIMG_WIDTH                       5  /*                   */
#define WM8400_LDO1_VSEL_MASK                   0x001F  /*                   */
#define WM8400_LDO1_VSEL_SHIFT                       0  /*                   */
#define WM8400_LDO1_VSEL_WIDTH                       5  /*                   */

/*
                             
 */
#define WM8400_LDO2_ENA                         0x8000  /*          */
#define WM8400_LDO2_ENA_MASK                    0x8000  /*          */
#define WM8400_LDO2_ENA_SHIFT                       15  /*          */
#define WM8400_LDO2_ENA_WIDTH                        1  /*          */
#define WM8400_LDO2_SWI                         0x4000  /*          */
#define WM8400_LDO2_SWI_MASK                    0x4000  /*          */
#define WM8400_LDO2_SWI_SHIFT                       14  /*          */
#define WM8400_LDO2_SWI_WIDTH                        1  /*          */
#define WM8400_LDO2_OPFLT                       0x1000  /*            */
#define WM8400_LDO2_OPFLT_MASK                  0x1000  /*            */
#define WM8400_LDO2_OPFLT_SHIFT                     12  /*            */
#define WM8400_LDO2_OPFLT_WIDTH                      1  /*            */
#define WM8400_LDO2_ERRACT                      0x0800  /*             */
#define WM8400_LDO2_ERRACT_MASK                 0x0800  /*             */
#define WM8400_LDO2_ERRACT_SHIFT                    11  /*             */
#define WM8400_LDO2_ERRACT_WIDTH                     1  /*             */
#define WM8400_LDO2_HIB_MODE                    0x0400  /*               */
#define WM8400_LDO2_HIB_MODE_MASK               0x0400  /*               */
#define WM8400_LDO2_HIB_MODE_SHIFT                  10  /*               */
#define WM8400_LDO2_HIB_MODE_WIDTH                   1  /*               */
#define WM8400_LDO2_VIMG_MASK                   0x03E0  /*                   */
#define WM8400_LDO2_VIMG_SHIFT                       5  /*                   */
#define WM8400_LDO2_VIMG_WIDTH                       5  /*                   */
#define WM8400_LDO2_VSEL_MASK                   0x001F  /*                   */
#define WM8400_LDO2_VSEL_SHIFT                       0  /*                   */
#define WM8400_LDO2_VSEL_WIDTH                       5  /*                   */

/*
                             
 */
#define WM8400_LDO3_ENA                         0x8000  /*          */
#define WM8400_LDO3_ENA_MASK                    0x8000  /*          */
#define WM8400_LDO3_ENA_SHIFT                       15  /*          */
#define WM8400_LDO3_ENA_WIDTH                        1  /*          */
#define WM8400_LDO3_SWI                         0x4000  /*          */
#define WM8400_LDO3_SWI_MASK                    0x4000  /*          */
#define WM8400_LDO3_SWI_SHIFT                       14  /*          */
#define WM8400_LDO3_SWI_WIDTH                        1  /*          */
#define WM8400_LDO3_OPFLT                       0x1000  /*            */
#define WM8400_LDO3_OPFLT_MASK                  0x1000  /*            */
#define WM8400_LDO3_OPFLT_SHIFT                     12  /*            */
#define WM8400_LDO3_OPFLT_WIDTH                      1  /*            */
#define WM8400_LDO3_ERRACT                      0x0800  /*             */
#define WM8400_LDO3_ERRACT_MASK                 0x0800  /*             */
#define WM8400_LDO3_ERRACT_SHIFT                    11  /*             */
#define WM8400_LDO3_ERRACT_WIDTH                     1  /*             */
#define WM8400_LDO3_HIB_MODE                    0x0400  /*               */
#define WM8400_LDO3_HIB_MODE_MASK               0x0400  /*               */
#define WM8400_LDO3_HIB_MODE_SHIFT                  10  /*               */
#define WM8400_LDO3_HIB_MODE_WIDTH                   1  /*               */
#define WM8400_LDO3_VIMG_MASK                   0x03E0  /*                   */
#define WM8400_LDO3_VIMG_SHIFT                       5  /*                   */
#define WM8400_LDO3_VIMG_WIDTH                       5  /*                   */
#define WM8400_LDO3_VSEL_MASK                   0x001F  /*                   */
#define WM8400_LDO3_VSEL_SHIFT                       0  /*                   */
#define WM8400_LDO3_VSEL_WIDTH                       5  /*                   */

/*
                             
 */
#define WM8400_LDO4_ENA                         0x8000  /*          */
#define WM8400_LDO4_ENA_MASK                    0x8000  /*          */
#define WM8400_LDO4_ENA_SHIFT                       15  /*          */
#define WM8400_LDO4_ENA_WIDTH                        1  /*          */
#define WM8400_LDO4_SWI                         0x4000  /*          */
#define WM8400_LDO4_SWI_MASK                    0x4000  /*          */
#define WM8400_LDO4_SWI_SHIFT                       14  /*          */
#define WM8400_LDO4_SWI_WIDTH                        1  /*          */
#define WM8400_LDO4_OPFLT                       0x1000  /*            */
#define WM8400_LDO4_OPFLT_MASK                  0x1000  /*            */
#define WM8400_LDO4_OPFLT_SHIFT                     12  /*            */
#define WM8400_LDO4_OPFLT_WIDTH                      1  /*            */
#define WM8400_LDO4_ERRACT                      0x0800  /*             */
#define WM8400_LDO4_ERRACT_MASK                 0x0800  /*             */
#define WM8400_LDO4_ERRACT_SHIFT                    11  /*             */
#define WM8400_LDO4_ERRACT_WIDTH                     1  /*             */
#define WM8400_LDO4_HIB_MODE                    0x0400  /*               */
#define WM8400_LDO4_HIB_MODE_MASK               0x0400  /*               */
#define WM8400_LDO4_HIB_MODE_SHIFT                  10  /*               */
#define WM8400_LDO4_HIB_MODE_WIDTH                   1  /*               */
#define WM8400_LDO4_VIMG_MASK                   0x03E0  /*                   */
#define WM8400_LDO4_VIMG_SHIFT                       5  /*                   */
#define WM8400_LDO4_VIMG_WIDTH                       5  /*                   */
#define WM8400_LDO4_VSEL_MASK                   0x001F  /*                   */
#define WM8400_LDO4_VSEL_SHIFT                       0  /*                   */
#define WM8400_LDO4_VSEL_WIDTH                       5  /*                   */

/*
                               
 */
#define WM8400_DC1_ENA                          0x8000  /*         */
#define WM8400_DC1_ENA_MASK                     0x8000  /*         */
#define WM8400_DC1_ENA_SHIFT                        15  /*         */
#define WM8400_DC1_ENA_WIDTH                         1  /*         */
#define WM8400_DC1_ACTIVE                       0x4000  /*            */
#define WM8400_DC1_ACTIVE_MASK                  0x4000  /*            */
#define WM8400_DC1_ACTIVE_SHIFT                     14  /*            */
#define WM8400_DC1_ACTIVE_WIDTH                      1  /*            */
#define WM8400_DC1_SLEEP                        0x2000  /*           */
#define WM8400_DC1_SLEEP_MASK                   0x2000  /*           */
#define WM8400_DC1_SLEEP_SHIFT                      13  /*           */
#define WM8400_DC1_SLEEP_WIDTH                       1  /*           */
#define WM8400_DC1_OPFLT                        0x1000  /*           */
#define WM8400_DC1_OPFLT_MASK                   0x1000  /*           */
#define WM8400_DC1_OPFLT_SHIFT                      12  /*           */
#define WM8400_DC1_OPFLT_WIDTH                       1  /*           */
#define WM8400_DC1_ERRACT                       0x0800  /*            */
#define WM8400_DC1_ERRACT_MASK                  0x0800  /*            */
#define WM8400_DC1_ERRACT_SHIFT                     11  /*            */
#define WM8400_DC1_ERRACT_WIDTH                      1  /*            */
#define WM8400_DC1_HIB_MODE                     0x0400  /*              */
#define WM8400_DC1_HIB_MODE_MASK                0x0400  /*              */
#define WM8400_DC1_HIB_MODE_SHIFT                   10  /*              */
#define WM8400_DC1_HIB_MODE_WIDTH                    1  /*              */
#define WM8400_DC1_SOFTST_MASK                  0x0300  /*                    */
#define WM8400_DC1_SOFTST_SHIFT                      8  /*                    */
#define WM8400_DC1_SOFTST_WIDTH                      2  /*                    */
#define WM8400_DC1_OV_PROT                      0x0080  /*             */
#define WM8400_DC1_OV_PROT_MASK                 0x0080  /*             */
#define WM8400_DC1_OV_PROT_SHIFT                     7  /*             */
#define WM8400_DC1_OV_PROT_WIDTH                     1  /*             */
#define WM8400_DC1_VSEL_MASK                    0x007F  /*                  */
#define WM8400_DC1_VSEL_SHIFT                        0  /*                  */
#define WM8400_DC1_VSEL_WIDTH                        7  /*                  */

/*
                               
 */
#define WM8400_DC1_FRC_PWM                      0x2000  /*             */
#define WM8400_DC1_FRC_PWM_MASK                 0x2000  /*             */
#define WM8400_DC1_FRC_PWM_SHIFT                    13  /*             */
#define WM8400_DC1_FRC_PWM_WIDTH                     1  /*             */
#define WM8400_DC1_STBY_LIM_MASK                0x0300  /*                      */
#define WM8400_DC1_STBY_LIM_SHIFT                    8  /*                      */
#define WM8400_DC1_STBY_LIM_WIDTH                    2  /*                      */
#define WM8400_DC1_ACT_LIM                      0x0080  /*             */
#define WM8400_DC1_ACT_LIM_MASK                 0x0080  /*             */
#define WM8400_DC1_ACT_LIM_SHIFT                     7  /*             */
#define WM8400_DC1_ACT_LIM_WIDTH                     1  /*             */
#define WM8400_DC1_VIMG_MASK                    0x007F  /*                  */
#define WM8400_DC1_VIMG_SHIFT                        0  /*                  */
#define WM8400_DC1_VIMG_WIDTH                        7  /*                  */

/*
                               
 */
#define WM8400_DC2_ENA                          0x8000  /*         */
#define WM8400_DC2_ENA_MASK                     0x8000  /*         */
#define WM8400_DC2_ENA_SHIFT                        15  /*         */
#define WM8400_DC2_ENA_WIDTH                         1  /*         */
#define WM8400_DC2_ACTIVE                       0x4000  /*            */
#define WM8400_DC2_ACTIVE_MASK                  0x4000  /*            */
#define WM8400_DC2_ACTIVE_SHIFT                     14  /*            */
#define WM8400_DC2_ACTIVE_WIDTH                      1  /*            */
#define WM8400_DC2_SLEEP                        0x2000  /*           */
#define WM8400_DC2_SLEEP_MASK                   0x2000  /*           */
#define WM8400_DC2_SLEEP_SHIFT                      13  /*           */
#define WM8400_DC2_SLEEP_WIDTH                       1  /*           */
#define WM8400_DC2_OPFLT                        0x1000  /*           */
#define WM8400_DC2_OPFLT_MASK                   0x1000  /*           */
#define WM8400_DC2_OPFLT_SHIFT                      12  /*           */
#define WM8400_DC2_OPFLT_WIDTH                       1  /*           */
#define WM8400_DC2_ERRACT                       0x0800  /*            */
#define WM8400_DC2_ERRACT_MASK                  0x0800  /*            */
#define WM8400_DC2_ERRACT_SHIFT                     11  /*            */
#define WM8400_DC2_ERRACT_WIDTH                      1  /*            */
#define WM8400_DC2_HIB_MODE                     0x0400  /*              */
#define WM8400_DC2_HIB_MODE_MASK                0x0400  /*              */
#define WM8400_DC2_HIB_MODE_SHIFT                   10  /*              */
#define WM8400_DC2_HIB_MODE_WIDTH                    1  /*              */
#define WM8400_DC2_SOFTST_MASK                  0x0300  /*                    */
#define WM8400_DC2_SOFTST_SHIFT                      8  /*                    */
#define WM8400_DC2_SOFTST_WIDTH                      2  /*                    */
#define WM8400_DC2_OV_PROT                      0x0080  /*             */
#define WM8400_DC2_OV_PROT_MASK                 0x0080  /*             */
#define WM8400_DC2_OV_PROT_SHIFT                     7  /*             */
#define WM8400_DC2_OV_PROT_WIDTH                     1  /*             */
#define WM8400_DC2_VSEL_MASK                    0x007F  /*                  */
#define WM8400_DC2_VSEL_SHIFT                        0  /*                  */
#define WM8400_DC2_VSEL_WIDTH                        7  /*                  */

/*
                               
 */
#define WM8400_DC2_FRC_PWM                      0x2000  /*             */
#define WM8400_DC2_FRC_PWM_MASK                 0x2000  /*             */
#define WM8400_DC2_FRC_PWM_SHIFT                    13  /*             */
#define WM8400_DC2_FRC_PWM_WIDTH                     1  /*             */
#define WM8400_DC2_STBY_LIM_MASK                0x0300  /*                      */
#define WM8400_DC2_STBY_LIM_SHIFT                    8  /*                      */
#define WM8400_DC2_STBY_LIM_WIDTH                    2  /*                      */
#define WM8400_DC2_ACT_LIM                      0x0080  /*             */
#define WM8400_DC2_ACT_LIM_MASK                 0x0080  /*             */
#define WM8400_DC2_ACT_LIM_SHIFT                     7  /*             */
#define WM8400_DC2_ACT_LIM_WIDTH                     1  /*             */
#define WM8400_DC2_VIMG_MASK                    0x007F  /*                  */
#define WM8400_DC2_VIMG_SHIFT                        0  /*                  */
#define WM8400_DC2_VIMG_WIDTH                        7  /*                  */

/*
                         
 */
#define WM8400_AUTOINC                          0x0008  /*         */
#define WM8400_AUTOINC_MASK                     0x0008  /*         */
#define WM8400_AUTOINC_SHIFT                         3  /*         */
#define WM8400_AUTOINC_WIDTH                         1  /*         */
#define WM8400_ARA_ENA                          0x0004  /*         */
#define WM8400_ARA_ENA_MASK                     0x0004  /*         */
#define WM8400_ARA_ENA_SHIFT                         2  /*         */
#define WM8400_ARA_ENA_WIDTH                         1  /*         */
#define WM8400_SPI_CFG                          0x0002  /*         */
#define WM8400_SPI_CFG_MASK                     0x0002  /*         */
#define WM8400_SPI_CFG_SHIFT                         1  /*         */
#define WM8400_SPI_CFG_WIDTH                         1  /*         */

/*
                          
 */
#define WM8400_CODEC_SOFTST                     0x8000  /*              */
#define WM8400_CODEC_SOFTST_MASK                0x8000  /*              */
#define WM8400_CODEC_SOFTST_SHIFT                   15  /*              */
#define WM8400_CODEC_SOFTST_WIDTH                    1  /*              */
#define WM8400_CODEC_SOFTSD                     0x4000  /*              */
#define WM8400_CODEC_SOFTSD_MASK                0x4000  /*              */
#define WM8400_CODEC_SOFTSD_SHIFT                   14  /*              */
#define WM8400_CODEC_SOFTSD_WIDTH                    1  /*              */
#define WM8400_CHIP_SOFTSD                      0x2000  /*             */
#define WM8400_CHIP_SOFTSD_MASK                 0x2000  /*             */
#define WM8400_CHIP_SOFTSD_SHIFT                    13  /*             */
#define WM8400_CHIP_SOFTSD_WIDTH                     1  /*             */
#define WM8400_DSLEEP1_POL                      0x0008  /*             */
#define WM8400_DSLEEP1_POL_MASK                 0x0008  /*             */
#define WM8400_DSLEEP1_POL_SHIFT                     3  /*             */
#define WM8400_DSLEEP1_POL_WIDTH                     1  /*             */
#define WM8400_DSLEEP2_POL                      0x0004  /*             */
#define WM8400_DSLEEP2_POL_MASK                 0x0004  /*             */
#define WM8400_DSLEEP2_POL_SHIFT                     2  /*             */
#define WM8400_DSLEEP2_POL_WIDTH                     1  /*             */
#define WM8400_PWR_STATE_MASK                   0x0003  /*                   */
#define WM8400_PWR_STATE_SHIFT                       0  /*                   */
#define WM8400_PWR_STATE_WIDTH                       2  /*                   */

/*
                                   
 */
#define WM8400_CHIP_GT150_ERRACT                0x0200  /*                   */
#define WM8400_CHIP_GT150_ERRACT_MASK           0x0200  /*                   */
#define WM8400_CHIP_GT150_ERRACT_SHIFT               9  /*                   */
#define WM8400_CHIP_GT150_ERRACT_WIDTH               1  /*                   */
#define WM8400_CHIP_GT115_ERRACT                0x0100  /*                   */
#define WM8400_CHIP_GT115_ERRACT_MASK           0x0100  /*                   */
#define WM8400_CHIP_GT115_ERRACT_SHIFT               8  /*                   */
#define WM8400_CHIP_GT115_ERRACT_WIDTH               1  /*                   */
#define WM8400_LINE_CMP_ERRACT                  0x0080  /*                 */
#define WM8400_LINE_CMP_ERRACT_MASK             0x0080  /*                 */
#define WM8400_LINE_CMP_ERRACT_SHIFT                 7  /*                 */
#define WM8400_LINE_CMP_ERRACT_WIDTH                 1  /*                 */
#define WM8400_UVLO_ERRACT                      0x0040  /*             */
#define WM8400_UVLO_ERRACT_MASK                 0x0040  /*             */
#define WM8400_UVLO_ERRACT_SHIFT                     6  /*             */
#define WM8400_UVLO_ERRACT_WIDTH                     1  /*             */

/*
                                  
 */
#define WM8400_MICD_CINT                        0x8000  /*           */
#define WM8400_MICD_CINT_MASK                   0x8000  /*           */
#define WM8400_MICD_CINT_SHIFT                      15  /*           */
#define WM8400_MICD_CINT_WIDTH                       1  /*           */
#define WM8400_MICSCD_CINT                      0x4000  /*             */
#define WM8400_MICSCD_CINT_MASK                 0x4000  /*             */
#define WM8400_MICSCD_CINT_SHIFT                    14  /*             */
#define WM8400_MICSCD_CINT_WIDTH                     1  /*             */
#define WM8400_JDL_CINT                         0x2000  /*          */
#define WM8400_JDL_CINT_MASK                    0x2000  /*          */
#define WM8400_JDL_CINT_SHIFT                       13  /*          */
#define WM8400_JDL_CINT_WIDTH                        1  /*          */
#define WM8400_JDR_CINT                         0x1000  /*          */
#define WM8400_JDR_CINT_MASK                    0x1000  /*          */
#define WM8400_JDR_CINT_SHIFT                       12  /*          */
#define WM8400_JDR_CINT_WIDTH                        1  /*          */
#define WM8400_CODEC_SEQ_END_EINT               0x0800  /*                    */
#define WM8400_CODEC_SEQ_END_EINT_MASK          0x0800  /*                    */
#define WM8400_CODEC_SEQ_END_EINT_SHIFT             11  /*                    */
#define WM8400_CODEC_SEQ_END_EINT_WIDTH              1  /*                    */
#define WM8400_CDEL_TO_EINT                     0x0400  /*              */
#define WM8400_CDEL_TO_EINT_MASK                0x0400  /*              */
#define WM8400_CDEL_TO_EINT_SHIFT                   10  /*              */
#define WM8400_CDEL_TO_EINT_WIDTH                    1  /*              */
#define WM8400_CHIP_GT150_EINT                  0x0200  /*                 */
#define WM8400_CHIP_GT150_EINT_MASK             0x0200  /*                 */
#define WM8400_CHIP_GT150_EINT_SHIFT                 9  /*                 */
#define WM8400_CHIP_GT150_EINT_WIDTH                 1  /*                 */
#define WM8400_CHIP_GT115_EINT                  0x0100  /*                 */
#define WM8400_CHIP_GT115_EINT_MASK             0x0100  /*                 */
#define WM8400_CHIP_GT115_EINT_SHIFT                 8  /*                 */
#define WM8400_CHIP_GT115_EINT_WIDTH                 1  /*                 */
#define WM8400_LINE_CMP_EINT                    0x0080  /*               */
#define WM8400_LINE_CMP_EINT_MASK               0x0080  /*               */
#define WM8400_LINE_CMP_EINT_SHIFT                   7  /*               */
#define WM8400_LINE_CMP_EINT_WIDTH                   1  /*               */
#define WM8400_UVLO_EINT                        0x0040  /*           */
#define WM8400_UVLO_EINT_MASK                   0x0040  /*           */
#define WM8400_UVLO_EINT_SHIFT                       6  /*           */
#define WM8400_UVLO_EINT_WIDTH                       1  /*           */
#define WM8400_DC2_UV_EINT                      0x0020  /*             */
#define WM8400_DC2_UV_EINT_MASK                 0x0020  /*             */
#define WM8400_DC2_UV_EINT_SHIFT                     5  /*             */
#define WM8400_DC2_UV_EINT_WIDTH                     1  /*             */
#define WM8400_DC1_UV_EINT                      0x0010  /*             */
#define WM8400_DC1_UV_EINT_MASK                 0x0010  /*             */
#define WM8400_DC1_UV_EINT_SHIFT                     4  /*             */
#define WM8400_DC1_UV_EINT_WIDTH                     1  /*             */
#define WM8400_LDO4_UV_EINT                     0x0008  /*              */
#define WM8400_LDO4_UV_EINT_MASK                0x0008  /*              */
#define WM8400_LDO4_UV_EINT_SHIFT                    3  /*              */
#define WM8400_LDO4_UV_EINT_WIDTH                    1  /*              */
#define WM8400_LDO3_UV_EINT                     0x0004  /*              */
#define WM8400_LDO3_UV_EINT_MASK                0x0004  /*              */
#define WM8400_LDO3_UV_EINT_SHIFT                    2  /*              */
#define WM8400_LDO3_UV_EINT_WIDTH                    1  /*              */
#define WM8400_LDO2_UV_EINT                     0x0002  /*              */
#define WM8400_LDO2_UV_EINT_MASK                0x0002  /*              */
#define WM8400_LDO2_UV_EINT_SHIFT                    1  /*              */
#define WM8400_LDO2_UV_EINT_WIDTH                    1  /*              */
#define WM8400_LDO1_UV_EINT                     0x0001  /*              */
#define WM8400_LDO1_UV_EINT_MASK                0x0001  /*              */
#define WM8400_LDO1_UV_EINT_SHIFT                    0  /*              */
#define WM8400_LDO1_UV_EINT_WIDTH                    1  /*              */

/*
                                       
 */
#define WM8400_IM_MICD_CINT                     0x8000  /*              */
#define WM8400_IM_MICD_CINT_MASK                0x8000  /*              */
#define WM8400_IM_MICD_CINT_SHIFT                   15  /*              */
#define WM8400_IM_MICD_CINT_WIDTH                    1  /*              */
#define WM8400_IM_MICSCD_CINT                   0x4000  /*                */
#define WM8400_IM_MICSCD_CINT_MASK              0x4000  /*                */
#define WM8400_IM_MICSCD_CINT_SHIFT                 14  /*                */
#define WM8400_IM_MICSCD_CINT_WIDTH                  1  /*                */
#define WM8400_IM_JDL_CINT                      0x2000  /*             */
#define WM8400_IM_JDL_CINT_MASK                 0x2000  /*             */
#define WM8400_IM_JDL_CINT_SHIFT                    13  /*             */
#define WM8400_IM_JDL_CINT_WIDTH                     1  /*             */
#define WM8400_IM_JDR_CINT                      0x1000  /*             */
#define WM8400_IM_JDR_CINT_MASK                 0x1000  /*             */
#define WM8400_IM_JDR_CINT_SHIFT                    12  /*             */
#define WM8400_IM_JDR_CINT_WIDTH                     1  /*             */
#define WM8400_IM_CODEC_SEQ_END_EINT            0x0800  /*                       */
#define WM8400_IM_CODEC_SEQ_END_EINT_MASK       0x0800  /*                       */
#define WM8400_IM_CODEC_SEQ_END_EINT_SHIFT          11  /*                       */
#define WM8400_IM_CODEC_SEQ_END_EINT_WIDTH           1  /*                       */
#define WM8400_IM_CDEL_TO_EINT                  0x0400  /*                 */
#define WM8400_IM_CDEL_TO_EINT_MASK             0x0400  /*                 */
#define WM8400_IM_CDEL_TO_EINT_SHIFT                10  /*                 */
#define WM8400_IM_CDEL_TO_EINT_WIDTH                 1  /*                 */
#define WM8400_IM_CHIP_GT150_EINT               0x0200  /*                    */
#define WM8400_IM_CHIP_GT150_EINT_MASK          0x0200  /*                    */
#define WM8400_IM_CHIP_GT150_EINT_SHIFT              9  /*                    */
#define WM8400_IM_CHIP_GT150_EINT_WIDTH              1  /*                    */
#define WM8400_IM_CHIP_GT115_EINT               0x0100  /*                    */
#define WM8400_IM_CHIP_GT115_EINT_MASK          0x0100  /*                    */
#define WM8400_IM_CHIP_GT115_EINT_SHIFT              8  /*                    */
#define WM8400_IM_CHIP_GT115_EINT_WIDTH              1  /*                    */
#define WM8400_IM_LINE_CMP_EINT                 0x0080  /*                  */
#define WM8400_IM_LINE_CMP_EINT_MASK            0x0080  /*                  */
#define WM8400_IM_LINE_CMP_EINT_SHIFT                7  /*                  */
#define WM8400_IM_LINE_CMP_EINT_WIDTH                1  /*                  */
#define WM8400_IM_UVLO_EINT                     0x0040  /*              */
#define WM8400_IM_UVLO_EINT_MASK                0x0040  /*              */
#define WM8400_IM_UVLO_EINT_SHIFT                    6  /*              */
#define WM8400_IM_UVLO_EINT_WIDTH                    1  /*              */
#define WM8400_IM_DC2_UV_EINT                   0x0020  /*                */
#define WM8400_IM_DC2_UV_EINT_MASK              0x0020  /*                */
#define WM8400_IM_DC2_UV_EINT_SHIFT                  5  /*                */
#define WM8400_IM_DC2_UV_EINT_WIDTH                  1  /*                */
#define WM8400_IM_DC1_UV_EINT                   0x0010  /*                */
#define WM8400_IM_DC1_UV_EINT_MASK              0x0010  /*                */
#define WM8400_IM_DC1_UV_EINT_SHIFT                  4  /*                */
#define WM8400_IM_DC1_UV_EINT_WIDTH                  1  /*                */
#define WM8400_IM_LDO4_UV_EINT                  0x0008  /*                 */
#define WM8400_IM_LDO4_UV_EINT_MASK             0x0008  /*                 */
#define WM8400_IM_LDO4_UV_EINT_SHIFT                 3  /*                 */
#define WM8400_IM_LDO4_UV_EINT_WIDTH                 1  /*                 */
#define WM8400_IM_LDO3_UV_EINT                  0x0004  /*                 */
#define WM8400_IM_LDO3_UV_EINT_MASK             0x0004  /*                 */
#define WM8400_IM_LDO3_UV_EINT_SHIFT                 2  /*                 */
#define WM8400_IM_LDO3_UV_EINT_WIDTH                 1  /*                 */
#define WM8400_IM_LDO2_UV_EINT                  0x0002  /*                 */
#define WM8400_IM_LDO2_UV_EINT_MASK             0x0002  /*                 */
#define WM8400_IM_LDO2_UV_EINT_SHIFT                 1  /*                 */
#define WM8400_IM_LDO2_UV_EINT_WIDTH                 1  /*                 */
#define WM8400_IM_LDO1_UV_EINT                  0x0001  /*                 */
#define WM8400_IM_LDO1_UV_EINT_MASK             0x0001  /*                 */
#define WM8400_IM_LDO1_UV_EINT_SHIFT                 0  /*                 */
#define WM8400_IM_LDO1_UV_EINT_WIDTH                 1  /*                 */

/*
                                
 */
#define WM8400_MICD_LVL                         0x8000  /*          */
#define WM8400_MICD_LVL_MASK                    0x8000  /*          */
#define WM8400_MICD_LVL_SHIFT                       15  /*          */
#define WM8400_MICD_LVL_WIDTH                        1  /*          */
#define WM8400_MICSCD_LVL                       0x4000  /*            */
#define WM8400_MICSCD_LVL_MASK                  0x4000  /*            */
#define WM8400_MICSCD_LVL_SHIFT                     14  /*            */
#define WM8400_MICSCD_LVL_WIDTH                      1  /*            */
#define WM8400_JDL_LVL                          0x2000  /*         */
#define WM8400_JDL_LVL_MASK                     0x2000  /*         */
#define WM8400_JDL_LVL_SHIFT                        13  /*         */
#define WM8400_JDL_LVL_WIDTH                         1  /*         */
#define WM8400_JDR_LVL                          0x1000  /*         */
#define WM8400_JDR_LVL_MASK                     0x1000  /*         */
#define WM8400_JDR_LVL_SHIFT                        12  /*         */
#define WM8400_JDR_LVL_WIDTH                         1  /*         */
#define WM8400_CODEC_SEQ_END_LVL                0x0800  /*                   */
#define WM8400_CODEC_SEQ_END_LVL_MASK           0x0800  /*                   */
#define WM8400_CODEC_SEQ_END_LVL_SHIFT              11  /*                   */
#define WM8400_CODEC_SEQ_END_LVL_WIDTH               1  /*                   */
#define WM8400_CDEL_TO_LVL                      0x0400  /*             */
#define WM8400_CDEL_TO_LVL_MASK                 0x0400  /*             */
#define WM8400_CDEL_TO_LVL_SHIFT                    10  /*             */
#define WM8400_CDEL_TO_LVL_WIDTH                     1  /*             */
#define WM8400_CHIP_GT150_LVL                   0x0200  /*                */
#define WM8400_CHIP_GT150_LVL_MASK              0x0200  /*                */
#define WM8400_CHIP_GT150_LVL_SHIFT                  9  /*                */
#define WM8400_CHIP_GT150_LVL_WIDTH                  1  /*                */
#define WM8400_CHIP_GT115_LVL                   0x0100  /*                */
#define WM8400_CHIP_GT115_LVL_MASK              0x0100  /*                */
#define WM8400_CHIP_GT115_LVL_SHIFT                  8  /*                */
#define WM8400_CHIP_GT115_LVL_WIDTH                  1  /*                */
#define WM8400_LINE_CMP_LVL                     0x0080  /*              */
#define WM8400_LINE_CMP_LVL_MASK                0x0080  /*              */
#define WM8400_LINE_CMP_LVL_SHIFT                    7  /*              */
#define WM8400_LINE_CMP_LVL_WIDTH                    1  /*              */
#define WM8400_UVLO_LVL                         0x0040  /*          */
#define WM8400_UVLO_LVL_MASK                    0x0040  /*          */
#define WM8400_UVLO_LVL_SHIFT                        6  /*          */
#define WM8400_UVLO_LVL_WIDTH                        1  /*          */
#define WM8400_DC2_UV_LVL                       0x0020  /*            */
#define WM8400_DC2_UV_LVL_MASK                  0x0020  /*            */
#define WM8400_DC2_UV_LVL_SHIFT                      5  /*            */
#define WM8400_DC2_UV_LVL_WIDTH                      1  /*            */
#define WM8400_DC1_UV_LVL                       0x0010  /*            */
#define WM8400_DC1_UV_LVL_MASK                  0x0010  /*            */
#define WM8400_DC1_UV_LVL_SHIFT                      4  /*            */
#define WM8400_DC1_UV_LVL_WIDTH                      1  /*            */
#define WM8400_LDO4_UV_LVL                      0x0008  /*             */
#define WM8400_LDO4_UV_LVL_MASK                 0x0008  /*             */
#define WM8400_LDO4_UV_LVL_SHIFT                     3  /*             */
#define WM8400_LDO4_UV_LVL_WIDTH                     1  /*             */
#define WM8400_LDO3_UV_LVL                      0x0004  /*             */
#define WM8400_LDO3_UV_LVL_MASK                 0x0004  /*             */
#define WM8400_LDO3_UV_LVL_SHIFT                     2  /*             */
#define WM8400_LDO3_UV_LVL_WIDTH                     1  /*             */
#define WM8400_LDO2_UV_LVL                      0x0002  /*             */
#define WM8400_LDO2_UV_LVL_MASK                 0x0002  /*             */
#define WM8400_LDO2_UV_LVL_SHIFT                     1  /*             */
#define WM8400_LDO2_UV_LVL_WIDTH                     1  /*             */
#define WM8400_LDO1_UV_LVL                      0x0001  /*             */
#define WM8400_LDO1_UV_LVL_MASK                 0x0001  /*             */
#define WM8400_LDO1_UV_LVL_SHIFT                     0  /*             */
#define WM8400_LDO1_UV_LVL_WIDTH                     1  /*             */

/*
                               
 */
#define WM8400_SDR_CHIP_SOFTSD                  0x2000  /*                 */
#define WM8400_SDR_CHIP_SOFTSD_MASK             0x2000  /*                 */
#define WM8400_SDR_CHIP_SOFTSD_SHIFT                13  /*                 */
#define WM8400_SDR_CHIP_SOFTSD_WIDTH                 1  /*                 */
#define WM8400_SDR_NPDN                         0x0800  /*          */
#define WM8400_SDR_NPDN_MASK                    0x0800  /*          */
#define WM8400_SDR_NPDN_SHIFT                       11  /*          */
#define WM8400_SDR_NPDN_WIDTH                        1  /*          */
#define WM8400_SDR_CHIP_GT150                   0x0200  /*                */
#define WM8400_SDR_CHIP_GT150_MASK              0x0200  /*                */
#define WM8400_SDR_CHIP_GT150_SHIFT                  9  /*                */
#define WM8400_SDR_CHIP_GT150_WIDTH                  1  /*                */
#define WM8400_SDR_CHIP_GT115                   0x0100  /*                */
#define WM8400_SDR_CHIP_GT115_MASK              0x0100  /*                */
#define WM8400_SDR_CHIP_GT115_SHIFT                  8  /*                */
#define WM8400_SDR_CHIP_GT115_WIDTH                  1  /*                */
#define WM8400_SDR_LINE_CMP                     0x0080  /*              */
#define WM8400_SDR_LINE_CMP_MASK                0x0080  /*              */
#define WM8400_SDR_LINE_CMP_SHIFT                    7  /*              */
#define WM8400_SDR_LINE_CMP_WIDTH                    1  /*              */
#define WM8400_SDR_UVLO                         0x0040  /*          */
#define WM8400_SDR_UVLO_MASK                    0x0040  /*          */
#define WM8400_SDR_UVLO_SHIFT                        6  /*          */
#define WM8400_SDR_UVLO_WIDTH                        1  /*          */
#define WM8400_SDR_DC2_UV                       0x0020  /*            */
#define WM8400_SDR_DC2_UV_MASK                  0x0020  /*            */
#define WM8400_SDR_DC2_UV_SHIFT                      5  /*            */
#define WM8400_SDR_DC2_UV_WIDTH                      1  /*            */
#define WM8400_SDR_DC1_UV                       0x0010  /*            */
#define WM8400_SDR_DC1_UV_MASK                  0x0010  /*            */
#define WM8400_SDR_DC1_UV_SHIFT                      4  /*            */
#define WM8400_SDR_DC1_UV_WIDTH                      1  /*            */
#define WM8400_SDR_LDO4_UV                      0x0008  /*             */
#define WM8400_SDR_LDO4_UV_MASK                 0x0008  /*             */
#define WM8400_SDR_LDO4_UV_SHIFT                     3  /*             */
#define WM8400_SDR_LDO4_UV_WIDTH                     1  /*             */
#define WM8400_SDR_LDO3_UV                      0x0004  /*             */
#define WM8400_SDR_LDO3_UV_MASK                 0x0004  /*             */
#define WM8400_SDR_LDO3_UV_SHIFT                     2  /*             */
#define WM8400_SDR_LDO3_UV_WIDTH                     1  /*             */
#define WM8400_SDR_LDO2_UV                      0x0002  /*             */
#define WM8400_SDR_LDO2_UV_MASK                 0x0002  /*             */
#define WM8400_SDR_LDO2_UV_SHIFT                     1  /*             */
#define WM8400_SDR_LDO2_UV_WIDTH                     1  /*             */
#define WM8400_SDR_LDO1_UV                      0x0001  /*             */
#define WM8400_SDR_LDO1_UV_MASK                 0x0001  /*             */
#define WM8400_SDR_LDO1_UV_SHIFT                     0  /*             */
#define WM8400_SDR_LDO1_UV_WIDTH                     1  /*             */

/*
                             
 */
#define WM8400_BG_LINE_COMP                     0x8000  /*              */
#define WM8400_BG_LINE_COMP_MASK                0x8000  /*              */
#define WM8400_BG_LINE_COMP_SHIFT                   15  /*              */
#define WM8400_BG_LINE_COMP_WIDTH                    1  /*              */
#define WM8400_LINE_CMP_VTHI_MASK               0x00F0  /*                       */
#define WM8400_LINE_CMP_VTHI_SHIFT                   4  /*                       */
#define WM8400_LINE_CMP_VTHI_WIDTH                   4  /*                       */
#define WM8400_LINE_CMP_VTHD_MASK               0x000F  /*                       */
#define WM8400_LINE_CMP_VTHD_SHIFT                   0  /*                       */
#define WM8400_LINE_CMP_VTHD_WIDTH                   4  /*                       */

u16 wm8400_reg_read(struct wm8400 *wm8400, u8 reg);
int wm8400_block_read(struct wm8400 *wm8400, u8 reg, int count, u16 *data);
int wm8400_set_bits(struct wm8400 *wm8400, u8 reg, u16 mask, u16 val);

#endif
