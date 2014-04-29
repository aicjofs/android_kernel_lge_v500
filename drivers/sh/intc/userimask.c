/*
 * Support for hardware-assisted userspace interrupt masking.
 *
 * Copyright (C) 2010  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 */
#define pr_fmt(fmt) "intc: " fmt

#include <linux/errno.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/stat.h>
#include <asm/sizes.h>
#include "internals.h"

static void __iomem *uimask;

static ssize_t
show_intc_userimask(struct device *dev,
		    struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", (__raw_readl(uimask) >> 4) & 0xf);
}

static ssize_t
store_intc_userimask(struct device *dev,
		     struct device_attribute *attr,
		     const char *buf, size_t count)
{
	unsigned long level;

	level = simple_strtoul(buf, NULL, 10);

	/*
                                                              
                                                              
   
                                                           
                                                                
                                                            
                                                               
   
                                                               
                                            
  */
	if (level >= intc_get_dfl_prio_level())
		return -EINVAL;

	__raw_writel(0xa5 << 24 | level << 4, uimask);

	return count;
}

static DEVICE_ATTR(userimask, S_IRUSR | S_IWUSR,
		   show_intc_userimask, store_intc_userimask);


static int __init userimask_sysdev_init(void)
{
	if (unlikely(!uimask))
		return -ENXIO;

	return device_create_file(intc_subsys.dev_root, &dev_attr_userimask);
}
late_initcall(userimask_sysdev_init);

int register_intc_userimask(unsigned long addr)
{
	if (unlikely(uimask))
		return -EBUSY;

	uimask = ioremap_nocache(addr, SZ_4K);
	if (unlikely(!uimask))
		return -ENOMEM;

	pr_info("userimask support registered for levels 0 -> %d\n",
		intc_get_dfl_prio_level() - 1);

	return 0;
}
