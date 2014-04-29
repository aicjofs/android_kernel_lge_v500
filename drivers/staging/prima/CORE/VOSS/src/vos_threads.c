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

/**=========================================================================
  
  \file  vos_threads.c
  
  \brief virtual Operating System Services (vOSS) Threading APIs
  
   Copyright 2008 (c) Qualcomm, Incorporated.  All Rights Reserved.
   
   Qualcomm Confidential and Proprietary.
  
  ========================================================================*/

/*          */

/*                                                                          
               
                                                                          */
#include <vos_threads.h>
#include <vos_trace.h>
#include <linux/jiffies.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/interrupt.h>

/*                                                                           
                                        
                                                                          */


/*                                                                           
                   
                                                                          */


/*                                                                          
                                        
                                                                          */

/*                                                                            
  
                            

                                                                          
                                                
     
                                                                               
                                                                
  
                  
    
     
  
                                                                            */
v_VOID_t vos_sleep( v_U32_t msInterval )
{
   if (in_interrupt())
   {
      VOS_TRACE(VOS_MODULE_ID_VOSS, VOS_TRACE_LEVEL_ERROR, "%s cannot be called from interrupt context!!!", __FUNCTION__);
      return;
   }
   msleep_interruptible(msInterval);
}

/*                                                                            
  
                               

                                                                             
                                                
     
                                                                               
                                                                
  
                  
    
     
  
                                                                            */
v_VOID_t vos_sleep_us( v_U32_t usInterval )
{
   unsigned long timeout = usecs_to_jiffies(usInterval) + 1;
   if (in_interrupt())
   {
      VOS_TRACE(VOS_MODULE_ID_VOSS, VOS_TRACE_LEVEL_ERROR, "%s cannot be called from interrupt context!!!", __FUNCTION__);
      return;
   }
   while (timeout && !signal_pending(current))
       timeout = schedule_timeout_interruptible(timeout);
}


/*                                                                            
  
                                    

                                                                        
                                                                           
                                              
     
                                                               
  
                  
    
     
  
                                                                            */
v_VOID_t vos_busy_wait( v_U32_t usInterval )
{
    udelay(usInterval);
}
