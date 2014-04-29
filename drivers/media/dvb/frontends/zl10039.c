/*
 *  Driver for Zarlink ZL10039 DVB-S tuner
 *
 *  Copyright 2007 Jan D. Louw <jd.louw@mweb.co.za>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/dvb/frontend.h>

#include "dvb_frontend.h"
#include "zl10039.h"

static int debug;

#define dprintk(args...) \
	do { \
		if (debug) \
			printk(KERN_DEBUG args); \
	} while (0)

enum zl10039_model_id {
	ID_ZL10039 = 1
};

struct zl10039_state {
	struct i2c_adapter *i2c;
	u8 i2c_addr;
	u8 id;
};

enum zl10039_reg_addr {
	PLL0 = 0,
	PLL1,
	PLL2,
	PLL3,
	RFFE,
	BASE0,
	BASE1,
	BASE2,
	LO0,
	LO1,
	LO2,
	LO3,
	LO4,
	LO5,
	LO6,
	GENERAL
};

static int zl10039_read(const struct zl10039_state *state,
			const enum zl10039_reg_addr reg, u8 *buf,
			const size_t count)
{
	u8 regbuf[] = { reg };
	struct i2c_msg msg[] = {
		{/*                        */
			.addr = state->i2c_addr,
			.flags = 0,
			.buf = regbuf,
			.len = 1,
		}, {/*                  */
			.addr = state->i2c_addr,
			.flags = I2C_M_RD,
			.buf = buf,
			.len = count,
		},
	};

	dprintk("%s\n", __func__);

	if (i2c_transfer(state->i2c, msg, 2) != 2) {
		dprintk("%s: i2c read error\n", __func__);
		return -EREMOTEIO;
	}

	return 0; /*         */
}

static int zl10039_write(struct zl10039_state *state,
			const enum zl10039_reg_addr reg, const u8 *src,
			const size_t count)
{
	u8 buf[count + 1];
	struct i2c_msg msg = {
		.addr = state->i2c_addr,
		.flags = 0,
		.buf = buf,
		.len = count + 1,
	};

	dprintk("%s\n", __func__);
	/*                                           */
	buf[0] = reg;
	memcpy(&buf[1], src, count);
	if (i2c_transfer(state->i2c, &msg, 1) != 1) {
		dprintk("%s: i2c write error\n", __func__);
		return -EREMOTEIO;
	}

	return 0; /*         */
}

static inline int zl10039_readreg(struct zl10039_state *state,
				const enum zl10039_reg_addr reg, u8 *val)
{
	return zl10039_read(state, reg, val, 1);
}

static inline int zl10039_writereg(struct zl10039_state *state,
				const enum zl10039_reg_addr reg,
				const u8 val)
{
	return zl10039_write(state, reg, &val, 1);
}

static int zl10039_init(struct dvb_frontend *fe)
{
	struct zl10039_state *state = fe->tuner_priv;
	int ret;

	dprintk("%s\n", __func__);
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	/*             */
	ret = zl10039_writereg(state, GENERAL, 0x40);
	if (ret < 0) {
		dprintk("Note: i2c write error normal when resetting the "
			"tuner\n");
	}
	/*         */
	ret = zl10039_writereg(state, GENERAL, 0x01);
	if (ret < 0) {
		dprintk("Tuner power up failed\n");
		return ret;
	}
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	return 0;
}

static int zl10039_sleep(struct dvb_frontend *fe)
{
	struct zl10039_state *state = fe->tuner_priv;
	int ret;

	dprintk("%s\n", __func__);
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	ret = zl10039_writereg(state, GENERAL, 0x80);
	if (ret < 0) {
		dprintk("Tuner sleep failed\n");
		return ret;
	}
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	return 0;
}

static int zl10039_set_params(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	struct zl10039_state *state = fe->tuner_priv;
	u8 buf[6];
	u8 bf;
	u32 fbw;
	u32 div;
	int ret;

	dprintk("%s\n", __func__);
	dprintk("Set frequency = %d, symbol rate = %d\n",
			c->frequency, c->symbol_rate);

	/*                                       */
	/*                                          */
	div = (c->frequency * 1000) / 126387;
	fbw = (c->symbol_rate * 27) / 32000;
	/*                                          */
	bf = ((fbw * 5088) / 1011100) - 1;

	/*           */
	buf[0] = (div >> 8) & 0x7f;
	buf[1] = (div >> 0) & 0xff;
	/*                 */
	/*                              */
	buf[2] = 0x1D;
	/*              */
	buf[3] = 0x40;
	/*                   */
	buf[4] = 0x6E; /*               */
	/*                       */
	buf[5] = bf;

	/*               */
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	/*                                   */
	ret = zl10039_writereg(state, BASE1, 0x0A);
	if (ret < 0)
		goto error;
	/*                         */
	ret = zl10039_write(state, PLL0, buf, sizeof(buf));
	if (ret < 0)
		goto error;
	/*                                    */
	ret = zl10039_writereg(state, BASE1, 0x6A);
	if (ret < 0)
		goto error;

	/*                */
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);
	return 0;
error:
	dprintk("Error setting tuner\n");
	return ret;
}

static int zl10039_release(struct dvb_frontend *fe)
{
	struct zl10039_state *state = fe->tuner_priv;

	dprintk("%s\n", __func__);
	kfree(state);
	fe->tuner_priv = NULL;
	return 0;
}

static struct dvb_tuner_ops zl10039_ops = {
	.release = zl10039_release,
	.init = zl10039_init,
	.sleep = zl10039_sleep,
	.set_params = zl10039_set_params,
};

struct dvb_frontend *zl10039_attach(struct dvb_frontend *fe,
		u8 i2c_addr, struct i2c_adapter *i2c)
{
	struct zl10039_state *state = NULL;

	dprintk("%s\n", __func__);
	state = kmalloc(sizeof(struct zl10039_state), GFP_KERNEL);
	if (state == NULL)
		goto error;

	state->i2c = i2c;
	state->i2c_addr = i2c_addr;

	/*               */
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	/*                                */
	if (zl10039_readreg(state, GENERAL, &state->id) < 0) {
		/*                */
		if (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
		goto error;
	}
	/*                */
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	state->id = state->id & 0x0f;
	switch (state->id) {
	case ID_ZL10039:
		strcpy(fe->ops.tuner_ops.info.name,
			"Zarlink ZL10039 DVB-S tuner");
		break;
	default:
		dprintk("Chip ID=%x does not match a known type\n", state->id);
		goto error;
	}

	memcpy(&fe->ops.tuner_ops, &zl10039_ops, sizeof(struct dvb_tuner_ops));
	fe->tuner_priv = state;
	dprintk("Tuner attached @ i2c address 0x%02x\n", i2c_addr);
	return fe;
error:
	kfree(state);
	return NULL;
}
EXPORT_SYMBOL(zl10039_attach);

module_param(debug, int, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");
MODULE_DESCRIPTION("Zarlink ZL10039 DVB-S tuner driver");
MODULE_AUTHOR("Jan D. Louw <jd.louw@mweb.co.za>");
MODULE_LICENSE("GPL");
