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

/*
                                                        
                                                         
                                    
                                  
                          
            
                                                         
                                                                       
  
 */
#include "palTypes.h"
#include "wniApi.h"
#ifdef FEATURE_WLAN_NON_INTEGRATED_SOC
#include "halDataStruct.h"
#include "halCommonApi.h"
#elif defined FEATURE_WLAN_INTEGRATED_SOC
#include "wlan_qct_wdi_ds.h"
#include "wlan_qct_pal_packet.h"
#include "wlan_qct_wda.h"
#endif

#ifdef ANI_PRODUCT_TYPE_AP
#include "wniCfgAp.h"
#else
#include "wniCfgSta.h"
#endif
#include "cfgApi.h"
#include "sirCommon.h"
#include "utilsApi.h"
#include "limTypes.h"
#include "limUtils.h"
#include "limAssocUtils.h"
#include "limPropExtsUtils.h"

#include "limAdmitControl.h"
#include "pmmApi.h"
#include "limIbssPeerMgmt.h"
#include "schApi.h"
#include "limSession.h"

#if defined WLAN_FEATURE_VOWIFI
#include "rrmApi.h"
#endif
#if defined FEATURE_WLAN_CCX
#include "ccxApi.h"
#endif

#if defined WLAN_FEATURE_VOWIFI_11R
#include "limFT.h"
#endif

#ifdef WMM_APSD
#include "wmmApsd.h"
#endif

#ifdef VOSS_ENABLED
#include "vos_types.h"
#include "vos_packet.h"
#include "vos_memory.h"
#endif

void limLogSessionStates(tpAniSirGlobal pMac);

/*                                                               
                  
                                                                                           
                            
                             
                                     
            
                                                               */

tANI_U8 static
defMsgDecision(tpAniSirGlobal pMac, tpSirMsgQ  limMsg)
{


/*                                  */
  if(pMac->lim.gLimSmeState == eLIM_SME_OFFLINE_STATE)
  {
      //                               
      if (limDeferMsg(pMac, limMsg) != TX_SUCCESS)
      {
          PELOGE(limLog(pMac, LOGE, FL("Unable to Defer message(0x%X) %s limSmeState %d (prev sme state %d) sysRole %d mlm state %d (prev mlm state %d)\n"),
                   limMsg->type, limMsgStr(limMsg->type), pMac->lim.gLimSmeState,  pMac->lim.gLimPrevSmeState,
                   pMac->lim.gLimSystemRole,  pMac->lim.gLimMlmState,  pMac->lim.gLimPrevMlmState);)
          limLogSessionStates(pMac);
          limHandleDeferMsgError(pMac, limMsg);
      }
      return true;
  }

  //                                                                         
  if((!limIsSystemInScanState(pMac)) && (true != GET_LIM_PROCESS_DEFD_MESGS(pMac)) &&
      !pMac->lim.gLimSystemInScanLearnMode)
  {
      if((limMsg->type != WDA_ADD_BSS_RSP) &&
        (limMsg->type != WDA_DELETE_BSS_RSP) &&
        (limMsg->type != WDA_ADD_STA_RSP) &&
        (limMsg->type != WDA_ADD_STA_SELF_RSP) &&
        (limMsg->type != WDA_DEL_STA_SELF_RSP) &&
        (limMsg->type != WDA_DELETE_STA_RSP)&&
        (limMsg->type != WDA_SET_BSSKEY_RSP)&&
        (limMsg->type != WDA_SET_STAKEY_RSP)&&
        (limMsg->type != WDA_SET_STA_BCASTKEY_RSP) &&
        (limMsg->type != eWNI_SME_START_REQ) &&
        (limMsg->type != WDA_AGGR_QOS_RSP) &&
        (limMsg->type != WDA_REMOVE_BSSKEY_RSP) &&
        (limMsg->type != WDA_REMOVE_STAKEY_RSP) &&
        (limMsg->type != WDA_SET_MIMOPS_RSP)&&
        (limMsg->type != WDA_ADDBA_RSP) &&
        (limMsg->type != WDA_ENTER_BMPS_RSP) &&
        (limMsg->type != WDA_EXIT_BMPS_RSP) &&
        (limMsg->type != WDA_ENTER_IMPS_RSP) &&
        (limMsg->type != WDA_EXIT_IMPS_RSP) &&
        (limMsg->type != WDA_ENTER_UAPSD_RSP) &&
        (limMsg->type != WDA_EXIT_UAPSD_RSP) &&
        (limMsg->type != WDA_WOWL_ENTER_RSP) &&
        (limMsg->type != WDA_WOWL_EXIT_RSP) &&
        (limMsg->type != WDA_SWITCH_CHANNEL_RSP) &&
#ifdef WLAN_FEATURE_P2P 
        (limMsg->type != WDA_P2P_NOA_ATTR_IND) &&
#endif
#ifdef FEATURE_OEM_DATA_SUPPORT
        (limMsg->type != WDA_START_OEM_DATA_RSP) &&
#endif
        (limMsg->type != WDA_ADD_TS_RSP))
    {
        PELOG1(limLog(pMac, LOG1, FL("Defer the current message %s , gLimProcessDefdMsgs is false and system is not in scan/learn mode\n"),
               limMsgStr(limMsg->type));)

        //                               
        if (limDeferMsg(pMac, limMsg) != TX_SUCCESS)
        {
            PELOGE(limLog(pMac, LOGE, FL("Unable to Defer message(0x%X) %s limSmeState %d (prev sme state %d) sysRole %d mlm state %d (prev mlm state %d)\n"),
                   limMsg->type, limMsgStr(limMsg->type), pMac->lim.gLimSmeState,  pMac->lim.gLimPrevSmeState,
                   pMac->lim.gLimSystemRole,  pMac->lim.gLimMlmState,  pMac->lim.gLimPrevMlmState);)
            limLogSessionStates(pMac);
            limHandleDeferMsgError(pMac, limMsg);

        }
        return true;
    }
  }
  return false;
}

/*
                        
                                             
                                                                                    
                                                                                                                         
                                                                                    
                                                                                                                           
                                                                                    
                           
                                                                         
                
*/
static void
__limHandleBeacon(tpAniSirGlobal pMac, tpSirMsgQ pMsg, tpPESession psessionEntry)
{
    /*                                 */
    tANI_U8 *pRxPacketInfo;
    limGetBDfromRxPacket(pMac, pMsg->bodyptr, (tANI_U32 **)&pRxPacketInfo);

    //                                                                       
    //                                             

    if(psessionEntry == NULL)
    {
        schBeaconProcess(pMac, pRxPacketInfo, NULL);
    }
    else if( (psessionEntry->limSmeState == eLIM_SME_LINK_EST_STATE) ||
                (psessionEntry->limSmeState == eLIM_SME_NORMAL_STATE))
    {
        schBeaconProcess(pMac, pRxPacketInfo, psessionEntry);
    }
     else
        limProcessBeaconFrame(pMac, pRxPacketInfo, psessionEntry);

        return;
}


//                  
void limProcessNormalHddMsg(tpAniSirGlobal pMac, tSirMsgQ *pLimMsg, tANI_U8 fRspReqd);

/* 
                         
  
           
                                                             
                                                        
           
  
        
  
              
     
  
       
     
  
                                                 
               
 */

void
limProcessMessageQueue(tpAniSirGlobal pMac)
{
    tSirMsgQ  limMsg = { 0, 0, 0 };

    if(pMac->gDriverType == eDRIVER_TYPE_MFG)
    {
        return;
    }

#if defined(ANI_OS_TYPE_RTAI_LINUX)
    ULONG param;
    while(get_timer_event(LIM_TIMER_EXPIRY_LIST,&param))
    {
        limMsg.type = (tANI_U16) param;
        limMsg.bodyval = 0;
        limMsg.bodyptr = NULL;
        limMessageProcessor(pMac, &limMsg);
    }
#endif

    if (tx_queue_receive( &pMac->sys.gSirLimMsgQ, (void *) &limMsg, TX_WAIT_FOREVER)
            == TX_SUCCESS)
    {
        PELOG3(limLog(pMac, LOG3, FL("LIM Received message %s\n"), limMsgStr(limMsg.type));)
        limPrintMsgInfo(pMac, LOG3, &limMsg);
        limMessageProcessor(pMac, &limMsg);
    } //                      
    
} /*                                  */



/* 
                
  
           
                                                         
                    
  
        
     
  
              
     
  
       
     
  
                                                 
                                                                   
               
 */

tANI_U32
limDeferMsg(tpAniSirGlobal pMac, tSirMsgQ *pMsg)
{
    tANI_U32 retCode = TX_SUCCESS;
#if defined(ANI_OS_TYPE_LINUX) || defined(ANI_OS_TYPE_OSX)
   PELOG3(limLog(pMac, LOG3, FL("Deferring message %X in Learn mode\n"),
           pMsg->type);
    limPrintMsgName(pMac, LOG3, pMsg->type);)
    retCode = tx_queue_send(&pMac->sys.gSirLimDeferredMsgQ,
                            pMsg,
                            TX_NO_WAIT);
    if (retCode == TX_SUCCESS)
        pMac->lim.gLimNumDeferredMsgs++;
#else

        retCode = limWriteDeferredMsgQ(pMac, pMsg);

#endif
    if(retCode == TX_SUCCESS)
        {
            MTRACE(macTraceMsgRx(pMac, NO_SESSION, LIM_TRACE_MAKE_RXMSG(pMsg->type, LIM_MSG_DEFERRED));)
        }
    else
        {
            MTRACE(macTraceMsgRx(pMac, NO_SESSION, LIM_TRACE_MAKE_RXMSG(pMsg->type, LIM_MSG_DROPPED));)
        }


    return retCode;
} /*                       */



/* 
                               
  
           
                                                   
                                 
  
        
     
  
              
     
  
       
     
  
                                                    
                                     
                                                              
                                                                   
               
 */

static void
limHandleFramesInScanState(tpAniSirGlobal pMac, tpSirMsgQ limMsg, tANI_U8 *pRxPacketInfo, tANI_U8 *deferMsg, tpPESession psessionEntry)
{
    tSirMacFrameCtl  fc;
    tpSirMacMgmtHdr  pHdr;
#if (WNI_POLARIS_FW_PACKAGE == ADVANCED) && defined(ANI_PRODUCT_TYPE_AP)
    tANI_U32         ignore = 0;
    tSirMacAddr      bssIdRcv;
#endif

    *deferMsg = false;
    pHdr = WDA_GET_RX_MAC_HEADER(pRxPacketInfo);
    fc = pHdr->fc;
    limLog( pMac, LOG2, FL("ProtVersion %d, Type %d, Subtype %d\n"),
            fc.protVer, fc.type, fc.subType );

#if (WNI_POLARIS_FW_PACKAGE == ADVANCED) && defined(ANI_PRODUCT_TYPE_AP)
    //                              
    pMac->lim.numLearn++;

    //                                      
    limGetBssidFromBD(pMac, (tpHalBufDesc) pRxPacketInfo, bssIdRcv, &ignore);

    if ((psessionEntry->limSystemRole == eLIM_AP_ROLE) &&
        palEqualMemory( pMac->hHdd,bssIdRcv, psessionEntry->bssId, sizeof(tSirMacAddr)))
    {
        /* 
                                                                
                                                         
                                                        
                                                             
                   */
        if ((fc.subType == SIR_MAC_MGMT_DISASSOC) ||
            (fc.subType == SIR_MAC_MGMT_DEAUTH))
        {
            if (limDeferMsg(pMac, limMsg) != TX_SUCCESS)
            {
                PELOGE(limLog(pMac, LOGE, FL("Unable to Defer message(0x%X) limSmeState %d (prev sme state %d) sysRole %d mlm state %d (prev mlm state %d)\n"),
                   limMsg->type, pMac->lim.gLimSmeState,  pMac->lim.gLimPrevSmeState,
                   pMac->lim.gLimSystemRole,  pMac->lim.gLimMlmState,  pMac->lim.gLimPrevMlmState);)
                limLogSessionStates(pMac);
                limPrintMsgName(pMac, LOGE, limMsg->type);
                limPktFree(pMac, HAL_TXRX_FRM_802_11_MGMT, NULL, limMsg->bodyptr);
            }
            return;
        }
        pMac->lim.numLearnIgnore++;
    }
    else
    {
        //                              
        if (fc.type == SIR_MAC_DATA_FRAME && psessionEntry->limSystemRole == eLIM_AP_ROLE)
        {
            /* 
                                             
                                                              
              */
            limCollectMeasurementData(pMac, pRxPacketInfo, NULL);
        }
        else if ((fc.type == SIR_MAC_MGMT_FRAME) && (fc.subType == SIR_MAC_MGMT_BEACON))
        {
            if (psessionEntry == NULL)
                limProcessBeaconFrameNoSession(pMac, pRxPacketInfo);
            else 
                limProcessBeaconFrame(pMac, pRxPacketInfo,psessionEntry);
        }
        else if ((fc.type == SIR_MAC_MGMT_FRAME) && (fc.subType == SIR_MAC_MGMT_PROBE_RSP))
        {
            if (psessionEntry == NULL)
                limProcessProbeRspFrameNoSession(pMac, pRxPacketInfo);
            else
                limProcessProbeRspFrame(pMac, pRxPacketInfo,psessionEntry);
        }
    }

#else
    //                                                                      
    if ((fc.type == SIR_MAC_MGMT_FRAME) && (fc.subType == SIR_MAC_MGMT_BEACON))
    {
        if (psessionEntry == NULL)
            limProcessBeaconFrameNoSession(pMac, pRxPacketInfo);
        else 
            limProcessBeaconFrame(pMac, pRxPacketInfo,psessionEntry);
    }
    else if ((fc.type == SIR_MAC_MGMT_FRAME) && (fc.subType == SIR_MAC_MGMT_PROBE_RSP))
    {
        if (psessionEntry == NULL)
            limProcessProbeRspFrameNoSession(pMac, pRxPacketInfo);
        else
            limProcessProbeRspFrame(pMac, pRxPacketInfo,psessionEntry);
    }
    else if ((fc.type == SIR_MAC_MGMT_FRAME) && (fc.subType == SIR_MAC_MGMT_PROBE_REQ))
    {
      limProcessProbeReqFrame_multiple_BSS(pMac, pRxPacketInfo, psessionEntry);
    }
#if defined WLAN_FEATURE_P2P
    else if ((fc.type == SIR_MAC_MGMT_FRAME) && (fc.subType == SIR_MAC_MGMT_ACTION))
    {
       limProcessActionFrameNoSession( pMac, pRxPacketInfo);
    }
#endif
    else
    {
        *deferMsg = true;
        return; 
    }
 
#endif
    limPktFree(pMac, HAL_TXRX_FRM_802_11_MGMT, pRxPacketInfo, (void *) limMsg->bodyptr);
    return;

} /*                                      */

/*                                                              
                                                          
                  
                                                       
                                                          
              
 
                                                                 */
static void limHandleUnknownA2IndexFrames(tpAniSirGlobal pMac, void *pRxPacketInfo,tpPESession psessionEntry)
{
#ifndef ANI_CHIPSET_VOLANS
    tpSirMacDataHdr3a pMacHdr;

    /*                                                           
                                                                  */
    if (pMac->lim.gLimDisassocFrameCredit > pMac->lim.gLimDisassocFrameThreshold)
        return;

    pMac->lim.gLimDisassocFrameCredit++;

    pMacHdr = WDA_GET_RX_MPDUHEADER3A(pRxPacketInfo);

    if (limIsGroupAddr(pMacHdr->addr2))
    {
        PELOG2(limLog(pMac, LOG2, FL("Ignoring A2 Invalid Packet received for MC/BC:\n"));
        limPrintMacAddr(pMac, pMacHdr->addr2, LOG2);)

        return;
    }

    if (((psessionEntry->limSystemRole == eLIM_AP_ROLE) || (psessionEntry->limSystemRole == eLIM_BT_AMP_AP_ROLE) )&&
        (psessionEntry->limMlmState == eLIM_MLM_BSS_STARTED_STATE))
    {
        switch (pMacHdr->fc.type)
        {
            case SIR_MAC_MGMT_FRAME:
                switch (pMacHdr->fc.subType)
                {
                    case SIR_MAC_MGMT_ACTION:
                        //                             
                        //                     
                        PELOG1(limLog(pMac, LOG1, FL("Send Disassoc Frame due to Invalid Addr2 packet"));
                        limPrintMacAddr(pMac, pMacHdr->addr2, LOG1);)
                        limSendDisassocMgmtFrame(pMac,
                           eSIR_MAC_CLASS3_FRAME_FROM_NON_ASSOC_STA_REASON, pMacHdr->addr2,psessionEntry);
                        break;

                    default:
                        break;

                }
                break;

            case SIR_MAC_CTRL_FRAME:
                switch (pMacHdr->fc.subType)
                {
                    case SIR_MAC_CTRL_PS_POLL:
                    case SIR_MAC_CTRL_BAR:
                        //                             
                        //                     
                        PELOG1(limLog(pMac, LOG1, FL("Send Disassoc Frame due to Invalid Addr2 packet"));
                        limPrintMacAddr(pMac, pMacHdr->addr2, LOG1);)
                        limSendDisassocMgmtFrame(pMac,
                           eSIR_MAC_CLASS3_FRAME_FROM_NON_ASSOC_STA_REASON, pMacHdr->addr2,psessionEntry);
                        break;

                    default:
                        break;
                }
                break;

            case SIR_MAC_DATA_FRAME:
                switch (pMacHdr->fc.subType)
                {
                    case SIR_MAC_DATA_NULL:
                    case SIR_MAC_DATA_QOS_NULL:
                        //                             
                        //                     
                        PELOG1(limLog(pMac, LOG1, FL("Send Disassoc Frame due to Invalid Addr2 packet"));
                        limPrintMacAddr(pMac, pMacHdr->addr2, LOG1);)
                        limSendDisassocMgmtFrame(pMac,
                           eSIR_MAC_CLASS3_FRAME_FROM_NON_ASSOC_STA_REASON, pMacHdr->addr2,psessionEntry);
                        break;

                    default:
                        //                               
                        //                     
                        PELOG1(limLog(pMac, LOG1, FL("Sending Deauth frame due to Invalid Addr2 packet"));
                        limPrintMacAddr(pMac, pMacHdr->addr2, LOG1);)
                        limSendDeauthMgmtFrame(pMac,
                           eSIR_MAC_CLASS3_FRAME_FROM_NON_ASSOC_STA_REASON, pMacHdr->addr2,psessionEntry);
                        break;
                }
                break;
        }
    }
#else
      /*                                                       
                                        
                                                                           */
       /*                                 */
       //                                
       //                                                                                                          
#if defined WLAN_FEATURE_P2P
    //                                    
    if( psessionEntry->limSystemRole == eLIM_P2P_DEVICE_ROLE )
        limProcessActionFrameNoSession(pMac, (tANI_U8 *) pRxPacketInfo);
#endif
#endif

    return;
}

#ifdef WLAN_FEATURE_P2P
/* 
                                 
  
           
                                                                            
                                                                       
  
        
  
              
  
       
  
                                                    
                                                                     
                                                                        
               
 */
static tANI_BOOLEAN
limCheckMgmtRegisteredFrames(tpAniSirGlobal pMac, tANI_U8 *pBd,
                                        tpPESession psessionEntry)
{
    tSirMacFrameCtl  fc;
    tpSirMacMgmtHdr  pHdr;
    tANI_U8          *pBody;
    tpLimMgmtFrameRegistration pLimMgmtRegistration = NULL, pNext = NULL;
    tANI_U16 frameType;
    tANI_U16 framelen;
    tANI_U8 type,subType;
    tANI_BOOLEAN match = VOS_FALSE;
    VOS_STATUS vosStatus;

    pHdr = WDA_GET_RX_MAC_HEADER(pBd);
    fc = pHdr->fc;
    frameType = (fc.type << 2 ) | (fc.subType << 4);
    pBody = WDA_GET_RX_MPDU_DATA(pBd);
    framelen = WDA_GET_RX_PAYLOAD_LEN(pBd);

    vos_list_peek_front(&pMac->lim.gLimMgmtFrameRegistratinQueue,
                        (vos_list_node_t**)&pLimMgmtRegistration);

    while(pLimMgmtRegistration != NULL)
    {
        type = (pLimMgmtRegistration->frameType >> 2) & 0x03;
        subType = (pLimMgmtRegistration->frameType >> 4) & 0x0f;
        if ( (type == SIR_MAC_MGMT_FRAME) && (fc.type == SIR_MAC_MGMT_FRAME)
              && (subType == SIR_MAC_MGMT_RESERVED15) )
        {
            limLog( pMac, LOG3, 
                FL("rcvd frame match with SIR_MAC_MGMT_RESERVED15\n"));
            match = VOS_TRUE;
            break;
        }

        if (pLimMgmtRegistration->frameType == frameType)
        { 
            if (pLimMgmtRegistration->matchLen > 0)
            {   
                if (pLimMgmtRegistration->matchLen <= framelen)
                {
                    if (palEqualMemory(pMac, pLimMgmtRegistration->matchData,
                                       pBody, pLimMgmtRegistration->matchLen))
                    {
                       /*              */   
                       match = VOS_TRUE;
                       break;
                    }
                } 
            }
            else
            {
                /*              */   
                match = VOS_TRUE;
                break;
            }
        }
             
        vosStatus = 
          vos_list_peek_next ( &pMac->lim.gLimMgmtFrameRegistratinQueue, 
                              (vos_list_node_t*) pLimMgmtRegistration, 
                              (vos_list_node_t**) &pNext );
        pLimMgmtRegistration = pNext;
        pNext = NULL;
    }
   
    if (match)
    {
        limLog( pMac, LOG1, 
                FL("rcvd frame match with registered frame params\n"));

        /*                      */
        limSendSmeMgmtFrameInd( pMac, pHdr->fc.subType, (tANI_U8*)pHdr, 
                     WDA_GET_RX_PAYLOAD_LEN(pBd) + sizeof(tSirMacMgmtHdr), 
                     pLimMgmtRegistration->sessionId,
                     WDA_GET_RX_CH(pBd), psessionEntry );
    
        if ( (type == SIR_MAC_MGMT_FRAME) && (fc.type == SIR_MAC_MGMT_FRAME)
              && (subType == SIR_MAC_MGMT_RESERVED15) )
        {
            //                                                              
            //                                                              
            match = VOS_FALSE;
        }
    }

    return match;
} /*                                         */
#endif /*                  */


/* 
                         
  
           
                                                   
                   
  
        
     
  
              
     
  
       
     
  
                                                 
                                                                   
               
 */

static void 
limHandle80211Frames(tpAniSirGlobal pMac, tpSirMsgQ limMsg, tANI_U8 *pDeferMsg)
{
    tANI_U8          *pRxPacketInfo = NULL;
    tSirMacFrameCtl  fc;
    tpSirMacMgmtHdr    pHdr=NULL;
    tpPESession         psessionEntry=NULL;
    tANI_U8             sessionId;
    tAniBool            isFrmFt = FALSE;
    tANI_U16            fcOffset = WLANHAL_RX_BD_HEADER_SIZE;

    *pDeferMsg= false;
    limGetBDfromRxPacket(pMac, limMsg->bodyptr, (tANI_U32 **)&pRxPacketInfo);

    pHdr = WDA_GET_RX_MAC_HEADER(pRxPacketInfo);
    isFrmFt = WDA_GET_RX_FT_DONE(pRxPacketInfo);
    fcOffset = (v_U8_t)WDA_GET_RX_MPDU_HEADER_OFFSET(pRxPacketInfo);
    fc = pHdr->fc;

    limLog( pMac, LOG4, FL("ProtVersion %d, Type %d, Subtype %d rateIndex=%d\n"),
            fc.protVer, fc.type, fc.subType, WDA_GET_RX_MAC_RATE_IDX(pRxPacketInfo));
   

#ifdef FEATURE_WLAN_CCX
    if (fc.type == SIR_MAC_DATA_FRAME && isFrmFt) 
    {
#if 0 //                     
        tpSirMacDot3Hdr pDataFrmHdr;

        pDataFrmHdr = (tpSirMacDot3Hdr)((tANI_U8 *)pBD+ WLANHAL_RX_BD_GET_MPDU_H_OFFSET(pBD));
        if((psessionEntry = peFindSessionByBssid(pMac,pDataFrmHdr->sa,&sessionId))== NULL)
        {
            limLog( pMac, LOGE, FL("Session not found for Frm type %d, subtype %d, SA: "), fc.type, fc.subType);
            limPrintMacAddr(pMac, pDataFrmHdr->sa, LOGE);
            limPktFree(pMac, HAL_TXRX_FRM_802_11_MGMT, pBD, limMsg->bodyptr);
            return;
        }

        if (!psessionEntry->isCCXconnection)
        {
            limLog( pMac, LOGE, FL("LIM received Type %d, Subtype %d in Non CCX connection\n"),
                    fc.type, fc.subType);
            limPktFree(pMac, HAL_TXRX_FRM_802_11_MGMT, pBD, limMsg->bodyptr);
            return;
        }
        limLog( pMac, LOGE, FL("Processing IAPP Frm from SA:"));
        limPrintMacAddr(pMac, pDataFrmHdr->sa, LOGE);
#else
        printk("%s: Need to port handling of IAPP frames to PRIMA for CCX\n", __func__);
#endif


    } else
#endif
    /*                          */
    if((psessionEntry = peFindSessionByBssid(pMac,pHdr->bssId,&sessionId))== NULL)
    {
#ifdef WLAN_FEATURE_VOWIFI_11R
        if (fc.subType == SIR_MAC_MGMT_AUTH) 
        {
#ifdef WLAN_FEATURE_VOWIFI_11R_DEBUG
            limLog( pMac, LOGE, FL("ProtVersion %d, Type %d, Subtype %d rateIndex=%d\n"),
                    fc.protVer, fc.type, fc.subType, WDA_GET_RX_MAC_RATE_IDX(pRxPacketInfo));
            limPrintMacAddr(pMac, pHdr->bssId, LOGE);
#endif
            if (limProcessAuthFrameNoSession(pMac, pRxPacketInfo, limMsg->bodyptr) == eSIR_SUCCESS)
            {
                limPktFree(pMac, HAL_TXRX_FRM_802_11_MGMT, pRxPacketInfo, limMsg->bodyptr);
                return;
            }
        }
#endif
        if((fc.subType != SIR_MAC_MGMT_PROBE_RSP )&&
            (fc.subType != SIR_MAC_MGMT_BEACON)&&
            (fc.subType != SIR_MAC_MGMT_PROBE_REQ)
#if defined WLAN_FEATURE_P2P
            && (fc.subType != SIR_MAC_MGMT_ACTION ) //                                                                 
#endif
          )
        {

            if((psessionEntry = peFindSessionByPeerSta(pMac,pHdr->sa,&sessionId))== NULL) 
            {
               limLog(pMac, LOG1, FL("session does not exist for given bssId\n"));
               limPktFree(pMac, HAL_TXRX_FRM_802_11_MGMT, pRxPacketInfo, limMsg->bodyptr);
               return;
            }
        } 
    }


#ifdef WLAN_FEATURE_P2P 
    /*                                     */
    if(limCheckMgmtRegisteredFrames(pMac, pRxPacketInfo, psessionEntry))
    {        
        limLog( pMac, LOG1, FL("Received frame is passed to SME\n"));
        limPktFree(pMac, HAL_TXRX_FRM_802_11_MGMT, pRxPacketInfo, limMsg->bodyptr);
        return;
    }
#endif 


#ifdef ANI_PRODUCT_TYPE_AP
    if ((psessionEntry->limSystemRole == eLIM_AP_ROLE) && (LIM_IS_RADAR_DETECTED(pMac)))
    {
        PELOGW(limLog(pMac, LOGW, FL("Droping the received packets as radar is detected\n"));)
        limPktFree(pMac, HAL_TXRX_FRM_802_11_MGMT, pRxPacketInfo, (void *) limMsg->bodyptr);
        return;
    }
#endif

    if (fc.protVer != SIR_MAC_PROTOCOL_VERSION)
    {   //                                              
        limLog(pMac, LOGE, FL("Unexpected frame with protVersion %d received\n"),
           fc.protVer);
        limPktFree(pMac, HAL_TXRX_FRM_802_11_MGMT, pRxPacketInfo, (void *) limMsg->bodyptr);
#ifdef WLAN_DEBUG            
        pMac->lim.numProtErr++;
#endif
        return;
    }


    if (limIsSystemInScanState(pMac))
    {
        limHandleFramesInScanState(pMac, limMsg, pRxPacketInfo, pDeferMsg, psessionEntry);
        return;
    }

/*                                                                                             */

#if 0
    if (psessionEntry->limSystemRole == eLIM_UNKNOWN_ROLE) {
        limLog( pMac, LOGW, FL( "gLimSystemRole is %d. Exiting...\n" ),psessionEntry->limSystemRole );
        limPktFree(pMac, HAL_TXRX_FRM_802_11_MGMT, pRxPacketInfo, (void *) limMsg->bodyptr);

#ifdef WLAN_DEBUG        
        pMac->lim.numProtErr++;
#endif
        return;
    }
 #endif     //                             


#ifdef WLAN_DEBUG    
    pMac->lim.numMAC[fc.type][fc.subType]++;
#endif
    
    switch (fc.type)
    {
        case SIR_MAC_MGMT_FRAME:
        {
                #if 0   //                   
                if (limIsReassocInProgress( pMac,psessionEntry) && (fc.subType != SIR_MAC_MGMT_DISASSOC) &&
                                                (fc.subType != SIR_MAC_MGMT_DEAUTH) && (fc.subType != SIR_MAC_MGMT_REASSOC_RSP))
                {
                    limLog(pMac, LOGE, FL("Frame with Type - %d, Subtype - %d received in ReAssoc Wait state, dropping...\n"),
                                                                fc.type, fc.subType);
                    return;
            }
                #endif   //                          
            //                          
            switch (fc.subType)
            {
                case SIR_MAC_MGMT_ASSOC_REQ:
                    //                                        
                    if ((psessionEntry->limSystemRole == eLIM_BT_AMP_AP_ROLE)
#ifdef WLAN_SOFTAP_FEATURE
                    || (psessionEntry->limSystemRole == eLIM_AP_ROLE)
#endif
                    )
                        limProcessAssocReqFrame(pMac, pRxPacketInfo, LIM_ASSOC, psessionEntry);

                    else
                    {
                        //                              
                        limLog(pMac, LOGE, FL("unexpected message received %X\n"),limMsg->type);
                        limPrintMsgName(pMac, LOGE, limMsg->type);
                    }
                    break;

                case SIR_MAC_MGMT_ASSOC_RSP:
                    limProcessAssocRspFrame(pMac, pRxPacketInfo, LIM_ASSOC,psessionEntry);
                    break;

                case SIR_MAC_MGMT_REASSOC_REQ:
                    //                                          
                    if ((psessionEntry->limSystemRole == eLIM_BT_AMP_AP_ROLE)
#ifdef WLAN_SOFTAP_FEATURE
                      || (psessionEntry->limSystemRole == eLIM_AP_ROLE)
#endif                   
                    ){
                        limProcessAssocReqFrame(pMac, pRxPacketInfo, LIM_REASSOC, psessionEntry);
                    }
                    else
                    {
                        //                              
                        limLog(pMac, LOGE, FL("unexpected message received %X\n"),limMsg->type);
                        limPrintMsgName(pMac, LOGE, limMsg->type);
                    }
                    break;

                case SIR_MAC_MGMT_REASSOC_RSP:
                    limProcessAssocRspFrame(pMac, pRxPacketInfo, LIM_REASSOC,psessionEntry);
                    break;

                case SIR_MAC_MGMT_PROBE_REQ:
                    limProcessProbeReqFrame_multiple_BSS(pMac, pRxPacketInfo,psessionEntry);
                    break;

                case SIR_MAC_MGMT_PROBE_RSP:
                    if(psessionEntry == NULL)
                        limProcessProbeRspFrameNoSession(pMac, pRxPacketInfo);
                    else
                        limProcessProbeRspFrame(pMac, pRxPacketInfo, psessionEntry);
                    break;

                case SIR_MAC_MGMT_BEACON:
                    __limHandleBeacon(pMac, limMsg,psessionEntry);
                    break;

                case SIR_MAC_MGMT_DISASSOC:
                    limProcessDisassocFrame(pMac, pRxPacketInfo,psessionEntry);
                    break;

                case SIR_MAC_MGMT_AUTH:
                    limProcessAuthFrame(pMac, pRxPacketInfo,psessionEntry);
                    break;

                case SIR_MAC_MGMT_DEAUTH:
                    limProcessDeauthFrame(pMac, pRxPacketInfo,psessionEntry);
                    break;

                case SIR_MAC_MGMT_ACTION:
#if defined WLAN_FEATURE_P2P
                   if(psessionEntry == NULL)
                      limProcessActionFrameNoSession(pMac, pRxPacketInfo);
                   else
                   {
#endif
                      if (WDA_GET_RX_UNKNOWN_UCAST(pRxPacketInfo))
                         limHandleUnknownA2IndexFrames(pMac, pRxPacketInfo,psessionEntry);
                     else
                         limProcessActionFrame(pMac, pRxPacketInfo,psessionEntry);
#if defined WLAN_FEATURE_P2P
                   }
#endif
                   break;
                default:
                    //                                                
                    break;
            } //                    

        }
        break;
#ifdef FEATURE_WLAN_CCX
        case SIR_MAC_DATA_FRAME:
        {
             /*                                                     
                                                                 
                       
              */
             if (psessionEntry && psessionEntry->isCCXconnection) {
                 limProcessIappFrame(pMac, pRxPacketInfo, psessionEntry);
             }
        }
        break;
#endif
        default:
            //                                  
            break;

    } //                 

    limPktFree(pMac, HAL_TXRX_FRM_802_11_MGMT, pRxPacketInfo, (void *) limMsg->bodyptr) ;
    return;
} /*                                */


/* 
                           
  
           
                                                                                  
  
  
       
  
                                                    
                                                        
               
 */
void
limProcessAbortScanInd(tpAniSirGlobal pMac)
{
#ifdef FEATURE_WLAN_DIAG_SUPPORT_LIM //                          
    limDiagEventReport(pMac, WLAN_PE_DIAG_SCAN_ABORT_IND_EVENT, NULL, 0, 0);
#endif //                         
    
    /*                                                                  
                                                                 
                                         
     */
    PELOGE(limLog(pMac, LOGE, FL("Processing AbortScan Ind\n"));)

    limAbortBackgroundScan(pMac);

    /*                                                 */
    if(limIsSystemInScanState(pMac))
    {
        if( (eLIM_HAL_INIT_SCAN_WAIT_STATE == pMac->lim.gLimHalScanState ) ||
            (eLIM_HAL_START_SCAN_WAIT_STATE == pMac->lim.gLimHalScanState ) ||
            (eLIM_HAL_END_SCAN_WAIT_STATE == pMac->lim.gLimHalScanState ) ||
            (eLIM_HAL_FINISH_SCAN_WAIT_STATE == pMac->lim.gLimHalScanState) )
        {
            //                              
            limLog( pMac, LOGW, FL(" waiting for HAL, simply signal abort gLimHalScanState = %d\n"), pMac->lim.gLimHalScanState );
            pMac->lim.abortScan = 1;
        }
        else
        {
            //           
            limLog( pMac, LOGW, FL(" Force aborting scan\n") );
            pMac->lim.abortScan = 0;
            limDeactivateAndChangeTimer(pMac, eLIM_MIN_CHANNEL_TIMER);
            limDeactivateAndChangeTimer(pMac, eLIM_MAX_CHANNEL_TIMER);
            //                                                       
            //                                                               
            peSetResumeChannel(pMac, 0, 0);
            limSendHalFinishScanReq(pMac, eLIM_HAL_FINISH_SCAN_WAIT_STATE);
        }
    }
    return;
}

/* 
                      
  
           
                                                                                  
                                               
                                                 
                                      
               
 */

void limMessageProcessor(tpAniSirGlobal pMac, tpSirMsgQ limMsg)
{
    if (eLIM_MLM_OFFLINE_STATE == pMac->lim.gLimMlmState)
    {
        peFreeMsg(pMac, limMsg);
        return;
    }

    if (!defMsgDecision(pMac, limMsg))
    {
        limProcessMessages(pMac, limMsg);
#ifdef ANI_PRODUCT_TYPE_CLIENT
        //                                          
        {
            if ( (! (pMac->lim.gLimAddtsSent))
                            &&
                    (! (limIsSystemInScanState(pMac)))
                )
            {
                if (true == GET_LIM_PROCESS_DEFD_MESGS(pMac))
                  limProcessDeferredMessageQueue(pMac);
            }
        }
#else
        {
        //                                          
            if (! (pMac->lim.gLimSystemInScanLearnMode))
            {
#if defined(ANI_AP_CLIENT_SDK)
                if (pMac->lim.gLimSystemRole != eLIM_AP_ROLE && (pMac->lim.gLimAddtsSent))
                    return;
#endif

                if (true == GET_LIM_PROCESS_DEFD_MESGS(pMac))
                        limProcessDeferredMessageQueue(pMac);
            }
        }
#endif
    }
}

#ifdef FEATURE_OEM_DATA_SUPPORT

void limOemDataRspHandleResumeLinkRsp(tpAniSirGlobal pMac, eHalStatus status, tANI_U32* mlmOemDataRsp)
{
    if(status != eHAL_STATUS_SUCCESS)
    {
        limLog(pMac, LOGE, FL("OEM Data Rsp failed to get the response for resume link\n"));
    }

    if(NULL != pMac->lim.gpLimMlmOemDataReq)
    {
        palFreeMemory(pMac->hHdd, pMac->lim.gpLimMlmOemDataReq);
        pMac->lim.gpLimMlmOemDataReq = NULL;
    }

    //                                                              
    //                                                                             
    //                                     
    //                        
    limPostSmeMessage(pMac, LIM_MLM_OEM_DATA_CNF, (tANI_U32*)(mlmOemDataRsp));

    return;
}

void limProcessOemDataRsp(tpAniSirGlobal pMac, tANI_U32* body)
{
    eHalStatus status = eHAL_STATUS_SUCCESS;
    tpLimMlmOemDataRsp mlmOemDataRsp = NULL;
    tpStartOemDataRsp oemDataRsp = NULL;

    //                                          
    SET_LIM_PROCESS_DEFD_MESGS(pMac, true);

    oemDataRsp = (tpStartOemDataRsp)(body);

    status = palAllocateMemory(pMac->hHdd, (void**)(&mlmOemDataRsp), sizeof(tLimMlmOemDataRsp));
    if(status != eHAL_STATUS_SUCCESS)
    {
        limLog(pMac, LOGP, FL("could not allocate memory for mlmOemDataRsp\n"));
        return;
    }

    //                                                                    
    //                                                                             
    palCopyMemory(pMac->hHdd, (void*)(mlmOemDataRsp), (void*)(oemDataRsp), sizeof(tLimMlmOemDataRsp));

    //                            
    palFreeMemory(pMac->hHdd, (void*)(oemDataRsp));

    limResumeLink(pMac, limOemDataRspHandleResumeLinkRsp, (tANI_U32*)mlmOemDataRsp);

    return;
}

#endif


/* 
                     
  
           
                                                                   
                                               
  
        
                                                                
                                                                
                                                                      
  
              
     
  
       
     
  
                                                 
                                      
               
 */

void
limProcessMessages(tpAniSirGlobal pMac, tpSirMsgQ  limMsg)
{
    tANI_U8  deferMsg = false;
    tLinkStateParams *linkStateParams;
#if defined WLAN_FEATURE_VOWIFI_11R
    tpPESession pSession;
#endif
#if defined(ANI_DVT_DEBUG)
    tSirMsgQ  msgQ;
#endif
    if(pMac->gDriverType == eDRIVER_TYPE_MFG)
    {
        palFreeMemory(pMac->hHdd, (tANI_U8 *)limMsg->bodyptr);
        limMsg->bodyptr = NULL;
        return;
    }
#ifdef WLAN_DEBUG    
    pMac->lim.numTot++;
#endif


   PELOG3(limLog(pMac, LOG3, FL("rcvd msgType = %s, sme state = %s, mlm state = %s\n"),
      limMsgStr(limMsg->type), limSmeStateStr(pMac->lim.gLimSmeState),
      limMlmStateStr(pMac->lim.gLimMlmState));)

    MTRACE(macTraceMsgRx(pMac, NO_SESSION, LIM_TRACE_MAKE_RXMSG(limMsg->type, LIM_MSG_PROCESSED));)

    switch (limMsg->type)
    {

        case SIR_LIM_UPDATE_BEACON:
            limUpdateBeacon(pMac);
            break;

        case SIR_CFG_PARAM_UPDATE_IND:
            //                       
            if (limIsSystemInScanState(pMac))
            {
                //                              
                //                               
                if (limDeferMsg(pMac, limMsg) != TX_SUCCESS)
                {
                    PELOGE(limLog(pMac, LOGE, FL("Unable to Defer message(0x%X) limSmeState %d (prev sme state %d) sysRole %d mlm state %d (prev mlm state %d)\n"),
                        limMsg->type, pMac->lim.gLimSmeState,  pMac->lim.gLimPrevSmeState,
                        pMac->lim.gLimSystemRole,  pMac->lim.gLimMlmState,  pMac->lim.gLimPrevMlmState);)
                    limLogSessionStates(pMac);
                    limPrintMsgName(pMac, LOGE, limMsg->type);
                }
            }
            else
            {
                limHandleCFGparamUpdate(pMac, limMsg->bodyval);
            }

            break;

        case WDA_INIT_SCAN_RSP:
            limProcessInitScanRsp(pMac, limMsg->bodyptr);
            break;

        case WDA_START_SCAN_RSP:
            limProcessStartScanRsp(pMac, limMsg->bodyptr);
            break;

        case WDA_END_SCAN_RSP:
            limProcessEndScanRsp(pMac, limMsg->bodyptr);
            break;

        case WDA_FINISH_SCAN_RSP:
            limProcessFinishScanRsp(pMac, limMsg->bodyptr);
            break;
#ifdef FEATURE_OEM_DATA_SUPPORT
        case WDA_START_OEM_DATA_RSP:
            limProcessOemDataRsp(pMac, limMsg->bodyptr);
            break;
#endif

        case WDA_SWITCH_CHANNEL_RSP:
            limProcessSwitchChannelRsp(pMac, limMsg->bodyptr);
            break;
            
#ifdef ANI_SIR_IBSS_PEER_CACHING
        case WDA_IBSS_STA_ADD:
            limIbssStaAdd(pMac, limMsg->bodyptr);
            break;
#endif
        case SIR_BB_XPORT_MGMT_MSG:
            //                                         
#ifdef WLAN_DEBUG                
            pMac->lim.numBbt++;
#endif

#ifdef VOSS_ENABLED
            {
                v_U16_t     pktLen = 0;
                vos_pkt_t  *pVosPkt;
                VOS_STATUS  vosStatus;
                tSirMsgQ    limMsgNew;

                /*                                                      
                                                                                          
                                                                                             
                                                                                            
                                                     
                 */
                palCopyMemory(pMac, (tANI_U8*)&limMsgNew, (tANI_U8*)limMsg, sizeof(tSirMsgQ));
                pVosPkt = (vos_pkt_t *)limMsgNew.bodyptr;
                vos_pkt_get_packet_length(pVosPkt, &pktLen);

                vosStatus = WDA_DS_PeekRxPacketInfo( pVosPkt, (v_PVOID_t *)&limMsgNew.bodyptr, VOS_FALSE );

                if( !VOS_IS_STATUS_SUCCESS(vosStatus) )
                {
                    vos_pkt_return_packet(pVosPkt);
                    break;

                }
                limHandle80211Frames(pMac, &limMsgNew, &deferMsg);

                if ( deferMsg == true )
                {
                    PELOG1(limLog(pMac, LOG1, FL("Defer message type=%X \n"), limMsg->type);)
                        if (limDeferMsg(pMac, limMsg) != TX_SUCCESS)
                        {
                            PELOGE(limLog(pMac, LOGE, FL("Unable to Defer message(0x%X) limSmeState %d (prev sme state %d) sysRole %d mlm state %d (prev mlm state %d)\n"),
                                limMsg->type, pMac->lim.gLimSmeState,  pMac->lim.gLimPrevSmeState,
                                pMac->lim.gLimSystemRole,  pMac->lim.gLimMlmState,  pMac->lim.gLimPrevMlmState);)
                            limLogSessionStates(pMac);
                            limPrintMsgName(pMac, LOGE, limMsg->type);
                            vos_pkt_return_packet(pVosPkt);
                        }
                }
                else
                {
                    /*                                                                          
                                                                               
                                                       
                     */
                    vos_pkt_return_packet(pVosPkt);
                }
            }
#else
            limHandle80211Frames(pMac, limMsg);
#endif
            break;

        case eWNI_SME_SCAN_REQ:
#ifdef WLAN_FEATURE_P2P
        case eWNI_SME_REMAIN_ON_CHANNEL_REQ:
#endif
        case eWNI_SME_DISASSOC_REQ:
        case eWNI_SME_DEAUTH_REQ:
        case eWNI_SME_STA_STAT_REQ:
        case eWNI_SME_AGGR_STAT_REQ:
        case eWNI_SME_GLOBAL_STAT_REQ:
        case eWNI_SME_STAT_SUMM_REQ:
        case eWNI_SME_GET_SCANNED_CHANNEL_REQ:
        case eWNI_SME_GET_STATISTICS_REQ:
#ifdef FEATURE_OEM_DATA_SUPPORT
        case eWNI_SME_OEM_DATA_REQ:
#endif
            //                            
            limProcessNormalHddMsg(pMac, limMsg, true);  //                       
            break;

        case eWNI_SME_SCAN_ABORT_IND:
            vos_mem_free((v_VOID_t *)limMsg->bodyptr);
            limMsg->bodyptr = NULL;
            limProcessAbortScanInd(pMac);
            break;

        case eWNI_SME_START_REQ:
        case eWNI_SME_SYS_READY_IND:
#ifndef WNI_ASKEY_NON_SUPPORT_FEATURE
        case eWNI_SME_JOIN_REQ:
#endif
        case eWNI_SME_AUTH_REQ:
        case eWNI_SME_REASSOC_REQ:
        case eWNI_SME_START_BSS_REQ:
        case eWNI_SME_STOP_BSS_REQ:
        case eWNI_SME_SWITCH_CHL_REQ:
        case eWNI_SME_SWITCH_CHL_CB_PRIMARY_REQ:
        case eWNI_SME_SWITCH_CHL_CB_SECONDARY_REQ:
        case eWNI_SME_SETCONTEXT_REQ:
        case eWNI_SME_REMOVEKEY_REQ:
#ifndef WNI_ASKEY_NON_SUPPORT_FEATURE
        case eWNI_SME_PROMISCUOUS_MODE_REQ:
#endif
        case eWNI_SME_DISASSOC_CNF:
        case eWNI_SME_DEAUTH_CNF:
        case eWNI_SME_ASSOC_CNF:
        case eWNI_SME_REASSOC_CNF:
        case eWNI_SME_ADDTS_REQ:
        case eWNI_SME_DELTS_REQ:
        case eWNI_SME_DEL_BA_PEER_IND:
        case eWNI_SME_SET_TX_POWER_REQ:
        case eWNI_SME_GET_TX_POWER_REQ:
        case eWNI_SME_GET_NOISE_REQ:
#ifdef WLAN_SOFTAP_FEATURE        
        case eWNI_SME_GET_ASSOC_STAS_REQ:
        case eWNI_SME_TKIP_CNTR_MEAS_REQ:
        case eWNI_SME_UPDATE_APWPSIE_REQ:
        case eWNI_SME_HIDE_SSID_REQ:
        case eWNI_SME_GET_WPSPBC_SESSION_REQ:
        case eWNI_SME_SET_APWPARSNIEs_REQ:
#endif
#if defined WLAN_FEATURE_VOWIFI
        case eWNI_SME_NEIGHBOR_REPORT_REQ_IND:
        case eWNI_SME_BEACON_REPORT_RESP_XMIT_IND:
#endif
#if defined FEATURE_WLAN_CCX
        case eWNI_SME_CCX_ADJACENT_AP_REPORT:
#endif
#ifdef WLAN_FEATURE_VOWIFI_11R
        case eWNI_SME_FT_UPDATE_KEY:
        case eWNI_SME_FT_PRE_AUTH_REQ:
        case eWNI_SME_FT_AGGR_QOS_REQ:
#endif
        case eWNI_SME_ADD_STA_SELF_REQ:
        case eWNI_SME_DEL_STA_SELF_REQ:
#ifdef WLAN_FEATURE_P2P
        case eWNI_SME_REGISTER_MGMT_FRAME_REQ:
        case eWNI_SME_UPDATE_NOA:
#endif
            //                            
            limProcessNormalHddMsg(pMac, limMsg, false);   //                          
            break;

        //                            
        case eWNI_PMC_PWR_SAVE_CFG:
        case eWNI_PMC_ENTER_BMPS_REQ:
        case eWNI_PMC_EXIT_BMPS_REQ:
        case eWNI_PMC_ENTER_IMPS_REQ:
        case eWNI_PMC_EXIT_IMPS_REQ:
        case eWNI_PMC_ENTER_UAPSD_REQ:
        case eWNI_PMC_EXIT_UAPSD_REQ:
        case eWNI_PMC_ENTER_WOWL_REQ:
        case eWNI_PMC_EXIT_WOWL_REQ:
        case eWNI_PMC_WOWL_ADD_BCAST_PTRN:
        case eWNI_PMC_WOWL_DEL_BCAST_PTRN:
            pmmProcessMessage(pMac, limMsg);
            break;

        case eWNI_PMC_SMPS_STATE_IND :
        {
            if(limMsg->bodyptr){
            palFreeMemory(pMac->hHdd, (tANI_U8 *)limMsg->bodyptr);
            limMsg->bodyptr = NULL;
            }
        }
            break;
#if defined WLAN_FEATURE_P2P
        case eWNI_SME_SEND_ACTION_FRAME_IND:
            limSendP2PActionFrame(pMac, limMsg);
            palFreeMemory(pMac->hHdd, (tANI_U8 *)limMsg->bodyptr);
            limMsg->bodyptr = NULL;
            break;
        case eWNI_SME_ABORT_REMAIN_ON_CHAN_IND:
            limAbortRemainOnChan(pMac);
            palFreeMemory(pMac->hHdd, (tANI_U8 *)limMsg->bodyptr);
            limMsg->bodyptr = NULL;
            break;

        case SIR_HAL_P2P_NOA_ATTR_IND:
            {
                tpPESession psessionEntry = &pMac->lim.gpSession[0];  
                tANI_U8  i;
                
                
                limLog(pMac, LOGW, FL("Received message Noa_ATTR %x\n"), limMsg->type);
                for(i=0; i < pMac->lim.maxBssId; i++)
                {
                    if   ( (psessionEntry != NULL) && (pMac->lim.gpSession[i].valid) && 
                        (psessionEntry->pePersona == VOS_P2P_GO_MODE))
                    { //                                      
                    
                        palCopyMemory(pMac->hHdd,&psessionEntry->p2pGoPsUpdate, limMsg->bodyptr,sizeof(tSirP2PNoaAttr));
                        
                        
                        limLog(pMac, LOGE, FL(" &psessionEntry->bssId%02x:%02x:%02x:%02x:%02x:%02x ctWin=%d oppPsFlag=%d\n"),
                                     psessionEntry->bssId[0],
                                     psessionEntry->bssId[1],
                                     psessionEntry->bssId[2],
                                     psessionEntry->bssId[3],
                                     psessionEntry->bssId[4],
                                     psessionEntry->bssId[5],                                     
                                     psessionEntry->p2pGoPsUpdate.ctWin,
                                     psessionEntry->p2pGoPsUpdate.oppPsFlag);

                        limLog(pMac, LOGE, FL(" uNoa1IntervalCnt=%d uNoa1Duration=%d uNoa1Interval=%d uNoa1StartTime=%d\n"),
                                     psessionEntry->p2pGoPsUpdate.uNoa1IntervalCnt,
                                     psessionEntry->p2pGoPsUpdate.uNoa1Duration,
                                     psessionEntry->p2pGoPsUpdate.uNoa1Interval,
                                     psessionEntry->p2pGoPsUpdate.uNoa1StartTime);

                        
                        break;
                    }
                }
                
            }
            palFreeMemory(pMac->hHdd, (tANI_U8 *)limMsg->bodyptr);
            limMsg->bodyptr = NULL;
            
            break;

            
#endif
        /*                                                               
                                                                          
                                                                              
                                                                             
                                    */
        case eWNI_SME_PRE_CHANNEL_SWITCH_FULL_POWER:
            if ( !tx_timer_running(&pMac->lim.limTimers.gLimChannelSwitchTimer) )
            {  
                limProcessChannelSwitchTimeout(pMac);
            }
            palFreeMemory(pMac->hHdd, (tANI_U8 *)limMsg->bodyptr);
            limMsg->bodyptr = NULL;
            break;

        //                                    
        case WDA_ENTER_BMPS_RSP:
        case WDA_EXIT_BMPS_RSP:
        case WDA_EXIT_BMPS_IND:
        case WDA_ENTER_IMPS_RSP:
        case WDA_EXIT_IMPS_RSP:
        case WDA_ENTER_UAPSD_RSP:
        case WDA_EXIT_UAPSD_RSP:
        case WDA_WOWL_ENTER_RSP:
        case WDA_WOWL_EXIT_RSP:
            pmmProcessMessage(pMac, limMsg);
            break;

        case WDA_LOW_RSSI_IND:
            //                          
            break;

        case WDA_BMPS_STATUS_IND:
            limHandleBmpsStatusInd(pMac);
            break;

        case WDA_MISSED_BEACON_IND:
            limHandleMissedBeaconInd(pMac);
            break;
        case WDA_MIC_FAILURE_IND:
           limMicFailureInd(pMac, limMsg);
           palFreeMemory(pMac->hHdd, (tANI_U8 *)limMsg->bodyptr);
           limMsg->bodyptr = NULL;
           break;
    

#if (WNI_POLARIS_FW_PACKAGE == ADVANCED) && defined(ANI_PRODUCT_TYPE_AP)
        case eWNI_SME_MEASUREMENT_REQ:
        case eWNI_SME_SET_WDS_INFO_REQ:
            //                                   
            //                                    
            if (limIsSystemInScanState(pMac))
            {
                //                              
                //                               
                if (limDeferMsg(pMac, limMsg) != TX_SUCCESS)
                {
                    pMac->lim.numSme++;
                    PELOGE(limLog(pMac, LOGE, FL("Unable to Defer message(0x%X) limSmeState %d (prev sme state %d) sysRole %d mlm state %d (prev mlm state %d)\n"),
                        limMsg->type, pMac->lim.gLimSmeState,  pMac->lim.gLimPrevSmeState,
                        pMac->lim.gLimSystemRole,  pMac->lim.gLimMlmState,  pMac->lim.gLimPrevMlmState);)
                    limLogSessionStates(pMac);
                    limPrintMsgName(pMac, LOGE, limMsg->type);
                    //             
                    palFreeMemory( pMac->hHdd, (tANI_U8 *) limMsg->bodyptr);
                    break;
                }

                if (limMsg->type == eWNI_SME_MEASUREMENT_REQ)
                {
                    if (GET_LIM_PROCESS_DEFD_MESGS(pMac))
                    {
                        //                                                       
                        //                                                               
                        peSetResumeChannel(pMac, 0, 0);
                        limSendHalFinishScanReq(pMac, eLIM_HAL_FINISH_LEARN_WAIT_STATE);
                    }
                }
            }
            else
            {
                pMac->lim.numSme++;
                limProcessLmmMessages(pMac,
                                      limMsg->type,
                                      (tANI_U32 *) limMsg->bodyptr);

                //             
                palFreeMemory( pMac->hHdd, (tANI_U8 *) limMsg->bodyptr);
            }
            break;

        case SIR_LIM_LEARN_INTERVAL_TIMEOUT:
            if ((pMac->lim.gLimSystemRole == eLIM_STA_ROLE) &&
                ((pMac->lim.gLimMlmState == eLIM_MLM_WT_DEL_STA_RSP_STATE) ||
                 (pMac->lim.gLimMlmState == eLIM_MLM_WT_DEL_BSS_RSP_STATE)))
            {
                //                                    
                //                                         
                //                                  
                PELOG1(limLog(pMac, LOG1,
                       FL("Discarding LEARN_INTERVAL_TO message\n"));)
            }
            else
                limProcessLmmMessages(pMac,
                                      limMsg->type,
                                      (tANI_U32 *) limMsg->bodyptr);
            break;

        case SIR_LIM_MEASUREMENT_IND_TIMEOUT:
        case SIR_LIM_LEARN_DURATION_TIMEOUT:
            //                                       
            //                           
            limProcessLmmMessages(pMac,
                                  limMsg->type,
                                  (tANI_U32 *) limMsg->bodyptr);

            break;

        case SIR_LIM_RADAR_DETECT_IND:
            limDetectRadar(pMac, (tANI_U32*)limMsg->bodyptr);
            palFreeMemory( pMac->hHdd, (tANI_U32*)limMsg->bodyptr);
            break;

#endif

        case SIR_LIM_ADDTS_RSP_TIMEOUT:
            limProcessSmeReqMessages(pMac,limMsg);
            break;
#ifdef FEATURE_WLAN_CCX
        case SIR_LIM_CCX_TSM_TIMEOUT:
            limProcessTsmTimeoutHandler(pMac,limMsg);
            break;
        case WDA_TSM_STATS_RSP:
            limProcessHalCcxTsmRsp(pMac, limMsg);
            break;
#endif
        case WDA_ADD_TS_RSP:
            limProcessHalAddTsRsp(pMac, limMsg);
            break;

        case SIR_LIM_DEL_TS_IND:
          limProcessDelTsInd(pMac, limMsg);
        case SIR_LIM_ADD_BA_IND:
            limProcessAddBaInd(pMac, limMsg);
            break;
        case SIR_LIM_DEL_BA_ALL_IND:
            limDelAllBASessions(pMac);  //                       
            break;
        case SIR_LIM_DEL_BA_IND:
            limProcessMlmHalBADeleteInd( pMac, limMsg );
            break;

         case SIR_LIM_BEACON_GEN_IND: {
#ifdef ANI_PRODUCT_TYPE_AP
                    if (pMac->lim.gLimSystemRole == eLIM_AP_ROLE)
                        pmmUpdateTIM(pMac, (tpBeaconGenParams)limMsg->bodyptr);
#endif

#ifdef WLAN_SOFTAP_FEATURE
                if( pMac->lim.gLimSystemRole != eLIM_AP_ROLE )
#endif                  
                    schProcessPreBeaconInd(pMac, limMsg);    

                }
                break;

        case SIR_LIM_DELETE_STA_CONTEXT_IND:
            limDeleteStaContext(pMac, limMsg);
            break;

        case SIR_LIM_MIN_CHANNEL_TIMEOUT:
        case SIR_LIM_MAX_CHANNEL_TIMEOUT:
        case SIR_LIM_PERIODIC_PROBE_REQ_TIMEOUT:
        case SIR_LIM_JOIN_FAIL_TIMEOUT:
        case SIR_LIM_AUTH_FAIL_TIMEOUT:
        case SIR_LIM_AUTH_RSP_TIMEOUT:
        case SIR_LIM_ASSOC_FAIL_TIMEOUT:
        case SIR_LIM_REASSOC_FAIL_TIMEOUT:
#ifdef WLAN_FEATURE_VOWIFI_11R
        case SIR_LIM_FT_PREAUTH_RSP_TIMEOUT:
#endif
#ifdef WLAN_FEATURE_P2P
        case SIR_LIM_REMAIN_CHN_TIMEOUT:
#endif
            //                                                     

            limProcessMlmReqMessages(pMac,
                                     limMsg);

            break;

        case SIR_LIM_HEART_BEAT_TIMEOUT:
            /*                                                
                                                                     
                                     
                    */

            #if 0 
            PELOG1(limLog(pMac, LOG1, FL("Heartbeat timeout, SME %d, MLME %d, #bcn %d\n"),
                   pMac->lim.gLimSmeState, pMac->lim.gLimMlmState,
                   pMac->lim.gLimRxedBeaconCntDuringHB);)

            if(pMac->lim.gLimSystemRole == eLIM_STA_IN_IBSS_ROLE)
                limIbssHeartBeatHandle(pMac); //                    
            else
                /* 
                                                           
                                                          
                        */
                limHandleHeartBeatFailure(pMac);

            break;
            #endif //                 

            limHandleHeartBeatTimeout(pMac);
            break;
           
        case SIR_LIM_PROBE_HB_FAILURE_TIMEOUT:
            limHandleHeartBeatFailureTimeout(pMac);            
            break;

        case SIR_LIM_CHANNEL_SCAN_TIMEOUT:
#if defined(ANI_PRODUCT_TYPE_CLIENT) || defined(ANI_AP_CLIENT_SDK)
            /* 
                                                       
                                                 
             */
             limDeactivateAndChangeTimer(pMac, eLIM_BACKGROUND_SCAN_TIMER);

            //                                             
            //                                 
            pMac->lim.gLimReportBackgroundScanResults = FALSE;
            limTriggerBackgroundScan(pMac);
#endif
            break;

#ifdef ANI_PRODUCT_TYPE_AP
        case SIR_LIM_PREAUTH_CLNUP_TIMEOUT:
            if (limIsSystemInScanState(pMac))
            {
                //                              
                //                               
                if (limDeferMsg(pMac, limMsg) != TX_SUCCESS)
                {
                    PELOGE(limLog(pMac, LOGE, FL("Unable to Defer message(0x%X) limSmeState %d (prev sme state %d) sysRole %d mlm state %d (prev mlm state %d)\n"),
                        limMsg->type, pMac->lim.gLimSmeState,  pMac->lim.gLimPrevSmeState,
                        pMac->lim.gLimSystemRole,  pMac->lim.gLimMlmState,  pMac->lim.gLimPrevMlmState);)
                    limLogSessionStates(pMac);
                }
            }
            else
            {
                //                                                   
                limPreAuthClnupHandler(pMac);
            }

            break;
#endif

        case SIR_LIM_HASH_MISS_THRES_TIMEOUT:

            /*
                                                                     
             */

            pMac->lim.gLimDisassocFrameCredit = 0;
            break;

        case SIR_LIM_CNF_WAIT_TIMEOUT:

            /*
                                                   
             */
            limHandleCnfWaitTimeout(pMac, (tANI_U16) limMsg->bodyval);

            break;

        case SIR_LIM_KEEPALIVE_TIMEOUT:
            limSendKeepAliveToPeer(pMac);

            break;

        case SIR_LIM_RETRY_INTERRUPT_MSG:
            //                                                      

            break;

        case SIR_LIM_INV_KEY_INTERRUPT_MSG:
            //                                                         

            break;

        case SIR_LIM_KEY_ID_INTERRUPT_MSG:
            //                                                    

            break;

        case SIR_LIM_REPLAY_THRES_INTERRUPT_MSG:
            //                                                      

            break;

        case SIR_LIM_CHANNEL_SWITCH_TIMEOUT:
            limProcessChannelSwitchTimeout(pMac);
            break;

        case SIR_LIM_QUIET_TIMEOUT:
            limProcessQuietTimeout(pMac);
            break;

        case SIR_LIM_QUIET_BSS_TIMEOUT:
            limProcessQuietBssTimeout(pMac);
            break;

#ifdef WLAN_SOFTAP_FEATURE
        case SIR_LIM_UPDATE_OLBC_CACHEL_TIMEOUT:
            limHandleUpdateOlbcCache(pMac);
            break;
#if 0
        case SIR_LIM_WPS_OVERLAP_TIMEOUT:
            limProcessWPSOverlapTimeout(pMac);
            break;
#endif

#endif

        case WDA_ADD_BSS_RSP:
            limProcessMlmAddBssRsp( pMac, limMsg );
            break;

        case WDA_ADD_STA_RSP:

            //                                                                                               
            limProcessAddStaRsp(pMac,limMsg);
            break;

        case WDA_DELETE_STA_RSP:
            limProcessMlmDelStaRsp(pMac, limMsg);
            break;

        case WDA_ADD_STA_SELF_RSP:
            limProcessAddStaSelfRsp(pMac, limMsg);
            break; 
        case WDA_DEL_STA_SELF_RSP:
            limProcessDelStaSelfRsp(pMac, limMsg);
            break;

        case WDA_DELETE_BSS_RSP:
            limHandleDeleteBssRsp(pMac,limMsg); //                                              
            break;

        case WDA_SET_BSSKEY_RSP:
        case WDA_SET_STA_BCASTKEY_RSP:
            limProcessMlmSetBssKeyRsp( pMac, limMsg );
            break;
        case WDA_SET_STAKEY_RSP:
            limProcessMlmSetStaKeyRsp( pMac, limMsg );
            break;
        case WDA_REMOVE_BSSKEY_RSP:
        case WDA_REMOVE_STAKEY_RSP:
            limProcessMlmRemoveKeyRsp( pMac, limMsg );
            break;
        case WDA_ADDBA_RSP:
            limProcessMlmHalAddBARsp( pMac, limMsg );
            break;

        case WDA_STA_STAT_RSP:
        case WDA_AGGR_STAT_RSP:
        case WDA_GLOBAL_STAT_RSP:
        case WDA_STAT_SUMM_RSP:
            limSendSmeStatsRsp ( pMac, limMsg->type, (void *)limMsg->bodyptr);
            break;

        case WDA_GET_STATISTICS_RSP:
            limSendSmePEStatisticsRsp ( pMac, limMsg->type, (void *)limMsg->bodyptr);
            break;

        case WDA_SET_MIMOPS_RSP:            //                                   
        case WDA_SET_TX_POWER_RSP:          //                                      
        case WDA_GET_TX_POWER_RSP:          //                                      
        case WDA_GET_NOISE_RSP:
            vos_mem_free((v_VOID_t*)limMsg->bodyptr);
            limMsg->bodyptr = NULL;
            //                                    
            break;

        case WDA_SET_MAX_TX_POWER_RSP:
#if defined WLAN_FEATURE_VOWIFI
            rrmSetMaxTxPowerRsp( pMac, limMsg );
#endif
            if(limMsg->bodyptr != NULL)
            {
               vos_mem_free((v_VOID_t*)limMsg->bodyptr);
               limMsg->bodyptr = NULL;
            }
            break;

#ifdef ANI_CHIPSET_VOLANS
       case SIR_LIM_ADDR2_MISS_IND:
       {
           limLog(pMac, LOGE,
                   FL("Addr2 mismatch interrupt received %X\n"),
                   limMsg->type);
           /*                                                               
                                                                        */
           //                                                            
           //                                                              

           /*                         */ 
           vos_mem_free((v_VOID_t *)(limMsg->bodyptr));
           break;
       }
#endif

#ifdef WLAN_FEATURE_VOWIFI_11R
    case WDA_AGGR_QOS_RSP:
       limProcessFTAggrQoSRsp( pMac, limMsg );
       break;
#endif

    case WDA_SET_LINK_STATE_RSP:
       linkStateParams = (tLinkStateParams *)limMsg->bodyptr;
#if defined WLAN_FEATURE_VOWIFI_11R
       pSession = linkStateParams->session;
       if(linkStateParams->ft)
       {
          limSendReassocReqWithFTIEsMgmtFrame(pMac, 
                                              pSession->pLimMlmReassocReq,
                                              pSession); 
       }
#endif
       if( linkStateParams->callback )
       {
          linkStateParams->callback( pMac, linkStateParams->callbackArg );
       }
       vos_mem_free((v_VOID_t *)(limMsg->bodyptr));
       break;

#ifdef WLAN_FEATURE_PACKET_FILTERING
    case WDA_PACKET_COALESCING_FILTER_MATCH_COUNT_RSP:
        pmmProcessMessage(pMac, limMsg);
        break;
#endif //                              

#ifdef WLAN_FEATURE_GTK_OFFLOAD
    case WDA_GTK_OFFLOAD_GETINFO_RSP:
        pmmProcessMessage(pMac, limMsg);
        break;
#endif //                         

    default:
        vos_mem_free((v_VOID_t*)limMsg->bodyptr);
        limMsg->bodyptr = NULL;
        //                  
        //          
        limLog(pMac, LOGE,
                FL("Discarding unexpected message received %X\n"),
                limMsg->type);
        limPrintMsgName(pMac, LOGE, limMsg->type);
        break;

    } //                      

   PELOG2(limLog(pMac, LOG2, FL("Done Processing msgType = %d, sme state = %s, mlm state = %s\n"),
            limMsg->type, limSmeStateStr(pMac->lim.gLimSmeState),
            limMlmStateStr(pMac->lim.gLimMlmState));)

} /*                              */



/* 
                                 
  
           
                                                          
                                                         
                                          
  
        
  
              
     
  
       
     
  
                                                 
               
 */

void
limProcessDeferredMessageQueue(tpAniSirGlobal pMac)
{
    tSirMsgQ  limMsg = { 0, 0, 0 };

#if defined(ANI_OS_TYPE_LINUX) || defined(ANI_OS_TYPE_OSX)
    while (TX_SUCCESS == tx_queue_receive(&pMac->sys.gSirLimDeferredMsgQ, (void *) &limMsg, TX_NO_WAIT))
    {
        PELOG3(limLog(pMac, LOG3, FL("Processing deferred message %X\n"), limMsg.type);)
        limPrintMsgName(pMac, LOG3, limMsg.type);
        pMac->lim.gLimNumDeferredMsgs--;
        limProcessMessages(pMac, &limMsg);

        if(true != GET_LIM_PROCESS_DEFD_MESGS(pMac))
            break;
    }
#else
    tSirMsgQ *readMsg;
    tANI_U16  size;

    /*
                                                       
     */
    size = pMac->lim.gLimDeferredMsgQ.size;
    if (size > 0)
    {
        while ((readMsg = limReadDeferredMsgQ(pMac)) != NULL)
        {
            palCopyMemory( pMac->hHdd, (tANI_U8*) &limMsg,
                    (tANI_U8*) readMsg, sizeof(tSirMsgQ));
            size--; 
            limProcessMessages(pMac, &limMsg);

            if((limIsSystemInScanState(pMac)) || (true != GET_LIM_PROCESS_DEFD_MESGS(pMac)) ||
                 (pMac->lim.gLimSystemInScanLearnMode))
                break;
        }
    }
#endif
} /*                                          */


/*
                         
                                                                                                                
                                                 
                                                      
                                                   
               
 */
void limProcessNormalHddMsg(tpAniSirGlobal pMac, tSirMsgQ *pLimMsg, tANI_U8 fRspReqd)
{
    tANI_BOOLEAN fDeferMsg = eANI_BOOLEAN_TRUE;

    /*                          */  
    if ((pMac->lim.gLimSystemRole == eLIM_AP_ROLE) ||(pMac->lim.gLimSystemRole == eLIM_BT_AMP_AP_ROLE )
                                                   ||(pMac->lim.gLimSystemRole == eLIM_BT_AMP_STA_ROLE)
                                                   ||(pMac->lim.gLimSystemRole == eLIM_UNKNOWN_ROLE))
    {
        /*                                                        
                                                                           
                                                                           
                                                                             
                                                  
                                                                        
                                                                         
                                                    
          
                                                                         
                                            
          */
        if (((pLimMsg->type == eWNI_SME_START_BSS_REQ) ||
             (pLimMsg->type == eWNI_SME_STOP_BSS_REQ) ||
             (pLimMsg->type == eWNI_SME_SWITCH_CHL_REQ) ||
             (pLimMsg->type == eWNI_SME_SWITCH_CHL_CB_SECONDARY_REQ) ||
             (pLimMsg->type == eWNI_SME_SWITCH_CHL_CB_PRIMARY_REQ)))
        {
            fDeferMsg = eANI_BOOLEAN_FALSE;
        }
    }

    /*                                                                                 */
    if (((pMac->lim.gLimAddtsSent) || (limIsSystemInScanState(pMac)) /*  
                                             */) && fDeferMsg)
    {
        //                                                         
        //                                                        
        if (limDeferMsg(pMac, pLimMsg) != TX_SUCCESS)
        {
#ifdef WLAN_DEBUG            
            pMac->lim.numSme++;
#endif
            PELOGE(limLog(pMac, LOGE, FL("Unable to Defer message(0x%X) limSmeState %d (prev sme state %d) sysRole %d mlm state %d (prev mlm state %d)\n"),
                        pLimMsg->type, pMac->lim.gLimSmeState,  pMac->lim.gLimPrevSmeState,
                        pMac->lim.gLimSystemRole,  pMac->lim.gLimMlmState,  pMac->lim.gLimPrevMlmState);)
            limLogSessionStates(pMac);
            limPrintMsgName(pMac, LOGE, pLimMsg->type);
            //             
            palFreeMemory( pMac->hHdd, (tANI_U8 *) pLimMsg->bodyptr);
        }
    }
    else
    {
        if(fRspReqd)
        {
            //                            
            //                                           
            //                                      
            //                                      
            pMac->lim.gLimRspReqd = eANI_BOOLEAN_TRUE;
        }
#ifdef WLAN_DEBUG            
        pMac->lim.numSme++;
#endif
        if(limProcessSmeReqMessages(pMac, pLimMsg))
        {
            //             
            //                                                             
            palFreeMemory( pMac->hHdd, (tANI_U8 *) pLimMsg->bodyptr);
        }
    }
}

void
handleHTCapabilityandHTInfo(struct sAniSirGlobal *pMac, tpPESession psessionEntry)
{
    tSirMacHTCapabilityInfo macHTCapabilityInfo;
    tSirMacHTParametersInfo macHTParametersInfo;
    tSirMacHTInfoField1 macHTInfoField1;
    tSirMacHTInfoField2 macHTInfoField2;
    tSirMacHTInfoField3 macHTInfoField3;
    tANI_U32  cfgValue;
    tANI_U8 *ptr;

    if (wlan_cfgGetInt(pMac, WNI_CFG_HT_CAP_INFO, &cfgValue) != eSIR_SUCCESS)
    {
        limLog(pMac, LOGP, FL("Fail to retrieve WNI_CFG_HT_CAP_INFO value\n"));
        return ;
    }
    ptr = (tANI_U8 *) &macHTCapabilityInfo;
    *((tANI_U16 *)ptr) =  (tANI_U16) (cfgValue & 0xffff);
    pMac->lim.gHTLsigTXOPProtection = (tANI_U8)macHTCapabilityInfo.lsigTXOPProtection;
    pMac->lim.gHTMIMOPSState = (tSirMacHTMIMOPowerSaveState) macHTCapabilityInfo.mimoPowerSave;
    pMac->lim.gHTGreenfield = (tANI_U8)macHTCapabilityInfo.greenField;
    pMac->lim.gHTMaxAmsduLength = (tANI_U8)macHTCapabilityInfo.maximalAMSDUsize;
    pMac->lim.gHTShortGI20Mhz = (tANI_U8)macHTCapabilityInfo.shortGI20MHz;
    pMac->lim.gHTShortGI40Mhz = (tANI_U8)macHTCapabilityInfo.shortGI40MHz;
    pMac->lim.gHTPSMPSupport = (tANI_U8)macHTCapabilityInfo.psmp;
    pMac->lim.gHTDsssCckRate40MHzSupport = (tANI_U8)macHTCapabilityInfo.dsssCckMode40MHz;

    if (wlan_cfgGetInt(pMac, WNI_CFG_HT_AMPDU_PARAMS, &cfgValue) != eSIR_SUCCESS)
    {
        limLog(pMac, LOGP, FL("Fail to retrieve WNI_CFG_HT_PARAM_INFO value\n"));
        return ;
    }
    ptr = (tANI_U8 *) &macHTParametersInfo;
    *ptr =  (tANI_U8) (cfgValue & 0xff);
    pMac->lim.gHTAMpduDensity = (tANI_U8)macHTParametersInfo.mpduDensity;
    pMac->lim.gHTMaxRxAMpduFactor = (tANI_U8)macHTParametersInfo.maxRxAMPDUFactor;

    //               
    if (wlan_cfgGetInt(pMac, WNI_CFG_HT_INFO_FIELD1, &cfgValue) != eSIR_SUCCESS)
    {
        limLog(pMac, LOGP, FL("Fail to retrieve WNI_CFG_HT_INFO_FIELD1 value\n"));
        return ;
    }
    ptr = (tANI_U8 *) &macHTInfoField1;
    *((tANI_U8 *)ptr) =  (tANI_U8) (cfgValue & 0xff);
    pMac->lim.gHTServiceIntervalGranularity = (tANI_U8)macHTInfoField1.serviceIntervalGranularity;
    pMac->lim.gHTControlledAccessOnly = (tANI_U8)macHTInfoField1.controlledAccessOnly;
    pMac->lim.gHTRifsMode = (tANI_U8)macHTInfoField1.rifsMode;

    if (wlan_cfgGetInt(pMac, WNI_CFG_HT_INFO_FIELD2, &cfgValue) != eSIR_SUCCESS)
    {
        limLog(pMac, LOGP, FL("Fail to retrieve WNI_CFG_HT_INFO_FIELD2 value\n"));
        return ;
    }
    ptr = (tANI_U8 *) &macHTInfoField2;
    *((tANI_U16 *)ptr) = (tANI_U16) (cfgValue & 0xffff);
    pMac->lim.gHTOperMode = (tSirMacHTOperatingMode) macHTInfoField2.opMode;

    if (wlan_cfgGetInt(pMac, WNI_CFG_HT_INFO_FIELD3, &cfgValue) != eSIR_SUCCESS)
    {
        limLog(pMac, LOGP, FL("Fail to retrieve WNI_CFG_HT_INFO_FIELD3 value\n"));
        return ;
    }
    ptr = (tANI_U8 *) &macHTInfoField3;
    *((tANI_U16 *)ptr) = (tANI_U16) (cfgValue & 0xffff);
    pMac->lim.gHTPCOActive = (tANI_U8)macHTInfoField3.pcoActive;
    pMac->lim.gHTPCOPhase = (tANI_U8)macHTInfoField3.pcoPhase;
    pMac->lim.gHTSecondaryBeacon = (tANI_U8)macHTInfoField3.secondaryBeacon;
    pMac->lim.gHTDualCTSProtection = (tANI_U8)macHTInfoField3.dualCTSProtection;
    pMac->lim.gHTSTBCBasicMCS = (tANI_U8)macHTInfoField3.basicSTBCMCS;

    /*                                                                                                                
                                                                                                         
                                                                                                                                
                                                                                                                           
     */
    if (psessionEntry != NULL)
    {
        psessionEntry->htCapability = IS_DOT11_MODE_HT(psessionEntry->dot11mode);  
        psessionEntry->beaconParams.fLsigTXOPProtectionFullSupport = (tANI_U8)macHTInfoField3.lsigTXOPProtectionFullSupport;
    }
}

void limLogSessionStates(tpAniSirGlobal pMac)
{
#ifdef WLAN_DEBUG
    int i;

    for(i = 0; i < pMac->lim.maxBssId; i++)
    {
        if(pMac->lim.gpSession[i].valid)
        {
            PELOGE(limLog(pMac, LOGE, FL("Session[%d] sysRole(%d) limSmeState %d (prev sme state %d) mlm state %d (prev mlm state %d)\n"),
                   i, pMac->lim.gpSession[i].limSystemRole,  pMac->lim.gpSession[i].limSmeState,  
                   pMac->lim.gpSession[i].limPrevSmeState,   pMac->lim.gpSession[i].limMlmState,  
                   pMac->lim.gpSession[i].limPrevMlmState);)
        }
    }
#endif //                
}
