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

#ifndef WLAN_QCT_WDI_H
#define WLAN_QCT_WDI_H

/*===========================================================================

         W L A N   D E V I C E   A B S T R A C T I O N   L A Y E R 
                       E X T E R N A L  A P I
                
                   
DESCRIPTION
  This file contains the external API exposed by the wlan transport layer 
  module.
  
      
  Copyright (c) 2010-2011 QUALCOMM Incorporated.
  All Rights Reserved.
  Qualcomm Confidential and Proprietary
===========================================================================*/


/*                                                                           

                                           


                                                                       
                                                                


                                   


                                   
                                                                             
                                                 
                                   

                                                                           */



/*                                                                           

                                                  

                                                                           */

/*                                                                            
                
                                                                            */
#include "wlan_qct_pal_api.h" 
#include "wlan_qct_pal_type.h" 
#include "wlan_qct_pack_align.h" 
#include "wlan_qct_wdi_cfg.h" 

/*                                                                            
                                         
                                                                            */
#ifdef __cplusplus
 extern "C" {
#endif 
 
/*                              */
#define WDI_MAC_ADDR_LEN 6

/*                                       */
#define WDI_NUM_11B_RATES                 4  

/*                                                 */
#define WDI_NUM_11A_RATES                 8  

/*                                          */
#define WDI_NUM_POLARIS_RATES             3  

/*                      */
#define WDI_MAC_MAX_SUPPORTED_MCS_SET    16

/*                                                   */
#define WDI_MAX_NO_AC                     4

/*                                            */
#define WDI_BEACON_TEMPLATE_SIZE  0x180

#define WDI_WOWL_BCAST_PATTERN_MAX_SIZE 128

#define WDI_WOWL_BCAST_MAX_NUM_PATTERNS 16

#define WDI_MAX_SSID_SIZE  32

/*                                                                               
                                                                                  
                                                             */

#define FRAGMENT_SIZE 3072

/*                                                         */
#define TOTALFRAGMENTS(x) ((x%FRAGMENT_SIZE)== 0) ? (x/FRAGMENT_SIZE):((x/FRAGMENT_SIZE)+1)

/*                     */
#define WDI_BEACON_FILTER_LEN 70

/*                                                                  */
#define WDI_COEX_IND_DATA_SIZE (4)

#define WDI_CIPHER_SEQ_CTR_SIZE 6

#define WDI_NUM_BSSID   2

/*                                          */
#define WDI_VERSION_LENGTH  64


/*                                                                            
                                                                            
                                              */
#define WDI_RESPONSE_TIMEOUT   10000

#define WDI_SET_POWER_STATE_TIMEOUT  10000 /*                                 */

/*                                                                            
                          
  
                                                                            */

/*                                                                           
                        
                                                                           */
typedef struct
{
    wpt_uint8                  revision;
    wpt_uint8                  version;
    wpt_uint8                  minor;
    wpt_uint8                  major;
} WDI_WlanVersionType;

/*                                                                           
                      
                                                                           */
typedef struct 
{
  /*                                                                       
                      */
  wpt_boolean   bFrameXtlSupported; 

  /*                                                */
  wpt_uint8     ucMaxBSSSupported;

  /*                                                   */
  wpt_uint8     ucMaxSTASupported;
}WDI_DeviceCapabilityType; 

/*                                                                           
                   
                                                                           */
typedef enum
{
  WDI_SECONDARY_CHANNEL_OFFSET_NONE   = 0,
  WDI_SECONDARY_CHANNEL_OFFSET_UP     = 1,
  WDI_SECONDARY_CHANNEL_OFFSET_DOWN   = 3,
#ifdef WLAN_FEATURE_11AC
  WDI_CHANNEL_20MHZ_LOW_40MHZ_CENTERED = 4, //                                            
  WDI_CHANNEL_20MHZ_CENTERED_40MHZ_CENTERED = 5, //                                                 
  WDI_CHANNEL_20MHZ_HIGH_40MHZ_CENTERED = 6, //                                             
  WDI_CHANNEL_20MHZ_LOW_40MHZ_LOW = 7,//                                       
  WDI_CHANNEL_20MHZ_HIGH_40MHZ_LOW = 8, //                                        
  WDI_CHANNEL_20MHZ_LOW_40MHZ_HIGH = 9, //                                        
  WDI_CHANNEL_20MHZ_HIGH_40MHZ_HIGH = 10,//                                         
#endif
  WDI_SECONDARY_CHANNEL_OFFSET_MAX
}WDI_HTSecondaryChannelOffset;

/*                                                                           
                 
                                       
                                                                           */
typedef  struct 
{
    wpt_uint8 protVer :2;
    wpt_uint8 type :2;
    wpt_uint8 subType :4;

    wpt_uint8 toDS :1;
    wpt_uint8 fromDS :1;
    wpt_uint8 moreFrag :1;
    wpt_uint8 retry :1;
    wpt_uint8 powerMgmt :1;
    wpt_uint8 moreData :1;
    wpt_uint8 wep :1;
    wpt_uint8 order :1;

} WDI_MacFrameCtl;

/*                                                                           
                            
                                                                           */
typedef struct 
{
  wpt_uint8 fragNum  : 4;
  wpt_uint8 seqNumLo : 4;
  wpt_uint8 seqNumHi : 8;
} WDI_MacSeqCtl;

/*                                                                           
                          
                                                                           */
typedef struct 
{
    WDI_MacFrameCtl     fc;
    wpt_uint8           durationLo;
    wpt_uint8           durationHi;
    wpt_uint8           da[WDI_MAC_ADDR_LEN];
    wpt_uint8           sa[WDI_MAC_ADDR_LEN];
    wpt_macAddr         bssId;
    WDI_MacSeqCtl       seqControl;
} WDI_MacMgmtHdr;

/*                                                                           
                              
                                                                             */

typedef struct
{
  /*                           */
  wpt_uint16 usTotalFragment;

  /*                  */
  wpt_uint16 usFragmentSize;

  /*                             */
  wpt_uint16 usCurrentFragment;

} WDI_NvBlobInfoParams;


/*                                                                           
                                      
                                                                             */

typedef enum
{
  /*                            */
  WDI_MGMT_POOL_ID = 0,
  /*                       */
  WDI_DATA_POOL_ID = 1
}WDI_ResPoolType;

/*                                                                            
                               
                                                                             */

/*                                                                            
                     
                                                                            */
/*                                                                           
             
                                                                           */
typedef enum
{
   WDI_STATUS_SUCCESS,       /*                                     */
   WDI_STATUS_SUCCESS_SYNC,  /*                                          
                                                                          */
   WDI_STATUS_PENDING,       /*                                        
                                                                              
                                         */
   WDI_STATUS_E_FAILURE,     /*                                         */
   WDI_STATUS_RES_FAILURE,   /*                                          */
   WDI_STATUS_MEM_FAILURE,   /*                                           
                                      */
   WDI_STATUS_E_NOT_ALLOWED, /*                                              
                                            */
   WDI_STATUS_E_NOT_IMPLEMENT, /*                                 */

   WDI_STATUS_DEV_INTERNAL_FAILURE, /*                                            */
   WDI_STATUS_MAX

}WDI_Status;


/*                                                                           
                  
 
                 
 
                                                                           
                                                              
 
              

      
                                                                   
                           
 
    
  
               
                                                            
                                                                           */
typedef void (*WDI_ReqStatusCb)(WDI_Status   wdiStatus,
                                void*        pUserData);

/*                                                                           
                         
                                                         
                                                                           */
typedef enum
{
  /*                                                                         
            */
  WDI_RSSI_NOTIFICATION_IND,

  /*                         */
  WDI_MISSED_BEACON_IND,

  /*                                                                       
                                                                              
                */
  WDI_UNKNOWN_ADDR2_FRAME_RX_IND,

  /*                          */
  WDI_MIC_FAILURE_IND,

  /*               */
  WDI_FATAL_ERROR_IND, 

  /*                  */
  WDI_DEL_STA_IND, 

  /*                    */
  WDI_COEX_IND,

  /*                            */
  WDI_TX_COMPLETE_IND,

  /*                         */
  WDI_P2P_NOA_ATTR_IND,

  /*                                    */
  WDI_PREF_NETWORK_FOUND_IND,

  WDI_WAKE_REASON_IND,

  /*                            */
  WDI_TX_PER_HIT_IND,
  
  WDI_MAX_IND
}WDI_LowLevelIndEnumType;


/*                                                                           
                      
                                                                           */
typedef struct
{
  /*                                 */
   wpt_uint32             bRssiThres1PosCross : 1;
  /*                                 */
   wpt_uint32             bRssiThres1NegCross : 1;
  /*                                 */
   wpt_uint32             bRssiThres2PosCross : 1;
  /*                                 */
   wpt_uint32             bRssiThres2NegCross : 1;
  /*                                 */
   wpt_uint32             bRssiThres3PosCross : 1;
  /*                                 */
   wpt_uint32             bRssiThres3NegCross : 1;

   wpt_uint32             bReserved           : 26;

}WDI_LowRSSIThIndType;


/*                                                                           
                          
                                                                           */
typedef struct
{
  /*                                               */
  void*  bufRxBd;

  /*             */
  wpt_uint16  usBufLen; 
}WDI_UnkAddr2FrmRxIndType;

/*                                                                           
                      
                                                                           */
typedef struct
{
   /*                             */
   wpt_uint16    usAssocId;

   /*                                                              */
   wpt_uint8     ucSTAIdx;

   /*            */
   wpt_macAddr   macBSSID; 

    /*               */
    wpt_macAddr  macADDR2;          
                                
    /*                                                     */
    wpt_uint16   wptReasonCode;   

}WDI_DeleteSTAIndType;

/*                                                                           
                       
                                                                           */
typedef struct
{
 /*             */
 wpt_macAddr bssId;
  
  /*                  */
 wpt_macAddr macSrcAddr;

 /*                       */
 wpt_macAddr macTaAddr;

 /*                       */
 wpt_macAddr macDstAddr;

 /*              */
 wpt_uint8   ucMulticast;

 /*                */
 wpt_uint8   ucIV1;

 /*      */
 wpt_uint8   keyId;

 /*               */
 wpt_uint8   TSC[WDI_CIPHER_SEQ_CTR_SIZE];

 /*                */
 wpt_macAddr   macRxAddr;
}WDI_MicFailureIndType;

/*                                                                           
                 
                                                                           */
typedef struct
{
  wpt_uint32  coexIndType;
  wpt_uint32  coexIndData[WDI_COEX_IND_DATA_SIZE];
} WDI_CoexIndType;

/*                                                                           
             
                                                                           */
typedef struct 
{
    wpt_uint8        ucLength;
    wpt_uint8        sSSID[WDI_MAX_SSID_SIZE];
} WDI_MacSSid;

#ifdef FEATURE_WLAN_SCAN_PNO
/*                                                                           
                             
                                                                           */
typedef struct
{  
  /*                                             */
  WDI_MacSSid ssId;
  /*                    */
  wpt_uint8  rssi;
} WDI_PrefNetworkFoundInd;
#endif //                      

#ifdef WLAN_FEATURE_P2P
/*                                                                           
                       
                                                                           */

typedef struct
{
  wpt_uint8       ucIndex ;
  wpt_uint8       ucOppPsFlag ;
  wpt_uint16      usCtWin  ;

  wpt_uint16      usNoa1IntervalCnt;
  wpt_uint16      usRsvd1 ;
  wpt_uint32      uslNoa1Duration;
  wpt_uint32      uslNoa1Interval;
  wpt_uint32      uslNoa1StartTime;

  wpt_uint16      usNoa2IntervalCnt;
  wpt_uint16      usRsvd2;
  wpt_uint32      uslNoa2Duration;
  wpt_uint32      uslNoa2Interval;
  wpt_uint32      uslNoa2StartTime;

  wpt_uint32      status;
}WDI_P2pNoaAttrIndType;
#endif

#ifdef WLAN_WAKEUP_EVENTS
/*                                                                           
                           
                                                                           */
typedef struct
{  
    wpt_uint32      ulReason;        /*                     */
    wpt_uint32      ulReasonArg;     /*                                      */
    wpt_uint32      ulStoredDataLen; /*                                                        
                                                                                    
                                                                  */
    wpt_uint32      ulActualDataLen; /*                       */
    wpt_uint8       aDataStart[1];  /*                                                        
                                                    */ 
} WDI_WakeReasonIndType;
#endif //                   

/*                                                                           
                     
                                                                      
        
                                                                           */
typedef struct
{
  /*               */
  WDI_LowLevelIndEnumType  wdiIndicationType; 

  /*               */
  union
  {
    /*                                        */
    WDI_LowRSSIThIndType        wdiLowRSSIInfo; 

    /*                                                   */
    WDI_UnkAddr2FrmRxIndType    wdiUnkAddr2FrmInfo;

    /*                                        */
    WDI_MicFailureIndType       wdiMICFailureInfo; 

    /*                                  */
    wpt_uint16                  usErrorCode;

    /*                     */
    WDI_DeleteSTAIndType        wdiDeleteSTAIndType; 
    
    /*               */
    WDI_CoexIndType             wdiCoexInfo;

    /*                        */
    wpt_uint32                  tx_complete_status;

#ifdef WLAN_FEATURE_P2P
    /*                         */
    WDI_P2pNoaAttrIndType        wdiP2pNoaAttrInfo;
#endif


#ifdef FEATURE_WLAN_SCAN_PNO
    WDI_PrefNetworkFoundInd     wdiPrefNetworkFoundInd;
#endif //                      

#ifdef WLAN_WAKEUP_EVENTS
    WDI_WakeReasonIndType        wdiWakeReasonInd;
#endif //                   
  }  wdiIndicationData;
}WDI_LowLevelIndType;

/*                                                                           
                       

                 
 
                                                                         
                                                                          
 
              

      
                                                        
                                                               
 
    
  
               
                                                            
                                                                           */
typedef void (*WDI_LowLevelIndCBType)(WDI_LowLevelIndType* pwdiInd,
                                      void*                pUserData);

/*                                                                           
                
                                                                           */
typedef enum
{
    WDI_DRIVER_TYPE_PRODUCTION  = 0,
    WDI_DRIVER_TYPE_MFG         = 1,
    WDI_DRIVER_TYPE_DVT         = 2
} WDI_DriverType;

/*                                                                           
                        
                                                                           */
typedef struct
{
  /*                                                                    
                                   
 
                                                 
 
                                                   
                                                         
 
                                                             
 
                               
    
                             
                                
                                 
                                    
            
                                    
                                 
                                
             
 
                                       
                    
 
                                                                       
                                    
 
                           
 
                                                                             
                                 
 
                                                                       
           
 
                                                                   
                     
 
  */
  void*                   pConfigBuffer; 

  /*                                 */
  wpt_uint16              usConfigBufferLen;

  /*                        */
  WDI_DriverType          wdiDriverType; 

  /*                                       */
  wpt_uint8               bFrameTransEnabled;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb         wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*                   pUserData;

  /*                                                                      
                                                          */
  WDI_LowLevelIndCBType   wdiLowLevelIndCB; 

  /*                                                                         
                                    */
  void*                   pIndUserData;
}WDI_StartReqParamsType;


/*                                                                           
                        
                                                                           */
typedef struct
{
  /*                      */
  WDI_Status    wdiStatus;

  /*                                         */
  wpt_uint8     ucMaxStations;

  /*                                         */
  wpt_uint8     ucMaxBssids;

  /*                                                       */
  WDI_WlanVersionType wlanCompiledVersion;

  /*                                             */
  WDI_WlanVersionType wlanReportedVersion;

  /*                             */
  wpt_uint8 wcnssSoftwareVersion[WDI_VERSION_LENGTH];

  /*                             */
  wpt_uint8 wcnssHardwareVersion[WDI_VERSION_LENGTH];
}WDI_StartRspParamsType;


/*                                                                           
              
                                                                           */
typedef enum
{
  /*                                      */
  WDI_STOP_TYPE_SYS_RESET,

  /*                                                  */
  WDI_STOP_TYPE_SYS_DEEP_SLEEP,

  /*                                                        
                        */
  WDI_STOP_TYPE_RF_KILL 
}WDI_StopType;

/*                                                                           
                       
                                                                           */
typedef struct
{

  /*                                                */
  WDI_StopType   wdiStopReason;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_StopReqParamsType;


/*                                                                           
              
                                                                           */
typedef enum
{
  WDI_SCAN_MODE_NORMAL = 0,
  WDI_SCAN_MODE_LEARN,
  WDI_SCAN_MODE_SCAN,
  WDI_SCAN_MODE_PROMISC,
  WDI_SCAN_MODE_SUSPEND_LINK,
  WDI_SCAN_MODE_ROAM_SCAN,
  WDI_SCAN_MODE_ROAM_SUSPEND_LINK,

} WDI_ScanMode;

/*                                                                           
               
                                                                           */
typedef struct 
{
  wpt_uint8 bssIdx[WDI_NUM_BSSID];
  wpt_uint8 activeBSScnt;
}WDI_ScanEntry;

/*                                                                           
                         
                                                                           */
typedef struct
{
   /*               
                   */
  WDI_ScanMode     wdiScanMode;

  /*                */
  wpt_macAddr      macBSSID;

  /*                                */
  wpt_boolean      bNotifyBSS;

  /*                                                                       
                                                  */
  wpt_uint8        ucFrameType;

  /*                                                                     
                                                                        
                                                                            
             */
  wpt_uint8        ucFrameLength;

  /*                                                                        */
  WDI_MacMgmtHdr   wdiMACMgmtHdr;

  /*                                                              
                    */
  WDI_ScanEntry    wdiScanEntry;

  /*                                  */
  wpt_boolean      bUseNOA;

  /*                                     */
  wpt_uint16       scanDuration;

}WDI_InitScanReqInfoType; 

/*                                                                           
                           
                                                                           */
typedef struct
{
  /*                                                                      
          */
  WDI_InitScanReqInfoType  wdiReqInfo; 

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb          wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*                    pUserData;
}WDI_InitScanReqParamsType;

/*                                                                           
                            
                                                                           */
typedef struct
{
  /*                             */
  wpt_uint8         ucChannel;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_StartScanReqParamsType;

/*                                                                           
                            
                                                                           */
typedef struct
{
  /*                                      */
  WDI_Status        wdiStatus;

#if defined WLAN_FEATURE_VOWIFI
  wpt_uint32        aStartTSF[2];
  wpt_int8          ucTxMgmtPower;
#endif
}WDI_StartScanRspParamsType;

/*                                                                           
                          
                                                                           */
typedef struct
{
  /*                                                                      
                                                                     
                    */
  wpt_uint8         ucChannel;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_EndScanReqParamsType;

/*                                                                           
                      
                                                                           */
typedef enum
{
  WDI_PHY_SINGLE_CHANNEL_CENTERED = 0,            
  WDI_PHY_DOUBLE_CHANNEL_LOW_PRIMARY = 1,     
  WDI_PHY_DOUBLE_CHANNEL_CENTERED = 2,            
  WDI_PHY_DOUBLE_CHANNEL_HIGH_PRIMARY = 3,
#ifdef WLAN_FEATURE_11AC
  WDI_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_CENTERED = 4, //                                            
  WDI_QUADRUPLE_CHANNEL_20MHZ_CENTERED_40MHZ_CENTERED = 5, //                                                 
  WDI_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_CENTERED = 6, //                                             
  WDI_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_LOW = 7,//                                       
  WDI_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_LOW = 8, //                                        
  WDI_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_HIGH = 9, //                                        
  WDI_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_HIGH = 10,//                                         
#endif
  WDI_MAX_CB_STATE
} WDI_PhyChanBondState;

/*                                                                           
                           
                                                                           */
typedef struct
{
   /*               
                   */
  WDI_ScanMode          wdiScanMode;

  /*                             */
  wpt_uint8             ucCurrentOperatingChannel;

  /*                                                                         
                                                                  */
  WDI_PhyChanBondState  wdiCBState;

  /*                */
  wpt_macAddr           macBSSID;

  /*                                */
  wpt_boolean           bNotifyBSS;

  /*                                                                       
                                                  */
  wpt_uint8             ucFrameType;

  /*                                                                     
                                                                        
                                                                            
             */
  wpt_uint8             ucFrameLength;

  /*                                                                        */
  WDI_MacMgmtHdr        wdiMACMgmtHdr;

  /*                                                                 */
  WDI_ScanEntry    wdiScanEntry;

}WDI_FinishScanReqInfoType; 

/*                                                                           
                         
                                                                           */
typedef struct
{
  /*                                   */
  wpt_uint8         ucChannel;

  /*                      */
  wpt_uint8         ucLocalPowerConstraint;

  /*                         */
  WDI_HTSecondaryChannelOffset  wdiSecondaryChannelOffset;

#ifdef WLAN_FEATURE_VOWIFI
  wpt_int8      cMaxTxPower;

  /*                    */
  wpt_macAddr   macSelfStaMacAddr;
#endif
  /*                                                                                        
                                                                                */
  /*                                                                                            
                                                                                                         
   */
  wpt_macAddr   macBSSId;

}WDI_SwitchChReqInfoType;

/*                                                                           
                           
                                                                           */
typedef struct
{
  /*            */
  WDI_SwitchChReqInfoType  wdiChInfo; 

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_SwitchChReqParamsType;

/*                                                                           
                             
                                                                           */
typedef struct
{
  /*                                                                     */
  WDI_FinishScanReqInfoType  wdiReqInfo; 

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb            wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*                      pUserData;
}WDI_FinishScanReqParamsType;

/*                                                                           
                     
                                                                           */
typedef struct
{
  /*                                                      */
  wpt_macAddr   macBSSID; 

  /*                                                 */
  wpt_macAddr   macSTASelf; 
 
  /*                                                                             */
  wpt_uint32    linkState;
  
  /*                                   */
  WDI_SwitchChReqInfoType  wdiChannelInfo; 

}WDI_JoinReqInfoType;

/*                                                                           
                       
                                                                           */
typedef struct
{
  /*                                                              */
  WDI_JoinReqInfoType   wdiReqInfo; 

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb       wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*                 pUserData;
}WDI_JoinReqParamsType;

/*                                                                           
             
                                                                           */
typedef enum 
{
  WDI_INFRASTRUCTURE_MODE,
  WDI_INFRA_AP_MODE,                    //                        
  WDI_IBSS_MODE,
  WDI_BTAMP_STA_MODE, 
  WDI_BTAMP_AP_MODE,
  WDI_BSS_AUTO_MODE,
}WDI_BssType;

/*                                                                           
            
                                                                           */
typedef enum 
{
  WDI_11A_NW_TYPE,
  WDI_11B_NW_TYPE,
  WDI_11G_NW_TYPE,
  WDI_11N_NW_TYPE,
} WDI_NwType;

/*                                                                           
                  
                                                                           */
typedef enum 
{
  WDI_ADD_BSS,
  WDI_UPDATE_BSS
} WDI_ConfigAction;

/*                                                                           
                     
                                                                           */
typedef enum
{
  WDI_HT_OP_MODE_PURE,
  WDI_HT_OP_MODE_OVERLAP_LEGACY,  
  WDI_HT_OP_MODE_NO_LEGACY_20MHZ_HT,  
  WDI_HT_OP_MODE_MIXED

} WDI_HTOperatingMode;


/*                                                                           
                  
                                                                           */
typedef enum 
{
  WDI_STA_ENTRY_SELF,
  WDI_STA_ENTRY_PEER,
  WDI_STA_ENTRY_BSSID,
  WDI_STA_ENTRY_BCAST
}WDI_STAEntryType;

/*                                                                           
                      
                                                                           */
typedef enum 
{
  WDI_ADD_STA,
  WDI_UPDATE_STA
} WDI_ConfigActionType;

/*                                                                             
                                                                       
                                                                              */
typedef enum 
{
    WDI_RESERVED_1 = 0,
    WDI_RESERVED_2,
    WDI_RESERVED_3,
    WDI_11b,
    WDI_11bg,
    WDI_11a,
    WDI_11n,
} WDI_RateModeType;

/*                                                                           
                        
                                                                           */
typedef struct  
{
    /*
                                                    
                                                              
                 
                                                         
                                                                                                              
            
                                                                                        
                                              
                                                                                            
    */

    WDI_RateModeType   opRateMode;

    /*                                                                              */
    wpt_uint16         llbRates[WDI_NUM_11B_RATES];
    wpt_uint16         llaRates[WDI_NUM_11A_RATES];
    wpt_uint16         aLegacyRates[WDI_NUM_POLARIS_RATES];

    /*                                                                          
                                                          
                                                                         */
    wpt_uint32         uEnhancedRateBitmap; //                      

    /*
                                        
                                     
    */
    wpt_uint8           aSupportedMCSSet[WDI_MAC_MAX_SUPPORTED_MCS_SET];

    /*
                                                              
                                                                
                                                                  
                                 
     */
    wpt_uint16         aRxHighestDataRate;

   
#ifdef WLAN_FEATURE_11AC
   /*                                                              
                           */
    wpt_uint16         vhtRxMCSMap;
  /*                                                                  */
    wpt_uint16         vhtRxHighestDataRate;
  /*                                                                  
                          */
    wpt_uint16         vhtTxMCSMap;
  /*                                                                   */
    wpt_uint16         vhtTxHighestDataRate;
#endif

} WDI_SupportedRates;

/*                                                                           
                           
                                            
                                                                           */
typedef enum 
{
  WDI_HT_MIMO_PS_STATIC   = 0,    //                          
  WDI_HT_MIMO_PS_DYNAMIC  = 1,   //                           
  WDI_HT_MIMO_PS_NA       = 2,        //         
  WDI_HT_MIMO_PS_NO_LIMIT = 3,  //                       
} WDI_HTMIMOPowerSaveState;

/*                                                                           
                          
                                                                           */
typedef struct
{
  /*            */
  wpt_macAddr               macBSSID;

  /*                             */
  wpt_uint16                usAssocId;

  /*                                               */
  WDI_STAEntryType          wdiSTAType;

  /*                         */
  wpt_uint8                 ucShortPreambleSupported;

  /*                  */
  wpt_macAddr               macSTA;

  /*                          */
  wpt_uint16                usListenInterval;

  /*                   */
  wpt_uint8                 ucWMMEnabled;

  /*                  */
  wpt_uint8                 ucHTCapable;

  /*                                            */
  wpt_uint8                 ucTXChannelWidthSet;

  /*                             */
  wpt_uint8                 ucRIFSMode;

  /*                               
                               
                                */
  wpt_uint8                 ucLSIGTxopProtection;

  /*                                                    
                                       */
  wpt_uint8                 ucMaxAmpduSize;

  /*                                                               */
  wpt_uint8                 ucMaxAmpduDensity;

  /*                                             */
  wpt_uint8                 ucMaxAmsduSize;

  /*                                  */
  wpt_uint8                 ucShortGI40Mhz;

  /*                                  */
  wpt_uint8                 ucShortGI20Mhz;

  /*                                                               */
  WDI_SupportedRates        wdiSupportedRates;

  /*                                              */
  wpt_uint8                 ucRMFEnabled;

  /*                                                */
  wpt_uint32                ucEncryptType;

  /*                                                                    
                                                                         
          */
  WDI_ConfigActionType      wdiAction;

  /*                                             
                              
                            
  */
  wpt_uint8                 ucAPSD;

  /*             */
  wpt_uint8                 ucMaxSPLen;

  /*                                */
  wpt_uint8                 ucGreenFieldCapable;

  /*                    */
  WDI_HTMIMOPowerSaveState  wdiMIMOPS;

  /*                  */
  wpt_uint8                 ucDelayedBASupport;

  /*                          */
  wpt_uint8                 us32MaxAmpduDuratio;

  /*                                                 
                                                                          
                                                                           
  */
  wpt_uint8                 ucDsssCckMode40Mhz;

  wpt_uint8                 ucP2pCapableSta;
#ifdef WLAN_FEATURE_11AC
  wpt_uint8                 ucVhtCapableSta;
  wpt_uint8                 ucVhtTxChannelWidthSet;
#endif
}WDI_ConfigStaReqInfoType;


/*                                                                           
             
 
                                                                    
                           
                                           
                                                                           */
#define WDI_RATESET_EID_MAX            12

typedef struct 
{
    wpt_uint8  ucNumRates;
    wpt_uint8  aRates[WDI_RATESET_EID_MAX];
} WDI_RateSet;

/*                                                                           
                  
                         
                                                                           */
typedef struct 
{
    wpt_uint8  rsvd  : 1;
    wpt_uint8  aci   : 2;
    wpt_uint8  acm   : 1;
    wpt_uint8  aifsn : 4;
} WDI_AciAifsnType;

/*                                                                           
            
                         
                                                                           */
typedef struct 
{
    wpt_uint8  max : 4;
    wpt_uint8  min : 4;
} WDI_CWType;

/*                                                                           
                     
                                                                           */
typedef struct 
{
    /*                      */
    WDI_AciAifsnType  wdiACI;

    /*                      */
    WDI_CWType        wdiCW;

    /*                   */
    wpt_uint16        usTXOPLimit;
} WDI_EdcaParamRecord;

/*                                                                           
                    
                                                                           */
typedef struct
{
  /*         */
  wpt_uint8      ucBSSIdx;
  
  /* */
  wpt_boolean    bHighPerformance;

  /*           */
  WDI_EdcaParamRecord wdiACBE; 
           
  /*          */
  WDI_EdcaParamRecord wdiACBK; 
                            
  /*     */
  WDI_EdcaParamRecord wdiACVI; 
  
  /*     */
  WDI_EdcaParamRecord acvo; //      
} WDI_EDCAParamsType;

/*                             */
#define WDI_BSS_OPERATIONAL_MODE_AP     0
#define WDI_BSS_OPERATIONAL_MODE_STA    1

/*                                                                           
                            
                                                                           */
typedef struct
{
  /*                      */
  WDI_Status   wdiStatus; 

  /*                */
  wpt_macAddr  macBSSID; 

  /*         */
  wpt_uint8    ucBSSIdx;

  /*                     */
  wpt_uint8    ucUcastSig;

  /*                       */
  wpt_uint8    ucBcastSig;

  /*                  */ 
  wpt_macAddr  macSTA;

  /*          */
  wpt_uint8    ucSTAIdx;

#ifdef WLAN_FEATURE_VOWIFI
  /*                                                             */
  wpt_int8    ucTxMgmtPower;
#endif

}WDI_ConfigBSSRspParamsType;

/*                                                                           
                         
                                                                           */
typedef struct
{
   /*                    */
   wpt_uint8      ucBssIdx;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_DelBSSReqParamsType;

/*                                                                           
                         
                                                                           */
typedef struct
{
  /*                      */
  WDI_Status   wdiStatus; 

  /*                */
  wpt_macAddr  macBSSID; 

  wpt_uint8    ucBssIdx;

}WDI_DelBSSRspParamsType;

/*                                                                           
                            
                                                                           */
typedef struct
{
  /*                      */
  WDI_Status      wdiStatus;

  /*                        */
  wpt_uint8       ucSTAIdx;

  /*                  */
  wpt_macAddr     macSTA;

  /*                                                       */
  wpt_uint8       ucBssIdx;
  
  /*                  */
  wpt_uint8       ucDpuIndex;

  /*                        */  
  wpt_uint8       ucBcastDpuIndex;

  /*                                                                 */
  wpt_uint8       ucBcastMgmtDpuIdx;

  /*                     */
  wpt_uint8       ucUcastSig;

  /*                       */
  wpt_uint8       ucBcastSig;

  /*                   */
  wpt_uint8       ucMgmtSig;

}WDI_ConfigSTARspParamsType;

/*                                                                           
                            
                                                                           */
typedef struct
{
  /*                      */
  WDI_Status   wdiStatus; 

  /*                             */
  WDI_ConfigBSSRspParamsType bssParams;

  /*                                  */
  WDI_ConfigSTARspParamsType staParams;

}WDI_PostAssocRspParamsType;

/*                                                                           
                         
                                                                           */
typedef struct
{
  /*                                                              */
  wpt_uint8         ucSTAIdx;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_DelSTAReqParamsType;

/*                                                                           
                         
                                                                           */
typedef struct
{
 /*                      */
  WDI_Status   wdiStatus; 

  /*                                                              */
  wpt_uint8    ucSTAIdx;
}WDI_DelSTARspParamsType;

/*                                                                           
                 
                                                                           */
typedef enum 
{
    WDI_ENCR_NONE,
    WDI_ENCR_WEP40,
    WDI_ENCR_WEP104,
    WDI_ENCR_TKIP,
    WDI_ENCR_CCMP,
#if defined(FEATURE_WLAN_WAPI)
    WDI_ENCR_WPI,
#endif
    WDI_ENCR_AES_128_CMAC
} WDI_EncryptType;

/*                                                                           
                      
                                                                           */
typedef enum
{
    WDI_TX_ONLY,
    WDI_RX_ONLY,
    WDI_TX_RX,
#ifdef WLAN_SOFTAP_FEATURE
    WDI_TX_DEFAULT,
#endif
    WDI_DONOT_USE_KEY_DIRECTION
} WDI_KeyDirectionType;

#define WDI_MAX_ENCR_KEYS 4
#define WDI_MAX_KEY_LENGTH 32
#if defined(FEATURE_WLAN_WAPI)
#define WDI_MAX_KEY_RSC_LEN         16
#define WDI_WAPI_KEY_RSC_LEN        16
#else
#define WDI_MAX_KEY_RSC_LEN         8
#endif

typedef struct
{
    /*        */
    wpt_uint8                  keyId;
    /*                 */
    wpt_uint8                  unicast;     
    /*               */
    WDI_KeyDirectionType       keyDirection;
    /*                  */
    wpt_uint8                  keyRsc[WDI_MAX_KEY_RSC_LEN];   
    /*                                         */
    wpt_uint8                  paeRole;     
    wpt_uint16                 keyLength;
    wpt_uint8                  key[WDI_MAX_KEY_LENGTH];

}WDI_KeysType;

/*                                                                           
                          
                                                                           */
typedef struct
{
   /*                    */
  wpt_uint8      ucBssIdx; 

  /*                              */
  WDI_EncryptType  wdiEncType;

  /*              */
  wpt_uint8        ucNumKeys;

  /*              */
  WDI_KeysType     aKeys[WDI_MAX_ENCR_KEYS]; 

  /*                                                                
                                         */
  wpt_uint8        ucSingleTidRc; 
}WDI_SetBSSKeyReqInfoType; 

/*                                                                           
                            
                                                                           */
typedef struct
{
  /*         */
  WDI_SetBSSKeyReqInfoType  wdiBSSKeyInfo; 

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb           wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*                      pUserData;
}WDI_SetBSSKeyReqParamsType;

/*                                                                           
             
                                                                           */
typedef enum 
{
  WDI_WEP_STATIC,
  WDI_WEP_DYNAMIC

} WDI_WepType;

/*                                                                           
                             
                                                                           */
typedef struct
{
   /*                    */
  wpt_uint8      ucBssIdx; 

  /*                              */
  WDI_EncryptType  wdiEncType;

  /*      */
  wpt_uint8    ucKeyId;

  /*                                                                        
        */
  WDI_WepType  wdiWEPType;
}WDI_RemoveBSSKeyReqInfoType;

/*                                                                           
                               
                                                                           */
typedef struct
{
  /*         */
  WDI_RemoveBSSKeyReqInfoType  wdiKeyInfo; 

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_RemoveBSSKeyReqParamsType;

/*                                                                           
                          
                                                                           */
typedef struct
{
   /*         */
  wpt_uint8        ucSTAIdx; 

  /*                              */
  WDI_EncryptType  wdiEncType;

  /*              */
  WDI_WepType      wdiWEPType;

  /*                                                                 */
  wpt_uint8        ucDefWEPIdx;

  /*              */
  wpt_uint8        ucNumKeys;

  /*              */
  WDI_KeysType     wdiKey[WDI_MAX_ENCR_KEYS]; 

  /*                                                                
                                         */
  wpt_uint8        ucSingleTidRc; 
}WDI_SetSTAKeyReqInfoType; 

/*                                                                           
                          
                                                                           */
typedef struct
{
  /*          */
  wpt_macAddr              macBSSID;

  /*                */
  wpt_macAddr              macSelfAddr; 

  /*        */
  WDI_BssType              wdiBSSType;

  /*                                */
  wpt_uint8                ucOperMode;

  /*            */
  WDI_NwType               wdiNWType;

  /*                                                  */
  wpt_uint8                ucShortSlotTimeSupported;

  /*                     */
  wpt_uint8                ucllaCoexist;

  /*                     */
  wpt_uint8                ucllbCoexist;

  /*                     */
  wpt_uint8                ucllgCoexist;

  /*                        */
  wpt_uint8                ucHT20Coexist;

  /*                   */
  wpt_uint8                ucllnNonGFCoexist;

  /*                       */
  wpt_uint8                ucTXOPProtectionFullSupport;

  /*         */
  wpt_uint8                ucRIFSMode;

  /*                     */
  wpt_uint16               usBeaconInterval;

  /*           */
  wpt_uint8                ucDTIMPeriod;

  /*                                            */
  wpt_uint8                ucTXChannelWidthSet;

  /*                 */
  wpt_uint8                ucCurrentOperChannel;

  /*                                     */
  wpt_uint8                ucCurrentExtChannel;

  /*                                         */
  WDI_ConfigStaReqInfoType wdiSTAContext;

  /*               */
  WDI_MacSSid              wdiSSID;

  /*                                                                        
                                                                           */
  WDI_ConfigAction         wdiAction;

  /*              */
  WDI_RateSet              wdiRateSet;

  /*                                         */
  wpt_uint8                ucHTCapable;

  /*                                */
  wpt_uint8                ucObssProtEnabled;

  /*                    */
  wpt_uint8                ucRMFEnabled;

  /*                                                              
               */
  WDI_HTOperatingMode      wdiHTOperMod;

  /*                                         */
  wpt_uint8                ucDualCTSProtection;

    /*                            */
  wpt_uint8   ucMaxProbeRespRetryLimit;

  /*                       */
  wpt_uint8   bHiddenSSIDEn;

  /*                                       */
  wpt_uint8   bProxyProbeRespEn;

 /*                                                                         
                                                                            
                                                */
  wpt_uint8   ucEDCAParamsValid;

   /*                      */  
  WDI_EdcaParamRecord       wdiBKEDCAParams; 

   /*                      */  
  WDI_EdcaParamRecord       wdiBEEDCAParams; 

   /*                      */  
  WDI_EdcaParamRecord       wdiVIEDCAParams; 

   /*                      */  
  WDI_EdcaParamRecord       wdiVOEDCAParams; 

#ifdef WLAN_FEATURE_VOWIFI
   /*                                                                 */
  wpt_int8                  cMaxTxPower;
#endif

  /*                                                                      */  
  wpt_uint8                 ucPersona;

  /*                              */
  wpt_uint8                 bSpectrumMgtEn;

#ifdef WLAN_FEATURE_VOWIFI_11R
  wpt_uint8                 bExtSetStaKeyParamValid;
  WDI_SetSTAKeyReqInfoType  wdiExtSetKeyParam;
#endif

#ifdef WLAN_FEATURE_11AC
  wpt_uint8                 ucVhtCapableSta;
  wpt_uint8                 ucVhtTxChannelWidthSet;
#endif

}WDI_ConfigBSSReqInfoType;

/*                                                                           
                            
                                                                           */
typedef struct
{
  /*                     */
  WDI_ConfigStaReqInfoType  wdiSTAParams; 

   /*                    */
  WDI_ConfigBSSReqInfoType  wdiBSSParams;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb           wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*                     pUserData;
}WDI_PostAssocReqParamsType;

/*                                                                           
                            
                                                                           */
typedef struct
{
  /*                                                              */
  WDI_ConfigBSSReqInfoType   wdiReqInfo; 

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb            wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*                      pUserData;
}WDI_ConfigBSSReqParamsType;

/*                                                                           
                            
                                                                           */
typedef struct
{
  /*        */
  WDI_SetSTAKeyReqInfoType  wdiKeyInfo;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_SetSTAKeyReqParamsType;

/*                                                                           
                             
                                                                           */
typedef struct
{
  /*         */
  wpt_uint8        ucSTAIdx; 

  /*                              */
  WDI_EncryptType  wdiEncType;

  /*      */
  wpt_uint8        ucKeyId;

  /*                                                                       
                                                      */
  wpt_uint8        ucUnicast;
}WDI_RemoveSTAKeyReqInfoType;

/*                                                                           
                               
                                                                           */
typedef struct
{
  /*         */
  WDI_RemoveSTAKeyReqInfoType  wdiKeyInfo; 

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_RemoveSTAKeyReqParamsType;

/*                                                                           
                                          
                                                                           */

/*                                                                           
               
                                                                           */
typedef struct 
{
    wpt_uint16       ackPolicy:2;
    wpt_uint16       userPrio:3;
    wpt_uint16       psb:1;
    wpt_uint16       aggregation : 1;
    wpt_uint16       accessPolicy : 2;
    wpt_uint16       direction : 2;
    wpt_uint16       tsid : 4;
    wpt_uint16       trafficType : 1;
} WDI_TSInfoTfc;

/*                                                                           
               
                                                                           */
typedef struct 
{
    wpt_uint8        rsvd : 7;
    wpt_uint8        schedule : 1;
} WDI_TSInfoSch;

/*                                                                           
                
                                                                           */
typedef struct 
{
    WDI_TSInfoTfc  wdiTraffic;
    WDI_TSInfoSch  wdiSchedule;
} WDI_TSInfoType;

/*                                                                           
                 
                                                                           */
typedef struct 
{
    wpt_uint8             ucType;
    wpt_uint8             ucLength;
    WDI_TSInfoType        wdiTSinfo;
    wpt_uint16            usNomMsduSz;
    wpt_uint16            usMaxMsduSz;
    wpt_uint32            uMinSvcInterval;
    wpt_uint32            uMaxSvcInterval;
    wpt_uint32            uInactInterval;
    wpt_uint32            uSuspendInterval;
    wpt_uint32            uSvcStartTime;
    wpt_uint32            uMinDataRate;
    wpt_uint32            uMeanDataRate;
    wpt_uint32            uPeakDataRate;
    wpt_uint32            uMaxBurstSz;
    wpt_uint32            uDelayBound;
    wpt_uint32            uMinPhyRate;
    wpt_uint16            usSurplusBw;
    wpt_uint16            usMediumTime;
}WDI_TspecIEType;

/*                                                                           
                      
                                                                           */
typedef struct
{
  /*         */
  wpt_uint8         ucSTAIdx; 

  /*                    */
  wpt_uint16        ucTspecIdx;

  /*                       */
  WDI_TspecIEType   wdiTspecIE;

  /*                                         */
  wpt_uint8         ucUapsdFlags;

  /*              */
  wpt_uint8         ucServiceInterval[WDI_MAX_NO_AC];

  /*                            */
  wpt_uint8         ucSuspendInterval[WDI_MAX_NO_AC];

  /*              */
  wpt_uint8         ucDelayedInterval[WDI_MAX_NO_AC];

}WDI_AddTSReqInfoType;


/*                                                                           
                        
                                                                           */
typedef struct
{
  /*           */
  WDI_AddTSReqInfoType  wdiTsInfo; 

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_AddTSReqParamsType;

/*                                                                           
                      
                                                                           */
typedef struct
{
  /*         */
  wpt_uint8         ucSTAIdx; 

  /*                    */
  wpt_uint16        ucTspecIdx;

  /*                */
  wpt_macAddr      macBSSID;
}WDI_DelTSReqInfoType;

/*                                                                           
                        
                                                                           */
typedef struct
{
  /*              */
  WDI_DelTSReqInfoType  wdiDelTSInfo;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_DelTSReqParamsType;

/*                                                                           
                        
                                                                           */
typedef struct
{
   /*                    */
   wpt_uint8      ucBssIdx;

  /*                                                                         
                                                                            
                                                */
  wpt_uint8   ucEDCAParamsValid;

  /*                  */
  WDI_EdcaParamRecord wdiEdcaBEInfo;

  /*                  */
  WDI_EdcaParamRecord wdiEdcaBKInfo;

  /*                  */
  WDI_EdcaParamRecord wdiEdcaVIInfo;

  /*                  */
  WDI_EdcaParamRecord wdiEdcaVOInfo;

}WDI_UpdateEDCAInfoType;

/*                                                                           
                          
                                                                           */
typedef struct
{
  /*          */
  WDI_UpdateEDCAInfoType  wdiEDCAInfo;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_UpdateEDCAParamsType;

/*                                                                           
                             
                                                                           */
typedef struct
{
  /*                                             */
  wpt_uint8        ucSTAIdx;

  /*                    */
  wpt_macAddr      macPeerAddr;

  /*                               */
  wpt_uint8        ucBaTID;

  /*                    */
  wpt_uint8        ucBaPolicy;

  /*                                          */
  wpt_uint16       usBaBufferSize;
  
  /*                  */
  wpt_uint16       usBaTimeout;
  
  /*                                          
                                                                              */
  wpt_uint16       usBaSSN;
  
  /*                    */
  wpt_uint8        ucBaDirection;
  
}WDI_AddBASessionReqinfoType;


/*                                                                           
                               
                                                                           */
typedef struct
{
  /*                    */
  WDI_AddBASessionReqinfoType  wdiBASessionInfoType; 

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb       wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*                 pUserData;
}WDI_AddBASessionReqParamsType;

/*                                                                           
                               
                                                                           */
typedef struct
{
  /*                      */
  WDI_Status   wdiStatus; 
  
  /*              */
  wpt_uint8    ucBaDialogToken;
  
  /*                                             */
  wpt_uint8    ucBaTID;
  
  /*                                                     */
  wpt_uint8    ucBaBufferSize;

  /*               */
  wpt_uint16   usBaSessionID;
  
  /*                          */
  wpt_uint8    ucWinSize;
  
  /*                            */
  wpt_uint8    ucSTAIdx;
  
  /*                          */
  wpt_uint16   usBaSSN;

}WDI_AddBASessionRspParamsType;

/*                                                                           
                      
                                                                           */
typedef struct
{
  /*                                             */
  wpt_uint8        ucSTAIdx;

  /*            */
  wpt_uint8        ucBaSessionID;
  
  /*                     */
  wpt_uint8        ucWinSize;
  
#ifdef FEATURE_ON_CHIP_REORDERING
  wpt_boolean      bIsReorderingDoneOnChip;
#endif

}WDI_AddBAReqinfoType;


/*                                                                           
                        
                                                                           */
typedef struct
{
  /*            */
  WDI_AddBAReqinfoType  wdiBAInfoType; 

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb       wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*                 pUserData;
}WDI_AddBAReqParamsType;


/*                                                                           
                      
                                                                           */
typedef struct
{
  /*                      */
  WDI_Status   wdiStatus; 

  /*              */
  wpt_uint8    ucBaDialogToken;

}WDI_AddBARspinfoType;

/*                                                                           
                               
                                                                           */
typedef struct
{
  /*           */
  wpt_uint8   ucSTAIdx;

  /*                          */
  wpt_uint8   ucTidBitmap;

}WDI_TriggerBAReqCandidateType;


/*                                                                           
                          
                                                                           */
typedef struct
{
  /*                                             */
  wpt_uint8        ucSTAIdx;

  /*            */
  wpt_uint8        ucBASessionID;

  /*                                    */
  wpt_uint16       usBACandidateCnt;

  /*                                                */

}WDI_TriggerBAReqinfoType;


/*                                                                           
                            
                                                                           */
typedef struct
{
  /*                    */
  WDI_TriggerBAReqinfoType  wdiTriggerBAInfoType; 

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb       wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*                 pUserData;
}WDI_TriggerBAReqParamsType;

/*                                                                           
                   
                                                                           */
typedef struct
{
  wpt_uint16 fBaEnable : 1;
  wpt_uint16 startingSeqNum: 12;
  wpt_uint16 reserved : 3;
}WDI_AddBAInfoType;

/*                                                                           
                               
                                                                           */
#define STA_MAX_TC 8

typedef struct
{
  /*           */
  wpt_macAddr       macSTA;

  /*         */
  WDI_AddBAInfoType wdiBAInfo[STA_MAX_TC];
}WDI_TriggerBARspCandidateType;

/*                                                                           
                            
                                                                           */
typedef struct
{
  /*                      */
  WDI_Status   wdiStatus; 

  /*                */
  wpt_macAddr  macBSSID;

  /*                                     */
  wpt_uint16   usBaCandidateCnt;

  /*                                                */

}WDI_TriggerBARspParamsType;

/*                                                                           
                      
                                                                           */
typedef struct
{
  /*                                             */
  wpt_uint8        ucSTAIdx;

  /*                               */
  wpt_uint8        ucBaTID;

  /*                    */
  wpt_uint8        ucBaDirection;
  
}WDI_DelBAReqinfoType;

/*                                                                           
                        
                                                                           */
typedef struct
{
  /*        */
  WDI_DelBAReqinfoType  wdiBAInfo; 

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_DelBAReqParamsType;


/*                                                                           
                           
                                                                           */
typedef struct
{
   /*                      */
  WDI_Status    wdiStatus;

  /*                                     */
  wpt_uint8     ucChannel;

#ifdef WLAN_FEATURE_VOWIFI
  /*                                                             */
  wpt_int8     ucTxMgmtPower;
#endif

}WDI_SwitchCHRspParamsType;

/*                                                                           
                            
                                                                           */
typedef struct
{
  /*                                                              */
  WDI_ConfigStaReqInfoType   wdiReqInfo; 

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb            wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*                      pUserData;
}WDI_ConfigSTAReqParamsType;


/*                                                                           
                                
                                                                           */

typedef struct
{
   /*                    */
   wpt_uint8      ucBssIdx;

    /*                                                               
                         */
    wpt_uint8 ucfShortPreamble;
    /*                 */
    wpt_uint8 ucfShortSlotTime;
    /*                 */
    wpt_uint16 usBeaconInterval;
    /*                   */
    wpt_uint8 ucllaCoexist;
    wpt_uint8 ucllbCoexist;
    wpt_uint8 ucllgCoexist;
    wpt_uint8 ucHt20MhzCoexist;
    wpt_uint8 ucllnNonGFCoexist;
    wpt_uint8 ucfLsigTXOPProtectionFullSupport;
    wpt_uint8 ucfRIFSMode;

    wpt_uint16 usChangeBitmap;
}WDI_UpdateBeaconParamsInfoType;



/*                                                                           
                            
                                                                           */
typedef struct
{
  /*                          */
  WDI_UpdateBeaconParamsInfoType  wdiUpdateBeaconParamsInfo;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_UpdateBeaconParamsType;

/*                                                                           
                              
                                                                           */

typedef struct {

   /*                */
   wpt_macAddr  macBSSID;

   /*             */
   wpt_uint8    beacon[WDI_BEACON_TEMPLATE_SIZE];     

   /*                        */
   wpt_uint32   beaconLength;

#ifdef WLAN_SOFTAP_FEATURE
   /*                                                  */
   wpt_uint32   timIeOffset; 
#endif

#ifdef WLAN_FEATURE_P2P
   /*                                                  */
   wpt_uint16   usP2PIeOffset;
#endif
} WDI_SendBeaconParamsInfoType;

/*                                                                           
                          
                                                                           */
typedef struct
{
  /*                        */
  WDI_SendBeaconParamsInfoType  wdiSendBeaconParamsInfo;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_SendBeaconParamsType;

/*                                                                           
                   
                                                                           */
typedef enum 
{
    WDI_LINK_IDLE_STATE              = 0,
    WDI_LINK_PREASSOC_STATE          = 1,
    WDI_LINK_POSTASSOC_STATE         = 2,
    WDI_LINK_AP_STATE                = 3,
    WDI_LINK_IBSS_STATE              = 4,

    //            
    WDI_LINK_BTAMP_PREASSOC_STATE    = 5,
    WDI_LINK_BTAMP_POSTASSOC_STATE   = 6,
    WDI_LINK_BTAMP_AP_STATE          = 7,
    WDI_LINK_BTAMP_STA_STATE         = 8,
    
    //                              
    WDI_LINK_LEARN_STATE             = 9,
    WDI_LINK_SCAN_STATE              = 10,
    WDI_LINK_FINISH_SCAN_STATE       = 11,
    WDI_LINK_INIT_CAL_STATE          = 12,
    WDI_LINK_FINISH_CAL_STATE        = 13,
#ifdef WLAN_FEATURE_P2P
    WDI_LINK_LISTEN_STATE            = 14,
#endif
    WDI_LINK_MAX                     = 0x7FFFFFFF
} WDI_LinkStateType;

/*                                                                           
                        
                                                                           */
typedef struct
{
  /*                */
  wpt_macAddr           macBSSID;

  /*          */
  WDI_LinkStateType     wdiLinkState;

  /*                */
  wpt_macAddr           macSelfStaMacAddr;
}WDI_SetLinkReqInfoType;

/*                                                                           
                          
                                                                           */
typedef struct
{
  /*         */
  WDI_SetLinkReqInfoType  wdiLinkInfo;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_SetLinkReqParamsType;

/*                                                                           
                            
                                                                           */
typedef struct
{
  /*                                                         */
  wpt_uint8        ucSTAIdx;

  /*                               */
  wpt_uint32       uStatsMask;
}WDI_GetStatsParamsInfoType;

/*                                                                           
                           
                                                                           */
typedef struct
{
  /*                      */
  WDI_GetStatsParamsInfoType  wdiGetStatsParamsInfo;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_GetStatsReqParamsType;

/*                                                                           
                           
                                                                           */
typedef struct
{
  /*                                        */
  wpt_uint16       usMsgType;

  /*                                                                */
  wpt_uint16       usMsgLen;
  
  /*                       */
  WDI_Status       wdiStatus;

  /*                                                         */
  wpt_uint8        ucSTAIdx;

  /*                               */
  wpt_uint32       uStatsMask;

  /*                                                                                  
                                      */
}WDI_GetStatsRspParamsType;

#ifdef FEATURE_WLAN_CCX
/*                                                                           
                            
                                                                           */
typedef struct
{
  /*                                                         */
  wpt_uint8        ucTid;

  wpt_macAddr      bssid;
}WDI_TSMStatsParamsInfoType;

/*                                                                           
                           
                                                                           */
typedef struct
{
  /*                          */
  WDI_TSMStatsParamsInfoType  wdiTsmStatsParamsInfo;

  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;

}WDI_TSMStatsReqParamsType;


/*                                                                           
                           
                                                                           */
typedef struct
{
  /*                                      */
  WDI_Status      wdiStatus;

  wpt_uint16      UplinkPktQueueDly;
  wpt_uint16      UplinkPktQueueDlyHist[4];
  wpt_uint32      UplinkPktTxDly;
  wpt_uint16      UplinkPktLoss;
  wpt_uint16      UplinkPktCount;
  wpt_uint8       RoamingCount;
  wpt_uint16      RoamingDly;
}WDI_TSMStatsRspParamsType;


#endif
/*                                                                           
                            
                                                                           */
typedef struct
{
  /*                                                                    
                                   
 
                                                 
 
                                                   
                                                         
 
                                                             
 
                               
    
                             
                                
                                 
                                    
            
                                    
                                 
                                
             
 
                                       
                    
 
                                                                       
                                    
 
                           
 
                                                                             
                                 
 
                                                                       
           
 
                                                                   
                     
  */
  void*                   pConfigBuffer; 

  /*                                 */
  wpt_uint32              uConfigBufferLen;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_UpdateCfgReqParamsType;

/*                                                                           
                                    
                                                                           */
//                            
#define WDI_PROBE_RSP_TEMPLATE_SIZE 0x180

#define WDI_PROBE_REQ_BITMAP_IE_LEN 8

typedef struct
{
  /*                                                */
  wpt_macAddr     macBSSID;

  /*                       */
  wpt_uint8      *pProbeRespTemplate[WDI_PROBE_RSP_TEMPLATE_SIZE];

  /*            */
  wpt_uint32      uProbeRespTemplateLen;

  /*                                                      */
  wpt_uint32      uaProxyProbeReqValidIEBmap[WDI_PROBE_REQ_BITMAP_IE_LEN];

}WDI_UpdateProbeRspTemplateInfoType;

/*                                                                           
                              
                                                                           */
typedef struct
{
  /*         */
  WDI_UpdateProbeRspTemplateInfoType  wdiProbeRspTemplateInfo;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_UpdateProbeRspTemplateParamsType;

/*                                                                           
                           
                                                                           */

typedef struct
{
  /*                      */
  void *pBlobAddress;

  /*           */
  wpt_uint32 uBlobSize;
  
}WDI_NvDownloadReqBlobInfo;

/*                                                                           
                            
                                                                           */
typedef struct
{
  /*            */
  WDI_NvDownloadReqBlobInfo  wdiBlobInfo; 

  /*                                                                     
                                                                        
                            */
  WDI_ReqStatusCb       wdiReqStatusCB; 

  /*                                                                    
                                   */
  void*                 pUserData;
  
}WDI_NvDownloadReqParamsType;

/*                                                                           
                           
                                                                           */
typedef struct
{
  /*                      */
  WDI_Status   wdiStatus; 

}WDI_NvDownloadRspInfoType;

/*                                                                           
                           
                                                                           */

typedef struct
{
  /*                                                                                  
                                                                  */
  wpt_macAddr macBSSId;


  wpt_macAddr macSelfStaMacAddr;

  /*                                            */
  wpt_int8  ucPower;

}WDI_SetMaxTxPowerInfoType;

/*                                                                           
                             
                                                                           */
typedef struct
{
  /*         */
  WDI_SetMaxTxPowerInfoType  wdiMaxTxPowerInfo;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_SetMaxTxPowerParamsType;


/*                                                                           
                         
                                                                           */

typedef struct
{
  /*                                                        */
  wpt_int8  ucPower;
  
  /*                       */
  WDI_Status wdiStatus;
 
}WDI_SetMaxTxPowerRspMsg;

#ifdef WLAN_FEATURE_P2P
typedef struct
{
  wpt_uint8   ucOpp_ps;
  wpt_uint32  uCtWindow;
  wpt_uint8   ucCount; 
  wpt_uint32  uDuration;
  wpt_uint32  uInterval;
  wpt_uint32  uSingle_noa_duration;
  wpt_uint8   ucPsSelection;
}WDI_SetP2PGONOAReqInfoType;

/*                                                                           
                              
                                                                           */
typedef struct
{
  /*              */
  WDI_SetP2PGONOAReqInfoType  wdiP2PGONOAInfo;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_SetP2PGONOAReqParamsType;
#endif


/*                                                                           
                             
                                                                           */
typedef struct
{
  /*                        */
  wpt_macAddr selfMacAddr;

  /*                       */
  wpt_uint32  uStatus;
}WDI_AddSTASelfInfoType;

/*                                                                           
                             
                                                                           */
typedef struct
{
  /*                  */
  WDI_AddSTASelfInfoType  wdiAddSTASelfInfo;

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb         wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*                   pUserData;
}WDI_AddSTASelfReqParamsType;


/*                                                                           
                             
                                                                           */
typedef struct
{
 /*                      */
  WDI_Status   wdiStatus; 

  /*                        */
  wpt_uint8    ucSTASelfIdx;

  /*                                     */
  wpt_uint8    dpuIdx;

  /*               */
  wpt_uint8    dpuSignature;

  /*            */
  wpt_macAddr  macSelfSta;

}WDI_AddSTASelfRspParamsType;

/*                                                                           
                             
                                          
                                                                           */
typedef struct
{
   wpt_macAddr       selfMacAddr;

}WDI_DelSTASelfInfoType;

/*                                                                           
                             
                                          
                                                                           */
typedef struct
{
  /*                       */
   WDI_DelSTASelfInfoType     wdiDelStaSelfInfo; 
   /*                                                                         
                                                                                
                */ 
   WDI_ReqStatusCb            wdiReqStatusCB; 
   /*                                                                    
                                   */ 
   void*                      pUserData; 
}WDI_DelSTASelfReqParamsType;

/*                                                                           
                             
                                                                           */
typedef struct
{
 /*                      */
  WDI_Status   wdiStatus; 

  /*                                                              */
//                       
}WDI_DelSTASelfRspParamsType;

/*                                                                           
                   
                                                 
                                                                           */
typedef struct  
{
   wpt_uint8  ucSTAIdx;        //          
   wpt_uint8  ucAc;            //                
   wpt_uint8  ucUp;            //              
   wpt_uint32 uSrvInterval;   //                 
   wpt_uint32 uSusInterval;   //                 
   wpt_uint32 uDelayInterval; //               
} WDI_UapsdInfoType;

/*                                                                           
                                   
                                                
                                                                           */
typedef struct 
{ 
   /*                                               */ 
   WDI_UapsdInfoType wdiUapsdInfo; 
   /*                                                                         
                                                                                
                */ 
   WDI_ReqStatusCb   wdiReqStatusCB; 
   /*                                                                    
                                   */ 
   void*             pUserData; 
}WDI_SetUapsdAcParamsReqParamsType;

/*                                                                           
                          
                                               
                                                                           */
typedef struct
{
   //                                       
   wpt_uint8         ucBssIdx;
   wpt_uint64        uTbtt;
   wpt_uint8         ucDtimCount;
   //                                                             
   //                                                      
   wpt_uint8         ucDtimPeriod;
   /*                                                                             
                                        */
   unsigned int      dxePhyAddr;

   //                        
   wpt_uint32 rssiFilterPeriod;
   wpt_uint32 numBeaconPerRssiAverage;
   wpt_uint8  bRssiFilterEnable;
}WDI_EnterBmpsReqinfoType;

/*                                                                           
                            
                                              
                                                                           */
typedef struct 
{ 
   /*                                               */ 
   WDI_EnterBmpsReqinfoType wdiEnterBmpsInfo; 
   /*                                                                         
                                                                                
                */ 
   WDI_ReqStatusCb          wdiReqStatusCB; 
   /*                                                                    
                                   */ 
   void*                    pUserData; 
}WDI_EnterBmpsReqParamsType;

/*                                                                           
                         
                                              
                                                                           */
typedef struct
{
   wpt_uint8     ucSendDataNull;
   wpt_uint8     bssIdx;
}WDI_ExitBmpsReqinfoType;

/*                                                                           
                           
                                             
                                                                           */
typedef struct 
{ 
   /*                                             */ 
   WDI_ExitBmpsReqinfoType wdiExitBmpsInfo; 
   /*                                                                         
                                                                                
                */ 
   WDI_ReqStatusCb         wdiReqStatusCB; 
   /*                                                                    
                                   */ 
   void*                   pUserData; 
}WDI_ExitBmpsReqParamsType;

/*                                                                           
                           
                                                
                                                                           */
typedef struct
{
   wpt_uint8     ucBkDeliveryEnabled:1;
   wpt_uint8     ucBeDeliveryEnabled:1;
   wpt_uint8     ucViDeliveryEnabled:1;
   wpt_uint8     ucVoDeliveryEnabled:1;
   wpt_uint8     ucBkTriggerEnabled:1;
   wpt_uint8     ucBeTriggerEnabled:1;
   wpt_uint8     ucViTriggerEnabled:1;
   wpt_uint8     ucVoTriggerEnabled:1;
   wpt_uint8     bssIdx;
}WDI_EnterUapsdReqinfoType;

/*                                                                           
                           
                                               
                                                                           */
typedef struct 
{ 
   /*                                            */ 
   WDI_EnterUapsdReqinfoType wdiEnterUapsdInfo; 
   /*                                                                         
                                                                                
                */ 
   WDI_ReqStatusCb           wdiReqStatusCB; 
   /*                                                                    
                                   */ 
   void*                     pUserData; 
}WDI_EnterUapsdReqParamsType;

/*                                                                           
                            
                                                 
                                                                           */
typedef struct
{
   wpt_uint8  ucSTAIdx;
   wpt_uint8  ucUapsdACMask; 
   wpt_uint32 uMaxSpLen;    
}WDI_UpdateUapsdReqinfoType;

/*                                                                           
                              
                                                
                                                                           */
typedef struct 
{ 
   /*                                                   */ 
   WDI_UpdateUapsdReqinfoType wdiUpdateUapsdInfo; 
   /*                                                                         
                                                                                
                */ 
   WDI_ReqStatusCb            wdiReqStatusCB; 
   /*                                                                    
                                   */ 
   void*                      pUserData; 
}WDI_UpdateUapsdReqParamsType;

/*                                                                           
                                     
                                              
                                                                           */
typedef struct 
{
  /*                                            */
  wpt_uint8 ucSetMcstBcstFilterSetting;

  /*                                   */
  wpt_uint8 ucSetMcstBcstFilter;
}WDI_RxpFilterReqParamsType;

typedef struct 
{
  /*            */
  WDI_RxpFilterReqParamsType wdiRxpFilterParam;
  
   /*                                                                         
                                                                                
                */ 
   WDI_ReqStatusCb            wdiReqStatusCB; 
   /*                                                                    
                                   */ 
   void*                      pUserData; 
}WDI_ConfigureRxpFilterReqParamsType;

/*                                                                           
                          
                                                          
                                                                           */
typedef struct 
{ 
   wpt_uint16    usCapabilityInfo;
   wpt_uint16    usCapabilityMask;
   wpt_uint16    usBeaconInterval;
   wpt_uint16    usIeNum;
}WDI_BeaconFilterInfoType;

/*                                                                           
                               
                                                    
                                                                           */
typedef struct 
{ 
   /*                                                     */ 
   WDI_BeaconFilterInfoType wdiBeaconFilterInfo; 
   /*                                                                        
                                  */ 
   wpt_uint8 aFilters[WDI_BEACON_FILTER_LEN];
   /*                                                                         
                                                                                
                */ 
   WDI_ReqStatusCb            wdiReqStatusCB; 
   /*                                                                    
                                   */ 
   void*                      pUserData; 
}WDI_BeaconFilterReqParamsType;

/*                                                                           
                             
                                                                           
                                                                           */
typedef struct 
{ 
   wpt_uint8  ucIeCount;
   wpt_uint8  ucRemIeId[1];
}WDI_RemBeaconFilterInfoType;

/*                                                                           
                                  
                                                                    
                                                                           */
typedef struct 
{ 
   /*                                                     */ 
   WDI_RemBeaconFilterInfoType wdiBeaconFilterInfo; 
   /*                                                                         
                                                                                
                */ 
   WDI_ReqStatusCb            wdiReqStatusCB; 
   /*                                                                    
                                   */ 
   void*                      pUserData; 
}WDI_RemBeaconFilterReqParamsType;

/*                                                                           
                        
                                                                          
                                                                           */
typedef struct
{
    wpt_int8    ucRssiThreshold1     : 8;
    wpt_int8    ucRssiThreshold2     : 8;
    wpt_int8    ucRssiThreshold3     : 8;
    wpt_uint8   bRssiThres1PosNotify : 1;
    wpt_uint8   bRssiThres1NegNotify : 1;
    wpt_uint8   bRssiThres2PosNotify : 1;
    wpt_uint8   bRssiThres2NegNotify : 1;
    wpt_uint8   bRssiThres3PosNotify : 1;
    wpt_uint8   bRssiThres3NegNotify : 1;
    wpt_uint8   bReserved10          : 2;
} WDI_RSSIThresholdsType;

/*                                                                           
                                    
                                                                   
                                                                           */
typedef struct 
{ 
   /*                                                      */ 
   WDI_RSSIThresholdsType     wdiRSSIThresholdsInfo; 
   /*                                                                         
                                                                                
                */ 
   WDI_ReqStatusCb            wdiReqStatusCB; 
   /*                                                                    
                                   */ 
   void*                      pUserData; 
}WDI_SetRSSIThresholdsReqParamsType;

/*                                                                           
                        
                                           
                                                                           */
#ifdef WLAN_NS_OFFLOAD
typedef struct
{
   wpt_uint8 srcIPv6Addr[16];
   wpt_uint8 selfIPv6Addr[16];
   //                                                          
   wpt_uint8 targetIPv6Addr1[16];
   wpt_uint8 targetIPv6Addr2[16];
   wpt_uint8 selfMacAddr[6];
   wpt_uint8 srcIPv6AddrValid : 1;
   wpt_uint8 targetIPv6Addr1Valid : 1;
   wpt_uint8 targetIPv6Addr2Valid : 1;
   wpt_uint8 bssIdx;
} WDI_NSOffloadParams;
#endif //               

typedef struct
{
   wpt_uint8 ucOffloadType;
   wpt_uint8 ucEnableOrDisable;
   wpt_uint8 bssIdx;
   union
   {
       wpt_uint8 aHostIpv4Addr [4];
       wpt_uint8 aHostIpv6Addr [16];
   } params;
} WDI_HostOffloadReqType;

/*                                                                           
                              
                                          
                                                                           */
typedef struct 
{ 
   /*                                                   */ 
   WDI_HostOffloadReqType     wdiHostOffloadInfo; 
#ifdef WLAN_NS_OFFLOAD
   WDI_NSOffloadParams        wdiNsOffloadParams;
#endif //               
   /*                                                                         
                                                                                
                */ 
   WDI_ReqStatusCb            wdiReqStatusCB; 
   /*                                                                    
                                   */ 
   void*                      pUserData; 
}WDI_HostOffloadReqParamsType;

/*                                                                           
                      
                                         
                                                                           */
typedef struct
{
    wpt_uint8  ucPacketType;
    wpt_uint32 ucTimePeriod;
    wpt_uint8  aHostIpv4Addr[4];
    wpt_uint8  aDestIpv4Addr[4];
    wpt_uint8  aDestMacAddr[6];
    wpt_uint8  bssIdx;
} WDI_KeepAliveReqType;

/*                                                                           
                            
                                   
                                                                           */
typedef struct 
{ 
   /*                                                */ 
   WDI_KeepAliveReqType     wdiKeepAliveInfo; 
   /*                                                                         
                                                                                
                */ 
   WDI_ReqStatusCb            wdiReqStatusCB; 
   /*                                                                    
                                   */ 
   void*                      pUserData; 
}WDI_KeepAliveReqParamsType;

/*                                                                           
                           
                                            
                                                                           */
typedef struct
{
   wpt_uint8  ucPatternId;           //           
   //                                                                        
   //                
   wpt_uint8  ucPatternByteOffset;   
   wpt_uint8  ucPatternSize;         //                      
   wpt_uint8  ucPattern[WDI_WOWL_BCAST_PATTERN_MAX_SIZE]; //        
   wpt_uint8  ucPatternMaskSize;     //                           
   wpt_uint8  ucPatternMask[WDI_WOWL_BCAST_PATTERN_MAX_SIZE]; //             
   wpt_uint8  ucPatternExt[WDI_WOWL_BCAST_PATTERN_MAX_SIZE]; //              
   wpt_uint8  ucPatternMaskExt[WDI_WOWL_BCAST_PATTERN_MAX_SIZE]; //                   
   wpt_uint8  bssIdx;
} WDI_WowlAddBcPtrnInfoType;

/*                                                                           
                                
                                           
                                                                           */
typedef struct 
{ 
   /*                                                       */ 
   WDI_WowlAddBcPtrnInfoType     wdiWowlAddBcPtrnInfo; 
   /*                                                                         
                                                                                
                */ 
   WDI_ReqStatusCb            wdiReqStatusCB; 
   /*                                                                    
                                   */ 
   void*                      pUserData; 
}WDI_WowlAddBcPtrnReqParamsType;

/*                                                                           
                           
                                            
                                                                           */
typedef struct
{
   /*                                                */
   wpt_uint8  ucPatternId;
} WDI_WowlDelBcPtrnInfoType;

/*                                                                           
                                
                                           
                                                                           */
typedef struct 
{ 
   /*                                                         */ 
   WDI_WowlDelBcPtrnInfoType     wdiWowlDelBcPtrnInfo; 
   /*                                                                         
                                                                                
                */ 
   WDI_ReqStatusCb            wdiReqStatusCB; 
   /*                                                                    
                                   */ 
   void*                      pUserData; 
}WDI_WowlDelBcPtrnReqParamsType;

/*                                                                           
                       
                                         
                                                                           */
typedef struct
{
   /*                                         */
   wpt_uint8   ucMagicPktEnable; 

   /*               */
   wpt_macAddr magicPtrn;

   /*                                                        
                                                            
                                                                 
                                                              
              
   */
   wpt_uint8   ucPatternFilteringEnable;

   /*                                                    
                                                              
                                                                 
                                                              
                                             
   */
   wpt_uint8   ucUcastPatternFilteringEnable;                     

   /*                                                         
                                                           
                                  
    */
   wpt_uint8   ucWowChnlSwitchRcv;

   /*                                                         
                                                           
                              
    */
   wpt_uint8   ucWowDeauthRcv;

   /*                                                         
                                                           
                            
    */
   wpt_uint8   ucWowDisassocRcv;

   /*                                                         
                                                        
                                                      
                                                    
    */
   wpt_uint8   ucWowMaxMissedBeacons;

   /*                                                         
                                                               
                                                             
                                                                        
    */
   wpt_uint8   ucWowMaxSleepUsec;

#ifdef WLAN_WAKEUP_EVENTS
    /*                                                                       
                                                                       
     */
    wpt_uint8   ucWoWEAPIDRequestEnable;

    /*                                                                           
                                              
     */
    wpt_uint8   ucWoWEAPOL4WayEnable;

    /*                                                                          
     */
    wpt_uint8   ucWowNetScanOffloadMatch;

    /*                                                                   
     */
    wpt_uint8   ucWowGTKRekeyError;

    /*                                                                
     */
    wpt_uint8   ucWoWBSSConnLoss;
#endif //                   
} WDI_WowlEnterInfoType;

/*                                                                           
                            
                                        
                                                                           */
typedef struct 
{ 
   /*                                                           */ 
   WDI_WowlEnterInfoType     wdiWowlEnterInfo; 
   /*                                                                         
                                                                                
                */ 
   WDI_ReqStatusCb            wdiReqStatusCB; 
   /*                                                                    
                                   */ 
   void*                      pUserData; 
}WDI_WowlEnterReqParamsType;

/*                                                                           
                                              
                                                         
                                                                           */
typedef struct 
{ 
   /*                                  */ 
   wpt_boolean                bIsAppsAwake;
   /*                                                                         
                                                                                
                */ 
   WDI_ReqStatusCb            wdiReqStatusCB; 
   /*                                                                    
                                   */ 
   void*                      pUserData; 
}WDI_ConfigureAppsCpuWakeupStateReqParamsType;
/*                                                                           
                        
                                                                           */
typedef struct
{
   //             
   wpt_uint16 usMesgType;

   //               
   wpt_uint16 usMesgLen;

   //                                   
   wpt_uint8  ucSTAId;

   //                                                   
   wpt_uint8  ucTid;
  
}WDI_FlushAcReqinfoType;

/*                                                                           
                          
                                                                           */
typedef struct
{
  /*        */
  WDI_FlushAcReqinfoType  wdiFlushAcInfo; 

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_FlushAcReqParamsType;

/*                                                                           
                        
                            
                                                                           */
typedef struct
{
  wpt_uint8 ucBtAmpEventType;

} WDI_BtAmpEventinfoType;

/*                                                                           
                          
                                                                           */
typedef struct
{
  /*                  */
  WDI_BtAmpEventinfoType  wdiBtAmpEventInfo; 

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_BtAmpEventParamsType;

#ifdef FEATURE_OEM_DATA_SUPPORT

#ifndef OEM_DATA_REQ_SIZE
#define OEM_DATA_REQ_SIZE 70
#endif
#ifndef OEM_DATA_RSP_SIZE
#define OEM_DATA_RSP_SIZE 968
#endif

/*                                                                            
                        
                                                                            */
typedef struct
{
  wpt_macAddr                  selfMacAddr;
  wpt_uint8                    oemDataReq[OEM_DATA_REQ_SIZE];
}WDI_oemDataReqInfoType;

/*                                                                            
                          
                                                                            */
typedef struct
{
  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb                wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*                          pUserData;

  /*                  */
  WDI_oemDataReqInfoType         wdiOemDataReqInfo;

}WDI_oemDataReqParamsType;

/*                                                                            
                          
                                                                            */
typedef struct
{
  wpt_uint8           oemDataRsp[OEM_DATA_RSP_SIZE];
}WDI_oemDataRspParamsType;

#endif /*                          */

#ifdef WLAN_FEATURE_VOWIFI_11R
/*                                                                           
                          
                                                                           */
typedef struct
{
  /*         */
  wpt_uint8         ucSTAIdx; 

  /*                    */
  wpt_uint8         ucTspecIdx;

  /*                       */
  WDI_TspecIEType   wdiTspecIE[WDI_MAX_NO_AC];

  /*                                         */
  wpt_uint8         ucUapsdFlags;

  /*              */
  wpt_uint8         ucServiceInterval[WDI_MAX_NO_AC];

  /*                            */
  wpt_uint8         ucSuspendInterval[WDI_MAX_NO_AC];

  /*              */
  wpt_uint8         ucDelayedInterval[WDI_MAX_NO_AC];

}WDI_AggrAddTSReqInfoType;


/*                                                                           
                            
                                                                           */
typedef struct
{
  /*           */
  WDI_AggrAddTSReqInfoType  wdiAggrTsInfo; 

  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}WDI_AggrAddTSReqParamsType;

#endif /*                         */

#ifdef ANI_MANF_DIAG
/*                                                                           
                       
                                                                           */
typedef struct
{
   /*                         */
   wpt_uint32   bodyLength;
   /*                         */
   void        *FTMCommandBody;
}WDI_FTMCommandReqType;
#endif /*               */

/*                                                                           
                         
                                                                           */
typedef struct 
{
  /*                                            */
  wpt_uint8 ucConfiguredMcstBcstFilterSetting;
}WDI_WlanSuspendInfoType;

/*                                                                           
                       
                                                                           */
typedef struct
{
  WDI_WlanSuspendInfoType wdiSuspendParams;

   /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;

}WDI_SuspendParamsType;

/*                                                                           
                        
                                                                           */
typedef struct 
{
  /*                                            */
  wpt_uint8 ucConfiguredMcstBcstFilterSetting;
}WDI_WlanResumeInfoType;

/*                                                                           
                      
                                                                           */
typedef struct
{
  WDI_WlanResumeInfoType wdiResumeParams;

   /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;

}WDI_ResumeParamsType;

#ifdef WLAN_FEATURE_GTK_OFFLOAD
/*                                                                           
                      
                                                                            */

typedef struct
{
  wpt_uint32     ulFlags;             /*                */
  wpt_uint8      aKCK[16];            /*                      */ 
  wpt_uint8      aKEK[16];            /*                    */
  wpt_uint64     ullKeyReplayCounter; /*                */
} WDI_GtkOffloadReqParams;

typedef struct
{
   WDI_GtkOffloadReqParams gtkOffloadReqParams;

   /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
} WDI_GtkOffloadReqMsg;

/*                                                                           
                      
                                                                            */
typedef struct
{
    /*                    */
    wpt_uint32   ulStatus;
} WDI_GtkOffloadRspParams;

typedef struct
{
   WDI_GtkOffloadRspParams gtkOffloadRspParams;

   /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
} WDI_GtkOffloadRspMsg;


/*                                                                           
                             
                                                                           */

typedef struct
{
   /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
} WDI_GtkOffloadGetInfoReqMsg;

/*                                                                           
                             
                                                                           */
typedef struct
{
   wpt_uint32   ulStatus;             /*                    */
   wpt_uint64   ullKeyReplayCounter;  /*                              */
   wpt_uint32   ulTotalRekeyCount;    /*                      */
   wpt_uint32   ulGTKRekeyCount;      /*                       */
   wpt_uint32   ulIGTKRekeyCount;     /*                        */
} WDI_GtkOffloadGetInfoRspParams;

typedef struct
{
   WDI_GtkOffloadGetInfoRspParams gtkOffloadGetInfoRspParams;

   /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 

  /*                                                                    
                                    */
  void*             pUserData;
}  WDI_GtkOffloadGetInfoRspMsg;
#endif //                         

/*                                                                           
                                
                                                                           */
typedef struct
{
  /*                      */
  WDI_Status   wdiStatus; 
}WDI_SuspendResumeRspParamsType;


#ifdef FEATURE_WLAN_SCAN_PNO

/*                                                           */
#define WDI_PNO_MAX_NETW_CHANNELS  26

/*                                              */
#define WDI_PNO_MAX_SUPP_NETWORKS  16

/*                                                 */
#define WDI_PNO_MAX_SCAN_TIMERS    10

#define WDI_PNO_MAX_PROBE_SIZE    450


/*                                                                           
              
                                                                           */
typedef enum 
{
    WDI_AUTH_TYPE_ANY     = 0, 

    WDI_AUTH_TYPE_NONE,   
    WDI_AUTH_TYPE_OPEN_SYSTEM,
    WDI_AUTH_TYPE_SHARED_KEY,

    WDI_AUTH_TYPE_WPA,
    WDI_AUTH_TYPE_WPA_PSK,
    WDI_AUTH_TYPE_WPA_NONE,

    WDI_AUTH_TYPE_RSN,
    WDI_AUTH_TYPE_RSN_PSK,
    WDI_AUTH_TYPE_FT_RSN,
    WDI_AUTH_TYPE_FT_RSN_PSK,
    WDI_AUTH_TYPE_WAPI_WAI_CERTIFICATE,
    WDI_AUTH_TYPE_WAPI_WAI_PSK,
    WDI_AUTH_TYPE_MAX = 0xFFFFFFFF /*                            */

}WDI_AuthType;

/*                                                                           
            
                                                                           */
typedef enum
{
    WDI_ED_ANY        = 0, 
    WDI_ED_NONE, 
    WDI_ED_WEP40,
    WDI_ED_WEP104,
    WDI_ED_TKIP,
    WDI_ED_CCMP,
    WDI_ED_WPI,
    WDI_ED_AES_128_CMAC,
    WDI_ED_MAX = 0xFFFFFFFF /*                            */
} WDI_EdType;


/*                                                                           
             
                                                                           */
typedef enum
{
  /*                                       */
  WDI_PNO_MODE_IMMEDIATE,

  /*                                           */
  WDI_PNO_MODE_ON_SUSPEND,

  /*                                          */
  WDI_PNO_MODE_ON_RESUME,
  WDI_PNO_MODE_MAX = 0xFFFFFFFF
} WDI_PNOMode;

/*                      */
typedef enum 
{
  WDI_BCAST_UNKNOWN      = 0,
  WDI_BCAST_NORMAL       = 1,
  WDI_BCAST_HIDDEN       = 2,

  WDI_BCAST_TYPE_MAX     = 0xFFFFFFFF
} WDI_SSIDBcastType;

/*                                                                           
                 
                                                                           */
typedef struct 
{
  /*                                 */
  WDI_MacSSid  ssId;

  /*                                                  */
  WDI_AuthType wdiAuth; 

  /*                                              */
  WDI_EdType   wdiEncryption; 

  /*                                              */
  WDI_SSIDBcastType wdiBcastNetworkType;

  /*                                  */
  wpt_uint8    ucChannelCount;

  /*                   */
  wpt_uint8    aChannels[WDI_PNO_MAX_NETW_CHANNELS];

  /*                                                                     */
  wpt_uint8    rssiThreshold;
} WDI_NetworkType; 


/*                                                                           
               
                                                                           */
typedef struct 
{
  /*               */
  wpt_uint32    uTimerValue; 

  /*                                                      */
  wpt_uint32    uTimerRepeat; 
} WDI_ScanTimer; 

/*                                                                           
                    
                                                                           */
typedef struct
{
  /*                                                       */
  wpt_uint8      ucScanTimersCount; 

  /*                           */
  WDI_ScanTimer  aTimerValues[WDI_PNO_MAX_SCAN_TIMERS]; 
} WDI_ScanTimersType;

/*                                                                           
                    
                                                                           */
typedef struct 
{
  /*                             */
  wpt_uint8           bEnable;

  /*                  */
  WDI_PNOMode         wdiModePNO;

  /*             */
  wpt_uint8           ucNetworksCount; 

  /*                        */
  WDI_NetworkType     aNetworks[WDI_PNO_MAX_SUPP_NETWORKS];

  /*                    */
  WDI_ScanTimersType  scanTimers; 

  /*                              */
  wpt_uint16          us24GProbeSize; 
  wpt_uint8           a24GProbeTemplate[WDI_PNO_MAX_PROBE_SIZE];

  /*                            */
  wpt_uint16          us5GProbeSize; 
  wpt_uint8           a5GProbeTemplate[WDI_PNO_MAX_PROBE_SIZE];
} WDI_PNOScanReqType;

/*                                                                           
                          
                                 
                                                                           */
typedef struct 
{ 
   /*                                            */ 
   WDI_PNOScanReqType        wdiPNOScanInfo; 
   /*                                                                          
                                                                                
                */ 
   WDI_ReqStatusCb            wdiReqStatusCB; 
   /*                                                                     
                                   */ 
   void*                      pUserData; 
} WDI_PNOScanReqParamsType;

/*                                                                           
                                
                                 
                                                                           */
typedef struct 
{ 
   /*                */ 
   wpt_uint8                  rssiThreshold; 
   /*                                                                          
                                                                                
                */ 
   WDI_ReqStatusCb            wdiReqStatusCB; 
   /*                                                                     
                                   */ 
   void*                      pUserData; 
} WDI_SetRssiFilterReqParamsType;

/*                                                                           
                          
                                                                           */
typedef struct 
{
  /*              */
  wpt_uint8    b11dEnabled; 

  /*                                           */
  wpt_uint8    b11dResolved;

  /*                                                  */
  wpt_uint8    ucChannelCount; 

  /*                                                    */
  wpt_uint8    aChannels[WDI_PNO_MAX_NETW_CHANNELS]; 

  /*                        */
  wpt_uint16   usPassiveMinChTime; 

  /*                        */
  wpt_uint16   usPassiveMaxChTime; 

  /*                       */
  wpt_uint16   usActiveMinChTime; 

  /*                       */
  wpt_uint16   usActiveMaxChTime; 

  /*                    */
  wpt_uint8    cbState; 
} WDI_UpdateScanParamsInfo;

/*                                                                           
                              
                                              
                                                                           */
typedef struct 
{ 
   /*                                          */ 
   WDI_UpdateScanParamsInfo   wdiUpdateScanParamsInfo; 
   /*                                                                          
                                                                                
                */ 
   WDI_ReqStatusCb            wdiReqStatusCB; 
   /*                                                                     
                                   */ 
   void*                      pUserData; 
} WDI_UpdateScanParamsInfoType;
#endif //                      

/*                                                                           
                          
                                                                           */
typedef struct 
{
   /*              */
  wpt_uint32 uIgnoreDTIM;

  /*           */
  wpt_uint32 uDTIMPeriod;

  /*                 */
  wpt_uint32 uListenInterval;

  /*                            */
  wpt_uint32 uBcastMcastFilter;

  /*                          */
  wpt_uint32 uEnableBET;

  /*                                   */
  wpt_uint32 uBETInterval; 

} WDI_SetPowerParamsInfo;

/*                                                                           
                              
                                              
                                                                           */
typedef struct 
{ 
   /*                                                    */ 
   WDI_SetPowerParamsInfo     wdiSetPowerParamsInfo; 
   /*                                                                          
                                                                                
                */ 
   WDI_ReqStatusCb            wdiReqStatusCB; 
   /*                                                                     
                                   */ 
   void*                      pUserData;
}WDI_SetPowerParamsReqParamsType;

/*                                                                           
                              
                                            
                                                                           */
typedef struct
{
   wpt_uint8  ucTxPerTrackingEnable;     /*                      */
   wpt_uint8  ucTxPerTrackingPeriod;        /*                            */
   wpt_uint8  ucTxPerTrackingRatio;      /*                                                            */
   wpt_uint32 uTxPerTrackingWatermark;         /*                                                                                                   */
} WDI_TxPerTrackingParamType;

/*                                                                           
                                   
                                                   
                                                                           */
typedef struct 
{ 
  /*                                    */ 
  WDI_TxPerTrackingParamType     wdiTxPerTrackingParam;
  /*                                                                         
                                                                                 
                 */ 
  WDI_ReqStatusCb            wdiReqStatusCB; 
  /*                                                                    
                                    */ 
  void*                      pUserData; 
}WDI_SetTxPerTrackingReqParamsType;

#ifdef WLAN_FEATURE_PACKET_FILTERING
/*                                                                           
                             
                                                                           */

#define    WDI_IPV4_ADDR_LEN                  4
#define    WDI_MAC_ADDR_LEN                   6
#define    WDI_MAX_FILTER_TEST_DATA_LEN       8
#define    WDI_MAX_NUM_MULTICAST_ADDRESS    240
#define    WDI_MAX_NUM_FILTERS               20 
#define    WDI_MAX_NUM_TESTS_PER_FILTER      10 

//
//                          
//
typedef enum
{
  WDI_RCV_FILTER_TYPE_INVALID,
  WDI_RCV_FILTER_TYPE_FILTER_PKT,
  WDI_RCV_FILTER_TYPE_BUFFER_PKT,
  WDI_RCV_FILTER_TYPE_MAX_ENUM_SIZE
}WDI_ReceivePacketFilterType;

typedef enum 
{
  WDI_FILTER_HDR_TYPE_INVALID,
  WDI_FILTER_HDR_TYPE_MAC,
  WDI_FILTER_HDR_TYPE_ARP,
  WDI_FILTER_HDR_TYPE_IPV4,
  WDI_FILTER_HDR_TYPE_IPV6,
  WDI_FILTER_HDR_TYPE_UDP,
  WDI_FILTER_HDR_TYPE_MAX
}WDI_RcvPktFltProtocolType;

typedef enum 
{
  WDI_FILTER_CMP_TYPE_INVALID,
  WDI_FILTER_CMP_TYPE_EQUAL,
  WDI_FILTER_CMP_TYPE_MASK_EQUAL,
  WDI_FILTER_CMP_TYPE_NOT_EQUAL,
  WDI_FILTER_CMP_TYPE_MASK_NOT_EQUAL,
  WDI_FILTER_CMP_TYPE_MAX
}WDI_RcvPktFltCmpFlagType;

typedef struct
{
  WDI_RcvPktFltProtocolType          protocolLayer;
  WDI_RcvPktFltCmpFlagType           cmpFlag;
/*                               */
  wpt_uint16                         dataLength; 
/*                                           */  
  wpt_uint8                          dataOffset; 
  wpt_uint8                          reserved; /*                */
/*                 */
  wpt_uint8                          compareData[WDI_MAX_FILTER_TEST_DATA_LEN];  
/*                                                               */
  wpt_uint8                          dataMask[WDI_MAX_FILTER_TEST_DATA_LEN];   
}WDI_RcvPktFilterFieldParams;

typedef struct
{
  wpt_uint8                       filterId; 
  wpt_uint8                       filterType;
  wpt_uint32                      numFieldParams;
  wpt_uint32                      coalesceTime;
  WDI_RcvPktFilterFieldParams     paramsData[1];
  wpt_macAddr                     selfMacAddr;
  wpt_macAddr                     bssId;
}WDI_RcvPktFilterCfgType;

typedef struct 
{
  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 
    
  /*                                                                    
                                    */
  void*             pUserData;
    
  //                                           
  WDI_RcvPktFilterCfgType wdiPktFilterCfg;
} WDI_SetRcvPktFilterReqParamsType;

//
//                                     
//
typedef struct
{
  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 
    
  /*                                                                    
                                    */
  void*             pUserData;
} WDI_RcvFltPktMatchCntReqParamsType;

typedef struct
{
  wpt_uint8    filterId;
  wpt_uint32   matchCnt;
} WDI_RcvFltPktMatchCnt;

typedef struct
{
  /*                    */
  wpt_uint32                 status;
  WDI_RcvFltPktMatchCnt    filterMatchCnt[WDI_MAX_NUM_FILTERS];
  
  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 
    
  /*                                                                    
                                    */
  void*             pUserData;
} WDI_RcvFltPktMatchRspParams;

typedef struct
{
  WDI_RcvFltPktMatchRspParams fltPktMatchRspParams;
  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 
    
  /*                                                                    
                                    */
  void*             pUserData;
} WDI_RcvFltPktMatchCntRspParamsType;


//
//                                
//
typedef struct
{
  wpt_uint32   status;  /*                                 */
  wpt_uint8    filterId;
  wpt_macAddr  selfMacAddr;
  wpt_macAddr  bssId;
}WDI_RcvFltPktClearParam;

typedef struct
{
  WDI_RcvFltPktClearParam     filterClearParam;
  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 
    
  /*                                                                    
                                    */
  void*             pUserData;
} WDI_RcvFltPktClearReqParamsType;

//
//                                  
//
typedef struct 
{
  wpt_uint32     ulMulticastAddrCnt;
  wpt_macAddr    multicastAddr[WDI_MAX_NUM_MULTICAST_ADDRESS];
  wpt_macAddr    selfMacAddr;
  wpt_macAddr    bssId;
} WDI_RcvFltMcAddrListType;

typedef struct
{
  WDI_RcvFltMcAddrListType         mcAddrList;
  /*                                                                     
                                                                         
                             */
  WDI_ReqStatusCb   wdiReqStatusCB; 
    
  /*                                                                    
                                    */
  void*             pUserData;
} WDI_RcvFltPktSetMcListReqParamsType;
#endif //                              

/*                                                                           
                           
                                                                           */
typedef struct
{
  /*       */
  wpt_uint32 command;

  /*         */
  wpt_uint32 argument1;
  wpt_uint32 argument2;
  wpt_uint32 argument3;
  wpt_uint32 argument4;

}WDI_HALDumpCmdReqInfoType;

/*                                                                           
                            
                                                                           */
typedef struct
{
  /*            */
  WDI_HALDumpCmdReqInfoType  wdiHALDumpCmdInfoType; 

  /*                                                                     
                                                                        
                            */
  WDI_ReqStatusCb       wdiReqStatusCB; 

  /*                                                                    
                                   */
  void*                 pUserData;
  
}WDI_HALDumpCmdReqParamsType;


/*                                                                           
                             
                                                                           */
typedef struct
{
  /*                       */
  WDI_Status       wdiStatus;

  /*                      */
  wpt_uint16       usBufferLen;
    
  /*        */
  wpt_uint8       *pBuffer;
}WDI_HALDumpCmdRspParamsType;


/*                                                                           
                       
                                                                           */
typedef struct
{
  wpt_uint16       tmMode;
  wpt_uint16       tmLevel;
  void*            pUserData;
}WDI_SetTmLevelReqType;

/*                                                                           
                       
                                                                           */
typedef struct
{
  WDI_Status       wdiStatus;
  void*            pUserData;
}WDI_SetTmLevelRspType;

/*                                                                            
                       
                                                                            */

/*                                                                           
                 
 
                 
 
                                                                             
                         
 
              

      
                                                        
                               
    
  
               
                                                            
                                                                           */
typedef void (*WDI_StartRspCb)(WDI_StartRspParamsType*   pwdiRspParams,
                               void*                     pUserData);

/*                                                                           
                 
 
                 
 
                                                                            
                         
 
              

      
                                                 
                           
 
    
  
               
                                                            
                                                                           */
typedef void (*WDI_StopRspCb)(WDI_Status   wdiStatus,
                              void*        pUserData);

/*                                                                           
                 
 
                 
 
                                                                             
                              
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_InitScanRspCb)(WDI_Status   wdiStatus,
                                   void*        pUserData);


/*                                                                           
                 
 
                 
 
                                                                            
                              
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_StartScanRspCb)(WDI_StartScanRspParamsType*  wdiParams,
                                    void*                        pUserData);


/*                                                                           
                 
 
                 
 
                                                                           
                              
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_EndScanRspCb)(WDI_Status   wdiStatus,
                                  void*        pUserData);


/*                                                                           
                 
 
                 
 
                                                                              
                              
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_FinishScanRspCb)(WDI_Status   wdiStatus,
                                     void*        pUserData);


/*                                                                           
                 
 
                 
 
                                                                            
                         
 
              

      
                                                 
                           
 
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_JoinRspCb)(WDI_Status   wdiStatus,
                               void*        pUserData);


/*                                                                           
                 
 
                 
 
                                                                             
                              
 
              

      
                                                           
                               
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_ConfigBSSRspCb)(
                            WDI_ConfigBSSRspParamsType*   pwdiConfigBSSRsp,
                            void*                        pUserData);


/*                                                                           
                 
 
                 
 
                                                                               
                         
 
              

      
                                                        
                               
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_DelBSSRspCb)(WDI_DelBSSRspParamsType*  pwdiDelBSSRsp,
                                 void*                     pUserData);


/*                                                                           
                 
 
                 
 
                                                                             
                              
 
              

      
                                                        
                               
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_PostAssocRspCb)(
                               WDI_PostAssocRspParamsType*  pwdiPostAssocRsp,
                               void*                        pUserData);


/*                                                                           
                 
 
                 
 
                                                                               
                         
 
              

      
                                                        
                               
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_DelSTARspCb)(WDI_DelSTARspParamsType*   pwdiDelSTARsp,
                                 void*                      pUserData);



/*                                                                           
                 
 
                 
 
                                                                              
                              
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_SetBSSKeyRspCb)(WDI_Status   wdiStatus,
                                    void*        pUserData);

/*                                                                           
                 
 
                 
 
                                                                        
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_RemoveBSSKeyRspCb)(WDI_Status   wdiStatus,
                                       void*        pUserData);

/*                                                                           
                 
 
                 
 
                                                                              
                              
 
              

      
                                                 
                           
  
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_SetSTAKeyRspCb)(WDI_Status   wdiStatus,
                                    void*        pUserData);

 
/*                                                                           
                 
 
                 
 
                                                                        
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_RemoveSTAKeyRspCb)(WDI_Status   wdiStatus,
                                       void*        pUserData);


#ifdef FEATURE_WLAN_CCX 
/*                                                                           
               
 
                 
 
                                                                                                        
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_TsmRspCb)(WDI_TSMStatsRspParamsType *pTSMStats,
                                void*        pUserData);
#endif

/*                                                                           
                 
 
                 
 
                                                                              
                         
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_AddTsRspCb)(WDI_Status   wdiStatus,
                                void*        pUserData);

/*                                                                           
                 
 
                 
 
                                                                              
                         
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_DelTsRspCb)(WDI_Status   wdiStatus,
                                void*        pUserData);

/*                                                                           
                 
 
                 
 
                                                                             
                                       
 
              

      
                                                 
                           
 
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_UpdateEDCAParamsRspCb)(WDI_Status   wdiStatus,
                                           void*        pUserData);

/*                                                                           
                 
 
                 
 
                                                                              
                         
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_AddBASessionRspCb)(
                            WDI_AddBASessionRspParamsType* wdiAddBASessionRsp,
                            void*                         pUserData);

 
/*                                                                           
                 
 
                 
 
                                                                              
                         
 
              

      
                                                 
                           
    
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_DelBARspCb)(WDI_Status   wdiStatus,
                                void*        pUserData);

 
/*                                                                           
                 
 
                 
 
                                                                            
                              
 
              

      
                                                        
                               
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_SwitchChRspCb)(WDI_SwitchCHRspParamsType*  pwdiSwitchChRsp,
                                   void*                       pUserData);

 
/*                                                                           
                 
 
                 
 
                                                                             
                              
 
              

      
                                                        
                               
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_ConfigSTARspCb)(
                            WDI_ConfigSTARspParamsType*  pwdiConfigSTARsp,
                            void*                        pUserData);

 
/*                                                                           
                 
 
                 
 
                                                                        
                                       
 
              

      
                                                        
                               
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_SetLinkStateRspCb)( WDI_Status   wdiStatus,
                                        void*        pUserData);

 
/*                                                                           
                 
 
                 
 
                                                                            
                              
 
              

      
                                                        
                               
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_GetStatsRspCb)(WDI_GetStatsRspParamsType*  pwdiGetStatsRsp,
                                   void*                       pUserData);

 
/*                                                                           
                 
 
                 
 
                                                                             
                              
 
              

      
                                                 
                           
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_UpdateCfgRspCb)(WDI_Status   wdiStatus,
                                    void*        pUserData);

/*                                                                           
                 
 
                 
 
                                                                         
                              
 
              

      
                                                 
                           
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_AddBARspCb)(WDI_AddBARspinfoType*   wdiAddBARsp,
                                    void*        pUserData);

/*                                                                           
                     
 
                 
 
                                                                         
                              
 
              

      
                                                 
                           
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_TriggerBARspCb)(WDI_TriggerBARspParamsType*   wdiTriggerBARsp,
                                    void*        pUserData);


/*                                                                           
                              
 
                 
 
                                                                                            
                         
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_UpdateBeaconParamsRspCb)(WDI_Status   wdiStatus,
                                void*        pUserData);

/*                                                                           
                            
 
                 
 
                                                                                          
                         
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_SendBeaconParamsRspCb)(WDI_Status   wdiStatus,
                                void*        pUserData);

/*                                                                           
                         
 
                 
 
                                                                                        
                         
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void (*WDA_SetMaxTxPowerRspCb)(WDI_SetMaxTxPowerRspMsg *wdiSetMaxTxPowerRsp,
                                             void* pUserData);

/*                                                                           
                                  
 
                 
 
                                                                            
                                               
 
              

      
                                                 
                           
    
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_UpdateProbeRspTemplateRspCb)(WDI_Status   wdiStatus,
                                               void*        pUserData);

#ifdef WLAN_FEATURE_P2P
/*                                                                           
                                
 
                 
 
                                                                                         
                         
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_SetP2PGONOAReqParamsRspCb)(WDI_Status   wdiStatus,
                                void*        pUserData);
#endif


/*                                                                           
                      
 
                 
 
                                                                            
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_SetPwrSaveCfgCb)(WDI_Status   wdiStatus,
                                     void*        pUserData);

/*                                                                           
                         
 
                 
 
                                                                          
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_SetUapsdAcParamsCb)(WDI_Status   wdiStatus,
                                        void*        pUserData);

/*                                                                           
                     
 
                 
 
                                                                             
                              
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_EnterImpsRspCb)(WDI_Status   wdiStatus,
                                    void*        pUserData);

/*                                                                           
                    
 
                 
 
                                                                            
                              
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_ExitImpsRspCb)(WDI_Status   wdiStatus,
                                    void*        pUserData);

/*                                                                           
                     
 
                 
 
                                                                             
                              
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_EnterBmpsRspCb)(WDI_Status   wdiStatus,
                                    void*        pUserData);

/*                                                                           
                    
 
                 
 
                                                                            
                              
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_ExitBmpsRspCb)(WDI_Status   wdiStatus,
                                    void*        pUserData);

/*                                                                           
                      
 
                 
 
                                                                              
                              
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_EnterUapsdRspCb)(WDI_Status   wdiStatus,
                                    void*        pUserData);

/*                                                                           
                     
 
                 
 
                                                                             
                              
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_ExitUapsdRspCb)(WDI_Status   wdiStatus,
                                    void*        pUserData);

/*                                                                           
                          
 
                 
 
                                                                             
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_UpdateUapsdParamsCb)(WDI_Status   wdiStatus,
                                        void*        pUserData);

/*                                                                           
                           
 
                 
 
                                                                           
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_ConfigureRxpFilterCb)(WDI_Status   wdiStatus,
                                          void*        pUserData);

/*                                                                           
                        
 
                 
 
                                                                           
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_SetBeaconFilterCb)(WDI_Status   wdiStatus,
                                       void*        pUserData);

/*                                                                           
                        
 
                 
 
                                                                              
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_RemBeaconFilterCb)(WDI_Status   wdiStatus,
                                       void*        pUserData);

/*                                                                           
                          
 
                 
 
                                                                             
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_SetRSSIThresholdsCb)(WDI_Status   wdiStatus,
                                         void*        pUserData);

/*                                                                           
                    
 
                 
 
                                                                      
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_HostOffloadCb)(WDI_Status   wdiStatus,
                                   void*        pUserData);

/*                                                                           
                  
 
                 
 
                                                                    
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_KeepAliveCb)(WDI_Status   wdiStatus,
                                   void*        pUserData);

/*                                                                           
                      
 
                 
 
                                                                             
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_WowlAddBcPtrnCb)(WDI_Status   wdiStatus,
                                     void*        pUserData);

/*                                                                           
                      
 
                 
 
                                                                                
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_WowlDelBcPtrnCb)(WDI_Status   wdiStatus,
                                     void*        pUserData);

/*                                                                           
                     
 
                 
 
                                                                    
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_WowlEnterReqCb)(WDI_Status   wdiStatus,
                                    void*        pUserData);

/*                                                                           
                    
 
                 
 
                                                                   
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_WowlExitReqCb)(WDI_Status   wdiStatus,
                                   void*        pUserData);

/*                                                                           
                                    
 
                 
 
                                                                                
                                             
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_ConfigureAppsCpuWakeupStateCb)(WDI_Status   wdiStatus,
                                                   void*        pUserData);
/*                                                                           
                      
 
              
 
                                                                              
                              
 
              

     
                                              
                         
  
               
                                                            
                                                                           */
typedef void  (*WDI_NvDownloadRspCb)(WDI_NvDownloadRspInfoType* wdiNvDownloadRsp,
                                          void*  pUserData);
/*                                                                           
                   
 
                 
 
                                                                                
                         
 
              

      
                                                 
                           
    
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_FlushAcRspCb)(WDI_Status   wdiStatus,
                                  void*        pUserData);

/*                                                                           
                      
 
                 
 
                                                                               
                              
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_BtAmpEventRspCb)(WDI_Status   wdiStatus,
                                     void*        pUserData);

#ifdef FEATURE_OEM_DATA_SUPPORT
/*                                                                           
                   
 
                 
 
                                                                                      
                         
 
              

      
                                                 
                           
    
    
  
               
                                                            
                                                                           */
typedef void  (*WDI_oemDataRspCb)(WDI_oemDataRspParamsType* wdiOemDataRspParams, 
                                  void*                     pUserData);

#endif

/*                                                                           
                           
 
                 
 
                                                                               
                              
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_HostResumeEventRspCb)(
                        WDI_SuspendResumeRspParamsType   *resumeRspParams,
                        void*        pUserData);


#ifdef WLAN_FEATURE_VOWIFI_11R
/*                                                                           
                     
 
                 
 
                                                                           
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_AggrAddTsRspCb)(WDI_Status   wdiStatus,
                                    void*        pUserData);
#endif /*                         */

#ifdef ANI_MANF_DIAG
/*                                                                           
                      
 
                 
 
                          
 
              

      
                                              
                           
    
  
               
        
                                                                           */
typedef void (*WDI_FTMCommandRspCb)(void *ftmCMDRspdata,
                                    void *pUserData);
#endif /*               */

/*                                                                           
                             
 
                 
 
                                                                             
                                       
 
              

      
                                                        
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_AddSTASelfParamsRspCb)(
                    WDI_AddSTASelfRspParamsType* pwdiAddSelfSTARsp,
                    void*                        pUserData);


/*                                                                           
                      
 
                 
 
                                                                      
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_DelSTASelfRspCb)
(
WDI_DelSTASelfRspParamsType*     wdiDelStaSelfRspParams,
void*        pUserData
);

#ifdef FEATURE_WLAN_SCAN_PNO
/*                                                                           
                
 
                 
 
                                                                 
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_PNOScanCb)(WDI_Status  wdiStatus,
                                void*       pUserData);

/*                                                                           
                
 
                 
 
                                                                 
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_RssiFilterCb)(WDI_Status  wdiStatus,
                                void*       pUserData);

/*                                                                           
                         
 
                 
 
                                                                            
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_UpdateScanParamsCb)(WDI_Status  wdiStatus,
                                        void*       pUserData);
#endif //                      

/*                                                                           
                            
 
                 
 
                                                                         
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_SetTxPerTrackingRspCb)(WDI_Status   wdiStatus,
                                           void*        pUserData);
                                     
#ifdef WLAN_FEATURE_PACKET_FILTERING
/*                                                                           
                          
 
                 
 
                                                                             
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_8023MulticastListCb)(WDI_Status   wdiStatus,
                                         void*        pUserData);

/*                                                                           
                               
 
                 
 
                                                                                   
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_ReceiveFilterSetFilterCb)(WDI_Status   wdiStatus,
                                              void*        pUserData);

/*                                                                           
                         
 
                 
 
                                                                                  
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_FilterMatchCountCb)(WDI_Status   wdiStatus,
                                        void*        pUserData);

/*                                                                           
                                 
 
                 
 
                                                                                     
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_ReceiveFilterClearFilterCb)(WDI_Status   wdiStatus,
                                                void*        pUserData);
#endif //                              

/*                                                                           
                      
 
                 
 
                                                                           
             
                 
 
              

      
                                                        
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_HALDumpCmdRspCb)(WDI_HALDumpCmdRspParamsType* wdiHalDumpCmdRsp,
                                                                       void*  pUserData);

/*                                                                           
                       
 
                 
 
                                                                         
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_SetPowerParamsCb)(WDI_Status  wdiStatus,
                                      void*       pUserData);

#ifdef WLAN_FEATURE_GTK_OFFLOAD
/*                                                                           
                   
 
                 
 
                                                                     
                                       
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_GtkOffloadCb)(WDI_Status   wdiStatus,
                                  void*        pUserData);

/*                                                                           
                          
 
                 
 
                                                                     
                                                   
 
              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_GtkOffloadGetInfoCb)(WDI_Status   wdiStatus,
                                         void*        pUserData);
#endif //                         

/*                                                                           
                   
 
                 
 
                                                                          
                                            

              

      
                                                 
                           

    
  
               
                                                            
                                                                           */
typedef void  (*WDI_SetTmLevelCb)(WDI_Status  wdiStatus,
                                  void*       pUserData);

/*                                                                           
                            
 
                 
 
                                                                                
                                                                        
                                              
 
              

     
                                                              
                             
  
                
                                                           
                                                                           */
typedef void  (*WDI_featureCapsExchangeCb)(void* wdiFeatCapRspParams,
                                                void*        pUserData);

/*                                                                        
                                              
                                                                           */

/*                                                                         
 
                                                
 
                                                                          */

/* 
                                               
 
                                                                             
                                                                           
                                              
 
                                                                  
                                                    
                                                        
                                                              

                                    
*/
WDI_Status 
WDI_Init
( 
  void*                      pOSContext,
  void**                     ppWDIGlobalCtx,
  WDI_DeviceCapabilityType*  pWdiDevCapability,
  unsigned int               driverType
);

/* 
                                                               
                                                              
                                                               
                                                               
                                                           

                                                             
                                                              
                                                            
                         

                                

                                                             
                                          
  
                                                                
                                                    
  
                                                         
                 
  
               
                                    
*/
WDI_Status 
WDI_Start
(
  WDI_StartReqParamsType*  pwdiStartParams,
  WDI_StartRspCb           wdiStartRspCb,
  void*                    pUserData
);


/* 
                                                              
                                                              
                                                              
                                                               
                         

                                                   
  
                                                          

                                 

                                                           
                                          
  
                                                               
                                                   
  
                                                         
                 
  
               
                                    
*/
WDI_Status 
WDI_Stop
(
  WDI_StopReqParamsType*  pwdiStopParams,
  WDI_StopRspCb           wdiStopRspCb,
  void*                   pUserData
);

/* 
                                                              
                                                              
              
  
                                               

                                

            
  
              
                                    
*/
WDI_Status 
WDI_Close
(
  void
);


/* 
                                                                     
                                                  
                                                         

                                                            
                            

                                         


                                 

                                                              

                                    
*/
WDI_Status
WDI_Shutdown
(
 wpt_boolean closeTransport
);

/*                                                                         
 
                                      
 
                                                                          */

/* 
                                                                
                                                               
                                                              
                                                       
                                              

                                                                
                                       

                                 

                                                                
                                             
  
                                                                
                                                           
  
                                                         
                 
  
               
                                    
*/
WDI_Status 
WDI_InitScanReq
(
  WDI_InitScanReqParamsType*  pwdiInitScanParams,
  WDI_InitScanRspCb           wdiInitScanRspCb,
  void*                       pUserData
);

/* 
                                                           
                                                             
                                                            
                                                               
                                              

                                                                
                                       

                                       

                                                         
                                                       
  
                                                        
                                                              
              
  
                                                         
                 
  
                     
                                    
*/
WDI_Status 
WDI_StartScanReq
(
  WDI_StartScanReqParamsType*  pwdiStartScanParams,
  WDI_StartScanRspCb           wdiStartScanRspCb,
  void*                        pUserData
);


/* 
                                                            
                                                              
                                                                
                                                            
                                                             
                                              

                                                                
                                       

                                        

                                                               
                                             
  
                                                               
                                                          
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_EndScanReq
(
  WDI_EndScanReqParamsType* pwdiEndScanParams,
  WDI_EndScanRspCb          wdiEndScanRspCb,
  void*                     pUserData
);


/* 
                                                                
                                                               
                                                              
                                                             
                                              

                                                                
                                       

                                       

                                                            
                                                       
  
                                                         
                                                               
              
  
                                                         
                 
  
                     
                                    
*/
WDI_Status 
WDI_FinishScanReq
(
  WDI_FinishScanReqParamsType* pwdiFinishScanParams,
  WDI_FinishScanRspCb          wdiFinishScanRspCb,
  void*                        pUserData
);

/*                                                                         
 
                                          
 
                                                                          */

/* 
                                                               
                                                            
                                                              
                                                            
                                

                                                                
                                       

                                 

                                                           
                                          
  
                                                               
                                                   
  
                                                         
                 
  
               
                                    
*/
WDI_Status 
WDI_JoinReq
(
  WDI_JoinReqParamsType* pwdiJoinParams,
  WDI_JoinRspCb          wdiJoinRspCb,
  void*                  pUserData
);

/* 
                                                           
                                                               
                                                                
                                                                
                                                               
                

                                                                
                                       

                                   

                                                         
                                                       
  
                                                        
                                                              
              
  
                                                         
                 
  
                 
                                    
*/
WDI_Status 
WDI_ConfigBSSReq
(
  WDI_ConfigBSSReqParamsType* pwdiConfigBSSParams,
  WDI_ConfigBSSRspCb          wdiConfigBSSRspCb,
  void*                       pUserData
);

/* 
                                                           
                                                            
                                                            
                                                            
                                              

                                                                
                                       

                                                            

                                                                
                                          
  
                                                              
                                                         
  
                                                         
                 
  
                                         
                                    
*/
WDI_Status 
WDI_DelBSSReq
(
  WDI_DelBSSReqParamsType* pwdiDelBSSParams,
  WDI_DelBSSRspCb          wdiDelBSSRspCb,
  void*                    pUserData
);

/* 
                                                               
                                                          
                                                                
                                                              
                                                             

                                                                
                                       

                                   

                                                                
                                             
  
                                                        
                                                              
              
  
                                                         
                 
  
                 
                                    
*/
WDI_Status 
WDI_PostAssocReq
(
  WDI_PostAssocReqParamsType* pwdiPostAssocReqParams,
  WDI_PostAssocRspCb          wdiPostAssocRspCb,
  void*                       pUserData
);

/* 
                                                                
                                                              
                                                              
                                                         
                                                               
                

                                                                
                                       

                                        

                                                                
                                          
  
                                                              
                                                         
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_DelSTAReq
(
  WDI_DelSTAReqParamsType* pwdiDelSTAParams,
  WDI_DelSTARspCb          wdiDelSTARspCb,
  void*                    pUserData
);

/*                                                                         
 
                                          
 
                                                                          */

/* 
                                                               
                                                                
                                                            
                                                              
                         

                                                                
                                       

                                        

                                                          
                                                       
  
                                                        
                                                               
              
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_SetBSSKeyReq
(
  WDI_SetBSSKeyReqParamsType* pwdiSetBSSKeyParams,
  WDI_SetBSSKeyRspCb          wdiSetBSSKeyRspCb,
  void*                       pUserData
);


/* 
                                                                
                                                              
                                                            
                                                              
                         

                                                                
                                       

                                        

                                                                
                                                       
  
                                                           
                                                              
                  
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_RemoveBSSKeyReq
(
  WDI_RemoveBSSKeyReqParamsType* pwdiRemoveBSSKeyParams,
  WDI_RemoveBSSKeyRspCb          wdiRemoveBSSKeyRspCb,
  void*                          pUserData
);


/* 
                                                              
                                                              
                                                              
                                                         
                                              

                                                                
                                       

                                        

                                                          
                                                       
  
                                                        
                                                               
              
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_SetSTAKeyReq
(
  WDI_SetSTAKeyReqParamsType* pwdiSetSTAKeyParams,
  WDI_SetSTAKeyRspCb          wdiSetSTAKeyRspCb,
  void*                       pUserData
);


/* 
                                                              
                                                              
                                                              
                                                            
                                              

                                                                
                                       

                                        

                                                                
                                                       
  
                                                           
                                                              
                  
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_RemoveSTAKeyReq
(
  WDI_RemoveSTAKeyReqParamsType* pwdiRemoveSTAKeyParams,
  WDI_RemoveSTAKeyRspCb          wdiRemoveSTAKeyRspCb,
  void*                          pUserData
);

/* 
                                                                
                                                              
                                                            
                                                          
                                              

                                                                
                                       

                                        

                                                                
                                                       
  
                                                             
                                                               
              
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_SetSTABcastKeyReq
(
  WDI_SetSTAKeyReqParamsType* pwdiSetSTABcastKeyParams,
  WDI_SetSTAKeyRspCb          wdiSetSTABcastKeyRspCb,
  void*                       pUserData
);


/* 
                                                               
                                                               
                                                                
                                                       
                                              

                                                                
                                       

                                             

                                                        
                                                           
                               
  
                                                                
                                                               
                       
  
                                                         
                 
  
                           
                                    
*/
WDI_Status 
WDI_RemoveSTABcastKeyReq
(
  WDI_RemoveSTAKeyReqParamsType* pwdiRemoveSTABcastKeyParams,
  WDI_RemoveSTAKeyRspCb          wdiRemoveSTABcastKeyRspCb,
  void*                          pUserData
);

/* 
                                                           
                                                     
                                                              
                                                              
                                              

                                                                
                                       

                                             

                                                        
                                                           
                               
  
                                                                
                                                               
                       
  
                                                         
                 
  
                          
                                    
*/
WDI_Status 
WDI_SetMaxTxPowerReq
(
  WDI_SetMaxTxPowerParamsType*   pwdiSetMaxTxPowerParams,
  WDA_SetMaxTxPowerRspCb         wdiReqStatusCb,
  void*                          pUserData
);

#ifdef FEATURE_WLAN_CCX
/* 
                                                                 
                                
                                                                
                                       

                                                                
                                          
  
                                                                
                                                     
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_TSMStatsReq
(
  WDI_TSMStatsReqParamsType* pwdiTsmStatsReqParams,
  WDI_TsmRspCb          wdiTsmStatsRspCb,
  void*                   pUserData
);


#endif

/*                                                                         
 
                                           
 
                                                                          */

/* 
                                                                
                                                            
                                                              
                                                            
                                                              
                                                              
                                

                                                                
                                       

                                        

                                                                
                                          
  
                                                                
                                                     
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_AddTSReq
(
  WDI_AddTSReqParamsType* pwdiAddTsReqParams,
  WDI_AddTsRspCb          wdiAddTsRspCb,
  void*                   pUserData
);



/* 
                                                                
                                                             
                                                             
                                                             
                                                              
                         

                                                                
                                       

                                    

                                                                
                                          
  
                                                                
                                                     
  
                                                         
                 
  
                  
                                    
*/
WDI_Status 
WDI_DelTSReq
(
  WDI_DelTSReqParamsType* pwdiDelTsReqParams,
  WDI_DelTsRspCb          wdiDelTsRspCb,
  void*                   pUserData
);



/* 
                                                               
                                                               
                                                            
                                                           
                                                               
                

                                                                
                                       

                                        

                                                               
                                             
  
                                                               
                                                                
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_UpdateEDCAParams
(
  WDI_UpdateEDCAParamsType*    pwdiUpdateEDCAParams,
  WDI_UpdateEDCAParamsRspCb    wdiUpdateEDCAParamsRspCb,
  void*                        pUserData
);



/* 
                                                                       
                                                                
                                                                
                                                             
                                                              
                         

                                                                
                                       

                                        

                                                                
                                          
  
                                                                
                                                     
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_AddBASessionReq
(
  WDI_AddBASessionReqParamsType* pwdiAddBASessionReqParams,
  WDI_AddBASessionRspCb          wdiAddBASessionRspCb,
  void*                          pUserData
);


/* 
                                                                
                                                             
                                                            
                                                               
                                                   

                                                                
                                       

                                    

                                                                
                                          
  
                                                                
                                                     
  
                                                         
                 
  
                  
                                    
*/
WDI_Status 
WDI_DelBAReq
(
  WDI_DelBAReqParamsType* pwdiDelBAReqParams,
  WDI_DelBARspCb          wdiDelBARspCb,
  void*                   pUserData
);

/* 
                                                                             
                                                                 
                                                    
                                                                
                                                   

                                                                
                                       

                                                 

                                                                                
                                          
  
                                                                              
                                                                   
  
                                                         
                 
  
                  
                                    
*/

WDI_Status 
WDI_UpdateBeaconParamsReq
(
  WDI_UpdateBeaconParamsType *   pwdiUpdateBeaconParams,
  WDI_UpdateBeaconParamsRspCb    wdiUpdateBeaconParamsRspCb,
  void*                          pUserData
);


/* 
                                                                           
                                                                               
                                                    
                                                               
                                                   

                                                                
                                       

                                               

                                                                              
                                          
  
                                                                            
                                                                 
  
                                                         
                 
  
                  
                                    
*/

WDI_Status 
WDI_SendBeaconParamsReq
(
  WDI_SendBeaconParamsType*    pwdiSendBeaconParams,
  WDI_SendBeaconParamsRspCb    wdiSendBeaconParamsRspCb,
  void*                        pUserData
);


/* 
                                                              
                                                                
                                 
                                                    
                                                            
                                                         

                                                                
                                       


                                                                  
                                                       
  
                                                               
                                                             
                       
  
                                                         
                 
  
                  
                                    
*/

WDI_Status 
WDI_UpdateProbeRspTemplateReq
(
  WDI_UpdateProbeRspTemplateParamsType*    pwdiUpdateProbeRspParams,
  WDI_UpdateProbeRspTemplateRspCb          wdiSendBeaconParamsRspCb,
  void*                                  pUserData
);

#ifdef WLAN_FEATURE_P2P
/* 
                                                   
                                                 
                                                    
                                                            
                                                         

                                                                
                                       


                                                                  
                                                       
  
                                                               
                                                             
                       
  
                                                         
                 
  
                  
                                    
*/
WDI_Status
WDI_SetP2PGONOAReq
(
  WDI_SetP2PGONOAReqParamsType*    pwdiP2PGONOAReqParams,
  WDI_SetP2PGONOAReqParamsRspCb    wdiP2PGONOAReqParamsRspCb,
  void*                            pUserData
);
#endif


/*                                                                         
 
                                           
 
                                                                          */

/* 
                                                               
                                                             
                                                               
                                                              
                                                             

                                                                
                                       

                                 

                                                           
                                                       
  
                                                         
                                                             
                       
  
                                                         
                 
  
               
                                      
*/ 
WDI_Status 
WDI_SetPwrSaveCfgReq
(
  WDI_UpdateCfgReqParamsType*   pwdiPowerSaveCfg,
  WDI_SetPwrSaveCfgCb     wdiSetPwrSaveCfgCb,
  void*                   pUserData
);

/* 
                                                              
                                                             
                                                               
                                                                
                            

                                                                
                                       

  
                                                         
                                                              
              
  
                                                         
                 
  
               
                                    
*/
WDI_Status 
WDI_EnterImpsReq
(
   WDI_EnterImpsRspCb  wdiEnterImpsRspCb,
   void*                   pUserData
);

/* 
                                                             
                                                               
                                                              
                                                                
                            

                                                                
                                       

 

                                                                 
                                                           
  
                                                         
                 
  
               
                                    
*/
WDI_Status 
WDI_ExitImpsReq
(
   WDI_ExitImpsRspCb  wdiExitImpsRspCb,
   void*                   pUserData
);

/* 
                                                              
                                                             
                                                              
                                                        
                                              

                                                                
                                       

                                        

                                                             
                                                       
  
                                                        
                                                              
              
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_EnterBmpsReq
(
   WDI_EnterBmpsReqParamsType *pwdiEnterBmpsReqParams,
   WDI_EnterBmpsRspCb  wdiEnterBmpsRspCb,
   void*                   pUserData
);

/* 
                                                             
                                                               
                                                              
                                                       
                                              

                                                                
                                       

                                        

                                                           
                                                       
  
                                                                
                                                           
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_ExitBmpsReq
(
   WDI_ExitBmpsReqParamsType *pwdiExitBmpsReqParams,
   WDI_ExitBmpsRspCb  wdiExitBmpsRspCb,
   void*                   pUserData
);

/* 
                                                               
                                                              
                                                              
                                                         
                                              

                                                                
                                       

                                        
                                               
  
                                                               
                                                       
  
                                                         
                                                               
              
  
                                                         
                 
  
                                               
                                    
*/
WDI_Status 
WDI_EnterUapsdReq
(
   WDI_EnterUapsdReqParamsType *pwdiEnterUapsdReqParams,
   WDI_EnterUapsdRspCb  wdiEnterUapsdRspCb,
   void*                   pUserData
);

/* 
                                                              
                                                                
                                                              
                                                             
                                

                                                                
                                       

                                        

                                                         
                                                              
              
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_ExitUapsdReq
(
   WDI_ExitUapsdRspCb  wdiExitUapsdRspCb,
   void*                   pUserData
);

/* 
                                                               
                                                         
                                                                
                                                                
                                                             
                                                             

                                                                
                                       

                                        

                                                       
                                                          
  
                                                             
                                                              
                       
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_UpdateUapsdParamsReq
(
   WDI_UpdateUapsdReqParamsType *pwdiUpdateUapsdReqParams,
   WDI_UpdateUapsdParamsCb  wdiUpdateUapsdParamsCb,
   void*                   pUserData
);

/* 
                                                              
                                                                
                                                          
                                                                
                                                          
                                                             

                                                                
                                       

                                        

                                                           
                                          
  
                                                            
                                                                
                  
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_SetUapsdAcParamsReq
(
  WDI_SetUapsdAcParamsReqParamsType*      pwdiPowerSaveCfg,
  WDI_SetUapsdAcParamsCb  wdiSetUapsdAcParamsCb,
  void*                   pUserData
);

/* 
                                                                
                                                                
                                                                       
                                                              
                                  

                                                                
                                       

  
                                                 
                                                       
                               
  
                                                              
                                                               
                       
  
                                                         
                 
  
                                    
*/
WDI_Status 
WDI_ConfigureRxpFilterReq
(
   WDI_ConfigureRxpFilterReqParamsType *pwdiConfigureRxpFilterReqParams,
   WDI_ConfigureRxpFilterCb             wdiConfigureRxpFilterCb,
   void*                                pUserData
);

/* 
                                                                
                                                            
                                                            
                                                   
                              

                                                                
                                       

  
                                              
                                                       
                               
  
                                                        
                                                            
                       
  
                                                         
                 
  
                                    
*/
WDI_Status 
WDI_SetBeaconFilterReq
(
   WDI_BeaconFilterReqParamsType   *pwdiBeaconFilterReqParams,
   WDI_SetBeaconFilterCb            wdiBeaconFilterCb,
   void*                            pUserData
);

/* 
                                                                
                                                           
                                                               
                                                             
                                             

                                                                
                                       

  
                                              
                                                       
                               
  
                                                        
                                                               
                       
  
                                                         
                 
  
                                    
*/
WDI_Status 
WDI_RemBeaconFilterReq
(
   WDI_RemBeaconFilterReqParamsType *pwdiBeaconFilterReqParams,
   WDI_RemBeaconFilterCb             wdiBeaconFilterCb,
   void*                             pUserData
);

/* 
                                                               
                                                    
                                                            
                                                               
                                                    
                                              

                                                                
                                       

                                        

                                                           
                                          
  
                                                            
                                                                
                  
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_SetRSSIThresholdsReq
(
  WDI_SetRSSIThresholdsReqParamsType*      pwdiRSSIThresholdsParams,
  WDI_SetRSSIThresholdsCb                  wdiSetRSSIThresholdsCb,
  void*                                    pUserData
);

/* 
                                                             
                                                            
                                                            
                                                            
                                                      
                                                         

                                                                
                                       

                                        

                                                             
                                             
  
                                                                
                                                       
              
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_HostOffloadReq
(
  WDI_HostOffloadReqParamsType*      pwdiHostOffloadParams,
  WDI_HostOffloadCb                  wdiHostOffloadCb,
  void*                              pUserData
);

/* 
                                                           
                                                                          
                                                                         
                                                            
                                                    
                                                         

                                                                
                                       

                                        

                                                         
                                             
  
                                                              
                                                     
              
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_KeepAliveReq
(
  WDI_KeepAliveReqParamsType*        pwdiKeepAliveParams,
  WDI_KeepAliveCb                    wdiKeepAliveCb,
  void*                              pUserData
);

/* 
                                                               
                                                                
                                                           
                                                              
                                                             
                                                         

                                                                
                                       

                                        

                                                        
                                                       
  
                                                         
                                                              
                       
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_WowlAddBcPtrnReq
(
  WDI_WowlAddBcPtrnReqParamsType*    pwdiWowlAddBcPtrnParams,
  WDI_WowlAddBcPtrnCb                wdiWowlAddBcPtrnCb,
  void*                              pUserData
);

/* 
                                                               
                                                            
                                                             
                                                         
                                              

                                                                
                                       

                                            

                                                        
                                                       
  
                                                         
                                                              
                       
  
                                                         
                 
  
                          
                                    
*/
WDI_Status 
WDI_WowlDelBcPtrnReq
(
  WDI_WowlDelBcPtrnReqParamsType*    pwdiWowlDelBcPtrnParams,
  WDI_WowlDelBcPtrnCb                wdiWowlDelBcPtrnCb,
  void*                              pUserData
);

/* 
                                                           
                                                             
                                                              
                                                            
                                                              
                         

                                                                
                                       

                                        

                                                       
                                                       
  
                                                        
                                                              
              
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_WowlEnterReq
(
  WDI_WowlEnterReqParamsType*    pwdiWowlEnterParams,
  WDI_WowlEnterReqCb             wdiWowlEnterCb,
  void*                          pUserData
);

/* 
                                                          
                                                               
                                                               
                                                               
                

                                                                
                                       

                                        

                                                     
                                                       
  
                                                                
                                                           
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_WowlExitReq
(
  WDI_WowlExitReqCb              wdiWowlExitCb,
  void*                          pUserData
);

/* 
                                                               
                                                             
                                                              
                                                         
                                                              
                              

                                                                
                                       

  
                                                      
                                                               
                                      
  
                                                              
                                                                
                                          
  
                                                         
                 
  
                                    
*/
WDI_Status 
WDI_ConfigureAppsCpuWakeupStateReq
(
   WDI_ConfigureAppsCpuWakeupStateReqParamsType *pwdiConfigureAppsCpuWakeupStateReqParams,
   WDI_ConfigureAppsCpuWakeupStateCb             wdiConfigureAppsCpuWakeupStateCb,
   void*                                         pUserData
);
/* 
                                                               
                                                               
                                                              
                                                                
                                

                                                                
                                       

  
                                                         
                                                       
  
                                                               
                                                          
  
                                                         
                 
 
                                    
*/
WDI_Status 
WDI_FlushAcReq
(
  WDI_FlushAcReqParamsType* pwdiFlushAcReqParams,
  WDI_FlushAcRspCb          wdiFlushAcRspCb,
  void*                     pUserData
);

/* 
                                                            
                                                                
                                                               
                                                              
                                                          
                                              

                                                                
                                       

  
                                                               
                                                       
  
                                                         
                                                                
              
  
                                                         
                 
 
                                    
*/
WDI_Status 
WDI_BtAmpEventReq
(
  WDI_BtAmpEventParamsType* pwdiBtAmpEventReqParams,
  WDI_BtAmpEventRspCb       wdiBtAmpEventRspCb,
  void*                     pUserData
);

#ifdef FEATURE_OEM_DATA_SUPPORT
/* 
                                                                 
                                                                  
                                                              
                                                                
                                              

                                                                
                                       

  
                                                             
                                                       
  
                                                           
                                                      
              
  
                                                         
                 
 
                                    
*/
WDI_Status 
WDI_StartOemDataReq
(
  WDI_oemDataReqParamsType*       pWdiOemDataReqParams,
  WDI_oemDataRspCb                wdiOemDataRspCb,
  void*                           pUserData
);
#endif

/*                                                                         
 
                                         
 
                                                                          */
/* 
                                                                
                                                               
                                                            
                                                          
                                              

                                                                
                                       

                                 

                                                          
                                                       
  
                                                                
                                                           
  
                                                         
                 
  
               
                                    
*/
WDI_Status 
WDI_SwitchChReq
(
  WDI_SwitchChReqParamsType* pwdiSwitchChReqParams,
  WDI_SwitchChRspCb          wdiSwitchChRspCb,
  void*                      pUserData
);



/* 
                                                           
                                                             
                                                            
                                                               
                                

                                                                
                                       

                                 

                                                            
                                                       
  
                                                        
                                                              
              
  
                                                         
                 
  
               
                                    
*/
WDI_Status 
WDI_ConfigSTAReq
(
  WDI_ConfigSTAReqParamsType* pwdiConfigSTAReqParams,
  WDI_ConfigSTARspCb          wdiConfigSTARspCb,
  void*                       pUserData
);

/* 
                                                              
                                                              
                                                              
                                                       
                                              

                                                                
                                       

                                   

                                                                
                                                          
  
                                                           
                                                              
                  
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_SetLinkStateReq
(
  WDI_SetLinkReqParamsType* pwdiSetLinkStateReqParams,
  WDI_SetLinkStateRspCb     wdiSetLinkStateRspCb,
  void*                     pUserData
);


/* 
                                                                
                                                              
                                                              
                                                              
                                   

                                                                
                                       

                                 

                                                             
                                                       
  
                                                                
                                                           
  
                                                         
                 
  
               
                                    
*/
WDI_Status 
WDI_GetStatsReq
(
  WDI_GetStatsReqParamsType* pwdiGetStatsReqParams,
  WDI_GetStatsRspCb          wdiGetStatsRspCb,
  void*                      pUserData
);


/* 
                                                                
                                                         
                                                                
                                                              
                                                   

                                                                
                                       

                                 

                                                            
                                                       
  
                                                         
                                                              
              
  
                                                         
                 
  
               
                                    
*/
WDI_Status 
WDI_UpdateCfgReq
(
  WDI_UpdateCfgReqParamsType* pwdiUpdateCfgReqParams,
  WDI_UpdateCfgRspCb          wdiUpdateCfgsRspCb,
  void*                       pUserData
);

/* 
                                                                           
                  

                                                                             
                        
   
                                                                   
                                                        
 
                                                        
                
  
                      
                                    
*/
WDI_Status 
WDI_NvDownloadReq
(
  WDI_NvDownloadReqParamsType* pwdiNvDownloadReqParams,
  WDI_NvDownloadRspCb      wdiNvDownloadRspCb,
   void*      pUserData
);
/* 
                                                                
                                                                
                                                                
                                                             
                                                              
                         

                                                                
                                       

                                        

                                                                
                                          
  
                                                                
                                                     
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_AddBAReq
(
  WDI_AddBAReqParamsType* pwdiAddBAReqParams,
  WDI_AddBARspCb          wdiAddBARspCb,
  void*                   pUserData
);

/* 
                                                                    
                                                                
                                                                
                                                             
                                                              
                         

                                                                
                                       

                                        

                                                                
                                          
  
                                                                
                                                     
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_TriggerBAReq
(
  WDI_TriggerBAReqParamsType* pwdiTriggerBAReqParams,
  WDI_TriggerBARspCb          wdiTriggerBARspCb,
  void*                       pUserData
);


/* 
                                                              
                                                  

                                        

                           
  
                      
                                    
*/
wpt_boolean WDI_IsHwFrameTxTranslationCapable
(
  wpt_uint8 uSTAIdx
);

#ifdef WLAN_FEATURE_VOWIFI_11R
/* 
                                                                    
                                                                    
                                                              
                                                            
                                                              
                                                                         
                                

                                                                
                                       

                                        

                                                                    
                                                   
  
                                                                    
                                                     
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_AggrAddTSReq
(
  WDI_AggrAddTSReqParamsType* pwdiAddTsReqParams,
  WDI_AggrAddTsRspCb          wdiAggrAddTsRspCb,
  void*                   pUserData
);
#endif /*                         */
/* 
                                                       
                                      

 
                                                          
  
     
                                    
*/

WDI_Status WDI_StubRunTest
(
   wpt_uint8   ucTestNo
);

#ifdef ANI_MANF_DIAG
/* 
                             
                                       
 
                                                         
                                           
                                                                  

                                    
*/
WDI_Status WDI_FTMCommandReq
(
  WDI_FTMCommandReqType *ftmCommandReq,
  WDI_FTMCommandRspCb    ftmCommandRspCb,
  void                  *pUserData
);
#endif /*               */

/* 
                                         

                                                                
                                       


                                             
                                          
  
                                                                    
                                               
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_HostResumeReq
(
  WDI_ResumeParamsType*            pwdiResumeReqParams,
  WDI_HostResumeEventRspCb         wdiResumeReqRspCb,
  void*                            pUserData
);

/* 
                                                                         
                                       
        
                                                      
                                                           
     
                                    
*/

wpt_uint32 WDI_GetAvailableResCount
(
  void            *pContext,
  WDI_ResPoolType wdiResPool
);

/* 
                                                    
                                                                 
                                                                
                                      


                                                            
                                                       

                                                         
                

     
                                    
*/
WDI_Status
WDI_AddSTASelfReq
(
  WDI_AddSTASelfReqParamsType*    pwdiAddSTASelfReqParams,
  WDI_AddSTASelfParamsRspCb       wdiAddSTASelfReqParamsRspCb,
  void*                           pUserData
);


/* 
                                          

                                   
  
                                                          
                                                                 
              
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_DelSTASelfReq
(
  WDI_DelSTASelfReqParamsType*    pwdiDelStaSelfParams,
  WDI_DelSTASelfRspCb             wdiDelStaSelfRspCb,
  void*                           pUserData
);

/* 
                           
  
                                                            
                   
  
                             
 
      
  
                              
*/
WDI_Status 
WDI_HostSuspendInd
(
  WDI_SuspendParamsType*    pwdiSuspendIndParams
);

#ifdef FEATURE_WLAN_SCAN_PNO
/* 
                                   

                                                       
                                             
  
                                                            
                                                  
              
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_SetPreferredNetworkReq
(
  WDI_PNOScanReqParamsType* pwdiPNOScanReqParams,
  WDI_PNOScanCb             wdiPNOScanCb,
  void*                      pUserData
);

/* 
                            

                                                        
                                                       
  
                                                               
                                                          
              
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_SetRssiFilterReq
(
  WDI_SetRssiFilterReqParamsType* pwdiRssiFilterReqParams,
  WDI_RssiFilterCb                wdiRssiFilterCb,
  void*                           pUserData
);

/* 
                            

                                                                          
                                             
  
                                                                     
                                                  
              
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_UpdateScanParamsReq
(
  WDI_UpdateScanParamsInfoType* pwdiUpdateScanParamsInfoType,
  WDI_UpdateScanParamsCb        wdiUpdateScanParamsCb,
  void*                         pUserData
);
#endif //                      

/* 
                                                                  
                                                         
                                                        
                                                                 
                                                         

                                                                
                                       

                                                                           
                                                       
  
                                                            
                                                                             
                       
  
                                                         
                 
  
                                    
*/
WDI_Status 
WDI_SetTxPerTrackingReq
(
  WDI_SetTxPerTrackingReqParamsType*      pwdiSetTxPerTrackingReqParams,
  WDI_SetTxPerTrackingRspCb               pwdiSetTxPerTrackingRspCb,
  void*                                   pUserData
);

/* 
                         
                                                                          
                             

                                                            
  
                                     
  
                                                       
                 
  
                                    
*/
WDI_Status
WDI_SetTmLevelReq
(
   WDI_SetTmLevelReqType        *pwdiSetTmLevelReq,
   WDI_SetTmLevelCb              pwdiSetTmLevelRspCb,
   void                         *usrData  
);

#ifdef WLAN_FEATURE_PACKET_FILTERING
/* 
                                

                                                              
                                                 
  
                                                               
                                                             
                                
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_8023MulticastListReq
(
  WDI_RcvFltPktSetMcListReqParamsType*  pwdiRcvFltPktSetMcListReqInfo,
  WDI_8023MulticastListCb               wdi8023MulticastListCallback,
  void*                                 pUserData
);

/* 
                                     

                                                              
                                         
  
                                                          
                                                           
                                          
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_ReceiveFilterSetFilterReq
(
  WDI_SetRcvPktFilterReqParamsType* pwdiSetRcvPktFilterReqInfo,
  WDI_ReceiveFilterSetFilterCb      wdiReceiveFilterSetFilterReqCallback,
  void*                             pUserData
);

/* 
                                 

                                                             
                                         
  
                                                                
                                                              
                                
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_FilterMatchCountReq
(
  WDI_RcvFltPktMatchCntReqParamsType* pwdiRcvFltPktMatchCntReqInfo,
  WDI_FilterMatchCountCb              wdiFilterMatchCountCallback,
  void*                               pUserData
);

/* 
                                       

                                                       
                                                       
  
                                                         
                                                     
                                          
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_ReceiveFilterClearFilterReq
(
  WDI_RcvFltPktClearReqParamsType*  pwdiRcvFltPktClearReqInfo,
  WDI_ReceiveFilterClearFilterCb    wdiReceiveFilterClearFilterCallback,
  void*                             pUserData
);
#endif //                              

/* 
                         
                                   
 
                                                      
                                                               
                                                          
                                     
  
     
                                    
*/
WDI_Status WDI_HALDumpCmdReq(
  WDI_HALDumpCmdReqParamsType *halDumpCmdReqParams,
  WDI_HALDumpCmdRspCb    halDumpCmdRspCb,
  void                  *pUserData
);


/* 
                             

                                                          
                                                       
  
                                                                
                                                           
              
  
                                                         
                 
  
                                    
*/
WDI_Status 
WDI_SetPowerParamsReq
(
  WDI_SetPowerParamsReqParamsType* pwdiPowerParamsReqParams,
  WDI_SetPowerParamsCb             wdiPowerParamsCb,
  void*                            pUserData
);

#ifdef WLAN_FEATURE_GTK_OFFLOAD
/* 
                                                            
                                                                
                                                              
                                                         
                                              

                                                                
                                       

                                        

                                                           
                                             
  
                                                               
                                                             
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_GTKOffloadReq
(
  WDI_GtkOffloadReqMsg*      pwdiGtkOffloadReqMsg,
  WDI_GtkOffloadCb           wdiGtkOffloadCb,
  void*                      pUserData
);

/* 
                                                               
                                                                 
                                                              
                                                                  
                                              

                                                                
                                       

                                        

                                                     
                                                               
                                        
  
                                                               
                                                                 
                
  
                                                         
                 
  
                      
                                    
*/
WDI_Status 
WDI_GTKOffloadGetInfoReq
(
  WDI_GtkOffloadGetInfoReqMsg*  pwdiGtkOffloadGetInfoReqMsg,
  WDI_GtkOffloadGetInfoCb       wdiGtkOffloadGetInfoCb,
  void*                          pUserData
);
#endif //                         

/* 
                                  
                                                      
                                                                
                                                                     
 
        
  
                                                                     
                                                                            
                                                       
  
                                                         
                 
  
     
                                    
*/
WDI_Status
WDI_featureCapsExchangeReq
(
  WDI_featureCapsExchangeCb     wdiFeatureCapsExchangeCb,
  void*                         pUserData
);

/* 
                               
                                                                              
                                                                                
                                                                                 
                                                                                
                                                  
 
        
  
                                                                                                   

     
         
                                                   
                                                                 
*/
wpt_uint8 WDI_getHostWlanFeatCaps(wpt_uint8 feat_enum_value);

/* 
                             
                                                                              
                                                                              
                                                                                 
                                                                                
                                                  
 
        
  
                                                                                 
                          

     
         
                                                 
                                                               
*/
wpt_uint8 WDI_getFwWlanFeatCaps(wpt_uint8 feat_enum_value);

/* 
                                                                         
                    
        
                                                     
     
             
*/

void WDI_GetWcnssCompiledApiVersion
(
  WDI_WlanVersionType     *pWcnssApiVersion
);




/* 
                                   
                                             
                                                    
                                                            
        
                                                      
                                                        
                                                                         
                                                             
     
             
*/
void WDI_TransportChannelDebug
(
   wpt_boolean  displaySnapshot,
   wpt_boolean  toggleStallDetect
);

#ifdef __cplusplus
 }
#endif 


#endif /*                        */
