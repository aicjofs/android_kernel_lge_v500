/*
 * Copyright (c) 2011, The Linux Foundation. All rights reserved.
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

#ifndef __ARCH_ARM_MACH_MSM_INCLUDE_MACH_RPM_REGULATOR_8960_H
#define __ARCH_ARM_MACH_MSM_INCLUDE_MACH_RPM_REGULATOR_8960_H

/*                            */
#define RPM_VREG_PIN_CTRL_PM8921_D1	0x01
#define RPM_VREG_PIN_CTRL_PM8921_A0	0x02
#define RPM_VREG_PIN_CTRL_PM8921_A1	0x04
#define RPM_VREG_PIN_CTRL_PM8921_A2	0x08

/* 
                                                                 
                                                                          
                                          
                                       
                                                                         
             
                                                                        
                                                                   
                                 
                                                                        
                                         
                          
  
                                                                              
                                                                           
                             
 */
enum rpm_vreg_pin_fn_8960 {
	RPM_VREG_PIN_FN_8960_DONT_CARE,
	RPM_VREG_PIN_FN_8960_ENABLE,
	RPM_VREG_PIN_FN_8960_MODE,
	RPM_VREG_PIN_FN_8960_SLEEP_B,
	RPM_VREG_PIN_FN_8960_NONE,
};

/* 
                                                                   
                                                              
                                                        
                                                           
                                                                          
                                             
                                    
                  
                                                            
                                                                           
                                          
                                          
  
                                                                           
                           
 */
enum rpm_vreg_force_mode_8960 {
	RPM_VREG_FORCE_MODE_8960_PIN_CTRL = 0,
	RPM_VREG_FORCE_MODE_8960_NONE = 0,
	RPM_VREG_FORCE_MODE_8960_LPM,
	RPM_VREG_FORCE_MODE_8960_AUTO,		/*           */
	RPM_VREG_FORCE_MODE_8960_HPM,
	RPM_VREG_FORCE_MODE_8960_BYPASS,	/*          */
};

/* 
                                                                 
                                                                             
                               
                                                                      
                         
 */
enum rpm_vreg_power_mode_8960 {
	RPM_VREG_POWER_MODE_8960_HYSTERETIC,
	RPM_VREG_POWER_MODE_8960_PWM,
};

/* 
                                                                          
 */
enum rpm_vreg_id_8960 {
	RPM_VREG_ID_PM8921_L1,
	RPM_VREG_ID_PM8921_L2,
	RPM_VREG_ID_PM8921_L3,
	RPM_VREG_ID_PM8921_L4,
	RPM_VREG_ID_PM8921_L5,
	RPM_VREG_ID_PM8921_L6,
	RPM_VREG_ID_PM8921_L7,
	RPM_VREG_ID_PM8921_L8,
	RPM_VREG_ID_PM8921_L9,
	RPM_VREG_ID_PM8921_L10,
	RPM_VREG_ID_PM8921_L11,
	RPM_VREG_ID_PM8921_L12,
	RPM_VREG_ID_PM8921_L13,
	RPM_VREG_ID_PM8921_L14,
	RPM_VREG_ID_PM8921_L15,
	RPM_VREG_ID_PM8921_L16,
	RPM_VREG_ID_PM8921_L17,
	RPM_VREG_ID_PM8921_L18,
	RPM_VREG_ID_PM8921_L21,
	RPM_VREG_ID_PM8921_L22,
	RPM_VREG_ID_PM8921_L23,
	RPM_VREG_ID_PM8921_L24,
	RPM_VREG_ID_PM8921_L25,
	RPM_VREG_ID_PM8921_L26,
	RPM_VREG_ID_PM8921_L27,
	RPM_VREG_ID_PM8921_L28,
	RPM_VREG_ID_PM8921_L29,
	RPM_VREG_ID_PM8921_S1,
	RPM_VREG_ID_PM8921_S2,
	RPM_VREG_ID_PM8921_S3,
	RPM_VREG_ID_PM8921_S4,
	RPM_VREG_ID_PM8921_S5,
	RPM_VREG_ID_PM8921_S6,
	RPM_VREG_ID_PM8921_S7,
	RPM_VREG_ID_PM8921_S8,
	RPM_VREG_ID_PM8921_LVS1,
	RPM_VREG_ID_PM8921_LVS2,
	RPM_VREG_ID_PM8921_LVS3,
	RPM_VREG_ID_PM8921_LVS4,
	RPM_VREG_ID_PM8921_LVS5,
	RPM_VREG_ID_PM8921_LVS6,
	RPM_VREG_ID_PM8921_LVS7,
	RPM_VREG_ID_PM8921_USB_OTG,
	RPM_VREG_ID_PM8921_HDMI_MVS,
	RPM_VREG_ID_PM8921_NCP,
	RPM_VREG_ID_PM8921_MAX_REAL = RPM_VREG_ID_PM8921_NCP,

	/*                                                                    */
	RPM_VREG_ID_PM8921_L1_PC,
	RPM_VREG_ID_PM8921_L2_PC,
	RPM_VREG_ID_PM8921_L3_PC,
	RPM_VREG_ID_PM8921_L4_PC,
	RPM_VREG_ID_PM8921_L5_PC,
	RPM_VREG_ID_PM8921_L6_PC,
	RPM_VREG_ID_PM8921_L7_PC,
	RPM_VREG_ID_PM8921_L8_PC,
	RPM_VREG_ID_PM8921_L9_PC,
	RPM_VREG_ID_PM8921_L10_PC,
	RPM_VREG_ID_PM8921_L11_PC,
	RPM_VREG_ID_PM8921_L12_PC,
	RPM_VREG_ID_PM8921_L14_PC,
	RPM_VREG_ID_PM8921_L15_PC,
	RPM_VREG_ID_PM8921_L16_PC,
	RPM_VREG_ID_PM8921_L17_PC,
	RPM_VREG_ID_PM8921_L18_PC,
	RPM_VREG_ID_PM8921_L21_PC,
	RPM_VREG_ID_PM8921_L22_PC,
	RPM_VREG_ID_PM8921_L23_PC,

	RPM_VREG_ID_PM8921_L29_PC,
	RPM_VREG_ID_PM8921_S1_PC,
	RPM_VREG_ID_PM8921_S2_PC,
	RPM_VREG_ID_PM8921_S3_PC,
	RPM_VREG_ID_PM8921_S4_PC,

	RPM_VREG_ID_PM8921_S7_PC,
	RPM_VREG_ID_PM8921_S8_PC,
	RPM_VREG_ID_PM8921_LVS1_PC,

	RPM_VREG_ID_PM8921_LVS3_PC,
	RPM_VREG_ID_PM8921_LVS4_PC,
	RPM_VREG_ID_PM8921_LVS5_PC,
	RPM_VREG_ID_PM8921_LVS6_PC,
	RPM_VREG_ID_PM8921_LVS7_PC,

	RPM_VREG_ID_PM8921_MAX = RPM_VREG_ID_PM8921_LVS7_PC,
};

/*                                      */
#define RPM_VREG_8960_LDO_5_HPM_MIN_LOAD		0
#define RPM_VREG_8960_LDO_50_HPM_MIN_LOAD		5000
#define RPM_VREG_8960_LDO_150_HPM_MIN_LOAD		10000
#define RPM_VREG_8960_LDO_300_HPM_MIN_LOAD		10000
#define RPM_VREG_8960_LDO_600_HPM_MIN_LOAD		10000
#define RPM_VREG_8960_LDO_1200_HPM_MIN_LOAD		10000
#define RPM_VREG_8960_SMPS_1500_HPM_MIN_LOAD		100000
#define RPM_VREG_8960_SMPS_2000_HPM_MIN_LOAD		100000

#endif
