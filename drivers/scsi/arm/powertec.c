/*
 *  linux/drivers/acorn/scsi/powertec.c
 *
 *  Copyright (C) 1997-2005 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/module.h>
#include <linux/blkdev.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/ioport.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/init.h>
#include <linux/dma-mapping.h>

#include <asm/dma.h>
#include <asm/ecard.h>
#include <asm/io.h>
#include <asm/pgtable.h>

#include "../scsi.h"
#include <scsi/scsi_host.h>
#include "fas216.h"
#include "scsi.h"

#include <scsi/scsicam.h>

#define POWERTEC_FAS216_OFFSET	0x3000
#define POWERTEC_FAS216_SHIFT	6

#define POWERTEC_INTR_STATUS	0x2000
#define POWERTEC_INTR_BIT	0x80

#define POWERTEC_RESET_CONTROL	0x1018
#define POWERTEC_RESET_BIT	1

#define POWERTEC_TERM_CONTROL	0x2018
#define POWERTEC_TERM_ENABLE	1

#define POWERTEC_INTR_CONTROL	0x101c
#define POWERTEC_INTR_ENABLE	1
#define POWERTEC_INTR_DISABLE	0

#define VERSION	"1.10 (19/01/2003 2.5.59)"

/*
                                                 
                      
 */
static int term[MAX_ECARDS] = { 1, 1, 1, 1, 1, 1, 1, 1 };

#define NR_SG	256

struct powertec_info {
	FAS216_Info		info;
	struct expansion_card	*ec;
	void __iomem		*base;
	unsigned int		term_ctl;
	struct scatterlist	sg[NR_SG];
};

/*                                                  
                                                     
                                              
                                      
 */
static void
powertecscsi_irqenable(struct expansion_card *ec, int irqnr)
{
	struct powertec_info *info = ec->irq_data;
	writeb(POWERTEC_INTR_ENABLE, info->base + POWERTEC_INTR_CONTROL);
}

/*                                                   
                                                      
                                              
                                      
 */
static void
powertecscsi_irqdisable(struct expansion_card *ec, int irqnr)
{
	struct powertec_info *info = ec->irq_data;
	writeb(POWERTEC_INTR_DISABLE, info->base + POWERTEC_INTR_CONTROL);
}

static const expansioncard_ops_t powertecscsi_ops = {
	.irqenable	= powertecscsi_irqenable,
	.irqdisable	= powertecscsi_irqdisable,
};

/*                                                          
                                                          
                                          
                                                   
 */
static void
powertecscsi_terminator_ctl(struct Scsi_Host *host, int on_off)
{
	struct powertec_info *info = (struct powertec_info *)host->hostdata;

	info->term_ctl = on_off ? POWERTEC_TERM_ENABLE : 0;
	writeb(info->term_ctl, info->base + POWERTEC_TERM_CONTROL);
}

/*                                                       
                                                       
                                       
                                                    
 */
static irqreturn_t powertecscsi_intr(int irq, void *dev_id)
{
	struct powertec_info *info = dev_id;

	return fas216_intr(&info->info);
}

/*                                                                                 
                                 
                              
                            
                                          
                                                                            
                                              
 */
static fasdmatype_t
powertecscsi_dma_setup(struct Scsi_Host *host, struct scsi_pointer *SCp,
		       fasdmadir_t direction, fasdmatype_t min_type)
{
	struct powertec_info *info = (struct powertec_info *)host->hostdata;
	struct device *dev = scsi_get_device(host);
	int dmach = info->info.scsi.dma;

	if (info->info.ifcfg.capabilities & FASCAP_DMA &&
	    min_type == fasdma_real_all) {
		int bufs, map_dir, dma_dir;

		bufs = copy_SCp_to_sg(&info->sg[0], SCp, NR_SG);

		if (direction == DMA_OUT)
			map_dir = DMA_TO_DEVICE,
			dma_dir = DMA_MODE_WRITE;
		else
			map_dir = DMA_FROM_DEVICE,
			dma_dir = DMA_MODE_READ;

		dma_map_sg(dev, info->sg, bufs, map_dir);

		disable_dma(dmach);
		set_dma_sg(dmach, info->sg, bufs);
		set_dma_mode(dmach, dma_dir);
		enable_dma(dmach);
		return fasdma_real_all;
	}

	/*
                           
                      
  */
	return fasdma_pio;
}

/*                                                  
                           
                          
                        
 */
static void
powertecscsi_dma_stop(struct Scsi_Host *host, struct scsi_pointer *SCp)
{
	struct powertec_info *info = (struct powertec_info *)host->hostdata;
	if (info->info.scsi.dma != NO_DMA)
		disable_dma(info->info.scsi.dma);
}

/*                                                                  
                                                                
                                                              
                                                                           
 */
const char *powertecscsi_info(struct Scsi_Host *host)
{
	struct powertec_info *info = (struct powertec_info *)host->hostdata;
	static char string[150];

	sprintf(string, "%s (%s) in slot %d v%s terminators o%s",
		host->hostt->name, info->info.scsi.type, info->ec->slot_no,
		VERSION, info->term_ctl ? "n" : "ff");

	return string;
}

/*                                                                                            
                                            
                                    
                                                                    
                                       
                           
 */
static int
powertecscsi_set_proc_info(struct Scsi_Host *host, char *buffer, int length)
{
	int ret = length;

	if (length >= 12 && strncmp(buffer, "POWERTECSCSI", 12) == 0) {
		buffer += 12;
		length -= 12;

		if (length >= 5 && strncmp(buffer, "term=", 5) == 0) {
			if (buffer[5] == '1')
				powertecscsi_terminator_ctl(host, 1);
			else if (buffer[5] == '0')
				powertecscsi_terminator_ctl(host, 0);
			else
				ret = -EINVAL;
		} else
			ret = -EINVAL;
	} else
		ret = -EINVAL;

	return ret;
}

/*                                                                                
                                          
                                                                             
                              
                                                        
                                                                              
                                        
                                                                   
                                   
                                                
                                               
 */
int powertecscsi_proc_info(struct Scsi_Host *host, char *buffer, char **start, off_t offset,
			    int length, int inout)
{
	struct powertec_info *info;
	char *p = buffer;
	int pos;

	if (inout == 1)
		return powertecscsi_set_proc_info(host, buffer, length);

	info = (struct powertec_info *)host->hostdata;

	p += sprintf(p, "PowerTec SCSI driver v%s\n", VERSION);
	p += fas216_print_host(&info->info, p);
	p += sprintf(p, "Term    : o%s\n",
			info->term_ctl ? "n" : "ff");

	p += fas216_print_stats(&info->info, p);
	p += fas216_print_devices(&info->info, p);

	*start = buffer + offset;
	pos = p - buffer - offset;
	if (pos > length)
		pos = length;

	return pos;
}

static ssize_t powertecscsi_show_term(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct expansion_card *ec = ECARD_DEV(dev);
	struct Scsi_Host *host = ecard_get_drvdata(ec);
	struct powertec_info *info = (struct powertec_info *)host->hostdata;

	return sprintf(buf, "%d\n", info->term_ctl ? 1 : 0);
}

static ssize_t
powertecscsi_store_term(struct device *dev, struct device_attribute *attr, const char *buf, size_t len)
{
	struct expansion_card *ec = ECARD_DEV(dev);
	struct Scsi_Host *host = ecard_get_drvdata(ec);

	if (len > 1)
		powertecscsi_terminator_ctl(host, buf[0] != '0');

	return len;
}

static DEVICE_ATTR(bus_term, S_IRUGO | S_IWUSR,
		   powertecscsi_show_term, powertecscsi_store_term);

static struct scsi_host_template powertecscsi_template = {
	.module				= THIS_MODULE,
	.proc_info			= powertecscsi_proc_info,
	.name				= "PowerTec SCSI",
	.info				= powertecscsi_info,
	.queuecommand			= fas216_queue_command,
	.eh_host_reset_handler		= fas216_eh_host_reset,
	.eh_bus_reset_handler		= fas216_eh_bus_reset,
	.eh_device_reset_handler	= fas216_eh_device_reset,
	.eh_abort_handler		= fas216_eh_abort,

	.can_queue			= 8,
	.this_id			= 7,
	.sg_tablesize			= SCSI_MAX_SG_CHAIN_SEGMENTS,
	.dma_boundary			= IOMD_DMA_BOUNDARY,
	.cmd_per_lun			= 2,
	.use_clustering			= ENABLE_CLUSTERING,
	.proc_name			= "powertec",
};

static int __devinit
powertecscsi_probe(struct expansion_card *ec, const struct ecard_id *id)
{
	struct Scsi_Host *host;
	struct powertec_info *info;
	void __iomem *base;
	int ret;

	ret = ecard_request_resources(ec);
	if (ret)
		goto out;

	base = ecardm_iomap(ec, ECARD_RES_IOCFAST, 0, 0);
	if (!base) {
		ret = -ENOMEM;
		goto out_region;
	}

	host = scsi_host_alloc(&powertecscsi_template,
			       sizeof (struct powertec_info));
	if (!host) {
		ret = -ENOMEM;
		goto out_region;
	}

	ecard_set_drvdata(ec, host);

	info = (struct powertec_info *)host->hostdata;
	info->base = base;
	powertecscsi_terminator_ctl(host, term[ec->slot_no]);

	info->ec = ec;
	info->info.scsi.io_base		= base + POWERTEC_FAS216_OFFSET;
	info->info.scsi.io_shift	= POWERTEC_FAS216_SHIFT;
	info->info.scsi.irq		= ec->irq;
	info->info.scsi.dma		= ec->dma;
	info->info.ifcfg.clockrate	= 40; /*     */
	info->info.ifcfg.select_timeout	= 255;
	info->info.ifcfg.asyncperiod	= 200; /*    */
	info->info.ifcfg.sync_max_depth	= 7;
	info->info.ifcfg.cntl3		= CNTL3_BS8 | CNTL3_FASTSCSI | CNTL3_FASTCLK;
	info->info.ifcfg.disconnect_ok	= 1;
	info->info.ifcfg.wide_max_size	= 0;
	info->info.ifcfg.capabilities	= 0;
	info->info.dma.setup		= powertecscsi_dma_setup;
	info->info.dma.pseudo		= NULL;
	info->info.dma.stop		= powertecscsi_dma_stop;

	ec->irqaddr	= base + POWERTEC_INTR_STATUS;
	ec->irqmask	= POWERTEC_INTR_BIT;

	ecard_setirq(ec, &powertecscsi_ops, info);

	device_create_file(&ec->dev, &dev_attr_bus_term);

	ret = fas216_init(host);
	if (ret)
		goto out_free;

	ret = request_irq(ec->irq, powertecscsi_intr,
			  IRQF_DISABLED, "powertec", info);
	if (ret) {
		printk("scsi%d: IRQ%d not free: %d\n",
		       host->host_no, ec->irq, ret);
		goto out_release;
	}

	if (info->info.scsi.dma != NO_DMA) {
		if (request_dma(info->info.scsi.dma, "powertec")) {
			printk("scsi%d: DMA%d not free, using PIO\n",
			       host->host_no, info->info.scsi.dma);
			info->info.scsi.dma = NO_DMA;
		} else {
			set_dma_speed(info->info.scsi.dma, 180);
			info->info.ifcfg.capabilities |= FASCAP_DMA;
		}
	}

	ret = fas216_add(host, &ec->dev);
	if (ret == 0)
		goto out;

	if (info->info.scsi.dma != NO_DMA)
		free_dma(info->info.scsi.dma);
	free_irq(ec->irq, host);

 out_release:
	fas216_release(host);

 out_free:
	device_remove_file(&ec->dev, &dev_attr_bus_term);
	scsi_host_put(host);

 out_region:
	ecard_release_resources(ec);

 out:
	return ret;
}

static void __devexit powertecscsi_remove(struct expansion_card *ec)
{
	struct Scsi_Host *host = ecard_get_drvdata(ec);
	struct powertec_info *info = (struct powertec_info *)host->hostdata;

	ecard_set_drvdata(ec, NULL);
	fas216_remove(host);

	device_remove_file(&ec->dev, &dev_attr_bus_term);

	if (info->info.scsi.dma != NO_DMA)
		free_dma(info->info.scsi.dma);
	free_irq(ec->irq, info);

	fas216_release(host);
	scsi_host_put(host);
	ecard_release_resources(ec);
}

static const struct ecard_id powertecscsi_cids[] = {
	{ MANU_ALSYSTEMS, PROD_ALSYS_SCSIATAPI },
	{ 0xffff, 0xffff },
};

static struct ecard_driver powertecscsi_driver = {
	.probe		= powertecscsi_probe,
	.remove		= __devexit_p(powertecscsi_remove),
	.id_table	= powertecscsi_cids,
	.drv = {
		.name		= "powertecscsi",
	},
};

static int __init powertecscsi_init(void)
{
	return ecard_register_driver(&powertecscsi_driver);
}

static void __exit powertecscsi_exit(void)
{
	ecard_remove_driver(&powertecscsi_driver);
}

module_init(powertecscsi_init);
module_exit(powertecscsi_exit);

MODULE_AUTHOR("Russell King");
MODULE_DESCRIPTION("Powertec SCSI driver");
module_param_array(term, int, NULL, 0);
MODULE_PARM_DESC(term, "SCSI bus termination");
MODULE_LICENSE("GPL");
