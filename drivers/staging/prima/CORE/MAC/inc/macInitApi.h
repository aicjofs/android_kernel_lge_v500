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
#ifndef __MAC_INIT_API_H
#define __MAC_INIT_API_H

#include "aniGlobal.h"

tSirRetStatus macStart(tHalHandle hHal, void* pHalMacStartParams);
tSirRetStatus macStop(tHalHandle hHal, tHalStopType stopType);
tSirRetStatus macOpen(tHalHandle * pHalHandle, tHddHandle hHdd, tMacOpenParameters * pMacOpenParms);
tSirRetStatus macClose(tHalHandle hHal);

#ifdef FEATURE_WLAN_INTEGRATED_SOC 
tSirRetStatus macPreStart(tHalHandle hHal);
#endif

#endif //                

