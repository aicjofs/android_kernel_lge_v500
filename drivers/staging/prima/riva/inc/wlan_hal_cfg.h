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

/*==========================================================================
 *
 *  @file:     wlan_hal_cfg.h
 *
 *  @brief:    Exports and types WLAN HAL configuration
 *
 *  @author:   Kumar Anand
 *
 *             Copyright (C) 2010, Qualcomm, Inc. 
 *             All rights reserved.
 *
 *=========================================================================*/

#ifndef __WLAN_HAL_CFG_H__
#define __WLAN_HAL_CFG_H__

/*                                                                         
               
                                                                         */
#include <wlan_defs.h>

/*                                                                         
                                        
                                                                         */
/*                                                                     */
#define WLAN_HAL_CONSTRUCT_API_VERSION(W,X,Y,Z) (((W)<<24)+((X)<<16)+((Y)<<8)+(Z))
#define IS_VERSION_BEFORE_VOWIFI(VER_FROM_HOST) \
                 ((VER_FROM_HOST)<=WLAN_HAL_CONSTRUCT_API_VERSION(0,0,2,0))?1:0

/*                                                                         
                             
                                                                         */
#define QWLAN_HAL_CFG_STA_ID                             0
#define QWLAN_HAL_CFG_CURRENT_TX_ANTENNA                 1
#define QWLAN_HAL_CFG_CURRENT_RX_ANTENNA                 2
#define QWLAN_HAL_CFG_LOW_GAIN_OVERRIDE                  3
#define QWLAN_HAL_CFG_POWER_STATE_PER_CHAIN              4
#define QWLAN_HAL_CFG_CAL_PERIOD                         5
#define QWLAN_HAL_CFG_CAL_CONTROL                        6
#define QWLAN_HAL_CFG_PROXIMITY                          7
#define QWLAN_HAL_CFG_NETWORK_DENSITY                    8
#define QWLAN_HAL_CFG_MAX_MEDIUM_TIME                    9
#define QWLAN_HAL_CFG_MAX_MPDUS_IN_AMPDU                 10
#define QWLAN_HAL_CFG_RTS_THRESHOLD                      11
#define QWLAN_HAL_CFG_SHORT_RETRY_LIMIT                  12
#define QWLAN_HAL_CFG_LONG_RETRY_LIMIT                   13
#define QWLAN_HAL_CFG_FRAGMENTATION_THRESHOLD            14
#define QWLAN_HAL_CFG_DYNAMIC_THRESHOLD_ZERO             15
#define QWLAN_HAL_CFG_DYNAMIC_THRESHOLD_ONE              16
#define QWLAN_HAL_CFG_DYNAMIC_THRESHOLD_TWO              17
#define QWLAN_HAL_CFG_FIXED_RATE                         18
#define QWLAN_HAL_CFG_RETRYRATE_POLICY                   19
#define QWLAN_HAL_CFG_RETRYRATE_SECONDARY                20
#define QWLAN_HAL_CFG_RETRYRATE_TERTIARY                 21
#define QWLAN_HAL_CFG_FORCE_POLICY_PROTECTION            22
#define QWLAN_HAL_CFG_FIXED_RATE_MULTICAST_24GHZ         23
#define QWLAN_HAL_CFG_FIXED_RATE_MULTICAST_5GHZ          24
#define QWLAN_HAL_CFG_DEFAULT_RATE_INDEX_24GHZ           25
#define QWLAN_HAL_CFG_DEFAULT_RATE_INDEX_5GHZ            26
#define QWLAN_HAL_CFG_MAX_BA_SESSIONS                    27
#define QWLAN_HAL_CFG_PS_DATA_INACTIVITY_TIMEOUT         28
#define QWLAN_HAL_CFG_PS_ENABLE_BCN_FILTER               29
#define QWLAN_HAL_CFG_PS_ENABLE_RSSI_MONITOR             30
#define QWLAN_HAL_CFG_NUM_BEACON_PER_RSSI_AVERAGE        31
#define QWLAN_HAL_CFG_STATS_PERIOD                       32
#define QWLAN_HAL_CFG_CFP_MAX_DURATION                   33
#define QWLAN_HAL_CFG_FRAME_TRANS_ENABLED                34
#define QWLAN_HAL_CFG_DTIM_PERIOD                        35
#define QWLAN_HAL_CFG_EDCA_WMM_ACBK                      36
#define QWLAN_HAL_CFG_EDCA_WMM_ACBE                      37
#define QWLAN_HAL_CFG_EDCA_WMM_ACVO                      38
#define QWLAN_HAL_CFG_EDCA_WMM_ACVI                      39
#define QWLAN_HAL_CFG_BA_THRESHOLD_HIGH                  40
#define QWLAN_HAL_CFG_MAX_BA_BUFFERS                     41
#define QWLAN_HAL_CFG_RPE_POLLING_THRESHOLD              42
#define QWLAN_HAL_CFG_RPE_AGING_THRESHOLD_FOR_AC0_REG    43
#define QWLAN_HAL_CFG_RPE_AGING_THRESHOLD_FOR_AC1_REG    44
#define QWLAN_HAL_CFG_RPE_AGING_THRESHOLD_FOR_AC2_REG    45
#define QWLAN_HAL_CFG_RPE_AGING_THRESHOLD_FOR_AC3_REG    46
#define QWLAN_HAL_CFG_NO_OF_ONCHIP_REORDER_SESSIONS      47
#define QWLAN_HAL_CFG_PS_LISTEN_INTERVAL                 48
#define QWLAN_HAL_CFG_PS_HEART_BEAT_THRESHOLD            49 
#define QWLAN_HAL_CFG_PS_NTH_BEACON_FILTER               50 
#define QWLAN_HAL_CFG_PS_MAX_PS_POLL                     51 
#define QWLAN_HAL_CFG_PS_MIN_RSSI_THRESHOLD              52
#define QWLAN_HAL_CFG_PS_RSSI_FILTER_PERIOD              53 
#define QWLAN_HAL_CFG_PS_BROADCAST_FRAME_FILTER_ENABLE   54
#define QWLAN_HAL_CFG_PS_IGNORE_DTIM                     55
#define QWLAN_HAL_CFG_PS_ENABLE_BCN_EARLY_TERM           56
#define QWLAN_HAL_CFG_DYNAMIC_PS_POLL_VALUE              57
#define QWLAN_HAL_CFG_PS_NULLDATA_AP_RESP_TIMEOUT        58 
#define QWLAN_HAL_CFG_TELE_BCN_WAKEUP_EN                 59
#define QWLAN_HAL_CFG_TELE_BCN_TRANS_LI                  60
#define QWLAN_HAL_CFG_TELE_BCN_TRANS_LI_IDLE_BCNS        61
#define QWLAN_HAL_CFG_TELE_BCN_MAX_LI                    62
#define QWLAN_HAL_CFG_TELE_BCN_MAX_LI_IDLE_BCNS          63
#define QWLAN_HAL_CFG_TX_PWR_CTRL_ENABLE                 64
#define QWLAN_HAL_CFG_VALID_RADAR_CHANNEL_LIST           65 
#define QWLAN_HAL_CFG_TX_POWER_24_20                     66 
#define QWLAN_HAL_CFG_TX_POWER_24_40                     67
#define QWLAN_HAL_CFG_TX_POWER_50_20                     68
#define QWLAN_HAL_CFG_TX_POWER_50_40                     69
#define QWLAN_HAL_CFG_MCAST_BCAST_FILTER_SETTING         70 
#define QWLAN_HAL_CFG_BCN_EARLY_TERM_WAKEUP_INTERVAL     71
#define QCOM_WLAN_CFG_MAX_TX_POWER_2_4                   72
#define QCOM_WLAN_CFG_MAX_TX_POWER_5                     73
#define QWLAN_HAL_CFG_INFRA_STA_KEEP_ALIVE_PERIOD        74
#define QWLAN_HAL_CFG_ENABLE_CLOSE_LOOP                  75
#define QWLAN_HAL_CFG_BTC_EXECUTION_MODE                 76
#define QWLAN_HAL_CFG_BTC_DHCP_BT_SLOTS_TO_BLOCK         77
#define QWLAN_HAL_CFG_BTC_A2DP_DHCP_BT_SUB_INTERVALS     78
#define QWLAN_HAL_CFG_PS_TX_INACTIVITY_TIMEOUT           79
#define QWLAN_HAL_CFG_WCNSS_API_VERSION                  80
#define QWLAN_HAL_CFG_AP_KEEPALIVE_TIMEOUT               81
#define QWLAN_HAL_CFG_GO_KEEPALIVE_TIMEOUT               82
#define QWLAN_HAL_CFG_ENABLE_MC_ADDR_LIST                83
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_INQ_BT              84
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_PAGE_BT             85
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_CONN_BT             86
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_LE_BT               87
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_INQ_WLAN            88
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_PAGE_WLAN           89
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_CONN_WLAN           90
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_LE_WLAN             91
#define QWLAN_HAL_CFG_BTC_DYN_MAX_LEN_BT                 92
#define QWLAN_HAL_CFG_BTC_DYN_MAX_LEN_WLAN               93
#define QWLAN_HAL_CFG_BTC_MAX_SCO_BLOCK_PERC             94
#define QWLAN_HAL_CFG_BTC_DHCP_PROT_ON_A2DP              95
#define QWLAN_HAL_CFG_BTC_DHCP_PROT_ON_SCO               96
#define QWLAN_HAL_CFG_MAX_PARAMS                         97


/*                                                                                */
#define QWLAN_HAL_CFG_INTEGER_PARAM                      93


/*                                                                         
                                            
                                                                         */

/*                     */
#define QWLAN_HAL_CFG_STA_ID_STADEF                  "000AF5898989"
#define QCOM_WLAN_CFG_STA_ID_LEN                     6

/*                                  */
#define QWLAN_HAL_CFG_CURRENT_TX_ANTENNA_STAMIN          1
#define QWLAN_HAL_CFG_CURRENT_TX_ANTENNA_STAMAX          1
#define QWLAN_HAL_CFG_CURRENT_TX_ANTENNA_STADEF          1

/*                                  */
#define QWLAN_HAL_CFG_CURRENT_RX_ANTENNA_STAMIN          1
#define QWLAN_HAL_CFG_CURRENT_RX_ANTENNA_STAMAX          2
#define QWLAN_HAL_CFG_CURRENT_RX_ANTENNA_STADEF          1

/*                                 */
#define QWLAN_HAL_CFG_LOW_GAIN_OVERRIDE_STAMIN           0
#define QWLAN_HAL_CFG_LOW_GAIN_OVERRIDE_STAMAX           1
#define QWLAN_HAL_CFG_LOW_GAIN_OVERRIDE_STADEF           0

/*                                     */
#define QWLAN_HAL_CFG_POWER_STATE_PER_CHAIN_STAMIN             0
#define QWLAN_HAL_CFG_POWER_STATE_PER_CHAIN_STAMAX             65535
#define QWLAN_HAL_CFG_POWER_STATE_PER_CHAIN_STADEF             785
#define QWLAN_HAL_CFG_POWER_STATE_PER_CHAIN_OFF                0
#define QWLAN_HAL_CFG_POWER_STATE_PER_CHAIN_ON                 1
#define QWLAN_HAL_CFG_POWER_STATE_PER_CHAIN_TX                 2
#define QWLAN_HAL_CFG_POWER_STATE_PER_CHAIN_RX                 3
#define QWLAN_HAL_CFG_POWER_STATE_PER_CHAIN_MASK               15
#define QWLAN_HAL_CFG_POWER_STATE_PER_CHAIN_CHAIN_0_OFFSET     0
#define QWLAN_HAL_CFG_POWER_STATE_PER_CHAIN_CHAIN_1_OFFSET     4
#define QWLAN_HAL_CFG_POWER_STATE_PER_CHAIN_CHAIN_2_OFFSET     8

/*                          */
#define QWLAN_HAL_CFG_CAL_PERIOD_STAMIN                  2
#define QWLAN_HAL_CFG_CAL_PERIOD_STAMAX                  10
#define QWLAN_HAL_CFG_CAL_PERIOD_STADEF                  5

/*                           */
#define QWLAN_HAL_CFG_CAL_CONTROL_STAMIN    0
#define QWLAN_HAL_CFG_CAL_CONTROL_STAMAX    1
#define QWLAN_HAL_CFG_CAL_CONTROL_STADEF    0
#define QWLAN_HAL_CFG_CAL_CONTROL_CAL_ON    0
#define QWLAN_HAL_CFG_CAL_CONTROL_CAL_OFF   1

/*                         */
#define QWLAN_HAL_CFG_PROXIMITY_STAMIN    0
#define QWLAN_HAL_CFG_PROXIMITY_STAMAX    1
#define QWLAN_HAL_CFG_PROXIMITY_STADEF    0
#define QWLAN_HAL_CFG_PROXIMITY_OFF       0
#define QWLAN_HAL_CFG_PROXIMITY_ON        1

/*                               */
#define QWLAN_HAL_CFG_NETWORK_DENSITY_STAMIN    0
#define QWLAN_HAL_CFG_NETWORK_DENSITY_STAMAX    3
#define QWLAN_HAL_CFG_NETWORK_DENSITY_STADEF    3
#define QWLAN_HAL_CFG_NETWORK_DENSITY_LOW       0
#define QWLAN_HAL_CFG_NETWORK_DENSITY_MEDIUM    1
#define QWLAN_HAL_CFG_NETWORK_DENSITY_HIGH      2
#define QWLAN_HAL_CFG_NETWORK_DENSITY_ADAPTIVE  3

/*                               */
#define QWLAN_HAL_CFG_MAX_MEDIUM_TIME_STAMIN    0
#define QWLAN_HAL_CFG_MAX_MEDIUM_TIME_STAMAX    65535
#define QWLAN_HAL_CFG_MAX_MEDIUM_TIME_STADEF    1024

/*                                  */
#define QWLAN_HAL_CFG_MAX_MPDUS_IN_AMPDU_STAMIN    0
#define QWLAN_HAL_CFG_MAX_MPDUS_IN_AMPDU_STAMAX    65535
#define QWLAN_HAL_CFG_MAX_MPDUS_IN_AMPDU_STADEF    64

/*                             */
#define QWLAN_HAL_CFG_RTS_THRESHOLD_STAMIN               0
#define QWLAN_HAL_CFG_RTS_THRESHOLD_STAMAX               2347
#define QWLAN_HAL_CFG_RTS_THRESHOLD_STADEF               2347

/*                                 */
#define QWLAN_HAL_CFG_SHORT_RETRY_LIMIT_STAMIN    0
#define QWLAN_HAL_CFG_SHORT_RETRY_LIMIT_STAMAX    255
#define QWLAN_HAL_CFG_SHORT_RETRY_LIMIT_STADEF    15

/*                                */
#define QWLAN_HAL_CFG_LONG_RETRY_LIMIT_STAMIN    0
#define QWLAN_HAL_CFG_LONG_RETRY_LIMIT_STAMAX    255
#define QWLAN_HAL_CFG_LONG_RETRY_LIMIT_STADEF    15

/*                                       */
#define QWLAN_HAL_CFG_FRAGMENTATION_THRESHOLD_STAMIN    256
#define QWLAN_HAL_CFG_FRAGMENTATION_THRESHOLD_STAMAX    8000
#define QWLAN_HAL_CFG_FRAGMENTATION_THRESHOLD_STADEF    8000

/*                                      */
#define QWLAN_HAL_CFG_DYNAMIC_THRESHOLD_ZERO_STAMIN    0
#define QWLAN_HAL_CFG_DYNAMIC_THRESHOLD_ZERO_STAMAX    255
#define QWLAN_HAL_CFG_DYNAMIC_THRESHOLD_ZERO_STADEF    5

/*                                     */
#define QWLAN_HAL_CFG_DYNAMIC_THRESHOLD_ONE_STAMIN    0
#define QWLAN_HAL_CFG_DYNAMIC_THRESHOLD_ONE_STAMAX    255
#define QWLAN_HAL_CFG_DYNAMIC_THRESHOLD_ONE_STADEF    10

/*                                     */
#define QWLAN_HAL_CFG_DYNAMIC_THRESHOLD_TWO_STAMIN    0
#define QWLAN_HAL_CFG_DYNAMIC_THRESHOLD_TWO_STAMAX    255
#define QWLAN_HAL_CFG_DYNAMIC_THRESHOLD_TWO_STADEF    15

/*                         
                                                               
                                                               
 */
#define QWLAN_HAL_CFG_FIXED_RATE_STAMIN                        0
#define QWLAN_HAL_CFG_FIXED_RATE_STAMAX                        44
#define QWLAN_HAL_CFG_FIXED_RATE_STADEF                        0
#define QWLAN_HAL_CFG_FIXED_RATE_AUTO                          0
#define QWLAN_HAL_CFG_FIXED_RATE_1MBPS                         1
#define QWLAN_HAL_CFG_FIXED_RATE_2MBPS                         2
#define QWLAN_HAL_CFG_FIXED_RATE_5_5MBPS                       3
#define QWLAN_HAL_CFG_FIXED_RATE_11MBPS                        4
#define QWLAN_HAL_CFG_FIXED_RATE_6MBPS                         5
#define QWLAN_HAL_CFG_FIXED_RATE_9MBPS                         6
#define QWLAN_HAL_CFG_FIXED_RATE_12MBPS                        7
#define QWLAN_HAL_CFG_FIXED_RATE_18MBPS                        8
#define QWLAN_HAL_CFG_FIXED_RATE_24MBPS                        9
#define QWLAN_HAL_CFG_FIXED_RATE_36MBPS                        10
#define QWLAN_HAL_CFG_FIXED_RATE_48MBPS                        11
#define QWLAN_HAL_CFG_FIXED_RATE_54MBPS                        12
#define QWLAN_HAL_CFG_FIXED_RATE_6_5MBPS_MCS0_20MHZ_SIMO       13
#define QWLAN_HAL_CFG_FIXED_RATE_13MBPS_MCS1_20MHZ_SIMO        14
#define QWLAN_HAL_CFG_FIXED_RATE_19_5MBPS_MCS2_20MHZ_SIMO      15
#define QWLAN_HAL_CFG_FIXED_RATE_26MBPS_MCS3_20MHZ_SIMO        16
#define QWLAN_HAL_CFG_FIXED_RATE_39MBPS_MCS4_20MHZ_SIMO        17
#define QWLAN_HAL_CFG_FIXED_RATE_52MBPS_MCS5_20MHZ_SIMO        18
#define QWLAN_HAL_CFG_FIXED_RATE_58_5MBPS_MCS6_20MHZ_SIMO      19
#define QWLAN_HAL_CFG_FIXED_RATE_65MBPS_MCS7_20MHZ_SIMO        20
#define QWLAN_HAL_CFG_FIXED_RATE_7_2MBPS_MCS0_20MHZ_SIMO_SGI   21
#define QWLAN_HAL_CFG_FIXED_RATE_14_4MBPS_MCS1_20MHZ_SIMO_SGI  22
#define QWLAN_HAL_CFG_FIXED_RATE_21_7MBPS_MCS2_20MHZ_SIMO_SGI  23
#define QWLAN_HAL_CFG_FIXED_RATE_28_9MBPS_MCS3_20MHZ_SIMO_SGI  24
#define QWLAN_HAL_CFG_FIXED_RATE_43_3MBPS_MCS4_20MHZ_SIMO_SGI  25
#define QWLAN_HAL_CFG_FIXED_RATE_57_8MBPS_MCS5_20MHZ_SIMO_SGI  26
#define QWLAN_HAL_CFG_FIXED_RATE_65MBPS_MCS6_20MHZ_SIMO_SGI    27
#define QWLAN_HAL_CFG_FIXED_RATE_72_2MBPS_MCS7_20MHZ_SIMO_SGI  28
#define QWLAN_HAL_CFG_FIXED_RATE_13_5MBPS_MCS0_40MHZ_SIMO      29
#define QWLAN_HAL_CFG_FIXED_RATE_27MBPS_MCS1_40MHZ_SIMO        30
#define QWLAN_HAL_CFG_FIXED_RATE_40_5MBPS_MCS2_40MHZ_SIMO      31
#define QWLAN_HAL_CFG_FIXED_RATE_54MBPS_MCS3_40MHZ_SIMO        32
#define QWLAN_HAL_CFG_FIXED_RATE_81MBPS_MCS4_40MHZ_SIMO        33
#define QWLAN_HAL_CFG_FIXED_RATE_108MBPS_MCS5_40MHZ_SIMO       34
#define QWLAN_HAL_CFG_FIXED_RATE_121_5MBPS_MCS6_40MHZ_SIMO     35
#define QWLAN_HAL_CFG_FIXED_RATE_135MBPS_MCS7_40MHZ_SIMO       36
#define QWLAN_HAL_CFG_FIXED_RATE_15MBPS_MCS0_40MHZ_SIMO_SGI    37
#define QWLAN_HAL_CFG_FIXED_RATE_30MBPS_MCS1_40MHZ_SIMO_SGI    38
#define QWLAN_HAL_CFG_FIXED_RATE_45MBPS_MCS2_40MHZ_SIMO_SGI    39
#define QWLAN_HAL_CFG_FIXED_RATE_60MBPS_MCS3_40MHZ_SIMO_SGI    40
#define QWLAN_HAL_CFG_FIXED_RATE_90MBPS_MCS4_40MHZ_SIMO_SGI    41
#define QWLAN_HAL_CFG_FIXED_RATE_120MBPS_MCS5_40MHZ_SIMO_SGI   42
#define QWLAN_HAL_CFG_FIXED_RATE_135MBPS_MCS6_40MHZ_SIMO_SGI   43
#define QWLAN_HAL_CFG_FIXED_RATE_150MBPS_MCS7_40MHZ_SIMO_SGI   44

/*                                */
#define QWLAN_HAL_CFG_RETRYRATE_POLICY_STAMIN         0
#define QWLAN_HAL_CFG_RETRYRATE_POLICY_STAMAX         255
#define QWLAN_HAL_CFG_RETRYRATE_POLICY_STADEF         4
#define QWLAN_HAL_CFG_RETRYRATE_POLICY_MIN_SUPPORTED  0
#define QWLAN_HAL_CFG_RETRYRATE_POLICY_PRIMARY        1
#define QWLAN_HAL_CFG_RETRYRATE_POLICY_RESERVED       2
#define QWLAN_HAL_CFG_RETRYRATE_POLICY_CLOSEST        3
#define QWLAN_HAL_CFG_RETRYRATE_POLICY_AUTOSELECT     4
#define QWLAN_HAL_CFG_RETRYRATE_POLICY_MAX            5

/*                                   */
#define QWLAN_HAL_CFG_RETRYRATE_SECONDARY_STAMIN    0
#define QWLAN_HAL_CFG_RETRYRATE_SECONDARY_STAMAX    255
#define QWLAN_HAL_CFG_RETRYRATE_SECONDARY_STADEF    0

/*                                  */
#define QWLAN_HAL_CFG_RETRYRATE_TERTIARY_STAMIN    0
#define QWLAN_HAL_CFG_RETRYRATE_TERTIARY_STAMAX    255
#define QWLAN_HAL_CFG_RETRYRATE_TERTIARY_STADEF    0

/*                                       */
#define QWLAN_HAL_CFG_FORCE_POLICY_PROTECTION_STAMIN     0
#define QWLAN_HAL_CFG_FORCE_POLICY_PROTECTION_STAMAX     5
#define QWLAN_HAL_CFG_FORCE_POLICY_PROTECTION_STADEF     5
#define QWLAN_HAL_CFG_FORCE_POLICY_PROTECTION_DISABLE    0
#define QWLAN_HAL_CFG_FORCE_POLICY_PROTECTION_CTS        1
#define QWLAN_HAL_CFG_FORCE_POLICY_PROTECTION_RTS        2
#define QWLAN_HAL_CFG_FORCE_POLICY_PROTECTION_DUAL_CTS   3
#define QWLAN_HAL_CFG_FORCE_POLICY_PROTECTION_RTS_ALWAYS 4
#define QWLAN_HAL_CFG_FORCE_POLICY_PROTECTION_AUTO       5

/*                                          */
#define QWLAN_HAL_CFG_FIXED_RATE_MULTICAST_24GHZ_STAMIN    0
#define QWLAN_HAL_CFG_FIXED_RATE_MULTICAST_24GHZ_STAMAX   QWLAN_HAL_CFG_FIXED_RATE_STAMAX
#define QWLAN_HAL_CFG_FIXED_RATE_MULTICAST_24GHZ_STADEF   QWLAN_HAL_CFG_FIXED_RATE_1MBPS

/*                                         */
#define QWLAN_HAL_CFG_FIXED_RATE_MULTICAST_5GHZ_STAMIN    0
#define QWLAN_HAL_CFG_FIXED_RATE_MULTICAST_5GHZ_STAMAX    QWLAN_HAL_CFG_FIXED_RATE_STAMAX
#define QWLAN_HAL_CFG_FIXED_RATE_MULTICAST_5GHZ_STADEF    QWLAN_HAL_CFG_FIXED_RATE_6MBPS

/*                                        */
#define QWLAN_HAL_CFG_DEFAULT_RATE_INDEX_24GHZ_STAMIN    0
#define QWLAN_HAL_CFG_DEFAULT_RATE_INDEX_24GHZ_STAMAX     QWLAN_HAL_CFG_FIXED_RATE_STAMAX
#define QWLAN_HAL_CFG_DEFAULT_RATE_INDEX_24GHZ_STADEF     QWLAN_HAL_CFG_FIXED_RATE_1MBPS

/*                                       */
#define QWLAN_HAL_CFG_DEFAULT_RATE_INDEX_5GHZ_STAMIN    0
#define QWLAN_HAL_CFG_DEFAULT_RATE_INDEX_5GHZ_STAMAX      QWLAN_HAL_CFG_FIXED_RATE_STAMAX
#define QWLAN_HAL_CFG_DEFAULT_RATE_INDEX_5GHZ_STADEF      QWLAN_HAL_CFG_FIXED_RATE_6MBPS

/*                               */
#define QWLAN_HAL_CFG_MAX_BA_SESSIONS_STAMIN    0
#define QWLAN_HAL_CFG_MAX_BA_SESSIONS_STAMAX    64
#define QWLAN_HAL_CFG_MAX_BA_SESSIONS_STADEF    40

/*                                          */
#define QWLAN_HAL_CFG_PS_DATA_INACTIVITY_TIMEOUT_STAMIN    1
#define QWLAN_HAL_CFG_PS_DATA_INACTIVITY_TIMEOUT_STAMAX    255
#define QWLAN_HAL_CFG_PS_DATA_INACTIVITY_TIMEOUT_STADEF    20

/*                                        */
#define QWLAN_HAL_CFG_PS_TX_INACTIVITY_TIMEOUT_STAMIN    0
#define QWLAN_HAL_CFG_PS_TX_INACTIVITY_TIMEOUT_STAMAX    255
#define QWLAN_HAL_CFG_PS_TX_INACTIVITY_TIMEOUT_STADEF    300

/*                                    */
#define QWLAN_HAL_CFG_PS_ENABLE_BCN_FILTER_STAMIN    0
#define QWLAN_HAL_CFG_PS_ENABLE_BCN_FILTER_STAMAX    1
#define QWLAN_HAL_CFG_PS_ENABLE_BCN_FILTER_STADEF    1

/*                                      */
#define QWLAN_HAL_CFG_PS_ENABLE_RSSI_MONITOR_STAMIN    0
#define QWLAN_HAL_CFG_PS_ENABLE_RSSI_MONITOR_STAMAX    1
#define QWLAN_HAL_CFG_PS_ENABLE_RSSI_MONITOR_STADEF    1

/*                                           */
#define QWLAN_HAL_CFG_NUM_BEACON_PER_RSSI_AVERAGE_STAMIN    1
#define QWLAN_HAL_CFG_NUM_BEACON_PER_RSSI_AVERAGE_STAMAX    20
#define QWLAN_HAL_CFG_NUM_BEACON_PER_RSSI_AVERAGE_STADEF    20

/*                            */
#define QWLAN_HAL_CFG_STATS_PERIOD_STAMIN    1
#define QWLAN_HAL_CFG_STATS_PERIOD_STAMAX    10
#define QWLAN_HAL_CFG_STATS_PERIOD_STADEF    10

/*                                */
#define QWLAN_HAL_CFG_CFP_MAX_DURATION_STAMIN    0
#define QWLAN_HAL_CFG_CFP_MAX_DURATION_STAMAX    65535
#define QWLAN_HAL_CFG_CFP_MAX_DURATION_STADEF    30000

/*                                   */
#define QWLAN_HAL_CFG_FRAME_TRANS_ENABLED_STAMIN  0
#define QWLAN_HAL_CFG_FRAME_TRANS_ENABLED_STAMAX  1
#define QWLAN_HAL_CFG_FRAME_TRANS_ENABLED_STADEF  0

/*                           */
#define QWLAN_HAL_CFG_DTIM_PERIOD_STAMIN    0
#define QWLAN_HAL_CFG_DTIM_PERIOD_STAMAX    65535
#define QWLAN_HAL_CFG_DTIM_PERIOD_STADEF    1

/*                                 */
#define QWLAN_HAL_CFG_BA_THRESHOLD_HIGH_STAMIN    0
#define QWLAN_HAL_CFG_BA_THRESHOLD_HIGH_STAMAX    65535
#define QWLAN_HAL_CFG_BA_THRESHOLD_HIGH_STADEF    1

/*                              */
#define QWLAN_HAL_CFG_MAX_BA_BUFFERS_STAMIN    0
#define QWLAN_HAL_CFG_MAX_BA_BUFFERS_STAMAX    2560
#define QWLAN_HAL_CFG_MAX_BA_BUFFERS_STADEF    2560



/*                                              
                                                                        
                              */
#define QWLAN_HAL_CFG_EDCA_PROFILE_ACM_IDX       0   /*         */
#define QWLAN_HAL_CFG_EDCA_PROFILE_AIFSN_IDX     1   /*         */
#define QWLAN_HAL_CFG_EDCA_PROFILE_CWMINA_IDX    2   /*                      */
#define QWLAN_HAL_CFG_EDCA_PROFILE_CWMAXA_IDX    4   /*                      */
#define QWLAN_HAL_CFG_EDCA_PROFILE_TXOPA_IDX     6   /*         */
#define QWLAN_HAL_CFG_EDCA_PROFILE_CWMINB_IDX    7   /*                      */
#define QWLAN_HAL_CFG_EDCA_PROFILE_CWMAXB_IDX    9   /*                      */
#define QWLAN_HAL_CFG_EDCA_PROFILE_TXOPB_IDX     11  /*         */  
#define QWLAN_HAL_CFG_EDCA_PROFILE_CWMING_IDX    12  /*                      */
#define QWLAN_HAL_CFG_EDCA_PROFILE_CWMAXG_IDX    14  /*                      */
#define QWLAN_HAL_CFG_EDCA_PROFILE_TXOPG_IDX     16  /*         */
#define QWLAN_HAL_CFG_EDCA_PARAM_MAX_LEN         20

/*                             */
#define QWLAN_HAL_CFG_EDCA_WMM_ACBK_DEFAULT  "0007000F03FF00001F03FF00000F03FF00"

/*                             */
#define QWLAN_HAL_CFG_EDCA_WMM_ACBE_DEFAULT  "0003000F03FF00001F03FF00000F03FF00"

/*                             */
#define QWLAN_HAL_CFG_EDCA_WMM_ACVI_DEFAULT  "00020007000F5E000F001FBC0007000F5E"

/*                             */
#define QWLAN_HAL_CFG_EDCA_WMM_ACVO_DEFAULT  "0002000300072F0007000F66000300072F"


/*                                     */
#define QWLAN_CFG_RPE_POLLING_THRESHOLD_STAMIN            0
#define QWLAN_CFG_RPE_POLLING_THRESHOLD_STAMAX            65535
#define QWLAN_CFG_RPE_POLLING_THRESHOLD_STADEF            30

/*                                               */
#define QWLAN_CFG_RPE_AGING_THRESHOLD_FOR_AC0_REG_STAMIN   0
#define QWLAN_CFG_RPE_AGING_THRESHOLD_FOR_AC0_REG_STAMAX   65535
#define QWLAN_CFG_RPE_AGING_THRESHOLD_FOR_AC0_REG_STADEF   30

/*                                               */
#define QWLAN_CFG_RPE_AGING_THRESHOLD_FOR_AC1_REG_STAMIN   0
#define QWLAN_CFG_RPE_AGING_THRESHOLD_FOR_AC1_REG_STAMAX   65535
#define QWLAN_CFG_RPE_AGING_THRESHOLD_FOR_AC1_REG_STADEF   30

/*                                               */
#define QWLAN_CFG_RPE_AGING_THRESHOLD_FOR_AC2_REG_STAMIN   0
#define QWLAN_CFG_RPE_AGING_THRESHOLD_FOR_AC2_REG_STAMAX   65535
#define QWLAN_CFG_RPE_AGING_THRESHOLD_FOR_AC2_REG_STADEF   30

/*                                               */
#define QWLAN_CFG_RPE_AGING_THRESHOLD_FOR_AC3_REG_STAMIN   0
#define QWLAN_CFG_RPE_AGING_THRESHOLD_FOR_AC3_REG_STAMAX   65535
#define QWLAN_CFG_RPE_AGING_THRESHOLD_FOR_AC3_REG_STADEF   30

/*                                             */
#define QWLAN_CFG_NO_OF_ONCHIP_REORDER_SESSIONS_STAMIN     0
#define QWLAN_CFG_NO_OF_ONCHIP_REORDER_SESSIONS_STAMAX     2
#define QWLAN_CFG_NO_OF_ONCHIP_REORDER_SESSIONS_STADEF     1

#define QWLAN_HAL_CFG_PS_LISTEN_INTERVAL_STAMIN    0
#define QWLAN_HAL_CFG_PS_LISTEN_INTERVAL_STAMAX    65535
#define QWLAN_HAL_CFG_PS_LISTEN_INTERVAL_STADEF    1

#define QWLAN_HAL_CFG_PS_HEART_BEAT_THRESHOLD_STAMIN    0
#define QWLAN_HAL_CFG_PS_HEART_BEAT_THRESHOLD_STAMAX    65535
#define QWLAN_HAL_CFG_PS_HEART_BEAT_THRESHOLD_STADEF    40

#define QWLAN_HAL_CFG_PS_NTH_BEACON_FILTER_STAMIN    0
#define QWLAN_HAL_CFG_PS_NTH_BEACON_FILTER_STAMAX    255
#define QWLAN_HAL_CFG_PS_NTH_BEACON_FILTER_STADEF    10

#define QWLAN_HAL_CFG_PS_MAX_PS_POLL_STAMIN    0
#define QWLAN_HAL_CFG_PS_MAX_PS_POLL_STAMAX    255
#define QWLAN_HAL_CFG_PS_MAX_PS_POLL_STADEF    0

#define QWLAN_HAL_CFG_PS_MIN_RSSI_THRESHOLD_STAMIN    0
#define QWLAN_HAL_CFG_PS_MIN_RSSI_THRESHOLD_STAMAX    10
#define QWLAN_HAL_CFG_PS_MIN_RSSI_THRESHOLD_STADEF    10

#define QWLAN_HAL_CFG_PS_RSSI_FILTER_PERIOD_STAMIN    0
#define QWLAN_HAL_CFG_PS_RSSI_FILTER_PERIOD_STAMAX    255
#define QWLAN_HAL_CFG_PS_RSSI_FILTER_PERIOD_STADEF    20

#define QWLAN_HAL_CFG_PS_BROADCAST_FRAME_FILTER_ENABLE_STAMIN    0
#define QWLAN_HAL_CFG_PS_BROADCAST_FRAME_FILTER_ENABLE_STAMAX    1
#define QWLAN_HAL_CFG_PS_BROADCAST_FRAME_FILTER_ENABLE_STADEF    0

#define QWLAN_HAL_CFG_PS_IGNORE_DTIM_STAMIN    0
#define QWLAN_HAL_CFG_PS_IGNORE_DTIM_STAMAX    1
#define QWLAN_HAL_CFG_PS_IGNORE_DTIM_STADEF    0

#define QWLAN_HAL_CFG_PS_ENABLE_BCN_EARLY_TERM_STAMIN    0
#define QWLAN_HAL_CFG_PS_ENABLE_BCN_EARLY_TERM_STAMAX    1
#define QWLAN_HAL_CFG_PS_ENABLE_BCN_EARLY_TERM_STADEF    0

#define QWLAN_HAL_CFG_DYNAMIC_PS_POLL_VALUE_STAMIN    0
#define QWLAN_HAL_CFG_DYNAMIC_PS_POLL_VALUE_STAMAX    255
#define QWLAN_HAL_CFG_DYNAMIC_PS_POLL_VALUE_STADEF    0

#define QWLAN_HAL_CFG_PS_NULLDATA_AP_RESP_TIMEOUT_STAMIN    0
#define QWLAN_HAL_CFG_PS_NULLDATA_AP_RESP_TIMEOUT_STAMAX    80
#define QWLAN_HAL_CFG_PS_NULLDATA_AP_RESP_TIMEOUT_STADEF    0

/*                                  */
#define QWLAN_CFG_TX_PWR_CTRL_ENABLE_STAMIN    0
#define QWLAN_CFG_TX_PWR_CTRL_ENABLE_STAMAX    1
#define QWLAN_CFG_TX_PWR_CTRL_ENABLE_STADEF    1

#define QWLAN_HAL_CFG_TELE_BCN_WAKEUP_EN_STAMIN    0
#define QWLAN_HAL_CFG_TELE_BCN_WAKEUP_EN_STAMAX    1
#define QWLAN_HAL_CFG_TELE_BCN_WAKEUP_EN_STADEF    0

#define QWLAN_HAL_CFG_TELE_BCN_TRANS_LI_STAMIN    0
#define QWLAN_HAL_CFG_TELE_BCN_TRANS_LI_STAMAX    7
#define QWLAN_HAL_CFG_TELE_BCN_TRANS_LI_STADEF    3

#define QWLAN_HAL_CFG_TELE_BCN_TRANS_LI_IDLE_BCNS_STAMIN    5
#define QWLAN_HAL_CFG_TELE_BCN_TRANS_LI_IDLE_BCNS_STAMAX    255
#define QWLAN_HAL_CFG_TELE_BCN_TRANS_LI_IDLE_BCNS_STADEF    10

#define QWLAN_HAL_CFG_TELE_BCN_MAX_LI_STAMIN    0
#define QWLAN_HAL_CFG_TELE_BCN_MAX_LI_STAMAX    7
#define QWLAN_HAL_CFG_TELE_BCN_MAX_LI_STADEF    5

#define QWLAN_HAL_CFG_TELE_BCN_MAX_LI_IDLE_BCNS_STAMIN    5
#define QWLAN_HAL_CFG_TELE_BCN_MAX_LI_IDLE_BCNS_STAMAX    255
#define QWLAN_HAL_CFG_TELE_BCN_MAX_LI_IDLE_BCNS_STADEF    15

#define QWLAN_HAL_CFG_MCAST_BCAST_FILTER_SETTING_STAMIN    0
#define QWLAN_HAL_CFG_MCAST_BCAST_FILTER_SETTING_STAMAX    3
#define QWLAN_HAL_CFG_MCAST_BCAST_FILTER_SETTING_STADEF    0

#define QWLAN_HAL_CFG_BCN_EARLY_TERM_WAKEUP_INTERVAL_STAMIN    1
#define QWLAN_HAL_CFG_BCN_EARLY_TERM_WAKEUP_INTERVAL_STAMAX    255
#define QWLAN_HAL_CFG_BCN_EARLY_TERM_WAKEUP_INTERVAL_STADEF    5

/*                                 */
/*                                */
#define QWLAN_HAL_CFG_VALID_RADAR_CHANNEL_LIST_DEFAULT "36"
#define QWLAN_HAL_CFG_RADAR_CHANNEL_LIST_LEN    20

/*                              */
#define QWLAN_WLAN_TX_POWER_24_20_DEFAULT    299 
#define QWLAN_WLAN_TX_POWER_24_20_MIN        299 
#define QWLAN_WLAN_TX_POWER_24_20_MAX        299 

/*                              */
#define QWLAN_WLAN_TX_POWER_24_40_DEFAULT    300
#define QWLAN_WLAN_TX_POWER_24_40_MIN        299 
#define QWLAN_WLAN_TX_POWER_24_40_MAX        299 

/*                              */
#define QWLAN_WLAN_TX_POWER_50_20_DEFAULT    301
#define QWLAN_WLAN_TX_POWER_50_20_MIN        299 
#define QWLAN_WLAN_TX_POWER_50_20_MAX        299 

/*                              */
#define QWLAN_WLAN_TX_POWER_50_40_DEFAULT    302
#define QWLAN_WLAN_TX_POWER_50_40_MIN        299 
#define QWLAN_WLAN_TX_POWER_50_40_MAX        299 

/*                                */
#define QCOM_WLAN_CFG_MAX_TX_POWER_2_4_LEN      128
/*                                                                                                          */
#define QCOM_WLAN_CFG_MAX_TX_POWER_2_4_DEFAULT  "010E14"

/*                              */
#define QCOM_WLAN_CFG_MAX_TX_POWER_5_LEN     128
/*                                                                                                                */
#define QCOM_WLAN_CFG_MAX_TX_POWER_5_DEFAULT  "248214"


#define QWLAN_HAL_CFG_INFRA_STA_KEEP_ALIVE_PERIOD_STAMIN    0
#define QWLAN_HAL_CFG_INFRA_STA_KEEP_ALIVE_PERIOD_STAMAX    65535
#define QWLAN_HAL_CFG_INFRA_STA_KEEP_ALIVE_PERIOD_STADEF    0

#define QWLAN_HAL_CFG_ENABLE_CLOSE_LOOP_MIN  0
#define QWLAN_HAL_CFG_ENABLE_CLOSE_LOOP_MAX  1
#define QWLAN_HAL_CFG_ENABLE_CLOSE_LOOP_DEF  0

/*                                  */
#define QWLAN_HAL_CFG_BTC_EXECUTION_MODE_MIN  0
#define QWLAN_HAL_CFG_BTC_EXECUTION_MODE_MAX  5
#define QWLAN_HAL_CFG_BTC_EXECUTION_MODE_DEF  0

/*                                          */
#define QWLAN_HAL_CFG_BTC_DHCP_BT_SLOTS_TO_BLOCK_MIN  0
#define QWLAN_HAL_CFG_BTC_DHCP_BT_SLOTS_TO_BLOCK_MAX  255
#define QWLAN_HAL_CFG_BTC_DHCP_BT_SLOTS_TO_BLOCK_DEF  0

/*                                              */
#define QWLAN_HAL_CFG_BTC_A2DP_DHCP_BT_SUB_INTERVALS_MIN  0
#define QWLAN_HAL_CFG_BTC_A2DP_DHCP_BT_SUB_INTERVALS_MAX  255
#define QWLAN_HAL_CFG_BTC_A2DP_DHCP_BT_SUB_INTERVALS_DEF  15

/*                                 */
#define QWLAN_HAL_CFG_WCNSS_API_VERSION_MIN  0           /*                       */
#define QWLAN_HAL_CFG_WCNSS_API_VERSION_MAX  4294967295U /*                               */
#define QWLAN_HAL_CFG_WCNSS_API_VERSION_DEF  0           /*                       */

/*                                    */
#define QWLAN_HAL_CFG_AP_KEEPALIVE_TIMEOUT_MIN  1
#define QWLAN_HAL_CFG_AP_KEEPALIVE_TIMEOUT_MAX  255
#define QWLAN_HAL_CFG_AP_KEEPALIVE_TIMEOUT_DEF  20

/*                                    */
#define QWLAN_HAL_CFG_GO_KEEPALIVE_TIMEOUT_MIN  1
#define QWLAN_HAL_CFG_GO_KEEPALIVE_TIMEOUT_MAX  255
#define QWLAN_HAL_CFG_GO_KEEPALIVE_TIMEOUT_DEF  20

/*                                   */
#define QWLAN_HAL_CFG_ENABLE_MC_ADDR_LIST_MIN  0
#define QWLAN_HAL_CFG_ENABLE_MC_ADDR_LIST_MAX  1
#define QWLAN_HAL_CFG_ENABLE_MC_ADDR_LIST_DEF  0

/*                                     */
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_INQ_BT_MIN 5000
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_INQ_BT_MAX 500000
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_INQ_BT_DEF 120000

/*                                      */
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_PAGE_BT_MIN 5000
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_PAGE_BT_MAX 500000
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_PAGE_BT_DEF 10000

/*                                      */
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_CONN_BT_MIN 5000
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_CONN_BT_MAX 500000
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_CONN_BT_DEF 10000

/*                                    */
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_LE_BT_MIN 5000
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_LE_BT_MAX 500000
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_LE_BT_DEF 10000

/*                                       */
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_INQ_WLAN_MIN 0
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_INQ_WLAN_MAX 500000
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_INQ_WLAN_DEF 30000

/*                                        */
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_PAGE_WLAN_MIN 0
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_PAGE_WLAN_MAX 500000
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_PAGE_WLAN_DEF 0

/*                                        */
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_CONN_WLAN_MIN 0
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_CONN_WLAN_MAX 500000
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_CONN_WLAN_DEF 0

/*                                      */
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_LE_WLAN_MIN 0
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_LE_WLAN_MAX 500000
#define QWLAN_HAL_CFG_BTC_STATIC_LEN_LE_WLAN_DEF 0

/*                                  */
#define QWLAN_HAL_CFG_BTC_DYN_MAX_LEN_BT_MIN 25000
#define QWLAN_HAL_CFG_BTC_DYN_MAX_LEN_BT_MAX 500000
#define QWLAN_HAL_CFG_BTC_DYN_MAX_LEN_BT_DEF 250000

/*                                    */
#define QWLAN_HAL_CFG_BTC_DYN_MAX_LEN_WLAN_MIN 15000
#define QWLAN_HAL_CFG_BTC_DYN_MAX_LEN_WLAN_MAX 500000
#define QWLAN_HAL_CFG_BTC_DYN_MAX_LEN_WLAN_DEF 45000

/*                                      */
#define QWLAN_HAL_CFG_BTC_MAX_SCO_BLOCK_PERC_MIN 0
#define QWLAN_HAL_CFG_BTC_MAX_SCO_BLOCK_PERC_MAX 100
#define QWLAN_HAL_CFG_BTC_MAX_SCO_BLOCK_PERC_DEF 1

/*                                     */
#define QWLAN_HAL_CFG_BTC_DHCP_PROT_ON_A2DP_MIN 0
#define QWLAN_HAL_CFG_BTC_DHCP_PROT_ON_A2DP_MAX 1
#define QWLAN_HAL_CFG_BTC_DHCP_PROT_ON_A2DP_DEF 1

/*                                    */
#define QWLAN_HAL_CFG_BTC_DHCP_PROT_ON_SCO_MIN 0
#define QWLAN_HAL_CFG_BTC_DHCP_PROT_ON_SCO_MAX 1
#define QWLAN_HAL_CFG_BTC_DHCP_PROT_ON_SCO_DEF 0

typedef struct 
{
   uint8    cfgStaId[QCOM_WLAN_CFG_STA_ID_LEN]; //                    
   uint8    reserved[2];               //                                                        
   uint32   cfgCurrentTxAntenna;       //                                
   uint32   cfgCurrentRxAntenna;       //                                
   uint32   cfgLowGainOverride;        //                               
   uint32   cfgPowerStatePerChain;     //                                   
   uint32   cfgCalPeriod;              //                        
   uint32   cfgCalControl;             //                         
   uint32   cfgProximity;              //                       
   uint32   cfgNetworkDensity;         //                             
   uint32   cfgMaxMediumTime;          //                             
   uint32   cfgMaxMpdusInAmpu;         //                                
   uint32   cfgRtsThreshold;           //                           
   uint32   cfgShortRetryLimit;        //                               
   uint32   cfgLongRetryLimit;         //                              
   uint32   cfgFragmentationThreshold; //                                     
   uint32   cfgDynamicThresholdZero;   //                                    
   uint32   cfgDynamicThresholdOne;    //                                   
   uint32   cfgDynamicThresholdTwo;    //                                   
   uint32   cfgFixedRate;              //                        
   uint32   cfgRetryRatePolicy;        //                              
   uint32   cfgRetryRateSecondary;     //                                 
   uint32   cfgRetryRateTertiary;      //                                
   uint32   cfgForcePolicyProtection;  //                                     
   uint32   cfgFixedRateMcast24GHz;    //                                        
   uint32   cfgFixedRateMcast5GHz;     //                                       
   uint32   cfgDefaultRateIndex24GHz;  //                                      
   uint32   cfgDefaultRateIndex5GHz;   //                                     
   uint32   cfgMaxBaSessions;          //                             
   uint32   cfgPsDataInactivityTimeout;//                                        
   uint32   cfgPsTxInactivityTimeout;  //                                      
   uint32   cfgPsEnableBcnFilter;      //                                  
   uint32   cfgPsEnableRssiMonitor;    //                                    
   uint32   cfgNumBeaconPerRssiAverage;//                                         
   uint32   cfgStatsPeriod;            //                          
   uint32   cfgCfpMaxDuration;         //                              
   uint32   cfgFrameTransEnabled;      //                                 
   uint32   cfgDtimPeriod;             //                         
   uint8    cfgEdcaWmmAcBk[QWLAN_HAL_CFG_EDCA_PARAM_MAX_LEN]; //                           
   uint8    cfgEdcaWmmAcBe[QWLAN_HAL_CFG_EDCA_PARAM_MAX_LEN]; //                           
   uint8    cfgEdcaWmmAcVo[QWLAN_HAL_CFG_EDCA_PARAM_MAX_LEN]; //                           
   uint8    cfgEdcaWmmAcVi[QWLAN_HAL_CFG_EDCA_PARAM_MAX_LEN]; //                           
   uint32   cfgbaSetupThresholdHigh;          //                               
   uint32   cfgbaRxMaxAvailBuffers;           //                            
   uint32   cfgRpePollingThreshold;           //                                   
   uint32   cfgRpeAgingThresholdForAc0Reg;    //                                             
   uint32   cfgRpeAgingThresholdForAc1Reg;    //                                             
   uint32   cfgRpeAgingThresholdForAc2Reg;    //                                             
   uint32   cfgRpeAgingThresholdForAc3Reg;    //                                             
   uint32   cfgNoOfOnchipReorderSessions;     //                                           
   uint32   cfgPsListenInterval;              //                                
   uint32   cfgPsHeartBeatThreshold;          //                                     
   uint32   cfgPsNthBeaconFilter;             //                                  
   uint32   cfgPsMaxPsPoll;                   //                            
   uint32   cfgPsMinRssiThreshold;            //                                   
   uint32   cfgPsRssiFilterPeriod;            //                                   
   uint32   cfgPsBroadcastFrameFilterEnable;  //                                              
   uint32   cfgPsIgnoreDtim;                  //                            
   uint32   cfgPsEnableBcnEarlyTerm;          //                                      
   uint32   cfgDynamicPsPollValue;            //                                   
   uint32   cfgPsNullDataApRespTimeout;       //                                         
   uint32   cfgTxPowerEnable;                 //                                
   uint32   cfgTeleBcnWakeupEn;               //                                
   uint32   cfgTeleBcnTransLi;                //                               
   uint32   cfgTeleBcnTransLiIdleBcns;        //                                         
   uint32   cfgTeleBcnMaxLi;                  //                             
   uint32   cfgTeleBcnMaxLiIdleBcns;          //                                       
   uint32   cfgMcastBcastFilterSetting;       //                                        
   uint32   cfgBcnEarlyTermWakeupInterval;    //                                            
   uint8    cfgValidRadarChannelList[QWLAN_HAL_CFG_RADAR_CHANNEL_LIST_LEN]; //                              
   uint32   cfgTxPower2420;                   //                            
   uint32   cfgTxPower2440;                   //                            
   uint32   cfgTxPower5020;                   //                            
   uint32   cfgTxPower5040;                   //                            
   uint8    cfgMaxTxPower24[QCOM_WLAN_CFG_MAX_TX_POWER_2_4_LEN]; //                              
   uint8    cfgMaxTxPower5[QCOM_WLAN_CFG_MAX_TX_POWER_5_LEN];    //                            
   uint32   cfgInfraStaKeepAlivePeriod;       //                                         
   uint32   cfgEnableCloseLoop;               //                               
   uint32   cfgBtcExecutionMode;              //                                
   uint32   cfgBtcDhcpBtSlotsToBlock;         //                                        
   uint32   cfgBtcA2dpDhcpBtSubIntervals;     //                                            
   uint32   cfgWcnssApiVersion;               //                               
   uint32   cfgApKeepAliveTimeout;            //                                  
   uint32   cfgGoKeepAliveTimeout;            //                                  
   uint32   cfgEnableMCAddrList;              //                                    
   uint32   cfgBtcStaticLenInqBt;             //                                   
   uint32   cfgBtcStaticLenPageBt;            //                                    
   uint32   cfgBtcStaticLenConnBt;            //                                    
   uint32   cfgBtcStaticLenLeBt;              //                                  
   uint32   cfgBtcStaticLenInqWlan;           //                                     
   uint32   cfgBtcStaticLenPageWlan;          //                                      
   uint32   cfgBtcStaticLenConnWlan;          //                                      
   uint32   cfgBtcStaticLenLeWlan;            //                                    
   uint32   cfgBtcDynMaxLenBt;                //                                
   uint32   cfgBtcDynMaxLenWlan;              //                                  
   uint32   cfgBtcMaxScoBlockPerc;            //                                    
   uint32   cfgBtcDhcpProtOnA2dp;             //                                   
   uint32   cfgBtcDhcpProtOnSco;              //                                  
}tAniHalCfg, *tpAniHalCfg;

#endif //                  


