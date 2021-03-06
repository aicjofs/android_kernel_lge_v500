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

#if !defined( __WLAN_QCT_OS_TRACE_H )
#define __WLAN_QCT_OS_TRACE_H


#ifdef WLAN_DEBUG

/*                                                                             
  
                                                        
   
                                                                   
                                                                       
                    
  
                                                                  
                                                                                  
         
                                                              
                                                                                
                                                                              
                                    
         
                                                                            
                                                                                      
                                                                                       
  
                   
    
                                                                            */
void wpalTrace( wpt_moduleid module, wpt_tracelevel level, char *strFormat, ... );

/*                                                                             
  
                                                      
   
                                                                    
                                                                    
                    
  
                                                                  
                                                                           
         
                                                              
                                                                                
                                                                       
                                    
         
                                                               

                                                               
  
                   
    
                                                                            */
void wpalDump( wpt_moduleid module, wpt_tracelevel level,
               wpt_uint8 *memory, wpt_uint32 length);

#define WPAL_TRACE wpalTrace
#define WPAL_DUMP wpalDump

#define WPAL_ASSERT( _condition )                          \
if ( ! ( _condition ) )                                   \
{                                                         \
   printk(KERN_CRIT "VOS ASSERT in %s Line %d\n", __FUNCTION__, __LINE__); \
   WARN_ON(1); \
}

#else //          

#define WPAL_TRACE
#define WPAL_DUMP
#define WPAL_ASSERT

#endif //          

#endif //                      
