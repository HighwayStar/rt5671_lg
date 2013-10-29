/*
 * linux/sound/rt5671.h -- Platform data for RT5671
 *
 * Copyright 2013 Realtek Microelectronics
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __LINUX_SND_RT5671_H
#define __LINUX_SND_RT5671_H

struct rt5671_platform_data {
	bool if1_force_64fs;
	bool if2_force_64fs;
};

#endif
