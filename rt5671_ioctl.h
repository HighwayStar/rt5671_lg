/* LGE_CHANGE_S
* Comment : add realtek alsa sound driver for woden R2
* 2013-03-05, hyunsoo.yoon@lge.com
*/
/*
 * rt5671_ioctl.h  --  RT5671 ALSA SoC audio driver IO control
 *
 * Copyright 2012 Realtek Microelectronics
 * Author: Bard <bardliao@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __RT5671_IOCTL_H__
#define __RT5671_IOCTL_H__

#include <sound/hwdep.h>
#include <linux/ioctl.h>

enum {
	NORMAL = 0,
	SPK,
	HP,
	ADC_TYPE1,
	ADC_TYPE2,
	ADC_TYPE3,
	MODE_NUM,
};

enum {
	EQ_CH_DACL = 0,
	EQ_CH_DACR,
	EQ_CH_ADC,
	EQ_CH_NUM,
};

#define EQ_REG_NUM 28
typedef struct  hweq_s {
	unsigned int reg[EQ_REG_NUM];
	unsigned int value[EQ_REG_NUM];
	unsigned int ctrl;
} hweq_t;

enum {
	ALC_NORMAL = 0,
	ALC_TYPE1,
	ALC_TYPE2,
	ALC_TYPE3,
	ALC_MODE_NUM,
};

#define ALC_REG_NUM 6
typedef struct hwalc_s {
	unsigned int value[ALC_REG_NUM];
} hwalc_t;

int rt5671_ioctl_common(struct snd_hwdep *hw, struct file *file,
			unsigned int cmd, unsigned long arg);
int rt5671_update_eqmode(
	struct snd_soc_codec *codec, int channel, int mode);
int rt5671_update_alcmode(struct snd_soc_codec *codec, int mode);

#endif /* __RT5671_IOCTL_H__ */
/* LGE_CHANGE_E */
