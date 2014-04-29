/* SPU ELF support for BFD.

   Copyright 2006 Free Software Foundation, Inc.

   This file is part of BFD, the Binary File Descriptor library.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.  */

/*                 

                    
                                                                                            
                                                                                              
                                                                                            
                                                                                            
                                                                                           
                                                                                           

                                                                                            
                                                                                            
                                                                                            
                                                                                           
                                                                                           

                                                                                            
                                                                                            
                                                                                            
                                                                                           
                                                                                           

                                                                                            
                                                                                            
                                                                                            
                                                                                           
                                                                                           

                                                    
                                                    
                                                    
                                                   
                                                   

                    

                                                                                                                                  
                                                                                                                                
                                                                                                        

                        

                                                             
                                                                              
                                                  

                                                              
                                                                            
                                                   
                                                   

                                                           
                                                                  
                          
                            

                                                                 
                                                                             
                                                                             
                                                                     
                                                                       
                         
                         
                            
                    
                         
                         

                                                                     
                                                                     
                  

                        

                                                                                                                             
                                                                                              
                                                                                        
                                                                                                
                                                                                                
                                                                                                              
                                                                                                                          
                                     

                  

                                                                 

                          
                         
                                                        
                         
                 
                          
                  
                

                          
                   
                 
                       
                      
                    

*/

#define _A0() {0}
#define _A1(a) {1,a}
#define _A2(a,b) {2,a,b}
#define _A3(a,b,c) {3,a,b,c}
#define _A4(a,b,c,d) {4,a,b,c,d}

/*                                                                      */
/*                               */
/*                              */

APUOP(M_BR,		RI16,	0x190,	"br",		_A1(A_R18),	00000,	BR)	/*                          */
APUOP(M_BRSL,		RI16,	0x198,	"brsl",		_A2(A_T,A_R18),	00002,	BR)	/*                                */
APUOP(M_BRA,		RI16,	0x180,	"bra",		_A1(A_S18),	00000,	BR)	/*                       */
APUOP(M_BRASL,		RI16,	0x188,	"brasl",	_A2(A_T,A_S18),	00002,	BR)	/*                             */
APUOP(M_FSMBI,		RI16,	0x194,	"fsmbi",	_A2(A_T,A_X16),	00002,	SHUF)	/*                            */
APUOP(M_LQA,		RI16,	0x184,	"lqa",		_A2(A_T,A_S18),	00002,	LS)	/*                          */
APUOP(M_LQR,		RI16,	0x19C,	"lqr",		_A2(A_T,A_R18),	00002,	LS)	/*                             */
APUOP(M_STOP,		RR,	0x000,	"stop",		_A0(),		00000,	BR)	/*                    */
APUOP(M_STOP2,		RR,	0x000,	"stop",		_A1(A_U14),	00000,	BR)	/*                    */
APUOP(M_STOPD,		RR,	0x140,	"stopd",	_A3(A_T,A_A,A_B),         00111,	BR)	/*                                                 */
APUOP(M_LNOP,		RR,	0x001,	"lnop",		_A0(),		00000,	LNOP)	/*                            */
APUOP(M_SYNC,		RR,	0x002,	"sync",		_A0(),		00000,	BR)	/*                          */
APUOP(M_DSYNC,		RR,	0x003,	"dsync",	_A0(),		00000,	BR)	/*                                 */
APUOP(M_MFSPR,		RR,	0x00c,	"mfspr",	_A2(A_T,A_S),	00002,	SPR)	/*                      */
APUOP(M_RDCH,		RR,	0x00d,	"rdch",		_A2(A_T,A_H),	00002,	SPR)	/*                           */
APUOP(M_RCHCNT,		RR,	0x00f,	"rchcnt",	_A2(A_T,A_H),	00002,	SPR)	/*                            */
APUOP(M_HBRA,		LBT,	0x080,	"hbra",		_A2(A_S11,A_S18),	00000,	LS)	/*                               */
APUOP(M_HBRR,		LBT,	0x090,	"hbrr",		_A2(A_S11,A_R18),	00000,	LS)	/*                                  */
APUOP(M_BRZ,		RI16,	0x100,	"brz",		_A2(A_T,A_R18),	00001,	BR)	/*                                 */
APUOP(M_BRNZ,		RI16,	0x108,	"brnz",		_A2(A_T,A_R18),	00001,	BR)	/*                                 */
APUOP(M_BRHZ,		RI16,	0x110,	"brhz",		_A2(A_T,A_R18),	00001,	BR)	/*                                 */
APUOP(M_BRHNZ,		RI16,	0x118,	"brhnz",	_A2(A_T,A_R18),	00001,	BR)	/*                                 */
APUOP(M_STQA,		RI16,	0x104,	"stqa",		_A2(A_T,A_S18),	00001,	LS)	/*                          */
APUOP(M_STQR,		RI16,	0x11C,	"stqr",		_A2(A_T,A_R18),	00001,	LS)	/*                             */
APUOP(M_MTSPR,		RR,	0x10c,	"mtspr",	_A2(A_S,A_T),	00001,	SPR)	/*                      */
APUOP(M_WRCH,		RR,	0x10d,	"wrch",		_A2(A_H,A_T),	00001,	SPR)	/*                      */
APUOP(M_LQD,		RI10,	0x1a0,	"lqd",		_A4(A_T,A_S14,A_P,A_A),	00012,	LS)	/*                             */
APUOP(M_BI,		RR,	0x1a8,	"bi",		_A1(A_A),		00010,	BR)	/*                      */
APUOP(M_BISL,		RR,	0x1a9,	"bisl",		_A2(A_T,A_A),	00012,	BR)	/*                            */
APUOP(M_IRET,  		RR,	0x1aa,	"iret",	        _A1(A_A), 	00010,	BR)	/*                        */
APUOP(M_IRET2, 		RR,	0x1aa,	"iret",	        _A0(),	 	00010,	BR)	/*                        */
APUOP(M_BISLED,		RR,	0x1ab,	"bisled",	_A2(A_T,A_A),	00012,	BR)	/*                                    */
APUOP(M_HBR,		LBTI,	0x1ac,	"hbr",		_A2(A_S11I,A_A),	00010,	LS)	/*                              */
APUOP(M_FREST,		RR,	0x1b8,	"frest",	_A2(A_T,A_A),	00012,	SHUF)	/*                             */
APUOP(M_FRSQEST,	RR,	0x1b9,	"frsqest",	_A2(A_T,A_A),	00012,	SHUF)	/*                             */
APUOP(M_FSM,		RR,	0x1b4,	"fsm",		_A2(A_T,A_A),	00012,	SHUF)	/*                              */
APUOP(M_FSMH,		RR,	0x1b5,	"fsmh",		_A2(A_T,A_A),	00012,	SHUF)	/*                              */
APUOP(M_FSMB,		RR,	0x1b6,	"fsmb",		_A2(A_T,A_A),	00012,	SHUF)	/*                              */
APUOP(M_GB,		RR,	0x1b0,	"gb",		_A2(A_T,A_A),	00012,	SHUF)	/*                              */
APUOP(M_GBH,		RR,	0x1b1,	"gbh",		_A2(A_T,A_A),	00012,	SHUF)	/*                              */
APUOP(M_GBB,		RR,	0x1b2,	"gbb",		_A2(A_T,A_A),	00012,	SHUF)	/*                              */
APUOP(M_CBD,		RI7,	0x1f4,	"cbd",		_A4(A_T,A_U7,A_P,A_A),	00012,	SHUF)	/*                                  */
APUOP(M_CHD,		RI7,	0x1f5,	"chd",		_A4(A_T,A_U7,A_P,A_A),	00012,	SHUF)	/*                                  */
APUOP(M_CWD,		RI7,	0x1f6,	"cwd",		_A4(A_T,A_U7,A_P,A_A),	00012,	SHUF)	/*                                  */
APUOP(M_CDD,		RI7,	0x1f7,	"cdd",		_A4(A_T,A_U7,A_P,A_A),	00012,	SHUF)	/*                                  */
APUOP(M_ROTQBII,	RI7,	0x1f8,	"rotqbii",	_A3(A_T,A_A,A_U3),	00012,	SHUF)	/*                           */
APUOP(M_ROTQBYI,	RI7,	0x1fc,	"rotqbyi",	_A3(A_T,A_A,A_S7N),	00012,	SHUF)	/*                               */
APUOP(M_ROTQMBII,	RI7,	0x1f9,	"rotqmbii",	_A3(A_T,A_A,A_S3),	00012,	SHUF)	/*                          */
APUOP(M_ROTQMBYI,	RI7,	0x1fd,	"rotqmbyi",	_A3(A_T,A_A,A_S6),	00012,	SHUF)	/*                          */
APUOP(M_SHLQBII,	RI7,	0x1fb,	"shlqbii",	_A3(A_T,A_A,A_U3),	00012,	SHUF)	/*                          */
APUOP(M_SHLQBYI,	RI7,	0x1ff,	"shlqbyi",	_A3(A_T,A_A,A_U5),	00012,	SHUF)	/*                          */
APUOP(M_STQD,		RI10,	0x120,	"stqd",		_A4(A_T,A_S14,A_P,A_A),	00011,	LS)	/*                             */
APUOP(M_BIHNZ,		RR,	0x12b,	"bihnz",	_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOP(M_BIHZ,		RR,	0x12a,	"bihz",		_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOP(M_BINZ,		RR,	0x129,	"binz",		_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOP(M_BIZ,		RR,	0x128,	"biz",		_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOP(M_CBX,		RR,	0x1d4,	"cbx",		_A3(A_T,A_A,A_B),		00112,	SHUF)	/*                                  */
APUOP(M_CHX,		RR,	0x1d5,	"chx",		_A3(A_T,A_A,A_B),		00112,	SHUF)	/*                                  */
APUOP(M_CWX,		RR,	0x1d6,	"cwx",		_A3(A_T,A_A,A_B),		00112,	SHUF)	/*                                  */
APUOP(M_CDX,		RR,	0x1d7,	"cdx",		_A3(A_T,A_A,A_B),		00112,	SHUF)	/*                                  */
APUOP(M_LQX,		RR,	0x1c4,	"lqx",		_A3(A_T,A_A,A_B),		00112,	LS)	/*                            */
APUOP(M_ROTQBI,		RR,	0x1d8,	"rotqbi",	_A3(A_T,A_A,A_B),		00112,	SHUF)	/*                           */
APUOP(M_ROTQMBI,	RR,	0x1d9,	"rotqmbi",	_A3(A_T,A_A,A_B),		00112,	SHUF)	/*                          */
APUOP(M_SHLQBI,		RR,	0x1db,	"shlqbi",	_A3(A_T,A_A,A_B),		00112,	SHUF)	/*                          */
APUOP(M_ROTQBY,		RR,	0x1dc,	"rotqby",	_A3(A_T,A_A,A_B),		00112,		SHUF)	/*                               */
APUOP(M_ROTQMBY,	RR,	0x1dd,	"rotqmby",	_A3(A_T,A_A,A_B),		00112,		SHUF)	/*                          */
APUOP(M_SHLQBY,		RR,	0x1df,	"shlqby",	_A3(A_T,A_A,A_B),		00112,	SHUF)	/*                          */
APUOP(M_ROTQBYBI,	RR,	0x1cc,	"rotqbybi",	_A3(A_T,A_A,A_B),		00112,		SHUF)	/*                          */
APUOP(M_ROTQMBYBI,	RR,	0x1cd,	"rotqmbybi",	_A3(A_T,A_A,A_B),		00112,		SHUF)	/*                          */
APUOP(M_SHLQBYBI,	RR,	0x1cf,	"shlqbybi",	_A3(A_T,A_A,A_B),		00112,	SHUF)	/*                          */
APUOP(M_STQX,		RR,	0x144,	"stqx",		_A3(A_T,A_A,A_B),		00111,	LS)	/*                            */
APUOP(M_SHUFB,		RRR,	0x580,	"shufb",	_A4(A_C,A_A,A_B,A_T),	02111,	SHUF)	/*                               */
APUOP(M_IL,		RI16,	0x204,	"il",		_A2(A_T,A_S16),	00002,	FX2)	/*                            */
APUOP(M_ILH,		RI16,	0x20c,	"ilh",		_A2(A_T,A_X16),	00002,	FX2)	/*                       */
APUOP(M_ILHU,		RI16,	0x208,	"ilhu",		_A2(A_T,A_X16),	00002,	FX2)	/*                           */
APUOP(M_ILA,		RI18,	0x210,	"ila",		_A2(A_T,A_U18),	00002,	FX2)	/*                            */
APUOP(M_NOP,		RR,	0x201,	"nop",		_A1(A_T),		00000,	NOP)	/*                            */
APUOP(M_NOP2,		RR,	0x201,	"nop",		_A0(),		00000,	NOP)	/*                            */
APUOP(M_IOHL,		RI16,	0x304,	"iohl",		_A2(A_T,A_X16),	00003,	FX2)	/*                               */
APUOP(M_ANDBI,		RI10,	0x0b0,	"andbi",	_A3(A_T,A_A,A_S10B),	00012,	FX2)	/*                          */
APUOP(M_ANDHI,		RI10,	0x0a8,	"andhi",	_A3(A_T,A_A,A_S10),	00012,	FX2)	/*                          */
APUOP(M_ANDI,		RI10,	0x0a0,	"andi",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/*                          */
APUOP(M_ORBI,		RI10,	0x030,	"orbi",		_A3(A_T,A_A,A_S10B),	00012,	FX2)	/*                          */
APUOP(M_ORHI,		RI10,	0x028,	"orhi",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/*                          */
APUOP(M_ORI,		RI10,	0x020,	"ori",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/*                          */
APUOP(M_ORX,		RR,	0x1f0,	"orx",		_A2(A_T,A_A),		00012,	BR)	/*                                           */
APUOP(M_XORBI,		RI10,	0x230,	"xorbi",	_A3(A_T,A_A,A_S10B),	00012,	FX2)	/*                          */
APUOP(M_XORHI,		RI10,	0x228,	"xorhi",	_A3(A_T,A_A,A_S10),	00012,	FX2)	/*                          */
APUOP(M_XORI,		RI10,	0x220,	"xori",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/*                          */
APUOP(M_AHI,		RI10,	0x0e8,	"ahi",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/*                          */
APUOP(M_AI,		RI10,	0x0e0,	"ai",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/*                          */
APUOP(M_SFHI,		RI10,	0x068,	"sfhi",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/*                          */
APUOP(M_SFI,		RI10,	0x060,	"sfi",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/*                          */
APUOP(M_CGTBI,		RI10,	0x270,	"cgtbi",	_A3(A_T,A_A,A_S10B),	00012,	FX2)	/*                            */
APUOP(M_CGTHI,		RI10,	0x268,	"cgthi",	_A3(A_T,A_A,A_S10),	00012,	FX2)	/*                            */
APUOP(M_CGTI,		RI10,	0x260,	"cgti",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/*                            */
APUOP(M_CLGTBI,		RI10,	0x2f0,	"clgtbi",	_A3(A_T,A_A,A_S10B),	00012,	FX2)	/*                            */
APUOP(M_CLGTHI,		RI10,	0x2e8,	"clgthi",	_A3(A_T,A_A,A_S10),	00012,	FX2)	/*                            */
APUOP(M_CLGTI,		RI10,	0x2e0,	"clgti",	_A3(A_T,A_A,A_S10),	00012,	FX2)	/*                            */
APUOP(M_CEQBI,		RI10,	0x3f0,	"ceqbi",	_A3(A_T,A_A,A_S10B),	00012,	FX2)	/*                            */
APUOP(M_CEQHI,		RI10,	0x3e8,	"ceqhi",	_A3(A_T,A_A,A_S10),	00012,	FX2)	/*                            */
APUOP(M_CEQI,		RI10,	0x3e0,	"ceqi",		_A3(A_T,A_A,A_S10),	00012,	FX2)	/*                            */
APUOP(M_HGTI,		RI10,	0x278,	"hgti",		_A3(A_T,A_A,A_S10),	00010,	FX2)	/*                               */
APUOP(M_HGTI2,		RI10,	0x278,	"hgti",		_A2(A_A,A_S10),	00010,	FX2)	/*                               */
APUOP(M_HLGTI,		RI10,	0x2f8,	"hlgti",	_A3(A_T,A_A,A_S10),	00010,	FX2)	/*                               */
APUOP(M_HLGTI2,		RI10,	0x2f8,	"hlgti",	_A2(A_A,A_S10),	00010,	FX2)	/*                               */
APUOP(M_HEQI,		RI10,	0x3f8,	"heqi",		_A3(A_T,A_A,A_S10),	00010,	FX2)	/*                               */
APUOP(M_HEQI2,		RI10,	0x3f8,	"heqi",		_A2(A_A,A_S10),	00010,	FX2)	/*                               */
APUOP(M_MPYI,		RI10,	0x3a0,	"mpyi",		_A3(A_T,A_A,A_S10),	00012,	FP7)	/*                          */
APUOP(M_MPYUI,		RI10,	0x3a8,	"mpyui",	_A3(A_T,A_A,A_S10),	00012,	FP7)	/*                          */
APUOP(M_CFLTS,		RI8,	0x3b0,	"cflts",	_A3(A_T,A_A,A_U7A),	00012,	FP7)	/*                              */
APUOP(M_CFLTU,		RI8,	0x3b2,	"cfltu",	_A3(A_T,A_A,A_U7A),	00012,	FP7)	/*                              */
APUOP(M_CSFLT,		RI8,	0x3b4,	"csflt",	_A3(A_T,A_A,A_U7B),	00012,	FP7)	/*                              */
APUOP(M_CUFLT,		RI8,	0x3b6,	"cuflt",	_A3(A_T,A_A,A_U7B),	00012,	FP7)	/*                              */
APUOP(M_FESD,		RR,	0x3b8,	"fesd",		_A2(A_T,A_A),	00012,	FPD)	/*                              */
APUOP(M_FRDS,		RR,	0x3b9,	"frds",		_A2(A_T,A_A),	00012,	FPD)	/*                              */
APUOP(M_FSCRRD,		RR,	0x398,	"fscrrd",	_A1(A_T),		00002,	FPD)	/*                             */
APUOP(M_FSCRWR,		RR,	0x3ba,	"fscrwr",	_A2(A_T,A_A),	00010,	FP7)	/*                             */
APUOP(M_FSCRWR2,	RR,	0x3ba,	"fscrwr",	_A1(A_A),		00010,	FP7)	/*                             */
APUOP(M_CLZ,		RR,	0x2a5,	"clz",		_A2(A_T,A_A),	00012,	FX2)	/*                           */
APUOP(M_CNTB,		RR,	0x2b4,	"cntb",		_A2(A_T,A_A),	00012,	FXB)	/*                           */
APUOP(M_XSBH,		RR,	0x2b6,	"xsbh",		_A2(A_T,A_A),	00012,	FX2)	/*                                */
APUOP(M_XSHW,		RR,	0x2ae,	"xshw",		_A2(A_T,A_A),	00012,	FX2)	/*                                */
APUOP(M_XSWD,		RR,	0x2a6,	"xswd",		_A2(A_T,A_A),	00012,	FX2)	/*                                */
APUOP(M_ROTI,		RI7,	0x078,	"roti",		_A3(A_T,A_A,A_S7N),	00012,	FX3)	/*                           */
APUOP(M_ROTMI,		RI7,	0x079,	"rotmi",	_A3(A_T,A_A,A_S7),	00012,	FX3)	/*                          */
APUOP(M_ROTMAI,		RI7,	0x07a,	"rotmai",	_A3(A_T,A_A,A_S7),	00012,	FX3)	/*                          */
APUOP(M_SHLI,		RI7,	0x07b,	"shli",		_A3(A_T,A_A,A_U6),	00012,	FX3)	/*                          */
APUOP(M_ROTHI,		RI7,	0x07c,	"rothi",	_A3(A_T,A_A,A_S7N),	00012,	FX3)	/*                           */
APUOP(M_ROTHMI,		RI7,	0x07d,	"rothmi",	_A3(A_T,A_A,A_S6),	00012,	FX3)	/*                          */
APUOP(M_ROTMAHI,	RI7,	0x07e,	"rotmahi",	_A3(A_T,A_A,A_S6),	00012,	FX3)	/*                          */
APUOP(M_SHLHI,		RI7,	0x07f,	"shlhi",	_A3(A_T,A_A,A_U5),	00012,	FX3)	/*                          */
APUOP(M_A,		RR,	0x0c0,	"a",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                         */
APUOP(M_AH,		RR,	0x0c8,	"ah",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                         */
APUOP(M_SF,		RR,	0x040,	"sf",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                         */
APUOP(M_SFH,		RR,	0x048,	"sfh",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                         */
APUOP(M_CGT,		RR,	0x240,	"cgt",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                           */
APUOP(M_CGTB,		RR,	0x250,	"cgtb",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                           */
APUOP(M_CGTH,		RR,	0x248,	"cgth",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                           */
APUOP(M_CLGT,		RR,	0x2c0,	"clgt",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                           */
APUOP(M_CLGTB,		RR,	0x2d0,	"clgtb",	_A3(A_T,A_A,A_B),		00112,	FX2)	/*                           */
APUOP(M_CLGTH,		RR,	0x2c8,	"clgth",	_A3(A_T,A_A,A_B),		00112,	FX2)	/*                           */
APUOP(M_CEQ,		RR,	0x3c0,	"ceq",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                           */
APUOP(M_CEQB,		RR,	0x3d0,	"ceqb",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                           */
APUOP(M_CEQH,		RR,	0x3c8,	"ceqh",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                           */
APUOP(M_HGT,		RR,	0x258,	"hgt",		_A3(A_T,A_A,A_B),		00110,	FX2)	/*                              */
APUOP(M_HGT2,		RR,	0x258,	"hgt",		_A2(A_A,A_B),	00110,	FX2)	/*                              */
APUOP(M_HLGT,		RR,	0x2d8,	"hlgt",		_A3(A_T,A_A,A_B),		00110,	FX2)	/*                              */
APUOP(M_HLGT2,		RR,	0x2d8,	"hlgt",		_A2(A_A,A_B),	00110,	FX2)	/*                              */
APUOP(M_HEQ,		RR,	0x3d8,	"heq",		_A3(A_T,A_A,A_B),		00110,	FX2)	/*                              */
APUOP(M_HEQ2,		RR,	0x3d8,	"heq",		_A2(A_A,A_B),	00110,	FX2)	/*                              */
APUOP(M_FCEQ,		RR,	0x3c2,	"fceq",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                           */
APUOP(M_FCMEQ,		RR,	0x3ca,	"fcmeq",	_A3(A_T,A_A,A_B),		00112,	FX2)	/*                               */
APUOP(M_FCGT,		RR,	0x2c2,	"fcgt",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                           */
APUOP(M_FCMGT,		RR,	0x2ca,	"fcmgt",	_A3(A_T,A_A,A_B),		00112,	FX2)	/*                               */
APUOP(M_AND,		RR,	0x0c1,	"and",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                         */
APUOP(M_NAND,		RR,	0x0c9,	"nand",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                            */
APUOP(M_OR,		RR,	0x041,	"or",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                         */
APUOP(M_NOR,		RR,	0x049,	"nor",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                            */
APUOP(M_XOR,		RR,	0x241,	"xor",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                         */
APUOP(M_EQV,		RR,	0x249,	"eqv",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                            */
APUOP(M_ANDC,		RR,	0x2c1,	"andc",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                          */
APUOP(M_ORC,		RR,	0x2c9,	"orc",		_A3(A_T,A_A,A_B),		00112,	FX2)	/*                          */
APUOP(M_ABSDB,		RR,	0x053,	"absdb",	_A3(A_T,A_A,A_B),		00112,	FXB)	/*                           */
APUOP(M_AVGB,		RR,	0x0d3,	"avgb",		_A3(A_T,A_A,A_B),		00112,	FXB)	/*                               */
APUOP(M_SUMB,		RR,	0x253,	"sumb",		_A3(A_T,A_A,A_B),		00112,	FXB)	/*                            */
APUOP(M_DFA,		RR,	0x2cc,	"dfa",		_A3(A_T,A_A,A_B),		00112,	FPD)	/*                         */
APUOP(M_DFM,		RR,	0x2ce,	"dfm",		_A3(A_T,A_A,A_B),		00112,	FPD)	/*                         */
APUOP(M_DFS,		RR,	0x2cd,	"dfs",		_A3(A_T,A_A,A_B),		00112,	FPD)	/*                         */
APUOP(M_FA,		RR,	0x2c4,	"fa",		_A3(A_T,A_A,A_B),		00112,	FP6)	/*                         */
APUOP(M_FM,		RR,	0x2c6,	"fm",		_A3(A_T,A_A,A_B),		00112,	FP6)	/*                         */
APUOP(M_FS,		RR,	0x2c5,	"fs",		_A3(A_T,A_A,A_B),		00112,	FP6)	/*                         */
APUOP(M_MPY,		RR,	0x3c4,	"mpy",		_A3(A_T,A_A,A_B),		00112,	FP7)	/*                         */
APUOP(M_MPYH,		RR,	0x3c5,	"mpyh",		_A3(A_T,A_A,A_B),		00112,	FP7)	/*                                */
APUOP(M_MPYHH,		RR,	0x3c6,	"mpyhh",	_A3(A_T,A_A,A_B),		00112,	FP7)	/*                           */
APUOP(M_MPYHHU,		RR,	0x3ce,	"mpyhhu",	_A3(A_T,A_A,A_B),		00112,	FP7)	/*                           */
APUOP(M_MPYS,		RR,	0x3c7,	"mpys",		_A3(A_T,A_A,A_B),		00112,	FP7)	/*                               */
APUOP(M_MPYU,		RR,	0x3cc,	"mpyu",		_A3(A_T,A_A,A_B),		00112,	FP7)	/*                         */
APUOP(M_FI,		RR,	0x3d4,	"fi",		_A3(A_T,A_A,A_B),		00112,	FP7)	/*                            */
APUOP(M_ROT,		RR,	0x058,	"rot",		_A3(A_T,A_A,A_B),		00112,	FX3)	/*                           */
APUOP(M_ROTM,		RR,	0x059,	"rotm",		_A3(A_T,A_A,A_B),		00112,	FX3)	/*                          */
APUOP(M_ROTMA,		RR,	0x05a,	"rotma",	_A3(A_T,A_A,A_B),		00112,	FX3)	/*                          */
APUOP(M_SHL,		RR,	0x05b,	"shl",		_A3(A_T,A_A,A_B),		00112,	FX3)	/*                          */
APUOP(M_ROTH,		RR,	0x05c,	"roth",		_A3(A_T,A_A,A_B),		00112,	FX3)	/*                           */
APUOP(M_ROTHM,		RR,	0x05d,	"rothm",	_A3(A_T,A_A,A_B),		00112,	FX3)	/*                          */
APUOP(M_ROTMAH,		RR,	0x05e,	"rotmah",	_A3(A_T,A_A,A_B),		00112,	FX3)	/*                          */
APUOP(M_SHLH,		RR,	0x05f,	"shlh",		_A3(A_T,A_A,A_B),		00112,	FX3)	/*                          */
APUOP(M_MPYHHA,		RR,	0x346,	"mpyhha",	_A3(A_T,A_A,A_B),		00113,	FP7)	/*                              */
APUOP(M_MPYHHAU,	RR,	0x34e,	"mpyhhau",	_A3(A_T,A_A,A_B),		00113,	FP7)	/*                              */
APUOP(M_DFMA,		RR,	0x35c,	"dfma",		_A3(A_T,A_A,A_B),		00113,	FPD)	/*                            */
APUOP(M_DFMS,		RR,	0x35d,	"dfms",		_A3(A_T,A_A,A_B),		00113,	FPD)	/*                            */
APUOP(M_DFNMS,		RR,	0x35e,	"dfnms",	_A3(A_T,A_A,A_B),		00113,	FPD)	/*                            */
APUOP(M_DFNMA,		RR,	0x35f,	"dfnma",	_A3(A_T,A_A,A_B),		00113,	FPD)	/*                               */
APUOP(M_FMA,		RRR,	0x700,	"fma",		_A4(A_C,A_A,A_B,A_T),	02111,	FP6)	/*                            */
APUOP(M_FMS,		RRR,	0x780,	"fms",		_A4(A_C,A_A,A_B,A_T),	02111,	FP6)	/*                            */
APUOP(M_FNMS,		RRR,	0x680,	"fnms",		_A4(A_C,A_A,A_B,A_T),	02111,	FP6)	/*                            */
APUOP(M_MPYA,		RRR,	0x600,	"mpya",		_A4(A_C,A_A,A_B,A_T),	02111,	FP7)	/*                            */
APUOP(M_SELB,		RRR,	0x400,	"selb",		_A4(A_C,A_A,A_B,A_T),	02111,	FX2)	/*                                */
/*                                                      */
APUOP(M_SYSCALL,	RI7,    0x10c,	"syscall",      _A3(A_T,A_A,A_S7N),	00002,	SPR)        /*             */
/*
                   
           
                     
      
                                  
                       
                                         
                                          
                                          
                   
                                

*/


/*                            */
APUOP(M_ADDX,		RR,	0x340,	"addx",		_A3(A_T,A_A,A_B),		00113,		FX2)	/*                            */
APUOP(M_CG,		RR,	0x0c2,	"cg",		_A3(A_T,A_A,A_B),		00112,		FX2)	/*                               */
APUOP(M_CGX,		RR,	0x342,	"cgx",		_A3(A_T,A_A,A_B),		00113,		FX2)	/*                                  */
APUOP(M_SFX,		RR,	0x341,	"sfx",		_A3(A_T,A_A,A_B),		00113,		FX2)	/*                            */
APUOP(M_BG,		RR,	0x042,	"bg",		_A3(A_T,A_A,A_B),		00112,		FX2)	/*                               */
APUOP(M_BGX,		RR,	0x343,	"bgx",		_A3(A_T,A_A,A_B),		00113,		FX2)	/*                                  */

/*

                                                                     
                                               

                        
                         
                        

*/
APUOPFB(M_BID,		RR,	0x1a8,	0x20,	"bid",		_A1(A_A),		00010,	BR)	/*                      */
APUOPFB(M_BIE,		RR,	0x1a8,	0x10,	"bie",		_A1(A_A),		00010,	BR)	/*                      */
APUOPFB(M_BISLD,	RR,	0x1a9,	0x20,	"bisld",	_A2(A_T,A_A),	00012,	BR)	/*                            */
APUOPFB(M_BISLE,	RR,	0x1a9,	0x10,	"bisle",	_A2(A_T,A_A),	00012,	BR)	/*                            */
APUOPFB(M_IRETD,  	RR,	0x1aa,	0x20,	"iretd",	_A1(A_A), 	00010,	BR)	/*                        */
APUOPFB(M_IRETD2,  	RR,	0x1aa,	0x20,	"iretd",	_A0(),	 	00010,	BR)	/*                        */
APUOPFB(M_IRETE,  	RR,	0x1aa,	0x10,	"irete",	_A1(A_A), 	00010,	BR)	/*                        */
APUOPFB(M_IRETE2,  	RR,	0x1aa,	0x10,	"irete",	_A0(),	 	00010,	BR)	/*                        */
APUOPFB(M_BISLEDD,	RR,	0x1ab,	0x20,	"bisledd",	_A2(A_T,A_A),	00012,	BR)	/*                                    */
APUOPFB(M_BISLEDE,	RR,	0x1ab,	0x10,	"bislede",	_A2(A_T,A_A),	00012,	BR)	/*                                    */
APUOPFB(M_BIHNZD,	RR,	0x12b,	0x20,	"bihnzd",	_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOPFB(M_BIHNZE,	RR,	0x12b,	0x10,	"bihnze",	_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOPFB(M_BIHZD,	RR,	0x12a,	0x20,	"bihzd",	_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOPFB(M_BIHZE,	RR,	0x12a,	0x10,	"bihze",	_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOPFB(M_BINZD,	RR,	0x129,	0x20,	"binzd",	_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOPFB(M_BINZE,	RR,	0x129,	0x10,	"binze",	_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOPFB(M_BIZD,		RR,	0x128,	0x20,	"bizd",		_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOPFB(M_BIZE,		RR,	0x128,	0x10,	"bize",		_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOPFB(M_SYNCC,	RR,	0x002,	0x40,	"syncc",	_A0(),		00000,	BR)	/*                           */
APUOPFB(M_HBRP,		LBTI,	0x1ac,	0x40,	"hbrp",		_A0(),	        00010,	LS)	/*                              */

/*                                     */
APUOP(M_LR,		RI10,	0x020,	"lr",		_A2(A_T,A_A),	00012,	FX2)	/*                          */
APUOP(M_BIHT,		RR,	0x12b,	"biht", 	_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOP(M_BIHF,		RR,	0x12a,	"bihf",		_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOP(M_BIT,		RR,	0x129,	"bit",		_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOP(M_BIF,		RR,	0x128,	"bif",		_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOPFB(M_BIHTD,	RR,	0x12b,	0x20,	"bihtd",	_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOPFB(M_BIHTE,	RR,	0x12b,	0x10,	"bihte",	_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOPFB(M_BIHFD,	RR,	0x12a,	0x20,	"bihfd",	_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOPFB(M_BIHFE,	RR,	0x12a,	0x10,	"bihfe",	_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOPFB(M_BITD, 	RR,	0x129,	0x20,	"bitd", 	_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOPFB(M_BITE, 	RR,	0x129,	0x10,	"bite", 	_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOPFB(M_BIFD,		RR,	0x128,	0x20,	"bifd",		_A2(A_T,A_A),	00011,	BR)	/*                             */
APUOPFB(M_BIFE,		RR,	0x128,	0x10,	"bife",		_A2(A_T,A_A),	00011,	BR)	/*                             */

#undef _A0
#undef _A1
#undef _A2
#undef _A3
#undef _A4
