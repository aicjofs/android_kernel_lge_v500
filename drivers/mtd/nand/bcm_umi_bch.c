/*****************************************************************************
* Copyright 2004 - 2009 Broadcom Corporation.  All rights reserved.
*
* Unless you and Broadcom execute a separate written software license
* agreement governing use of this software, this software is licensed to you
* under the terms of the GNU General Public License version 2, available at
* http://www.broadcom.com/licenses/GPLv2.php (the "GPL").
*
* Notwithstanding the above, under no circumstances may you combine this
* software in any way with any other Broadcom software provided under a
* license other than the GPL, without Broadcom's express prior written
* consent.
*****************************************************************************/

/*                                                                         */
#include "nand_bcm_umi.h"

/*                                                                         */
/*                                                                         */
/*                                                                         */
/*                                                                         */

/*                                                                         */
static int bcm_umi_bch_read_page_hwecc(struct mtd_info *mtd,
	struct nand_chip *chip, uint8_t *buf, int page);
static void bcm_umi_bch_write_page_hwecc(struct mtd_info *mtd,
	struct nand_chip *chip, const uint8_t *buf);

/*                                                                         */

/*
                 
                                                                
*/
static struct nand_ecclayout nand_hw_eccoob_512 = {
	/*                            */
	.oobfree = {
#if (NAND_ECC_NUM_BYTES > 3)
		    {.offset = 0, .length = 2}
#else
		    {.offset = 0, .length = 5},
		    {.offset = 6, .length = 7}
#endif
		    }
};

/*
                                                                
                              
*/
static struct nand_ecclayout nand_hw_eccoob_2048 = {
	/*                           */
	.oobfree = {
#if (NAND_ECC_NUM_BYTES > 10)
		    {.offset = 1, .length = 2},
#elif (NAND_ECC_NUM_BYTES > 7)
		    {.offset = 1, .length = 5},
		    {.offset = 16, .length = 6},
		    {.offset = 32, .length = 6},
		    {.offset = 48, .length = 6}
#else
		    {.offset = 1, .length = 8},
		    {.offset = 16, .length = 9},
		    {.offset = 32, .length = 9},
		    {.offset = 48, .length = 9}
#endif
		    }
};

/*                                                              
                               */
static struct nand_ecclayout nand_hw_eccoob_4096 = {
	/*                           */
	.oobfree = {
#if (NAND_ECC_NUM_BYTES > 10)
		    {.offset = 1, .length = 2},
		    {.offset = 16, .length = 3},
		    {.offset = 32, .length = 3},
		    {.offset = 48, .length = 3},
		    {.offset = 64, .length = 3},
		    {.offset = 80, .length = 3},
		    {.offset = 96, .length = 3},
		    {.offset = 112, .length = 3}
#else
		    {.offset = 1, .length = 5},
		    {.offset = 16, .length = 6},
		    {.offset = 32, .length = 6},
		    {.offset = 48, .length = 6},
		    {.offset = 64, .length = 6},
		    {.offset = 80, .length = 6},
		    {.offset = 96, .length = 6},
		    {.offset = 112, .length = 6}
#endif
		    }
};

/*                                                                         */
/*                                                                         */

/*                                                                           
 
                                                                      
                           
                                  
                                  
 
                                                                          */
static int bcm_umi_bch_read_page_hwecc(struct mtd_info *mtd,
				       struct nand_chip *chip, uint8_t * buf,
						 int page)
{
	int sectorIdx = 0;
	int eccsize = chip->ecc.size;
	int eccsteps = chip->ecc.steps;
	uint8_t *datap = buf;
	uint8_t eccCalc[NAND_ECC_NUM_BYTES];
	int sectorOobSize = mtd->oobsize / eccsteps;
	int stat;

	for (sectorIdx = 0; sectorIdx < eccsteps;
			sectorIdx++, datap += eccsize) {
		if (sectorIdx > 0) {
			/*                                     */
			chip->cmdfunc(mtd, NAND_CMD_RNDOUT, sectorIdx * eccsize,
				      -1);
		}

		/*                                            */
		nand_bcm_umi_bch_enable_read_hwecc();

		/*              */
		bcm_umi_nand_read_buf(mtd, datap, eccsize);

		/*                                          */
		nand_bcm_umi_bch_pause_read_ecc_calc();

		/*                  */
		chip->cmdfunc(mtd, NAND_CMD_RNDOUT,
			      mtd->writesize + sectorIdx * sectorOobSize, -1);
		nand_bcm_umi_bch_read_oobEcc(mtd->writesize, eccCalc,
					     NAND_ECC_NUM_BYTES,
					     chip->oob_poi +
					     sectorIdx * sectorOobSize);

		/*                                 */
		stat =
		    nand_bcm_umi_bch_correct_page(datap, eccCalc,
						  NAND_ECC_NUM_BYTES);

		/*              */
		if (stat < 0) {
#if defined(NAND_BCM_UMI_DEBUG)
			printk(KERN_WARNING "%s uncorr_err sectorIdx=%d\n",
			       __func__, sectorIdx);
			printk(KERN_WARNING
			       "%s data %02x %02x %02x %02x "
					 "%02x %02x %02x %02x\n",
			       __func__, datap[0], datap[1], datap[2], datap[3],
			       datap[4], datap[5], datap[6], datap[7]);
			printk(KERN_WARNING
			       "%s ecc  %02x %02x %02x %02x "
					 "%02x %02x %02x %02x %02x %02x "
					 "%02x %02x %02x\n",
			       __func__, eccCalc[0], eccCalc[1], eccCalc[2],
			       eccCalc[3], eccCalc[4], eccCalc[5], eccCalc[6],
			       eccCalc[7], eccCalc[8], eccCalc[9], eccCalc[10],
			       eccCalc[11], eccCalc[12]);
			BUG();
#endif
			mtd->ecc_stats.failed++;
		} else {
#if defined(NAND_BCM_UMI_DEBUG)
			if (stat > 0) {
				printk(KERN_INFO
				       "%s %d correctable_errors detected\n",
				       __func__, stat);
			}
#endif
			mtd->ecc_stats.corrected += stat;
		}
	}
	return 0;
}

/*                                                                           
 
                                                                        
                           
                                  
                    
 
                                                                          */
static void bcm_umi_bch_write_page_hwecc(struct mtd_info *mtd,
	struct nand_chip *chip, const uint8_t *buf)
{
	int sectorIdx = 0;
	int eccsize = chip->ecc.size;
	int eccsteps = chip->ecc.steps;
	const uint8_t *datap = buf;
	uint8_t *oobp = chip->oob_poi;
	int sectorOobSize = mtd->oobsize / eccsteps;

	for (sectorIdx = 0; sectorIdx < eccsteps;
	     sectorIdx++, datap += eccsize, oobp += sectorOobSize) {
		/*                                            */
		nand_bcm_umi_bch_enable_write_hwecc();
		bcm_umi_nand_write_buf(mtd, datap, eccsize);
		nand_bcm_umi_bch_write_oobEcc(mtd->writesize, oobp,
					      NAND_ECC_NUM_BYTES);
	}

	bcm_umi_nand_write_buf(mtd, chip->oob_poi, mtd->oobsize);
}
