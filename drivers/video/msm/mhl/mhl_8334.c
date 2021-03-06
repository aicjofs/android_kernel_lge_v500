/* Copyright (c) 2012, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/types.h>
#include <linux/bitops.h>
#include <linux/clk.h>
#include <linux/mutex.h>
#include <mach/msm_hdmi_audio.h>
#include <mach/clk.h>
#include <mach/msm_iomap.h>
#include <mach/socinfo.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/regulator/consumer.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/mhl_8334.h>

#include "msm_fb.h"
#include "external_common.h"
#include "hdmi_msm.h"
#include "mhl_i2c_utils.h"


static struct i2c_device_id mhl_sii_i2c_id[] = {
	{ MHL_DRIVER_NAME, 0 },
	{ }
};

struct mhl_msm_state_t *mhl_msm_state;
spinlock_t mhl_state_lock;

static int mhl_i2c_probe(struct i2c_client *client,\
	const struct i2c_device_id *id);
static int mhl_i2c_remove(struct i2c_client *client);
static void force_usb_switch_open(void);
static void release_usb_switch_open(void);
static void switch_mode(enum mhl_st_type to_mode);
static irqreturn_t mhl_tx_isr(int irq, void *dev_id);
void (*notify_usb_online)(int online);
static void mhl_drive_hpd(uint8_t to_state);

static struct i2c_driver mhl_sii_i2c_driver = {
	.driver = {
		.name = MHL_DRIVER_NAME,
		.owner = THIS_MODULE,
	},
	.probe = mhl_i2c_probe,
	/*                                    */
	.remove =  mhl_i2c_remove,
	.id_table = mhl_sii_i2c_id,
};

static void mhl_sii_reset_pin(int on)
{
	gpio_set_value(mhl_msm_state->mhl_data->gpio_mhl_reset, on);
	return;
}

static int mhl_sii_reg_enable(void)
{
	static struct regulator *reg_8038_l20;
	static struct regulator *reg_8038_l11;
	int rc = -EINVAL;

	pr_debug("Inside %s\n", __func__);
	if (!reg_8038_l20) {
		reg_8038_l20 = regulator_get(&mhl_msm_state->i2c_client->dev,
			"mhl_avcc12");
		if (IS_ERR(reg_8038_l20)) {
			pr_err("could not get reg_8038_l20, rc = %ld\n",
				PTR_ERR(reg_8038_l20));
			return -ENODEV;
		}
		rc = regulator_enable(reg_8038_l20);
		if (rc) {
			pr_err("'%s' regulator enable failed, rc=%d\n",
				"mhl_l20", rc);
			return rc;
		} else
		       pr_debug("REGULATOR L20 ENABLED\n");
	}

	if (!reg_8038_l11) {
		reg_8038_l11 = regulator_get(&mhl_msm_state->i2c_client->dev,
			"mhl_iovcc18");
		if (IS_ERR(reg_8038_l11)) {
			pr_err("could not get reg_8038_l11, rc = %ld\n",
				PTR_ERR(reg_8038_l11));
			return -ENODEV;
		}
		rc = regulator_enable(reg_8038_l11);
		if (rc) {
			pr_err("'%s' regulator enable failed, rc=%d\n",
				"mhl_l11", rc);
			return rc;
		} else
			pr_debug("REGULATOR L11 ENABLED\n");
	}

	return rc;
}


static void mhl_sii_power_on(void)
{
	int ret;
	pr_debug("MHL SII POWER ON\n");
	if (!mhl_msm_state->mhl_data->gpio_mhl_power) {
		pr_warn("%s: no power reqd for this platform\n", __func__);
		return;
	}

	ret = gpio_request(mhl_msm_state->mhl_data->gpio_mhl_power, "W_PWR");
	if (ret < 0) {
		pr_err("MHL_POWER_GPIO req failed: %d\n",
			ret);
		return;
	}
	ret = gpio_direction_output(mhl_msm_state->mhl_data->gpio_mhl_power,
		1);
	if (ret < 0) {
		pr_err(
		"SET GPIO MHL_POWER_GPIO direction failed: %d\n",
			ret);
		gpio_free(mhl_msm_state->mhl_data->gpio_mhl_power);
		return;
	}
	gpio_set_value(mhl_msm_state->mhl_data->gpio_mhl_power, 1);

	if (mhl_sii_reg_enable())
		pr_err("Regulator enable failed\n");

	pr_debug("MHL SII POWER ON Successful\n");
	return;
}

/*
                               
                                  
 */
static int mhl_sii_gpio_setup(int on)
{
	int ret;
	if (on) {
		if (mhl_msm_state->mhl_data->gpio_hdmi_mhl_mux) {
			ret = gpio_request(mhl_msm_state->\
				mhl_data->gpio_hdmi_mhl_mux, "W_MUX");
			if (ret < 0) {
				pr_err("GPIO HDMI_MHL MUX req failed:%d\n",
					ret);
				return -EBUSY;
			}
			ret = gpio_direction_output(
				mhl_msm_state->mhl_data->gpio_hdmi_mhl_mux, 0);
			if (ret < 0) {
				pr_err("SET GPIO HDMI_MHL dir failed:%d\n",
					ret);
				gpio_free(mhl_msm_state->\
					mhl_data->gpio_hdmi_mhl_mux);
				return -EBUSY;
			}
			msleep(50);
			gpio_set_value(mhl_msm_state->\
				mhl_data->gpio_hdmi_mhl_mux, 0);
			pr_debug("SET GPIO HDMI MHL MUX %d to 0\n",
				mhl_msm_state->mhl_data->gpio_hdmi_mhl_mux);
		}

		ret = gpio_request(mhl_msm_state->mhl_data->gpio_mhl_reset,
			"W_RST#");
		if (ret < 0) {
			pr_err("GPIO RESET request failed: %d\n", ret);
			return -EBUSY;
		}
		ret = gpio_direction_output(mhl_msm_state->\
			mhl_data->gpio_mhl_reset, 1);
		if (ret < 0) {
			pr_err("SET GPIO RESET direction failed: %d\n", ret);
			gpio_free(mhl_msm_state->mhl_data->gpio_mhl_reset);
			gpio_free(mhl_msm_state->mhl_data->gpio_hdmi_mhl_mux);
			return -EBUSY;
		}
		ret = gpio_request(mhl_msm_state->mhl_data->gpio_mhl_int,
			"W_INT");
		if (ret < 0) {
			pr_err("GPIO INT request failed: %d\n", ret);
			gpio_free(mhl_msm_state->mhl_data->gpio_mhl_reset);
			gpio_free(mhl_msm_state->mhl_data->gpio_hdmi_mhl_mux);
			return -EBUSY;
		}
		ret = gpio_direction_input(mhl_msm_state->\
			mhl_data->gpio_mhl_int);
		if (ret < 0) {
			pr_err("SET GPIO INTR direction failed: %d\n", ret);
			gpio_free(mhl_msm_state->mhl_data->gpio_mhl_reset);
			gpio_free(mhl_msm_state->mhl_data->gpio_mhl_int);
			gpio_free(mhl_msm_state->mhl_data->gpio_hdmi_mhl_mux);
			return -EBUSY;
		}
	} else {
		gpio_free(mhl_msm_state->mhl_data->gpio_mhl_reset);
		gpio_free(mhl_msm_state->mhl_data->gpio_mhl_int);
		gpio_free(mhl_msm_state->mhl_data->gpio_hdmi_mhl_mux);
		gpio_free(mhl_msm_state->mhl_data->gpio_mhl_power);
	}

	return 0;
}

bool mhl_is_connected(void)
{
	return true;
}


/*                            */

int mhl_device_discovery(const char *name, int *result)

{
	int timeout ;
	mhl_i2c_reg_write(TX_PAGE_3, 0x0010, 0x27);
	msleep(50);
	if (mhl_msm_state->cur_state == POWER_STATE_D3) {
		/*                                                 */
		INIT_COMPLETION(mhl_msm_state->rgnd_done);
		timeout = wait_for_completion_interruptible_timeout
			(&mhl_msm_state->rgnd_done, HZ/2);
		if (!timeout) {
			/*                                    */
			/*                                           */
			pr_debug("Timedout Returning from discovery mode\n");
			*result = MHL_DISCOVERY_RESULT_USB;
			return 0;
		}
		*result = mhl_msm_state->mhl_mode ?
			MHL_DISCOVERY_RESULT_MHL : MHL_DISCOVERY_RESULT_USB;
	} else
		/*                                */
		*result = MHL_DISCOVERY_RESULT_MHL;

	return 0;
}
EXPORT_SYMBOL(mhl_device_discovery);

int mhl_register_callback(const char *name, void (*callback)(int online))
{
	pr_debug("%s\n", __func__);
	if (!callback)
		return -EINVAL;
	if (!notify_usb_online)
		notify_usb_online = callback;
	return 0;
}
EXPORT_SYMBOL(mhl_register_callback);

int mhl_unregister_callback(const char *name)
{
	pr_debug("%s\n", __func__);
	if (notify_usb_online)
		notify_usb_online = NULL;
	return 0;
}
EXPORT_SYMBOL(mhl_unregister_callback);


static void cbus_reset(void)
{
	uint8_t i;

	/*
            
  */
	mhl_i2c_reg_modify(TX_PAGE_3, 0x0000, BIT3, BIT3);
	msleep(20);
	mhl_i2c_reg_modify(TX_PAGE_3, 0x0000, BIT3, 0x00);
	/*
                           
  */
	mhl_i2c_reg_write(TX_PAGE_L0, 0x0075, BIT6);
	mhl_i2c_reg_write(TX_PAGE_3, 0x0022,
		BIT0 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6);
	/*      */
	if (mhl_msm_state->chip_rev_id < 1)
		mhl_i2c_reg_write(TX_PAGE_3, 0x0024, BIT3 | BIT4);
	else
		/*                                            */
		mhl_i2c_reg_write(TX_PAGE_3, 0x0024, 0x00);

	/*                    */
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0009,
		BIT2 | BIT3 | BIT4 | BIT5 | BIT6);

	/*                    */
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x001F, BIT2 | BIT3);

	for (i = 0; i < 4; i++) {
		/*
                                              
                                
   */
		mhl_i2c_reg_write(TX_PAGE_CBUS, (0xE0 + i), 0xFF);

		/*
                                           
                                   
   */
		mhl_i2c_reg_write(TX_PAGE_CBUS, (0xF0 + i), 0xFF);
	}
}

static void init_cbus_regs(void)
{
	uint8_t		regval;

	/*                                     */
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0007, 0xF2);
	/*                 */
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0036, 0x03);
	/*                       */
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0039, 0x30);
	/*                     */
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0040, 0x03);
	/*
                                  
                                    
  */
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0080 | DEVCAP_OFFSET_DEV_STATE,
		DEVCAP_VAL_DEV_STATE);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0080 | DEVCAP_OFFSET_MHL_VERSION,
		DEVCAP_VAL_MHL_VERSION);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0080 | DEVCAP_OFFSET_DEV_CAT,
		DEVCAP_VAL_DEV_CAT);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0080 | DEVCAP_OFFSET_ADOPTER_ID_H,
		DEVCAP_VAL_ADOPTER_ID_H);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0080 | DEVCAP_OFFSET_ADOPTER_ID_L,
		DEVCAP_VAL_ADOPTER_ID_L);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0080 | DEVCAP_OFFSET_VID_LINK_MODE,
		DEVCAP_VAL_VID_LINK_MODE);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0080 | DEVCAP_OFFSET_AUD_LINK_MODE,
		DEVCAP_VAL_AUD_LINK_MODE);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0080 | DEVCAP_OFFSET_VIDEO_TYPE,
		DEVCAP_VAL_VIDEO_TYPE);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0080 | DEVCAP_OFFSET_LOG_DEV_MAP,
		DEVCAP_VAL_LOG_DEV_MAP);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0080 | DEVCAP_OFFSET_BANDWIDTH,
		DEVCAP_VAL_BANDWIDTH);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0080 | DEVCAP_OFFSET_FEATURE_FLAG,
		DEVCAP_VAL_FEATURE_FLAG);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0080 | DEVCAP_OFFSET_DEVICE_ID_H,
		DEVCAP_VAL_DEVICE_ID_H);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0080 | DEVCAP_OFFSET_DEVICE_ID_L,
		DEVCAP_VAL_DEVICE_ID_L);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0080 | DEVCAP_OFFSET_SCRATCHPAD_SIZE,
		DEVCAP_VAL_SCRATCHPAD_SIZE);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0080 | DEVCAP_OFFSET_INT_STAT_SIZE,
		DEVCAP_VAL_INT_STAT_SIZE);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0080 | DEVCAP_OFFSET_RESERVED,
		DEVCAP_VAL_RESERVED);

	/*                                         
                                    
                           
  */
	regval = mhl_i2c_reg_read(TX_PAGE_CBUS, 0x0031);
	regval = (regval | 0x0C);
	/*                         */
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0031, regval);
	 /*                       */
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0022, 0x0F);
	/*                         */
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0030, 0x01);
	/*                                   */
	mhl_i2c_reg_modify(TX_PAGE_CBUS, 0x002E, BIT4, BIT4);
}

/*
                                     
 */
static void mhl_init_reg_settings(bool mhl_disc_en)
{

	/*
                                                
            
                                                
  */

	/*                    */
	mhl_i2c_reg_write(TX_PAGE_L1, 0x003D, 0x3F);
	/*
                                           
                               
  */
	msleep(50);
	/*                     */
	mhl_i2c_reg_write(TX_PAGE_2, 0x0011, 0x01);
	/*                                    */
	mhl_i2c_reg_write(TX_PAGE_2, 0x0012, 0x11);
	/*                          */
	mhl_i2c_reg_write(TX_PAGE_3, 0x0030, 0x10);
	/*                            */
	mhl_i2c_reg_write(TX_PAGE_3, 0x0035, 0xAC);
	/*                               */
	mhl_i2c_reg_write(TX_PAGE_3, 0x0031, 0x3C);
	mhl_i2c_reg_write(TX_PAGE_3, 0x0033, 0xD9);
	/*                       */
	mhl_i2c_reg_write(TX_PAGE_3, 0x0037, 0x02);
	/*
                                                
                      
                                                
  */
	/*                     */
	mhl_i2c_reg_write(TX_PAGE_L0, 0x0080, 0x00);
	mhl_i2c_reg_write(TX_PAGE_L0, 0x00F8, 0x0C);
	mhl_i2c_reg_write(TX_PAGE_L0, 0x0085, 0x02);
	mhl_i2c_reg_write(TX_PAGE_2, 0x0000, 0x00);
	mhl_i2c_reg_write(TX_PAGE_2, 0x0013, 0x60);
	/*                 */
	mhl_i2c_reg_write(TX_PAGE_2, 0x0017, 0x03);
	/*         */
	mhl_i2c_reg_write(TX_PAGE_2, 0x001A, 0x20);
	/*         */
	mhl_i2c_reg_write(TX_PAGE_2, 0x0022, 0xE0);
	mhl_i2c_reg_write(TX_PAGE_2, 0x0023, 0xC0);
	mhl_i2c_reg_write(TX_PAGE_2, 0x0024, 0xA0);
	mhl_i2c_reg_write(TX_PAGE_2, 0x0025, 0x80);
	mhl_i2c_reg_write(TX_PAGE_2, 0x0026, 0x60);
	mhl_i2c_reg_write(TX_PAGE_2, 0x0027, 0x40);
	mhl_i2c_reg_write(TX_PAGE_2, 0x0028, 0x20);
	mhl_i2c_reg_write(TX_PAGE_2, 0x0029, 0x00);
	/*                       */
	mhl_i2c_reg_write(TX_PAGE_2, 0x0031, 0x0A);
	/*                                 */
	mhl_i2c_reg_write(TX_PAGE_2, 0x0045, 0x06);
	mhl_i2c_reg_write(TX_PAGE_2, 0x004B, 0x06);
	/*                     */
	mhl_i2c_reg_write(TX_PAGE_2, 0x004C, 0xE0);
	/*                */
	mhl_i2c_reg_write(TX_PAGE_2, 0x004D, 0x00);
	mhl_i2c_reg_write(TX_PAGE_L0, 0x0008, 0x35);
	/*
                                     
                                             
                           
  */
	mhl_i2c_reg_write(TX_PAGE_3, 0x0011, 0xAD);
	/*               */
	mhl_i2c_reg_write(TX_PAGE_3, 0x0014, 0x55);
	/*                                   */
	mhl_i2c_reg_write(TX_PAGE_3, 0x0015, 0x11);
	/*             */
	mhl_i2c_reg_write(TX_PAGE_3, 0x0017, 0x82);
	mhl_i2c_reg_write(TX_PAGE_3, 0x0018, 0x24);
	/*                                       */
	mhl_i2c_reg_write(TX_PAGE_3, 0x0013, 0x8C);
	/*                       */
	if (mhl_disc_en)
		/*                      */
		mhl_i2c_reg_write(TX_PAGE_3, 0x0010, 0x27);
	else
		/*                       */
		mhl_i2c_reg_write(TX_PAGE_3, 0x0010, 0x26);
	mhl_i2c_reg_write(TX_PAGE_3, 0x0016, 0x20);
	/*                                       */
	mhl_i2c_reg_write(TX_PAGE_3, 0x0012, 0x86);
	/*                                              */
	if (mhl_msm_state->cur_state != POWER_STATE_D0_MHL)
		mhl_drive_hpd(HPD_DOWN);

	/*                        */
	mhl_i2c_reg_write(TX_PAGE_3, 0x0000, 0x084);
	/*                            */
	mhl_i2c_reg_write(TX_PAGE_L0, 0x000D, 0x1C);

	cbus_reset();
	init_cbus_regs();
}

static int mhl_chip_init(void)
{
	/*                      */
	mhl_msm_state->chip_rev_id = mhl_i2c_reg_read(TX_PAGE_L0, 0x04);
	pr_debug("MHL: chip rev ID read=[%x]\n", mhl_msm_state->chip_rev_id);

	/*                   */
	mhl_sii_reset_pin(1);
	msleep(20);
	mhl_sii_reset_pin(0);
	msleep(20);
	mhl_sii_reset_pin(1);
	/*                                        */
	msleep(100);

	/*
                                 
  */
	mhl_init_reg_settings(true);

	/*
                              
                                 
                                                    
  */
	switch_mode(POWER_STATE_D3);
	return 0;
}

/*
            
 */
static int mhl_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	int ret = -ENODEV;
	mhl_msm_state->mhl_data = kzalloc(sizeof(struct msm_mhl_platform_data),
		GFP_KERNEL);
	if (!(mhl_msm_state->mhl_data)) {
		ret = -ENOMEM;
		pr_err("MHL I2C Probe failed - no mem\n");
		goto probe_exit;
	}
	mhl_msm_state->i2c_client = client;

	spin_lock_init(&mhl_state_lock);

	i2c_set_clientdata(client, mhl_msm_state);
	mhl_msm_state->mhl_data = client->dev.platform_data;
	pr_debug("MHL: mhl_msm_state->mhl_data->irq=[%d]\n",
		mhl_msm_state->mhl_data->irq);

	/*                      */
	ret = mhl_sii_gpio_setup(1);
	if (ret == -1) {
		pr_err("MHL: mhl_gpio_init has failed\n");
		ret = -ENODEV;
		goto probe_exit;
	}

	mhl_sii_power_on();

	pr_debug("I2C PROBE successful\n");
	return 0;

probe_exit:
	if (mhl_msm_state->mhl_data) {
		/*                */
		mhl_sii_gpio_setup(0);
		kfree(mhl_msm_state->mhl_data);
		mhl_msm_state->mhl_data = NULL;
	}
	return ret;
}

static int mhl_i2c_remove(struct i2c_client *client)
{
	pr_debug("%s\n", __func__);
	mhl_sii_gpio_setup(0);
	kfree(mhl_msm_state->mhl_data);
	return 0;
}

static int __init mhl_msm_init(void)
{
	int32_t     ret;

	pr_debug("%s\n", __func__);
	mhl_msm_state = kzalloc(sizeof(struct mhl_msm_state_t), GFP_KERNEL);
	if (!mhl_msm_state) {
		pr_err("mhl_msm_init FAILED: out of memory\n");
		ret = -ENOMEM;
		goto init_exit;
	}

	mhl_msm_state->i2c_client = NULL;
	ret = i2c_add_driver(&mhl_sii_i2c_driver);
	if (ret) {
		pr_err("MHL: I2C driver add failed: %d\n", ret);
		ret = -ENODEV;
		goto init_exit;
	} else {
		if (mhl_msm_state->i2c_client == NULL) {
			pr_err("MHL: I2C driver add failed\n");
			ret = -ENODEV;
			goto init_exit;
		}
		pr_info("MHL: I2C driver added\n");
	}

	/*                        */
	pr_debug("MHL: mhl_msm_state->mhl_data->irq=[%d]\n",
		mhl_msm_state->mhl_data->irq);
	ret = request_threaded_irq(mhl_msm_state->mhl_data->irq, NULL,
				   &mhl_tx_isr,
				 IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				 "mhl_tx_isr", mhl_msm_state);
	if (ret != 0) {
		pr_err("request_threaded_irq failed, status: %d\n",
			ret);
		ret = -EACCES; /*                */
		goto init_exit;
	} else
		pr_debug("request_threaded_irq succeeded\n");

	mhl_msm_state->cur_state = POWER_STATE_D0_MHL;

	/*                                 */
	mhl_chip_init();
	init_completion(&mhl_msm_state->rgnd_done);
	return 0;

init_exit:
	pr_err("Exiting from the init with err\n");
	i2c_del_driver(&mhl_sii_i2c_driver);
	if (!mhl_msm_state) {
		kfree(mhl_msm_state);
		mhl_msm_state = NULL;
	 }
	 return ret;
}

static void switch_mode(enum mhl_st_type to_mode)
{
	unsigned long flags;

	switch (to_mode) {
	case POWER_STATE_D0_NO_MHL:
		break;
	case POWER_STATE_D0_MHL:
		mhl_init_reg_settings(true);
		/*                */
		mhl_i2c_reg_modify(TX_PAGE_3, 0x0010, BIT1 | BIT0, BIT0);

		/*
                                    
                                      
   */
		mhl_i2c_reg_modify(TX_PAGE_TPI, 0x001E, BIT1 | BIT0, 0x00);
		break;
	case POWER_STATE_D3:
		if (mhl_msm_state->cur_state != POWER_STATE_D3) {
			/*                                       */
			mhl_drive_hpd(HPD_DOWN);
			/*
                                               
                       
    */
			mhl_i2c_reg_write(TX_PAGE_3, 0x0030, 0xD0);
			msleep(50);
			mhl_i2c_reg_modify(TX_PAGE_3, 0x0010,
				BIT1 | BIT0, BIT1);
			spin_lock_irqsave(&mhl_state_lock, flags);
			mhl_msm_state->cur_state = POWER_STATE_D3;
			spin_unlock_irqrestore(&mhl_state_lock, flags);
		}
		break;
	default:
		break;
	}
}

static void mhl_drive_hpd(uint8_t to_state)
{
	if (mhl_msm_state->cur_state != POWER_STATE_D0_MHL) {
		pr_err("MHL: invalid state to ctrl HPD\n");
		return;
	}

	pr_debug("%s: To state=[0x%x]\n", __func__, to_state);
	if (to_state == HPD_UP) {
		/*
                          
    
                                       
                        
   */

		/*                           */
		mhl_i2c_reg_modify(TX_PAGE_L0, 0x0080, BIT4, BIT4);

		/*
                                   
                                          
                                               
                     
   */
		mhl_i2c_reg_modify(TX_PAGE_3, 0x0020, BIT4, 0x00);
	} else {
		/*
                            
                                          
                                                      
   */
		mhl_i2c_reg_modify(TX_PAGE_3, 0x20, BIT4 | BIT5, BIT4);
		mhl_i2c_reg_modify(TX_PAGE_L0, 0x0080, BIT4, 0x00);
	}
	return;
}

static void mhl_msm_connection(void)
{
	uint8_t val;
	unsigned long flags;

	pr_debug("%s: cur state = [0x%x]\n", __func__,
		mhl_msm_state->cur_state);

	if (mhl_msm_state->cur_state == POWER_STATE_D0_MHL) {
		/*                                 */
		return;
	}
	spin_lock_irqsave(&mhl_state_lock, flags);
	mhl_msm_state->cur_state = POWER_STATE_D0_MHL;
	spin_unlock_irqrestore(&mhl_state_lock, flags);

	mhl_i2c_reg_write(TX_PAGE_3, 0x30, 0x10);

	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x07, 0xF2);

	/*
                                                   
                                                    
                          
  */
	val = mhl_i2c_reg_read(TX_PAGE_3, 0x10);
	mhl_i2c_reg_write(TX_PAGE_3, 0x10, val | BIT(0));

	return;
}

static void mhl_msm_disconnection(void)
{
	/*
               
                            
  */
	mhl_i2c_reg_write(TX_PAGE_3, 0x30, 0xD0);
	/*                                 */
	mhl_drive_hpd(HPD_DOWN);
	/*                          */
	switch_mode(POWER_STATE_D3);
	return;
}

/*
                                                                
                                                                 
                                                     
 */
static int  mhl_msm_read_rgnd_int(void)
{
	uint8_t rgnd_imp;

	/*
                     
            
                    
                      
                                                                     
                     
  */
	rgnd_imp = (mhl_i2c_reg_read(TX_PAGE_3, 0x001C) & (BIT1 | BIT0));
	pr_debug("Imp Range read = %02X\n", (int)rgnd_imp);

	if (0x02 == rgnd_imp) {
		pr_debug("MHL: MHL DEVICE!!!\n");
		mhl_i2c_reg_modify(TX_PAGE_3, 0x0018, BIT0, BIT0);
		/*
                                     
   */
		mhl_msm_state->mhl_mode = TRUE;
		if (notify_usb_online)
			notify_usb_online(1);
	} else {
		pr_debug("MHL: NON-MHL DEVICE!!!\n");
		mhl_msm_state->mhl_mode = FALSE;
		mhl_i2c_reg_modify(TX_PAGE_3, 0x0018, BIT3, BIT3);
		switch_mode(POWER_STATE_D3);
	}
	complete(&mhl_msm_state->rgnd_done);
	return mhl_msm_state->mhl_mode ?
		MHL_DISCOVERY_RESULT_MHL : MHL_DISCOVERY_RESULT_USB;
}

static void force_usb_switch_open(void)
{
	/*                 */
	mhl_i2c_reg_modify(TX_PAGE_3, 0x0010, BIT0, 0);
	/*                            */
	mhl_i2c_reg_modify(TX_PAGE_3, 0x0015, BIT6, BIT6);
	mhl_i2c_reg_write(TX_PAGE_3, 0x0012, 0x86);
	/*                                            */
	mhl_i2c_reg_modify(TX_PAGE_3, 0x0020, BIT5 | BIT4, BIT4);
}

static void release_usb_switch_open(void)
{
	msleep(50);
	mhl_i2c_reg_modify(TX_PAGE_3, 0x0015, BIT6, 0x00);
	mhl_i2c_reg_modify(TX_PAGE_3, 0x0010, BIT0, BIT0);
}

static void int_4_isr(void)
{
	uint8_t status, reg ;

	/*              */
	status = mhl_i2c_reg_read(TX_PAGE_3, 0x0021);

	/*
                                      
                                         
               
  */
	if ((0x00 == status) && (mhl_msm_state->cur_state == POWER_STATE_D3)) {
		pr_debug("MHL: spurious interrupt\n");
		return;
	}
	if (0xFF != status) {
		if ((status & BIT0) && (mhl_msm_state->chip_rev_id < 1)) {
			uint8_t tmds_cstat;
			uint8_t mhl_fifo_status;

			/*            */
			tmds_cstat = mhl_i2c_reg_read(TX_PAGE_3, 0x0040);

			pr_debug("TMDS CSTAT: 0x%02x\n", tmds_cstat);

			if (tmds_cstat & 0x02) {
				mhl_fifo_status = mhl_i2c_reg_read(TX_PAGE_3,
					0x0023);
				pr_debug("MHL FIFO status: 0x%02x\n",
					mhl_fifo_status);
				if (mhl_fifo_status & 0x0C) {
					mhl_i2c_reg_write(TX_PAGE_3, 0x0023,
						0x0C);

					pr_debug("Apply MHL FIFO Reset\n");
					mhl_i2c_reg_write(TX_PAGE_3, 0x0000,
						0x94);
					mhl_i2c_reg_write(TX_PAGE_3, 0x0000,
						0x84);
				}
			}
		}

		if (status & BIT1)
			pr_debug("MHL: INT4 BIT1 is set\n");

		/*                   */
		if (status & BIT2) {
			pr_debug("mhl_msm_connection() from ISR\n");
			mhl_connect_api(true);
			mhl_msm_connection();
			pr_debug("MHL Connect  Drv: INT4 Status = %02X\n",
				(int) status);
		} else if (status & BIT3) {
			pr_debug("MHL: uUSB-A type device detected.\n");
			mhl_i2c_reg_write(TX_PAGE_3, 0x001C, 0x80);
			switch_mode(POWER_STATE_D3);
		}

		if (status & BIT5) {
			mhl_connect_api(false);
			/*                              */
			reg = mhl_i2c_reg_read(TX_PAGE_3, 0x0021);
			mhl_i2c_reg_write(TX_PAGE_3, 0x0021, reg);
			mhl_msm_disconnection();
			if (notify_usb_online)
				notify_usb_online(0);
			pr_debug("MHL Disconnect Drv: INT4 Status = %02X\n",
				(int)status);
		}

		if ((mhl_msm_state->cur_state != POWER_STATE_D0_MHL) &&\
			(status & BIT6)) {
			/*                 */
			switch_mode(POWER_STATE_D0_MHL);
			mhl_msm_read_rgnd_int();
		}

		/*                              */
		if (mhl_msm_state->cur_state != POWER_STATE_D3) {
			/*                         */
			/*
                                               
                                               
                                                
    */
			if (status & BIT4) {
				force_usb_switch_open();
				release_usb_switch_open();
			}
		}
	}
	pr_debug("MHL END  Drv: INT4 Status = %02X\n", (int) status);
	mhl_i2c_reg_write(TX_PAGE_3, 0x0021, status);

	return;
}

static void int_5_isr(void)
{
	uint8_t intr_5_stat;

	/*
                  
                                       
                                                     
                                               
  */
	intr_5_stat = mhl_i2c_reg_read(TX_PAGE_3, 0x0023);
	mhl_i2c_reg_write(TX_PAGE_3, 0x0023, intr_5_stat);
}


static void int_1_isr(void)
{
	/*                                                */
	uint8_t intr_1_stat;
	uint8_t cbus_stat;

	/*               */
	intr_1_stat = mhl_i2c_reg_read(TX_PAGE_L0, 0x0071);

	if (intr_1_stat) {
		/*                  */
		mhl_i2c_reg_write(TX_PAGE_L0, 0x0071, intr_1_stat);
		if (BIT6 & intr_1_stat) {
			/*
                                        
                                        
    */

			/*                     */
			cbus_stat = mhl_i2c_reg_read(TX_PAGE_CBUS, 0x0D);
			if (BIT6 & cbus_stat)
				mhl_drive_hpd(HPD_UP);
		}
	}
	return;
}

/*
                                               
  
 */
static void mhl_cbus_isr(void)
{
	uint8_t regval;
	int req_done = FALSE;
	uint8_t sub_cmd;
	uint8_t cmd_data;
	int msc_msg_recved = FALSE;
	int rc = -1;

	regval  = mhl_i2c_reg_read(TX_PAGE_CBUS, 0x08);
	if (regval == 0xff)
		return;

	/*                                                                  */
	if (regval)
		mhl_i2c_reg_write(TX_PAGE_CBUS, 0x08, regval);

	pr_debug("%s: CBUS_INT = %02x\n", __func__, regval);

	/*                   */
	if (regval & BIT(3)) {
		sub_cmd = mhl_i2c_reg_read(TX_PAGE_CBUS, 0x18);
		cmd_data = mhl_i2c_reg_read(TX_PAGE_CBUS, 0x19);
		msc_msg_recved = TRUE;
	}

	/*              */
	if (regval & BIT(4))
		req_done = TRUE;

	/*                                          */
	regval  = mhl_i2c_reg_read(TX_PAGE_CBUS, 0x1E);

	/*                                       */
	/*                            */
	if (regval)
		mhl_i2c_reg_write(TX_PAGE_CBUS, 0x1E, regval);

	pr_debug("%s: CBUS_MSC_INT2 = %02x\n", __func__, regval);

	/*                  */
	if (regval & BIT(2)) {
		uint8_t intr;
		intr = mhl_i2c_reg_read(TX_PAGE_CBUS, 0xA0);
		pr_debug("%s: MHL_INT_0 = %02x\n", __func__, intr);
		intr = mhl_i2c_reg_read(TX_PAGE_CBUS, 0xA1);
		pr_debug("%s: MHL_INT_1 = %02x\n", __func__, intr);
		mhl_i2c_reg_write(TX_PAGE_CBUS, 0xA0, 0xFF);
		mhl_i2c_reg_write(TX_PAGE_CBUS, 0xA1, 0xFF);
		mhl_i2c_reg_write(TX_PAGE_CBUS, 0xA2, 0xFF);
		mhl_i2c_reg_write(TX_PAGE_CBUS, 0xA3, 0xFF);
	}

	/*                     */
	if (regval & BIT(3)) {
		uint8_t stat;
		stat = mhl_i2c_reg_read(TX_PAGE_CBUS, 0xB0);
		pr_debug("%s: MHL_STATUS_0 = %02x\n", __func__, stat);
		stat = mhl_i2c_reg_read(TX_PAGE_CBUS, 0xB1);
		pr_debug("%s: MHL_STATUS_1 = %02x\n", __func__, stat);

		mhl_i2c_reg_write(TX_PAGE_CBUS, 0xB0, 0xFF);
		mhl_i2c_reg_write(TX_PAGE_CBUS, 0xB1, 0xFF);
		mhl_i2c_reg_write(TX_PAGE_CBUS, 0xB2, 0xFF);
		mhl_i2c_reg_write(TX_PAGE_CBUS, 0xB3, 0xFF);
	}

	/*                  */
	if (msc_msg_recved) {
		/*                    */
		if (rc)
			pr_err("MHL: mhl msc recv msc msg failed(%d)!\n", rc);
	}

	return;
}

static void clear_all_intrs(void)
{
	uint8_t regval = 0x00;
	/*
                    
 */
	pr_debug("********* EXITING ISR MASK CHECK ?? *************\n");
	pr_debug("Drv: INT1 MASK = %02X\n",
		(int) mhl_i2c_reg_read(TX_PAGE_L0, 0x0071));
	pr_debug("Drv: INT3 MASK = %02X\n",
		(int) mhl_i2c_reg_read(TX_PAGE_L0, 0x0077));
	pr_debug("Drv: INT4 MASK = %02X\n",
		(int) mhl_i2c_reg_read(TX_PAGE_3, 0x0021));
	pr_debug("Drv: INT5 MASK = %02X\n",
		(int) mhl_i2c_reg_read(TX_PAGE_3, 0x0023));
	pr_debug("Drv: CBUS1 MASK = %02X\n",
		(int) mhl_i2c_reg_read(TX_PAGE_CBUS, 0x0009));
	pr_debug("Drv: CBUS2 MASK = %02X\n",
		(int) mhl_i2c_reg_read(TX_PAGE_CBUS, 0x001F));
	pr_debug("********* END OF ISR MASK CHECK *************\n");

	pr_debug("********* EXITING IN ISR ?? *************\n");
	regval = mhl_i2c_reg_read(TX_PAGE_L0, 0x0071);
	pr_debug("Drv: INT1 Status = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_L0, 0x0071, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_L0, 0x0072);
	pr_debug("Drv: INT2 Status = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_L0, 0x0072, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_L0, 0x0073);
	pr_debug("Drv: INT3 Status = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_L0, 0x0073, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_3, 0x0021);
	pr_debug("Drv: INT4 Status = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_3, 0x0021, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_3, 0x0023);
	pr_debug("Drv: INT5 Status = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_3, 0x0023, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x0008);
	pr_debug("Drv: cbusInt Status = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x0008, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x001E);
	pr_debug("Drv: CBUS INTR_2: %d\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x001E, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x00A0);
	pr_debug("Drv: A0 INT Set = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x00A0, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x00A1);
	pr_debug("Drv: A1 INT Set = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x00A1, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x00A2);
	pr_debug("Drv: A2 INT Set = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x00A2, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x00A3);
	pr_debug("Drv: A3 INT Set = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x00A3, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x00B0);
	pr_debug("Drv: B0 STATUS Set = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x00B0, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x00B1);
	pr_debug("Drv: B1 STATUS Set = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x00B1, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x00B2);
	pr_debug("Drv: B2 STATUS Set = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x00B2, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x00B3);
	pr_debug("Drv: B3 STATUS Set = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x00B3, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x00E0);
	pr_debug("Drv: E0 STATUS Set = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x00E0, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x00E1);
	pr_debug("Drv: E1 STATUS Set = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x00E1, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x00E2);
	pr_debug("Drv: E2 STATUS Set = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x00E2, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x00E3);
	pr_debug("Drv: E3 STATUS Set = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x00E3, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x00F0);
	pr_debug("Drv: F0 INT Set = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x00F0, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x00F1);
	pr_debug("Drv: F1 INT Set = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x00F1, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x00F2);
	pr_debug("Drv: F2 INT Set = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x00F2, regval);

	regval =  mhl_i2c_reg_read(TX_PAGE_CBUS, 0x00F3);
	pr_debug("Drv: F3 INT Set = %02X\n", (int)regval);
	mhl_i2c_reg_write(TX_PAGE_CBUS, 0x00F3, regval);
	pr_debug("********* END OF EXITING IN ISR *************\n");
}

static irqreturn_t mhl_tx_isr(int irq, void *dev_id)
{
	/*
                                           
                                       
  */
	int_4_isr();

	pr_debug("MHL: Current POWER state is [0x%x]\n",
		mhl_msm_state->cur_state);
	if (mhl_msm_state->cur_state == POWER_STATE_D0_MHL) {
		/*
                                            
                                           
                       
   */
		int_5_isr();

		/*
                                                 
                                                  
                    
   */
		mhl_cbus_isr();
		int_1_isr();
	}
	clear_all_intrs();
	return IRQ_HANDLED;
}

static void __exit mhl_msm_exit(void)
{
	pr_warn("MHL: Exiting, Bye\n");
	/*
                                                 
  */
	i2c_del_driver(&mhl_sii_i2c_driver);
	if (!mhl_msm_state) {
		kfree(mhl_msm_state);
		mhl_msm_state = NULL;
	 }
}

module_init(mhl_msm_init);
module_exit(mhl_msm_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MHL SII 8334 TX driver");
