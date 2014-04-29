/*
 * Copyright 2010 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *     Alex Deucher <alexander.deucher@amd.com>
 */

#include <linux/bug.h>
#include <linux/types.h>
#include <linux/kernel.h>

/*
                                                                        
                                                                       
                                                                      
                                                                     
                                                                     
                                                                
                       
 */

const u32 cayman_default_state[] =
{
	0xc0066900,
	0x00000000,
	0x00000060, /*                   */
	0x00000000, /*                  */
	0x00000000, /*               */
	0x0000002a, /*                    */
	0x00000000, /*                     */
	0x00000000, /*                    */

	0xc0026900,
	0x0000000a,
	0x00000000, /*                  */
	0x00000000, /*                */

	0xc0036900,
	0x0000000f,
	0x00000000, /*               */
	0x00000000, /*           */
	0x00000000, /*                 */

	0xc0016900,
	0x00000080,
	0x00000000, /*                     */

	0xc00d6900,
	0x00000083,
	0x0000ffff, /*                     */
	0x00000000, /*                     */
	0x20002000, /*                     */
	0x00000000,
	0x20002000,
	0x00000000,
	0x20002000,
	0x00000000,
	0x20002000,
	0xaaaaaaaa, /*                */
	0x00000000, /*                              */
	0x0000000f, /*                */
	0x0000000f, /*                */

	0xc0226900,
	0x00000094,
	0x80000000, /*                          */
	0x20002000, /*                          */
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x80000000,
	0x20002000,
	0x00000000, /*                    */
	0x3f800000, /*                    */

	0xc0016900,
	0x000000d4,
	0x00000000, /*         */

	0xc0026900,
	0x000000d9,
	0x00000000, /*           */
	0x00000000, /*         */

	0xc0096900,
	0x00000100,
	0x00ffffff, /*                  */
	0x00000000, /*                  */
	0x00000000, /*                 */
	0x00000000, /*                              */
	0x00000000, /*                       */
	0x00000000, /*              */
	0x00000000, /*                */
	0x00000000, /*               */
	0x00000000, /*                */

	0xc0016900,
	0x00000187,
	0x00000100, /*                 */

	0xc0026900,
	0x00000191,
	0x00000100, /*                     */
	0x00000101, /*                     */

	0xc0016900,
	0x000001b1,
	0x00000000, /*                   */

	0xc0106900,
	0x000001b3,
	0x20000001, /*                     */
	0x00000000, /*                     */
	0x00000000, /*                      */
	0x00000000, /*             */
	0x00000000, /*              */
	0x00100000, /*                */
	0x00000000, /*                     */
	0x00000000, /*                        */
	0x00000000, /*                          */
	0x00000000, /*                          */
	0x00000000, /*                          */
	0x00000000, /*              */
	0x00000000, /*              */
	0x00000000, /*                */
	0x00000000, /*                 */
	0x00000000, /*                 */

	0xc0016900,
	0x000001e0,
	0x00000000, /*                   */

	0xc00e6900,
	0x00000200,
	0x00000000, /*                  */
	0x00000000, /*         */
	0x00cc0010, /*                  */
	0x00000210, /*                   */
	0x00010000, /*                 */
	0x00000004, /*                    */
	0x00000100, /*                */
	0x00000000, /*                   */
	0x00000000, /*                   */
	0x00000000, /*                         */
	0x00000000, /*                          */
	0x00000000, /*                        */
	0x00000000, /*  */
	0x00000000, /*  */

	0xc0026900,
	0x00000229,
	0x00000000, /*                 */
	0x00000000,

	0xc0016900,
	0x0000023b,
	0x00000000, /*                 */

	0xc0066900,
	0x00000240,
	0x00000000, /*                       */
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,

	0xc0046900,
	0x00000247,
	0x00000000, /*                     */
	0x00000000,
	0x00000000,
	0x00000000,

	0xc0116900,
	0x00000280,
	0x00000000, /*                  */
	0x00000000, /*                    */
	0x00000008, /*                 */
	0x00000000, /*                    */
	0x00000000, /*                      */
	0x00000000, /*              */
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000, /*             */

	0xc0026900,
	0x00000292,
	0x00000000, /*                   */
	0x00000000, /*                   */

	0xc0016900,
	0x000002a1,
	0x00000000, /*                    */

	0xc0016900,
	0x000002a5,
	0x00000000, /*                            */

	0xc0026900,
	0x000002a8,
	0x00000000, /*                          */
	0x00000000,

	0xc0026900,
	0x000002ad,
	0x00000000, /*               */
	0x00000000,

	0xc0016900,
	0x000002d5,
	0x00000000, /*                      */

	0xc0016900,
	0x000002dc,
	0x0000aa00, /*                  */

	0xc0066900,
	0x000002de,
	0x00000000, /*                               */
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,

	0xc0026900,
	0x000002e5,
	0x00000000, /*                    */
	0x00000000,

	0xc01b6900,
	0x000002f5,
	0x76543210, /*                           */
	0xfedcba98, /*                           */
	0x00000000, /*                 */
	0x00000000, /*                 */
	0x00000005, /*                */
	0x3f800000, /*                        */
	0x3f800000, /*                        */
	0x3f800000, /*                        */
	0x3f800000, /*                        */
	0x00000000, /*                                   */
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0xffffffff, /*                         */
	0xffffffff,

	0xc0026900,
	0x00000316,
	0x0000000e, /*                             */
	0x00000010, /*  */
};

const u32 cayman_vs[] =
{
	0x00000004,
	0x80400400,
	0x0000a03c,
	0x95000688,
	0x00004000,
	0x15000688,
	0x00000000,
	0x88000000,
	0x04000000,
	0x67961001,
#ifdef __BIG_ENDIAN
	0x00020000,
#else
	0x00000000,
#endif
	0x00000000,
	0x04000000,
	0x67961000,
#ifdef __BIG_ENDIAN
	0x00020008,
#else
	0x00000008,
#endif
	0x00000000,
};

const u32 cayman_ps[] =
{
	0x00000004,
	0xa00c0000,
	0x00000008,
	0x80400000,
	0x00000000,
	0x95000688,
	0x00000000,
	0x88000000,
	0x00380400,
	0x00146b10,
	0x00380000,
	0x20146b10,
	0x00380400,
	0x40146b00,
	0x80380000,
	0x60146b00,
	0x00000010,
	0x000d1000,
	0xb0800000,
	0x00000000,
};

const u32 cayman_ps_size = ARRAY_SIZE(cayman_ps);
const u32 cayman_vs_size = ARRAY_SIZE(cayman_vs);
const u32 cayman_default_size = ARRAY_SIZE(cayman_default_state);
