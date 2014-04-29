#include "usb.h"
#include "scsiglue.h"
#include "transport.h"
/*                     */
/*                      */
#include "smcommon.h"
#include "smil.h"

/*                    */
/*                     */
/*                     */
/*                  */
/*                      */

/*                    */
static BYTE ecctable[256] = {
0x00, 0x55, 0x56, 0x03, 0x59, 0x0C, 0x0F, 0x5A, 0x5A, 0x0F, 0x0C, 0x59, 0x03,
0x56, 0x55, 0x00, 0x65, 0x30, 0x33, 0x66, 0x3C, 0x69, 0x6A, 0x3F, 0x3F, 0x6A,
0x69, 0x3C, 0x66, 0x33, 0x30, 0x65, 0x66, 0x33, 0x30, 0x65, 0x3F, 0x6A, 0x69,
0x3C, 0x3C, 0x69, 0x6A, 0x3F, 0x65, 0x30, 0x33, 0x66, 0x03, 0x56, 0x55, 0x00,
0x5A, 0x0F, 0x0C, 0x59, 0x59, 0x0C, 0x0F, 0x5A, 0x00, 0x55, 0x56, 0x03, 0x69,
0x3C, 0x3F, 0x6A, 0x30, 0x65, 0x66, 0x33, 0x33, 0x66, 0x65, 0x30, 0x6A, 0x3F,
0x3C, 0x69, 0x0C, 0x59, 0x5A, 0x0F, 0x55, 0x00, 0x03, 0x56, 0x56, 0x03, 0x00,
0x55, 0x0F, 0x5A, 0x59, 0x0C, 0x0F, 0x5A, 0x59, 0x0C, 0x56, 0x03, 0x00, 0x55,
0x55, 0x00, 0x03, 0x56, 0x0C, 0x59, 0x5A, 0x0F, 0x6A, 0x3F, 0x3C, 0x69, 0x33,
0x66, 0x65, 0x30, 0x30, 0x65, 0x66, 0x33, 0x69, 0x3C, 0x3F, 0x6A, 0x6A, 0x3F,
0x3C, 0x69, 0x33, 0x66, 0x65, 0x30, 0x30, 0x65, 0x66, 0x33, 0x69, 0x3C, 0x3F,
0x6A, 0x0F, 0x5A, 0x59, 0x0C, 0x56, 0x03, 0x00, 0x55, 0x55, 0x00, 0x03, 0x56,
0x0C, 0x59, 0x5A, 0x0F, 0x0C, 0x59, 0x5A, 0x0F, 0x55, 0x00, 0x03, 0x56, 0x56,
0x03, 0x00, 0x55, 0x0F, 0x5A, 0x59, 0x0C, 0x69, 0x3C, 0x3F, 0x6A, 0x30, 0x65,
0x66, 0x33, 0x33, 0x66, 0x65, 0x30, 0x6A, 0x3F, 0x3C, 0x69, 0x03, 0x56, 0x55,
0x00, 0x5A, 0x0F, 0x0C, 0x59, 0x59, 0x0C, 0x0F, 0x5A, 0x00, 0x55, 0x56, 0x03,
0x66, 0x33, 0x30, 0x65, 0x3F, 0x6A, 0x69, 0x3C, 0x3C, 0x69, 0x6A, 0x3F, 0x65,
0x30, 0x33, 0x66, 0x65, 0x30, 0x33, 0x66, 0x3C, 0x69, 0x6A, 0x3F, 0x3F, 0x6A,
0x69, 0x3C, 0x66, 0x33, 0x30, 0x65, 0x00, 0x55, 0x56, 0x03, 0x59, 0x0C, 0x0F,
0x5A, 0x5A, 0x0F, 0x0C, 0x59, 0x03, 0x56, 0x55, 0x00
};

static void   trans_result(BYTE,   BYTE,   BYTE *, BYTE *);

#define BIT7        0x80
#define BIT6        0x40
#define BIT5        0x20
#define BIT4        0x10
#define BIT3        0x08
#define BIT2        0x04
#define BIT1        0x02
#define BIT0        0x01
#define BIT1BIT0    0x03
#define BIT23       0x00800000L
#define MASK_CPS    0x3f
#define CORRECTABLE 0x00555554L

/*
                             
                             
                              
                              
 */
static void trans_result(BYTE reg2, BYTE reg3, BYTE *ecc1, BYTE *ecc2)
{
	BYTE a; /*                       */
	BYTE b; /*                       */
	BYTE i; /*              */

	a = BIT7; b = BIT7; /*               */
	*ecc1 = *ecc2 = 0; /*                 */
	for (i = 0; i < 4; ++i) {
		if ((reg3&a) != 0)
			*ecc1 |= b; /*                      */
		b = b>>1; /*             */
		if ((reg2&a) != 0)
			*ecc1 |= b; /*                      */
		b = b>>1; /*             */
		a = a>>1; /*             */
	}

	b = BIT7; /*               */
	for (i = 0; i < 4; ++i) {
		if ((reg3&a) != 0)
			*ecc2 |= b; /*                   */
		b = b>>1; /*             */
		if ((reg2&a) != 0)
			*ecc2 |= b; /*                   */
		b = b>>1; /*             */
		a = a>>1; /*             */
	}
}

/*                                                     */
/*
                               
                
                              
                              
                                   
 */
void calculate_ecc(BYTE *table, BYTE *data, BYTE *ecc1, BYTE *ecc2, BYTE *ecc3)
{
	DWORD  i;    /*              */
	BYTE a;    /*                   */
	BYTE reg1; /*                       */
	BYTE reg2; /*                   */
	BYTE reg3; /*                   */

	reg1 = reg2 = reg3 = 0;   /*                 */
	for (i = 0; i < 256; ++i) {
		a = table[data[i]]; /*                             */
		reg1 ^= (a&MASK_CPS); /*            */
		if ((a&BIT6) != 0) { /*                           */
			reg3 ^= (BYTE)i; /*                  */
			reg2 ^= ~((BYTE)i); /*                          */
		}
	}

	/*                                         
                                  */
	trans_result(reg2, reg3, ecc1, ecc2);
	*ecc1 = ~(*ecc1); *ecc2 = ~(*ecc2); /*                  */
	*ecc3 = ((~reg1)<<2)|BIT1BIT0; /*                 */
}

/*
                
                       
                             
                             
                                  
 */
BYTE correct_data(BYTE *data, BYTE *eccdata, BYTE ecc1, BYTE ecc2, BYTE ecc3)
{
	DWORD l; /*                    */
	DWORD d; /*                      */
	DWORD i; /*              */
	BYTE d1, d2, d3; /*                      */
	BYTE a; /*                 */
	BYTE add; /*                           */
	BYTE b; /*                 */
	BYTE bit; /*                          */

	d1 = ecc1^eccdata[1]; d2 = ecc2^eccdata[0]; /*              */
	d3 = ecc3^eccdata[2]; /*              */
	d = ((DWORD)d1<<16) /*                      */
	+((DWORD)d2<<8)
	+(DWORD)d3;

	if (d == 0)
		return 0; /*                     */

	if (((d^(d>>1))&CORRECTABLE) == CORRECTABLE) { /*                */
		l = BIT23;
		add = 0; /*                 */
		a = BIT7;

		for (i = 0; i < 8; ++i) { /*                */
			if ((d&l) != 0)
				add |= a; /*                             */
			l >>= 2; a >>= 1; /*             */
		}

		bit = 0; /*                 */
		b = BIT2;
		for (i = 0; i < 3; ++i) { /*                */
			if ((d&l) != 0)
				bit |= b; /*                            */
			l >>= 2; b >>= 1; /*             */
		}

		b = BIT0;
		data[add] ^= (b<<bit); /*                    */
		return 1;
	}

	i = 0; /*             */
	d &= 0x00ffffffL; /*         */

	while (d) { /*                        */
		if (d&BIT0)
			++i; /*                       */
		d >>= 1; /*             */
	}

	if (i == 1) { /*              */
		eccdata[1] = ecc1; eccdata[0] = ecc2; /*                    */
		eccdata[2] = ecc3;
		return 2;
	}
	return 3; /*                     */
}

int _Correct_D_SwECC(BYTE *buf, BYTE *redundant_ecc, BYTE *calculate_ecc)
{
	DWORD err;

	err = correct_data(buf, redundant_ecc, *(calculate_ecc + 1),
			   *(calculate_ecc), *(calculate_ecc + 2));
	if (err == 1)
		memcpy(calculate_ecc, redundant_ecc, 3);

	if (err == 0 || err == 1 || err == 2)
		return 0;

	return -1;
}

void _Calculate_D_SwECC(BYTE *buf, BYTE *ecc)
{
	calculate_ecc(ecctable, buf, ecc+1, ecc+0, ecc+2);
}


