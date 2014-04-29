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

/**
 * \file limSendManagementFrames.c
 *
 * \brief Code for preparing and sending 802.11 Management frames
 *
 * Copyright (C) 2005-2007 Airgo Networks, Incorporated
 *
 */

#include "sirApi.h"
#include "aniGlobal.h"
#include "sirMacProtDef.h"
#ifdef FEATURE_WLAN_NON_INTEGRATED_SOC
#include "halDataStruct.h"
#endif
#include "cfgApi.h"
#include "utilsApi.h"
#include "limTypes.h"
#include "limUtils.h"
#include "limSecurityUtils.h"
#include "dot11f.h"
#include "limStaHashApi.h"
#include "schApi.h"
#include "limSendMessages.h"
#if defined WLAN_FEATURE_VOWIFI
#include "rrmApi.h"
#endif

#ifdef FEATURE_WLAN_CCX
#include <limCcxparserApi.h>
#endif
#include "wlan_qct_wda.h"
#ifdef WLAN_FEATURE_11W
#include "dot11fdefs.h"
#endif


//                                                                      

//                                                                 
//                
#define CFG_LIM_GET_INT_NO_STATUS(nStatus, pMac, nItem, cfg )      \
    (nStatus) = wlan_cfgGetInt( (pMac), (nItem), & (cfg) );             \
    if ( eSIR_SUCCESS != (nStatus) )                               \
    {                                                              \
        limLog( (pMac), LOGP, FL("Failed to retrieve "             \
                                 #nItem " from CFG (%d).\n"),      \
                (nStatus) );                                       \
        return;                                                    \
    }

//                                                                    
//         
#define CFG_LIM_GET_STR_NO_STATUS(nStatus, pMac, nItem, cfg, nCfg, \
                              nMaxCfg)                             \
    (nCfg) = (nMaxCfg);                                            \
    (nStatus) = wlan_cfgGetStr( (pMac), (nItem), (cfg), & (nCfg) );     \
    if ( eSIR_SUCCESS != (nStatus) )                               \
    {                                                              \
        limLog( (pMac), LOGP, FL("Failed to retrieve "             \
                                 #nItem " from CFG (%d).\n"),      \
                (nStatus) );                                       \
        return;                                                    \
    }

/* 
  
                                                                       
                          
  
  
                                               
  
                                                                   
  
                                
  
                                      
  
                     
  
  
                                                                        
                                                                       
                                                                        
             
  
  
 */

tSirRetStatus limPopulateMacHeader( tpAniSirGlobal pMac,
                             tANI_U8* pBD,
                             tANI_U8 type,
                             tANI_U8 subType,
                             tSirMacAddr peerAddr ,tSirMacAddr selfMacAddr)
{
    tSirRetStatus   statusCode = eSIR_SUCCESS;
    tpSirMacMgmtHdr pMacHdr;
    
    //                               
    pMacHdr = (tpSirMacMgmtHdr) (pBD);

    //           
    pMacHdr->fc.protVer = SIR_MAC_PROTOCOL_VERSION;
    pMacHdr->fc.type    = type;
    pMacHdr->fc.subType = subType;

    //                  
    palCopyMemory( pMac->hHdd,
                   (tANI_U8 *) pMacHdr->da,
                   (tANI_U8 *) peerAddr,
                   sizeof( tSirMacAddr ));

    //                  
    #if 0
    if ((statusCode = wlan_cfgGetStr(pMac, WNI_CFG_STA_ID, (tANI_U8 *) pMacHdr->sa,
                                &cfgLen)) != eSIR_SUCCESS)
    {
        //                                          
        limLog( pMac, LOGP,
                FL("Failed to retrive STA_ID\n"));
        return statusCode;
    }
    #endif//                  
    sirCopyMacAddr(pMacHdr->sa,selfMacAddr);

    //                  
    palCopyMemory( pMac->hHdd,
                   (tANI_U8 *) pMacHdr->bssId,
                   (tANI_U8 *) peerAddr,
                   sizeof( tSirMacAddr ));
    return statusCode;
} /*                                */

/* 
                                  
  
  
                                               
  
                                                       
  
                                                        
  
                                                                          
        
  
                                                                       
  
                                                                                        
  
                                                                                                      
  
                                                                             
                                  
                                                        
                                       
                                       
                                   
                                   
                                                                  
  
  
 */
tSirRetStatus
limSendProbeReqMgmtFrame(tpAniSirGlobal pMac,
                         tSirMacSSid   *pSsid,
                         tSirMacAddr    bssid,
                         tANI_U8        nChannelNum,
                         tSirMacAddr    SelfMacAddr,
                         tANI_U32 dot11mode,
                         tANI_U32 nAdditionalIELen, 
                         tANI_U8 *pAdditionalIE)
{
    tDot11fProbeRequest pr;
    tANI_U32            nStatus, nBytes, nPayload;
    tSirRetStatus       nSirStatus;
    tANI_U8            *pFrame;
    void               *pPacket;
    eHalStatus          halstatus;
    tpPESession         psessionEntry;
    tANI_U8             sessionId;
#ifdef WLAN_FEATURE_P2P
    tANI_U8             *p2pIe = NULL;
#endif
    tANI_U8             txFlag = 0;

#ifndef GEN4_SCAN
    return eSIR_FAILURE;
#endif

#if defined ( ANI_DVT_DEBUG )
    return eSIR_FAILURE;
#endif

    /*
                                                                                         
                            
                                              
                                          
                                      
                                      
                                                                     
                                                                               
                                              
    */
    psessionEntry = peFindSessionByBssid(pMac,bssid,&sessionId);

    //                                                                 
    //                                                      
    //                                                              
    palZeroMemory( pMac->hHdd, ( tANI_U8* )&pr, sizeof( pr ) );

    //                                  
    PopulateDot11fSSID( pMac, pSsid, &pr.SSID );

#ifdef WLAN_FEATURE_P2P
    if( nAdditionalIELen && pAdditionalIE )
    {
        p2pIe = limGetP2pIEPtr(pMac, pAdditionalIE, nAdditionalIELen);
    }
    /*                                                             */
    if( ( WNI_CFG_DOT11_MODE_11B != dot11mode ) && 
        ( p2pIe != NULL ) && 
    /*                                                                                     */
        ( ( ( pMac->lim.gpLimMlmScanReq != NULL ) &&
              pMac->lim.gpLimMlmScanReq->p2pSearch ) || 
          ( ( psessionEntry != NULL ) && 
            ( VOS_P2P_CLIENT_MODE == psessionEntry->pePersona ) )
         )
      )
    {
        /*                                                                 
                                        */
        PopulateDot11fSuppRates( pMac, 15, &pr.SuppRates,psessionEntry);
    }
    else
    {
#endif
        PopulateDot11fSuppRates( pMac, nChannelNum, 
                                               &pr.SuppRates,psessionEntry);

        if ( WNI_CFG_DOT11_MODE_11B != dot11mode )
        {
            PopulateDot11fExtSuppRates1( pMac, nChannelNum, &pr.ExtSuppRates );
        }
#ifdef WLAN_FEATURE_P2P
    }
#endif

#if defined WLAN_FEATURE_VOWIFI
    //                                         
    //                                                                  
    //                                                                      
    //                    
    PopulateDot11fDSParams( pMac, &pr.DSParams, nChannelNum, psessionEntry );
    //                                                        
    {
       tANI_U8 txPower = (tANI_U8) rrmGetMgmtTxPower( pMac, psessionEntry );
       PopulateDot11fWFATPC( pMac, &pr.WFATPC, txPower, 0 );
    }
#endif

    if (psessionEntry != NULL ) {
       psessionEntry->htCapability = IS_DOT11_MODE_HT(dot11mode);
       //                        
       if (psessionEntry->htCapability)
       {
           PopulateDot11fHTCaps( pMac, psessionEntry, &pr.HTCaps );
       }
    } else { //                     
           if (IS_DOT11_MODE_HT(dot11mode))
           {
               PopulateDot11fHTCaps( pMac, psessionEntry, &pr.HTCaps );
           }
    }
#ifdef WLAN_FEATURE_11AC
    if (psessionEntry != NULL ) {
       psessionEntry->vhtCapability = IS_DOT11_MODE_VHT(dot11mode);
       //                        
       if (psessionEntry->vhtCapability)
       {
          PopulateDot11fVHTCaps( pMac, &pr.VHTCaps );
       }
    }  else {
       if (IS_DOT11_MODE_VHT(dot11mode))
       {
          PopulateDot11fVHTCaps( pMac, &pr.VHTCaps );
       }
    }
#endif


    //                                                                   
    //      
    nStatus = dot11fGetPackedProbeRequestSize( pMac, &pr, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to calculate the packed size f"
                               "or a Probe Request (0x%08x).\n"), nStatus );
        //                                            
        nPayload = sizeof( tDot11fProbeRequest );
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while calculating"
                               "the packed size for a Probe Request ("
                               "0x%08x).\n"), nStatus );
    }

    nBytes = nPayload + sizeof( tSirMacMgmtHdr ) + nAdditionalIELen;
  
    //                                  
    halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                             ( tANI_U16 )nBytes, ( void** ) &pFrame,
                             ( void** ) &pPacket );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to allocate %d bytes for a Pro"
                               "be Request.\n"), nBytes );
        return eSIR_MEM_ALLOC_FAILED;
    }

    //          
    palZeroMemory( pMac->hHdd, pFrame, nBytes );

    //                                         
    nSirStatus = limPopulateMacHeader( pMac, pFrame, SIR_MAC_MGMT_FRAME,
                                SIR_MAC_MGMT_PROBE_REQ, bssid ,SelfMacAddr);
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to populate the buffer descrip"
                               "tor for a Probe Request (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                    ( void* ) pFrame, ( void* ) pPacket );
        return nSirStatus;      //           
    }

    //                                   
    nStatus = dot11fPackProbeRequest( pMac, &pr, pFrame +
                                      sizeof( tSirMacMgmtHdr ),
                                      nPayload, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to pack a Probe Request (0x%08x).\n"),
                nStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return eSIR_FAILURE;    //           
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while packing a P"
                               "robe Request (0x%08x).\n") );
    }

    //                             
    if( nAdditionalIELen )
    {
        palCopyMemory( pMac->hHdd, pFrame+sizeof(tSirMacMgmtHdr)+nPayload, 
                                                    pAdditionalIE, nAdditionalIELen );
        nPayload += nAdditionalIELen;
    }

    /*                                                                     
                                
     */
    if( ( SIR_BAND_5_GHZ == limGetRFBand(nChannelNum))
#ifdef WLAN_FEATURE_P2P
      || (( pMac->lim.gpLimMlmScanReq != NULL) &&
          pMac->lim.gpLimMlmScanReq->p2pSearch )
#endif
      ) 
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME; 
    }


    halstatus = halTxFrame( pMac, pPacket, ( tANI_U16 ) sizeof(tSirMacMgmtHdr) + nPayload,
                            HAL_TXRX_FRM_802_11_MGMT,
                            ANI_TXDIR_TODS,
                            7,//                           
                            limTxComplete, pFrame, txFlag );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGE, FL("could not send Probe Request frame!\n" ));
        //                                    
        return eSIR_FAILURE;
    }

    return eSIR_SUCCESS;
} //                              

#ifdef WLAN_FEATURE_P2P
tSirRetStatus limGetAddnIeForProbeResp(tpAniSirGlobal pMac,
                              tANI_U8* addIE, tANI_U16 *addnIELen,
                              tANI_U8 probeReqP2pIe)
{
    /*                                                           
                          */
    if(!probeReqP2pIe)
    {
        tANI_U8* tempbuf = NULL;
        tANI_U16 tempLen = 0;
        int left = *addnIELen;
        v_U8_t *ptr = addIE;
        v_U8_t elem_id, elem_len;

        if(NULL == addIE)
        {
           PELOGE(limLog(pMac, LOGE,
                 FL(" NULL addIE pointer"));)
            return eSIR_FAILURE;
        }

        if( (palAllocateMemory(pMac->hHdd, (void**)&tempbuf,
             left)) != eHAL_STATUS_SUCCESS)
        {
            PELOGE(limLog(pMac, LOGE,
                 FL("Unable to allocate memory to store addn IE"));)
            return eSIR_MEM_ALLOC_FAILED;
        }

        while(left >= 2)
        {
            elem_id  = ptr[0];
            elem_len = ptr[1];
            left -= 2;
            if(elem_len > left)
            {
                limLog( pMac, LOGE,
                   FL("****Invalid IEs eid = %d elem_len=%d left=%d*****\n"),
                                                   elem_id,elem_len,left);
                palFreeMemory(pMac->hHdd, tempbuf);
                return eSIR_FAILURE;
            }
            if ( !( (SIR_MAC_EID_VENDOR == elem_id) &&
                   (memcmp(&ptr[2], SIR_MAC_P2P_OUI, SIR_MAC_P2P_OUI_SIZE)==0) ) )
            {
                palCopyMemory ( pMac->hHdd, tempbuf + tempLen, &ptr[0], elem_len + 2);
                tempLen += (elem_len + 2);
            }
            left -= elem_len;
            ptr += (elem_len + 2);
       }
       palCopyMemory ( pMac->hHdd, addIE, tempbuf, tempLen);
       *addnIELen = tempLen;
       palFreeMemory(pMac->hHdd, tempbuf);
    }
    return eSIR_SUCCESS;
}
#endif

void
limSendProbeRspMgmtFrame(tpAniSirGlobal pMac,
                         tSirMacAddr    peerMacAddr,
                         tpAniSSID      pSsid,
                         short          nStaId,
                         tANI_U8        nKeepAlive,
                         tpPESession psessionEntry,
                         tANI_U8        probeReqP2pIe)
{
    tDot11fProbeResponse *pFrm;
    tSirRetStatus        nSirStatus;
    tANI_U32             cfg, nPayload, nBytes, nStatus;
    tpSirMacMgmtHdr      pMacHdr;
    tANI_U8             *pFrame;
    void                *pPacket;
    eHalStatus           halstatus;
    tANI_U32             addnIEPresent;
    tANI_U32             addnIE1Len=0;
    tANI_U32             addnIE2Len=0;
    tANI_U32             addnIE3Len=0;
    tANI_U16             totalAddnIeLen = 0;
    tANI_U32             wpsApEnable=0, tmp;
    tANI_U8              txFlag = 0;
    tANI_U8              *addIE = NULL;
#ifdef WLAN_FEATURE_P2P
    tANI_U8             *pP2pIe = NULL;
    tANI_U8              noaLen = 0;
    tANI_U8              total_noaLen = 0;
    tANI_U8              noaStream[SIR_MAX_NOA_ATTR_LEN 
                                           + SIR_P2P_IE_HEADER_LEN];
    tANI_U8              noaIe[SIR_MAX_NOA_ATTR_LEN + SIR_P2P_IE_HEADER_LEN];
#endif
  
    if(pMac->gDriverType == eDRIVER_TYPE_MFG)         //                         
    {
        return;                     //              
    }

    if(NULL == psessionEntry)
    {
        return;
    }
    
    if(eHAL_STATUS_SUCCESS != palAllocateMemory(pMac->hHdd, 
                                                (void **)&pFrm, sizeof(tDot11fProbeResponse)))
    {
        limLog(pMac, LOGE, FL("Unable to PAL allocate memory in limSendProbeRspMgmtFrame\n") );
        return;
    }

    //                                                              
    //                           
    palZeroMemory( pMac->hHdd, ( tANI_U8* )pFrm, sizeof( tDot11fProbeResponse ) );

    //                                       

    //                 
#ifdef WLAN_SOFTAP_FEATURE
    if(psessionEntry->limSystemRole == eLIM_AP_ROLE)
    {
        pFrm->BeaconInterval.interval = pMac->sch.schObject.gSchBeaconInterval;        
    }
    else
    {
#endif
    CFG_LIM_GET_INT_NO_STATUS( nSirStatus, pMac,
                               WNI_CFG_BEACON_INTERVAL, cfg );
    pFrm->BeaconInterval.interval = ( tANI_U16 ) cfg;
#ifdef WLAN_SOFTAP_FEATURE
    }
#endif


    PopulateDot11fCapabilities( pMac, &pFrm->Capabilities, psessionEntry );
    PopulateDot11fSSID( pMac, ( tSirMacSSid* )pSsid, &pFrm->SSID );
    PopulateDot11fSuppRates( pMac, POPULATE_DOT11F_RATES_OPERATIONAL,
                             &pFrm->SuppRates,psessionEntry);

    PopulateDot11fDSParams( pMac, &pFrm->DSParams, psessionEntry->currentOperChannel,psessionEntry);
    PopulateDot11fIBSSParams( pMac, &pFrm->IBSSParams, psessionEntry );

#ifdef ANI_PRODUCT_TYPE_AP
    PopulateDot11fCFParams( pMac, &pFrm->Capabilities, &pFrm->CFParams );
#endif //         

#ifdef WLAN_SOFTAP_FEATURE
    if(psessionEntry->limSystemRole == eLIM_AP_ROLE)
    {
        if(psessionEntry->wps_state != SAP_WPS_DISABLED)
        {
            PopulateDot11fProbeResWPSIEs(pMac, &pFrm->WscProbeRes, psessionEntry);
        }
    }
    else
    {
#endif
    if (wlan_cfgGetInt(pMac, (tANI_U16) WNI_CFG_WPS_ENABLE, &tmp) != eSIR_SUCCESS)
        limLog(pMac, LOGP,"Failed to cfg get id %d\n", WNI_CFG_WPS_ENABLE );
    
    wpsApEnable = tmp & WNI_CFG_WPS_ENABLE_AP;
    
    if (wpsApEnable)
    {
        PopulateDot11fWscInProbeRes(pMac, &pFrm->WscProbeRes);
    }

    if (pMac->lim.wscIeInfo.probeRespWscEnrollmentState == eLIM_WSC_ENROLL_BEGIN)
    {
        PopulateDot11fWscRegistrarInfoInProbeRes(pMac, &pFrm->WscProbeRes);
        pMac->lim.wscIeInfo.probeRespWscEnrollmentState = eLIM_WSC_ENROLL_IN_PROGRESS;
    }

    if (pMac->lim.wscIeInfo.wscEnrollmentState == eLIM_WSC_ENROLL_END)
    {
        DePopulateDot11fWscRegistrarInfoInProbeRes(pMac, &pFrm->WscProbeRes);
        pMac->lim.wscIeInfo.probeRespWscEnrollmentState = eLIM_WSC_ENROLL_NOOP;
    }
#ifdef WLAN_SOFTAP_FEATURE
    }
#endif

    PopulateDot11fCountry( pMac, &pFrm->Country, psessionEntry);
    PopulateDot11fEDCAParamSet( pMac, &pFrm->EDCAParamSet, psessionEntry);

#ifdef ANI_PRODUCT_TYPE_AP
    if( pSessionEntry->lim11hEnable )
    {
        PopulateDot11fPowerConstraints( pMac, &pFrm->PowerConstraints );
        PopulateDot11fTPCReport( pMac, &pFrm->TPCReport, psessionEntry);

        //                                                                 
        //                                                                  
        //                                   
        if (( pMac->lim.gLimChannelSwitch.switchCount != 0 ) &&
             ( pMac->lim.gLimChannelSwitch.state ==
               eLIM_CHANNEL_SWITCH_PRIMARY_ONLY ||
               pMac->lim.gLimChannelSwitch.state ==
               eLIM_CHANNEL_SWITCH_PRIMARY_AND_SECONDARY ) )
        {
            PopulateDot11fChanSwitchAnn( pMac, &pFrm->ChanSwitchAnn, psessionEntry );
            PopulateDot11fExtChanSwitchAnn(pMac, &pFrm->ExtChanSwitchAnn, psessionEntry );
        }
    }
#endif

    if (psessionEntry->dot11mode != WNI_CFG_DOT11_MODE_11B)
        PopulateDot11fERPInfo( pMac, &pFrm->ERPInfo, psessionEntry);


    //                                                               
    //                                                                    
    PopulateDot11fExtSuppRates( pMac, POPULATE_DOT11F_RATES_OPERATIONAL,
                                &pFrm->ExtSuppRates, psessionEntry );

    //                                                       
    if ( psessionEntry->htCapability )
    {
        PopulateDot11fHTCaps( pMac, psessionEntry, &pFrm->HTCaps );
#ifdef WLAN_SOFTAP_FEATURE
        PopulateDot11fHTInfo( pMac, &pFrm->HTInfo, psessionEntry );
#else
        PopulateDot11fHTInfo( pMac, &pFrm->HTInfo );
#endif
    }
#ifdef WLAN_FEATURE_11AC
    if(psessionEntry->vhtCapability)
    {
        limLog( pMac, LOGW, FL("Populate VHT IE in Probe Response\n"));
        PopulateDot11fVHTCaps( pMac, &pFrm->VHTCaps );
        PopulateDot11fVHTOperation( pMac, &pFrm->VHTOperation );
        //                                  
        //                                                        
    }
#endif

    if ( psessionEntry->pLimStartBssReq ) 
    {
      PopulateDot11fWPA( pMac, &( psessionEntry->pLimStartBssReq->rsnIE ),
          &pFrm->WPA );
      PopulateDot11fRSN( pMac, &( psessionEntry->pLimStartBssReq->rsnIE ),
          &pFrm->RSN );
    }

    PopulateDot11fWMM( pMac, &pFrm->WMMInfoAp, &pFrm->WMMParams, &pFrm->WMMCaps, psessionEntry );

#if defined(FEATURE_WLAN_WAPI)
    if( psessionEntry->pLimStartBssReq ) 
    {
      PopulateDot11fWAPI( pMac, &( psessionEntry->pLimStartBssReq->rsnIE ),
          &pFrm->WAPI );
    }

#endif //                           


    nStatus = dot11fGetPackedProbeResponseSize( pMac, pFrm, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to calculate the packed size f"
                               "or a Probe Response (0x%08x).\n"),
                nStatus );
        //                                            
        nPayload = sizeof( tDot11fProbeResponse );
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while calculating"
                               "the packed size for a Probe Response "
                               "(0x%08x).\n"), nStatus );
    }

    nBytes = nPayload + sizeof( tSirMacMgmtHdr );

    addnIEPresent = false;
    
#ifdef WLAN_FEATURE_P2P
    if( pMac->lim.gpLimRemainOnChanReq )
    {
        nBytes += (pMac->lim.gpLimRemainOnChanReq->length - sizeof( tSirRemainOnChnReq ) );
    }
    //                                                                         
    //                                                                        
    else
#endif
    {

        if (wlan_cfgGetInt(pMac, WNI_CFG_PROBE_RSP_ADDNIE_FLAG,
                           &addnIEPresent) != eSIR_SUCCESS)
        {
            limLog(pMac, LOGP, FL("Unable to get WNI_CFG_PROBE_RSP_ADDNIE_FLAG"));
            palFreeMemory(pMac->hHdd, pFrm);
            return;
        }
    }

    if (addnIEPresent)
    {
        if( (palAllocateMemory(pMac->hHdd, (void**)&addIE, 
             WNI_CFG_PROBE_RSP_ADDNIE_DATA1_LEN*3 )) != eHAL_STATUS_SUCCESS)
        {
            PELOGE(limLog(pMac, LOGE,
                 FL("Unable to allocate memory to store addn IE"));)
            palFreeMemory(pMac->hHdd, pFrm);
            return;
        }
        
        //                      
        if ( eSIR_SUCCESS != wlan_cfgGetStrLen(pMac,
                                  WNI_CFG_PROBE_RSP_ADDNIE_DATA1, &addnIE1Len) )
        {
            limLog(pMac, LOGP, FL("Unable to get WNI_CFG_PROBE_RSP_ADDNIE_DATA1 length"));
            palFreeMemory(pMac->hHdd, addIE);
            palFreeMemory(pMac->hHdd, pFrm);
            return;
        }
        if (addnIE1Len <= WNI_CFG_PROBE_RSP_ADDNIE_DATA1_LEN && addnIE1Len &&
                     (nBytes + addnIE1Len) <= SIR_MAX_PACKET_SIZE)
        {
            if ( eSIR_SUCCESS != wlan_cfgGetStr(pMac,
                                     WNI_CFG_PROBE_RSP_ADDNIE_DATA1, &addIE[0],
                                     &addnIE1Len) )
            {
                limLog(pMac, LOGP,
                     FL("Unable to get WNI_CFG_PROBE_RSP_ADDNIE_DATA1 String"));
                palFreeMemory(pMac->hHdd, addIE);
                palFreeMemory(pMac->hHdd, pFrm);
                return;
            }
        }

        //                      
        if ( eSIR_SUCCESS != wlan_cfgGetStrLen(pMac,
                                  WNI_CFG_PROBE_RSP_ADDNIE_DATA2, &addnIE2Len) )
        {
            limLog(pMac, LOGP, FL("Unable to get WNI_CFG_PROBE_RSP_ADDNIE_DATA2 length"));
            palFreeMemory(pMac->hHdd, addIE);
            palFreeMemory(pMac->hHdd, pFrm);
            return;
        }
        if (addnIE2Len <= WNI_CFG_PROBE_RSP_ADDNIE_DATA2_LEN && addnIE2Len &&
                     (nBytes + addnIE2Len) <= SIR_MAX_PACKET_SIZE)
        {
            if ( eSIR_SUCCESS != wlan_cfgGetStr(pMac,
                                     WNI_CFG_PROBE_RSP_ADDNIE_DATA2, &addIE[addnIE1Len],
                                     &addnIE2Len) )
            {
                limLog(pMac, LOGP,
                     FL("Unable to get WNI_CFG_PROBE_RSP_ADDNIE_DATA2 String"));
                palFreeMemory(pMac->hHdd, addIE);
                palFreeMemory(pMac->hHdd, pFrm);
                return;
            }
        }

        //                      
        if ( eSIR_SUCCESS != wlan_cfgGetStrLen(pMac,
                                  WNI_CFG_PROBE_RSP_ADDNIE_DATA3, &addnIE3Len) )
        {
            limLog(pMac, LOGP, FL("Unable to get WNI_CFG_PROBE_RSP_ADDNIE_DATA3 length"));
            palFreeMemory(pMac->hHdd, addIE);
            palFreeMemory(pMac->hHdd, pFrm);
            return;
        }
        if (addnIE3Len <= WNI_CFG_PROBE_RSP_ADDNIE_DATA3_LEN && addnIE3Len &&
                     (nBytes + addnIE3Len) <= SIR_MAX_PACKET_SIZE)
        {
            if ( eSIR_SUCCESS != wlan_cfgGetStr(pMac,
                                     WNI_CFG_PROBE_RSP_ADDNIE_DATA3,
                                     &addIE[addnIE1Len + addnIE2Len],
                                     &addnIE3Len) )
            {
                limLog(pMac, LOGP,
                     FL("Unable to get WNI_CFG_PROBE_RSP_ADDNIE_DATA3 String"));
                palFreeMemory(pMac->hHdd, addIE);
                palFreeMemory(pMac->hHdd, pFrm);
                return;
            }
        }
        totalAddnIeLen = addnIE1Len + addnIE2Len + addnIE3Len;

#ifdef WLAN_FEATURE_P2P
        if(eSIR_SUCCESS != limGetAddnIeForProbeResp(pMac, addIE, &totalAddnIeLen, probeReqP2pIe))
        {
            limLog(pMac, LOGP,
                 FL("Unable to get final Additional IE for Probe Req"));
            palFreeMemory(pMac->hHdd, addIE);
                palFreeMemory(pMac->hHdd, pFrm);
            return;
        }
        nBytes = nBytes + totalAddnIeLen;

        if (probeReqP2pIe)
        {
            pP2pIe = limGetP2pIEPtr(pMac, &addIE[0], totalAddnIeLen);
            if (pP2pIe != NULL)
            {
                //                               
                noaLen = limGetNoaAttrStream(pMac, noaStream, psessionEntry);
                if (noaLen != 0)
                {
                    total_noaLen = limBuildP2pIe(pMac, &noaIe[0], 
                                            &noaStream[0], noaLen); 
                    nBytes = nBytes + total_noaLen;
                }
            }
        }
#endif
    }

    halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                             ( tANI_U16 )nBytes, ( void** ) &pFrame,
                             ( void** ) &pPacket );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to allocate %d bytes for a Pro"
                               "be Response.\n"), nBytes );
        if ( addIE != NULL )
        {
            palFreeMemory(pMac->hHdd, addIE);
        }
        palFreeMemory(pMac->hHdd, pFrm);
        return;
    }

    //          
    palZeroMemory( pMac->hHdd, pFrame, nBytes );

    //                                         
    nSirStatus = limPopulateMacHeader( pMac, pFrame, SIR_MAC_MGMT_FRAME,
                                SIR_MAC_MGMT_PROBE_RSP, peerMacAddr,psessionEntry->selfMacAddr);
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to populate the buffer descrip"
                               "tor for a Probe Response (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                    ( void* ) pFrame, ( void* ) pPacket );
        if ( addIE != NULL )
        {
            palFreeMemory(pMac->hHdd, addIE);
        }
        palFreeMemory(pMac->hHdd, pFrm);
        return;
    }

    pMacHdr = ( tpSirMacMgmtHdr ) pFrame;
  
    sirCopyMacAddr(pMacHdr->bssId,psessionEntry->bssId);

    //                                    
    nStatus = dot11fPackProbeResponse( pMac, pFrm, pFrame + sizeof(tSirMacMgmtHdr),
                                       nPayload, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to pack a Probe Response (0x%08x).\n"),
                nStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        if ( addIE != NULL )
        {
            palFreeMemory(pMac->hHdd, addIE);
        }
        palFreeMemory(pMac->hHdd, pFrm);
        return;                 //           
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while packing a P"
                               "robe Response (0x%08x).\n") );
    }

    PELOG3(limLog( pMac, LOG3, FL("Sending Probe Response frame to ") );
    limPrintMacAddr( pMac, peerMacAddr, LOG3 );)

    pMac->sys.probeRespond++;

#ifdef WLAN_FEATURE_P2P
    if( pMac->lim.gpLimRemainOnChanReq )
    {
        palCopyMemory ( pMac->hHdd, pFrame+sizeof(tSirMacMgmtHdr)+nPayload,
          pMac->lim.gpLimRemainOnChanReq->probeRspIe, (pMac->lim.gpLimRemainOnChanReq->length - sizeof( tSirRemainOnChnReq )) );
    }
#endif

    if ( addnIEPresent )
    {
        if (palCopyMemory ( pMac->hHdd, pFrame+sizeof(tSirMacMgmtHdr)+nPayload,
             &addIE[0], totalAddnIeLen) != eHAL_STATUS_SUCCESS)
        {
            limLog(pMac, LOGP, FL("Additional Probe Rp IE request failed while Appending: %x"),halstatus);
            palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                            ( void* ) pFrame, ( void* ) pPacket );
            if ( addIE != NULL )
            {
                palFreeMemory(pMac->hHdd, addIE);
            }
            palFreeMemory(pMac->hHdd, pFrm);
            return;
        }
    }
#ifdef WLAN_FEATURE_P2P
    if (noaLen != 0)
    {
        if (palCopyMemory ( pMac->hHdd, &pFrame[nBytes - (total_noaLen)],
                            &noaIe[0], total_noaLen) != eHAL_STATUS_SUCCESS)
        {
            limLog(pMac, LOGE,
                  FL("Not able to insert NoA because of length constraint"));
        }
    }
#endif

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }

    //                                               
    halstatus = halTxFrame( ( tHalHandle ) pMac, pPacket,
                            ( tANI_U16 ) nBytes,
                            HAL_TXRX_FRM_802_11_MGMT,
                            ANI_TXDIR_TODS,
                            7,//                          
                            limTxComplete, pFrame, txFlag );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGE, FL("Could not send Probe Response.\n") );
        //                                    
    }

    if ( addIE != NULL )
    {
        palFreeMemory(pMac->hHdd, addIE);
    }

    palFreeMemory(pMac->hHdd, pFrm);
    return;


} //                              

void
limSendAddtsReqActionFrame(tpAniSirGlobal    pMac,
                           tSirMacAddr       peerMacAddr,
                           tSirAddtsReqInfo *pAddTS,
                           tpPESession       psessionEntry)
{
    tANI_U16               i;
    tANI_U8               *pFrame;
    tSirRetStatus          nSirStatus;
    tDot11fAddTSRequest    AddTSReq;
    tDot11fWMMAddTSRequest WMMAddTSReq;
    tANI_U32               nPayload, nBytes, nStatus;
    tpSirMacMgmtHdr        pMacHdr;
    void                  *pPacket;
#ifdef FEATURE_WLAN_CCX
    tANI_U32               phyMode;
#endif
    eHalStatus             halstatus;
    tANI_U8                txFlag = 0;

    if(NULL == psessionEntry)
    {
           return;
    }

    if ( ! pAddTS->wmeTspecPresent )
    {
        palZeroMemory( pMac->hHdd, ( tANI_U8* )&AddTSReq, sizeof( AddTSReq ) );

        AddTSReq.Action.action     = SIR_MAC_QOS_ADD_TS_REQ;
        AddTSReq.DialogToken.token = pAddTS->dialogToken;
        AddTSReq.Category.category = SIR_MAC_ACTION_QOS_MGMT;
        if ( pAddTS->lleTspecPresent )
        {
            PopulateDot11fTSPEC( &pAddTS->tspec, &AddTSReq.TSPEC );
        }
        else
        {
            PopulateDot11fWMMTSPEC( &pAddTS->tspec, &AddTSReq.WMMTSPEC );
        }

        if ( pAddTS->lleTspecPresent )
        {
            AddTSReq.num_WMMTCLAS = 0;
            AddTSReq.num_TCLAS = pAddTS->numTclas;
            for ( i = 0; i < pAddTS->numTclas; ++i)
            {
                PopulateDot11fTCLAS( pMac, &pAddTS->tclasInfo[i],
                                     &AddTSReq.TCLAS[i] );
            }
        }
        else
        {
            AddTSReq.num_TCLAS = 0;
            AddTSReq.num_WMMTCLAS = pAddTS->numTclas;
            for ( i = 0; i < pAddTS->numTclas; ++i)
            {
                PopulateDot11fWMMTCLAS( pMac, &pAddTS->tclasInfo[i],
                                        &AddTSReq.WMMTCLAS[i] );
            }
        }

        if ( pAddTS->tclasProcPresent )
        {
            if ( pAddTS->lleTspecPresent )
            {
                AddTSReq.TCLASSPROC.processing = pAddTS->tclasProc;
                AddTSReq.TCLASSPROC.present    = 1;
            }
            else
            {
                AddTSReq.WMMTCLASPROC.version    = 1;
                AddTSReq.WMMTCLASPROC.processing = pAddTS->tclasProc;
                AddTSReq.WMMTCLASPROC.present    = 1;
            }
        }

        nStatus = dot11fGetPackedAddTSRequestSize( pMac, &AddTSReq, &nPayload );
        if ( DOT11F_FAILED( nStatus ) )
        {
            limLog( pMac, LOGP, FL("Failed to calculate the packed size f"
                                   "or an Add TS Request (0x%08x).\n"),
                    nStatus );
            //                                            
            nPayload = sizeof( tDot11fAddTSRequest );
        }
        else if ( DOT11F_WARNED( nStatus ) )
        {
            limLog( pMac, LOGW, FL("There were warnings while calculating"
                                   "the packed size for an Add TS Request"
                                   " (0x%08x).\n"), nStatus );
        }
    }
    else
    {
        palZeroMemory( pMac->hHdd, ( tANI_U8* )&WMMAddTSReq, sizeof( WMMAddTSReq ) );

        WMMAddTSReq.Action.action     = SIR_MAC_QOS_ADD_TS_REQ;
        WMMAddTSReq.DialogToken.token = pAddTS->dialogToken;
        WMMAddTSReq.Category.category = SIR_MAC_ACTION_WME;

        //                                                                   
        WMMAddTSReq.StatusCode.statusCode = 0;

        PopulateDot11fWMMTSPEC( &pAddTS->tspec, &WMMAddTSReq.WMMTSPEC );
#ifdef FEATURE_WLAN_CCX
        limGetPhyMode(pMac, &phyMode, psessionEntry);

        if( phyMode == WNI_CFG_PHY_MODE_11G || phyMode == WNI_CFG_PHY_MODE_11A)
        {
            pAddTS->tsrsIE.rates[0] = TSRS_11AG_RATE_6MBPS;
        }
        else 
        {
            pAddTS->tsrsIE.rates[0] = TSRS_11B_RATE_5_5MBPS;
        }
        PopulateDot11TSRSIE(pMac,&pAddTS->tsrsIE, &WMMAddTSReq.CCXTrafStrmRateSet,sizeof(tANI_U8));
#endif
        //               

        nStatus = dot11fGetPackedWMMAddTSRequestSize( pMac, &WMMAddTSReq, &nPayload );
        if ( DOT11F_FAILED( nStatus ) )
        {
            limLog( pMac, LOGP, FL("Failed to calculate the packed size f"
                                   "or a WMM Add TS Request (0x%08x).\n"),
                    nStatus );
            //                                            
            nPayload = sizeof( tDot11fAddTSRequest );
        }
        else if ( DOT11F_WARNED( nStatus ) )
        {
            limLog( pMac, LOGW, FL("There were warnings while calculating"
                                   "the packed size for a WMM Add TS Requ"
                                   "est (0x%08x).\n"), nStatus );
        }
    }

    nBytes = nPayload + sizeof( tSirMacMgmtHdr );

    halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                             ( tANI_U16 )nBytes, ( void** ) &pFrame,
                             ( void** ) &pPacket );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to allocate %d bytes for an Ad"
                               "d TS Request.\n"), nBytes );
        return;
    }

    //          
    palZeroMemory( pMac->hHdd, pFrame, nBytes );

    //                                         
    nSirStatus = limPopulateMacHeader( pMac, pFrame, SIR_MAC_MGMT_FRAME,
                                SIR_MAC_MGMT_ACTION, peerMacAddr,psessionEntry->selfMacAddr);
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to populate the buffer descrip"
                               "tor for an Add TS Request (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                    ( void* ) pFrame, ( void* ) pPacket );
        return;
    }

    pMacHdr = ( tpSirMacMgmtHdr ) pFrame;

    #if 0
    cfgLen = SIR_MAC_ADDR_LENGTH;
    if ( eSIR_SUCCESS != wlan_cfgGetStr( pMac, WNI_CFG_BSSID,
                                    ( tANI_U8* )pMacHdr->bssId, &cfgLen ) )
    {
        limLog( pMac, LOGP, FL("Failed to retrieve WNI_CFG_BSSID whil"
                               "e sending an Add TS Request.\n") );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                    ( void* ) pFrame, ( void* ) pPacket );
        return;
    }
    #endif //                 
    
    sirCopyMacAddr(pMacHdr->bssId,psessionEntry->bssId);

    //                            
    if ( ! pAddTS->wmeTspecPresent )
    {
        nStatus = dot11fPackAddTSRequest( pMac, &AddTSReq,
                                          pFrame + sizeof(tSirMacMgmtHdr),
                                          nPayload, &nPayload );
        if ( DOT11F_FAILED( nStatus ) )
        {
            limLog( pMac, LOGE, FL("Failed to pack an Add TS Request "
                                   "(0x%08x).\n"),
                    nStatus );
            palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
            return;             //           
        }
        else if ( DOT11F_WARNED( nStatus ) )
        {
            limLog( pMac, LOGW, FL("There were warnings while packing"
                                   "an Add TS Request (0x%08x).\n") );
        }
    }
    else
    {
        nStatus = dot11fPackWMMAddTSRequest( pMac, &WMMAddTSReq,
                                             pFrame + sizeof(tSirMacMgmtHdr),
                                             nPayload, &nPayload );
        if ( DOT11F_FAILED( nStatus ) )
        {
            limLog( pMac, LOGE, FL("Failed to pack a WMM Add TS Reque"
                                   "st (0x%08x).\n"),
                    nStatus );
            palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
            return;            //           
        }
        else if ( DOT11F_WARNED( nStatus ) )
        {
            limLog( pMac, LOGW, FL("There were warnings while packing"
                                   "a WMM Add TS Request (0x%08x).\n") );
        }
    }

    PELOG3(limLog( pMac, LOG3, FL("Sending an Add TS Request frame to ") );
    limPrintMacAddr( pMac, peerMacAddr, LOG3 );)

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }

    //                                               
    halstatus = halTxFrame( pMac, pPacket, ( tANI_U16 ) nBytes,
                            HAL_TXRX_FRM_802_11_MGMT,
                            ANI_TXDIR_TODS,
                            7,//                           
                            limTxComplete, pFrame, txFlag );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGE, FL( "*** Could not send an Add TS Request"
                                " (%X) ***\n" ), halstatus );
        //                                    
    }

} //                                

/*                                                  */
#ifdef ANI_PRODUCT_TYPE_AP

void
limSendAssocRspMgmtFrame(tpAniSirGlobal pMac,
                         tANI_U16       statusCode,
                         tANI_U16       aid,
                         tSirMacAddr    peerMacAddr,
                         tANI_U8        subType,
                         tpDphHashNode  pSta,
                         tpPESession psessionEntry)
{
    tDot11fAssocResponse frm;
    tANI_U8             *pFrame, *macAddr;
    tpSirMacMgmtHdr      pMacHdr;
    tSirRetStatus        nSirStatus;
    tANI_U8              lleMode = 0, fAddTS, edcaInclude = 0;
    tHalBitVal           qosMode, wmeMode;
    tANI_U32             nPayload, nBytes, nStatus, cfgLen;
    void                *pPacket;
    eHalStatus           halstatus;
    tUpdateBeaconParams beaconParams;
    tANI_U32             wpsApEnable=0, tmp;
    tANI_U8              txFlag = 0;

    palZeroMemory( pMac->hHdd, ( tANI_U8* )&frm, sizeof( frm ) );

    limGetQosMode(pMac, &qosMode);
    limGetWmeMode(pMac, &wmeMode);

    //                                                                    
    //                         
    fAddTS = ( qosMode && pSta && pSta->qos.addtsPresent ) ? 1 : 0;

    PopulateDot11fCapabilities( pMac, &frm.Capabilities, psessionEntry);

    frm.Status.status = statusCode;

    frm.AID.associd = aid | LIM_AID_MASK;

    PopulateDot11fSuppRates( pMac, POPULATE_DOT11F_RATES_OPERATIONAL, &frm.SuppRates );

    if (wlan_cfgGetInt(pMac, (tANI_U16) WNI_CFG_WPS_ENABLE, &tmp) != eSIR_SUCCESS)
        limLog(pMac, LOGP,"Failed to cfg get id %d\n", WNI_CFG_WPS_ENABLE );
    
    wpsApEnable = tmp & WNI_CFG_WPS_ENABLE_AP;

    if (wpsApEnable)
    {
        PopulateDot11fWscInAssocRes(pMac, &frm.WscAssocRes);
    }

    PopulateDot11fExtSuppRates( pMac, POPULATE_DOT11F_RATES_OPERATIONAL,
                                &frm.ExtSuppRates, psessionEntry );

    if ( NULL != pSta )
    {
        if ( eHAL_SET == qosMode )
        {
            if ( pSta->lleEnabled )
            {
                lleMode = 1;
                if ( ( ! pSta->aniPeer ) || ( ! PROP_CAPABILITY_GET( 11EQOS, pSta->propCapability ) ) )
                {
                    PopulateDot11fEDCAParamSet( pMac, &frm.EDCAParamSet, psessionEntry);

//                                   
//                                  
//                      
//                                              
//                                                         
//                                       
//                                                                                                
//                                                                            
//                                           
                }
            } //                                  
        } //                       

        if ( ( ! lleMode ) && ( eHAL_SET == wmeMode ) && pSta->wmeEnabled )
        {
            if ( ( ! pSta->aniPeer ) || ( ! PROP_CAPABILITY_GET( WME, pSta->propCapability ) ) )
            {
                PopulateDot11fWMMParams( pMac, &frm.WMMParams );

                if ( pSta->wsmEnabled )
                {
                    PopulateDot11fWMMCaps(&frm.WMMCaps );
                }
            }
        }

        if ( pSta->aniPeer )
        {
            if ( ( lleMode && PROP_CAPABILITY_GET( 11EQOS, pSta->propCapability ) ) ||
                 ( pSta->wmeEnabled && PROP_CAPABILITY_GET( WME, pSta->propCapability ) ) )
            {
                edcaInclude = 1;
            }

        } //                      

        if ( pSta->mlmStaContext.htCapability  && 
             psessionEntry->htCapability )
        {
            PopulateDot11fHTCaps( pMac, psessionEntry, &frm.HTCaps );
            PopulateDot11fHTInfo( pMac, &frm.HTInfo, psessionEntry);
        }
    } //                           


    if(pMac->lim.gLimProtectionControl != WNI_CFG_FORCE_POLICY_PROTECTION_DISABLE)
        limDecideApProtection(pMac, peerMacAddr, &beaconParams);
    limUpdateShortPreamble(pMac, peerMacAddr, &beaconParams);
    limUpdateShortSlotTime(pMac, peerMacAddr, &beaconParams);

    //                                                  
    if(beaconParams.paramChangeBitmap)
    {
        schSetFixedBeaconFields(pMac,psessionEntry);
        limSendBeaconParams(pMac, &beaconParams, psessionEntry );
    }

    //                                  
    nStatus = dot11fGetPackedAssocResponseSize( pMac, &frm, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to calculate the packed size f"
                               "or an Association Response (0x%08x).\n"),
                nStatus );
        return;
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while calculating"
                               "the packed size for an Association Re"
                               "sponse (0x%08x).\n"), nStatus );
    }

    nBytes = sizeof( tSirMacMgmtHdr ) + nPayload;

    halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                             ( tANI_U16 )nBytes, ( void** ) &pFrame,
                             ( void** ) &pPacket );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog(pMac, LOGP, FL("Call to bufAlloc failed for RE/ASSOC RSP.\n"));
        return;
    }

    //          
    palZeroMemory( pMac->hHdd, pFrame, nBytes );

    //                                         
    nSirStatus = limPopulateMacHeader( pMac,
                                pFrame,
                                SIR_MAC_MGMT_FRAME,
                                ( LIM_ASSOC == subType ) ?
                                    SIR_MAC_MGMT_ASSOC_RSP :
                                    SIR_MAC_MGMT_REASSOC_RSP,
                                    peerMacAddr);
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to populate the buffer descrip"
                               "tor for an Association Response (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                    ( void* ) pFrame, ( void* ) pPacket );
        return;
    }

    pMacHdr = ( tpSirMacMgmtHdr ) pFrame;

   
    cfgLen = SIR_MAC_ADDR_LENGTH;
    if ( eSIR_SUCCESS != wlan_cfgGetStr( pMac, WNI_CFG_BSSID,
                                    ( tANI_U8* )pMacHdr->bssId, &cfgLen ) )
    {
        limLog( pMac, LOGP, FL("Failed to retrieve WNI_CFG_BSSID whil"
                               "e sending an Association Response.\n") );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return;                 //           
    }
  
    nStatus = dot11fPackAssocResponse( pMac, &frm,
                                       pFrame + sizeof( tSirMacMgmtHdr ),
                                       nPayload, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to pack an Association Response (0x%08x).\n"),
                nStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                    ( void* ) pFrame, ( void* ) pPacket );
        return;                 //           
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while packing an "
                               "Association Response (0x%08x).\n") );
    }

    macAddr = pMacHdr->da;

    if (subType == LIM_ASSOC)
        limLog(pMac, LOG1,
               FL("*** Sending Assoc Resp status %d aid %d to "),
               statusCode, aid);
    else
        limLog(pMac, LOG1,
               FL("*** Sending ReAssoc Resp status %d aid %d to "),
               statusCode, aid);
    limPrintMacAddr(pMac, pMacHdr->da, LOG1);

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }

    //                                                      
    halstatus = halTxFrame( pMac, pPacket, ( tANI_U16 ) nBytes,
                            HAL_TXRX_FRM_802_11_MGMT,
                            ANI_TXDIR_TODS,
                            7,//                           
                            limTxComplete, pFrame, txFlag );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog(pMac, LOGE,
               FL("*** Could not Send Re/AssocRsp, retCode=%X ***\n"),
               nSirStatus);

        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                  (void *) pFrame, (void *) pPacket );
    }

    //                                  
    //                                                         
    //                              
    limUtilCountStaAdd(pMac, pSta, psessionEntry);

} //                              


#endif  //                    


void
limSendAssocRspMgmtFrame(tpAniSirGlobal pMac,
                         tANI_U16       statusCode,
                         tANI_U16       aid,
                         tSirMacAddr    peerMacAddr,
                         tANI_U8        subType,
                         tpDphHashNode  pSta,tpPESession psessionEntry)
{
    static tDot11fAssocResponse frm;
    tANI_U8             *pFrame, *macAddr;
    tpSirMacMgmtHdr      pMacHdr;
    tSirRetStatus        nSirStatus;
    tANI_U8              lleMode = 0, fAddTS, edcaInclude = 0;
    tHalBitVal           qosMode, wmeMode;
    tANI_U32             nPayload, nBytes, nStatus;
    void                *pPacket;
    eHalStatus           halstatus;
    tUpdateBeaconParams beaconParams;
    tANI_U8              txFlag = 0;
    tANI_U32             addnIEPresent = false;
    tANI_U32             addnIELen=0;
    tANI_U8              addIE[WNI_CFG_ASSOC_RSP_ADDNIE_DATA_LEN];
    tpSirAssocReq        pAssocReq = NULL; 

    if(NULL == psessionEntry)
    {
        return;
    }

    palZeroMemory( pMac->hHdd, ( tANI_U8* )&frm, sizeof( frm ) );

    limGetQosMode(psessionEntry, &qosMode);
    limGetWmeMode(psessionEntry, &wmeMode);

    //                                                                    
    //                         
    fAddTS = ( qosMode && pSta && pSta->qos.addtsPresent ) ? 1 : 0;

    PopulateDot11fCapabilities( pMac, &frm.Capabilities, psessionEntry );

    frm.Status.status = statusCode;

    frm.AID.associd = aid | LIM_AID_MASK;

    if ( NULL == pSta )
    {
       PopulateDot11fSuppRates( pMac, POPULATE_DOT11F_RATES_OPERATIONAL, &frm.SuppRates,psessionEntry);
       PopulateDot11fExtSuppRates( pMac, POPULATE_DOT11F_RATES_OPERATIONAL, &frm.ExtSuppRates, psessionEntry );
    }
    else
    {
       PopulateDot11fAssocRspRates( pMac, &frm.SuppRates, &frm.ExtSuppRates,
                      pSta->supportedRates.llbRates, pSta->supportedRates.llaRates );
    }

#ifdef WLAN_SOFTAP_FEATURE
    if(psessionEntry->limSystemRole == eLIM_AP_ROLE)
    {
        if( pSta != NULL && eSIR_SUCCESS == statusCode )
        {
            pAssocReq = 
                (tpSirAssocReq) psessionEntry->parsedAssocReq[pSta->assocId];
#ifdef WLAN_FEATURE_P2P
            /*                                                                         */
            if( pAssocReq != NULL && pAssocReq->addIEPresent ) {
                PopulateDot11AssocResP2PIE(pMac, &frm.P2PAssocRes, pAssocReq);
            }
#endif
        }
    }
#endif

    if ( NULL != pSta )
    {
        if ( eHAL_SET == qosMode )
        {
            if ( pSta->lleEnabled )
            {
                lleMode = 1;
                if ( ( ! pSta->aniPeer ) || ( ! PROP_CAPABILITY_GET( 11EQOS, pSta->propCapability ) ) )
                {
                    PopulateDot11fEDCAParamSet( pMac, &frm.EDCAParamSet, psessionEntry);

//                                   
//                                  
//                      
//                                              
//                                                         
//                                       
//                                                                                                
//                                                                            
//                                           
                }
            } //                                  
        } //                       

        if ( ( ! lleMode ) && ( eHAL_SET == wmeMode ) && pSta->wmeEnabled )
        {
            if ( ( ! pSta->aniPeer ) || ( ! PROP_CAPABILITY_GET( WME, pSta->propCapability ) ) )
            {

#ifdef WLAN_SOFTAP_FEATURE
                PopulateDot11fWMMParams( pMac, &frm.WMMParams, psessionEntry);
#else
                PopulateDot11fWMMParams( pMac, &frm.WMMParams );
#endif

                if ( pSta->wsmEnabled )
                {
                    PopulateDot11fWMMCaps(&frm.WMMCaps );
                }
            }
        }

        if ( pSta->aniPeer )
        {
            if ( ( lleMode && PROP_CAPABILITY_GET( 11EQOS, pSta->propCapability ) ) ||
                 ( pSta->wmeEnabled && PROP_CAPABILITY_GET( WME, pSta->propCapability ) ) )
            {
                edcaInclude = 1;
            }

        } //                      

        if ( pSta->mlmStaContext.htCapability  && 
             psessionEntry->htCapability )
        {
            PopulateDot11fHTCaps( pMac, psessionEntry, &frm.HTCaps );
#ifdef WLAN_SOFTAP_FEATURE
            PopulateDot11fHTInfo( pMac, &frm.HTInfo, psessionEntry );
#else
            PopulateDot11fHTInfo( pMac, &frm.HTInfo );
#endif
        }

#ifdef WLAN_FEATURE_11AC
        if( pSta->mlmStaContext.vhtCapability && 
            psessionEntry->vhtCapability )
        {
            limLog( pMac, LOGW, FL("Populate VHT IEs in Assoc Response\n"));
            PopulateDot11fVHTCaps( pMac, &frm.VHTCaps );
            PopulateDot11fVHTOperation( pMac, &frm.VHTOperation);
        }
#endif

    } //                           


   palZeroMemory( pMac->hHdd, ( tANI_U8* )&beaconParams, sizeof( tUpdateBeaconParams) );

#ifdef WLAN_SOFTAP_FEATURE
    if( psessionEntry->limSystemRole == eLIM_AP_ROLE ){
        if(psessionEntry->gLimProtectionControl != WNI_CFG_FORCE_POLICY_PROTECTION_DISABLE)
        limDecideApProtection(pMac, peerMacAddr, &beaconParams,psessionEntry);
    }
#endif

    limUpdateShortPreamble(pMac, peerMacAddr, &beaconParams, psessionEntry);
    limUpdateShortSlotTime(pMac, peerMacAddr, &beaconParams, psessionEntry);

    beaconParams.bssIdx = psessionEntry->bssIdx;

    //                                                  
    if(beaconParams.paramChangeBitmap)
    {
        schSetFixedBeaconFields(pMac,psessionEntry);
        limSendBeaconParams(pMac, &beaconParams, psessionEntry );
    }

    //                                  
    nStatus = dot11fGetPackedAssocResponseSize( pMac, &frm, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to calculate the packed size f"
                               "or an Association Response (0x%08x).\n"),
                nStatus );
        return;
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while calculating"
                               "the packed size for an Association Re"
                               "sponse (0x%08x).\n"), nStatus );
    }

    nBytes = sizeof( tSirMacMgmtHdr ) + nPayload;

    if ( pAssocReq != NULL ) 
    {
        if (wlan_cfgGetInt(pMac, WNI_CFG_ASSOC_RSP_ADDNIE_FLAG, 
                    &addnIEPresent) != eSIR_SUCCESS)
        {
            limLog(pMac, LOGP, FL("Unable to get WNI_CFG_ASSOC_RSP_ADDNIE_FLAG"));
            return;
        }

        if (addnIEPresent)
        {
            //                      
            if (wlan_cfgGetStrLen(pMac, WNI_CFG_ASSOC_RSP_ADDNIE_DATA,
                        &addnIELen) != eSIR_SUCCESS)
            {
                limLog(pMac, LOGP, FL("Unable to get WNI_CFG_ASSOC_RSP_ADDNIE_DATA length"));
                return;
            }

            if (addnIELen <= WNI_CFG_ASSOC_RSP_ADDNIE_DATA_LEN && addnIELen &&
                    (nBytes + addnIELen) <= SIR_MAX_PACKET_SIZE)
            {
                if (wlan_cfgGetStr(pMac, WNI_CFG_ASSOC_RSP_ADDNIE_DATA,
                            &addIE[0], &addnIELen) == eSIR_SUCCESS)
                {
                    nBytes = nBytes + addnIELen;
                }
            }
        }
    }

    halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                             ( tANI_U16 )nBytes, ( void** ) &pFrame,
                             ( void** ) &pPacket );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog(pMac, LOGP, FL("Call to bufAlloc failed for RE/ASSOC RSP.\n"));
        return;
    }

    //          
    palZeroMemory( pMac->hHdd, pFrame, nBytes );

    //                                         
    nSirStatus = limPopulateMacHeader( pMac,
                                pFrame,
                                SIR_MAC_MGMT_FRAME,
                                ( LIM_ASSOC == subType ) ?
                                    SIR_MAC_MGMT_ASSOC_RSP :
                                    SIR_MAC_MGMT_REASSOC_RSP,
                                peerMacAddr,psessionEntry->selfMacAddr);
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to populate the buffer descrip"
                               "tor for an Association Response (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                    ( void* ) pFrame, ( void* ) pPacket );
        return;
    }

    pMacHdr = ( tpSirMacMgmtHdr ) pFrame;

    #if 0
    cfgLen = SIR_MAC_ADDR_LENGTH;
    if ( eSIR_SUCCESS != cfgGetStr( pMac, WNI_CFG_BSSID,
                                    ( tANI_U8* )pMacHdr->bssId, &cfgLen ) )
    {
        limLog( pMac, LOGP, FL("Failed to retrieve WNI_CFG_BSSID whil"
                               "e sending an Association Response.\n") );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return;                 //           
    }
    #endif //                 
    sirCopyMacAddr(pMacHdr->bssId,psessionEntry->bssId);

    nStatus = dot11fPackAssocResponse( pMac, &frm,
                                       pFrame + sizeof( tSirMacMgmtHdr ),
                                       nPayload, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to pack an Association Response (0x%08x).\n"),
                nStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                    ( void* ) pFrame, ( void* ) pPacket );
        return;                 //           
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while packing an "
                               "Association Response (0x%08x).\n") );
    }

    macAddr = pMacHdr->da;

    if (subType == LIM_ASSOC)
    {
        PELOG1(limLog(pMac, LOG1,
               FL("*** Sending Assoc Resp status %d aid %d to "),
               statusCode, aid);)
    }    
    else{
        PELOG1(limLog(pMac, LOG1,
               FL("*** Sending ReAssoc Resp status %d aid %d to "),
               statusCode, aid);)
    }
    PELOG1(limPrintMacAddr(pMac, pMacHdr->da, LOG1);)

    if ( addnIEPresent )
    {
        if (palCopyMemory ( pMac->hHdd, pFrame+sizeof(tSirMacMgmtHdr)+nPayload,
                           &addIE[0], addnIELen ) != eHAL_STATUS_SUCCESS)
        {
            limLog(pMac, LOGP, FL("Additional Assoc IEs request failed while Appending: %x\n"),halstatus);
            palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                       ( void* ) pFrame, ( void* ) pPacket );
            return;
        }
    }

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }

    //                                                      
    halstatus = halTxFrame( pMac, pPacket, ( tANI_U16 ) nBytes,
                            HAL_TXRX_FRM_802_11_MGMT,
                            ANI_TXDIR_TODS,
                            7,//                           
                            limTxComplete, pFrame, txFlag );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog(pMac, LOGE,
               FL("*** Could not Send Re/AssocRsp, retCode=%X ***\n"),
               nSirStatus);

        //                                    
    }

    //                                  
    //                                                         
    //                              
    limUtilCountStaAdd(pMac, pSta, psessionEntry);

} //                              


 
void
limSendAddtsRspActionFrame(tpAniSirGlobal     pMac,
                           tSirMacAddr        peer,
                           tANI_U16           nStatusCode,
                           tSirAddtsReqInfo  *pAddTS,
                           tSirMacScheduleIE *pSchedule,
                           tpPESession        psessionEntry)
{
    tANI_U8                *pFrame;
    tpSirMacMgmtHdr         pMacHdr;
    tDot11fAddTSResponse    AddTSRsp;
    tDot11fWMMAddTSResponse WMMAddTSRsp;
    tSirRetStatus           nSirStatus;
    tANI_U32                i, nBytes, nPayload, nStatus;
    void                   *pPacket;
    eHalStatus              halstatus;
    tANI_U8                 txFlag = 0;

    if(NULL == psessionEntry)
    {
              return;
    }

    if ( ! pAddTS->wmeTspecPresent )
    {
        palZeroMemory( pMac->hHdd, ( tANI_U8* )&AddTSRsp, sizeof( AddTSRsp ) );

        AddTSRsp.Category.category = SIR_MAC_ACTION_QOS_MGMT;
        AddTSRsp.Action.action     = SIR_MAC_QOS_ADD_TS_RSP;
        AddTSRsp.DialogToken.token = pAddTS->dialogToken;
        AddTSRsp.Status.status     = nStatusCode;

        //                                                                 
        //             
        if ( eSIR_MAC_TS_NOT_CREATED_STATUS == nStatusCode )
        {
            if ( pAddTS->wsmTspecPresent )
            {
                AddTSRsp.WMMTSDelay.version = 1;
                AddTSRsp.WMMTSDelay.delay   = 10;
                AddTSRsp.WMMTSDelay.present = 1;
            }
            else
            {
                AddTSRsp.TSDelay.delay   = 10;
                AddTSRsp.TSDelay.present = 1;
            }
        }

        if ( pAddTS->wsmTspecPresent )
        {
            PopulateDot11fWMMTSPEC( &pAddTS->tspec, &AddTSRsp.WMMTSPEC );
        }
        else
        {
            PopulateDot11fTSPEC( &pAddTS->tspec, &AddTSRsp.TSPEC );
        }

        if ( pAddTS->wsmTspecPresent )
        {
            AddTSRsp.num_WMMTCLAS = 0;
            AddTSRsp.num_TCLAS = pAddTS->numTclas;
            for ( i = 0; i < AddTSRsp.num_TCLAS; ++i)
            {
                PopulateDot11fTCLAS( pMac, &pAddTS->tclasInfo[i],
                                     &AddTSRsp.TCLAS[i] );
            }
        }
        else
        {
            AddTSRsp.num_TCLAS = 0;
            AddTSRsp.num_WMMTCLAS = pAddTS->numTclas;
            for ( i = 0; i < AddTSRsp.num_WMMTCLAS; ++i)
            {
                PopulateDot11fWMMTCLAS( pMac, &pAddTS->tclasInfo[i],
                                        &AddTSRsp.WMMTCLAS[i] );
            }
        }

        if ( pAddTS->tclasProcPresent )
        {
            if ( pAddTS->wsmTspecPresent )
            {
                AddTSRsp.WMMTCLASPROC.version    = 1;
                AddTSRsp.WMMTCLASPROC.processing = pAddTS->tclasProc;
                AddTSRsp.WMMTCLASPROC.present    = 1;
            }
            else
            {
                AddTSRsp.TCLASSPROC.processing = pAddTS->tclasProc;
                AddTSRsp.TCLASSPROC.present    = 1;
            }
        }

        //                                                                       
        //                                   
        //                                                                     
        //                                                                    
        //                                                                      
        //                  
        if ((pSchedule != NULL) &&
            ((pAddTS->tspec.tsinfo.traffic.accessPolicy == SIR_MAC_ACCESSPOLICY_HCCA) ||
             (pAddTS->tspec.tsinfo.traffic.accessPolicy == SIR_MAC_ACCESSPOLICY_BOTH)))
        {
            if ( pAddTS->wsmTspecPresent )
            {
                PopulateDot11fWMMSchedule( pSchedule, &AddTSRsp.WMMSchedule );
            }
            else
            {
                PopulateDot11fSchedule( pSchedule, &AddTSRsp.Schedule );
            }
        }

        nStatus = dot11fGetPackedAddTSResponseSize( pMac, &AddTSRsp, &nPayload );
        if ( DOT11F_FAILED( nStatus ) )
        {
            limLog( pMac, LOGP, FL("Failed to calculate the packed si"
                                   "ze for an Add TS Response (0x%08x).\n"),
                    nStatus );
            //                                            
            nPayload = sizeof( tDot11fAddTSResponse );
        }
        else if ( DOT11F_WARNED( nStatus ) )
        {
            limLog( pMac, LOGW, FL("There were warnings while calcula"
                                   "tingthe packed size for an Add TS"
                                   " Response (0x%08x).\n"), nStatus );
        }
    }
    else
    {
        palZeroMemory( pMac->hHdd, ( tANI_U8* )&WMMAddTSRsp, sizeof( WMMAddTSRsp ) );

        WMMAddTSRsp.Category.category = SIR_MAC_ACTION_WME;
        WMMAddTSRsp.Action.action     = SIR_MAC_QOS_ADD_TS_RSP;
        WMMAddTSRsp.DialogToken.token = pAddTS->dialogToken;
        WMMAddTSRsp.StatusCode.statusCode = (tANI_U8)nStatusCode;

        PopulateDot11fWMMTSPEC( &pAddTS->tspec, &WMMAddTSRsp.WMMTSPEC );

        nStatus = dot11fGetPackedWMMAddTSResponseSize( pMac, &WMMAddTSRsp, &nPayload );
        if ( DOT11F_FAILED( nStatus ) )
        {
            limLog( pMac, LOGP, FL("Failed to calculate the packed si"
                                   "ze for a WMM Add TS Response (0x%08x).\n"),
                    nStatus );
            //                                            
            nPayload = sizeof( tDot11fWMMAddTSResponse );
        }
        else if ( DOT11F_WARNED( nStatus ) )
        {
            limLog( pMac, LOGW, FL("There were warnings while calcula"
                                   "tingthe packed size for a WMM Add"
                                   "TS Response (0x%08x).\n"), nStatus );
        }
    }

    nBytes = nPayload + sizeof( tSirMacMgmtHdr );

    halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( tANI_U16 )nBytes, ( void** ) &pFrame, ( void** ) &pPacket );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to allocate %d bytes for an Ad"
                               "d TS Response.\n"), nBytes );
        return;
    }

    //          
    palZeroMemory( pMac->hHdd, pFrame, nBytes );

    //                                         
    nSirStatus = limPopulateMacHeader( pMac, pFrame, SIR_MAC_MGMT_FRAME,
                                SIR_MAC_MGMT_ACTION, peer,psessionEntry->selfMacAddr);
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to populate the buffer descrip"
                               "tor for an Add TS Response (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return;                 //           
    }

    pMacHdr = ( tpSirMacMgmtHdr ) pFrame;

     
    #if 0
    if ( eSIR_SUCCESS != wlan_cfgGetStr( pMac, WNI_CFG_BSSID,
                                    ( tANI_U8* )pMacHdr->bssId, &cfgLen ) )
    {
        limLog( pMac, LOGP, FL("Failed to retrieve WNI_CFG_BSSID whil"
                               "e sending an Add TS Response.\n") );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return;                 //           
    }
    #endif //                 
    sirCopyMacAddr(pMacHdr->bssId,psessionEntry->bssId);

    //                            
    if ( ! pAddTS->wmeTspecPresent )
    {
        nStatus = dot11fPackAddTSResponse( pMac, &AddTSRsp,
                                           pFrame + sizeof( tSirMacMgmtHdr ),
                                           nPayload, &nPayload );
        if ( DOT11F_FAILED( nStatus ) )
        {
            limLog( pMac, LOGE, FL("Failed to pack an Add TS Response "
                                   "(0x%08x).\n"),
                    nStatus );
            palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
            return;
        }
        else if ( DOT11F_WARNED( nStatus ) )
        {
            limLog( pMac, LOGW, FL("There were warnings while packing"
                                   "an Add TS Response (0x%08x).\n") );
        }
    }
    else
    {
        nStatus = dot11fPackWMMAddTSResponse( pMac, &WMMAddTSRsp,
                                              pFrame + sizeof( tSirMacMgmtHdr ),
                                              nPayload, &nPayload );
        if ( DOT11F_FAILED( nStatus ) )
        {
            limLog( pMac, LOGE, FL("Failed to pack a WMM Add TS Response "
                                   "(0x%08x).\n"),
                    nStatus );
            palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
            return;
        }
        else if ( DOT11F_WARNED( nStatus ) )
        {
            limLog( pMac, LOGW, FL("There were warnings while packing"
                                   "a WMM Add TS Response (0x%08x).\n") );
        }
    }

    PELOG1(limLog( pMac, LOG1, FL("Sending an Add TS Response (status %d) to "),
            nStatusCode );
    limPrintMacAddr( pMac, pMacHdr->da, LOG1 );)

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }

    //                                     
    halstatus = halTxFrame( pMac, pPacket, ( tANI_U16 ) nBytes,
                            HAL_TXRX_FRM_802_11_MGMT,
                            ANI_TXDIR_TODS,
                            7,//                           
                            limTxComplete, pFrame, txFlag );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to send Add TS Response (%X)!\n"),
                nSirStatus );
        //                                    
    }

} //                                

void
limSendDeltsReqActionFrame(tpAniSirGlobal  pMac,
                           tSirMacAddr  peer,
                           tANI_U8  wmmTspecPresent,
                           tSirMacTSInfo  *pTsinfo,
                           tSirMacTspecIE  *pTspecIe,
                           tpPESession psessionEntry)
{
    tANI_U8         *pFrame;
    tpSirMacMgmtHdr  pMacHdr;
    tDot11fDelTS     DelTS;
    tDot11fWMMDelTS  WMMDelTS;
    tSirRetStatus    nSirStatus;
    tANI_U32         nBytes, nPayload, nStatus;
    void            *pPacket;
    eHalStatus       halstatus;
    tANI_U8          txFlag = 0;

    if(NULL == psessionEntry)
    {
              return;
    }

    if ( ! wmmTspecPresent )
    {
        palZeroMemory( pMac->hHdd, ( tANI_U8* )&DelTS, sizeof( DelTS ) );

        DelTS.Category.category = SIR_MAC_ACTION_QOS_MGMT;
        DelTS.Action.action     = SIR_MAC_QOS_DEL_TS_REQ;
        PopulateDot11fTSInfo( pTsinfo, &DelTS.TSInfo );

        nStatus = dot11fGetPackedDelTSSize( pMac, &DelTS, &nPayload );
        if ( DOT11F_FAILED( nStatus ) )
        {
            limLog( pMac, LOGP, FL("Failed to calculate the packed si"
                                   "ze for a Del TS (0x%08x).\n"),
                    nStatus );
            //                                            
            nPayload = sizeof( tDot11fDelTS );
        }
        else if ( DOT11F_WARNED( nStatus ) )
        {
            limLog( pMac, LOGW, FL("There were warnings while calcula"
                                   "ting the packed size for a Del TS"
                                   " (0x%08x).\n"), nStatus );
        }
    }
    else
    {
        palZeroMemory( pMac->hHdd, ( tANI_U8* )&WMMDelTS, sizeof( WMMDelTS ) );

        WMMDelTS.Category.category = SIR_MAC_ACTION_WME;
        WMMDelTS.Action.action     = SIR_MAC_QOS_DEL_TS_REQ;
        WMMDelTS.DialogToken.token = 0;
        WMMDelTS.StatusCode.statusCode = 0;
        PopulateDot11fWMMTSPEC( pTspecIe, &WMMDelTS.WMMTSPEC );
        nStatus = dot11fGetPackedWMMDelTSSize( pMac, &WMMDelTS, &nPayload );
        if ( DOT11F_FAILED( nStatus ) )
        {
            limLog( pMac, LOGP, FL("Failed to calculate the packed si"
                                   "ze for a WMM Del TS (0x%08x).\n"),
                    nStatus );
            //                                            
            nPayload = sizeof( tDot11fDelTS );
        }
        else if ( DOT11F_WARNED( nStatus ) )
        {
            limLog( pMac, LOGW, FL("There were warnings while calcula"
                                   "ting the packed size for a WMM De"
                                   "l TS (0x%08x).\n"), nStatus );
        }
    }

    nBytes = nPayload + sizeof( tSirMacMgmtHdr );

    halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( tANI_U16 )nBytes, ( void** ) &pFrame, ( void** ) &pPacket );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to allocate %d bytes for an Ad"
                               "d TS Response.\n"), nBytes );
        return;
    }

    //          
    palZeroMemory( pMac->hHdd, pFrame, nBytes );

    //                                         
    nSirStatus = limPopulateMacHeader( pMac, pFrame, SIR_MAC_MGMT_FRAME,
                                SIR_MAC_MGMT_ACTION, peer,
                                psessionEntry->selfMacAddr);
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to populate the buffer descrip"
                               "tor for an Add TS Response (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return;                 //           
    }

    pMacHdr = ( tpSirMacMgmtHdr ) pFrame;

    #if 0

    cfgLen = SIR_MAC_ADDR_LENGTH;
    if ( eSIR_SUCCESS != wlan_cfgGetStr( pMac, WNI_CFG_BSSID,
                                    ( tANI_U8* )pMacHdr->bssId, &cfgLen ) )
    {
        limLog( pMac, LOGP, FL("Failed to retrieve WNI_CFG_BSSID whil"
                               "e sending an Add TS Response.\n") );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return;                 //           
    }
    #endif //                 
    sirCopyMacAddr(pMacHdr->bssId, psessionEntry->bssId);
    
    //                            
    if ( !wmmTspecPresent )
    {
        nStatus = dot11fPackDelTS( pMac, &DelTS,
                                   pFrame + sizeof( tSirMacMgmtHdr ),
                                   nPayload, &nPayload );
        if ( DOT11F_FAILED( nStatus ) )
        {
            limLog( pMac, LOGE, FL("Failed to pack a Del TS frame (0x%08x).\n"),
                    nStatus );
            palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
            return;             //           
        }
        else if ( DOT11F_WARNED( nStatus ) )
        {
            limLog( pMac, LOGW, FL("There were warnings while packing"
                                   "a Del TS frame (0x%08x).\n") );
        }
    }
    else
    {
        nStatus = dot11fPackWMMDelTS( pMac, &WMMDelTS,
                                      pFrame + sizeof( tSirMacMgmtHdr ),
                                      nPayload, &nPayload );
        if ( DOT11F_FAILED( nStatus ) )
        {
            limLog( pMac, LOGE, FL("Failed to pack a WMM Del TS frame (0x%08x).\n"),
                    nStatus );
            palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
            return;             //           
        }
        else if ( DOT11F_WARNED( nStatus ) )
        {
            limLog( pMac, LOGW, FL("There were warnings while packing"
                                   "a WMM Del TS frame (0x%08x).\n") );
        }
    }

    PELOG1(limLog(pMac, LOG1, FL("Sending DELTS REQ (size %d) to "), nBytes);
    limPrintMacAddr(pMac, pMacHdr->da, LOG1);)

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }

    halstatus = halTxFrame( pMac, pPacket, ( tANI_U16 ) nBytes,
                            HAL_TXRX_FRM_802_11_MGMT,
                            ANI_TXDIR_TODS,
                            7,//                           
                            limTxComplete, pFrame, txFlag );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to send Del TS (%X)!\n"),
                nSirStatus );
        //                                    
    }

} //                                

void
limSendAssocReqMgmtFrame(tpAniSirGlobal   pMac,
                         tLimMlmAssocReq *pMlmAssocReq,
                         tpPESession psessionEntry)
{
    tDot11fAssocRequest *pFrm;
    tANI_U16            caps;
    tANI_U8            *pFrame;
    tSirRetStatus       nSirStatus;
    tLimMlmAssocCnf     mlmAssocCnf;
    tANI_U32            nBytes, nPayload, nStatus;
    tANI_U8             fQosEnabled, fWmeEnabled, fWsmEnabled;
    void               *pPacket;
    eHalStatus          halstatus;
    tANI_U16            nAddIELen; 
    tANI_U8             *pAddIE;
    tANI_U8             *wpsIe = NULL;
#if defined WLAN_FEATURE_VOWIFI
    tANI_U8             PowerCapsPopulated = FALSE;
#endif
    tANI_U8             txFlag = 0;

    if(NULL == psessionEntry)
    {
        return;
    }

    if(NULL == psessionEntry->pLimJoinReq)
    {
        return;
    }
    
    /*                                                */
    if(NULL == psessionEntry->pLimJoinReq)
    {
        return;
    }
    nAddIELen = psessionEntry->pLimJoinReq->addIEAssoc.length; 
    pAddIE = psessionEntry->pLimJoinReq->addIEAssoc.addIEdata;

    if(eHAL_STATUS_SUCCESS != palAllocateMemory(pMac->hHdd, 
                                                (void **)&pFrm, sizeof(tDot11fAssocRequest)))
    {
        limLog(pMac, LOGE, FL("Unable to PAL allocate memory in limSendAssocReqMgmtFrame\n") );
        return;
    }


    palZeroMemory( pMac->hHdd, ( tANI_U8* )pFrm, sizeof( tDot11fAssocRequest ) );

    caps = pMlmAssocReq->capabilityInfo;
    if ( PROP_CAPABILITY_GET( 11EQOS, psessionEntry->limCurrentBssPropCap ) )
        ((tSirMacCapabilityInfo *) &caps)->qos = 0;
#if defined(FEATURE_WLAN_WAPI)
    /*              
                                  
                                           
                                                                                       
                                                                                                                       
                                        */
    if ( psessionEntry->encryptType == eSIR_ED_WPI)
        ((tSirMacCapabilityInfo *) &caps)->privacy = 0;
#endif
    swapBitField16(caps, ( tANI_U16* )&pFrm->Capabilities );

    pFrm->ListenInterval.interval = pMlmAssocReq->listenInterval;
    PopulateDot11fSSID2( pMac, &pFrm->SSID );
    PopulateDot11fSuppRates( pMac, POPULATE_DOT11F_RATES_OPERATIONAL,
            &pFrm->SuppRates,psessionEntry);

    fQosEnabled = ( psessionEntry->limQosEnabled) &&
        SIR_MAC_GET_QOS( psessionEntry->limCurrentBssCaps );

    fWmeEnabled = ( psessionEntry->limWmeEnabled ) &&
        LIM_BSS_CAPS_GET( WME, psessionEntry->limCurrentBssQosCaps );

    //                            
    if ( fQosEnabled ) fWmeEnabled = false;

    fWsmEnabled = ( psessionEntry->limWsmEnabled ) && fWmeEnabled &&
        LIM_BSS_CAPS_GET( WSM, psessionEntry->limCurrentBssQosCaps );

    if ( psessionEntry->lim11hEnable  &&
            psessionEntry->pLimJoinReq->spectrumMgtIndicator == eSIR_TRUE ) 
    {
#if defined WLAN_FEATURE_VOWIFI
        PowerCapsPopulated = TRUE;

        PopulateDot11fPowerCaps( pMac, &pFrm->PowerCaps, LIM_ASSOC,psessionEntry);
#endif
        PopulateDot11fSuppChannels( pMac, &pFrm->SuppChannels, LIM_ASSOC,psessionEntry);

    }

#if defined WLAN_FEATURE_VOWIFI
    if( pMac->rrm.rrmPEContext.rrmEnable &&
            SIR_MAC_GET_RRM( psessionEntry->limCurrentBssCaps ) )
    {
        if (PowerCapsPopulated == FALSE) 
        {
            PowerCapsPopulated = TRUE;
            PopulateDot11fPowerCaps(pMac, &pFrm->PowerCaps, LIM_ASSOC, psessionEntry);
        }
    }
#endif

    if ( fQosEnabled &&
            ( ! PROP_CAPABILITY_GET(11EQOS, psessionEntry->limCurrentBssPropCap)))
        PopulateDot11fQOSCapsStation( pMac, &pFrm->QOSCapsStation );

    PopulateDot11fExtSuppRates( pMac, POPULATE_DOT11F_RATES_OPERATIONAL,
            &pFrm->ExtSuppRates, psessionEntry );

#if defined WLAN_FEATURE_VOWIFI
    if( pMac->rrm.rrmPEContext.rrmEnable &&
            SIR_MAC_GET_RRM( psessionEntry->limCurrentBssCaps ) )
    {
        PopulateDot11fRRMIe( pMac, &pFrm->RRMEnabledCap, psessionEntry );       
    }
#endif
    //                                                                 
    //                                                   
    //                                                               

    //                             
    //      
    //                               
    //                                                           
    //                              

    //                                                                  
    //                                                             
    //                                        

    //                                                               
    //                                    

    //                                                       
    //                                                          
    //                                              
    if( nAddIELen && pAddIE )
    {
        wpsIe = limGetWscIEPtr (pMac, pAddIE, nAddIELen);
    }
    if ( NULL == wpsIe )
    {
        PopulateDot11fRSNOpaque( pMac, &( psessionEntry->pLimJoinReq->rsnIE ),
                &pFrm->RSNOpaque );
        PopulateDot11fWPAOpaque( pMac, &( psessionEntry->pLimJoinReq->rsnIE ),
                &pFrm->WPAOpaque );
#if defined(FEATURE_WLAN_WAPI)
        PopulateDot11fWAPIOpaque( pMac, &( psessionEntry->pLimJoinReq->rsnIE ),
                &pFrm->WAPIOpaque );
#endif //                           
    }

    //                            
    if ( fWmeEnabled )
    {
        if ( ! PROP_CAPABILITY_GET( WME, psessionEntry->limCurrentBssPropCap ) )
        {
            PopulateDot11fWMMInfoStation( pMac, &pFrm->WMMInfoStation );
        }

        if ( fWsmEnabled &&
                ( ! PROP_CAPABILITY_GET(WSM, psessionEntry->limCurrentBssPropCap )))
        {
            PopulateDot11fWMMCaps( &pFrm->WMMCaps );
        }
    }

    //                                                          
    //                                      
    if ( psessionEntry->htCapability &&
            pMac->lim.htCapabilityPresentInBeacon)
    {
        PopulateDot11fHTCaps( pMac, psessionEntry, &pFrm->HTCaps );
#ifdef DISABLE_GF_FOR_INTEROP

        /*
                                                            
                                                               
                                                          
                                                
         */

        if( (psessionEntry->pLimJoinReq != NULL) && (!psessionEntry->pLimJoinReq->bssDescription.aniIndicator))
        {
                limLog( pMac, LOG1, FL("Sending Assoc Req to Non-TQ AP, Turning off Greenfield"));
            pFrm->HTCaps.greenField = WNI_CFG_GREENFIELD_CAPABILITY_DISABLE;
        }
#endif

    }
#ifdef WLAN_FEATURE_11AC
    if ( psessionEntry->vhtCapability &&
        pMac->lim.vhtCapabilityPresentInBeacon)
    {
        limLog( pMac, LOG1, FL("Populate VHT IEs in Assoc Request"));
        PopulateDot11fVHTCaps( pMac, &pFrm->VHTCaps );
    }
#endif


#if defined WLAN_FEATURE_VOWIFI_11R
    if (psessionEntry->pLimJoinReq->is11Rconnection)
    {
#if defined WLAN_FEATURE_VOWIFI_11R_DEBUG
        limLog( pMac, LOG1, FL("mdie = %02x %02x %02x"), 
                (unsigned int)psessionEntry->pLimJoinReq->bssDescription.mdie[0],
                (unsigned int)psessionEntry->pLimJoinReq->bssDescription.mdie[1],
                (unsigned int)psessionEntry->pLimJoinReq->bssDescription.mdie[2]);
#endif
        PopulateMDIE( pMac, &pFrm->MobilityDomain, psessionEntry->pLimJoinReq->bssDescription.mdie); 
    }
    else 
    {
        //                              
        limLog( pMac, LOG1, FL("mdie not present")); 
    }
#endif

#ifdef FEATURE_WLAN_CCX
    //                                      
    if (psessionEntry->isCCXconnection)
    {
        PopulateDot11fCCXRadMgmtCap(&pFrm->CCXRadMgmtCap);
        PopulateDot11fCCXVersion(&pFrm->CCXVersion);
    }
#endif

    nStatus = dot11fGetPackedAssocRequestSize( pMac, pFrm, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to calculate the packed size f"
                    "or an Association Request (0x%08x).\n"),
                nStatus );
        //                                            
        nPayload = sizeof( tDot11fAssocRequest );
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while calculating"
                    "the packed size for an Association Re "
                    "quest(0x%08x).\n"), nStatus );
    }

    nBytes = nPayload + sizeof( tSirMacMgmtHdr ) + nAddIELen;

    halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
            ( tANI_U16 )nBytes, ( void** ) &pFrame,
            ( void** ) &pPacket );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to allocate %d bytes for an As"
                    "sociation Request.\n"), nBytes );

        psessionEntry->limMlmState = psessionEntry->limPrevMlmState;
        MTRACE(macTrace(pMac, TRACE_CODE_MLM_STATE, psessionEntry->peSessionId, psessionEntry->limMlmState));


        /*                     */
        mlmAssocCnf.sessionId = psessionEntry->peSessionId;

        mlmAssocCnf.resultCode = eSIR_SME_RESOURCES_UNAVAILABLE;

        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                ( void* ) pFrame, ( void* ) pPacket );

        limPostSmeMessage( pMac, LIM_MLM_ASSOC_CNF,
                ( tANI_U32* ) &mlmAssocCnf);

        palFreeMemory(pMac->hHdd, pFrm);
        return;
    }

    //          
    palZeroMemory( pMac->hHdd, pFrame, nBytes );

    //                                         
    nSirStatus = limPopulateMacHeader( pMac, pFrame, SIR_MAC_MGMT_FRAME,
            SIR_MAC_MGMT_ASSOC_REQ, psessionEntry->bssId,psessionEntry->selfMacAddr);
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to populate the buffer descrip"
                    "tor for an Association Request (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        palFreeMemory(pMac->hHdd, pFrm);
        return;
    }


    //                                   
    nStatus = dot11fPackAssocRequest( pMac, pFrm, pFrame +
            sizeof(tSirMacMgmtHdr),
            nPayload, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to pack a Probe Response (0x%0"
                    "8x).\n"),
                nStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                ( void* ) pFrame, ( void* ) pPacket );
        palFreeMemory(pMac->hHdd, pFrm);
        return;
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while packing a P"
                    "robe Response (0x%08x).\n") );
    }

    PELOG1(limLog( pMac, LOG1, FL("*** Sending Association Request length %d"
                    "to \n"),
                nBytes );)
        //                                        

        if( psessionEntry->assocReq != NULL )
        {
            palFreeMemory(pMac->hHdd, psessionEntry->assocReq);
            psessionEntry->assocReq = NULL;
        }

    if( nAddIELen )
    {
        palCopyMemory( pMac->hHdd, pFrame + sizeof(tSirMacMgmtHdr) + nPayload, 
                pAddIE, 
                nAddIELen );
        nPayload += nAddIELen;
    }

    if( (palAllocateMemory(pMac->hHdd, (void**)&psessionEntry->assocReq,
                           nPayload)) != eHAL_STATUS_SUCCESS)
    {
        PELOGE(limLog(pMac, LOGE, FL("Unable to allocate memory to store assoc request"));)
    }
    else
    {
        //                                                                       
        palCopyMemory(pMac->hHdd, psessionEntry->assocReq, pFrame + sizeof(tSirMacMgmtHdr), nPayload);
        psessionEntry->assocReqLen = nPayload;
    }

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }

    halstatus = halTxFrame( pMac, pPacket, ( tANI_U16 ) (sizeof(tSirMacMgmtHdr) + nPayload),
            HAL_TXRX_FRM_802_11_MGMT,
            ANI_TXDIR_TODS,
            7,//                           
            limTxComplete, pFrame, txFlag );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to send Association Request (%X)!\n"),
                halstatus );
        //                                    
        palFreeMemory(pMac->hHdd, pFrm);
        return;
    }

    //                                         
    palFreeMemory( pMac->hHdd, ( tANI_U8* ) pMlmAssocReq );
    palFreeMemory(pMac->hHdd, pFrm);
    return;
} //                             


#if defined WLAN_FEATURE_VOWIFI_11R || defined FEATURE_WLAN_CCX || defined(FEATURE_WLAN_LFR)
/*                                                                                    
  
                               
  
                                                                                     
 */
void
limSendReassocReqWithFTIEsMgmtFrame(tpAniSirGlobal     pMac,
                           tLimMlmReassocReq *pMlmReassocReq,tpPESession psessionEntry)
{
    static tDot11fReAssocRequest frm;
    tANI_U16              caps;
    tANI_U8              *pFrame;
    tSirRetStatus         nSirStatus;
    tANI_U32              nBytes, nPayload, nStatus;
    tANI_U8               fQosEnabled, fWmeEnabled, fWsmEnabled;
    void                 *pPacket;
    eHalStatus            halstatus;
#if defined WLAN_FEATURE_VOWIFI
    tANI_U8               PowerCapsPopulated = FALSE;
#endif
    tANI_U16              ft_ies_length = 0;
    tANI_U8               *pBody;
    tANI_U16              nAddIELen; 
    tANI_U8               *pAddIE;
#if defined FEATURE_WLAN_CCX || defined(FEATURE_WLAN_LFR)
    tANI_U8               *wpsIe = NULL;
#endif
    tANI_U8               txFlag = 0;

    if (NULL == psessionEntry)
    {
        return;
    }

#if defined WLAN_FEATURE_VOWIFI_11R
    if (psessionEntry->is11Rconnection)
    {
        if (pMac->ft.ftSmeContext.reassoc_ft_ies_length == 0)
        {
            return;
        }
    }
#endif

    /*                                                */
    if(NULL == psessionEntry->pLimReAssocReq)
    {
        return;
    }
    nAddIELen = psessionEntry->pLimReAssocReq->addIEAssoc.length; 
    pAddIE = psessionEntry->pLimReAssocReq->addIEAssoc.addIEdata;
    limLog( pMac, LOGE, FL("limSendReassocReqWithFTIEsMgmtFrame received in " 
                           "state (%d).\n"), psessionEntry->limMlmState);

    palZeroMemory( pMac->hHdd, ( tANI_U8* )&frm, sizeof( frm ) );

    caps = pMlmReassocReq->capabilityInfo;
    if (PROP_CAPABILITY_GET(11EQOS, psessionEntry->limReassocBssPropCap))
        ((tSirMacCapabilityInfo *) &caps)->qos = 0;
#if defined(FEATURE_WLAN_WAPI)
    /*              
                                  
                                           
                                                                                       
                                                                                                                       
                                        */
    if ( psessionEntry->encryptType == eSIR_ED_WPI)
        ((tSirMacCapabilityInfo *) &caps)->privacy = 0;
#endif
    swapBitField16(caps, ( tANI_U16* )&frm.Capabilities );

    frm.ListenInterval.interval = pMlmReassocReq->listenInterval;

    //                                   
    palCopyMemory( pMac->hHdd, ( tANI_U8* )frm.CurrentAPAddress.mac,
            pMac->ft.ftPEContext.pFTPreAuthReq->currbssId, 6); 

    PopulateDot11fSSID2( pMac, &frm.SSID );
    PopulateDot11fSuppRates( pMac, POPULATE_DOT11F_RATES_OPERATIONAL,
            &frm.SuppRates,psessionEntry);

    fQosEnabled = ( psessionEntry->limQosEnabled) &&
        SIR_MAC_GET_QOS( psessionEntry->limReassocBssCaps );

    fWmeEnabled = ( psessionEntry->limWmeEnabled ) &&
        LIM_BSS_CAPS_GET( WME, psessionEntry->limReassocBssQosCaps );

    fWsmEnabled = ( psessionEntry->limWsmEnabled ) && fWmeEnabled &&
        LIM_BSS_CAPS_GET( WSM, psessionEntry->limReassocBssQosCaps );

    if ( psessionEntry->lim11hEnable  &&
            psessionEntry->pLimReAssocReq->spectrumMgtIndicator == eSIR_TRUE )
    {
#if defined WLAN_FEATURE_VOWIFI
        PowerCapsPopulated = TRUE;

        PopulateDot11fPowerCaps( pMac, &frm.PowerCaps, LIM_REASSOC,psessionEntry);
        PopulateDot11fSuppChannels( pMac, &frm.SuppChannels, LIM_REASSOC,psessionEntry);
#endif
    }

#if defined WLAN_FEATURE_VOWIFI
    if( pMac->rrm.rrmPEContext.rrmEnable &&
            SIR_MAC_GET_RRM( psessionEntry->limCurrentBssCaps ) )
    {
        if (PowerCapsPopulated == FALSE) 
        {
            PowerCapsPopulated = TRUE;
            PopulateDot11fPowerCaps(pMac, &frm.PowerCaps, LIM_REASSOC, psessionEntry);
        }
    }
#endif

    if ( fQosEnabled &&
            ( ! PROP_CAPABILITY_GET(11EQOS, psessionEntry->limReassocBssPropCap ) ))
    {
        PopulateDot11fQOSCapsStation( pMac, &frm.QOSCapsStation );
    }

    PopulateDot11fExtSuppRates( pMac, POPULATE_DOT11F_RATES_OPERATIONAL,
            &frm.ExtSuppRates, psessionEntry );

#if defined WLAN_FEATURE_VOWIFI
    if( pMac->rrm.rrmPEContext.rrmEnable &&
            SIR_MAC_GET_RRM( psessionEntry->limReassocBssCaps ) )
    {
        PopulateDot11fRRMIe( pMac, &frm.RRMEnabledCap, psessionEntry );       
    }
#endif

    //                                                          
    //                                                     
    //                                         
    //                                                            
    //                               
#if defined FEATURE_WLAN_CCX || defined(FEATURE_WLAN_LFR)
    //
    //                                                                 
    //                                                   
    //                                                               

    //                             
    //      
    //                               
    //                                                           
    //                              

    //                                                                  
    //                                                             
    //                                        

    //                                                               
    //                                    

    //                                                       
    //                                                          
    //                                              
    if (!psessionEntry->is11Rconnection)
    {
        if( nAddIELen && pAddIE )
        {
            wpsIe = limGetWscIEPtr(pMac, pAddIE, nAddIELen);
        }
        if ( NULL == wpsIe )
        {
            PopulateDot11fRSNOpaque( pMac, &( psessionEntry->pLimReAssocReq->rsnIE ),
                    &frm.RSNOpaque );
            PopulateDot11fWPAOpaque( pMac, &( psessionEntry->pLimReAssocReq->rsnIE ),
                    &frm.WPAOpaque );
        }

#ifdef FEATURE_WLAN_CCX
        if(psessionEntry->pLimReAssocReq->cckmIE.length)
        {
            PopulateDot11fCCXCckmOpaque( pMac, &( psessionEntry->pLimReAssocReq->cckmIE ),
                    &frm.CCXCckmOpaque );
        }
#endif //                
    }

#ifdef FEATURE_WLAN_CCX
    //                                      
    if (psessionEntry->isCCXconnection)
    {
        PopulateDot11fCCXRadMgmtCap(&frm.CCXRadMgmtCap);
        PopulateDot11fCCXVersion(&frm.CCXVersion);
    }
#endif //                 
#endif //                                    

    //                            
    if ( fWmeEnabled )
    {
        if ( ! PROP_CAPABILITY_GET( WME, psessionEntry->limReassocBssPropCap ) )
        {
            PopulateDot11fWMMInfoStation( pMac, &frm.WMMInfoStation );
        }

        if ( fWsmEnabled &&
                ( ! PROP_CAPABILITY_GET(WSM, psessionEntry->limReassocBssPropCap )))
        {
            PopulateDot11fWMMCaps( &frm.WMMCaps );
        }
#ifdef FEATURE_WLAN_CCX
        if (psessionEntry->isCCXconnection) 
        {
            PopulateDot11fReAssocTspec(pMac, &frm, psessionEntry);

            //                                                                 
            if (psessionEntry->pLimReAssocReq->ccxTspecInfo.numTspecs) 
            {
                tANI_U32 phyMode;
                tSirMacCCXTSRSIE    tsrsIE; 
                limGetPhyMode(pMac, &phyMode, psessionEntry);

                tsrsIE.tsid = 0;
                if( phyMode == WNI_CFG_PHY_MODE_11G || phyMode == WNI_CFG_PHY_MODE_11A)
                {
                    tsrsIE.rates[0] = TSRS_11AG_RATE_6MBPS;
                }
                else 
                {
                    tsrsIE.rates[0] = TSRS_11B_RATE_5_5MBPS;
                }
                PopulateDot11TSRSIE(pMac,&tsrsIE, &frm.CCXTrafStrmRateSet, sizeof(tANI_U8));
            }
        }
#endif    
    }

    if ( psessionEntry->htCapability &&
            pMac->lim.htCapabilityPresentInBeacon)
    {
        PopulateDot11fHTCaps( pMac, psessionEntry, &frm.HTCaps );
    }

    nStatus = dot11fGetPackedReAssocRequestSize( pMac, &frm, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to calculate the packed size f"
                    "or a Re-Association Request (0x%08x).\n"),
                nStatus );
        //                                            
        nPayload = sizeof( tDot11fReAssocRequest );
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while calculating"
                    "the packed size for a Re-Association Re "
                    "quest(0x%08x).\n"), nStatus );
    }

    nBytes = nPayload + sizeof( tSirMacMgmtHdr ) + nAddIELen; ;

#ifdef WLAN_FEATURE_VOWIFI_11R_DEBUG
    limLog( pMac, LOGE, FL("FT IE Reassoc Req (%d).\n"), 
            pMac->ft.ftSmeContext.reassoc_ft_ies_length);
#endif

#if defined WLAN_FEATURE_VOWIFI_11R
    if (psessionEntry->is11Rconnection)
    {
        ft_ies_length = pMac->ft.ftSmeContext.reassoc_ft_ies_length;
    }
#endif

    halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
            ( tANI_U16 )nBytes+ft_ies_length, ( void** ) &pFrame,
            ( void** ) &pPacket );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        psessionEntry->limMlmState = psessionEntry->limPrevMlmState;
        MTRACE(macTrace(pMac, TRACE_CODE_MLM_STATE, psessionEntry->peSessionId, psessionEntry->limMlmState));
        limLog( pMac, LOGP, FL("Failed to allocate %d bytes for a Re-As"
                    "sociation Request.\n"), nBytes );
        goto end;
    }

    //          
    palZeroMemory( pMac->hHdd, pFrame, nBytes + ft_ies_length);

#if defined WLAN_FEATURE_VOWIFI_11R_DEBUG || defined FEATURE_WLAN_CCX || defined(FEATURE_WLAN_LFR)
    limPrintMacAddr(pMac, psessionEntry->limReAssocbssId, LOGE);
#endif
    //                                         
    nSirStatus = limPopulateMacHeader( pMac, pFrame, SIR_MAC_MGMT_FRAME,
            SIR_MAC_MGMT_REASSOC_REQ,
            psessionEntry->limReAssocbssId,psessionEntry->selfMacAddr);
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to populate the buffer descrip"
                    "tor for an Association Request (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        goto end;
    }


    //                                     
    nStatus = dot11fPackReAssocRequest( pMac, &frm, pFrame +
            sizeof(tSirMacMgmtHdr),
            nPayload, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to pack a Re-Association Reque"
                    "st (0x%08x).\n"),
                nStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        goto end;
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while packing a R"
                    "e-Association Request (0x%08x).\n") );
    }

    PELOG3(limLog( pMac, LOG3, 
            FL("*** Sending Re-Association Request length %d %d to \n"),
            nBytes, nPayload );)
    if( psessionEntry->assocReq != NULL )
    {
        palFreeMemory(pMac->hHdd, psessionEntry->assocReq);
        psessionEntry->assocReq = NULL;
    }

    if( nAddIELen )
    {
        palCopyMemory( pMac->hHdd, pFrame + sizeof(tSirMacMgmtHdr) + nPayload, 
                       pAddIE, 
                       nAddIELen );
        nPayload += nAddIELen;
    }

    if( (palAllocateMemory(pMac->hHdd, (void**)&psessionEntry->assocReq,
                           nPayload)) != eHAL_STATUS_SUCCESS)
    {
        PELOGE(limLog(pMac, LOGE, FL("Unable to allocate memory to store assoc request"));)
    }
    else
    {
        //                                                                       
        palCopyMemory(pMac->hHdd, psessionEntry->assocReq, pFrame + sizeof(tSirMacMgmtHdr), nPayload);
        psessionEntry->assocReqLen = nPayload;
    }

    if (psessionEntry->is11Rconnection)
    {
        {
            int i = 0;

            pBody = pFrame + nBytes;
            for (i=0; i<ft_ies_length; i++)
            {
                *pBody = pMac->ft.ftSmeContext.reassoc_ft_ies[i];
                pBody++;
            }
        }
    }

#ifdef WLAN_FEATURE_VOWIFI_11R_DEBUG
    PELOGE(limLog(pMac, LOGE, FL("Re-assoc Req Frame is: "));
            sirDumpBuf(pMac, SIR_LIM_MODULE_ID, LOGE,
                (tANI_U8 *)pFrame,
                (nBytes + ft_ies_length));)
#endif


    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }
 
    halstatus = halTxFrame( pMac, pPacket, ( tANI_U16 ) (nBytes + ft_ies_length),
            HAL_TXRX_FRM_802_11_MGMT,
            ANI_TXDIR_TODS,
            7,//                           
            limTxComplete, pFrame, txFlag );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to send Re-Association Request"
                    "(%X)!\n"),
                nSirStatus );
        //                                    
        goto end;
    }

end:
    //                                         
    palFreeMemory( pMac->hHdd, ( tANI_U8* ) pMlmReassocReq );
    psessionEntry->pLimMlmReassocReq = NULL;

}
#endif /*                         */


void
limSendReassocReqMgmtFrame(tpAniSirGlobal     pMac,
                           tLimMlmReassocReq *pMlmReassocReq,tpPESession psessionEntry)
{
    static tDot11fReAssocRequest frm;
    tANI_U16              caps;
    tANI_U8              *pFrame;
    tSirRetStatus         nSirStatus;
    tANI_U32              nBytes, nPayload, nStatus;
    tANI_U8               fQosEnabled, fWmeEnabled, fWsmEnabled;
    void                 *pPacket;
    eHalStatus            halstatus;
    tANI_U16              nAddIELen; 
    tANI_U8               *pAddIE;
    tANI_U8               *wpsIe = NULL;
    tANI_U8               txFlag = 0;
#if defined WLAN_FEATURE_VOWIFI
    tANI_U8               PowerCapsPopulated = FALSE;
#endif

    if(NULL == psessionEntry)
    {
        return;
    }

    /*                                                */
    if(NULL == psessionEntry->pLimReAssocReq)
    {
        return;
    }
    nAddIELen = psessionEntry->pLimReAssocReq->addIEAssoc.length; 
    pAddIE = psessionEntry->pLimReAssocReq->addIEAssoc.addIEdata;
    
    palZeroMemory( pMac->hHdd, ( tANI_U8* )&frm, sizeof( frm ) );

    caps = pMlmReassocReq->capabilityInfo;
    if (PROP_CAPABILITY_GET(11EQOS, psessionEntry->limReassocBssPropCap))
        ((tSirMacCapabilityInfo *) &caps)->qos = 0;
#if defined(FEATURE_WLAN_WAPI)
    /*              
                               
                                        
                                                                                    
                                                                                                                    
                                     */
    if ( psessionEntry->encryptType == eSIR_ED_WPI)
        ((tSirMacCapabilityInfo *) &caps)->privacy = 0;
#endif
    swapBitField16(caps, ( tANI_U16* )&frm.Capabilities );

    frm.ListenInterval.interval = pMlmReassocReq->listenInterval;

    palCopyMemory( pMac->hHdd, ( tANI_U8* )frm.CurrentAPAddress.mac,
                   ( tANI_U8* )psessionEntry->bssId, 6 );

    PopulateDot11fSSID2( pMac, &frm.SSID );
    PopulateDot11fSuppRates( pMac, POPULATE_DOT11F_RATES_OPERATIONAL,
                             &frm.SuppRates,psessionEntry);

    fQosEnabled = ( psessionEntry->limQosEnabled ) &&
        SIR_MAC_GET_QOS( psessionEntry->limReassocBssCaps );

    fWmeEnabled = ( psessionEntry->limWmeEnabled ) &&
        LIM_BSS_CAPS_GET( WME, psessionEntry->limReassocBssQosCaps );

    fWsmEnabled = ( psessionEntry->limWsmEnabled ) && fWmeEnabled &&
        LIM_BSS_CAPS_GET( WSM, psessionEntry->limReassocBssQosCaps );


    if ( psessionEntry->lim11hEnable  &&
         psessionEntry->pLimReAssocReq->spectrumMgtIndicator == eSIR_TRUE )
    {
#if defined WLAN_FEATURE_VOWIFI
        PowerCapsPopulated = TRUE;
        PopulateDot11fPowerCaps( pMac, &frm.PowerCaps, LIM_REASSOC,psessionEntry);
        PopulateDot11fSuppChannels( pMac, &frm.SuppChannels, LIM_REASSOC,psessionEntry);
#endif
    }

#if defined WLAN_FEATURE_VOWIFI
    if( pMac->rrm.rrmPEContext.rrmEnable &&
        SIR_MAC_GET_RRM( psessionEntry->limCurrentBssCaps ) )
    {
        if (PowerCapsPopulated == FALSE) 
        {
            PowerCapsPopulated = TRUE;
            PopulateDot11fPowerCaps(pMac, &frm.PowerCaps, LIM_REASSOC, psessionEntry);
        }
    }
#endif

    if ( fQosEnabled &&
         ( ! PROP_CAPABILITY_GET(11EQOS, psessionEntry->limReassocBssPropCap ) ))
    {
        PopulateDot11fQOSCapsStation( pMac, &frm.QOSCapsStation );
    }

    PopulateDot11fExtSuppRates( pMac, POPULATE_DOT11F_RATES_OPERATIONAL,
                                &frm.ExtSuppRates, psessionEntry );

#if defined WLAN_FEATURE_VOWIFI
    if( pMac->rrm.rrmPEContext.rrmEnable &&
        SIR_MAC_GET_RRM( psessionEntry->limReassocBssCaps ) )
    {
        PopulateDot11fRRMIe( pMac, &frm.RRMEnabledCap, psessionEntry );       
    }
#endif
    //                                                                 
    //                                                   
    //                                                               

    //                             
    //      
    //                               
    //                                                           
    //                              

    //                                                                  
    //                                                             
    //                                        

    //                                                               
    //                                    

    //                                                       
    //                                                          
    //                                              
    if( nAddIELen && pAddIE )
    {
        wpsIe = limGetWscIEPtr(pMac, pAddIE, nAddIELen);
    }
    if ( NULL == wpsIe )
    {
        PopulateDot11fRSNOpaque( pMac, &( psessionEntry->pLimReAssocReq->rsnIE ),
                                 &frm.RSNOpaque );
        PopulateDot11fWPAOpaque( pMac, &( psessionEntry->pLimReAssocReq->rsnIE ),
                                 &frm.WPAOpaque );
#if defined(FEATURE_WLAN_WAPI)
        PopulateDot11fWAPIOpaque( pMac, &( psessionEntry->pLimReAssocReq->rsnIE ),
                                 &frm.WAPIOpaque );
#endif //                           
    }

    //                            
    if ( fWmeEnabled )
    {
        if ( ! PROP_CAPABILITY_GET( WME, psessionEntry->limReassocBssPropCap ) )
        {
            PopulateDot11fWMMInfoStation( pMac, &frm.WMMInfoStation );
        }

        if ( fWsmEnabled &&
             ( ! PROP_CAPABILITY_GET(WSM, psessionEntry->limReassocBssPropCap )))
        {
            PopulateDot11fWMMCaps( &frm.WMMCaps );
        }
    }

    if ( psessionEntry->htCapability &&
          pMac->lim.htCapabilityPresentInBeacon)
    {
        PopulateDot11fHTCaps( pMac, psessionEntry, &frm.HTCaps );
    }
#ifdef WLAN_FEATURE_11AC
    if ( psessionEntry->vhtCapability &&
             pMac->lim.vhtCapabilityPresentInBeacon)
    {
        limLog( pMac, LOGW, FL("Populate VHT IEs in Re-Assoc Request\n"));
        PopulateDot11fVHTCaps( pMac, &frm.VHTCaps );
    }
#endif

    nStatus = dot11fGetPackedReAssocRequestSize( pMac, &frm, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to calculate the packed size f"
                               "or a Re-Association Request (0x%08x).\n"),
                nStatus );
        //                                            
        nPayload = sizeof( tDot11fReAssocRequest );
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while calculating"
                               "the packed size for a Re-Association Re "
                               "quest(0x%08x).\n"), nStatus );
    }

    nBytes = nPayload + sizeof( tSirMacMgmtHdr ) + nAddIELen;

    halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                             ( tANI_U16 )nBytes, ( void** ) &pFrame,
                             ( void** ) &pPacket );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        psessionEntry->limMlmState = psessionEntry->limPrevMlmState;
        MTRACE(macTrace(pMac, TRACE_CODE_MLM_STATE, psessionEntry->peSessionId, psessionEntry->limMlmState));
        limLog( pMac, LOGP, FL("Failed to allocate %d bytes for a Re-As"
                               "sociation Request.\n"), nBytes );
        goto end;
    }

    //          
    palZeroMemory( pMac->hHdd, pFrame, nBytes );

    //                                         
    nSirStatus = limPopulateMacHeader( pMac, pFrame, SIR_MAC_MGMT_FRAME,
                                SIR_MAC_MGMT_REASSOC_REQ,
                                psessionEntry->limReAssocbssId,psessionEntry->selfMacAddr);
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to populate the buffer descrip"
                               "tor for an Association Request (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        goto end;
    }


    //                                   
    nStatus = dot11fPackReAssocRequest( pMac, &frm, pFrame +
                                        sizeof(tSirMacMgmtHdr),
                                        nPayload, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to pack a Re-Association Reque"
                               "st (0x%08x).\n"),
                nStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        goto end;
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while packing a R"
                               "e-Association Request (0x%08x).\n") );
    }

    PELOG1(limLog( pMac, LOG1, FL("*** Sending Re-Association Request length %d"
                           "to \n"),
            nBytes );)

    if( psessionEntry->assocReq != NULL )
    {
        palFreeMemory(pMac->hHdd, psessionEntry->assocReq);
        psessionEntry->assocReq = NULL;
    }

    if( nAddIELen )
    {
        palCopyMemory( pMac->hHdd, pFrame + sizeof(tSirMacMgmtHdr) + nPayload, 
                       pAddIE, 
                       nAddIELen );
        nPayload += nAddIELen;
    }

    if( (palAllocateMemory(pMac->hHdd, (void**)&psessionEntry->assocReq,
                           nPayload)) != eHAL_STATUS_SUCCESS)
    {
        PELOGE(limLog(pMac, LOGE, FL("Unable to allocate memory to store assoc request"));)
    }
    else
    {
        //                                                                       
        palCopyMemory(pMac->hHdd, psessionEntry->assocReq, pFrame + sizeof(tSirMacMgmtHdr), nPayload);
        psessionEntry->assocReqLen = nPayload;
    }

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }

    halstatus = halTxFrame( pMac, pPacket, ( tANI_U16 ) (sizeof(tSirMacMgmtHdr) + nPayload),
                            HAL_TXRX_FRM_802_11_MGMT,
                            ANI_TXDIR_TODS,
                            7,//                           
                            limTxComplete, pFrame, txFlag );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to send Re-Association Request"
                               "(%X)!\n"),
                nSirStatus );
        //                                    
        goto end;
    }

end:
    //                                         
    palFreeMemory( pMac->hHdd, ( tANI_U8* ) pMlmReassocReq );
    psessionEntry->pLimMlmReassocReq = NULL;

} //                           

/* 
                                      
  
  
                                              
  
                                                                            
             
  
                                                                            
                    
  
                                                                        
                        
  
  
                                                                            
                                                      
  
  
 */

void
limSendAuthMgmtFrame(tpAniSirGlobal pMac,
                     tpSirMacAuthFrameBody pAuthFrameBody,
                     tSirMacAddr           peerMacAddr,
                     tANI_U8               wepBit,
                     tpPESession           psessionEntry 
                                                       )
{
    tANI_U8            *pFrame, *pBody;
    tANI_U32            frameLen = 0, bodyLen = 0;
    tpSirMacMgmtHdr     pMacHdr;
    tANI_U16            i;
    void               *pPacket;
    eHalStatus          halstatus;
    tANI_U8             txFlag = 0;

    if(NULL == psessionEntry)
    {
        return;
    }
      
    if (wepBit == LIM_WEP_IN_FC)
    {
        //                                                 
        /* 
                                                                
                                                                  
                                                                  
                                                            
                    
         */

        frameLen = sizeof(tSirMacMgmtHdr) + LIM_ENCR_AUTH_BODY_LEN;

        bodyLen = LIM_ENCR_AUTH_BODY_LEN;
    } //                             
    else
    {
        switch (pAuthFrameBody->authTransactionSeqNumber)
        {
            case SIR_MAC_AUTH_FRAME_1:
                /* 
                                                                  
                                                                       
                                                                     
                                   
                 */

                frameLen = sizeof(tSirMacMgmtHdr) +
                           SIR_MAC_AUTH_CHALLENGE_OFFSET;
                bodyLen  = SIR_MAC_AUTH_CHALLENGE_OFFSET;

#if defined WLAN_FEATURE_VOWIFI_11R
                if (pAuthFrameBody->authAlgoNumber == eSIR_FT_AUTH)
                {
                    if (pMac->ft.ftPEContext.pFTPreAuthReq->ft_ies) 
                    {
                        frameLen += pMac->ft.ftPEContext.pFTPreAuthReq->ft_ies_length;
                        limLog(pMac, LOG3, FL("Auth frame, FTIES length added=%d\n"), 
                        pMac->ft.ftPEContext.pFTPreAuthReq->ft_ies_length);
                    }
                    else 
                        limLog(pMac, LOG3, FL("Auth frame, Does not contain FTIES!!!\n"));
                }
#endif
                break;

            case SIR_MAC_AUTH_FRAME_2:
                if ((pAuthFrameBody->authAlgoNumber == eSIR_OPEN_SYSTEM) ||
                    ((pAuthFrameBody->authAlgoNumber == eSIR_SHARED_KEY) &&
                     (pAuthFrameBody->authStatusCode != eSIR_MAC_SUCCESS_STATUS)))
                {
                    /* 
                                                                      
                                                                   
                                                              
                                                          
                     */

                    frameLen = sizeof(tSirMacMgmtHdr) +
                               SIR_MAC_AUTH_CHALLENGE_OFFSET;
                    bodyLen = SIR_MAC_AUTH_CHALLENGE_OFFSET;
                }
                else
                {
                    //                                         
                    //           
                    /* 
                                                                      
                                                                   
                                                              
                                                                    
                                          
                     */

                    frameLen = sizeof(tSirMacMgmtHdr) +
                               sizeof(tSirMacAuthFrame);
                    bodyLen  = sizeof(tSirMacAuthFrameBody);
                }

                break;

            case SIR_MAC_AUTH_FRAME_3:
                //                                                    
                /* 
                                                                        
                                                                      
                                                                    
                               
                 */

                frameLen = sizeof(tSirMacMgmtHdr) +
                           SIR_MAC_AUTH_CHALLENGE_OFFSET;
                bodyLen  = SIR_MAC_AUTH_CHALLENGE_OFFSET;

                break;

            case SIR_MAC_AUTH_FRAME_4:
                /* 
                                                                        
                                                                      
                                                                    
                               
                 */

                frameLen = sizeof(tSirMacMgmtHdr) +
                           SIR_MAC_AUTH_CHALLENGE_OFFSET;
                bodyLen  = SIR_MAC_AUTH_CHALLENGE_OFFSET;

                break;
        } //                                                  
    } //                                 


    halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( tANI_U16 )frameLen, ( void** ) &pFrame, ( void** ) &pPacket );

    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        //          
        limLog(pMac, LOGP, FL("call to bufAlloc failed for AUTH frame\n"));

        return;
    }

    for (i = 0; i < frameLen; i++)
        pFrame[i] = 0;

    //           
    if (limPopulateMacHeader(pMac, pFrame, SIR_MAC_MGMT_FRAME,
                      SIR_MAC_MGMT_AUTH, peerMacAddr,psessionEntry->selfMacAddr) != eSIR_SUCCESS)
    {
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return;
    }

    pMacHdr = ( tpSirMacMgmtHdr ) pFrame;
    pMacHdr->fc.wep = wepBit;

    //              
    if(  (psessionEntry->limSystemRole == eLIM_AP_ROLE)|| (psessionEntry->limSystemRole == eLIM_BT_AMP_AP_ROLE) )
    {
        palCopyMemory( pMac->hHdd,(tANI_U8 *) pMacHdr->bssId,
                       (tANI_U8 *) psessionEntry->bssId,
                       sizeof( tSirMacAddr ));
    }

    //                                   
    pBody    = pFrame + sizeof(tSirMacMgmtHdr);

    if (wepBit == LIM_WEP_IN_FC)
    {
        palCopyMemory( pMac->hHdd, pBody, (tANI_U8 *) pAuthFrameBody, bodyLen);

        PELOG1(limLog(pMac, LOG1,
           FL("*** Sending Auth seq# 3 status %d (%d) to\n"),
           pAuthFrameBody->authStatusCode,
           (pAuthFrameBody->authStatusCode == eSIR_MAC_SUCCESS_STATUS));

        limPrintMacAddr(pMac, pMacHdr->da, LOG1);)
    }
    else
    {
        *((tANI_U16 *)(pBody)) = sirSwapU16ifNeeded(pAuthFrameBody->authAlgoNumber);
        pBody   += sizeof(tANI_U16);
        bodyLen -= sizeof(tANI_U16);

        *((tANI_U16 *)(pBody)) = sirSwapU16ifNeeded(pAuthFrameBody->authTransactionSeqNumber);
        pBody   += sizeof(tANI_U16);
        bodyLen -= sizeof(tANI_U16);

        *((tANI_U16 *)(pBody)) = sirSwapU16ifNeeded(pAuthFrameBody->authStatusCode);
        pBody   += sizeof(tANI_U16);
        bodyLen -= sizeof(tANI_U16);

        palCopyMemory( pMac->hHdd, pBody, (tANI_U8 *) &pAuthFrameBody->type, bodyLen);

#if defined WLAN_FEATURE_VOWIFI_11R
        if ((pAuthFrameBody->authAlgoNumber == eSIR_FT_AUTH) && 
                (pAuthFrameBody->authTransactionSeqNumber == SIR_MAC_AUTH_FRAME_1))
        {

            {
                int i = 0;
#if defined WLAN_FEATURE_VOWIFI_11R_DEBUG
                if (pMac->ft.ftPEContext.pFTPreAuthReq->ft_ies_length) 
                {
                    PELOGE(limLog(pMac, LOGE, FL("Auth1 Frame FTIE is: "));
                        sirDumpBuf(pMac, SIR_LIM_MODULE_ID, LOGE,
                            (tANI_U8 *)pBody,
                            (pMac->ft.ftPEContext.pFTPreAuthReq->ft_ies_length));)
                }
#endif
                for (i=0; i<pMac->ft.ftPEContext.pFTPreAuthReq->ft_ies_length; i++)
                {
                    *pBody = pMac->ft.ftPEContext.pFTPreAuthReq->ft_ies[i];
                    pBody++;
                }
            }
        }
#endif

        PELOG1(limLog(pMac, LOG1,
           FL("*** Sending Auth seq# %d status %d (%d) to "),
           pAuthFrameBody->authTransactionSeqNumber,
           pAuthFrameBody->authStatusCode,
           (pAuthFrameBody->authStatusCode == eSIR_MAC_SUCCESS_STATUS));

        limPrintMacAddr(pMac, pMacHdr->da, LOG1);)
    }
    PELOG2(sirDumpBuf(pMac, SIR_LIM_MODULE_ID, LOG2, pFrame, frameLen);)

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
#if  defined (WLAN_FEATURE_VOWIFI_11R) || defined (FEATURE_WLAN_CCX) || defined(FEATURE_WLAN_LFR)
       || ((NULL != pMac->ft.ftPEContext.pFTPreAuthReq) 
           && ( SIR_BAND_5_GHZ == limGetRFBand(pMac->ft.ftPEContext.pFTPreAuthReq->preAuthchannelNum)))
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }

    //                                                
    halstatus = halTxFrame( pMac, pPacket, ( tANI_U16 ) frameLen,
                            HAL_TXRX_FRM_802_11_MGMT,
                            ANI_TXDIR_TODS,
                            7,//                           
                            limTxComplete, pFrame, txFlag );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog(pMac, LOGE,
               FL("*** Could not send Auth frame, retCode=%X ***\n"),
               halstatus);

        //                                    
    }

    return;
} /*                                */

/* 
                                                             
  
  
                                              
  
                                                              
                       
  
                                                                             
       
  
  
 */

void
limSendDisassocMgmtFrame(tpAniSirGlobal pMac,
                         tANI_U16       nReason,
                         tSirMacAddr    peer,tpPESession psessionEntry)
{
    tDot11fDisassociation frm;
    tANI_U8              *pFrame;
    tSirRetStatus         nSirStatus;
    tpSirMacMgmtHdr       pMacHdr;
    tANI_U32              nBytes, nPayload, nStatus;
    void                 *pPacket;
    eHalStatus            halstatus;
    tANI_U8               txFlag = 0;

    if(NULL == psessionEntry)
    {
        return;
    }
    
    palZeroMemory( pMac->hHdd, ( tANI_U8* )&frm, sizeof( frm ) );

    frm.Reason.code = nReason;

    nStatus = dot11fGetPackedDisassociationSize( pMac, &frm, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to calculate the packed size f"
                               "or a Disassociation (0x%08x).\n"),
                nStatus );
        //                                            
        nPayload = sizeof( tDot11fDisassociation );
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while calculating"
                               "the packed size for a Disassociation "
                               "(0x%08x).\n"), nStatus );
    }

    nBytes = nPayload + sizeof( tSirMacMgmtHdr );

    halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                             ( tANI_U16 )nBytes, ( void** ) &pFrame,
                             ( void** ) &pPacket );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to allocate %d bytes for a Dis"
                               "association.\n"), nBytes );
        return;
    }

    //          
    palZeroMemory( pMac->hHdd, pFrame, nBytes );

    //                                         
    nSirStatus = limPopulateMacHeader( pMac, pFrame, SIR_MAC_MGMT_FRAME,
                                SIR_MAC_MGMT_DISASSOC, peer,psessionEntry->selfMacAddr);
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to populate the buffer descrip"
                               "tor for a Disassociation (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                    ( void* ) pFrame, ( void* ) pPacket );
        return;                 //                  
    }

    pMacHdr = ( tpSirMacMgmtHdr ) pFrame;

    //                  
    sirCopyMacAddr(pMacHdr->bssId,psessionEntry->bssId);
    
    nStatus = dot11fPackDisassociation( pMac, &frm, pFrame +
                                        sizeof(tSirMacMgmtHdr),
                                        nPayload, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to pack a Disassociation (0x%08x).\n"),
                nStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                    ( void* ) pFrame, ( void* ) pPacket );
        return;                 //           
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while packing a D"
                               "isassociation (0x%08x).\n") );
    }

    PELOG1(limLog( pMac, LOG1, FL("*** Sending Disassociation frame with rea"
                           "son %d to\n"), nReason );
    limPrintMacAddr( pMac, pMacHdr->da, LOG1 );)

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }

    //                                               
    halstatus = halTxFrame( pMac, pPacket, ( tANI_U16 ) nBytes,
                            HAL_TXRX_FRM_802_11_MGMT,
                            ANI_TXDIR_TODS,
                            7,//                           
                            limTxComplete, pFrame, txFlag );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to send Disassociation "
                               "(%X)!\n"),
                nSirStatus );
        //                                    
        return;
    }

} //                              

/* 
                                                                
  
  
                                              
  
                                                                  
                       
  
                                                                   
  
  
 */

void
limSendDeauthMgmtFrame(tpAniSirGlobal pMac,
                       tANI_U16       nReason,
                       tSirMacAddr    peer,tpPESession psessionEntry)
{
    tDot11fDeAuth    frm;
    tANI_U8         *pFrame;
    tSirRetStatus    nSirStatus;
    tpSirMacMgmtHdr  pMacHdr;
    tANI_U32         nBytes, nPayload, nStatus;
    void            *pPacket;
    eHalStatus       halstatus;
    tANI_U8          txFlag = 0;

    if(NULL == psessionEntry)
    {
        return;
    }
    
    palZeroMemory( pMac->hHdd, ( tANI_U8* ) &frm, sizeof( frm ) );

    frm.Reason.code = nReason;

    nStatus = dot11fGetPackedDeAuthSize( pMac, &frm, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to calculate the packed size f"
                               "or a De-Authentication (0x%08x).\n"),
                nStatus );
        //                                            
        nPayload = sizeof( tDot11fDeAuth );
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while calculating"
                               "the packed size for a De-Authentication "
                               "(0x%08x).\n"), nStatus );
    }

    nBytes = nPayload + sizeof( tSirMacMgmtHdr );

    halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                             ( tANI_U16 )nBytes, ( void** ) &pFrame,
                             ( void** ) &pPacket );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to allocate %d bytes for a De-"
                               "Authentication.\n"), nBytes );
        return;
    }

    //          
    palZeroMemory( pMac->hHdd, pFrame, nBytes );

    //                                         
    nSirStatus = limPopulateMacHeader( pMac, pFrame, SIR_MAC_MGMT_FRAME,
                                SIR_MAC_MGMT_DEAUTH, peer,psessionEntry->selfMacAddr);
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to populate the buffer descrip"
                               "tor for a De-Authentication (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                    ( void* ) pFrame, ( void* ) pPacket );
        return;                 //                  
    }

    pMacHdr = ( tpSirMacMgmtHdr ) pFrame;

    //                  
    sirCopyMacAddr(pMacHdr->bssId,psessionEntry->bssId);

    nStatus = dot11fPackDeAuth( pMac, &frm, pFrame +
                                sizeof(tSirMacMgmtHdr),
                                nPayload, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to pack a DeAuthentication (0x%08x).\n"),
                nStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,
                    ( void* ) pFrame, ( void* ) pPacket );
        return;
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while packing a D"
                               "e-Authentication (0x%08x).\n") );
    }

    PELOG1(limLog( pMac, LOG1, FL("*** Sending De-Authentication frame with rea"
                           "son %d to\n"), nReason );
    limPrintMacAddr( pMac, pMacHdr->da, LOG1 );)

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }

    //                                               
    halstatus = halTxFrame( pMac, pPacket, ( tANI_U16 ) nBytes,
                            HAL_TXRX_FRM_802_11_MGMT,
                            ANI_TXDIR_TODS,
                            7,//                           
                            limTxComplete, pFrame, txFlag );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to send De-Authentication "
                               "(%X)!\n"),
                nSirStatus );
        //                                    
        return;
    }

} //                            


#ifdef ANI_SUPPORT_11H
/* 
                                                
  
  
                                                  
  
                                                              
  
                                                     
  
  
 */

tSirRetStatus
limSendMeasReportFrame(tpAniSirGlobal             pMac,
                       tpSirMacMeasReqActionFrame pMeasReqFrame,
                       tSirMacAddr                peer)
{
    tDot11fMeasurementReport frm;
    tANI_U8                      *pFrame;
    tSirRetStatus            nSirStatus;
    tpSirMacMgmtHdr          pMacHdr;
    tANI_U32                      nBytes, nPayload, nStatus, nCfg;
    void               *pPacket;
    eHalStatus          halstatus;
   
    palZeroMemory( pMac->hHdd, ( tANI_U8* )&frm, sizeof( frm ) );

    frm.Category.category = SIR_MAC_ACTION_SPECTRUM_MGMT;
    frm.Action.action     = SIR_MAC_ACTION_MEASURE_REPORT_ID;
    frm.DialogToken.token = pMeasReqFrame->actionHeader.dialogToken;

    switch ( pMeasReqFrame->measReqIE.measType )
    {
    case SIR_MAC_BASIC_MEASUREMENT_TYPE:
        nSirStatus =
            PopulateDot11fMeasurementReport0( pMac, pMeasReqFrame,
                                               &frm.MeasurementReport );
        break;
    case SIR_MAC_CCA_MEASUREMENT_TYPE:
        nSirStatus =
            PopulateDot11fMeasurementReport1( pMac, pMeasReqFrame,
                                               &frm.MeasurementReport );
        break;
    case SIR_MAC_RPI_MEASUREMENT_TYPE:
        nSirStatus =
            PopulateDot11fMeasurementReport2( pMac, pMeasReqFrame,
                                               &frm.MeasurementReport );
        break;
    default:
        limLog( pMac, LOGE, FL("Unknown measurement type %d in limSen"
                               "dMeasReportFrame.\n"),
                pMeasReqFrame->measReqIE.measType );
        return eSIR_FAILURE;
    }

    if ( eSIR_SUCCESS != nSirStatus ) return eSIR_FAILURE;

    nStatus = dot11fGetPackedMeasurementReportSize( pMac, &frm, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to calculate the packed size f"
                               "or a Measurement Report (0x%08x).\n"),
                nStatus );
        //                                            
        nPayload = sizeof( tDot11fMeasurementReport );
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while calculating"
                               "the packed size for a Measurement Rep"
                               "ort (0x%08x).\n"), nStatus );
    }

    nBytes = nPayload + sizeof( tSirMacMgmtHdr );

    halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( tANI_U16 )nBytes, ( void** ) &pFrame, ( void** ) &pPacket );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to allocate %d bytes for a De-"
                               "Authentication.\n"), nBytes );
        return eSIR_FAILURE;
    }

    //          
    palZeroMemory( pMac->hHdd, pFrame, nBytes );

    //                                         
    nSirStatus = limPopulateMacHeader( pMac, pFrame, SIR_MAC_MGMT_FRAME,
                                SIR_MAC_MGMT_ACTION, peer);
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to populate the buffer descrip"
                               "tor for a Measurement Report (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return eSIR_FAILURE;    //                  
    }

    pMacHdr = ( tpSirMacMgmtHdr ) pFrame;

    nCfg = 6;
    nSirStatus = wlan_cfgGetStr( pMac, WNI_CFG_BSSID, pMacHdr->bssId, &nCfg );
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to retrieve WNI_CFG_BSSID from"
                               " CFG (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return eSIR_FAILURE;    //                  
    }

    nStatus = dot11fPackMeasurementReport( pMac, &frm, pFrame +
                                           sizeof(tSirMacMgmtHdr),
                                           nPayload, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to pack a Measurement Report (0x%08x).\n"),
                nStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return eSIR_FAILURE;    //           
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while packing a M"
                               "easurement Report (0x%08x).\n") );
    }

    halstatus = halTxFrame( pMac, pPacket, ( tANI_U16 ) nBytes,
                            HAL_TXRX_FRM_802_11_MGMT,
                            ANI_TXDIR_TODS,
                            7,//                           
                            limTxComplete, pFrame, 0 );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to send a Measurement Report  "
                               "(%X)!\n"),
                nSirStatus );
        //                                    
        return eSIR_FAILURE;    //                  
    }

    return eSIR_SUCCESS;

} //                            


/* 
                                         
  
  
                                                      
  
                                                            
  
  
 */

void
limSendTpcRequestFrame(tpAniSirGlobal pMac,
                       tSirMacAddr    peer)
{
    tDot11fTPCRequest  frm;
    tANI_U8                *pFrame;
    tSirRetStatus      nSirStatus;
    tpSirMacMgmtHdr    pMacHdr;
    tANI_U32                nBytes, nPayload, nStatus, nCfg;
    void               *pPacket;
    eHalStatus          halstatus;
   
    palZeroMemory( pMac->hHdd, ( tANI_U8* )&frm, sizeof( frm ) );

    frm.Category.category  = SIR_MAC_ACTION_SPECTRUM_MGMT;
    frm.Action.action      = SIR_MAC_ACTION_TPC_REQUEST_ID;
    frm.DialogToken.token  = 1;
    frm.TPCRequest.present = 1;

    nStatus = dot11fGetPackedTPCRequestSize( pMac, &frm, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to calculate the packed size f"
                               "or a TPC Request (0x%08x).\n"),
                nStatus );
        //                                            
        nPayload = sizeof( tDot11fTPCRequest );
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while calculating"
                               "the packed size for a TPC Request (0x"
                               "%08x).\n"), nStatus );
    }

    nBytes = nPayload + sizeof( tSirMacMgmtHdr );

    halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( tANI_U16 )nBytes, ( void** ) &pFrame, ( void** ) &pPacket );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to allocate %d bytes for a TPC"
                               " Request.\n"), nBytes );
        return;
    }

    //          
    palZeroMemory( pMac->hHdd, pFrame, nBytes );

    //                                         
    nSirStatus = limPopulateMacHeader( pMac, pFrame, SIR_MAC_MGMT_FRAME,
                                SIR_MAC_MGMT_ACTION, peer);
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to populate the buffer descrip"
                               "tor for a TPC Request (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return;                 //                  
    }

    pMacHdr = ( tpSirMacMgmtHdr ) pFrame;

    nCfg = 6;
    nSirStatus = wlan_cfgGetStr( pMac, WNI_CFG_BSSID, pMacHdr->bssId, &nCfg );
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to retrieve WNI_CFG_BSSID from"
                               " CFG (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return;                 //                  
    }

    nStatus = dot11fPackTPCRequest( pMac, &frm, pFrame +
                                    sizeof(tSirMacMgmtHdr),
                                    nPayload, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to pack a TPC Request (0x%08x).\n"),
                nStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return;                 //           
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while packing a T"
                               "PC Request (0x%08x).\n") );
    }

    halstatus = halTxFrame( pMac, pPacket, ( tANI_U16 ) nBytes,
                            HAL_TXRX_FRM_802_11_MGMT,
                            ANI_TXDIR_TODS,
                            7,//                           
                            limTxComplete, pFrame, 0 );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to send a TPC Request "
                               "(%X)!\n"),
                nSirStatus );
        //                                    
        return;
    }

} //                            


/* 
                                        
  
  
                                                      
  
                                                          
  
                                                     
  
  
 */

tSirRetStatus
limSendTpcReportFrame(tpAniSirGlobal            pMac,
                      tpSirMacTpcReqActionFrame pTpcReqFrame,
                      tSirMacAddr               peer)
{
    tDot11fTPCReport frm;
    tANI_U8              *pFrame;
    tSirRetStatus    nSirStatus;
    tpSirMacMgmtHdr  pMacHdr;
    tANI_U32              nBytes, nPayload, nStatus, nCfg;
    void               *pPacket;
    eHalStatus          halstatus;
   
    palZeroMemory( pMac->hHdd, ( tANI_U8* )&frm, sizeof( frm ) );

    frm.Category.category  = SIR_MAC_ACTION_SPECTRUM_MGMT;
    frm.Action.action      = SIR_MAC_ACTION_TPC_REPORT_ID;
    frm.DialogToken.token  = pTpcReqFrame->actionHeader.dialogToken;

    //                                                         
    //                                           
    //                                            
    //                                        
    frm.TPCReport.tx_power    = 0;
    frm.TPCReport.link_margin = 0;
    frm.TPCReport.present     = 1;

    nStatus = dot11fGetPackedTPCReportSize( pMac, &frm, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to calculate the packed size f"
                               "or a TPC Report (0x%08x).\n"),
                nStatus );
        //                                            
        nPayload = sizeof( tDot11fTPCReport );
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while calculating"
                               "the packed size for a TPC Report (0x"
                               "%08x).\n"), nStatus );
    }

    nBytes = nPayload + sizeof( tSirMacMgmtHdr );

    halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( tANI_U16 )nBytes, ( void** ) &pFrame, ( void** ) &pPacket );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to allocate %d bytes for a TPC"
                               " Report.\n"), nBytes );
        return eSIR_FAILURE;
    }

    //          
    palZeroMemory( pMac->hHdd, pFrame, nBytes );

    //                                         
    nSirStatus = limPopulateMacHeader( pMac, pFrame, SIR_MAC_MGMT_FRAME,
                                SIR_MAC_MGMT_ACTION, peer);
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to populate the buffer descrip"
                               "tor for a TPC Report (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return eSIR_FAILURE;    //                  
    }

    pMacHdr = ( tpSirMacMgmtHdr ) pFrame;

    nCfg = 6;
    nSirStatus = wlan_cfgGetStr( pMac, WNI_CFG_BSSID, pMacHdr->bssId, &nCfg );
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to retrieve WNI_CFG_BSSID from"
                               " CFG (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return eSIR_FAILURE;    //                  
    }

    nStatus = dot11fPackTPCReport( pMac, &frm, pFrame +
                                   sizeof(tSirMacMgmtHdr),
                                   nPayload, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to pack a TPC Report (0x%08x).\n"),
                nStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return eSIR_FAILURE;    //           
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while packing a T"
                               "PC Report (0x%08x).\n") );
    }


    halstatus = halTxFrame( pMac, pPacket, ( tANI_U16 ) nBytes,
                            HAL_TXRX_FRM_802_11_MGMT,
                            ANI_TXDIR_TODS,
                            7,//                           
                            limTxComplete, pFrame, 0 );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to send a TPC Report "
                               "(%X)!\n"),
                nSirStatus );
        //                                    
        return eSIR_FAILURE;    //                  
    }

    return eSIR_SUCCESS;

} //                           
#endif  //               


#if 1//                       
/* 
                                            
  
  
                                                      
  
                                                           
  
               
  
                     
  
                
  
                                                     
  
  
 */

tSirRetStatus
limSendChannelSwitchMgmtFrame(tpAniSirGlobal pMac,
                              tSirMacAddr    peer,
                              tANI_U8        nMode,
                              tANI_U8        nNewChannel,
                              tANI_U8        nCount,
                              tpPESession    psessionEntry )
{
    tDot11fChannelSwitch frm;
    tANI_U8                  *pFrame;
    tSirRetStatus        nSirStatus;
    tpSirMacMgmtHdr      pMacHdr;
    tANI_U32                  nBytes, nPayload, nStatus;//       
    void               *pPacket;
    eHalStatus          halstatus;
    tANI_U8 txFlag = 0;
    
    palZeroMemory( pMac->hHdd, ( tANI_U8* )&frm, sizeof( frm ) );

    frm.Category.category     = SIR_MAC_ACTION_SPECTRUM_MGMT;
    frm.Action.action         = SIR_MAC_ACTION_CHANNEL_SWITCH_ID;
    frm.ChanSwitchAnn.switchMode    = nMode;
    frm.ChanSwitchAnn.newChannel    = nNewChannel;
    frm.ChanSwitchAnn.switchCount   = nCount;
    frm.ChanSwitchAnn.present = 1;

    nStatus = dot11fGetPackedChannelSwitchSize( pMac, &frm, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to calculate the packed size f"
                               "or a Channel Switch (0x%08x).\n"),
                nStatus );
        //                                            
        nPayload = sizeof( tDot11fChannelSwitch );
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while calculating"
                               "the packed size for a Channel Switch (0x"
                               "%08x).\n"), nStatus );
    }

    nBytes = nPayload + sizeof( tSirMacMgmtHdr );

    halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( tANI_U16 )nBytes, ( void** ) &pFrame, ( void** ) &pPacket );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGP, FL("Failed to allocate %d bytes for a TPC"
                               " Report.\n"), nBytes );
        return eSIR_FAILURE;
    }

    //          
    palZeroMemory( pMac->hHdd, pFrame, nBytes );

    //                                         
    nSirStatus = limPopulateMacHeader( pMac, pFrame, SIR_MAC_MGMT_FRAME,
                                SIR_MAC_MGMT_ACTION, peer, psessionEntry->selfMacAddr);
    pMacHdr = ( tpSirMacMgmtHdr ) pFrame;
    palCopyMemory( pMac->hHdd,
                   (tANI_U8 *) pMacHdr->bssId,
                   (tANI_U8 *) psessionEntry->bssId,
                   sizeof( tSirMacAddr ));
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to populate the buffer descrip"
                               "tor for a Channel Switch (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return eSIR_FAILURE;    //                  
    }

#if 0
    pMacHdr = ( tpSirMacMgmtHdr ) pFrame;

    nCfg = 6;
    nSirStatus = wlan_cfgGetStr( pMac, WNI_CFG_BSSID, pMacHdr->bssId, &nCfg );
    if ( eSIR_SUCCESS != nSirStatus )
    {
        limLog( pMac, LOGE, FL("Failed to retrieve WNI_CFG_BSSID from"
                               " CFG (%d).\n"),
                nSirStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return eSIR_FAILURE;    //                  
    }
#endif
    nStatus = dot11fPackChannelSwitch( pMac, &frm, pFrame +
                                       sizeof(tSirMacMgmtHdr),
                                       nPayload, &nPayload );
    if ( DOT11F_FAILED( nStatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to pack a Channel Switch (0x%08x).\n"),
                nStatus );
        palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
        return eSIR_FAILURE;    //           
    }
    else if ( DOT11F_WARNED( nStatus ) )
    {
        limLog( pMac, LOGW, FL("There were warnings while packing a C"
                               "hannel Switch (0x%08x).\n") );
    }

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }
    halstatus = halTxFrame( pMac, pPacket, ( tANI_U16 ) nBytes,
                            HAL_TXRX_FRM_802_11_MGMT,
                            ANI_TXDIR_TODS,
                            7,//                           
                            limTxComplete, pFrame, txFlag );
    if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
    {
        limLog( pMac, LOGE, FL("Failed to send a Channel Switch "
                               "(%X)!\n"),
                nSirStatus );
        //                                    
        return eSIR_FAILURE;
    }

    return eSIR_SUCCESS;

} //                                   

#endif //                      


/* 
                                                
  
                      
  
                                               
  
                                                                  
                                                                
                    
  
                                                       
                                                      
 */
tSirRetStatus limSendAddBAReq( tpAniSirGlobal pMac,
    tpLimMlmAddBAReq pMlmAddBAReq ,tpPESession psessionEntry)
{
    tDot11fAddBAReq frmAddBAReq;
    tANI_U8 *pAddBAReqBuffer = NULL;
    tpSirMacMgmtHdr pMacHdr;
    tANI_U32 frameLen = 0, nStatus, nPayload;
    tSirRetStatus statusCode;
    eHalStatus halStatus;
    void *pPacket;
    tANI_U8 txFlag = 0;

     if(NULL == psessionEntry)
    {
        return eSIR_FAILURE;
    }

    palZeroMemory( pMac->hHdd, (void *) &frmAddBAReq, sizeof( frmAddBAReq ));

    //                  
    frmAddBAReq.Category.category = SIR_MAC_ACTION_BLKACK;
    
    //                       
    frmAddBAReq.Action.action = SIR_MAC_BLKACK_ADD_REQ;

    //                                         
    frmAddBAReq.DialogToken.token = pMlmAddBAReq->baDialogToken;

    //                             
    frmAddBAReq.AddBAParameterSet.tid = pMlmAddBAReq->baTID;
    frmAddBAReq.AddBAParameterSet.policy = pMlmAddBAReq->baPolicy;
    frmAddBAReq.AddBAParameterSet.bufferSize = pMlmAddBAReq->baBufferSize;

    //           
    //                            
    frmAddBAReq.BATimeout.timeout = pMlmAddBAReq->baTimeout;

  //                            
  //                                    
  if (pMlmAddBAReq->baSSN < LIM_TX_FRAMES_THRESHOLD_ON_CHIP) {
      pMlmAddBAReq->baSSN = LIM_TX_FRAMES_THRESHOLD_ON_CHIP;
  }
  
  frmAddBAReq.BAStartingSequenceControl.ssn = 
                pMlmAddBAReq->baSSN - LIM_TX_FRAMES_THRESHOLD_ON_CHIP;

    nStatus = dot11fGetPackedAddBAReqSize( pMac, &frmAddBAReq, &nPayload );

    if( DOT11F_FAILED( nStatus ))
    {
        limLog( pMac, LOGW,
        FL( "Failed to calculate the packed size for "
          "an ADDBA Request (0x%08x).\n"),
        nStatus );

        //                                            
        nPayload = sizeof( tDot11fAddBAReq );
    }
    else if( DOT11F_WARNED( nStatus ))
    {
        limLog( pMac, LOGW,
        FL( "There were warnings while calculating"
          "the packed size for an ADDBA Req (0x%08x).\n"),
        nStatus );
    }

    //                                    
    frameLen = nPayload + sizeof( tSirMacMgmtHdr );

    //                                       
    if( eHAL_STATUS_SUCCESS !=
      (halStatus = palPktAlloc( pMac->hHdd,
                                HAL_TXRX_FRM_802_11_MGMT,
                                (tANI_U16) frameLen,
                                (void **) &pAddBAReqBuffer,
                                (void **) &pPacket )))
    {
        //          
        limLog( pMac, LOGP,
        FL("palPktAlloc FAILED! Length [%d], Status [%d]\n"),
        frameLen,
        halStatus );

        statusCode = eSIR_MEM_ALLOC_FAILED;
        goto returnAfterError;
    }

    palZeroMemory( pMac->hHdd, (void *) pAddBAReqBuffer, frameLen );

    //                          
    if( eSIR_SUCCESS !=
      (statusCode = limPopulateMacHeader( pMac,
                                   pAddBAReqBuffer,
                                   SIR_MAC_MGMT_FRAME,
                                   SIR_MAC_MGMT_ACTION,
                                   pMlmAddBAReq->peerMacAddr,psessionEntry->selfMacAddr)))
    goto returnAfterError;

    //                         
    pMacHdr = ( tpSirMacMgmtHdr ) pAddBAReqBuffer;
    
    #if 0
    cfgLen = SIR_MAC_ADDR_LENGTH;
    if( eSIR_SUCCESS != cfgGetStr( pMac,
        WNI_CFG_BSSID,
        (tANI_U8 *) pMacHdr->bssId,
        &cfgLen ))
    {
        limLog( pMac, LOGP,
        FL( "Failed to retrieve WNI_CFG_BSSID while"
          "sending an ACTION Frame\n" ));

        //                                         
        statusCode = eSIR_FAILURE;
        goto returnAfterError;
    }
    #endif//                 
    sirCopyMacAddr(pMacHdr->bssId,psessionEntry->bssId);

    //                                      
    nStatus = dot11fPackAddBAReq( pMac,
      &frmAddBAReq,
      pAddBAReqBuffer + sizeof( tSirMacMgmtHdr ),
      nPayload,
      &nPayload );

    if( DOT11F_FAILED( nStatus ))
    {
        limLog( pMac, LOGE,
        FL( "Failed to pack an ADDBA Req (0x%08x).\n" ),
        nStatus );

        //                                         
        statusCode = eSIR_FAILURE;
        goto returnAfterError;
    }
    else if( DOT11F_WARNED( nStatus ))
    {
        limLog( pMac, LOGW,
        FL( "There were warnings while packing an ADDBA Req (0x%08x).\n" ));
    }

    limLog( pMac, LOGW,
      FL( "Sending an ADDBA REQ to \n" ));
    limPrintMacAddr( pMac, pMlmAddBAReq->peerMacAddr, LOGW );

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }

    if( eHAL_STATUS_SUCCESS !=
      (halStatus = halTxFrame( pMac,
                               pPacket,
                               (tANI_U16) frameLen,
                               HAL_TXRX_FRM_802_11_MGMT,
                               ANI_TXDIR_TODS,
                               7,//                           
                               limTxComplete,
                               pAddBAReqBuffer, txFlag )))
    {
        limLog( pMac, LOGE,
        FL( "halTxFrame FAILED! Status [%d]\n"),
        halStatus );

    //                                                    
    statusCode = eSIR_FAILURE;
    //                                    
    return statusCode;
  }
  else
    return eSIR_SUCCESS;

returnAfterError:

  //                             
  if( NULL != pAddBAReqBuffer )
    palPktFree( pMac->hHdd,
        HAL_TXRX_FRM_802_11_MGMT,
        (void *) pAddBAReqBuffer,
        (void *) pPacket );

  return statusCode;
}

/* 
                                                
  
                      
  
                                               
  
                                                                  
                                                                
                    
  
                                                       
                                                      
 */
tSirRetStatus limSendAddBARsp( tpAniSirGlobal pMac,
    tpLimMlmAddBARsp pMlmAddBARsp,
    tpPESession      psessionEntry)
{
    tDot11fAddBARsp frmAddBARsp;
    tANI_U8 *pAddBARspBuffer = NULL;
    tpSirMacMgmtHdr pMacHdr;
    tANI_U32 frameLen = 0, nStatus, nPayload;
    tSirRetStatus statusCode;
    eHalStatus halStatus;
    void *pPacket;
    tANI_U8 txFlag = 0;

     if(NULL == psessionEntry)
    {
        PELOGE(limLog(pMac, LOGE, FL("Session entry is NULL!!!\n"));)
        return eSIR_FAILURE;
    }

      palZeroMemory( pMac->hHdd, (void *) &frmAddBARsp, sizeof( frmAddBARsp ));

      //                  
      frmAddBARsp.Category.category = SIR_MAC_ACTION_BLKACK;
      //                       
      frmAddBARsp.Action.action = SIR_MAC_BLKACK_ADD_RSP;

      //                                                       
      frmAddBARsp.DialogToken.token = pMlmAddBARsp->baDialogToken;

      //                 
      frmAddBARsp.Status.status = pMlmAddBARsp->addBAResultCode;

      //                                                   
      frmAddBARsp.AddBAParameterSet.tid = pMlmAddBARsp->baTID;
      frmAddBARsp.AddBAParameterSet.policy = pMlmAddBARsp->baPolicy;
      frmAddBARsp.AddBAParameterSet.bufferSize = pMlmAddBARsp->baBufferSize;

      //           
      //                            
      frmAddBARsp.BATimeout.timeout = pMlmAddBARsp->baTimeout;

      nStatus = dot11fGetPackedAddBARspSize( pMac, &frmAddBARsp, &nPayload );

      if( DOT11F_FAILED( nStatus ))
      {
        limLog( pMac, LOGW,
            FL( "Failed to calculate the packed size for "
              "an ADDBA Response (0x%08x).\n"),
            nStatus );

        //                                            
        nPayload = sizeof( tDot11fAddBARsp );
      }
      else if( DOT11F_WARNED( nStatus ))
      {
        limLog( pMac, LOGW,
            FL( "There were warnings while calculating"
              "the packed size for an ADDBA Rsp (0x%08x).\n"),
            nStatus );
      }

      //                                       
      frameLen = nPayload + sizeof( tSirMacMgmtHdr );

      //                       
      if( eHAL_STATUS_SUCCESS !=
          (halStatus = palPktAlloc( pMac->hHdd,
                                    HAL_TXRX_FRM_802_11_MGMT,
                                    (tANI_U16) frameLen,
                                    (void **) &pAddBARspBuffer,
                                    (void **) &pPacket )))
      {
        //          
        limLog( pMac, LOGP,
            FL("palPktAlloc FAILED! Length [%d], Status [%d]\n"),
            frameLen,
            halStatus );

        statusCode = eSIR_MEM_ALLOC_FAILED;
        goto returnAfterError;
      }

      palZeroMemory( pMac->hHdd, (void *) pAddBARspBuffer, frameLen );

      //                          
      if( eSIR_SUCCESS !=
          (statusCode = limPopulateMacHeader( pMac,
                                       pAddBARspBuffer,
                                       SIR_MAC_MGMT_FRAME,
                                       SIR_MAC_MGMT_ACTION,
                                       pMlmAddBARsp->peerMacAddr,psessionEntry->selfMacAddr)))
        goto returnAfterError;

      //                         
      
      pMacHdr = ( tpSirMacMgmtHdr ) pAddBARspBuffer;
      
      #if 0
      cfgLen = SIR_MAC_ADDR_LENGTH;
      if( eSIR_SUCCESS != wlan_cfgGetStr( pMac,
            WNI_CFG_BSSID,
            (tANI_U8 *) pMacHdr->bssId,
            &cfgLen ))
      {
        limLog( pMac, LOGP,
            FL( "Failed to retrieve WNI_CFG_BSSID while"
              "sending an ACTION Frame\n" ));

        //                                         
        statusCode = eSIR_FAILURE;
        goto returnAfterError;
      }
      #endif //                  
      sirCopyMacAddr(pMacHdr->bssId,psessionEntry->bssId);

      //                                      
      nStatus = dot11fPackAddBARsp( pMac,
          &frmAddBARsp,
          pAddBARspBuffer + sizeof( tSirMacMgmtHdr ),
          nPayload,
          &nPayload );

      if( DOT11F_FAILED( nStatus ))
      {
        limLog( pMac, LOGE,
            FL( "Failed to pack an ADDBA Rsp (0x%08x).\n" ),
            nStatus );

        //                                         
        statusCode = eSIR_FAILURE;
        goto returnAfterError;
      }
      else if( DOT11F_WARNED( nStatus ))
      {
        limLog( pMac, LOGW,
            FL( "There were warnings while packing an ADDBA Rsp (0x%08x).\n" ));
      }

      limLog( pMac, LOGW,
          FL( "Sending an ADDBA RSP to \n" ));
      limPrintMacAddr( pMac, pMlmAddBARsp->peerMacAddr, LOGW );

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }

  if( eHAL_STATUS_SUCCESS !=
      (halStatus = halTxFrame( pMac,
                               pPacket,
                               (tANI_U16) frameLen,
                               HAL_TXRX_FRM_802_11_MGMT,
                               ANI_TXDIR_TODS,
                               7,//                           
                               limTxComplete,
                               pAddBARspBuffer, txFlag )))
  {
    limLog( pMac, LOGE,
        FL( "halTxFrame FAILED! Status [%d]\n" ),
        halStatus );

    //                                                    
    //                                                     
    statusCode = eSIR_FAILURE;
    //                                    
    return statusCode;
  }
  else
    return eSIR_SUCCESS;

    returnAfterError:

      //                             
      if( NULL != pAddBARspBuffer )
        palPktFree( pMac->hHdd,
            HAL_TXRX_FRM_802_11_MGMT,
            (void *) pAddBARspBuffer,
            (void *) pPacket );

      return statusCode;
}

/* 
                                                      
  
                      
  
                                               
  
                                         
  
                                                      
  
                                                  
                                                      
                 
  
                                                       
                                                      
 */
tSirRetStatus limSendDelBAInd( tpAniSirGlobal pMac,
    tpLimMlmDelBAReq pMlmDelBAReq,tpPESession psessionEntry)
{
    tDot11fDelBAInd frmDelBAInd;
    tANI_U8 *pDelBAIndBuffer = NULL;
    //             
    tpSirMacMgmtHdr pMacHdr;
    tANI_U32 frameLen = 0, nStatus, nPayload;
    tSirRetStatus statusCode;
    eHalStatus halStatus;
    void *pPacket;
    tANI_U8 txFlag = 0;

     if(NULL == psessionEntry)
    {
        return eSIR_FAILURE;
    }

    palZeroMemory( pMac->hHdd, (void *) &frmDelBAInd, sizeof( frmDelBAInd ));

      //                  
      frmDelBAInd.Category.category = SIR_MAC_ACTION_BLKACK;
      //                   
      frmDelBAInd.Action.action = SIR_MAC_BLKACK_DEL;

      //                                                   
      frmDelBAInd.DelBAParameterSet.tid = pMlmDelBAReq->baTID;
      frmDelBAInd.DelBAParameterSet.initiator = pMlmDelBAReq->baDirection;

      //                            
      //                                    
      frmDelBAInd.Reason.code = pMlmDelBAReq->delBAReasonCode;

      nStatus = dot11fGetPackedDelBAIndSize( pMac, &frmDelBAInd, &nPayload );

      if( DOT11F_FAILED( nStatus ))
      {
        limLog( pMac, LOGW,
            FL( "Failed to calculate the packed size for "
              "an DELBA Indication (0x%08x).\n"),
            nStatus );

        //                                            
        nPayload = sizeof( tDot11fDelBAInd );
      }
      else if( DOT11F_WARNED( nStatus ))
      {
        limLog( pMac, LOGW,
            FL( "There were warnings while calculating"
              "the packed size for an DELBA Ind (0x%08x).\n"),
            nStatus );
      }

      //                                    
      frameLen = nPayload + sizeof( tSirMacMgmtHdr );

      //                       
      if( eHAL_STATUS_SUCCESS !=
          (halStatus = palPktAlloc( pMac->hHdd,
                                    HAL_TXRX_FRM_802_11_MGMT,
                                    (tANI_U16) frameLen,
                                    (void **) &pDelBAIndBuffer,
                                    (void **) &pPacket )))
      {
        //          
        limLog( pMac, LOGP,
            FL("palPktAlloc FAILED! Length [%d], Status [%d]\n"),
            frameLen,
            halStatus );

        statusCode = eSIR_MEM_ALLOC_FAILED;
        goto returnAfterError;
      }

      palZeroMemory( pMac->hHdd, (void *) pDelBAIndBuffer, frameLen );

      //                          
      if( eSIR_SUCCESS !=
          (statusCode = limPopulateMacHeader( pMac,
                                       pDelBAIndBuffer,
                                       SIR_MAC_MGMT_FRAME,
                                       SIR_MAC_MGMT_ACTION,
                                       pMlmDelBAReq->peerMacAddr,psessionEntry->selfMacAddr)))
        goto returnAfterError;

      //                         
      pMacHdr = ( tpSirMacMgmtHdr ) pDelBAIndBuffer;
      
      #if 0
      cfgLen = SIR_MAC_ADDR_LENGTH;
      if( eSIR_SUCCESS != cfgGetStr( pMac,
            WNI_CFG_BSSID,
            (tANI_U8 *) pMacHdr->bssId,
            &cfgLen ))
      {
        limLog( pMac, LOGP,
            FL( "Failed to retrieve WNI_CFG_BSSID while"
              "sending an ACTION Frame\n" ));

        //                                         
        statusCode = eSIR_FAILURE;
        goto returnAfterError;
      }
      #endif //                 
      sirCopyMacAddr(pMacHdr->bssId,psessionEntry->bssId);

      //                                      
      nStatus = dot11fPackDelBAInd( pMac,
          &frmDelBAInd,
          pDelBAIndBuffer + sizeof( tSirMacMgmtHdr ),
          nPayload,
          &nPayload );

      if( DOT11F_FAILED( nStatus ))
      {
        limLog( pMac, LOGE,
            FL( "Failed to pack an DELBA Ind (0x%08x).\n" ),
            nStatus );

        //                                         
        statusCode = eSIR_FAILURE;
        goto returnAfterError;
      }
      else if( DOT11F_WARNED( nStatus ))
      {
        limLog( pMac, LOGW,
            FL( "There were warnings while packing an DELBA Ind (0x%08x).\n" ));
      }

      limLog( pMac, LOGW,
          FL( "Sending a DELBA IND to \n" ));
      limPrintMacAddr( pMac, pMlmDelBAReq->peerMacAddr, LOGW );

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }

  if( eHAL_STATUS_SUCCESS !=
      (halStatus = halTxFrame( pMac,
                               pPacket,
                               (tANI_U16) frameLen,
                               HAL_TXRX_FRM_802_11_MGMT,
                               ANI_TXDIR_TODS,
                               7,//                           
                               limTxComplete,
                               pDelBAIndBuffer, txFlag )))
  {
    PELOGE(limLog( pMac, LOGE, FL( "halTxFrame FAILED! Status [%d]\n" ), halStatus );)
    statusCode = eSIR_FAILURE;
    //                                    
    return statusCode;
  }
  else
    return eSIR_SUCCESS;

    returnAfterError:

      //                             
      if( NULL != pDelBAIndBuffer )
        palPktFree( pMac->hHdd,
            HAL_TXRX_FRM_802_11_MGMT,
            (void *) pDelBAIndBuffer,
            (void *) pPacket );

      return statusCode;
}

#if defined WLAN_FEATURE_VOWIFI

/* 
                                                     
  
  
                                                  
  
                                                            
  
                                           
  
                                                 
  
                                                     
  
  
 */

tSirRetStatus
limSendNeighborReportRequestFrame(tpAniSirGlobal        pMac,
                       tpSirMacNeighborReportReq pNeighborReq,
                       tSirMacAddr                peer,
                       tpPESession psessionEntry
                       )
{
   tSirRetStatus statusCode = eSIR_SUCCESS;
   tDot11fNeighborReportRequest frm;
   tANI_U8                      *pFrame;
   tpSirMacMgmtHdr          pMacHdr;
   tANI_U32                      nBytes, nPayload, nStatus;
   void               *pPacket;
   eHalStatus          halstatus;
   tANI_U8             txFlag = 0;

   if ( psessionEntry == NULL )
   {
      limLog( pMac, LOGE, FL("(psession == NULL) in Request to send Neighbor Report request action frame\n") );
      return eSIR_FAILURE;
   }
   palZeroMemory( pMac->hHdd, ( tANI_U8* )&frm, sizeof( frm ) );

   frm.Category.category = SIR_MAC_ACTION_RRM;
   frm.Action.action     = SIR_MAC_RRM_NEIGHBOR_REQ;
   frm.DialogToken.token = pNeighborReq->dialogToken;


   if( pNeighborReq->ssid_present )
   {
      PopulateDot11fSSID( pMac, &pNeighborReq->ssid, &frm.SSID );
   }

   nStatus = dot11fGetPackedNeighborReportRequestSize( pMac, &frm, &nPayload );
   if ( DOT11F_FAILED( nStatus ) )
   {
      limLog( pMac, LOGP, FL("Failed to calculate the packed size f"
               "or a Neighbor Report Request(0x%08x).\n"),
            nStatus );
      //                                            
      nPayload = sizeof( tDot11fNeighborReportRequest );
   }
   else if ( DOT11F_WARNED( nStatus ) )
   {
      limLog( pMac, LOGW, FL("There were warnings while calculating"
               "the packed size for a Neighbor Rep"
               "ort Request(0x%08x).\n"), nStatus );
   }

   nBytes = nPayload + sizeof( tSirMacMgmtHdr );

   halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( tANI_U16 )nBytes, ( void** ) &pFrame, ( void** ) &pPacket );
   if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
   {
      limLog( pMac, LOGP, FL("Failed to allocate %d bytes for a Neighbor "
               "Report Request.\n"), nBytes );
      return eSIR_FAILURE;
   }

   //          
   palZeroMemory( pMac->hHdd, pFrame, nBytes );

   //                          
   if( eSIR_SUCCESS !=
         (statusCode = limPopulateMacHeader( pMac,
                                      pFrame,
                                      SIR_MAC_MGMT_FRAME,
                                      SIR_MAC_MGMT_ACTION,
                                      peer, psessionEntry->selfMacAddr)))
      goto returnAfterError;

   //                         
   pMacHdr = ( tpSirMacMgmtHdr ) pFrame;

   sirCopyMacAddr( pMacHdr->bssId, psessionEntry->bssId );

   //                                      
   nStatus = dot11fPackNeighborReportRequest( pMac,
         &frm,
         pFrame + sizeof( tSirMacMgmtHdr ),
         nPayload,
         &nPayload );

   if( DOT11F_FAILED( nStatus ))
   {
      limLog( pMac, LOGE,
            FL( "Failed to pack an Neighbor Report Request (0x%08x).\n" ),
            nStatus );

      //                                         
      statusCode = eSIR_FAILURE;
      goto returnAfterError;
   }
   else if( DOT11F_WARNED( nStatus ))
   {
      limLog( pMac, LOGW,
            FL( "There were warnings while packing Neighbor Report Request (0x%08x).\n" ));
   }

   limLog( pMac, LOGW,
         FL( "Sending a Neighbor Report Request to \n" ));
   limPrintMacAddr( pMac, peer, LOGW );

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }

   if( eHAL_STATUS_SUCCESS !=
         (halstatus = halTxFrame( pMac,
                                  pPacket,
                                  (tANI_U16) nBytes,
                                  HAL_TXRX_FRM_802_11_MGMT,
                                  ANI_TXDIR_TODS,
                                  7,//                           
                                  limTxComplete,
                                  pFrame, txFlag )))
   {
      PELOGE(limLog( pMac, LOGE, FL( "halTxFrame FAILED! Status [%d]\n" ), halstatus );)
         statusCode = eSIR_FAILURE;
      //                                    
      return statusCode;
   }
   else
      return eSIR_SUCCESS;

returnAfterError:
   palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );

   return statusCode;
} //                                       

/* 
                                         
  
  
                                                  
  
                                                    
  
                                           
  
                                                 
  
                                                     
  
  
 */

tSirRetStatus
limSendLinkReportActionFrame(tpAniSirGlobal        pMac,
                       tpSirMacLinkReport pLinkReport,
                       tSirMacAddr                peer,
                       tpPESession psessionEntry
                       )
{
   tSirRetStatus statusCode = eSIR_SUCCESS;
   tDot11fLinkMeasurementReport frm;
   tANI_U8                      *pFrame;
   tpSirMacMgmtHdr          pMacHdr;
   tANI_U32                      nBytes, nPayload, nStatus;
   void               *pPacket;
   eHalStatus          halstatus;
   tANI_U8             txFlag = 0;


   if ( psessionEntry == NULL )
   {
      limLog( pMac, LOGE, FL("(psession == NULL) in Request to send Link Report action frame\n") );
      return eSIR_FAILURE;
   }

   palZeroMemory( pMac->hHdd, ( tANI_U8* )&frm, sizeof( frm ) );

   frm.Category.category = SIR_MAC_ACTION_RRM;
   frm.Action.action     = SIR_MAC_RRM_LINK_MEASUREMENT_RPT;
   frm.DialogToken.token = pLinkReport->dialogToken;


   //                                                  
   //                                                                                         
   //                                                                                             
   //                                                                                           
   //                                                  
   frm.TPCEleID.TPCId = SIR_MAC_TPC_RPT_EID; 
   frm.TPCEleLen.TPCLen = 2;
   frm.TxPower.txPower = pLinkReport->txPower;
   frm.LinkMargin.linkMargin = 0;

   frm.RxAntennaId.antennaId = pLinkReport->rxAntenna;
   frm.TxAntennaId.antennaId = pLinkReport->txAntenna;
   frm.RCPI.rcpi = pLinkReport->rcpi;
   frm.RSNI.rsni = pLinkReport->rsni;

   nStatus = dot11fGetPackedLinkMeasurementReportSize( pMac, &frm, &nPayload );
   if ( DOT11F_FAILED( nStatus ) )
   {
      limLog( pMac, LOGP, FL("Failed to calculate the packed size f"
               "or a Link Report (0x%08x).\n"),
            nStatus );
      //                                            
      nPayload = sizeof( tDot11fLinkMeasurementReport );
   }
   else if ( DOT11F_WARNED( nStatus ) )
   {
      limLog( pMac, LOGW, FL("There were warnings while calculating"
               "the packed size for a Link Rep"
               "ort (0x%08x).\n"), nStatus );
   }

   nBytes = nPayload + sizeof( tSirMacMgmtHdr );

   halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( tANI_U16 )nBytes, ( void** ) &pFrame, ( void** ) &pPacket );
   if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
   {
      limLog( pMac, LOGP, FL("Failed to allocate %d bytes for a Link "
               "Report.\n"), nBytes );
      return eSIR_FAILURE;
   }

   //          
   palZeroMemory( pMac->hHdd, pFrame, nBytes );

   //                          
   if( eSIR_SUCCESS !=
         (statusCode = limPopulateMacHeader( pMac,
                                      pFrame,
                                      SIR_MAC_MGMT_FRAME,
                                      SIR_MAC_MGMT_ACTION,
                                      peer, psessionEntry->selfMacAddr)))
      goto returnAfterError;

   //                         
   pMacHdr = ( tpSirMacMgmtHdr ) pFrame;

   sirCopyMacAddr( pMacHdr->bssId, psessionEntry->bssId );

   //                                      
   nStatus = dot11fPackLinkMeasurementReport( pMac,
         &frm,
         pFrame + sizeof( tSirMacMgmtHdr ),
         nPayload,
         &nPayload );

   if( DOT11F_FAILED( nStatus ))
   {
      limLog( pMac, LOGE,
            FL( "Failed to pack an Link Report (0x%08x).\n" ),
            nStatus );

      //                                         
      statusCode = eSIR_FAILURE;
      goto returnAfterError;
   }
   else if( DOT11F_WARNED( nStatus ))
   {
      limLog( pMac, LOGW,
            FL( "There were warnings while packing Link Report (0x%08x).\n" ));
   }

   limLog( pMac, LOGW,
         FL( "Sending a Link Report to \n" ));
   limPrintMacAddr( pMac, peer, LOGW );

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }

   if( eHAL_STATUS_SUCCESS !=
         (halstatus = halTxFrame( pMac,
                                  pPacket,
                                  (tANI_U16) nBytes,
                                  HAL_TXRX_FRM_802_11_MGMT,
                                  ANI_TXDIR_TODS,
                                  7,//                           
                                  limTxComplete,
                                  pFrame, txFlag )))
   {
      PELOGE(limLog( pMac, LOGE, FL( "halTxFrame FAILED! Status [%d]\n" ), halstatus );)
         statusCode = eSIR_FAILURE;
      //                                    
      return statusCode;
   }
   else
      return eSIR_SUCCESS;

returnAfterError:
   palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );

   return statusCode;
} //                                  

/* 
                                           
  
  
                                                  
  
                                                                   
  
                                                     
  
                                                            
  
                                           
  
                                                 
  
                                                     
  
  
 */

tSirRetStatus
limSendRadioMeasureReportActionFrame(tpAniSirGlobal        pMac,
                       tANI_U8              dialog_token,
                       tANI_U8              num_report,
                       tpSirMacRadioMeasureReport pRRMReport,
                       tSirMacAddr                peer,
                       tpPESession psessionEntry
                       )
{
   tSirRetStatus statusCode = eSIR_SUCCESS;
   tANI_U8                      *pFrame;
   tpSirMacMgmtHdr          pMacHdr;
   tANI_U32                      nBytes, nPayload, nStatus;
   void               *pPacket;
   eHalStatus          halstatus;
   tANI_U8             i;
   tANI_U8             txFlag = 0;

   tDot11fRadioMeasurementReport *frm =
         vos_mem_malloc(sizeof(tDot11fRadioMeasurementReport));
   if (!frm) {
      limLog( pMac, LOGE, FL("Not enough memory to allocate tDot11fRadioMeasurementReport\n") );
      return eSIR_FAILURE;
   }

   if ( psessionEntry == NULL )
   {
      limLog( pMac, LOGE, FL("(psession == NULL) in Request to send Beacon Report action frame\n") );
      vos_mem_free(frm);
      return eSIR_FAILURE;
   }
   palZeroMemory( pMac->hHdd, ( tANI_U8* )frm, sizeof( *frm ) );

   frm->Category.category = SIR_MAC_ACTION_RRM;
   frm->Action.action     = SIR_MAC_RRM_RADIO_MEASURE_RPT;
   frm->DialogToken.token = dialog_token;

   frm->num_MeasurementReport = (num_report > RADIO_REPORTS_MAX_IN_A_FRAME ) ? RADIO_REPORTS_MAX_IN_A_FRAME  : num_report;

   for( i = 0 ; i < frm->num_MeasurementReport ; i++ )
   {
      frm->MeasurementReport[i].type = pRRMReport[i].type;
      frm->MeasurementReport[i].token = pRRMReport[i].token;
      frm->MeasurementReport[i].late = 0; //                                                 
      switch( pRRMReport[i].type )
      {
         case SIR_MAC_RRM_BEACON_TYPE:
            PopulateDot11fBeaconReport( pMac, &frm->MeasurementReport[i], &pRRMReport[i].report.beaconReport );
            frm->MeasurementReport[i].incapable = pRRMReport[i].incapable;
            frm->MeasurementReport[i].refused = pRRMReport[i].refused;
            frm->MeasurementReport[i].present = 1;
            break;
         default:
            frm->MeasurementReport[i].present = 1;
            break;
      }
   }

   nStatus = dot11fGetPackedRadioMeasurementReportSize( pMac, frm, &nPayload );
   if ( DOT11F_FAILED( nStatus ) )
   {
      limLog( pMac, LOGP, FL("Failed to calculate the packed size f"
               "or a Radio Measure Report (0x%08x).\n"),
            nStatus );
      //                                            
      nPayload = sizeof( tDot11fLinkMeasurementReport );
      vos_mem_free(frm);
      return eSIR_FAILURE;
   }
   else if ( DOT11F_WARNED( nStatus ) )
   {
      limLog( pMac, LOGW, FL("There were warnings while calculating"
               "the packed size for a Radio Measure Rep"
               "ort (0x%08x).\n"), nStatus );
   }

   nBytes = nPayload + sizeof( tSirMacMgmtHdr );

   halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( tANI_U16 )nBytes, ( void** ) &pFrame, ( void** ) &pPacket );
   if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
   {
      limLog( pMac, LOGP, FL("Failed to allocate %d bytes for a Radio Measure "
               "Report.\n"), nBytes );
      vos_mem_free(frm);
      return eSIR_FAILURE;
   }

   //          
   palZeroMemory( pMac->hHdd, pFrame, nBytes );

   //                          
   if( eSIR_SUCCESS !=
         (statusCode = limPopulateMacHeader( pMac,
                                      pFrame,
                                      SIR_MAC_MGMT_FRAME,
                                      SIR_MAC_MGMT_ACTION,
                                      peer, psessionEntry->selfMacAddr)))
      goto returnAfterError;

   //                         
   pMacHdr = ( tpSirMacMgmtHdr ) pFrame;

   sirCopyMacAddr( pMacHdr->bssId, psessionEntry->bssId );

   //                                      
   nStatus = dot11fPackRadioMeasurementReport( pMac,
         frm,
         pFrame + sizeof( tSirMacMgmtHdr ),
         nPayload,
         &nPayload );

   if( DOT11F_FAILED( nStatus ))
   {
      limLog( pMac, LOGE,
            FL( "Failed to pack an Radio Measure Report (0x%08x).\n" ),
            nStatus );

      //                                         
      statusCode = eSIR_FAILURE;
      goto returnAfterError;
   }
   else if( DOT11F_WARNED( nStatus ))
   {
      limLog( pMac, LOGW,
            FL( "There were warnings while packing Radio Measure Report (0x%08x).\n" ));
   }

   limLog( pMac, LOGW,
         FL( "Sending a Radio Measure Report to \n" ));
   limPrintMacAddr( pMac, peer, LOGW );

    if( ( SIR_BAND_5_GHZ == limGetRFBand(psessionEntry->currentOperChannel))
#ifdef WLAN_FEATURE_P2P
       || ( psessionEntry->pePersona == VOS_P2P_CLIENT_MODE ) ||
         ( psessionEntry->pePersona == VOS_P2P_GO_MODE)
#endif
         )
    {
        txFlag |= HAL_USE_BD_RATE2_FOR_MANAGEMENT_FRAME;
    }

   if( eHAL_STATUS_SUCCESS !=
         (halstatus = halTxFrame( pMac,
                                  pPacket,
                                  (tANI_U16) nBytes,
                                  HAL_TXRX_FRM_802_11_MGMT,
                                  ANI_TXDIR_TODS,
                                  7,//                           
                                  limTxComplete,
                                  pFrame, txFlag )))
   {
      PELOGE(limLog( pMac, LOGE, FL( "halTxFrame FAILED! Status [%d]\n" ), halstatus );)
         statusCode = eSIR_FAILURE;
      //                                    
      vos_mem_free(frm);
      return statusCode;
   }
   else {
      vos_mem_free(frm);
      return eSIR_SUCCESS;
   }

returnAfterError:
   vos_mem_free(frm);
   palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
   return statusCode;
} //                                    

#endif

#ifdef WLAN_FEATURE_11W
/* 
                                                      
  
                                  
   
  
                                                  
  
                                                                          
         
  
                                                                             
      
   
                                                       
                                                      
 */

tSirRetStatus limSendSaQueryResponseFrame( tpAniSirGlobal pMac, tANI_U16 transId,
tSirMacAddr peer,tpPESession psessionEntry)
{

   tDot11wSaQueryRsp  frm; //                              
   tANI_U8            *pFrame;
   tSirRetStatus      nSirStatus;
   tpSirMacMgmtHdr    pMacHdr;
   tANI_U32           nBytes, nPayload;
   void               *pPacket;
   eHalStatus         halstatus;
   //                                                              
   tANI_U8            *pDump; 
   tANI_U16           dumpCount;
   tANI_U8             txFlag = 0;
   //               
   
   palZeroMemory( pMac->hHdd, ( tANI_U8* )&frm, sizeof( frm ) );
   frm.category  = SIR_MAC_ACTION_SA_QUERY;
   /*                      
                                               
                                                 */ 
   frm.action    = 1;
   /*                                                 
                             */
   frm.transId   = transId;

   nPayload = sizeof(tDot11wSaQueryRsp);
   nBytes = nPayload + sizeof( tSirMacMgmtHdr );
   halstatus = palPktAlloc( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT,  nBytes, ( void** ) &pFrame, ( void** ) &pPacket );
   if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
   {
      limLog( pMac, LOGP, FL("Failed to allocate %d bytes for a SA query response"
                               " action frame\n"), nBytes );
      return eSIR_FAILURE;
   }

   //          
   palZeroMemory( pMac->hHdd, pFrame, nBytes );

   //                                         
   nSirStatus = limPopulateMacHeader( pMac, pFrame, SIR_MAC_MGMT_FRAME,
                                SIR_MAC_MGMT_ACTION, peer,psessionEntry->selfMacAddr );
   if ( eSIR_SUCCESS != nSirStatus )
   {
      limLog( pMac, LOGE, FL("Failed to populate the buffer descrip"
                              "tor for a TPC Report (%d).\n"),
               nSirStatus );
      palPktFree( pMac->hHdd, HAL_TXRX_FRM_802_11_MGMT, ( void* ) pFrame, ( void* ) pPacket );
      return eSIR_FAILURE;    //                  
   }

   pMacHdr = ( tpSirMacMgmtHdr ) pFrame;

   //                                 
   DOT11F_MEMCPY(pMac, (tANI_U8 *)(pFrame + sizeof(tSirMacMgmtHdr)),(tANI_U8 *)&frm, nPayload);
   pDump = (tANI_U8 *) pFrame;

   halstatus = halTxFrame( pMac, pPacket, ( tANI_U16 ) nBytes,
                            HAL_TXRX_FRM_802_11_MGMT,
                            ANI_TXDIR_TODS,
                            7,//                           
                            limTxComplete, pFrame,txFlag);
   if ( ! HAL_STATUS_SUCCESS ( halstatus ) )
   {
      limLog( pMac, LOGE, FL("Failed to send a SA Query resp frame "
                             "(%X)!\n"),halstatus );
        //                                    
      return eSIR_FAILURE;    //                  
   }

   return eSIR_SUCCESS;
}
#endif
