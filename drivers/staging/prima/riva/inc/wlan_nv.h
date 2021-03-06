/*
 * Copyright (c) 2012, The Linux Foundation. All rights reserved.
 *
 * Previously licensed under the ISC license by Qualcomm Atheros, Inc.
 *
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/** ------------------------------------------------------------------------- *
    ------------------------------------------------------------------------- *


    \file wlan_nv.h

    \brief Types for NV implementation
           Anything that needs to be publicly available should
           be in this file

    $Id$

    Copyright (C) 2006 Airgo Networks, Incorporated


   ========================================================================== */

#if !defined( __WLAN_NV_H )
#define __WLAN_NV_H

#include "halLegacyPalTypes.h"
#include "halCompiler.h"

//                    
typedef enum
{
    //                
    NV_COMMON_PRODUCT_ID,               //  
    NV_COMMON_PRODUCT_BANDS,            //  
    NV_COMMON_NUM_OF_TX_CHAINS,         //  
    NV_COMMON_NUM_OF_RX_CHAINS,         //  
    NV_COMMON_MAC_ADDR,                 //  
    NV_COMMON_MFG_SERIAL_NUMBER,        //  
    NV_COMMON_WLAN_NV_REV_ID,           //  
    NV_COMMON_COUPLER_TYPE,             //  

    NUM_NV_FIELDS,
    NV_MAX_FIELD = 0x7FFFFFFF  /*                        */

}eNvField;


#define NV_FIELD_MAC_ADDR_SIZE      6
#define NV_FIELD_MFG_SN_SIZE        40
typedef enum
{
    PRODUCT_BAND_11_B_G     = 0,    //                           
    PRODUCT_BAND_11_A_B_G   = 1,
    PRODUCT_BAND_11_A       = 2,

    NUM_PRODUCT_BANDS,
    NUM_PRODUCT_BANDS_INVALID = 0x7FFFFFFF  /*                        */
}eNvProductBands;           //                       


typedef PACKED_PRE union PACKED_POST
{
    //                
    tANI_U16  productId;
    tANI_U8   productBands;
    tANI_U8   wlanNvRevId;
    tANI_U8   numOfTxChains;
    tANI_U8   numOfRxChains;
    tANI_U8   macAddr[NV_FIELD_MAC_ADDR_SIZE];   /*                                            */
    tANI_U8   macAddr2[NV_FIELD_MAC_ADDR_SIZE];
    tANI_U8   macAddr3[NV_FIELD_MAC_ADDR_SIZE];
    tANI_U8   macAddr4[NV_FIELD_MAC_ADDR_SIZE];
    tANI_U8   mfgSN[NV_FIELD_MFG_SN_SIZE];
    tANI_U8   couplerType;                       /*                                            */
    tANI_U8   reserved;                          /*                     */
} uNvFields;



//                           
typedef PACKED_PRE struct PACKED_POST
{
    //                                                     
    tANI_U16  productId;
    tANI_U8   productBands;
    tANI_U8   wlanNvRevId; //                                  

    tANI_U8   numOfTxChains;
    tANI_U8   numOfRxChains;
    tANI_U8   macAddr[NV_FIELD_MAC_ADDR_SIZE];   /*                                            */
    tANI_U8   macAddr2[NV_FIELD_MAC_ADDR_SIZE];
    tANI_U8   macAddr3[NV_FIELD_MAC_ADDR_SIZE];
    tANI_U8   macAddr4[NV_FIELD_MAC_ADDR_SIZE];
    tANI_U8   mfgSN[NV_FIELD_MFG_SN_SIZE];
    tANI_U8   couplerType;                       /*                                            */
    tANI_U8   reserved;                          /*                     */
} sNvFields;


//                             

typedef tANI_S8 tPowerdBm;   //                                                

typedef PACKED_PRE union PACKED_POST
{
    tANI_U32 measurement;      //                                                                                          
    tANI_S16 reported;         //                                                                      
}uAbsPwrPrecision;

typedef enum
{
    PHY_TX_CHAIN_0 = 0,

    PHY_MAX_TX_CHAINS = 1,
    PHY_ALL_TX_CHAINS,

    //                              
    PHY_NO_TX_CHAINS,
    PHY_TX_CHAIN_INVALID = 0x7FFFFFFF  /*                        */
}ePhyTxChains;

//                            

typedef enum
{
    REG_DOMAIN_FCC,
    REG_DOMAIN_ETSI,
    REG_DOMAIN_JAPAN,
    REG_DOMAIN_WORLD,
    REG_DOMAIN_N_AMER_EXC_FCC,
    REG_DOMAIN_APAC,
    REG_DOMAIN_KOREA,
    REG_DOMAIN_HI_5GHZ,
    REG_DOMAIN_NO_5GHZ,

    NUM_REG_DOMAINS,
    NUM_REG_DOMAINS_INVALID = 0x7FFFFFFF  /*                        */
}eRegDomainId;

typedef enum
{
    RF_SUBBAND_2_4_GHZ      = 0,
    RF_SUBBAND_5_LOW_GHZ    = 1,    //               
    RF_SUBBAND_5_MID_GHZ    = 2,    //    
    RF_SUBBAND_5_HIGH_GHZ   = 3,    //          
    RF_SUBBAND_4_9_GHZ      = 4,    //        


    NUM_RF_SUBBANDS,

    MAX_RF_SUBBANDS,
    INVALID_RF_SUBBAND,

    RF_BAND_2_4_GHZ = 0,
    RF_BAND_5_GHZ = 1,
    NUM_RF_BANDS,
    BOTH_RF_BANDS,
    RF_SUBBAND_INVALID = 0x7FFFFFFF  /*                        */
}eRfSubBand;

typedef enum
{
    //           
    RF_CHAN_1                 = 0,
    RF_CHAN_2                 = 1,
    RF_CHAN_3                 = 2,
    RF_CHAN_4                 = 3,
    RF_CHAN_5                 = 4,
    RF_CHAN_6                 = 5,
    RF_CHAN_7                 = 6,
    RF_CHAN_8                 = 7,
    RF_CHAN_9                 = 8,
    RF_CHAN_10                = 9,
    RF_CHAN_11                = 10,
    RF_CHAN_12                = 11,
    RF_CHAN_13                = 12,
    RF_CHAN_14                = 13,

    //           
    RF_CHAN_240               = 14,
    RF_CHAN_244               = 15,
    RF_CHAN_248               = 16,
    RF_CHAN_252               = 17,
    RF_CHAN_208               = 18,
    RF_CHAN_212               = 19,
    RF_CHAN_216               = 20,

    //                         
    RF_CHAN_36                = 21,
    RF_CHAN_40                = 22,
    RF_CHAN_44                = 23,
    RF_CHAN_48                = 24,
    RF_CHAN_52                = 25,
    RF_CHAN_56                = 26,
    RF_CHAN_60                = 27,
    RF_CHAN_64                = 28,

    //                          
    RF_CHAN_100               = 29,
    RF_CHAN_104               = 30,
    RF_CHAN_108               = 31,
    RF_CHAN_112               = 32,
    RF_CHAN_116               = 33,
    RF_CHAN_120               = 34,
    RF_CHAN_124               = 35,
    RF_CHAN_128               = 36,
    RF_CHAN_132               = 37,
    RF_CHAN_136               = 38,
    RF_CHAN_140               = 39,

    //                    
    RF_CHAN_149               = 40,
    RF_CHAN_153               = 41,
    RF_CHAN_157               = 42,
    RF_CHAN_161               = 43,
    RF_CHAN_165               = 44,

    //                       
    RF_CHAN_BOND_3            = 45,
    RF_CHAN_BOND_4            = 46,
    RF_CHAN_BOND_5            = 47,
    RF_CHAN_BOND_6            = 48,
    RF_CHAN_BOND_7            = 49,
    RF_CHAN_BOND_8            = 50,
    RF_CHAN_BOND_9            = 51,
    RF_CHAN_BOND_10           = 52,
    RF_CHAN_BOND_11           = 53,
    RF_CHAN_BOND_242          = 54,    //           
    RF_CHAN_BOND_246          = 55,
    RF_CHAN_BOND_250          = 56,
    RF_CHAN_BOND_210          = 57,
    RF_CHAN_BOND_214          = 58,
    RF_CHAN_BOND_38           = 59,    //                         
    RF_CHAN_BOND_42           = 60,
    RF_CHAN_BOND_46           = 61,
    RF_CHAN_BOND_50           = 62,
    RF_CHAN_BOND_54           = 63,
    RF_CHAN_BOND_58           = 64,
    RF_CHAN_BOND_62           = 65,
    RF_CHAN_BOND_102          = 66,    //                          
    RF_CHAN_BOND_106          = 67,
    RF_CHAN_BOND_110          = 68,
    RF_CHAN_BOND_114          = 69,
    RF_CHAN_BOND_118          = 70,
    RF_CHAN_BOND_122          = 71,
    RF_CHAN_BOND_126          = 72,
    RF_CHAN_BOND_130          = 73,
    RF_CHAN_BOND_134          = 74,
    RF_CHAN_BOND_138          = 75,
    RF_CHAN_BOND_151          = 76,    //                    
    RF_CHAN_BOND_155          = 77,
    RF_CHAN_BOND_159          = 78,
    RF_CHAN_BOND_163          = 79,

    NUM_RF_CHANNELS,

    MIN_2_4GHZ_CHANNEL = RF_CHAN_1,
    MAX_2_4GHZ_CHANNEL = RF_CHAN_14,
    NUM_2_4GHZ_CHANNELS = (MAX_2_4GHZ_CHANNEL - MIN_2_4GHZ_CHANNEL + 1),

    MIN_5GHZ_CHANNEL = RF_CHAN_240,
    MAX_5GHZ_CHANNEL = RF_CHAN_165,
    NUM_5GHZ_CHANNELS = (MAX_5GHZ_CHANNEL - MIN_5GHZ_CHANNEL + 1),

    MIN_20MHZ_RF_CHANNEL = RF_CHAN_1,
    MAX_20MHZ_RF_CHANNEL = RF_CHAN_165,
    NUM_20MHZ_RF_CHANNELS = (MAX_20MHZ_RF_CHANNEL - MIN_20MHZ_RF_CHANNEL + 1),

    MIN_40MHZ_RF_CHANNEL = RF_CHAN_BOND_3,
    MAX_40MHZ_RF_CHANNEL = RF_CHAN_BOND_163,
    NUM_40MHZ_RF_CHANNELS = (MAX_40MHZ_RF_CHANNEL - MIN_40MHZ_RF_CHANNEL + 1),

    MIN_CB_2_4GHZ_CHANNEL = RF_CHAN_BOND_3,
    MAX_CB_2_4GHZ_CHANNEL = RF_CHAN_BOND_11,

    MIN_CB_5GHZ_CHANNEL = RF_CHAN_BOND_242,
    MAX_CB_5GHZ_CHANNEL = RF_CHAN_BOND_163,

    NUM_TPC_2_4GHZ_CHANNELS = 14,
    NUM_TPC_5GHZ_CHANNELS = NUM_5GHZ_CHANNELS,

    INVALID_RF_CHANNEL = 0xBAD,
    RF_CHANNEL_INVALID_MAX_FIELD = 0x7FFFFFFF  /*                        */
}eRfChannels;

enum
{
   NV_CHANNEL_DISABLE,
   NV_CHANNEL_ENABLE,
   NV_CHANNEL_DFS,
   NV_CHANNEL_INVALID
};
typedef tANI_U8 eNVChannelEnabledType;

typedef PACKED_PRE struct PACKED_POST
{
    eNVChannelEnabledType   enabled;
    tPowerdBm pwrLimit;
}sRegulatoryChannel;

typedef PACKED_PRE struct PACKED_POST
{
    sRegulatoryChannel channels[NUM_RF_CHANNELS];
    uAbsPwrPrecision antennaGain[NUM_RF_SUBBANDS];
    uAbsPwrPrecision bRatePowerOffset[NUM_2_4GHZ_CHANNELS];
    uAbsPwrPrecision gnRatePowerOffset[NUM_RF_CHANNELS];
}ALIGN_4 sRegulatoryDomains;

typedef PACKED_PRE struct PACKED_POST
{
    tANI_S16 bRssiOffset[NUM_RF_CHANNELS];
    tANI_S16 gnRssiOffset[NUM_RF_CHANNELS];
}ALIGN_4 sRssiChannelOffsets;

typedef PACKED_PRE struct PACKED_POST
{
    tANI_U16 targetFreq;           //             
    tANI_U16 channelNum;           //                                                
    eRfSubBand band;               //                                 
}tRfChannelProps;

typedef enum
{
    MODE_802_11B    = 0,
    MODE_802_11AG   = 1,
    MODE_802_11N    = 2,
    NUM_802_11_MODES,
    MODE_802_11_INVALID = 0x7FFFFFFF  /*                        */
} e80211Modes;


//                                 
typedef PACKED_PRE struct PACKED_POST
{
    tANI_U16    process_monitor;
    tANI_U8     hdet_cal_code;
    tANI_U8     rxfe_gm_2;

    tANI_U8     tx_bbf_rtune;
    tANI_U8     pa_rtune_reg;
    tANI_U8     rt_code;
    tANI_U8     bias_rtune;

    tANI_U8     bb_bw1;
    tANI_U8     bb_bw2;
    tANI_U8     pa_ctune_reg;
    tANI_U8     reserved1;

    tANI_U8     bb_bw3;
    tANI_U8     bb_bw4;
    tANI_U8     bb_bw5;
    tANI_U8     bb_bw6;

    tANI_U16    rcMeasured;
    tANI_U8     tx_bbf_ct;
    tANI_U8     tx_bbf_ctr;

    tANI_U8     csh_maxgain_reg;
    tANI_U8     csh_0db_reg;
    tANI_U8     csh_m3db_reg;
    tANI_U8     csh_m6db_reg;

    tANI_U8     cff_0db_reg;
    tANI_U8     cff_m3db_reg;
    tANI_U8     cff_m6db_reg;
    tANI_U8     rxfe_gpio_ctl_1;

    tANI_U8     mix_bal_cnt_2;
    tANI_S8     rxfe_lna_highgain_bias_ctl_delta;
    tANI_U8     rxfe_lna_load_ctune;
    tANI_U8     rxfe_lna_ngm_rtune;

    tANI_U8     rx_im2_spare0;
    tANI_U8     rx_im2_spare1;
    tANI_U16    hdet_dco;

    tANI_U8     pll_vfc_reg3_b0;
    tANI_U8     pll_vfc_reg3_b1;
    tANI_U8     pll_vfc_reg3_b2;
    tANI_U8     pll_vfc_reg3_b3;

    tANI_U16    tempStart;
    tANI_U16    roomTemp;

    tANI_S16    ambientCalTemp;
    tANI_U8     ambientCalTempValid;
    tANI_U8     reserved2;

}sCalData;

typedef PACKED_PRE struct PACKED_POST
{
    tANI_U32 calStatus;  //            
    sCalData calData;
}sRFCalValues;

typedef PACKED_PRE struct PACKED_POST
{
    tANI_U32 txFirFilterMode;
}sTxBbFilterMode;

typedef PACKED_PRE struct PACKED_POST
{
    tANI_S16 ofdmPwrOffset;
    tANI_S16 rsvd;
}sOfdmCmdPwrOffset;

//                           
typedef tANI_U8 tTpcLutValue;

#define MAX_TPC_CAL_POINTS      (8)

typedef tANI_U8 tPowerDetect;        //                          

typedef PACKED_PRE struct PACKED_POST
{
    tPowerDetect pwrDetAdc;            //                                                  
                                       //                                                                    
    tPowerDetect adjustedPwrDet;       //                                                              
                                       //                                                    
}tTpcCaldPowerPoint;

typedef tTpcCaldPowerPoint tTpcCaldPowerTable[PHY_MAX_TX_CHAINS][MAX_TPC_CAL_POINTS];

typedef PACKED_PRE struct PACKED_POST
{
    tTpcCaldPowerTable empirical;                      //                       
}tTpcConfig;

//                            
#ifndef TPC_MEM_POWER_LUT_DEPTH
#define TPC_MEM_POWER_LUT_DEPTH 256
#endif

typedef tTpcLutValue tTpcPowerTable[PHY_MAX_TX_CHAINS][TPC_MEM_POWER_LUT_DEPTH];

typedef PACKED_PRE struct PACKED_POST
{
    tTpcConfig *pwrSampled;             //                                
}tPhyTxPowerBand;

//                  
typedef enum
{
    //             
    HAL_PHY_RATE_11B_LONG_1_MBPS,
    HAL_PHY_RATE_11B_LONG_2_MBPS,
    HAL_PHY_RATE_11B_LONG_5_5_MBPS,
    HAL_PHY_RATE_11B_LONG_11_MBPS,
    HAL_PHY_RATE_11B_SHORT_2_MBPS,
    HAL_PHY_RATE_11B_SHORT_5_5_MBPS,
    HAL_PHY_RATE_11B_SHORT_11_MBPS,

    //                           
    HAL_PHY_RATE_11A_6_MBPS,
    HAL_PHY_RATE_11A_9_MBPS,
    HAL_PHY_RATE_11A_12_MBPS,
    HAL_PHY_RATE_11A_18_MBPS,
    HAL_PHY_RATE_11A_24_MBPS,
    HAL_PHY_RATE_11A_36_MBPS,
    HAL_PHY_RATE_11A_48_MBPS,
    HAL_PHY_RATE_11A_54_MBPS,

    //                
    HAL_PHY_RATE_11A_DUP_6_MBPS,
    HAL_PHY_RATE_11A_DUP_9_MBPS,
    HAL_PHY_RATE_11A_DUP_12_MBPS,
    HAL_PHY_RATE_11A_DUP_18_MBPS,
    HAL_PHY_RATE_11A_DUP_24_MBPS,
    HAL_PHY_RATE_11A_DUP_36_MBPS,
    HAL_PHY_RATE_11A_DUP_48_MBPS,
    HAL_PHY_RATE_11A_DUP_54_MBPS,

    //                         
    HAL_PHY_RATE_MCS_1NSS_6_5_MBPS,
    HAL_PHY_RATE_MCS_1NSS_13_MBPS,
    HAL_PHY_RATE_MCS_1NSS_19_5_MBPS,
    HAL_PHY_RATE_MCS_1NSS_26_MBPS,
    HAL_PHY_RATE_MCS_1NSS_39_MBPS,
    HAL_PHY_RATE_MCS_1NSS_52_MBPS,
    HAL_PHY_RATE_MCS_1NSS_58_5_MBPS,
    HAL_PHY_RATE_MCS_1NSS_65_MBPS,
    HAL_PHY_RATE_MCS_1NSS_MM_SG_7_2_MBPS,
    HAL_PHY_RATE_MCS_1NSS_MM_SG_14_4_MBPS,
    HAL_PHY_RATE_MCS_1NSS_MM_SG_21_7_MBPS,
    HAL_PHY_RATE_MCS_1NSS_MM_SG_28_9_MBPS,
    HAL_PHY_RATE_MCS_1NSS_MM_SG_43_3_MBPS,
    HAL_PHY_RATE_MCS_1NSS_MM_SG_57_8_MBPS,
    HAL_PHY_RATE_MCS_1NSS_MM_SG_65_MBPS,
    HAL_PHY_RATE_MCS_1NSS_MM_SG_72_2_MBPS,

    //                          
    HAL_PHY_RATE_MCS_1NSS_CB_13_5_MBPS,
    HAL_PHY_RATE_MCS_1NSS_CB_27_MBPS,
    HAL_PHY_RATE_MCS_1NSS_CB_40_5_MBPS,
    HAL_PHY_RATE_MCS_1NSS_CB_54_MBPS,
    HAL_PHY_RATE_MCS_1NSS_CB_81_MBPS,
    HAL_PHY_RATE_MCS_1NSS_CB_108_MBPS,
    HAL_PHY_RATE_MCS_1NSS_CB_121_5_MBPS,
    HAL_PHY_RATE_MCS_1NSS_CB_135_MBPS,
    HAL_PHY_RATE_MCS_1NSS_MM_SG_CB_15_MBPS,
    HAL_PHY_RATE_MCS_1NSS_MM_SG_CB_30_MBPS,
    HAL_PHY_RATE_MCS_1NSS_MM_SG_CB_45_MBPS,
    HAL_PHY_RATE_MCS_1NSS_MM_SG_CB_60_MBPS,
    HAL_PHY_RATE_MCS_1NSS_MM_SG_CB_90_MBPS,
    HAL_PHY_RATE_MCS_1NSS_MM_SG_CB_120_MBPS,
    HAL_PHY_RATE_MCS_1NSS_MM_SG_CB_135_MBPS,
    HAL_PHY_RATE_MCS_1NSS_MM_SG_CB_150_MBPS,

#ifdef WLAN_FEATURE_11AC
    /*                         */
    HAL_PHY_RATE_11AC_DUP_6_MBPS,
    HAL_PHY_RATE_11AC_DUP_9_MBPS,
    HAL_PHY_RATE_11AC_DUP_12_MBPS,
    HAL_PHY_RATE_11AC_DUP_18_MBPS,
    HAL_PHY_RATE_11AC_DUP_24_MBPS,
    HAL_PHY_RATE_11AC_DUP_36_MBPS,
    HAL_PHY_RATE_11AC_DUP_48_MBPS,
    HAL_PHY_RATE_11AC_DUP_54_MBPS,

    /*                         */
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_NGI_6_5_MBPS,
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_NGI_13_MBPS,
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_NGI_19_5_MBPS,
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_NGI_26_MBPS,
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_NGI_39_MBPS,
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_NGI_52_MBPS,
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_NGI_58_5_MBPS,
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_NGI_65_MBPS,
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_NGI_78_MBPS,
    
    /*                         */
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_SGI_7_2_MBPS,
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_SGI_14_4_MBPS,
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_SGI_21_6_MBPS,
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_SGI_28_8_MBPS,
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_SGI_43_3_MBPS,
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_SGI_57_7_MBPS,
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_SGI_65_MBPS,
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_SGI_72_2_MBPS,
    HAL_PHY_RATE_VHT_20MHZ_MCS_1NSS_SGI_86_6_MBPS,
    
    /*                          */
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_NGI_13_5_MBPS ,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_NGI_27_MBPS,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_NGI_40_5_MBPS,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_NGI_54_MBPS,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_NGI_81_MBPS,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_NGI_108_MBPS,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_NGI_121_5_MBPS,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_NGI_135_MBPS,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_NGI_162_MBPS,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_NGI_180_MBPS,
    
    /*                         */
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_SGI_15_MBPS ,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_SGI_30_MBPS,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_SGI_45_MBPS,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_SGI_60_MBPS,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_SGI_90_MBPS,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_SGI_120_MBPS,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_SGI_135_MBPS,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_SGI_150_MBPS,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_SGI_180_MBPS,
    HAL_PHY_RATE_VHT_40MHZ_MCS_1NSS_CB_SGI_200_MBPS,
    
    /*                           */
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_NGI_29_3_MBPS ,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_NGI_58_5_MBPS,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_NGI_87_8_MBPS,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_NGI_117_MBPS,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_NGI_175_5_MBPS,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_NGI_234_MBPS,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_NGI_263_3_MBPS,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_NGI_292_5_MBPS,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_NGI_351_MBPS,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_NGI_390_MBPS,
    
    /*                          */
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_SGI_32_5_MBPS ,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_SGI_65_MBPS,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_SGI_97_5_MBPS,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_SGI_130_MBPS,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_SGI_195_MBPS,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_SGI_260_MBPS,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_SGI_292_5_MBPS,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_SGI_325_MBPS,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_SGI_390_MBPS,
    HAL_PHY_RATE_VHT_80MHZ_MCS_1NSS_CB_SGI_433_3_MBPS,
#endif //                 

    NUM_HAL_PHY_RATES,
    HAL_PHY_RATE_INVALID,
    MIN_RATE_INDEX = 0,
    MAX_RATE_INDEX = NUM_HAL_PHY_RATES - 1,
    HAL_PHY_RATE_INVALID_MAX_FIELD = 0x7FFFFFFF  /*                        */
}eHalPhyRates;


#define NUM_RATE_POWER_GROUPS           NUM_HAL_PHY_RATES  //                                                                    
typedef uAbsPwrPrecision tRateGroupPwr[NUM_RATE_POWER_GROUPS];

//                  
#define NV_FIELD_COUNTRY_CODE_SIZE  3
typedef PACKED_PRE struct PACKED_POST
{
    tANI_U8 regDomain;                                  //                 
    tANI_U8 countryCode[NV_FIELD_COUNTRY_CODE_SIZE];    //                  
}sDefaultCountry;

typedef PACKED_PRE struct PACKED_POST
{
    tANI_U8     overall;
    tANI_U8     fwInit;
    tANI_U8     hdet_dco;
    tANI_U8     rtuner;

    tANI_U8     ctuner;
    tANI_U8     insitu;
    tANI_U8     process_monitor;
    tANI_U8     pllVcoLinearity;

    tANI_U8     txIQ;
    tANI_U8     rxIQ;
    tANI_U8     rxDco;
    tANI_U8     txLo;

    tANI_U8     lnaBias;
    tANI_U8     lnaBandTuning;
    tANI_U8     lnaGainAdjust;
    tANI_U8     im2UsingNoisePwr;

    tANI_U8     temperature;
    tANI_U8     clpc;
    tANI_U8     clpc_temp_adjust;
    tANI_U8     txDpd;

    tANI_U8     channelTune;
    tANI_U8     rxGmStageLinearity;
    tANI_U8     im2UsingToneGen;
    tANI_U8     rxBbfTuning; //                          

    tANI_U8     txBbfTuning; //                          
    tANI_U8     paCTuning;   //                               
    tANI_U8     unused[6];
}sCalStatus;

#define NUM_RF_VR_RATE   13
typedef uAbsPwrPrecision tRateGroupPwrVR[NUM_RF_VR_RATE];

typedef PACKED_PRE union PACKED_POST
{
    tRateGroupPwr        pwrOptimum[NUM_RF_SUBBANDS];                         //                             
    sRegulatoryDomains   regDomains[NUM_REG_DOMAINS];                         //                            
    sDefaultCountry      defaultCountryTable;                                 //                         
    tTpcPowerTable       plutCharacterized[NUM_RF_CHANNELS];                  //                         
    tANI_S16             plutPdadcOffset[NUM_RF_CHANNELS];                    //                           
    tRateGroupPwrVR      pwrOptimum_virtualRate[NUM_RF_SUBBANDS];             //                      
    //                                                                                              
    sCalStatus           calStatus;                                           //                    
    sRssiChannelOffsets  rssiChanOffsets[2];                                  //                              
    sRFCalValues         rFCalValues;                                         //                       
    tANI_S16             antennaPathLoss[NUM_RF_CHANNELS];                    //                           
    tANI_S16             pktTypePwrLimits[NUM_802_11_MODES][NUM_RF_CHANNELS]; //                                  
    sOfdmCmdPwrOffset    ofdmCmdPwrOffset;                                    //                             
    sTxBbFilterMode      txbbFilterMode;                                      //                           
}ALIGN_4 uNvTables;

//             
typedef tPowerdBm tChannelPwrLimit;

typedef PACKED_PRE struct PACKED_POST
{
    tANI_U8 chanId;
    tChannelPwrLimit pwr;
} ALIGN_4 tChannelListWithPower;

//                          
typedef enum
{
    NV_FIELDS_IMAGE                 = 0,    //                   

    NV_TABLE_RATE_POWER_SETTINGS    = 2,
    NV_TABLE_REGULATORY_DOMAINS     = 3,
    NV_TABLE_DEFAULT_COUNTRY        = 4,
    NV_TABLE_TPC_POWER_TABLE        = 5,
    NV_TABLE_TPC_PDADC_OFFSETS      = 6,
    NV_TABLE_RF_CAL_VALUES          = 7,
    NV_TABLE_RSSI_CHANNEL_OFFSETS   = 9,
    NV_TABLE_CAL_MEMORY             = 10,    //                                                              
    NV_TABLE_CAL_STATUS             = 11,
    NV_TABLE_ANTENNA_PATH_LOSS          = 12,
    NV_TABLE_PACKET_TYPE_POWER_LIMITS   = 13,
    NV_TABLE_OFDM_CMD_PWR_OFFSET        = 14,
    NV_TABLE_TX_BB_FILTER_MODE          = 15,
    NV_TABLE_VIRTUAL_RATE               = 18,

    NUM_NV_TABLE_IDS,
    NV_ALL_TABLES                   = 0xFFF,
    NV_BINARY_IMAGE                 = 0x1000,
    NV_MAX_TABLE                    = 0x7FFFFFFF  /*                        */
}eNvTable;

typedef PACKED_PRE struct PACKED_POST
{
    tRateGroupPwr        pwrOptimum[NUM_RF_SUBBANDS];                         //                             
    sRegulatoryDomains   regDomains[NUM_REG_DOMAINS];                         //                            
    sDefaultCountry      defaultCountryTable;                                 //                         
    tTpcPowerTable       plutCharacterized[NUM_RF_CHANNELS];                  //                         
    tANI_S16             plutPdadcOffset[NUM_RF_CHANNELS];                    //                           
    tRateGroupPwrVR      pwrOptimum_virtualRate[NUM_RF_SUBBANDS];             //                      
    //                                                                                              
    sCalStatus           calStatus;                                           //                    
    sRssiChannelOffsets  rssiChanOffsets[2];                                  //                              
    sRFCalValues         rFCalValues;                                         //                       
    tANI_S16             antennaPathLoss[NUM_RF_CHANNELS];                    //                           
    tANI_S16             pktTypePwrLimits[NUM_802_11_MODES][NUM_RF_CHANNELS]; //                                  
    sOfdmCmdPwrOffset    ofdmCmdPwrOffset;                                    //                             
    sTxBbFilterMode      txbbFilterMode;                                      //                           
}ALIGN_4 sNvTables;

typedef PACKED_PRE struct PACKED_POST
{
    sNvFields fields;
    sNvTables tables;
}ALIGN_4 sHalNv;

extern const sHalNv nvDefaults;

#endif

