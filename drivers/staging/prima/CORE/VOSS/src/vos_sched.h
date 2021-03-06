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

#if !defined( __VOS_SCHED_H )
#define __VOS_SCHED_H

/**=========================================================================
  
  \file  vos_sched.h
  
  \brief virtual Operating System Servies (vOSS)
               
   Definitions for some of the internal data type that is internally used 
   by the vOSS scheduler on Windows Mobile.
   
   This file defines a vOSS message queue on Win Mobile and give some
   insights about how the scheduler implements the execution model supported
   by vOSS.
    
  
   Copyright 2008 (c) Qualcomm, Incorporated.  All Rights Reserved.
   
   Qualcomm Confidential and Proprietary.
  
  ========================================================================*/

/*                                                                            
    
                                             
   
   
                                                                        
                                                                 
   
   
                                    
   
   
                                      
                                                                             
                                                             
                                     
     
                                                                           */ 

/*                                                                          
               
                                                                          */
#include <vos_event.h>
#include "i_vos_types.h"
#include "i_vos_packet.h"
#include <linux/wait.h>
#include <linux/wakelock.h>
#include <vos_power.h>

#define TX_POST_EVENT_MASK               0x001
#define TX_SUSPEND_EVENT_MASK            0x002
#define MC_POST_EVENT_MASK               0x001
#define MC_SUSPEND_EVENT_MASK            0x002
#ifdef FEATURE_WLAN_INTEGRATED_SOC
#define RX_POST_EVENT_MASK               0x001
#define RX_SUSPEND_EVENT_MASK            0x002
#endif
#define TX_SHUTDOWN_EVENT_MASK           0x010
#define MC_SHUTDOWN_EVENT_MASK           0x010
#ifdef FEATURE_WLAN_INTEGRATED_SOC
#define RX_SHUTDOWN_EVENT_MASK           0x010
#endif
#define WD_POST_EVENT_MASK               0x001
#define WD_SHUTDOWN_EVENT_MASK           0x002
#define WD_CHIP_RESET_EVENT_MASK         0x004
#define WD_WLAN_SHUTDOWN_EVENT_MASK      0x008
#define WD_WLAN_REINIT_EVENT_MASK        0x010

 
 
/*
                                           
                                                         
                                              
                                                   
                                                    
            
*/
#define VOS_CORE_MAX_MESSAGES           (VPKT_NUM_RX_RAW_PACKETS + 32)


/*
                                 
*/
typedef struct _VosMqType
{
  /*                                                      */
  spinlock_t       mqLock;

  /*                                            */
  struct list_head  mqList;

} VosMqType, *pVosMqType;


/*
                         
                                                
                           
                               
                                                                            
      
*/
typedef struct _VosSchedContext
{
  /*                                  */ 
   v_PVOID_t           pVContext; 
#ifndef FEATURE_WLAN_INTEGRATED_SOC
  /*                                     */
   VosMqType           halMcMq;
#else
  /*                                     */
   VosMqType           wdaMcMq;
#endif



   /*                                    */
   VosMqType           peMcMq;

   /*                                     */
   VosMqType           smeMcMq;

   /*                                     */
   VosMqType           tlMcMq;

   /*                                      */
   VosMqType           sysMcMq;

#ifndef FEATURE_WLAN_INTEGRATED_SOC
   /*                             */
   VosMqType           sscTxMq;
#else
  /*                                     */
   VosMqType           wdiMcMq;

   /*                                   */
   VosMqType           wdiTxMq;

   /*                                   */
   VosMqType           wdiRxMq;
#endif

   /*                                   */
   VosMqType           tlTxMq;

   /*                                    */
   VosMqType           sysTxMq;

#ifdef FEATURE_WLAN_INTEGRATED_SOC
   VosMqType           sysRxMq;
#endif

   /*                                                 */
   struct completion   McStartEvent;

   /*                                                 */
   struct completion   TxStartEvent;

#ifdef FEATURE_WLAN_INTEGRATED_SOC
   /*                                                 */
   struct completion   RxStartEvent;
#endif

   struct task_struct* McThread;

   /*                  */
   
   struct task_struct*   TxThread;

#ifdef FEATURE_WLAN_INTEGRATED_SOC
   /*                  */
   struct task_struct*   RxThread;
#endif


   /*                                          */
   struct completion   McShutdown; 

   /*                                          */
   struct completion   TxShutdown; 

#ifdef FEATURE_WLAN_INTEGRATED_SOC
   /*                                          */
   struct completion   RxShutdown;
#endif

   /*                          */
   wait_queue_head_t mcWaitQueue;

   unsigned long     mcEventFlag;

   /*                          */
   wait_queue_head_t txWaitQueue;

   unsigned long     txEventFlag;

#ifdef FEATURE_WLAN_INTEGRATED_SOC
   /*                          */
   wait_queue_head_t rxWaitQueue;

   unsigned long     rxEventFlag;
#endif
   
   /*                                       */
   struct completion ResumeMcEvent;

   /*                                       */
   struct completion ResumeTxEvent;

#ifdef FEATURE_WLAN_INTEGRATED_SOC
   /*                                       */
   struct completion ResumeRxEvent;
#endif

   /*                                                                                 */
   spinlock_t McThreadLock;
   spinlock_t TxThreadLock;
   spinlock_t RxThreadLock;

} VosSchedContext, *pVosSchedContext;

/*
                        
                                               
                                 
                           
      
*/
typedef struct _VosWatchdogContext
{

   /*                                  */ 
   v_PVOID_t pVContext; 

   /*                                                       */
   struct completion WdStartEvent;

   /*                        */
  
   struct task_struct* WdThread;

   /*                                                */
   struct completion WdShutdown; 

   /*                                */
   wait_queue_head_t wdWaitQueue;

   /*                                           */
   unsigned long wdEventFlag;

   v_BOOL_t resetInProgress;

   vos_chip_reset_reason_type reason;

   /*                                                                   */
   spinlock_t wdLock;

} VosWatchdogContext, *pVosWatchdogContext;

/*
                         
                                                                         
                    
*/
typedef struct _VosMsgWrapper
{
   /*              */
   struct list_head  msgNode;

   /*                                     */
   vos_msg_t    *pVosMsg;

} VosMsgWrapper, *pVosMsgWrapper;



typedef struct _VosContextType
{                                                  
   /*                  */
   vos_msg_t           aMsgBuffers[VOS_CORE_MAX_MESSAGES];

   VosMsgWrapper       aMsgWrappers[VOS_CORE_MAX_MESSAGES];
   
   /*                   */
   VosMqType           freeVosMq;

   /*                   */
   VosSchedContext     vosSched;

   /*                  */
   VosWatchdogContext  vosWatchdog;

   /*                     */
   v_VOID_t           *pHDDContext;

#ifdef WLAN_SOFTAP_FEATURE
   /*                            */
   v_VOID_t           *pHDDSoftAPContext;
#endif

   /*                    */
   v_VOID_t           *pTLContext;

   /*                     */
   v_VOID_t           *pMACContext;

#ifndef FEATURE_WLAN_INTEGRATED_SOC   /*               */

   v_VOID_t           *pBALContext;
   
   /*             */
   v_VOID_t           *pSALContext;

   /*             */
   v_VOID_t           *pSSCContext;
#endif
   /*             */
   v_VOID_t           *pBAPContext;

#ifdef WLAN_SOFTAP_FEATURE   
   /*             */
   v_VOID_t           *pSAPContext;
#endif
   
   /*                    */
   vos_pkt_context_t   vosPacket; 

   vos_event_t         ProbeEvent;

   volatile v_U8_t     isLogpInProgress;

#ifdef FEATURE_WLAN_INTEGRATED_SOC
   vos_event_t         wdaCompleteEvent;

   /*             */
   v_VOID_t            *pWDAContext;
#endif

   volatile v_U8_t    isLoadUnloadInProgress;

} VosContextType, *pVosContextType;



/*                                                                            
                                        
                                                                           */
 
int vos_sched_is_tx_thread(int threadID);
#ifdef FEATURE_WLAN_INTEGRATED_SOC
int vos_sched_is_rx_thread(int threadID);
#endif
/*                                                                           
  
                                                           
    
                                                                 
                                 
  
                                             
     
                                                                     
                         
     
                                                                          
      
  
                                                          
  
                                                                         
                                                    
   
  
                                                                          
                              
  
                                                                        
                                                    

                                                                        
                       
          
                                                                             
                   
          
                                                                        
          
                      
  
                                                                           */
VOS_STATUS vos_sched_open( v_PVOID_t pVosContext, 
                           pVosSchedContext pSchedCxt,
                           v_SIZE_t SchedCtxSize);

/*                                                                           
  
                                                             
    
                                                                                     
                                                                                                  
     
   
                                                          
  
                                                                   
                                                   

                                                                         
                              
  
                                                                        
                                                   

                                                                        
                      
          
                                                                            
                   
          
                                                                       

                         
  
                                                                           */

VOS_STATUS vos_watchdog_open

(
  v_PVOID_t           pVosContext,
  pVosWatchdogContext pWdContext,
  v_SIZE_t            wdCtxSize
);

/*                                                                           
  
                                                       
    
                                                              
                          
  
                                         
     
                                           
     
                              
      
  
                                                          
  
                                                                          
                              
          
                                                                             
                   
          
                                                                        
          
                       
  
                                                                           */
VOS_STATUS vos_sched_close( v_PVOID_t pVosContext);

/*                                                                           
  
                                                         
    
                                                               
                          
  
                                    
     
      
                                                          
  
                                                                         
                              
          
                                                        
          
                                                                       
          
                          
  
                                                                           */
VOS_STATUS vos_watchdog_close ( v_PVOID_t pVosContext );

/*                                             */
VOS_STATUS vos_mq_init(pVosMqType pMq);
void vos_mq_deinit(pVosMqType pMq);
void vos_mq_put(pVosMqType pMq, pVosMsgWrapper pMsgWrapper);
pVosMsgWrapper vos_mq_get(pVosMqType pMq);
v_BOOL_t vos_is_mq_empty(pVosMqType pMq);
pVosSchedContext get_vos_sched_ctxt(void);
pVosWatchdogContext get_vos_watchdog_ctxt(void);
VOS_STATUS vos_sched_init_mqs   (pVosSchedContext pSchedContext);
void vos_sched_deinit_mqs (pVosSchedContext pSchedContext);
void vos_sched_flush_mc_mqs  (pVosSchedContext pSchedContext);
void vos_sched_flush_tx_mqs  (pVosSchedContext pSchedContext);
#ifdef FEATURE_WLAN_INTEGRATED_SOC
void vos_sched_flush_rx_mqs  (pVosSchedContext pSchedContext);
#endif
VOS_STATUS vos_watchdog_chip_reset ( vos_chip_reset_reason_type reason );
void clearWlanResetReason(void);

void vos_timer_module_init( void );
VOS_STATUS vos_watchdog_wlan_shutdown(void);
VOS_STATUS vos_watchdog_wlan_re_init(void);

#endif //                            
