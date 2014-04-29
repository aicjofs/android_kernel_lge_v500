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
 *
 */


#include "qs_s5k4e1.h"

struct qs_s5k4e1_i2c_reg_conf qs_s5k4e1_prev_settings_3d[] = {
	{0x0100, 0x00},
	/*            */
	{0x0340, 0x04},
	{0x0341, 0x90},
	/*           */
	{0x0342, 0x0A},
	{0x0343, 0xB2},
	{0x3030, 0x06},
	{0x3017, 0xA4},
	{0x301B, 0x88},
	{0x30BC, 0x90},
	{0x301C, 0x04},
	{0x0202, 0x04},
	{0x0203, 0x12},
	{0x0204, 0x00},
	{0x0205, 0x80},
	{0x0306, 0x00},
	{0x0307, 0x60},
	{0x30B5, 0x01},
	{0x30E2, 0x02},/*                  */
	{0x30F1, 0x60},
/*                 */
	{0x30A9, 0x02},
	{0x300E, 0xE8},
	{0x0387, 0x01},
	{0x0344, 0x01},
	{0x0345, 0x18},
	{0x0348, 0x09},
	{0x0349, 0x17},
	{0x0346, 0x01},
	{0x0347, 0x94},
	{0x034A, 0x06},
	{0x034B, 0x13},
	{0x0380, 0x00},
	{0x0381, 0x01},
	{0x0382, 0x00},
	{0x0383, 0x01},
	{0x0384, 0x00},
	{0x0385, 0x01},
	{0x0386, 0x00},
	{0x0387, 0x01},
	{0x034C, 0x04},
	{0x034D, 0x00},
	{0x034E, 0x04},
	{0x034F, 0x80},
	{0x30BF, 0xAA},
	{0x30C0, 0x40},
	{0x30C8, 0x04},
	{0x30C9, 0x00},
};

struct qs_s5k4e1_i2c_reg_conf qs_s5k4e1_prev_settings_2d[] = {
	{0x0100, 0x00},
	{0x0340, 0x03},
	{0x0341, 0xe0},
	{0x0342, 0x0A},
	{0x0343, 0xB2},
	{0x3030, 0x06},
	{0x301B, 0x83},
	{0x30BC, 0x98},
	{0x301C, 0x04},
	{0x0202, 0x01},
	{0x0203, 0xFD},
	{0x0204, 0x00},
	{0x0205, 0x80},
	{0x0306, 0x00},
	{0x0307, 0x64},
	{0x30B5, 0x00},
	{0x30E2, 0x01},/*                  */
	{0x30F1, 0xd0},
	{0x30A9, 0x02},
	{0x300E, 0xEB},
	{0x0387, 0x03},
	{0x0344, 0x00},
	{0x0345, 0x00},
	{0x0348, 0x0A},
	{0x0349, 0x2F},
	{0x0346, 0x00},
	{0x0347, 0x00},
	{0x034A, 0x07},
	{0x034B, 0xA7},
	{0x0380, 0x00},
	{0x0381, 0x01},
	{0x0382, 0x00},
	{0x0383, 0x01},
	{0x0384, 0x00},
	{0x0385, 0x01},
	{0x0386, 0x00},
	{0x0387, 0x03},
	{0x034C, 0x05},
	{0x034D, 0x10},
	{0x034E, 0x03},
	{0x034F, 0xd4},
	{0x30BF, 0xAB},
	{0x30C0, 0xc0},
	{0x30C8, 0x06},
	{0x30C9, 0x54},
};

struct qs_s5k4e1_i2c_reg_conf qs_s5k4e1_snap_settings_2d[] = {
	{0x0100, 0x00},
	{0x0340, 0x07},
	{0x0341, 0xb4},
	{0x0342, 0x0A},
	{0x0343, 0xB2},
	{0x3030, 0x06}, /*                  */
	{0x300E, 0xE8},
	{0x301B, 0x75},
	{0x301C, 0x04},
	{0x30BC, 0x98},
	{0x0202, 0x04},
	{0x0203, 0x12},
	{0x0204, 0x00},
	{0x0205, 0x80},
	{0x0306, 0x00},
	{0x0307, 0x64},
	{0x30B5, 0x00},
	{0x30E2, 0x01},/*                  */
	{0x30F1, 0xd0},
	{0x30A9, 0x03},/*                      */
	{0x300E, 0xE8},/*                    */
	{0x0387, 0x01},/*         */
	{0x034C, 0x0A},/*             */
	{0x034D, 0x30},
	{0x034E, 0x07},/*             */
	{0x034F, 0xA8},
	{0x30BF, 0xAB},/*                                                  */
	{0x30C0, 0x86},/*                         */
	{0x30C8, 0x0C},/*                                    */
	{0x30C9, 0xBC},

};

struct qs_s5k4e1_i2c_reg_conf qs_s5k4e1_snap_settings_3d[] = {
	{0x0100, 0x00},

/*             */
	{0x0340, 0x09},
	{0x0341, 0x20},
/*            */
	{0x0342, 0x0A},
	{0x0343, 0xB2},
	{0x3030, 0x06},/*                  */
/*              */
	{0x3017, 0xA4},
	{0x301B, 0x88},
	{0x30BC, 0x90},
	{0x301C, 0x04},
/*                        */
	{0x0202, 0x04},
	{0x0203, 0x12},
	{0x0204, 0x00},
	{0x0205, 0x80},
/*               */
	{0x0306, 0x00},
	{0x0307, 0x60},
	{0x30B5, 0x01},
	{0x30E2, 0x02},/*                  */
	{0x30F1, 0x60},
/*                 */
	{0x30A9, 0x01},
	{0x300E, 0xE8},
	{0x0387, 0x01},
	{0x0344, 0x01},/*            */
	{0x0345, 0x14},
	{0x0348, 0x09},/*          */
	{0x0349, 0x17},
	{0x0346, 0x01},/*            */
	{0x0347, 0x94},
	{0x034A, 0x06},/*          */
	{0x034B, 0x13},
	{0x0380, 0x00},/*            */
	{0x0381, 0x01},
	{0x0382, 0x00},/*           */
	{0x0383, 0x01},
	{0x0384, 0x00},/*            */
	{0x0385, 0x01},
	{0x0386, 0x00},/*           */
	{0x0387, 0x01},
	{0x034C, 0x08},/*             */
	{0x034D, 0x00},
	{0x034E, 0x04},/*             */
	{0x034F, 0x80},
	{0x30BF, 0xAA},/*                                                 */
	{0x30C0, 0x80},/*                 */
	{0x30C8, 0x08},/*                 */
	{0x30C9, 0x00},

};

struct qs_s5k4e1_i2c_reg_conf qs_s5k4e1_recommend_settings[] = {
	{0x0100, 0x00},

	{0x3030, 0x06},/*              */
/*              */
	{0x3000, 0x05},
	{0x3001, 0x03},
	{0x3002, 0x08},
	{0x3003, 0x09},
	{0x3004, 0x2E},
	{0x3005, 0x06},
	{0x3006, 0x34},
	{0x3007, 0x00},
	{0x3008, 0x3C},
	{0x3009, 0x3C},
	{0x300A, 0x28},
	{0x300B, 0x04},
	{0x300C, 0x0A},
	{0x300D, 0x02},
	{0x300F, 0x82},
	{0x3010, 0x00},
	{0x3011, 0x4C},
	{0x3012, 0x30},
	{0x3013, 0xC0},
	{0x3014, 0x00},
	{0x3015, 0x00},
	{0x3016, 0x2C},
	{0x3017, 0x94},
	{0x3018, 0x78},
	{0x301D, 0xD4},
	{0x3021, 0x02},
	{0x3022, 0x24},
	{0x3024, 0x40},
	{0x3027, 0x08},
	{0x3029, 0xC6},
	{0x302B, 0x01},
	{0x30D8, 0x3F},
/*                 */
	{0x3070, 0x5F},
	{0x3071, 0x00},
	{0x3080, 0x04},
	{0x3081, 0x38},

/*            */
	{0x30BD, 0x00},/*          */
	{0x3084, 0x15},/*         */
	{0x30BE, 0x1A},/*                                  */
	{0x30C1, 0x01},/*                     */
	{0x30EE, 0x02},/*               */
	{0x3111, 0x86},/*                     */
/*              */
	{0x30E3, 0x38},
	{0x30E4, 0x40},
	{0x3113, 0x70},
	{0x3114, 0x80},
	{0x3115, 0x7B},
	{0x3116, 0xC0},
	{0x30EE, 0x12},

/*               */
	{0x0305, 0x06},
};
static struct qs_s5k4e1_i2c_reg_conf qs_s5k4e1_default_lenshading_settings[] = {

	{0x3200, 0x00},
	{0x3201, 0x9a},
	{0x3202, 0x56},
	{0x3203, 0xf },
	{0x3204, 0xd8},
	{0x3205, 0x94},
	{0x3206, 0x0 },
	{0x3207, 0x10},
	{0x3208, 0x71},
	{0x3209, 0x0 },
	{0x320a, 0x9 },
	{0x320b, 0xc1},
	{0x320c, 0xf },
	{0x320d, 0xf1},
	{0x320e, 0x3d},
	{0x320f, 0x0 },
	{0x3210, 0xa },
	{0x3211, 0x93},
	{0x3212, 0xf },
	{0x3213, 0xc9},
	{0x3214, 0xa1},
	{0x3215, 0x0 },
	{0x3216, 0x10},
	{0x3217, 0x89},
	{0x3218, 0xf },
	{0x3219, 0xfb},
	{0x321a, 0xf3},
	{0x321b, 0xf },
	{0x321c, 0xf8},
	{0x321d, 0xfc},
	{0x321e, 0x0 },
	{0x321f, 0x4 },
	{0x3220, 0xe3},
	{0x3221, 0xf },
	{0x3222, 0xfe},
	{0x3223, 0x94},
	{0x3224, 0x0 },
	{0x3225, 0x24},
	{0x3226, 0x59},
	{0x3227, 0xf },
	{0x3228, 0xe9},
	{0x3229, 0x68},
	{0x322a, 0xf },
	{0x322b, 0xfa},
	{0x322c, 0x7f},
	{0x322d, 0x0 },
	{0x322e, 0x13},
	{0x322f, 0xe1},
	{0x3230, 0x0 },
	{0x3231, 0x3 },
	{0x3232, 0xbc},
	{0x3233, 0xf },
	{0x3234, 0xf0},
	{0x3235, 0xa1},
	{0x3236, 0xf },
	{0x3237, 0xf4},
	{0x3238, 0xc9},
	{0x3239, 0x0 },
	{0x323a, 0x11},
	{0x323b, 0x4b},
	{0x323c, 0x0 },
	{0x323d, 0x12},
	{0x323e, 0xc5},
	{0x323f, 0xf },
	{0x3240, 0xe3},
	{0x3241, 0xb },
	{0x3242, 0xf },
	{0x3243, 0xf8},
	{0x3244, 0x4f},
	{0x3245, 0x0 },
	{0x3246, 0x13},
	{0x3247, 0xac},
	{0x3248, 0x0 },
	{0x3249, 0x0 },
	{0x324a, 0x7c},
	{0x324b, 0xf },
	{0x324c, 0xfe},
	{0x324d, 0xdd},
	{0x324e, 0xf },
	{0x324f, 0xf2},
	{0x3250, 0x96},
	{0x3251, 0x0 },
	{0x3252, 0x8 },
	{0x3253, 0xef},
	{0x3254, 0x0 },
	{0x3255, 0x6 },
	{0x3256, 0xa4},
	{0x3257, 0x0 },
	{0x3258, 0x2 },
	{0x3259, 0x4b},
	{0x325a, 0x0 },
	{0x325b, 0x6 },
	{0x325c, 0x85},
	{0x325d, 0xf },
	{0x325e, 0xf8},
	{0x325f, 0x6a},
	{0x3260, 0xf },
	{0x3261, 0xfd},
	{0x3262, 0x70},
	{0x3263, 0x0 },
	{0x3264, 0xd },
	{0x3265, 0xa9},
	{0x3266, 0xf },
	{0x3267, 0xfd},
	{0x3268, 0xf8},
	{0x3269, 0xf },
	{0x326a, 0xec},
	{0x326b, 0xfc},
	{0x326c, 0x0 },
	{0x326d, 0xa7},
	{0x326e, 0x5 },
	{0x326f, 0xf },
	{0x3270, 0xd6},
	{0x3271, 0x19},
	{0x3272, 0x0 },
	{0x3273, 0xa },
	{0x3274, 0xe8},
	{0x3275, 0x0 },
	{0x3276, 0x17},
	{0x3277, 0x1 },
	{0x3278, 0xf },
	{0x3279, 0xe7},
	{0x327a, 0xa0},
	{0x327b, 0x0 },
	{0x327c, 0xb },
	{0x327d, 0xc3},
	{0x327e, 0xf },
	{0x327f, 0xc0},
	{0x3280, 0xe3},
	{0x3281, 0x0 },
	{0x3282, 0x15},
	{0x3283, 0x5a},
	{0x3284, 0xf },
	{0x3285, 0xf9},
	{0x3286, 0xa0},
	{0x3287, 0xf },
	{0x3288, 0xf4},
	{0x3289, 0xce},
	{0x328a, 0x0 },
	{0x328b, 0xb },
	{0x328c, 0x72},
	{0x328d, 0xf },
	{0x328e, 0xfb},
	{0x328f, 0xb5},
	{0x3290, 0x0 },
	{0x3291, 0x2f},
	{0x3292, 0xb },
	{0x3293, 0xf },
	{0x3294, 0xde},
	{0x3295, 0xc0},
	{0x3296, 0x0 },
	{0x3297, 0x0 },
	{0x3298, 0x58},
	{0x3299, 0x0 },
	{0x329a, 0x1b},
	{0x329b, 0x5 },
	{0x329c, 0xf },
	{0x329d, 0xf9},
	{0x329e, 0x23},
	{0x329f, 0xf },
	{0x32a0, 0xf3},
	{0x32a1, 0x94},
	{0x32a2, 0xf },
	{0x32a3, 0xe7},
	{0x32a4, 0xc2},
	{0x32a5, 0x0 },
	{0x32a6, 0x1d},
	{0x32a7, 0xe5},
	{0x32a8, 0x0 },
	{0x32a9, 0x5 },
	{0x32aa, 0xaf},
	{0x32ab, 0xf },
	{0x32ac, 0xe3},
	{0x32ad, 0xb7},
	{0x32ae, 0xf },
	{0x32af, 0xf8},
	{0x32b0, 0x34},
	{0x32b1, 0x0 },
	{0x32b2, 0x1c},
	{0x32b3, 0x3d},
	{0x32b4, 0x0 },
	{0x32b5, 0x10},
	{0x32b6, 0x4a},
	{0x32b7, 0xf },
	{0x32b8, 0xfa},
	{0x32b9, 0x7 },
	{0x32ba, 0xf },
	{0x32bb, 0xff},
	{0x32bc, 0x16},
	{0x32bd, 0x0 },
	{0x32be, 0x5 },
	{0x32bf, 0x4e},
	{0x32c0, 0x0 },
	{0x32c1, 0xc },
	{0x32c2, 0x1b},
	{0x32c3, 0xf },
	{0x32c4, 0xf1},
	{0x32c5, 0xdb},
	{0x32c6, 0xf },
	{0x32c7, 0xfc},
	{0x32c8, 0xf8},
	{0x32c9, 0xf },
	{0x32ca, 0xf4},
	{0x32cb, 0xad},
	{0x32cc, 0xf },
	{0x32cd, 0xfb},
	{0x32ce, 0x59},
	{0x32cf, 0x0 },
	{0x32d0, 0x9 },
	{0x32d1, 0xf7},
	{0x32d2, 0x0 },
	{0x32d3, 0x0 },
	{0x32d4, 0xc1},
	{0x32d5, 0xf },
	{0x32d6, 0xf5},
	{0x32d7, 0x30},
	{0x32d8, 0x0 },
	{0x32d9, 0x83},
	{0x32da, 0x1d},
	{0x32db, 0xf },
	{0x32dc, 0xe3},
	{0x32dd, 0x3c},
	{0x32de, 0x0 },
	{0x32df, 0xa },
	{0x32e0, 0x10},
	{0x32e1, 0x0 },
	{0x32e2, 0x7 },
	{0x32e3, 0x65},
	{0x32e4, 0xf },
	{0x32e5, 0xfe},
	{0x32e6, 0x79},
	{0x32e7, 0xf },
	{0x32e8, 0xfd},
	{0x32e9, 0x57},
	{0x32ea, 0xf },
	{0x32eb, 0xd6},
	{0x32ec, 0x8f},
	{0x32ed, 0x0 },
	{0x32ee, 0x3 },
	{0x32ef, 0x93},
	{0x32f0, 0x0 },
	{0x32f1, 0x6 },
	{0x32f2, 0xa },
	{0x32f3, 0xf },
	{0x32f4, 0xfa},
	{0x32f5, 0x6c},
	{0x32f6, 0xf },
	{0x32f7, 0xf1},
	{0x32f8, 0x1e},
	{0x32f9, 0x0 },
	{0x32fa, 0x14},
	{0x32fb, 0xe7},
	{0x32fc, 0x0 },
	{0x32fd, 0x1f},
	{0x32fe, 0x2d},
	{0x32ff, 0x0 },
	{0x3300, 0x7 },
	{0x3301, 0x5e},
	{0x3302, 0xf },
	{0x3303, 0xe0},
	{0x3304, 0x55},
	{0x3305, 0x0 },
	{0x3306, 0x20},
	{0x3307, 0x93},
	{0x3308, 0x0 },
	{0x3309, 0xf },
	{0x330a, 0x20},
	{0x330b, 0xf },
	{0x330c, 0xd7},
	{0x330d, 0xf5},
	{0x330e, 0xf },
	{0x330f, 0xef},
	{0x3310, 0xb8},
	{0x3311, 0xf },
	{0x3312, 0xf0},
	{0x3313, 0x29},
	{0x3314, 0x0 },
	{0x3315, 0x27},
	{0x3316, 0x5e},
	{0x3317, 0xf },
	{0x3318, 0xda},
	{0x3319, 0x14},
	{0x331a, 0xf },
	{0x331b, 0xef},
	{0x331c, 0x93},
	{0x331d, 0x0 },
	{0x331e, 0x2c},
	{0x331f, 0xdc},
	{0x3320, 0x0 },
	{0x3321, 0xe },
	{0x3322, 0x2d},
	{0x3323, 0x0 },
	{0x3324, 0x6 },
	{0x3325, 0xcf},
	{0x3326, 0xf },
	{0x3327, 0xfb},
	{0x3328, 0x26},
	{0x3329, 0x0 },
	{0x332a, 0x3 },
	{0x332b, 0x5 },
	{0x332c, 0x0 },
	{0x332d, 0x6 },
	{0x332e, 0xa6},
	{0x332f, 0xf },
	{0x3330, 0xf7},
	{0x3331, 0x7b},
	{0x3332, 0xf },
	{0x3333, 0xf9},
	{0x3334, 0xb },
	{0x3335, 0x0 },
	{0x3336, 0x7 },
	{0x3337, 0x5a},
	{0x3338, 0xf },
	{0x3339, 0xe4},
	{0x333a, 0x7a},
	{0x333b, 0x0 },
	{0x333c, 0x1b},
	{0x333d, 0xb0},
	{0x333e, 0x0 },
	{0x333f, 0x2 },
	{0x3340, 0xa7},
	{0x3341, 0xf },
	{0x3342, 0xe9},
	{0x3343, 0x3a},
	{0x3344, 0x0 },
	{0x3345, 0x95},
	{0x3346, 0x42},
	{0x3347, 0xf },
	{0x3348, 0xda},
	{0x3349, 0x45},
	{0x334a, 0x0 },
	{0x334b, 0x16},
	{0x334c, 0x7a},
	{0x334d, 0xf },
	{0x334e, 0xfb},
	{0x334f, 0x32},
	{0x3350, 0x0 },
	{0x3351, 0x6 },
	{0x3352, 0x35},
	{0x3353, 0xf },
	{0x3354, 0xfc},
	{0x3355, 0x8f},
	{0x3356, 0xf },
	{0x3357, 0xca},
	{0x3358, 0xd5},
	{0x3359, 0x0 },
	{0x335a, 0x11},
	{0x335b, 0x59},
	{0x335c, 0xf },
	{0x335d, 0xfa},
	{0x335e, 0xaa},
	{0x335f, 0xf },
	{0x3360, 0xfe},
	{0x3361, 0x84},
	{0x3362, 0xf },
	{0x3363, 0xf6},
	{0x3364, 0x8f},
	{0x3365, 0x0 },
	{0x3366, 0xb },
	{0x3367, 0x70},
	{0x3368, 0x0 },
	{0x3369, 0x25},
	{0x336a, 0x83},
	{0x336b, 0xf },
	{0x336c, 0xe7},
	{0x336d, 0x27},
	{0x336e, 0xf },
	{0x336f, 0xf1},
	{0x3370, 0x72},
	{0x3371, 0x0 },
	{0x3372, 0x21},
	{0x3373, 0x6d},
	{0x3374, 0x0 },
	{0x3375, 0x2 },
	{0x3376, 0xc3},
	{0x3377, 0xf },
	{0x3378, 0xe8},
	{0x3379, 0x5a},
	{0x337a, 0xf },
	{0x337b, 0xf2},
	{0x337c, 0x73},
	{0x337d, 0x0 },
	{0x337e, 0x19},
	{0x337f, 0xa5},
	{0x3380, 0x0 },
	{0x3381, 0x1a},
	{0x3382, 0x81},
	{0x3383, 0xf },
	{0x3384, 0xd0},
	{0x3385, 0x31},
	{0x3386, 0xf },
	{0x3387, 0xfb},
	{0x3388, 0xff},
	{0x3389, 0x0 },
	{0x338a, 0x1e},
	{0x338b, 0xe1},
	{0x338c, 0x0 },
	{0x338d, 0x5 },
	{0x338e, 0xe1},
	{0x338f, 0xf },
	{0x3390, 0xee},
	{0x3391, 0xe2},
	{0x3392, 0xf },
	{0x3393, 0xf6},
	{0x3394, 0xcf},
	{0x3395, 0x0 },
	{0x3396, 0x13},
	{0x3397, 0x8f},
	{0x3398, 0x0 },
	{0x3399, 0x3 },
	{0x339a, 0x61},
	{0x339b, 0xf },
	{0x339c, 0xf8},
	{0x339d, 0xf7},
	{0x339e, 0x0 },
	{0x339f, 0x0 },
	{0x33a0, 0xb5},
	{0x33a1, 0x0 },
	{0x33a2, 0x5 },
	{0x33a3, 0x78},
	{0x33a4, 0xf },
	{0x33a5, 0xf4},
	{0x33a6, 0x5 },
	{0x33a7, 0x0 },
	{0x33a8, 0xc },
	{0x33a9, 0xe },
	{0x33aa, 0x0 },
	{0x33ab, 0x3 },
	{0x33ac, 0x53},
	{0x33ad, 0xf },
	{0x33ae, 0xec},
	{0x33af, 0xbd},
};

const struct
qs_s5k4e1_i2c_reg_conf qs_s5k4e1_lenshading_settings[4][LENS_SHADE_TABLE] = {
	{/*          */
		{0x3097, 0x52},/*                    */
		{0x3098, 0x3e},/*                     */
		{0x3099, 0x03},/*                                     */
		{0x309a, 0x1f},/*                */
		{0x309b, 0x04},/*                                      */
		{0x309c, 0x21},/*                */
		{0x309d, 0x00},/*                         */
		{0x309e, 0x00},/*                         */
		{0x309f, 0x00},/*                              */
		{0x30a0, 0x00},/*                          */
		{0x30a1, 0x00},/*                         */
		{0x30a2, 0x00},/*                         */
		{0x30a3, 0x00},/*                              */
		{0x30a4, 0x00},/*                          */
		{0x30a5, 0x01},
		{0x30a6, 0x00},/*                */
	},
	{/*           */
		{0x3097, 0x52},/*                    */
		{0x3098, 0x7b},/*                      */
		{0x3099, 0x03},/*                                     */
		{0x309a, 0x1f},/*                */
		{0x309b, 0x02},/*                                     */
		{0x309c, 0x15},/*                */
		{0x309d, 0x00},/*                         */
		{0x309e, 0x00},/*                         */
		{0x309f, 0x00},/*                              */
		{0x30a0, 0x00},/*                          */
		{0x30a1, 0x00},/*                         */
		{0x30a2, 0x00},/*                         */
		{0x30a3, 0x00},/*                              */
		{0x30a4, 0x00},/*                          */
		{0x30a5, 0x01},
		{0x30a6, 0x00},/*                */
	},

	{/*          */
		{0x3097, 0x52},/*                    */
		{0x3098, 0x7b},/*                      */
		{0x3099, 0x03},/*                                     */
		{0x309a, 0x1f},/*                */
		{0x309b, 0x02},/*                                     */
		{0x309c, 0x15},/*                */
		{0x309d, 0x3a},/*                          */
		{0x309e, 0x01},/*                         */
		{0x309f, 0xb5},/*                                  */
		{0x30a0, 0x06},/*                          */
		{0x30a1, 0x23},/*                          */
		{0x30a2, 0x03},/*                         */
		{0x30a3, 0x48},/*                                  */
		{0x30a4, 0xdf},/*                          */
		{0x30a5, 0x01},
		{0x30a6, 0x00},/*                */
	},

	{/*           */
		{0x3097, 0x52},/*                    */
		{0x3098, 0x7b},/*                      */
		{0x3099, 0x03},/*                                     */
		{0x309a, 0x1f},/*                */
		{0x309b, 0x02},/*                                     */
		{0x309c, 0x15},/*                */
		{0x309d, 0x38},/*                          */
		{0x309e, 0x01},/*                         */
		{0x309f, 0xae},/*                                  */
		{0x30a0, 0xc8},/*                          */
		{0x30a1, 0x23},/*                          */
		{0x30a2, 0x03},/*                         */
		{0x30a3, 0x48},/*                                  */
		{0x30a4, 0xdf},/*                          */
		{0x30a5, 0x01},
		{0x30a6, 0x00},/*                */
	},

};

struct qs_s5k4e1_i2c_conf_array qs_s5k4e1_confs[] = {
	{&qs_s5k4e1_prev_settings_2d[0], \
		ARRAY_SIZE(qs_s5k4e1_prev_settings_2d)},
	{&qs_s5k4e1_snap_settings_2d[0], \
		ARRAY_SIZE(qs_s5k4e1_snap_settings_2d)},
	{&qs_s5k4e1_prev_settings_3d[0], \
		ARRAY_SIZE(qs_s5k4e1_prev_settings_3d)},
	{&qs_s5k4e1_snap_settings_3d[0], \
		ARRAY_SIZE(qs_s5k4e1_snap_settings_3d)},
};
struct qs_s5k4e1_reg qs_s5k4e1_regs = {
	.rec_settings = &qs_s5k4e1_recommend_settings[0],
	.rec_size = ARRAY_SIZE(qs_s5k4e1_recommend_settings),
	.reg_lens = &qs_s5k4e1_lenshading_settings[0],
	.reg_lens_size = ARRAY_SIZE(qs_s5k4e1_lenshading_settings[0]),
	.reg_default_lens = &qs_s5k4e1_default_lenshading_settings[0],
	.reg_default_lens_size =
		ARRAY_SIZE(qs_s5k4e1_default_lenshading_settings),
	.conf_array = &qs_s5k4e1_confs[0],
};
