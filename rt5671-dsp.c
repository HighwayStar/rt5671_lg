/*
 * rt5671.c  --  RT5671 ALSA SoC DSP driver
 *
 * Copyright 2011 Realtek Semiconductor Corp.
 * Author: Johnny Hsu <johnnyhsu@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
/*
#define DEBUG
*/
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/platform_device.h>
#include <sound/soc.h>
#include <sound/soc-dapm.h>

#define RTK_IOCTL
#ifdef RTK_IOCTL
#include <linux/spi/spi.h>
#include "rt_codec_ioctl.h"
#endif

#include "rt5671.h"
#include "rt5671-dsp.h"

#define DSP_CLK_RATE RT5671_DSP_CLK_768K

static unsigned short rt5671_dsp_init_patch_code[][2] = { // patch for init time, which is auto generated from FM36600C_signoff0902.patch
	{0xe1, 0x0010}, {0xe2, 0x0000}, {0xe0, 0x6ac9},	// set to dsp0
	{0xe1, 0x0064}, {0xe2, 0x0000}, {0xe0, 0x68c5}, // warm reset
	{0xe1, 0x3f00}, {0xe2, 0x8301}, {0xe3, 0x00f8}, {0xe0, 0x0dcf},
	{0xe1, 0x3f01}, {0xe2, 0x9212}, {0xe3, 0x0098}, {0xe0, 0x0dcf},
	{0xe1, 0x3f02}, {0xe2, 0x830f}, {0xe3, 0x00fa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f03}, {0xe2, 0x9301}, {0xe3, 0x00fa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f04}, {0xe2, 0x81cc}, {0xe3, 0x008c}, {0xe0, 0x0dcf},
	{0xe1, 0x3f05}, {0xe2, 0x4009}, {0xe3, 0x000a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f06}, {0xe2, 0x267c}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f07}, {0xe2, 0x23a2}, {0xe3, 0x00d0}, {0xe0, 0x0dcf},
	{0xe1, 0x3f08}, {0xe2, 0x9212}, {0xe3, 0x00aa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f09}, {0xe2, 0x93ff}, {0xe3, 0x00ea}, {0xe0, 0x0dcf},
	{0xe1, 0x3f0a}, {0xe2, 0x83ff}, {0xe3, 0x00ea}, {0xe0, 0x0dcf},
	{0xe1, 0x3f0b}, {0xe2, 0x278a}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f0c}, {0xe2, 0x1bf0}, {0xe3, 0x00a1}, {0xe0, 0x0dcf},
	{0xe1, 0x3f0d}, {0xe2, 0x8212}, {0xe3, 0x0098}, {0xe0, 0x0dcf},
	{0xe1, 0x3f0e}, {0xe2, 0x9301}, {0xe3, 0x00f8}, {0xe0, 0x0dcf},
	{0xe1, 0x3f0f}, {0xe2, 0x81cc}, {0xe3, 0x008c}, {0xe0, 0x0dcf},
	{0xe1, 0x3f10}, {0xe2, 0x1918}, {0xe3, 0x004f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f11}, {0xe2, 0x8301}, {0xe3, 0x00f8}, {0xe0, 0x0dcf},
	{0xe1, 0x3f12}, {0xe2, 0x9212}, {0xe3, 0x0098}, {0xe0, 0x0dcf},
	{0xe1, 0x3f13}, {0xe2, 0x830f}, {0xe3, 0x00fa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f14}, {0xe2, 0x9301}, {0xe3, 0x00fa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f15}, {0xe2, 0x8212}, {0xe3, 0x00aa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f16}, {0xe2, 0x93ff}, {0xe3, 0x00ea}, {0xe0, 0x0dcf},
	{0xe1, 0x3f17}, {0xe2, 0x83ff}, {0xe3, 0x00ea}, {0xe0, 0x0dcf},
	{0xe1, 0x3f18}, {0xe2, 0x278a}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f19}, {0xe2, 0x1bf1}, {0xe3, 0x0071}, {0xe0, 0x0dcf},
	{0xe1, 0x3f1a}, {0xe2, 0x8212}, {0xe3, 0x0098}, {0xe0, 0x0dcf},
	{0xe1, 0x3f1b}, {0xe2, 0x9301}, {0xe3, 0x00f8}, {0xe0, 0x0dcf},
	{0xe1, 0x3f1c}, {0xe2, 0x8117}, {0xe3, 0x00e5}, {0xe0, 0x0dcf},
	{0xe1, 0x3f1d}, {0xe2, 0x191b}, {0xe3, 0x004f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f1e}, {0xe2, 0x8301}, {0xe3, 0x00f8}, {0xe0, 0x0dcf},
	{0xe1, 0x3f1f}, {0xe2, 0x9212}, {0xe3, 0x0098}, {0xe0, 0x0dcf},
	{0xe1, 0x3f20}, {0xe2, 0x830f}, {0xe3, 0x00fa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f21}, {0xe2, 0x9301}, {0xe3, 0x00fa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f22}, {0xe2, 0x8212}, {0xe3, 0x00aa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f23}, {0xe2, 0x93ff}, {0xe3, 0x00ea}, {0xe0, 0x0dcf},
	{0xe1, 0x3f24}, {0xe2, 0x83ff}, {0xe3, 0x00ea}, {0xe0, 0x0dcf},
	{0xe1, 0x3f25}, {0xe2, 0x278a}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f26}, {0xe2, 0x1bf2}, {0xe3, 0x0041}, {0xe0, 0x0dcf},
	{0xe1, 0x3f27}, {0xe2, 0x8212}, {0xe3, 0x0098}, {0xe0, 0x0dcf},
	{0xe1, 0x3f28}, {0xe2, 0x9301}, {0xe3, 0x00f8}, {0xe0, 0x0dcf},
	{0xe1, 0x3f29}, {0xe2, 0x8117}, {0xe3, 0x00e5}, {0xe0, 0x0dcf},
	{0xe1, 0x3f2a}, {0xe2, 0x1921}, {0xe3, 0x007f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f2b}, {0xe2, 0x8301}, {0xe3, 0x00f8}, {0xe0, 0x0dcf},
	{0xe1, 0x3f2c}, {0xe2, 0x9212}, {0xe3, 0x0098}, {0xe0, 0x0dcf},
	{0xe1, 0x3f2d}, {0xe2, 0x8307}, {0xe3, 0x00fa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f2e}, {0xe2, 0x9301}, {0xe3, 0x00fa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f2f}, {0xe2, 0x81cc}, {0xe3, 0x008c}, {0xe0, 0x0dcf},
	{0xe1, 0x3f30}, {0xe2, 0x4009}, {0xe3, 0x000a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f31}, {0xe2, 0x267c}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f32}, {0xe2, 0x23a2}, {0xe3, 0x00d0}, {0xe0, 0x0dcf},
	{0xe1, 0x3f33}, {0xe2, 0x9212}, {0xe3, 0x00aa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f34}, {0xe2, 0x93ff}, {0xe3, 0x00ea}, {0xe0, 0x0dcf},
	{0xe1, 0x3f35}, {0xe2, 0x83ff}, {0xe3, 0x00ea}, {0xe0, 0x0dcf},
	{0xe1, 0x3f36}, {0xe2, 0x278a}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f37}, {0xe2, 0x1bf3}, {0xe3, 0x0051}, {0xe0, 0x0dcf},
	{0xe1, 0x3f38}, {0xe2, 0x8212}, {0xe3, 0x0098}, {0xe0, 0x0dcf},
	{0xe1, 0x3f39}, {0xe2, 0x9301}, {0xe3, 0x00f8}, {0xe0, 0x0dcf},
	{0xe1, 0x3f3a}, {0xe2, 0x81cc}, {0xe3, 0x008c}, {0xe0, 0x0dcf},
	{0xe1, 0x3f3b}, {0xe2, 0x3400}, {0xe3, 0x004e}, {0xe0, 0x0dcf},
	{0xe1, 0x3f3c}, {0xe2, 0x1a09}, {0xe3, 0x00ef}, {0xe0, 0x0dcf},
	{0xe1, 0x3f3d}, {0xe2, 0x8301}, {0xe3, 0x00f8}, {0xe0, 0x0dcf},
	{0xe1, 0x3f3e}, {0xe2, 0x9212}, {0xe3, 0x0098}, {0xe0, 0x0dcf},
	{0xe1, 0x3f3f}, {0xe2, 0x8307}, {0xe3, 0x00fa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f40}, {0xe2, 0x9301}, {0xe3, 0x00fa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f41}, {0xe2, 0x8212}, {0xe3, 0x00aa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f42}, {0xe2, 0x93ff}, {0xe3, 0x00ea}, {0xe0, 0x0dcf},
	{0xe1, 0x3f43}, {0xe2, 0x83ff}, {0xe3, 0x00ea}, {0xe0, 0x0dcf},
	{0xe1, 0x3f44}, {0xe2, 0x278a}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f45}, {0xe2, 0x1bf4}, {0xe3, 0x0031}, {0xe0, 0x0dcf},
	{0xe1, 0x3f46}, {0xe2, 0x8212}, {0xe3, 0x0098}, {0xe0, 0x0dcf},
	{0xe1, 0x3f47}, {0xe2, 0x9301}, {0xe3, 0x00f8}, {0xe0, 0x0dcf},
	{0xe1, 0x3f48}, {0xe2, 0x8117}, {0xe3, 0x00e5}, {0xe0, 0x0dcf},
	{0xe1, 0x3f49}, {0xe2, 0x3400}, {0xe3, 0x004e}, {0xe0, 0x0dcf},
	{0xe1, 0x3f4a}, {0xe2, 0x1a0c}, {0xe3, 0x00ef}, {0xe0, 0x0dcf},
	{0xe1, 0x3f4b}, {0xe2, 0x8301}, {0xe3, 0x00f8}, {0xe0, 0x0dcf},
	{0xe1, 0x3f4c}, {0xe2, 0x9212}, {0xe3, 0x0098}, {0xe0, 0x0dcf},
	{0xe1, 0x3f4d}, {0xe2, 0x8307}, {0xe3, 0x00fa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f4e}, {0xe2, 0x9301}, {0xe3, 0x00fa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f4f}, {0xe2, 0x8212}, {0xe3, 0x00aa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f50}, {0xe2, 0x93ff}, {0xe3, 0x00ea}, {0xe0, 0x0dcf},
	{0xe1, 0x3f51}, {0xe2, 0x83ff}, {0xe3, 0x00ea}, {0xe0, 0x0dcf},
	{0xe1, 0x3f52}, {0xe2, 0x278a}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f53}, {0xe2, 0x1bf5}, {0xe3, 0x0011}, {0xe0, 0x0dcf},
	{0xe1, 0x3f54}, {0xe2, 0x8212}, {0xe3, 0x0098}, {0xe0, 0x0dcf},
	{0xe1, 0x3f55}, {0xe2, 0x9301}, {0xe3, 0x00f8}, {0xe0, 0x0dcf},
	{0xe1, 0x3f56}, {0xe2, 0x8117}, {0xe3, 0x00e5}, {0xe0, 0x0dcf},
	{0xe1, 0x3f57}, {0xe2, 0x3400}, {0xe3, 0x004e}, {0xe0, 0x0dcf},
	{0xe1, 0x3f58}, {0xe2, 0x1a13}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f59}, {0xe2, 0x8e77}, {0xe3, 0x00c5}, {0xe0, 0x0dcf},
	{0xe1, 0x3f5a}, {0xe2, 0x34b8}, {0xe3, 0x0001}, {0xe0, 0x0dcf},
	{0xe1, 0x3f5b}, {0xe2, 0x3960}, {0xe3, 0x0002}, {0xe0, 0x0dcf},
	{0xe1, 0x3f5c}, {0xe2, 0x17f6}, {0xe3, 0x000e}, {0xe0, 0x0dcf},
	{0xe1, 0x3f5d}, {0xe2, 0x6000}, {0xe3, 0x0016}, {0xe0, 0x0dcf},
	{0xe1, 0x3f5e}, {0xe2, 0x7000}, {0xe3, 0x005a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f5f}, {0xe2, 0x6800}, {0xe3, 0x0055}, {0xe0, 0x0dcf},
	{0xe1, 0x3f60}, {0xe2, 0x7800}, {0xe3, 0x0019}, {0xe0, 0x0dcf},
	{0xe1, 0x3f61}, {0xe2, 0x1859}, {0xe3, 0x00bf}, {0xe0, 0x0dcf},
	{0xe1, 0x3f62}, {0xe2, 0x8230}, {0xe3, 0x0010}, {0xe0, 0x0dcf},
	{0xe1, 0x3f63}, {0xe2, 0x26e0}, {0xe3, 0x00df}, {0xe0, 0x0dcf},
	{0xe1, 0x3f64}, {0xe2, 0x1bf6}, {0xe3, 0x0072}, {0xe0, 0x0dcf},
	{0xe1, 0x3f65}, {0xe2, 0x3c00}, {0xe3, 0x0015}, {0xe0, 0x0dcf},
	{0xe1, 0x3f66}, {0xe2, 0x194f}, {0xe3, 0x00df}, {0xe0, 0x0dcf},
	{0xe1, 0x3f67}, {0xe2, 0x0c20}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f68}, {0xe2, 0x8240}, {0xe3, 0x0003}, {0xe0, 0x0dcf},
	{0xe1, 0x3f69}, {0xe2, 0x8324}, {0xe3, 0x0007}, {0xe0, 0x0dcf},
	{0xe1, 0x3f6a}, {0xe2, 0x2029}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f6b}, {0xe2, 0x9240}, {0xe3, 0x000c}, {0xe0, 0x0dcf},
	{0xe1, 0x3f6c}, {0xe2, 0x824c}, {0xe3, 0x0003}, {0xe0, 0x0dcf},
	{0xe1, 0x3f6d}, {0xe2, 0x2029}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f6e}, {0xe2, 0x924c}, {0xe3, 0x000c}, {0xe0, 0x0dcf},
	{0xe1, 0x3f6f}, {0xe2, 0x0c30}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f70}, {0xe2, 0x1950}, {0xe3, 0x002f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f71}, {0xe2, 0x962c}, {0xe3, 0x0076}, {0xe0, 0x0dcf},
	{0xe1, 0x3f72}, {0xe2, 0x962c}, {0xe3, 0x0086}, {0xe0, 0x0dcf},
	{0xe1, 0x3f73}, {0xe2, 0x4001}, {0xe3, 0x009a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f74}, {0xe2, 0x922c}, {0xe3, 0x009a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f75}, {0xe2, 0x3521}, {0xe3, 0x0091}, {0xe0, 0x0dcf},
	{0xe1, 0x3f76}, {0xe2, 0x3521}, {0xe3, 0x0062}, {0xe0, 0x0dcf},
	{0xe1, 0x3f77}, {0xe2, 0x3521}, {0xe3, 0x00c0}, {0xe0, 0x0dcf},
	{0xe1, 0x3f78}, {0xe2, 0x3c00}, {0xe3, 0x00c5}, {0xe0, 0x0dcf},
	{0xe1, 0x3f79}, {0xe2, 0x0c0c}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f7a}, {0xe2, 0x17f8}, {0xe3, 0x00ee}, {0xe0, 0x0dcf},
	{0xe1, 0x3f7b}, {0xe2, 0x6000}, {0xe3, 0x00a5}, {0xe0, 0x0dcf},
	{0xe1, 0x3f7c}, {0xe2, 0x22fa}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f7d}, {0xe2, 0x6000}, {0xe3, 0x0049}, {0xe0, 0x0dcf},
	{0xe1, 0x3f7e}, {0xe2, 0x66e2}, {0xe3, 0x0051}, {0xe0, 0x0dcf},
	{0xe1, 0x3f7f}, {0xe2, 0x1bf8}, {0xe3, 0x00c3}, {0xe0, 0x0dcf},
	{0xe1, 0x3f80}, {0xe2, 0x26ea}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f81}, {0xe2, 0x1bf8}, {0xe3, 0x00c3}, {0xe0, 0x0dcf},
	{0xe1, 0x3f82}, {0xe2, 0x822c}, {0xe3, 0x008a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f83}, {0xe2, 0x2262}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f84}, {0xe2, 0x822c}, {0xe3, 0x0094}, {0xe0, 0x0dcf},
	{0xe1, 0x3f85}, {0xe2, 0x26e2}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f86}, {0xe2, 0x1bf8}, {0xe3, 0x00a0}, {0xe0, 0x0dcf},
	{0xe1, 0x3f87}, {0xe2, 0x822c}, {0xe3, 0x007a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f88}, {0xe2, 0x2262}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f89}, {0xe2, 0x922c}, {0xe3, 0x007a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f8a}, {0xe2, 0x822c}, {0xe3, 0x009a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f8b}, {0xe2, 0x922c}, {0xe3, 0x008a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f8c}, {0xe2, 0x822c}, {0xe3, 0x009a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f8d}, {0xe2, 0x2262}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f8e}, {0xe2, 0x922c}, {0xe3, 0x009a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f8f}, {0xe2, 0x0c08}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f90}, {0xe2, 0x8230}, {0xe3, 0x0030}, {0xe0, 0x0dcf},
	{0xe1, 0x3f91}, {0xe2, 0x2398}, {0xe3, 0x005f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f92}, {0xe2, 0x1bfa}, {0xe3, 0x0020}, {0xe0, 0x0dcf},
	{0xe1, 0x3f93}, {0xe2, 0x822c}, {0xe3, 0x007a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f94}, {0xe2, 0x822c}, {0xe3, 0x00c4}, {0xe0, 0x0dcf},
	{0xe1, 0x3f95}, {0xe2, 0x26e2}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f96}, {0xe2, 0x1bf9}, {0xe3, 0x00e5}, {0xe0, 0x0dcf},
	{0xe1, 0x3f97}, {0xe2, 0x822c}, {0xe3, 0x00aa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f98}, {0xe2, 0x22e2}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f99}, {0xe2, 0x922c}, {0xe3, 0x00aa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f9a}, {0xe2, 0x1bfa}, {0xe3, 0x0022}, {0xe0, 0x0dcf},
	{0xe1, 0x3f9b}, {0xe2, 0x962c}, {0xe3, 0x00a6}, {0xe0, 0x0dcf},
	{0xe1, 0x3f9c}, {0xe2, 0x962c}, {0xe3, 0x00b6}, {0xe0, 0x0dcf},
	{0xe1, 0x3f9d}, {0xe2, 0x1bfa}, {0xe3, 0x002f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f9e}, {0xe2, 0x4100}, {0xe3, 0x0014}, {0xe0, 0x0dcf},
	{0xe1, 0x3f9f}, {0xe2, 0x922c}, {0xe3, 0x00b4}, {0xe0, 0x0dcf},
	{0xe1, 0x3fa0}, {0xe2, 0x4001}, {0xe3, 0x0044}, {0xe0, 0x0dcf},
	{0xe1, 0x3fa1}, {0xe2, 0x922c}, {0xe3, 0x00a4}, {0xe0, 0x0dcf},
	{0xe1, 0x3fa2}, {0xe2, 0x3c00}, {0xe3, 0x0075}, {0xe0, 0x0dcf},
	{0xe1, 0x3fa3}, {0xe2, 0x193c}, {0xe3, 0x00af}, {0xe0, 0x0dcf},
	{0xe1, 0x3fa4}, {0xe2, 0x8230}, {0xe3, 0x0030}, {0xe0, 0x0dcf},
	{0xe1, 0x3fa5}, {0xe2, 0x2398}, {0xe3, 0x005f}, {0xe0, 0x0dcf},
	{0xe1, 0x3fa6}, {0xe2, 0x1bfb}, {0xe3, 0x0050}, {0xe0, 0x0dcf},
	{0xe1, 0x3fa7}, {0xe2, 0x822c}, {0xe3, 0x00ba}, {0xe0, 0x0dcf},
	{0xe1, 0x3fa8}, {0xe2, 0x267a}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3fa9}, {0xe2, 0x1bfb}, {0xe3, 0x0050}, {0xe0, 0x0dcf},
	{0xe1, 0x3faa}, {0xe2, 0x8230}, {0xe3, 0x001a}, {0xe0, 0x0dcf},
	{0xe1, 0x3fab}, {0xe2, 0x267a}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3fac}, {0xe2, 0x4001}, {0xe3, 0x006a}, {0xe0, 0x0dcf},
	{0xe1, 0x3fad}, {0xe2, 0x4001}, {0xe3, 0x00f1}, {0xe0, 0x0dcf},
	{0xe1, 0x3fae}, {0xe2, 0x2279}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3faf}, {0xe2, 0x0d04}, {0xe3, 0x007a}, {0xe0, 0x0dcf},
	{0xe1, 0x3fb0}, {0xe2, 0x3724}, {0xe3, 0x0001}, {0xe0, 0x0dcf},
	{0xe1, 0x3fb1}, {0xe2, 0x0900}, {0xe3, 0x0007}, {0xe0, 0x0dcf},
	{0xe1, 0x3fb2}, {0xe2, 0xa7ff}, {0xe3, 0x00f5}, {0xe0, 0x0dcf},
	{0xe1, 0x3fb3}, {0xe2, 0xa7ff}, {0xe3, 0x00f5}, {0xe0, 0x0dcf},
	{0xe1, 0x3fb4}, {0xe2, 0xa7ff}, {0xe3, 0x00f5}, {0xe0, 0x0dcf},
	{0xe1, 0x3fb5}, {0xe2, 0x3b24}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3fb6}, {0xe2, 0x194f}, {0xe3, 0x003f}, {0xe0, 0x0dcf},
	{0xe1, 0x3fb7}, {0xe2, 0x3c00}, {0xe3, 0x0025}, {0xe0, 0x0dcf},
	{0xe1, 0x3fb8}, {0xe2, 0x3916}, {0xe3, 0x0072}, {0xe0, 0x0dcf},
	{0xe1, 0x3fb9}, {0xe2, 0x3501}, {0xe3, 0x0051}, {0xe0, 0x0dcf},
	{0xe1, 0x3fba}, {0xe2, 0x1dbe}, {0xe3, 0x008f}, {0xe0, 0x0dcf},
	{0xe1, 0x3fbb}, {0xe2, 0x8e2e}, {0xe3, 0x00b5}, {0xe0, 0x0dcf},
	{0xe1, 0x3fbc}, {0xe2, 0x3916}, {0xe3, 0x0012}, {0xe0, 0x0dcf},
	{0xe1, 0x3fbd}, {0xe2, 0x3500}, {0xe3, 0x0091}, {0xe0, 0x0dcf},
	{0xe1, 0x3fbe}, {0xe2, 0x1dbe}, {0xe3, 0x008f}, {0xe0, 0x0dcf},
	{0xe1, 0x3fbf}, {0xe2, 0x822e}, {0xe3, 0x00a0}, {0xe0, 0x0dcf},
	{0xe1, 0x3fc0}, {0xe2, 0x2780}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3fc1}, {0xe2, 0x1bfc}, {0xe3, 0x0060}, {0xe0, 0x0dcf},
	{0xe1, 0x3fc2}, {0xe2, 0x3c00}, {0xe3, 0x0025}, {0xe0, 0x0dcf},
	{0xe1, 0x3fc3}, {0xe2, 0x3916}, {0xe3, 0x0012}, {0xe0, 0x0dcf},
	{0xe1, 0x3fc4}, {0xe2, 0x3501}, {0xe3, 0x00a1}, {0xe0, 0x0dcf},
	{0xe1, 0x3fc5}, {0xe2, 0x1dbe}, {0xe3, 0x008f}, {0xe0, 0x0dcf},
	{0xe1, 0x3fc6}, {0xe2, 0x810b}, {0xe3, 0x00f1}, {0xe0, 0x0dcf},
	{0xe1, 0x3fc7}, {0xe2, 0x1831}, {0xe3, 0x00df}, {0xe0, 0x0dcf},
	{0xe1, 0x0064}, {0xe2, 0x0000}, {0xe0, 0x68c5}, // warm reset
	{0xe1, 0x3fa0}, {0xe2, 0x9183}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb0}, {0xe2, 0x3f00}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa1}, {0xe2, 0x91b3}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb1}, {0xe2, 0x3f11}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa2}, {0xe2, 0x9216}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb2}, {0xe2, 0x3f1e}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa3}, {0xe2, 0xe09d}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb3}, {0xe2, 0x3f2b}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa4}, {0xe2, 0xe0cd}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb4}, {0xe2, 0x3f3d}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa5}, {0xe2, 0xe130}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb5}, {0xe2, 0x3f4b}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa6}, {0xe2, 0x859a}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb6}, {0xe2, 0x3f59}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa7}, {0xe2, 0x94fc}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb7}, {0xe2, 0x3f62}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa8}, {0xe2, 0x93c9}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb8}, {0xe2, 0x3f71}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa9}, {0xe2, 0x94f2}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb9}, {0xe2, 0x3fa4}, {0xe0, 0x3bcb},
	{0xe1, 0x22cc}, {0xe2, 0x0001}, {0xe0, 0x3bcb},
	{0xe1, 0x3faa}, {0xe2, 0x823a}, {0xe0, 0x3bcb},
	{0xe1, 0x3fba}, {0xe2, 0x023e}, {0xe0, 0x3bcb},
	{0xe1, 0x3fab}, {0xe2, 0x8351}, {0xe0, 0x3bcb},
	{0xe1, 0x3fbb}, {0xe2, 0x0355}, {0xe0, 0x3bcb},
	{0xe1, 0x3fac}, {0xe2, 0x838d}, {0xe0, 0x3bcb},
	{0xe1, 0x3fbc}, {0xe2, 0x0391}, {0xe0, 0x3bcb},
	{0xe1, 0x3fad}, {0xe2, 0x8342}, {0xe0, 0x3bcb},
	{0xe1, 0x3fbd}, {0xe2, 0x0346}, {0xe0, 0x3bcb},
	{0xe1, 0x3fae}, {0xe2, 0x8382}, {0xe0, 0x3bcb},
	{0xe1, 0x3fbe}, {0xe2, 0x0386}, {0xe0, 0x3bcb},
	{0xe1, 0x3faf}, {0xe2, 0x831c}, {0xe0, 0x3bcb},
	{0xe1, 0x3fbf}, {0xe2, 0x3fb7}, {0xe0, 0x3bcb},
	{0xe1, 0x0010}, {0xe2, 0x0001}, {0xe0, 0x6ac9}, // set to dsp1
	{0xe1, 0x0064}, {0xe2, 0x0000}, {0xe0, 0x68c5}, // warm reset
	{0xe1, 0x3f00}, {0xe2, 0x26e1}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f01}, {0xe2, 0x1924}, {0xe3, 0x009f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f02}, {0xe2, 0x82f5}, {0xe3, 0x0050}, {0xe0, 0x0dcf},
	{0xe1, 0x3f03}, {0xe2, 0x26e0}, {0xe3, 0x00df}, {0xe0, 0x0dcf},
	{0xe1, 0x3f04}, {0xe2, 0x1bf0}, {0xe3, 0x0072}, {0xe0, 0x0dcf},
	{0xe1, 0x3f05}, {0xe2, 0x3400}, {0xe3, 0x0008}, {0xe0, 0x0dcf},
	{0xe1, 0x3f06}, {0xe2, 0x198e}, {0xe3, 0x003f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f07}, {0xe2, 0x0c20}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f08}, {0xe2, 0x80f5}, {0xe3, 0x00b3}, {0xe0, 0x0dcf},
	{0xe1, 0x3f09}, {0xe2, 0x8149}, {0xe3, 0x00b7}, {0xe0, 0x0dcf},
	{0xe1, 0x3f0a}, {0xe2, 0x2029}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f0b}, {0xe2, 0x90f5}, {0xe3, 0x00bc}, {0xe0, 0x0dcf},
	{0xe1, 0x3f0c}, {0xe2, 0x8101}, {0xe3, 0x00b3}, {0xe0, 0x0dcf},
	{0xe1, 0x3f0d}, {0xe2, 0x2029}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f0e}, {0xe2, 0x9101}, {0xe3, 0x00bc}, {0xe0, 0x0dcf},
	{0xe1, 0x3f0f}, {0xe2, 0x0c30}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f10}, {0xe2, 0x198e}, {0xe3, 0x009f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f11}, {0xe2, 0x9433}, {0xe3, 0x0006}, {0xe0, 0x0dcf},
	{0xe1, 0x3f12}, {0xe2, 0x9433}, {0xe3, 0x0016}, {0xe0, 0x0dcf},
	{0xe1, 0x3f13}, {0xe2, 0x4001}, {0xe3, 0x009a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f14}, {0xe2, 0x9033}, {0xe3, 0x002a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f15}, {0xe2, 0x3527}, {0xe3, 0x0041}, {0xe0, 0x0dcf},
	{0xe1, 0x3f16}, {0xe2, 0x3527}, {0xe3, 0x0012}, {0xe0, 0x0dcf},
	{0xe1, 0x3f17}, {0xe2, 0x3527}, {0xe3, 0x0070}, {0xe0, 0x0dcf},
	{0xe1, 0x3f18}, {0xe2, 0x3c00}, {0xe3, 0x00c5}, {0xe0, 0x0dcf},
	{0xe1, 0x3f19}, {0xe2, 0x0c0c}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f1a}, {0xe2, 0x17f2}, {0xe3, 0x00ee}, {0xe0, 0x0dcf},
	{0xe1, 0x3f1b}, {0xe2, 0x6000}, {0xe3, 0x00a5}, {0xe0, 0x0dcf},
	{0xe1, 0x3f1c}, {0xe2, 0x22fa}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f1d}, {0xe2, 0x6000}, {0xe3, 0x0049}, {0xe0, 0x0dcf},
	{0xe1, 0x3f1e}, {0xe2, 0x66e2}, {0xe3, 0x0051}, {0xe0, 0x0dcf},
	{0xe1, 0x3f1f}, {0xe2, 0x1bf2}, {0xe3, 0x00c3}, {0xe0, 0x0dcf},
	{0xe1, 0x3f20}, {0xe2, 0x26ea}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f21}, {0xe2, 0x1bf2}, {0xe3, 0x00c3}, {0xe0, 0x0dcf},
	{0xe1, 0x3f22}, {0xe2, 0x8033}, {0xe3, 0x001a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f23}, {0xe2, 0x2262}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f24}, {0xe2, 0x8033}, {0xe3, 0x0024}, {0xe0, 0x0dcf},
	{0xe1, 0x3f25}, {0xe2, 0x26e2}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f26}, {0xe2, 0x1bf2}, {0xe3, 0x00a0}, {0xe0, 0x0dcf},
	{0xe1, 0x3f27}, {0xe2, 0x8033}, {0xe3, 0x000a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f28}, {0xe2, 0x2262}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f29}, {0xe2, 0x9033}, {0xe3, 0x000a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f2a}, {0xe2, 0x8033}, {0xe3, 0x002a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f2b}, {0xe2, 0x9033}, {0xe3, 0x001a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f2c}, {0xe2, 0x8033}, {0xe3, 0x002a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f2d}, {0xe2, 0x2262}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f2e}, {0xe2, 0x9033}, {0xe3, 0x002a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f2f}, {0xe2, 0x0c08}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f30}, {0xe2, 0x82f5}, {0xe3, 0x0060}, {0xe0, 0x0dcf},
	{0xe1, 0x3f31}, {0xe2, 0x2398}, {0xe3, 0x005f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f32}, {0xe2, 0x1bf4}, {0xe3, 0x0020}, {0xe0, 0x0dcf},
	{0xe1, 0x3f33}, {0xe2, 0x8033}, {0xe3, 0x000a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f34}, {0xe2, 0x8033}, {0xe3, 0x0054}, {0xe0, 0x0dcf},
	{0xe1, 0x3f35}, {0xe2, 0x26e2}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f36}, {0xe2, 0x1bf3}, {0xe3, 0x00e5}, {0xe0, 0x0dcf},
	{0xe1, 0x3f37}, {0xe2, 0x8033}, {0xe3, 0x003a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f38}, {0xe2, 0x22e2}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f39}, {0xe2, 0x9033}, {0xe3, 0x003a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f3a}, {0xe2, 0x1bf4}, {0xe3, 0x0022}, {0xe0, 0x0dcf},
	{0xe1, 0x3f3b}, {0xe2, 0x9433}, {0xe3, 0x0036}, {0xe0, 0x0dcf},
	{0xe1, 0x3f3c}, {0xe2, 0x9433}, {0xe3, 0x0046}, {0xe0, 0x0dcf},
	{0xe1, 0x3f3d}, {0xe2, 0x1bf4}, {0xe3, 0x002f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f3e}, {0xe2, 0x4100}, {0xe3, 0x0014}, {0xe0, 0x0dcf},
	{0xe1, 0x3f3f}, {0xe2, 0x9033}, {0xe3, 0x0044}, {0xe0, 0x0dcf},
	{0xe1, 0x3f40}, {0xe2, 0x4001}, {0xe3, 0x0044}, {0xe0, 0x0dcf},
	{0xe1, 0x3f41}, {0xe2, 0x9033}, {0xe3, 0x0034}, {0xe0, 0x0dcf},
	{0xe1, 0x3f42}, {0xe2, 0x3c00}, {0xe3, 0x0075}, {0xe0, 0x0dcf},
	{0xe1, 0x3f43}, {0xe2, 0x192f}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f44}, {0xe2, 0x82f5}, {0xe3, 0x0060}, {0xe0, 0x0dcf},
	{0xe1, 0x3f45}, {0xe2, 0x2398}, {0xe3, 0x005f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f46}, {0xe2, 0x1bf5}, {0xe3, 0x0050}, {0xe0, 0x0dcf},
	{0xe1, 0x3f47}, {0xe2, 0x8033}, {0xe3, 0x004a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f48}, {0xe2, 0x267a}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f49}, {0xe2, 0x1bf5}, {0xe3, 0x0050}, {0xe0, 0x0dcf},
	{0xe1, 0x3f4a}, {0xe2, 0x82f5}, {0xe3, 0x005a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f4b}, {0xe2, 0x267a}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f4c}, {0xe2, 0x4001}, {0xe3, 0x006a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f4d}, {0xe2, 0x4001}, {0xe3, 0x00f1}, {0xe0, 0x0dcf},
	{0xe1, 0x3f4e}, {0xe2, 0x2279}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f4f}, {0xe2, 0x0d04}, {0xe3, 0x007a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f50}, {0xe2, 0x3549}, {0xe3, 0x00b1}, {0xe0, 0x0dcf},
	{0xe1, 0x3f51}, {0xe2, 0x0900}, {0xe3, 0x0007}, {0xe0, 0x0dcf},
	{0xe1, 0x3f52}, {0xe2, 0xa7ff}, {0xe3, 0x00f5}, {0xe0, 0x0dcf},
	{0xe1, 0x3f53}, {0xe2, 0xa7ff}, {0xe3, 0x00f5}, {0xe0, 0x0dcf},
	{0xe1, 0x3f54}, {0xe2, 0xa7ff}, {0xe3, 0x00f5}, {0xe0, 0x0dcf},
	{0xe1, 0x3f55}, {0xe2, 0x3949}, {0xe3, 0x00b0}, {0xe0, 0x0dcf},
	{0xe1, 0x3f56}, {0xe2, 0x1984}, {0xe3, 0x003f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f57}, {0xe2, 0x82b6}, {0xe3, 0x0061}, {0xe0, 0x0dcf},
	{0xe1, 0x3f58}, {0xe2, 0x17f8}, {0xe3, 0x006e}, {0xe0, 0x0dcf},
	{0xe1, 0x3f59}, {0xe2, 0x8291}, {0xe3, 0x006a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f5a}, {0xe2, 0x602a}, {0xe3, 0x0065}, {0xe0, 0x0dcf},
	{0xe1, 0x3f5b}, {0xe2, 0x2084}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f5c}, {0xe2, 0x0d00}, {0xe3, 0x00fc}, {0xe0, 0x0dcf},
	{0xe1, 0x3f5d}, {0xe2, 0x0d00}, {0xe3, 0x00eb}, {0xe0, 0x0dcf},
	{0xe1, 0x3f5e}, {0xe2, 0x2058}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f5f}, {0xe2, 0x1067}, {0xe3, 0x00be}, {0xe0, 0x0dcf},
	{0xe1, 0x3f60}, {0xe2, 0x1073}, {0xe3, 0x0087}, {0xe0, 0x0dcf},
	{0xe1, 0x3f61}, {0xe2, 0x1047}, {0xe3, 0x00a9}, {0xe0, 0x0dcf},
	{0xe1, 0x3f62}, {0xe2, 0x0e5b}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f63}, {0xe2, 0x2262}, {0xe3, 0x009f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f64}, {0xe2, 0x902f}, {0xe3, 0x009f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f65}, {0xe2, 0x902f}, {0xe3, 0x00aa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f66}, {0xe2, 0x1c95}, {0xe3, 0x00cf}, {0xe0, 0x0dcf},
	{0xe1, 0x3f67}, {0xe2, 0x1c50}, {0xe3, 0x00cf}, {0xe0, 0x0dcf},
	{0xe1, 0x3f68}, {0xe2, 0x0f22}, {0xe3, 0x00ff}, {0xe0, 0x0dcf},
	{0xe1, 0x3f69}, {0xe2, 0x802f}, {0xe3, 0x009a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f6a}, {0xe2, 0x0d00}, {0xe3, 0x005f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f6b}, {0xe2, 0x4000}, {0xe3, 0x0004}, {0xe0, 0x0dcf},
	{0xe1, 0x3f6c}, {0xe2, 0x060a}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f6d}, {0xe2, 0x0712}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f6e}, {0xe2, 0x0712}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f6f}, {0xe2, 0x0712}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f70}, {0xe2, 0x0712}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f71}, {0xe2, 0x0712}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f72}, {0xe2, 0x0712}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f73}, {0xe2, 0x0712}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f74}, {0xe2, 0x0712}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f75}, {0xe2, 0x0712}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f76}, {0xe2, 0x0712}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f77}, {0xe2, 0x0712}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f78}, {0xe2, 0x0712}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f79}, {0xe2, 0x0712}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f7a}, {0xe2, 0x0712}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f7b}, {0xe2, 0x0712}, {0xe3, 0x0000}, {0xe0, 0x0dcf},
	{0xe1, 0x3f7c}, {0xe2, 0x802f}, {0xe3, 0x00aa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f7d}, {0xe2, 0x2b3a}, {0xe3, 0x00b4}, {0xe0, 0x0dcf},
	{0xe1, 0x3f7e}, {0xe2, 0x2262}, {0xe3, 0x001f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f7f}, {0xe2, 0x0d00}, {0xe3, 0x009a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f80}, {0xe2, 0x1023}, {0xe3, 0x0061}, {0xe0, 0x0dcf},
	{0xe1, 0x3f81}, {0xe2, 0x2027}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f82}, {0xe2, 0x428b}, {0xe3, 0x00e6}, {0xe0, 0x0dcf},
	{0xe1, 0x3f83}, {0xe2, 0x2024}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f84}, {0xe2, 0x82b7}, {0xe3, 0x0084}, {0xe0, 0x0dcf},
	{0xe1, 0x3f85}, {0xe2, 0x2b24}, {0xe3, 0x0078}, {0xe0, 0x0dcf},
	{0xe1, 0x3f86}, {0xe2, 0x92b7}, {0xe3, 0x008a}, {0xe0, 0x0dcf},
	{0xe1, 0x3f87}, {0xe2, 0x1a20}, {0xe3, 0x007f}, {0xe0, 0x0dcf},
	{0xe1, 0x3f88}, {0xe2, 0x47ff}, {0xe3, 0x00fa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f89}, {0xe2, 0x92b5}, {0xe3, 0x00fa}, {0xe0, 0x0dcf},
	{0xe1, 0x3f8a}, {0xe2, 0x356d}, {0xe3, 0x00b1}, {0xe0, 0x0dcf},
	{0xe1, 0x3f8b}, {0xe2, 0x19e4}, {0xe3, 0x000f}, {0xe0, 0x0dcf},
	{0xe1, 0x0064}, {0xe2, 0x0000}, {0xe0, 0x68c5}, // warm reset
	{0xe1, 0x3fa0}, {0xe2, 0x9248}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb0}, {0xe2, 0x3f00}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa1}, {0xe2, 0x98e2}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb1}, {0xe2, 0x3f02}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa2}, {0xe2, 0x92f0}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb2}, {0xe2, 0x3f11}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa3}, {0xe2, 0x9842}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb3}, {0xe2, 0x3f44}, {0xe0, 0x3bcb},
	{0xe1, 0x0335}, {0xe2, 0x0001}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa4}, {0xe2, 0xa1d6}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb4}, {0xe2, 0x3f57}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa5}, {0xe2, 0x9e3f}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb5}, {0xe2, 0x3f88}, {0xe0, 0x3bcb},
	{0xe1, 0x0010}, {0xe2, 0x0000}, {0xe0, 0x6ac9},	// set to dsp0
};
#define RT5671_DSP_INIT_PATCH_NUM \
	(sizeof(rt5671_dsp_init_patch_code) / sizeof(rt5671_dsp_init_patch_code[0]))

static unsigned short rt5671_dsp_reset_patch_code[][2] = { // patch for switching mode, which is auto generated from fm36600c_signoff0902.patch
	{0xe1, 0x0010}, {0xe2, 0x0000}, {0xe0, 0x6ac9}, // set to dsp0
	{0xe1, 0x0064}, {0xe2, 0x0000}, {0xe0, 0x68c5}, // warm reset
	{0xe1, 0x3fa0}, {0xe2, 0x9183}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb0}, {0xe2, 0x3f00}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa1}, {0xe2, 0x91b3}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb1}, {0xe2, 0x3f11}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa2}, {0xe2, 0x9216}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb2}, {0xe2, 0x3f1e}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa3}, {0xe2, 0xe09d}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb3}, {0xe2, 0x3f2b}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa4}, {0xe2, 0xe0cd}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb4}, {0xe2, 0x3f3d}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa5}, {0xe2, 0xe130}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb5}, {0xe2, 0x3f4b}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa6}, {0xe2, 0x859a}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb6}, {0xe2, 0x3f59}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa7}, {0xe2, 0x94fc}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb7}, {0xe2, 0x3f62}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa8}, {0xe2, 0x93c9}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb8}, {0xe2, 0x3f71}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa9}, {0xe2, 0x94f2}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb9}, {0xe2, 0x3fa4}, {0xe0, 0x3bcb},
	{0xe1, 0x22cc}, {0xe2, 0x0001}, {0xe0, 0x3bcb},
	{0xe1, 0x3faa}, {0xe2, 0x823a}, {0xe0, 0x3bcb},
	{0xe1, 0x3fba}, {0xe2, 0x023e}, {0xe0, 0x3bcb},
	{0xe1, 0x3fab}, {0xe2, 0x8351}, {0xe0, 0x3bcb},
	{0xe1, 0x3fbb}, {0xe2, 0x0355}, {0xe0, 0x3bcb},
	{0xe1, 0x3fac}, {0xe2, 0x838d}, {0xe0, 0x3bcb},
	{0xe1, 0x3fbc}, {0xe2, 0x0391}, {0xe0, 0x3bcb},
	{0xe1, 0x3fad}, {0xe2, 0x8342}, {0xe0, 0x3bcb},
	{0xe1, 0x3fbd}, {0xe2, 0x0346}, {0xe0, 0x3bcb},
	{0xe1, 0x3fae}, {0xe2, 0x8382}, {0xe0, 0x3bcb},
	{0xe1, 0x3fbe}, {0xe2, 0x0386}, {0xe0, 0x3bcb},
	{0xe1, 0x3faf}, {0xe2, 0x831c}, {0xe0, 0x3bcb},
	{0xe1, 0x3fbf}, {0xe2, 0x3fb7}, {0xe0, 0x3bcb},

	{0xe1, 0x0010}, {0xe2, 0x0001}, {0xe0, 0x6ac9}, // set to dsp1 
	{0xe1, 0x0064}, {0xe2, 0x0000}, {0xe0, 0x68c5}, // warm reset
	{0xe1, 0x3fa0}, {0xe2, 0x9248}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb0}, {0xe2, 0x3f00}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa1}, {0xe2, 0x98e2}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb1}, {0xe2, 0x3f02}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa2}, {0xe2, 0x92f0}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb2}, {0xe2, 0x3f11}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa3}, {0xe2, 0x9842}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb3}, {0xe2, 0x3f44}, {0xe0, 0x3bcb},
	{0xe1, 0x0335}, {0xe2, 0x0001}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa4}, {0xe2, 0xa1d6}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb4}, {0xe2, 0x3f57}, {0xe0, 0x3bcb},
	{0xe1, 0x3fa5}, {0xe2, 0x9e3f}, {0xe0, 0x3bcb},
	{0xe1, 0x3fb5}, {0xe2, 0x3f88}, {0xe0, 0x3bcb},
	{0xe1, 0x0010}, {0xe2, 0x0000}, {0xe0, 0x6ac9},	// set to dsp0
};
#define RT5671_DSP_RESET_PATCH_NUM \
	(sizeof(rt5671_dsp_reset_patch_code) / sizeof(rt5671_dsp_reset_patch_code[0]))

/* DSP init */
static unsigned short rt5671_dsp_init[][2] = {
	{0x2260, 0x30d9}, /*{0x2261, 0x30d9},*/ {0x2289, 0x7fff}, {0x2290, 0x7fff},
	{0x2288, 0x0002}, {0x22b2, 0x0002}, {0x2295, 0x0001}, {0x22b3, 0x0001},
	/*{0x22d7, 0x0008}, {0x22d8, 0x0009},*/ {0x22d9, 0x0000}, {0x22da, 0x0001},
	{0x22fd, 0x009e}, {0x22c1, 0x1006}, {0x22c2, 0x1006}, {0x22c3, 0x1007},
	{0x22c4, 0x1007}, {0x229d, 0x0000}
};
#define RT5671_DSP_INIT_NUM \
	(sizeof(rt5671_dsp_init) / sizeof(rt5671_dsp_init[0]))

/* Data Source */
#define RT5671_DSP_TDM_SRC_PAR_NUM 5

static unsigned short rt5671_dsp_data_src[][2] = {
	/*For Stereo1 ADC mixer*/
	{0x2261, 0x30d9}, {0x2282, 0x0008}, {0x2283, 0x0009},
	{0x22d7, 0x0008}, {0x22d8, 0x0009},
	/*For Mono ADC mixer*/
	{0x2261, 0x30df}, {0x2282, 0x000a}, {0x2283, 0x000b},
	{0x22d7, 0x000a}, {0x22d8, 0x000b},
	/*For Stereo2 ADC mixer*/
	{0x2261, 0x30df}, {0x2282, 0x000c}, {0x2283, 0x000d},
	{0x22d7, 0x000c}, {0x22d8, 0x000d},
	/*For IF2 DAC*/
	{0x2261, 0x30df}, {0x2282, 0x000e}, {0x2283, 0x000f},
	{0x22d7, 0x000e}, {0x22d8, 0x000f},
};

static unsigned short rt5671_dsp_rate_par[] = {
	0x226c, 0x226d, 0x226e, 0x22f2, 0x2301, 0x2306,
};
#define RT5671_DSP_RATE_NUM \
	(sizeof(rt5671_dsp_rate_par) / sizeof(rt5671_dsp_rate_par[0]))

/* MCLK rate */
static unsigned short rt5671_dsp_4096000[][2] = {
	{0x226c, 0x000c}, {0x226d, 0x000c}, {0x226e, 0x0022},
};
#define RT5671_DSP_4096000_NUM \
	(sizeof(rt5671_dsp_4096000) / sizeof(rt5671_dsp_4096000[0]))

static unsigned short rt5671_dsp_12288000[][2] = {
	{0x226c, 0x000c}, {0x226d, 0x000c}, {0x226e, 0x0026},
};
#define RT5671_DSP_12288000_NUM \
	(sizeof(rt5671_dsp_12288000) / sizeof(rt5671_dsp_12288000[0]))

static unsigned short rt5671_dsp_11289600[][2] = {
	{0x226c, 0x0031}, {0x226d, 0x0050}, {0x226e, 0x0009},
};
#define RT5671_DSP_11289600_NUM \
	(sizeof(rt5671_dsp_11289600) / sizeof(rt5671_dsp_11289600[0]))

static unsigned short rt5671_dsp_24576000[][2] = {
	{0x226c, 0x000c}, {0x226d, 0x000c}, {0x226e, 0x002c},
};
#define RT5671_DSP_24576000_NUM \
	(sizeof(rt5671_dsp_24576000) / sizeof(rt5671_dsp_24576000[0]))

/* sample rate */
static unsigned short rt5671_dsp_48_441[][2] = {
	{0x22f2, 0x005c}, {0x2301, 0x0016}
};
#define RT5671_DSP_48_441_NUM \
	(sizeof(rt5671_dsp_48_441) / sizeof(rt5671_dsp_48_441[0]))

static unsigned short rt5671_dsp_24[][2] = {
	{0x22f2, 0x0058}, {0x2301, 0x0004}
};
#define RT5671_DSP_24_NUM (sizeof(rt5671_dsp_24) / sizeof(rt5671_dsp_24[0]))

static unsigned short rt5671_dsp_16[][2] = {
	{0x22f2, 0x004c}, {0x2301, 0x0002}
};
#define RT5671_DSP_16_NUM (sizeof(rt5671_dsp_16) / sizeof(rt5671_dsp_16[0]))

static unsigned short rt5671_dsp_8[][2] = {
	{0x22f2, 0x004c}, {0x2301, 0x0000}
};
#define RT5671_DSP_8_NUM (sizeof(rt5671_dsp_8) / sizeof(rt5671_dsp_8[0]))

/* DSP mode */
static int rt5671_dsp_handset_size = 0;
static char *rt5671_dsp_handset_buf;
static char *rt5671_dsp_handset_file = "/etc/firmware/rt5671_dsp_handset.bin";
static int rt5671_dsp_handset_1mic_size = 0;
static char *rt5671_dsp_handset_1mic_buf;
static char *rt5671_dsp_handset_1mic_file = "/etc/firmware/rt5671_dsp_handset_1mic.bin";
static int rt5671_dsp_handset_2mic_size = 0;
static char *rt5671_dsp_handset_2mic_buf;
static char *rt5671_dsp_handset_2mic_file = "/etc/firmware/rt5671_dsp_handset_2mic.bin";
static unsigned short rt5671_dsp_handset[][2] = {
	{0x22f8, 0x8003}, {0x232f, 0x00d0}, {0x2355, 0x2666}, {0x2356, 0x2666},
	{0x2357, 0x2666}, {0x2358, 0x6666}, {0x2359, 0x6666}, {0x235a, 0x6666},
	{0x235b, 0x7fff}, {0x235c, 0x7fff}, {0x235d, 0x7fff}, {0x235e, 0x7fff},
	{0x235f, 0x7fff}, {0x2360, 0x7fff}, {0x2361, 0x7fff}, {0x2362, 0x1000},
	{0x2367, 0x0007}, {0x2368, 0x4000}, {0x2369, 0x0008}, {0x236a, 0x2000},
	{0x236b, 0x0009}, {0x236c, 0x003c}, {0x236d, 0x0000}, {0x236f, 0x2000},
	{0x2370, 0x0008}, {0x2371, 0x000a}, {0x2373, 0x0000}, {0x2374, 0x7fff},
	{0x2375, 0x7ff0}, {0x2376, 0x7990}, {0x2377, 0x7332}, {0x2379, 0x1000},
	{0x237a, 0x1000}, {0x2388, 0x7fff}, {0x2389, 0x6000}, {0x238a, 0x4000},
	{0x238b, 0x1000}, {0x238c, 0x1000}, {0x2398, 0x4668}, {0x23a1, 0x2000},
	{0x23a3, 0x4000}, {0x23ad, 0x2000}, {0x23ae, 0x2000}, {0x23af, 0x2000},
	{0x23b4, 0x2000}, {0x23b5, 0x2000}, {0x23b6, 0x2000}, {0x23bb, 0x6000},
	{0x2303, 0x0710}, {0x2304, 0x0332}, {0x230c, 0x0200}, {0x230d, 0x0080},
	{0x2310, 0x0010}, {0x22fb, 0x0000}
};
#define RT5671_DSP_HANDSET_NUM \
	(sizeof(rt5671_dsp_handset) / sizeof(rt5671_dsp_handset[0]))

static int rt5671_dsp_handsfree_size = 0;
static char *rt5671_dsp_handsfree_buf;
static char *rt5671_dsp_handsfree_file = "/etc/firmware/rt5671_dsp_handsfree.bin";
static int rt5671_dsp_handsfree_1mic_size = 0;
static char *rt5671_dsp_handsfree_1mic_buf;
static char *rt5671_dsp_handsfree_1mic_file = "/etc/firmware/rt5671_dsp_handsfree_1mic.bin";
static int rt5671_dsp_handsfree_2mic_size = 0;
static char *rt5671_dsp_handsfree_2mic_buf;
static char *rt5671_dsp_handsfree_2mic_file = "/etc/firmware/rt5671_dsp_handsfree_2mic.bin";
static unsigned short rt5671_dsp_handsfree[][2] = {
	{0x22f8, 0x8003}, {0x232f, 0x00d0}, {0x2355, 0x2666}, {0x2356, 0x2666},
	{0x2357, 0x2666}, {0x2358, 0x6666}, {0x2359, 0x6666}, {0x235a, 0x6666},
	{0x235b, 0x7fff}, {0x235c, 0x7fff}, {0x235d, 0x7fff}, {0x235e, 0x7fff},
	{0x235f, 0x7fff}, {0x2360, 0x7fff}, {0x2361, 0x7fff}, {0x2362, 0x1000},
	{0x2367, 0x0007}, {0x2368, 0x4000}, {0x2369, 0x0008}, {0x236a, 0x2000},
	{0x236b, 0x0009}, {0x236c, 0x003c}, {0x236d, 0x0000}, {0x236f, 0x2000},
	{0x2370, 0x0008}, {0x2371, 0x000a}, {0x2373, 0x0000}, {0x2374, 0x7fff},
	{0x2375, 0x7ff0}, {0x2376, 0x7990}, {0x2377, 0x7332}, {0x2379, 0x1000},
	{0x237a, 0x1000}, {0x2388, 0x7fff}, {0x2389, 0x6000}, {0x238a, 0x4000},
	{0x238b, 0x1000}, {0x238c, 0x1000}, {0x2398, 0x4668}, {0x23a1, 0x2000},
	{0x23a3, 0x4000}, {0x23ad, 0x2000}, {0x23ae, 0x2000}, {0x23af, 0x2000},
	{0x23b4, 0x2000}, {0x23b5, 0x2000}, {0x23b6, 0x2000}, {0x23bb, 0x6000},
	{0x2303, 0x0710}, {0x2304, 0x0332}, {0x230c, 0x0200}, {0x230d, 0x0080},
	{0x2310, 0x0010}, {0x22fb, 0x0000}
};
#define RT5671_DSP_HANDSFREE_NUM \
	(sizeof(rt5671_dsp_handsfree) / sizeof(rt5671_dsp_handsfree[0]))

static int rt5671_dsp_headphone_size = 0;
static char *rt5671_dsp_headphone_buf;
static char *rt5671_dsp_headphone_file = "/etc/firmware/rt5671_dsp_headphone.bin";
static int rt5671_dsp_headphone_1mic_size = 0;
static char *rt5671_dsp_headphone_1mic_buf;
static char *rt5671_dsp_headphone_1mic_file = "/etc/firmware/rt5671_dsp_headphone_1mic.bin";
static int rt5671_dsp_headphone_2mic_size = 0;
static char *rt5671_dsp_headphone_2mic_buf;
static char *rt5671_dsp_headphone_2mic_file = "/etc/firmware/rt5671_dsp_headphone_2mic.bin";
static unsigned short rt5671_dsp_headphone[][2] = {
	{0x22f8, 0x8003}, {0x232f, 0x00d0}, {0x2355, 0x2666}, {0x2356, 0x2666},
	{0x2357, 0x2666}, {0x2358, 0x6666}, {0x2359, 0x6666}, {0x235a, 0x6666},
	{0x235b, 0x7fff}, {0x235c, 0x7fff}, {0x235d, 0x7fff}, {0x235e, 0x7fff},
	{0x235f, 0x7fff}, {0x2360, 0x7fff}, {0x2361, 0x7fff}, {0x2362, 0x1000},
	{0x2367, 0x0007}, {0x2368, 0x4000}, {0x2369, 0x0008}, {0x236a, 0x2000},
	{0x236b, 0x0009}, {0x236c, 0x003c}, {0x236d, 0x0000}, {0x236f, 0x2000},
	{0x2370, 0x0008}, {0x2371, 0x000a}, {0x2373, 0x0000}, {0x2374, 0x7fff},
	{0x2375, 0x7ff0}, {0x2376, 0x7990}, {0x2377, 0x7332}, {0x2379, 0x1000},
	{0x237a, 0x1000}, {0x2388, 0x7fff}, {0x2389, 0x6000}, {0x238a, 0x4000},
	{0x238b, 0x1000}, {0x238c, 0x1000}, {0x2398, 0x4668}, {0x23a1, 0x2000},
	{0x23a3, 0x4000}, {0x23ad, 0x2000}, {0x23ae, 0x2000}, {0x23af, 0x2000},
	{0x23b4, 0x2000}, {0x23b5, 0x2000}, {0x23b6, 0x2000}, {0x23bb, 0x6000},
	{0x2303, 0x0710}, {0x2304, 0x0332}, {0x230c, 0x0200}, {0x230d, 0x0080},
	{0x2310, 0x0010}, {0x22fb, 0x0000}
};
#define RT5671_DSP_HEADPHONE_NUM \
	(sizeof(rt5671_dsp_headphone) / sizeof(rt5671_dsp_headphone[0]))

static int rt5671_dsp_headset_size = 0;
static char *rt5671_dsp_headset_buf;
static char *rt5671_dsp_headset_file = "/etc/firmware/rt5671_dsp_headset.bin";
static int rt5671_dsp_headset_1mic_size = 0;
static char *rt5671_dsp_headset_1mic_buf;
static char *rt5671_dsp_headset_1mic_file = "/etc/firmware/rt5671_dsp_headset_1mic.bin";
static int rt5671_dsp_headset_2mic_size = 0;
static char *rt5671_dsp_headset_2mic_buf;
static char *rt5671_dsp_headset_2mic_file = "/etc/firmware/rt5671_dsp_headset_2mic.bin";
static unsigned short rt5671_dsp_headset[][2] = {
	{0x22f8, 0x8003}, {0x232f, 0x00d0}, {0x2355, 0x2666}, {0x2356, 0x2666},
	{0x2357, 0x2666}, {0x2358, 0x6666}, {0x2359, 0x6666}, {0x235a, 0x6666},
	{0x235b, 0x7fff}, {0x235c, 0x7fff}, {0x235d, 0x7fff}, {0x235e, 0x7fff},
	{0x235f, 0x7fff}, {0x2360, 0x7fff}, {0x2361, 0x7fff}, {0x2362, 0x1000},
	{0x2367, 0x0007}, {0x2368, 0x4000}, {0x2369, 0x0008}, {0x236a, 0x2000},
	{0x236b, 0x0009}, {0x236c, 0x003c}, {0x236d, 0x0000}, {0x236f, 0x2000},
	{0x2370, 0x0008}, {0x2371, 0x000a}, {0x2373, 0x0000}, {0x2374, 0x7fff},
	{0x2375, 0x7ff0}, {0x2376, 0x7990}, {0x2377, 0x7332}, {0x2379, 0x1000},
	{0x237a, 0x1000}, {0x2388, 0x7fff}, {0x2389, 0x6000}, {0x238a, 0x4000},
	{0x238b, 0x1000}, {0x238c, 0x1000}, {0x2398, 0x4668}, {0x23a1, 0x2000},
	{0x23a3, 0x4000}, {0x23ad, 0x2000}, {0x23ae, 0x2000}, {0x23af, 0x2000},
	{0x23b4, 0x2000}, {0x23b5, 0x2000}, {0x23b6, 0x2000}, {0x23bb, 0x6000},
	{0x2303, 0x0710}, {0x2304, 0x0332}, {0x230c, 0x0200}, {0x230d, 0x0080},
	{0x2310, 0x0010}, {0x22fb, 0x0000}
};
#define RT5671_DSP_HEADSET_NUM \
	(sizeof(rt5671_dsp_headset) / sizeof(rt5671_dsp_headset[0]))

static int rt5671_dsp_bluetooth_size = 0;
static char *rt5671_dsp_bluetooth_buf;
static char *rt5671_dsp_bluetooth_file = "/etc/firmware/rt5671_dsp_bluetooth.bin";
static int rt5671_dsp_bluetooth_1mic_size = 0;
static char *rt5671_dsp_bluetooth_1mic_buf;
static char *rt5671_dsp_bluetooth_1mic_file = "/etc/firmware/rt5671_dsp_bluetooth_1mic.bin";
static int rt5671_dsp_bluetooth_2mic_size = 0;
static char *rt5671_dsp_bluetooth_2mic_buf;
static char *rt5671_dsp_bluetooth_2mic_file = "/etc/firmware/rt5671_dsp_bluetooth_2mic.bin";
static unsigned short rt5671_dsp_bluetooth[][2] = {
	{0x22f8, 0x8003}, {0x232f, 0x00d0}, {0x2355, 0x2666}, {0x2356, 0x2666},
	{0x2357, 0x2666}, {0x2358, 0x6666}, {0x2359, 0x6666}, {0x235a, 0x6666},
	{0x235b, 0x7fff}, {0x235c, 0x7fff}, {0x235d, 0x7fff}, {0x235e, 0x7fff},
	{0x235f, 0x7fff}, {0x2360, 0x7fff}, {0x2361, 0x7fff}, {0x2362, 0x1000},
	{0x2367, 0x0007}, {0x2368, 0x4000}, {0x2369, 0x0008}, {0x236a, 0x2000},
	{0x236b, 0x0009}, {0x236c, 0x003c}, {0x236d, 0x0000}, {0x236f, 0x2000},
	{0x2370, 0x0008}, {0x2371, 0x000a}, {0x2373, 0x0000}, {0x2374, 0x7fff},
	{0x2375, 0x7ff0}, {0x2376, 0x7990}, {0x2377, 0x7332}, {0x2379, 0x1000},
	{0x237a, 0x1000}, {0x2388, 0x7fff}, {0x2389, 0x6000}, {0x238a, 0x4000},
	{0x238b, 0x1000}, {0x238c, 0x1000}, {0x2398, 0x4668}, {0x23a1, 0x2000},
	{0x23a3, 0x4000}, {0x23ad, 0x2000}, {0x23ae, 0x2000}, {0x23af, 0x2000},
	{0x23b4, 0x2000}, {0x23b5, 0x2000}, {0x23b6, 0x2000}, {0x23bb, 0x6000},
	{0x2303, 0x0710}, {0x2304, 0x0332}, {0x230c, 0x0200}, {0x230d, 0x0080},
	{0x2310, 0x0010}, {0x22fb, 0x0000}
};
#define RT5671_DSP_BLUETOOTH_NUM \
	(sizeof(rt5671_dsp_bluetooth) / sizeof(rt5671_dsp_bluetooth[0]))

static int rt5671_dsp_handset_nb_size = 0;
static char *rt5671_dsp_handset_nb_buf;
static char *rt5671_dsp_handset_nb_file = "/etc/firmware/rt5671_dsp_handset_nb.bin";
static int rt5671_dsp_handset_nb_1mic_size = 0;
static char *rt5671_dsp_handset_nb_1mic_buf;
static char *rt5671_dsp_handset_nb_1mic_file = "/etc/firmware/rt5671_dsp_handset_nb_1mic.bin";
static int rt5671_dsp_handset_nb_2mic_size = 0;
static char *rt5671_dsp_handset_nb_2mic_buf;
static char *rt5671_dsp_handset_nb_2mic_file = "/etc/firmware/rt5671_dsp_handset_nb_2mic.bin";
static unsigned short rt5671_dsp_handset_nb[][2] = {
	{0x22f8, 0x8003}, {0x232f, 0x00d0}, {0x2355, 0x2666}, {0x2356, 0x2666},
	{0x2357, 0x2666}, {0x2358, 0x6666}, {0x2359, 0x6666}, {0x235a, 0x6666},
	{0x235b, 0x7fff}, {0x235c, 0x7fff}, {0x235d, 0x7fff}, {0x235e, 0x7fff},
	{0x235f, 0x7fff}, {0x2360, 0x7fff}, {0x2361, 0x7fff}, {0x2362, 0x1000},
	{0x2367, 0x0007}, {0x2368, 0x4000}, {0x2369, 0x0008}, {0x236a, 0x2000},
	{0x236b, 0x0009}, {0x236c, 0x003c}, {0x236d, 0x0000}, {0x236f, 0x2000},
	{0x2370, 0x0008}, {0x2371, 0x000a}, {0x2373, 0x0000}, {0x2374, 0x7fff},
	{0x2375, 0x7ff0}, {0x2376, 0x7990}, {0x2377, 0x7332}, {0x2379, 0x1000},
	{0x237a, 0x1000}, {0x2388, 0x7fff}, {0x2389, 0x6000}, {0x238a, 0x4000},
	{0x238b, 0x1000}, {0x238c, 0x1000}, {0x2398, 0x4668}, {0x23a1, 0x2000},
	{0x23a3, 0x4000}, {0x23ad, 0x2000}, {0x23ae, 0x2000}, {0x23af, 0x2000},
	{0x23b4, 0x2000}, {0x23b5, 0x2000}, {0x23b6, 0x2000}, {0x23bb, 0x6000},
	{0x2303, 0x0710}, {0x2304, 0x0332}, {0x230c, 0x0200}, {0x230d, 0x0080},
	{0x2310, 0x0010}, {0x22fb, 0x0000}
};
#define RT5671_DSP_HANDSET_NB_NUM \
	(sizeof(rt5671_dsp_handset_nb) / sizeof(rt5671_dsp_handset_nb[0]))

static int rt5671_dsp_handsfree_nb_size = 0;
static char *rt5671_dsp_handsfree_nb_buf;
static char *rt5671_dsp_handsfree_nb_file = "/etc/firmware/rt5671_dsp_handsfree_nb.bin";
static int rt5671_dsp_handsfree_nb_1mic_size = 0;
static char *rt5671_dsp_handsfree_nb_1mic_buf;
static char *rt5671_dsp_handsfree_nb_1mic_file = "/etc/firmware/rt5671_dsp_handsfree_nb_1mic.bin";
static int rt5671_dsp_handsfree_nb_2mic_size = 0;
static char *rt5671_dsp_handsfree_nb_2mic_buf;
static char *rt5671_dsp_handsfree_nb_2mic_file = "/etc/firmware/rt5671_dsp_handsfree_nb_2mic.bin";
static unsigned short rt5671_dsp_handsfree_nb[][2] = {
	{0x22f8, 0x8003}, {0x232f, 0x00d0}, {0x2355, 0x2666}, {0x2356, 0x2666},
	{0x2357, 0x2666}, {0x2358, 0x6666}, {0x2359, 0x6666}, {0x235a, 0x6666},
	{0x235b, 0x7fff}, {0x235c, 0x7fff}, {0x235d, 0x7fff}, {0x235e, 0x7fff},
	{0x235f, 0x7fff}, {0x2360, 0x7fff}, {0x2361, 0x7fff}, {0x2362, 0x1000},
	{0x2367, 0x0007}, {0x2368, 0x4000}, {0x2369, 0x0008}, {0x236a, 0x2000},
	{0x236b, 0x0009}, {0x236c, 0x003c}, {0x236d, 0x0000}, {0x236f, 0x2000},
	{0x2370, 0x0008}, {0x2371, 0x000a}, {0x2373, 0x0000}, {0x2374, 0x7fff},
	{0x2375, 0x7ff0}, {0x2376, 0x7990}, {0x2377, 0x7332}, {0x2379, 0x1000},
	{0x237a, 0x1000}, {0x2388, 0x7fff}, {0x2389, 0x6000}, {0x238a, 0x4000},
	{0x238b, 0x1000}, {0x238c, 0x1000}, {0x2398, 0x4668}, {0x23a1, 0x2000},
	{0x23a3, 0x4000}, {0x23ad, 0x2000}, {0x23ae, 0x2000}, {0x23af, 0x2000},
	{0x23b4, 0x2000}, {0x23b5, 0x2000}, {0x23b6, 0x2000}, {0x23bb, 0x6000},
	{0x2303, 0x0710}, {0x2304, 0x0332}, {0x230c, 0x0200}, {0x230d, 0x0080},
	{0x2310, 0x0010}, {0x22fb, 0x0000}
};
#define RT5671_DSP_HANDSFREE_NB_NUM \
	(sizeof(rt5671_dsp_handsfree_nb) / sizeof(rt5671_dsp_handsfree_nb[0]))

static int rt5671_dsp_headphone_nb_size = 0;
static char *rt5671_dsp_headphone_nb_buf;
static char *rt5671_dsp_headphone_nb_file = "/etc/firmware/rt5671_dsp_headphone_nb.bin";
static int rt5671_dsp_headphone_nb_1mic_size = 0;
static char *rt5671_dsp_headphone_nb_1mic_buf;
static char *rt5671_dsp_headphone_nb_1mic_file = "/etc/firmware/rt5671_dsp_headphone_nb_1mic.bin";
static int rt5671_dsp_headphone_nb_2mic_size = 0;
static char *rt5671_dsp_headphone_nb_2mic_buf;
static char *rt5671_dsp_headphone_nb_2mic_file = "/etc/firmware/rt5671_dsp_headphone_nb_2mic.bin";
static unsigned short rt5671_dsp_headphone_nb[][2] = {
	{0x22f8, 0x8003}, {0x232f, 0x00d0}, {0x2355, 0x2666}, {0x2356, 0x2666},
	{0x2357, 0x2666}, {0x2358, 0x6666}, {0x2359, 0x6666}, {0x235a, 0x6666},
	{0x235b, 0x7fff}, {0x235c, 0x7fff}, {0x235d, 0x7fff}, {0x235e, 0x7fff},
	{0x235f, 0x7fff}, {0x2360, 0x7fff}, {0x2361, 0x7fff}, {0x2362, 0x1000},
	{0x2367, 0x0007}, {0x2368, 0x4000}, {0x2369, 0x0008}, {0x236a, 0x2000},
	{0x236b, 0x0009}, {0x236c, 0x003c}, {0x236d, 0x0000}, {0x236f, 0x2000},
	{0x2370, 0x0008}, {0x2371, 0x000a}, {0x2373, 0x0000}, {0x2374, 0x7fff},
	{0x2375, 0x7ff0}, {0x2376, 0x7990}, {0x2377, 0x7332}, {0x2379, 0x1000},
	{0x237a, 0x1000}, {0x2388, 0x7fff}, {0x2389, 0x6000}, {0x238a, 0x4000},
	{0x238b, 0x1000}, {0x238c, 0x1000}, {0x2398, 0x4668}, {0x23a1, 0x2000},
	{0x23a3, 0x4000}, {0x23ad, 0x2000}, {0x23ae, 0x2000}, {0x23af, 0x2000},
	{0x23b4, 0x2000}, {0x23b5, 0x2000}, {0x23b6, 0x2000}, {0x23bb, 0x6000},
	{0x2303, 0x0710}, {0x2304, 0x0332}, {0x230c, 0x0200}, {0x230d, 0x0080},
	{0x2310, 0x0010}, {0x22fb, 0x0000}
};
#define RT5671_DSP_HEADPHONE_NB_NUM \
	(sizeof(rt5671_dsp_headphone_nb) / sizeof(rt5671_dsp_headphone_nb[0]))

static int rt5671_dsp_headset_nb_size = 0;
static char *rt5671_dsp_headset_nb_buf;
static char *rt5671_dsp_headset_nb_file = "/etc/firmware/rt5671_dsp_headset_nb.bin";
static int rt5671_dsp_headset_nb_1mic_size = 0;
static char *rt5671_dsp_headset_nb_1mic_buf;
static char *rt5671_dsp_headset_nb_1mic_file = "/etc/firmware/rt5671_dsp_headset_nb_1mic.bin";
static int rt5671_dsp_headset_nb_2mic_size = 0;
static char *rt5671_dsp_headset_nb_2mic_buf;
static char *rt5671_dsp_headset_nb_2mic_file = "/etc/firmware/rt5671_dsp_headset_nb_2mic.bin";
static unsigned short rt5671_dsp_headset_nb[][2] = {
	{0x22f8, 0x8003}, {0x232f, 0x00d0}, {0x2355, 0x2666}, {0x2356, 0x2666},
	{0x2357, 0x2666}, {0x2358, 0x6666}, {0x2359, 0x6666}, {0x235a, 0x6666},
	{0x235b, 0x7fff}, {0x235c, 0x7fff}, {0x235d, 0x7fff}, {0x235e, 0x7fff},
	{0x235f, 0x7fff}, {0x2360, 0x7fff}, {0x2361, 0x7fff}, {0x2362, 0x1000},
	{0x2367, 0x0007}, {0x2368, 0x4000}, {0x2369, 0x0008}, {0x236a, 0x2000},
	{0x236b, 0x0009}, {0x236c, 0x003c}, {0x236d, 0x0000}, {0x236f, 0x2000},
	{0x2370, 0x0008}, {0x2371, 0x000a}, {0x2373, 0x0000}, {0x2374, 0x7fff},
	{0x2375, 0x7ff0}, {0x2376, 0x7990}, {0x2377, 0x7332}, {0x2379, 0x1000},
	{0x237a, 0x1000}, {0x2388, 0x7fff}, {0x2389, 0x6000}, {0x238a, 0x4000},
	{0x238b, 0x1000}, {0x238c, 0x1000}, {0x2398, 0x4668}, {0x23a1, 0x2000},
	{0x23a3, 0x4000}, {0x23ad, 0x2000}, {0x23ae, 0x2000}, {0x23af, 0x2000},
	{0x23b4, 0x2000}, {0x23b5, 0x2000}, {0x23b6, 0x2000}, {0x23bb, 0x6000},
	{0x2303, 0x0710}, {0x2304, 0x0332}, {0x230c, 0x0200}, {0x230d, 0x0080},
	{0x2310, 0x0010}, {0x22fb, 0x0000}
};
#define RT5671_DSP_HEADSET_NB_NUM \
	(sizeof(rt5671_dsp_headset_nb) / sizeof(rt5671_dsp_headset_nb[0]))

static int rt5671_dsp_bluetooth_nb_size = 0;
static char *rt5671_dsp_bluetooth_nb_buf;
static char *rt5671_dsp_bluetooth_nb_file = "/etc/firmware/rt5671_dsp_bluetooth_nb.bin";
static int rt5671_dsp_bluetooth_nb_1mic_size = 0;
static char *rt5671_dsp_bluetooth_nb_1mic_buf;
static char *rt5671_dsp_bluetooth_nb_1mic_file = "/etc/firmware/rt5671_dsp_bluetooth_nb_1mic.bin";
static int rt5671_dsp_bluetooth_nb_2mic_size = 0;
static char *rt5671_dsp_bluetooth_nb_2mic_buf;
static char *rt5671_dsp_bluetooth_nb_2mic_file = "/etc/firmware/rt5671_dsp_bluetooth_nb_2mic.bin";
static unsigned short rt5671_dsp_bluetooth_nb[][2] = {
	{0x22f8, 0x8003}, {0x232f, 0x00d0}, {0x2355, 0x2666}, {0x2356, 0x2666},
	{0x2357, 0x2666}, {0x2358, 0x6666}, {0x2359, 0x6666}, {0x235a, 0x6666},
	{0x235b, 0x7fff}, {0x235c, 0x7fff}, {0x235d, 0x7fff}, {0x235e, 0x7fff},
	{0x235f, 0x7fff}, {0x2360, 0x7fff}, {0x2361, 0x7fff}, {0x2362, 0x1000},
	{0x2367, 0x0007}, {0x2368, 0x4000}, {0x2369, 0x0008}, {0x236a, 0x2000},
	{0x236b, 0x0009}, {0x236c, 0x003c}, {0x236d, 0x0000}, {0x236f, 0x2000},
	{0x2370, 0x0008}, {0x2371, 0x000a}, {0x2373, 0x0000}, {0x2374, 0x7fff},
	{0x2375, 0x7ff0}, {0x2376, 0x7990}, {0x2377, 0x7332}, {0x2379, 0x1000},
	{0x237a, 0x1000}, {0x2388, 0x7fff}, {0x2389, 0x6000}, {0x238a, 0x4000},
	{0x238b, 0x1000}, {0x238c, 0x1000}, {0x2398, 0x4668}, {0x23a1, 0x2000},
	{0x23a3, 0x4000}, {0x23ad, 0x2000}, {0x23ae, 0x2000}, {0x23af, 0x2000},
	{0x23b4, 0x2000}, {0x23b5, 0x2000}, {0x23b6, 0x2000}, {0x23bb, 0x6000},
	{0x2303, 0x0710}, {0x2304, 0x0332}, {0x230c, 0x0200}, {0x230d, 0x0080},
	{0x2310, 0x0010}, {0x22fb, 0x0000}
};
#define RT5671_DSP_BLUETOOTH_NB_NUM \
	(sizeof(rt5671_dsp_bluetooth_nb) / sizeof(rt5671_dsp_bluetooth_nb[0]))

static int rt5671_dsp_handset_voip_size = 0;
static char *rt5671_dsp_handset_voip_buf;
static char *rt5671_dsp_handset_voip_file = "/etc/firmware/rt5671_dsp_handset_voip.bin";
static int rt5671_dsp_handset_voip_1mic_size = 0;
static char *rt5671_dsp_handset_voip_1mic_buf;
static char *rt5671_dsp_handset_voip_1mic_file = "/etc/firmware/rt5671_dsp_handset_voip_1mic.bin";
static int rt5671_dsp_handset_voip_2mic_size = 0;
static char *rt5671_dsp_handset_voip_2mic_buf;
static char *rt5671_dsp_handset_voip_2mic_file = "/etc/firmware/rt5671_dsp_handset_voip_2mic.bin";
static unsigned short rt5671_dsp_handset_voip[][2] = {
	{0x22f8, 0x8003}, {0x232f, 0x00d0}, {0x2355, 0x2666}, {0x2356, 0x2666},
	{0x2357, 0x2666}, {0x2358, 0x6666}, {0x2359, 0x6666}, {0x235a, 0x6666},
	{0x235b, 0x7fff}, {0x235c, 0x7fff}, {0x235d, 0x7fff}, {0x235e, 0x7fff},
	{0x235f, 0x7fff}, {0x2360, 0x7fff}, {0x2361, 0x7fff}, {0x2362, 0x1000},
	{0x2367, 0x0007}, {0x2368, 0x4000}, {0x2369, 0x0008}, {0x236a, 0x2000},
	{0x236b, 0x0009}, {0x236c, 0x003c}, {0x236d, 0x0000}, {0x236f, 0x2000},
	{0x2370, 0x0008}, {0x2371, 0x000a}, {0x2373, 0x0000}, {0x2374, 0x7fff},
	{0x2375, 0x7ff0}, {0x2376, 0x7990}, {0x2377, 0x7332}, {0x2379, 0x1000},
	{0x237a, 0x1000}, {0x2388, 0x7fff}, {0x2389, 0x6000}, {0x238a, 0x4000},
	{0x238b, 0x1000}, {0x238c, 0x1000}, {0x2398, 0x4668}, {0x23a1, 0x2000},
	{0x23a3, 0x4000}, {0x23ad, 0x2000}, {0x23ae, 0x2000}, {0x23af, 0x2000},
	{0x23b4, 0x2000}, {0x23b5, 0x2000}, {0x23b6, 0x2000}, {0x23bb, 0x6000},
	{0x2303, 0x0710}, {0x2304, 0x0332}, {0x230c, 0x0200}, {0x230d, 0x0080},
	{0x2310, 0x0010}, {0x22fb, 0x0000}
};
#define RT5671_DSP_HANDSET_VOIP_NUM \
	(sizeof(rt5671_dsp_handset_voip) / sizeof(rt5671_dsp_handset_voip[0]))

static int rt5671_dsp_handsfree_voip_size = 0;
static char *rt5671_dsp_handsfree_voip_buf;
static char *rt5671_dsp_handsfree_voip_file = "/etc/firmware/rt5671_dsp_handsfree_voip.bin";
static int rt5671_dsp_handsfree_voip_1mic_size = 0;
static char *rt5671_dsp_handsfree_voip_1mic_buf;
static char *rt5671_dsp_handsfree_voip_1mic_file = "/etc/firmware/rt5671_dsp_handsfree_voip_1mic.bin";
static int rt5671_dsp_handsfree_voip_2mic_size = 0;
static char *rt5671_dsp_handsfree_voip_2mic_buf;
static char *rt5671_dsp_handsfree_voip_2mic_file = "/etc/firmware/rt5671_dsp_handsfree_voip_2mic.bin";
static unsigned short rt5671_dsp_handsfree_voip[][2] = {
	{0x22f8, 0x8003}, {0x232f, 0x00d0}, {0x2355, 0x2666}, {0x2356, 0x2666},
	{0x2357, 0x2666}, {0x2358, 0x6666}, {0x2359, 0x6666}, {0x235a, 0x6666},
	{0x235b, 0x7fff}, {0x235c, 0x7fff}, {0x235d, 0x7fff}, {0x235e, 0x7fff},
	{0x235f, 0x7fff}, {0x2360, 0x7fff}, {0x2361, 0x7fff}, {0x2362, 0x1000},
	{0x2367, 0x0007}, {0x2368, 0x4000}, {0x2369, 0x0008}, {0x236a, 0x2000},
	{0x236b, 0x0009}, {0x236c, 0x003c}, {0x236d, 0x0000}, {0x236f, 0x2000},
	{0x2370, 0x0008}, {0x2371, 0x000a}, {0x2373, 0x0000}, {0x2374, 0x7fff},
	{0x2375, 0x7ff0}, {0x2376, 0x7990}, {0x2377, 0x7332}, {0x2379, 0x1000},
	{0x237a, 0x1000}, {0x2388, 0x7fff}, {0x2389, 0x6000}, {0x238a, 0x4000},
	{0x238b, 0x1000}, {0x238c, 0x1000}, {0x2398, 0x4668}, {0x23a1, 0x2000},
	{0x23a3, 0x4000}, {0x23ad, 0x2000}, {0x23ae, 0x2000}, {0x23af, 0x2000},
	{0x23b4, 0x2000}, {0x23b5, 0x2000}, {0x23b6, 0x2000}, {0x23bb, 0x6000},
	{0x2303, 0x0710}, {0x2304, 0x0332}, {0x230c, 0x0200}, {0x230d, 0x0080},
	{0x2310, 0x0010}, {0x22fb, 0x0000}
};
#define RT5671_DSP_HANDSFREE_VOIP_NUM \
	(sizeof(rt5671_dsp_handsfree_voip) / sizeof(rt5671_dsp_handsfree_voip[0]))

static int rt5671_dsp_headphone_voip_size = 0;
static char *rt5671_dsp_headphone_voip_buf;
static char *rt5671_dsp_headphone_voip_file = "/etc/firmware/rt5671_dsp_headphone_voip.bin";
static int rt5671_dsp_headphone_voip_1mic_size = 0;
static char *rt5671_dsp_headphone_voip_1mic_buf;
static char *rt5671_dsp_headphone_voip_1mic_file = "/etc/firmware/rt5671_dsp_headphone_voip_1mic.bin";
static int rt5671_dsp_headphone_voip_2mic_size = 0;
static char *rt5671_dsp_headphone_voip_2mic_buf;
static char *rt5671_dsp_headphone_voip_2mic_file = "/etc/firmware/rt5671_dsp_headphone_voip_2mic.bin";
static unsigned short rt5671_dsp_headphone_voip[][2] = {
	{0x22f8, 0x8003}, {0x232f, 0x00d0}, {0x2355, 0x2666}, {0x2356, 0x2666},
	{0x2357, 0x2666}, {0x2358, 0x6666}, {0x2359, 0x6666}, {0x235a, 0x6666},
	{0x235b, 0x7fff}, {0x235c, 0x7fff}, {0x235d, 0x7fff}, {0x235e, 0x7fff},
	{0x235f, 0x7fff}, {0x2360, 0x7fff}, {0x2361, 0x7fff}, {0x2362, 0x1000},
	{0x2367, 0x0007}, {0x2368, 0x4000}, {0x2369, 0x0008}, {0x236a, 0x2000},
	{0x236b, 0x0009}, {0x236c, 0x003c}, {0x236d, 0x0000}, {0x236f, 0x2000},
	{0x2370, 0x0008}, {0x2371, 0x000a}, {0x2373, 0x0000}, {0x2374, 0x7fff},
	{0x2375, 0x7ff0}, {0x2376, 0x7990}, {0x2377, 0x7332}, {0x2379, 0x1000},
	{0x237a, 0x1000}, {0x2388, 0x7fff}, {0x2389, 0x6000}, {0x238a, 0x4000},
	{0x238b, 0x1000}, {0x238c, 0x1000}, {0x2398, 0x4668}, {0x23a1, 0x2000},
	{0x23a3, 0x4000}, {0x23ad, 0x2000}, {0x23ae, 0x2000}, {0x23af, 0x2000},
	{0x23b4, 0x2000}, {0x23b5, 0x2000}, {0x23b6, 0x2000}, {0x23bb, 0x6000},
	{0x2303, 0x0710}, {0x2304, 0x0332}, {0x230c, 0x0200}, {0x230d, 0x0080},
	{0x2310, 0x0010}, {0x22fb, 0x0000}
};
#define RT5671_DSP_HEADPHONE_VOIP_NUM \
	(sizeof(rt5671_dsp_headphone_voip) / sizeof(rt5671_dsp_headphone_voip[0]))

static int rt5671_dsp_headset_voip_size = 0;
static char *rt5671_dsp_headset_voip_buf;
static char *rt5671_dsp_headset_voip_file = "/etc/firmware/rt5671_dsp_headset_voip.bin";
static int rt5671_dsp_headset_voip_1mic_size = 0;
static char *rt5671_dsp_headset_voip_1mic_buf;
static char *rt5671_dsp_headset_voip_1mic_file = "/etc/firmware/rt5671_dsp_headset_voip_1mic.bin";
static int rt5671_dsp_headset_voip_2mic_size = 0;
static char *rt5671_dsp_headset_voip_2mic_buf;
static char *rt5671_dsp_headset_voip_2mic_file = "/etc/firmware/rt5671_dsp_headset_voip_2mic.bin";
static unsigned short rt5671_dsp_headset_voip[][2] = {
	{0x22f8, 0x8003}, {0x232f, 0x00d0}, {0x2355, 0x2666}, {0x2356, 0x2666},
	{0x2357, 0x2666}, {0x2358, 0x6666}, {0x2359, 0x6666}, {0x235a, 0x6666},
	{0x235b, 0x7fff}, {0x235c, 0x7fff}, {0x235d, 0x7fff}, {0x235e, 0x7fff},
	{0x235f, 0x7fff}, {0x2360, 0x7fff}, {0x2361, 0x7fff}, {0x2362, 0x1000},
	{0x2367, 0x0007}, {0x2368, 0x4000}, {0x2369, 0x0008}, {0x236a, 0x2000},
	{0x236b, 0x0009}, {0x236c, 0x003c}, {0x236d, 0x0000}, {0x236f, 0x2000},
	{0x2370, 0x0008}, {0x2371, 0x000a}, {0x2373, 0x0000}, {0x2374, 0x7fff},
	{0x2375, 0x7ff0}, {0x2376, 0x7990}, {0x2377, 0x7332}, {0x2379, 0x1000},
	{0x237a, 0x1000}, {0x2388, 0x7fff}, {0x2389, 0x6000}, {0x238a, 0x4000},
	{0x238b, 0x1000}, {0x238c, 0x1000}, {0x2398, 0x4668}, {0x23a1, 0x2000},
	{0x23a3, 0x4000}, {0x23ad, 0x2000}, {0x23ae, 0x2000}, {0x23af, 0x2000},
	{0x23b4, 0x2000}, {0x23b5, 0x2000}, {0x23b6, 0x2000}, {0x23bb, 0x6000},
	{0x2303, 0x0710}, {0x2304, 0x0332}, {0x230c, 0x0200}, {0x230d, 0x0080},
	{0x2310, 0x0010}, {0x22fb, 0x0000}
};
#define RT5671_DSP_HEADSET_VOIP_NUM \
	(sizeof(rt5671_dsp_headset_voip) / sizeof(rt5671_dsp_headset_voip[0]))

static int rt5671_dsp_bluetooth_voip_size = 0;
static char *rt5671_dsp_bluetooth_voip_buf;
static char *rt5671_dsp_bluetooth_voip_file = "/etc/firmware/rt5671_dsp_bluetooth_voip.bin";
static int rt5671_dsp_bluetooth_voip_1mic_size = 0;
static char *rt5671_dsp_bluetooth_voip_1mic_buf;
static char *rt5671_dsp_bluetooth_voip_1mic_file = "/etc/firmware/rt5671_dsp_bluetooth_voip_1mic.bin";
static int rt5671_dsp_bluetooth_voip_2mic_size = 0;
static char *rt5671_dsp_bluetooth_voip_2mic_buf;
static char *rt5671_dsp_bluetooth_voip_2mic_file = "/etc/firmware/rt5671_dsp_bluetooth_voip_2mic.bin";
static unsigned short rt5671_dsp_bluetooth_voip[][2] = {
	{0x22f8, 0x8003}, {0x232f, 0x00d0}, {0x2355, 0x2666}, {0x2356, 0x2666},
	{0x2357, 0x2666}, {0x2358, 0x6666}, {0x2359, 0x6666}, {0x235a, 0x6666},
	{0x235b, 0x7fff}, {0x235c, 0x7fff}, {0x235d, 0x7fff}, {0x235e, 0x7fff},
	{0x235f, 0x7fff}, {0x2360, 0x7fff}, {0x2361, 0x7fff}, {0x2362, 0x1000},
	{0x2367, 0x0007}, {0x2368, 0x4000}, {0x2369, 0x0008}, {0x236a, 0x2000},
	{0x236b, 0x0009}, {0x236c, 0x003c}, {0x236d, 0x0000}, {0x236f, 0x2000},
	{0x2370, 0x0008}, {0x2371, 0x000a}, {0x2373, 0x0000}, {0x2374, 0x7fff},
	{0x2375, 0x7ff0}, {0x2376, 0x7990}, {0x2377, 0x7332}, {0x2379, 0x1000},
	{0x237a, 0x1000}, {0x2388, 0x7fff}, {0x2389, 0x6000}, {0x238a, 0x4000},
	{0x238b, 0x1000}, {0x238c, 0x1000}, {0x2398, 0x4668}, {0x23a1, 0x2000},
	{0x23a3, 0x4000}, {0x23ad, 0x2000}, {0x23ae, 0x2000}, {0x23af, 0x2000},
	{0x23b4, 0x2000}, {0x23b5, 0x2000}, {0x23b6, 0x2000}, {0x23bb, 0x6000},
	{0x2303, 0x0710}, {0x2304, 0x0332}, {0x230c, 0x0200}, {0x230d, 0x0080},
	{0x2310, 0x0010}, {0x22fb, 0x0000}
};
#define RT5671_DSP_BLUETOOTH_VOIP_NUM \
	(sizeof(rt5671_dsp_bluetooth_voip) / sizeof(rt5671_dsp_bluetooth_voip[0]))

/**
 * rt5671_dsp_done - Wait until DSP is ready.
 * @codec: SoC Audio Codec device.
 *
 * To check voice DSP status and confirm it's ready for next work.
 *
 * Returns 0 for success or negative error code.
 */
static int rt5671_dsp_done(struct snd_soc_codec *codec)
{
	unsigned int count = 0, dsp_val;

	dsp_val = snd_soc_read(codec, RT5671_DSP_CTRL1);
	while (dsp_val & RT5671_DSP_BUSY_MASK) {
		if (count > 10)
			return -EBUSY;
		dsp_val = snd_soc_read(codec, RT5671_DSP_CTRL1);
		count++;
	}

	return 0;
}

/**
 * rt5671_dsp_write - Write DSP register.
 * @codec: SoC audio codec device.
 * @param: DSP parameters.
  *
 * Modify voice DSP register for sound effect. The DSP can be controlled
 * through DSP command format (0xfc), addr (0xc4), data (0xc5) and cmd (0xc6)
 * register. It has to wait until the DSP is ready.
 *
 * Returns 0 for success or negative error code.
 */
int rt5671_dsp_write(struct snd_soc_codec *codec, unsigned int addr,
	unsigned int data)
{
	unsigned int dsp_val;
	int ret;

	ret = snd_soc_write(codec, RT5671_DSP_CTRL2, addr);
	if (ret < 0) {
		dev_err(codec->dev, "Failed to write DSP addr reg: %d\n", ret);
		goto err;
	}
	ret = snd_soc_write(codec, RT5671_DSP_CTRL3, data);
	if (ret < 0) {
		dev_err(codec->dev, "Failed to write DSP data reg: %d\n", ret);
		goto err;
	}
	dsp_val = RT5671_DSP_I2C_AL_16 | RT5671_DSP_DL_2 |
		RT5671_DSP_CMD_MW | DSP_CLK_RATE | RT5671_DSP_CMD_EN;

	ret = snd_soc_write(codec, RT5671_DSP_CTRL1, dsp_val);
	if (ret < 0) {
		dev_err(codec->dev, "Failed to write DSP cmd reg: %d\n", ret);
		goto err;
	}
	ret = rt5671_dsp_done(codec);
	if (ret < 0) {
		dev_err(codec->dev, "DSP is busy: %d\n", ret);
		goto err;
	}

	return 0;

err:
	return ret;
}

/**
 * rt5671_dsp_read - Read DSP register.
 * @codec: SoC audio codec device.
 * @reg: DSP register index.
 *
 * Read DSP setting value from voice DSP. The DSP can be controlled
 * through DSP addr (0xc4), data (0xc5) and cmd (0xc6) register. Each
 * command has to wait until the DSP is ready.
 *
 * Returns DSP register value or negative error code.
 */
unsigned int rt5671_dsp_read(struct snd_soc_codec *codec, unsigned int reg)
{
	unsigned int value;
	unsigned int dsp_val;
	int ret = 0;

	ret = rt5671_dsp_done(codec);
	if (ret < 0) {
		dev_err(codec->dev, "DSP is busy: %d\n", ret);
		goto err;
	}

	ret = snd_soc_write(codec, RT5671_DSP_CTRL2, reg);
	if (ret < 0) {
		dev_err(codec->dev, "Failed to write DSP addr reg: %d\n", ret);
		goto err;
	}
	dsp_val = RT5671_DSP_I2C_AL_16 | RT5671_DSP_DL_0 | RT5671_DSP_RW_MASK |
		RT5671_DSP_CMD_MR | DSP_CLK_RATE | RT5671_DSP_CMD_EN;

	ret = snd_soc_write(codec, RT5671_DSP_CTRL1, dsp_val);
	if (ret < 0) {
		dev_err(codec->dev, "Failed to write DSP cmd reg: %d\n", ret);
		goto err;
	}

	ret = rt5671_dsp_done(codec);
	if (ret < 0) {
		dev_err(codec->dev, "DSP is busy: %d\n", ret);
		goto err;
	}

	ret = snd_soc_write(codec, RT5671_DSP_CTRL2, 0x26);
	if (ret < 0) {
		dev_err(codec->dev, "Failed to write DSP addr reg: %d\n", ret);
		goto err;
	}
	dsp_val = RT5671_DSP_DL_1 | RT5671_DSP_CMD_RR | RT5671_DSP_RW_MASK |
		DSP_CLK_RATE | RT5671_DSP_CMD_EN;

	ret = snd_soc_write(codec, RT5671_DSP_CTRL1, dsp_val);
	if (ret < 0) {
		dev_err(codec->dev, "Failed to write DSP cmd reg: %d\n", ret);
		goto err;
	}

	ret = rt5671_dsp_done(codec);
	if (ret < 0) {
		dev_err(codec->dev, "DSP is busy: %d\n", ret);
		goto err;
	}

	ret = snd_soc_write(codec, RT5671_DSP_CTRL2, 0x25);
	if (ret < 0) {
		dev_err(codec->dev, "Failed to write DSP addr reg: %d\n", ret);
		goto err;
	}

	dsp_val = RT5671_DSP_DL_1 | RT5671_DSP_CMD_RR | RT5671_DSP_RW_MASK |
		DSP_CLK_RATE | RT5671_DSP_CMD_EN;

	ret = snd_soc_write(codec, RT5671_DSP_CTRL1, dsp_val);
	if (ret < 0) {
		dev_err(codec->dev, "Failed to write DSP cmd reg: %d\n", ret);
		goto err;
	}

	ret = rt5671_dsp_done(codec);
	if (ret < 0) {
		dev_err(codec->dev, "DSP is busy: %d\n", ret);
		goto err;
	}

	ret = snd_soc_read(codec, RT5671_DSP_CTRL5);
	if (ret < 0) {
		dev_err(codec->dev, "Failed to read DSP data reg: %d\n", ret);
		goto err;
	}

	value = ret;
	return value;

err:
	return ret;
}

static unsigned int rt5671_read_dsp_code_from_file(char *file_path,
	 u8 **buf)
{
	loff_t pos = 0;
	unsigned int file_size = 0;
	struct file *fp;

	pr_debug("%s\n", __func__);


	fp = filp_open(file_path, O_RDONLY, 0);
	if (!IS_ERR(fp)) {
		file_size = vfs_llseek(fp, pos, SEEK_END);
		*buf = kzalloc(file_size, GFP_KERNEL);
		if (*buf == NULL) {
			pr_err("%s: kzalloc size=0x%x fail\n", __func__,
				file_size);
			filp_close(fp, 0);
			return 0;
		}

		kernel_read(fp, pos, *buf, file_size);
		filp_close(fp, 0);

		return file_size;
	} else {
		pr_err("%s: filp_open fail\n", __func__);
	}
	return 0;
}

static int char2int(char *buf, int count)
{
	int i, val = 0;

	for (i = 0; i < count; i++) {
		if (*(buf+i) <= '9' && *(buf + i) >= '0')
			val = (val << 4) | (*(buf + i) - '0');
		else if (*(buf+i) <= 'f' && *(buf + i) >= 'a')
			val = (val << 4) | ((*(buf + i) - 'a') + 0xa);
		else if (*(buf+i) <= 'F' && *(buf + i) >= 'A')
			val = (val << 4) | ((*(buf + i) - 'A') + 0xa);
		else
			break;
	}

	return val;
}

static int load_dsp_parameters(struct snd_soc_codec *codec, char *buf)
{
	char *ptr;
	int addr, val, ret;
	ptr = buf;

	ptr = strstr(ptr, "0x");
	while (ptr) {
		ptr += 2;
		addr = char2int(ptr, 4);
		ptr = strstr(ptr, "0x");
		ptr += 2;
		val = char2int(ptr, 4);
		ptr = strstr(ptr, "0x");

		ret = rt5671_dsp_write(codec, addr, val);
		if (ret < 0) {
			dev_err(codec->dev, "Fail to load Dsp: %d\n", ret);
			return 0;
		}
	}

	return 0;
}

static int rt5671_dsp_get(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kcontrol);
	struct rt5671_priv *rt5671 = snd_soc_codec_get_drvdata(codec);

	ucontrol->value.integer.value[0] = rt5671->dsp_sw;

	return 0;
}

static int rt5671_dsp_put(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kcontrol);
	struct rt5671_priv *rt5671 = snd_soc_codec_get_drvdata(codec);
	struct snd_soc_dapm_widget *w;

	if (rt5671->dsp_sw != ucontrol->value.integer.value[0]) {
		rt5671->dsp_sw = ucontrol->value.integer.value[0];

		list_for_each_entry(w, &codec->card->widgets, list)
			if (!strcmp(w->name, "Voice DSP") && w->power) {
				rt5671_dsp_write(codec, 0x22f9, 1);
				rt5671_dsp_snd_effect(codec);
			}
	}

	return 0;
}

static int rt5671_dsp_set_mic_mode(struct snd_soc_codec *codec,
	int mode, bool two_mic)
{
	int ret, i, *mic_file_size;
	char *mic_file_buf, *mic_file_name;

	switch (mode) {
	case RT5671_DSP_HANDSET:
		if (two_mic){
			mic_file_size = &rt5671_dsp_handset_2mic_size;
			mic_file_buf = rt5671_dsp_handset_2mic_buf;
			mic_file_name = rt5671_dsp_handset_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_handset_1mic_size;
			mic_file_buf = rt5671_dsp_handset_1mic_buf;
			mic_file_name = rt5671_dsp_handset_1mic_file; 
		}
		break;

	case RT5671_DSP_HANDSFREE:
		if (two_mic){
			mic_file_size = &rt5671_dsp_handsfree_2mic_size;
			mic_file_buf = rt5671_dsp_handsfree_2mic_buf;
			mic_file_name = rt5671_dsp_handsfree_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_handsfree_1mic_size;
			mic_file_buf = rt5671_dsp_handsfree_1mic_buf;
			mic_file_name = rt5671_dsp_handsfree_1mic_file; 
		}
		break;

	case RT5671_DSP_HEADPHONE:
		if (two_mic){
			mic_file_size = &rt5671_dsp_headphone_2mic_size;
			mic_file_buf = rt5671_dsp_headphone_2mic_buf;
			mic_file_name = rt5671_dsp_headphone_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_headphone_1mic_size;
			mic_file_buf = rt5671_dsp_headphone_1mic_buf;
			mic_file_name = rt5671_dsp_headphone_1mic_file; 
		}
		break;
	
	case RT5671_DSP_HEADSET:
		if (two_mic){
			mic_file_size = &rt5671_dsp_headset_2mic_size;
			mic_file_buf = rt5671_dsp_headset_2mic_buf;
			mic_file_name = rt5671_dsp_headset_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_headset_1mic_size;
			mic_file_buf = rt5671_dsp_headset_1mic_buf;
			mic_file_name = rt5671_dsp_headset_1mic_file; 
		}
		break;

	case RT5671_DSP_BLUETOOTH:
		if (two_mic){
			mic_file_size = &rt5671_dsp_bluetooth_2mic_size;
			mic_file_buf = rt5671_dsp_bluetooth_2mic_buf;
			mic_file_name = rt5671_dsp_bluetooth_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_bluetooth_1mic_size;
			mic_file_buf = rt5671_dsp_bluetooth_1mic_buf;
			mic_file_name = rt5671_dsp_bluetooth_1mic_file; 
		}
		break;

	case RT5671_DSP_HANDSET_NB:
		if (two_mic){
			mic_file_size = &rt5671_dsp_handset_nb_2mic_size;
			mic_file_buf = rt5671_dsp_handset_nb_2mic_buf;
			mic_file_name = rt5671_dsp_handset_nb_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_handset_nb_1mic_size;
			mic_file_buf = rt5671_dsp_handset_nb_1mic_buf;
			mic_file_name = rt5671_dsp_handset_nb_1mic_file; 
		}
		break;

	case RT5671_DSP_HANDSFREE_NB:
		if (two_mic){
			mic_file_size = &rt5671_dsp_handsfree_nb_2mic_size;
			mic_file_buf = rt5671_dsp_handsfree_nb_2mic_buf;
			mic_file_name = rt5671_dsp_handsfree_nb_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_handsfree_nb_1mic_size;
			mic_file_buf = rt5671_dsp_handsfree_nb_1mic_buf;
			mic_file_name = rt5671_dsp_handsfree_nb_1mic_file; 
		}
		break;

	case RT5671_DSP_HEADPHONE_NB:
		if (two_mic){
			mic_file_size = &rt5671_dsp_headphone_nb_2mic_size;
			mic_file_buf = rt5671_dsp_headphone_nb_2mic_buf;
			mic_file_name = rt5671_dsp_headphone_nb_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_headphone_nb_1mic_size;
			mic_file_buf = rt5671_dsp_headphone_nb_1mic_buf;
			mic_file_name = rt5671_dsp_headphone_nb_1mic_file; 
		}
		break;
	
	case RT5671_DSP_HEADSET_NB:
		if (two_mic){
			mic_file_size = &rt5671_dsp_headset_nb_2mic_size;
			mic_file_buf = rt5671_dsp_headset_nb_2mic_buf;
			mic_file_name = rt5671_dsp_headset_nb_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_headset_nb_1mic_size;
			mic_file_buf = rt5671_dsp_headset_nb_1mic_buf;
			mic_file_name = rt5671_dsp_headset_nb_1mic_file; 
		}
		break;

	case RT5671_DSP_BLUETOOTH_NB:
		if (two_mic){
			mic_file_size = &rt5671_dsp_bluetooth_nb_2mic_size;
			mic_file_buf = rt5671_dsp_bluetooth_nb_2mic_buf;
			mic_file_name = rt5671_dsp_bluetooth_nb_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_bluetooth_nb_1mic_size;
			mic_file_buf = rt5671_dsp_bluetooth_nb_1mic_buf;
			mic_file_name = rt5671_dsp_bluetooth_nb_1mic_file; 
		}
		break;

	case RT5671_DSP_HANDSET_VOIP:
		if (two_mic){
			mic_file_size = &rt5671_dsp_handset_voip_2mic_size;
			mic_file_buf = rt5671_dsp_handset_voip_2mic_buf;
			mic_file_name = rt5671_dsp_handset_voip_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_handset_voip_1mic_size;
			mic_file_buf = rt5671_dsp_handset_voip_1mic_buf;
			mic_file_name = rt5671_dsp_handset_voip_1mic_file; 
		}
		break;

	case RT5671_DSP_HANDSFREE_VOIP:
		if (two_mic){
			mic_file_size = &rt5671_dsp_handsfree_voip_2mic_size;
			mic_file_buf = rt5671_dsp_handsfree_voip_2mic_buf;
			mic_file_name = rt5671_dsp_handsfree_voip_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_handsfree_voip_1mic_size;
			mic_file_buf = rt5671_dsp_handsfree_voip_1mic_buf;
			mic_file_name = rt5671_dsp_handsfree_voip_1mic_file; 
		}
		break;

	case RT5671_DSP_HEADPHONE_VOIP:
		if (two_mic){
			mic_file_size = &rt5671_dsp_headphone_voip_2mic_size;
			mic_file_buf = rt5671_dsp_headphone_voip_2mic_buf;
			mic_file_name = rt5671_dsp_headphone_voip_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_headphone_voip_1mic_size;
			mic_file_buf = rt5671_dsp_headphone_voip_1mic_buf;
			mic_file_name = rt5671_dsp_headphone_voip_1mic_file; 
		}
		break;
	
	case RT5671_DSP_HEADSET_VOIP:
		if (two_mic){
			mic_file_size = &rt5671_dsp_headset_voip_2mic_size;
			mic_file_buf = rt5671_dsp_headset_voip_2mic_buf;
			mic_file_name = rt5671_dsp_headset_voip_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_headset_voip_1mic_size;
			mic_file_buf = rt5671_dsp_headset_voip_1mic_buf;
			mic_file_name = rt5671_dsp_headset_voip_1mic_file; 
		}
		break;

	case RT5671_DSP_BLUETOOTH_VOIP:
		if (two_mic){
			mic_file_size = &rt5671_dsp_bluetooth_voip_2mic_size;
			mic_file_buf = rt5671_dsp_bluetooth_voip_2mic_buf;
			mic_file_name = rt5671_dsp_bluetooth_voip_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_bluetooth_voip_1mic_size;
			mic_file_buf = rt5671_dsp_bluetooth_voip_1mic_buf;
			mic_file_name = rt5671_dsp_bluetooth_voip_1mic_file; 
		}
		break;

	default:
		dev_info(codec->dev, "Disable\n");
		return 0;
	}

	if (*mic_file_size == 0) {
		*mic_file_size = rt5671_read_dsp_code_from_file(mic_file_name,
				(u8 **)&mic_file_buf);

		switch (mode) {
		case RT5671_DSP_HANDSET:
			if (two_mic)
				rt5671_dsp_handset_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_handset_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HANDSFREE:
			if (two_mic)
				rt5671_dsp_handsfree_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_handsfree_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HEADPHONE:
			if (two_mic)
				rt5671_dsp_headphone_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_headphone_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HEADSET:
			if (two_mic)
				rt5671_dsp_headset_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_headset_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_BLUETOOTH:
			if (two_mic)
				rt5671_dsp_bluetooth_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_bluetooth_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HANDSET_NB:
			if (two_mic)
				rt5671_dsp_handset_nb_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_handset_nb_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HANDSFREE_NB:
			if (two_mic)
				rt5671_dsp_handsfree_nb_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_handsfree_nb_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HEADPHONE_NB:
			if (two_mic)
				rt5671_dsp_headphone_nb_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_headphone_nb_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HEADSET_NB:
			if (two_mic)
				rt5671_dsp_headset_nb_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_headset_nb_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_BLUETOOTH_NB:
			if (two_mic)
				rt5671_dsp_bluetooth_nb_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_bluetooth_nb_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HANDSET_VOIP:
			if (two_mic)
				rt5671_dsp_handset_voip_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_handset_voip_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HANDSFREE_VOIP:
			if (two_mic)
				rt5671_dsp_handsfree_voip_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_handsfree_voip_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HEADPHONE_VOIP:
			if (two_mic)
				rt5671_dsp_headphone_voip_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_headphone_voip_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HEADSET_VOIP:
			if (two_mic)
				rt5671_dsp_headset_voip_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_headset_voip_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_BLUETOOTH_VOIP:
			if (two_mic)
				rt5671_dsp_bluetooth_voip_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_bluetooth_voip_1mic_buf = mic_file_buf;
			break;

		default:
			return 0;
		}
	}

	if (*mic_file_size)
		load_dsp_parameters(codec, mic_file_buf);

	return 0;
}

static int rt5671_dsp_2mic_get(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kcontrol);
	struct rt5671_priv *rt5671 = snd_soc_codec_get_drvdata(codec);

	ucontrol->value.integer.value[0] = rt5671->dsp_2mic;

	return 0;
}

static int rt5671_dsp_2mic_put(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_codec *codec = snd_kcontrol_chip(kcontrol);
	struct rt5671_priv *rt5671 = snd_soc_codec_get_drvdata(codec);
	struct snd_soc_dapm_widget *w;

	if (rt5671->dsp_2mic != ucontrol->value.integer.value[0]) {
		rt5671->dsp_2mic = ucontrol->value.integer.value[0];

		list_for_each_entry(w, &codec->card->widgets, list)
			if (!strcmp(w->name, "Voice DSP") && w->power)
				rt5671_dsp_set_mic_mode(codec, rt5671->dsp_sw,
					rt5671->dsp_2mic);
	}

	return 0;
}

/* DSP Path Control 1 */
static const char * const rt5671_src_rxdp_mode[] = {
	"Normal", "Divided by 2", "Divided by 3"
};

static const SOC_ENUM_SINGLE_DECL(
	rt5671_src_rxdp_enum, RT5671_DSP_PATH1,
	RT5671_RXDP_SRC_SFT, rt5671_src_rxdp_mode);

static const char * const rt5671_src_txdp_mode[] = {
	"Normal", "Multiplied by 2", "Multiplied by 3"
};

static const SOC_ENUM_SINGLE_DECL(
	rt5671_src_txdp_enum, RT5671_DSP_PATH1,
	RT5671_TXDP_SRC_SFT, rt5671_src_txdp_mode);

/* Sound Effect */
static const char *rt5671_dsp_mode[] = {
	"Handset", "Handsfree", "Headphone", "Headset", "Bluetooth",
	"Handset-NB", "Handsfree-NB", "Headphone-NB", "Headset-NB", "Bluetooth-NB",
	"Handset-VOIP", "Handsfree-VOIP", "Headphone-VOIP", "Headset-VOIP", "Bluetooth-VOIP"
};

static const SOC_ENUM_SINGLE_DECL(rt5671_dsp_enum, 0, 0,
	rt5671_dsp_mode);

static const struct snd_kcontrol_new rt5671_dsp_snd_controls[] = {
	SOC_ENUM("RxDP SRC Switch", rt5671_src_rxdp_enum),
	SOC_ENUM("TxDP SRC Switch", rt5671_src_txdp_enum),
	/* AEC */
	SOC_ENUM_EXT("DSP Function Switch", rt5671_dsp_enum,
		rt5671_dsp_get, rt5671_dsp_put),
	SOC_SINGLE_EXT("DSP 2MIC Switch", SND_SOC_NOPM, 0, 1, 0,
		rt5671_dsp_2mic_get, rt5671_dsp_2mic_put),
};

/**
 * rt5671_dsp_conf - Set DSP basic setting.
 *
 * @codec: SoC audio codec device.
 *
 * Set parameters of basic setting to DSP.
 *
 * Returns 0 for success or negative error code.
 */
static int rt5671_dsp_conf(struct snd_soc_codec *codec)
{
	int ret, i;

	for (i = 0; i < RT5671_DSP_INIT_NUM; i++) {
		ret = rt5671_dsp_write(codec, rt5671_dsp_init[i][0],
			rt5671_dsp_init[i][1]);
		if (ret < 0) {
			dev_err(codec->dev, "Fail to config Dsp: %d\n", ret);
			goto conf_err;
		}
	}

	return 0;

conf_err:

	return ret;
}

/**
 * rt5671_dsp_rate - Set DSP rate setting.
 *
 * @codec: SoC audio codec device.
 * @sys_clk: System clock.
 * @srate: Sampling rate.
 *
 * Set parameters of system clock and sampling rate to DSP.
 *
 * Returns 0 for success or negative error code.
 */
static int rt5671_dsp_rate(struct snd_soc_codec *codec, int sys_clk,
	int srate)
{
	int ret, i, tab_num;
	unsigned short (*rate_tab)[2];

	dev_dbg(codec->dev,"rt5671_dsp_rate sys:%d srate:%d\n", sys_clk, srate);

	switch(sys_clk) {
	case 4096000:
		rate_tab = rt5671_dsp_4096000;
		tab_num = RT5671_DSP_4096000_NUM;
		break;
	case 11289600:
		rate_tab = rt5671_dsp_11289600;
		tab_num = RT5671_DSP_11289600_NUM;
		break;
	case 12288000:
		rate_tab = rt5671_dsp_12288000;
		tab_num = RT5671_DSP_12288000_NUM;
		break;
	case 24576000:
		rate_tab = rt5671_dsp_24576000;
		tab_num = RT5671_DSP_24576000_NUM;
		break;
	default:
		return -EINVAL;
		break;
	}

	for (i = 0; i < tab_num; i++) {
		ret = rt5671_dsp_write(codec, rate_tab[i][0], rate_tab[i][1]);
		if (ret < 0)
			goto rate_err;
	}

	switch(srate) {
	case 8000:
		rate_tab = rt5671_dsp_8;
		tab_num = RT5671_DSP_8_NUM;
		break;
	case 16000:
		rate_tab = rt5671_dsp_16;
		tab_num = RT5671_DSP_16_NUM;
		break;
	case 24000:
		rate_tab = rt5671_dsp_24;
		tab_num = RT5671_DSP_24_NUM;
		break;
	case 44100:
	case 48000:
		rate_tab = rt5671_dsp_48_441;
		tab_num = RT5671_DSP_48_441_NUM;
		break;
	default:
		return -EINVAL;
		break;
	}

	for (i = 0; i < tab_num; i++) {
		ret = rt5671_dsp_write(codec, rate_tab[i][0], rate_tab[i][1]);
		if (ret < 0)
			goto rate_err;
	}

	return 0;

rate_err:

	dev_err(codec->dev, "Fail to set rate parameters: %d\n", ret);
	return ret;
}

/**
 * rt5671_dsp_do_patch - Write DSP patch code.
 *
 * @codec: SoC audio codec device.
 *
 * Write patch codes to DSP.
 *
 * mode: 
 * 0: Init
 * 1: Reset
 *
 * Returns 0 for success or negative error code.
 */
static int rt5671_dsp_do_patch(struct snd_soc_codec *codec, int mode)
{
	int ret, i;

	switch (mode) {
	case 0: /*Init*/
		for (i = 0; i < RT5671_DSP_INIT_PATCH_NUM; i++) {
			ret = snd_soc_write(codec, rt5671_dsp_init_patch_code[i][0],
				rt5671_dsp_init_patch_code[i][1]);
			if (ret < 0)
				goto patch_err;


			if (rt5671_dsp_init_patch_code[i][0] == 0xe0) {
				ret = rt5671_dsp_done(codec);
				if (ret < 0) {
					dev_err(codec->dev, "DSP is busy: %d\n", ret);
					goto patch_err;
				}
			}
		}
		break;
	case 1: /*Reset*/
		for (i = 0; i < RT5671_DSP_RESET_PATCH_NUM; i++) {
			ret = snd_soc_write(codec, rt5671_dsp_reset_patch_code[i][0],
				rt5671_dsp_reset_patch_code[i][1]);
			if (ret < 0)
				goto patch_err;


			if (rt5671_dsp_reset_patch_code[i][0] == 0xe0) {
				ret = rt5671_dsp_done(codec);
				if (ret < 0) {
					dev_err(codec->dev, "DSP is busy: %d\n", ret);
					goto patch_err;
				}
			}
		}
		break;
	default:
		pr_err("Invalid patch mode %d\n", mode);
		ret = -EINVAL;
		break;
	}

	return 0;

patch_err:

	return ret;
}

static void rt5671_do_dsp_patch(struct work_struct *work)
{
	struct rt5671_priv *rt5671 =
		container_of(work, struct rt5671_priv, patch_work.work);
	struct snd_soc_codec *codec = rt5671->codec;

	snd_soc_update_bits(codec, RT5671_GEN_CTRL1, 0x1, 0x1);
	snd_soc_update_bits(codec, RT5671_PWR_ANLG1, RT5671_LDO_SEL_MASK, 0x3);
	snd_soc_write(codec, RT5671_PRIV_INDEX, 0x15);
	snd_soc_update_bits(codec, RT5671_PRIV_DATA, 0x7, 0x7);

	snd_soc_update_bits(codec, RT5671_PWR_DIG2,
		RT5671_PWR_I2S_DSP, RT5671_PWR_I2S_DSP);

	snd_soc_update_bits(codec, RT5671_GEN_CTRL1, RT5671_RST_DSP, 0);
	mdelay(1);
	snd_soc_update_bits(codec, RT5671_GEN_CTRL1, RT5671_RST_DSP,
		RT5671_RST_DSP);
	mdelay(15);
	snd_soc_update_bits(codec, RT5671_GEN_CTRL1, RT5671_RST_DSP, 0);

	mdelay(10);

	if (rt5671_dsp_do_patch(codec, 0) < 0)
		dev_err(codec->dev, "Patch DSP rom code Fail !!!\n");

	rt5671_dsp_rate(codec, 12288000, 16000);
	rt5671_dsp_conf(codec);
	rt5671_dsp_write(codec, 0x22fb, 0);
	/* power down DSP*/
	mdelay(15);
	printk("read %x=%x\n", 0x3fb5, rt5671_dsp_read(codec, 0x3fb5));
	rt5671_dsp_write(codec, 0x22f9, 1);
	printk("read %x=%x\n", 0x3fb5, rt5671_dsp_read(codec, 0x3fb5));

	snd_soc_update_bits(codec, RT5671_PWR_DIG2,
		RT5671_PWR_I2S_DSP, 0);

	snd_soc_update_bits(codec, RT5671_GEN_CTRL1, 0x1, 0x0);
	snd_soc_update_bits(codec, RT5671_PWR_ANLG1, RT5671_LDO_SEL_MASK, 0x1);
	snd_soc_write(codec, RT5671_PRIV_INDEX, 0x15);
	snd_soc_update_bits(codec, RT5671_PRIV_DATA, 0x7, 0x0);
}

int rt5671_dsp_set_data_source(struct snd_soc_codec *codec, int src)
{
	int ret, i;

	pr_debug("%s: src=%d\n", __func__, src);
	for (i = src * RT5671_DSP_TDM_SRC_PAR_NUM;
		i < (src + 1) * RT5671_DSP_TDM_SRC_PAR_NUM; i++) {
		ret = rt5671_dsp_write(codec,
			rt5671_dsp_data_src[i][0], rt5671_dsp_data_src[i][1]);
		if (ret < 0)
			goto src_err;
	}

	return 0;

src_err:

	dev_err(codec->dev, "Fail to set tdm source %d parameters: %d\n",
								src, ret);
	return ret;
}

/**
 * rt5671_dsp_set_mode - Set DSP mode parameters.
 *
 * @codec: SoC audio codec device.
 * @mode: DSP mode.
 *
 * Set parameters of mode to DSP.
 *
 * Returns 0 for success or negative error code.
 */
static int rt5671_dsp_set_mode(struct snd_soc_codec *codec, int mode,
	bool two_mic)
{
	int ret, i, tab_num, *file_size, *mic_file_size;
	char *file_buf, *file_name, *mic_file_buf, *mic_file_name;
	unsigned short (*mode_tab)[2];

	switch (mode) {
	case RT5671_DSP_HANDSET:
		dev_info(codec->dev, "HANDSET\n");
		mode_tab = rt5671_dsp_handset;
		tab_num = RT5671_DSP_HANDSET_NUM;
		file_size = &rt5671_dsp_handset_size;
		file_buf = rt5671_dsp_handset_buf;
		file_name = rt5671_dsp_handset_file; 

		if (two_mic){
			mic_file_size = &rt5671_dsp_handset_2mic_size;
			mic_file_buf = rt5671_dsp_handset_2mic_buf;
			mic_file_name = rt5671_dsp_handset_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_handset_1mic_size;
			mic_file_buf = rt5671_dsp_handset_1mic_buf;
			mic_file_name = rt5671_dsp_handset_1mic_file; 
		}
		break;

	case RT5671_DSP_HANDSFREE:
		dev_info(codec->dev, "HANDSFREE\n");
		mode_tab = rt5671_dsp_handsfree;
		tab_num = RT5671_DSP_HANDSFREE_NUM;
		file_size = &rt5671_dsp_handsfree_size;
		file_buf = rt5671_dsp_handsfree_buf;
		file_name = rt5671_dsp_handsfree_file; 

		if (two_mic){
			mic_file_size = &rt5671_dsp_handsfree_2mic_size;
			mic_file_buf = rt5671_dsp_handsfree_2mic_buf;
			mic_file_name = rt5671_dsp_handsfree_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_handsfree_1mic_size;
			mic_file_buf = rt5671_dsp_handsfree_1mic_buf;
			mic_file_name = rt5671_dsp_handsfree_1mic_file; 
		}
		break;

	case RT5671_DSP_HEADPHONE:
		dev_info(codec->dev, "HEADPHONE\n");
		mode_tab = rt5671_dsp_headphone;
		tab_num = RT5671_DSP_HEADPHONE_NUM;
		file_size = &rt5671_dsp_headphone_size;
		file_buf = rt5671_dsp_headphone_buf;
		file_name = rt5671_dsp_headphone_file; 

		if (two_mic){
			mic_file_size = &rt5671_dsp_headphone_2mic_size;
			mic_file_buf = rt5671_dsp_headphone_2mic_buf;
			mic_file_name = rt5671_dsp_headphone_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_headphone_1mic_size;
			mic_file_buf = rt5671_dsp_headphone_1mic_buf;
			mic_file_name = rt5671_dsp_headphone_1mic_file; 
		}
		break;
	
	case RT5671_DSP_HEADSET:
		dev_info(codec->dev, "HEADSET\n");
		mode_tab = rt5671_dsp_headset;
		tab_num = RT5671_DSP_HEADSET_NUM;
		file_size = &rt5671_dsp_headset_size;
		file_buf = rt5671_dsp_headset_buf;
		file_name = rt5671_dsp_headset_file; 

		if (two_mic){
			mic_file_size = &rt5671_dsp_headset_2mic_size;
			mic_file_buf = rt5671_dsp_headset_2mic_buf;
			mic_file_name = rt5671_dsp_headset_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_headset_1mic_size;
			mic_file_buf = rt5671_dsp_headset_1mic_buf;
			mic_file_name = rt5671_dsp_headset_1mic_file; 
		}
		break;

	case RT5671_DSP_BLUETOOTH:
		dev_info(codec->dev, "BLUETOOTH\n");
		mode_tab = rt5671_dsp_bluetooth;
		tab_num = RT5671_DSP_BLUETOOTH_NUM;
		file_size = &rt5671_dsp_bluetooth_size;
		file_buf = rt5671_dsp_bluetooth_buf;
		file_name = rt5671_dsp_bluetooth_file; 

		if (two_mic){
			mic_file_size = &rt5671_dsp_bluetooth_2mic_size;
			mic_file_buf = rt5671_dsp_bluetooth_2mic_buf;
			mic_file_name = rt5671_dsp_bluetooth_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_bluetooth_1mic_size;
			mic_file_buf = rt5671_dsp_bluetooth_1mic_buf;
			mic_file_name = rt5671_dsp_bluetooth_1mic_file; 
		}
		break;

	case RT5671_DSP_HANDSET_NB:
		dev_info(codec->dev, "HANDSET_NB\n");
		mode_tab = rt5671_dsp_handset_nb;
		tab_num = RT5671_DSP_HANDSET_NB_NUM;
		file_size = &rt5671_dsp_handset_nb_size;
		file_buf = rt5671_dsp_handset_nb_buf;
		file_name = rt5671_dsp_handset_nb_file; 

		if (two_mic){
			mic_file_size = &rt5671_dsp_handset_nb_2mic_size;
			mic_file_buf = rt5671_dsp_handset_nb_2mic_buf;
			mic_file_name = rt5671_dsp_handset_nb_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_handset_nb_1mic_size;
			mic_file_buf = rt5671_dsp_handset_nb_1mic_buf;
			mic_file_name = rt5671_dsp_handset_nb_1mic_file; 
		}
		break;

	case RT5671_DSP_HANDSFREE_NB:
		dev_info(codec->dev, "HANDSFREE_NB\n");
		mode_tab = rt5671_dsp_handsfree_nb;
		tab_num = RT5671_DSP_HANDSFREE_NB_NUM;
		file_size = &rt5671_dsp_handsfree_nb_size;
		file_buf = rt5671_dsp_handsfree_nb_buf;
		file_name = rt5671_dsp_handsfree_nb_file; 

		if (two_mic){
			mic_file_size = &rt5671_dsp_handsfree_nb_2mic_size;
			mic_file_buf = rt5671_dsp_handsfree_nb_2mic_buf;
			mic_file_name = rt5671_dsp_handsfree_nb_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_handsfree_nb_1mic_size;
			mic_file_buf = rt5671_dsp_handsfree_nb_1mic_buf;
			mic_file_name = rt5671_dsp_handsfree_nb_1mic_file; 
		}
		break;

	case RT5671_DSP_HEADPHONE_NB:
		dev_info(codec->dev, "HEADPHONE_NB\n");
		mode_tab = rt5671_dsp_headphone_nb;
		tab_num = RT5671_DSP_HEADPHONE_NB_NUM;
		file_size = &rt5671_dsp_headphone_nb_size;
		file_buf = rt5671_dsp_headphone_nb_buf;
		file_name = rt5671_dsp_headphone_nb_file; 

		if (two_mic){
			mic_file_size = &rt5671_dsp_headphone_nb_2mic_size;
			mic_file_buf = rt5671_dsp_headphone_nb_2mic_buf;
			mic_file_name = rt5671_dsp_headphone_nb_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_headphone_nb_1mic_size;
			mic_file_buf = rt5671_dsp_headphone_nb_1mic_buf;
			mic_file_name = rt5671_dsp_headphone_nb_1mic_file; 
		}
		break;
	
	case RT5671_DSP_HEADSET_NB:
		dev_info(codec->dev, "HEADSET_NB\n");
		mode_tab = rt5671_dsp_headset_nb;
		tab_num = RT5671_DSP_HEADSET_NB_NUM;
		file_size = &rt5671_dsp_headset_nb_size;
		file_buf = rt5671_dsp_headset_nb_buf;
		file_name = rt5671_dsp_headset_nb_file; 

		if (two_mic){
			mic_file_size = &rt5671_dsp_headset_nb_2mic_size;
			mic_file_buf = rt5671_dsp_headset_nb_2mic_buf;
			mic_file_name = rt5671_dsp_headset_nb_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_headset_nb_1mic_size;
			mic_file_buf = rt5671_dsp_headset_nb_1mic_buf;
			mic_file_name = rt5671_dsp_headset_nb_1mic_file; 
		}
		break;

	case RT5671_DSP_BLUETOOTH_NB:
		dev_info(codec->dev, "BLUETOOTH_NB\n");
		mode_tab = rt5671_dsp_bluetooth_nb;
		tab_num = RT5671_DSP_BLUETOOTH_NB_NUM;
		file_size = &rt5671_dsp_bluetooth_nb_size;
		file_buf = rt5671_dsp_bluetooth_nb_buf;
		file_name = rt5671_dsp_bluetooth_nb_file; 

		if (two_mic){
			mic_file_size = &rt5671_dsp_bluetooth_nb_2mic_size;
			mic_file_buf = rt5671_dsp_bluetooth_nb_2mic_buf;
			mic_file_name = rt5671_dsp_bluetooth_nb_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_bluetooth_nb_1mic_size;
			mic_file_buf = rt5671_dsp_bluetooth_nb_1mic_buf;
			mic_file_name = rt5671_dsp_bluetooth_nb_1mic_file; 
		}
		break;

	case RT5671_DSP_HANDSET_VOIP:
		dev_info(codec->dev, "HANDSET_VOIP\n");
		mode_tab = rt5671_dsp_handset_voip;
		tab_num = RT5671_DSP_HANDSET_VOIP_NUM;
		file_size = &rt5671_dsp_handset_voip_size;
		file_buf = rt5671_dsp_handset_voip_buf;
		file_name = rt5671_dsp_handset_voip_file; 

		if (two_mic){
			mic_file_size = &rt5671_dsp_handset_voip_2mic_size;
			mic_file_buf = rt5671_dsp_handset_voip_2mic_buf;
			mic_file_name = rt5671_dsp_handset_voip_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_handset_voip_1mic_size;
			mic_file_buf = rt5671_dsp_handset_voip_1mic_buf;
			mic_file_name = rt5671_dsp_handset_voip_1mic_file; 
		}
		break;

	case RT5671_DSP_HANDSFREE_VOIP:
		dev_info(codec->dev, "HANDSFREE_VOIP\n");
		mode_tab = rt5671_dsp_handsfree_voip;
		tab_num = RT5671_DSP_HANDSFREE_VOIP_NUM;
		file_size = &rt5671_dsp_handsfree_voip_size;
		file_buf = rt5671_dsp_handsfree_voip_buf;
		file_name = rt5671_dsp_handsfree_voip_file; 

		if (two_mic){
			mic_file_size = &rt5671_dsp_handsfree_voip_2mic_size;
			mic_file_buf = rt5671_dsp_handsfree_voip_2mic_buf;
			mic_file_name = rt5671_dsp_handsfree_voip_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_handsfree_voip_1mic_size;
			mic_file_buf = rt5671_dsp_handsfree_voip_1mic_buf;
			mic_file_name = rt5671_dsp_handsfree_voip_1mic_file; 
		}
		break;

	case RT5671_DSP_HEADPHONE_VOIP:
		dev_info(codec->dev, "HEADPHONE_VOIP\n");
		mode_tab = rt5671_dsp_headphone_voip;
		tab_num = RT5671_DSP_HEADPHONE_VOIP_NUM;
		file_size = &rt5671_dsp_headphone_voip_size;
		file_buf = rt5671_dsp_headphone_voip_buf;
		file_name = rt5671_dsp_headphone_voip_file; 

		if (two_mic){
			mic_file_size = &rt5671_dsp_headphone_voip_2mic_size;
			mic_file_buf = rt5671_dsp_headphone_voip_2mic_buf;
			mic_file_name = rt5671_dsp_headphone_voip_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_headphone_voip_1mic_size;
			mic_file_buf = rt5671_dsp_headphone_voip_1mic_buf;
			mic_file_name = rt5671_dsp_headphone_voip_1mic_file; 
		}
		break;
	
	case RT5671_DSP_HEADSET_VOIP:
		dev_info(codec->dev, "HEADSET_VOIP\n");
		mode_tab = rt5671_dsp_headset_voip;
		tab_num = RT5671_DSP_HEADSET_VOIP_NUM;
		file_size = &rt5671_dsp_headset_voip_size;
		file_buf = rt5671_dsp_headset_voip_buf;
		file_name = rt5671_dsp_headset_voip_file; 

		if (two_mic){
			mic_file_size = &rt5671_dsp_headset_voip_2mic_size;
			mic_file_buf = rt5671_dsp_headset_voip_2mic_buf;
			mic_file_name = rt5671_dsp_headset_voip_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_headset_voip_1mic_size;
			mic_file_buf = rt5671_dsp_headset_voip_1mic_buf;
			mic_file_name = rt5671_dsp_headset_voip_1mic_file; 
		}
		break;

	case RT5671_DSP_BLUETOOTH_VOIP:
		dev_info(codec->dev, "BLUETOOTH_VOIP\n");
		mode_tab = rt5671_dsp_bluetooth_voip;
		tab_num = RT5671_DSP_BLUETOOTH_VOIP_NUM;
		file_size = &rt5671_dsp_bluetooth_voip_size;
		file_buf = rt5671_dsp_bluetooth_voip_buf;
		file_name = rt5671_dsp_bluetooth_voip_file; 

		if (two_mic){
			mic_file_size = &rt5671_dsp_bluetooth_voip_2mic_size;
			mic_file_buf = rt5671_dsp_bluetooth_voip_2mic_buf;
			mic_file_name = rt5671_dsp_bluetooth_voip_2mic_file; 
		} else {
			mic_file_size = &rt5671_dsp_bluetooth_voip_1mic_size;
			mic_file_buf = rt5671_dsp_bluetooth_voip_1mic_buf;
			mic_file_name = rt5671_dsp_bluetooth_voip_1mic_file; 
		}
		break;

	default:
		dev_info(codec->dev, "Disable\n");
		return 0;
	}

	if (*mic_file_size == 0) {
		*mic_file_size = rt5671_read_dsp_code_from_file(mic_file_name,
				(u8 **)&mic_file_buf);

		switch (mode) {
		case RT5671_DSP_HANDSET:
			if (two_mic)
				rt5671_dsp_handset_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_handset_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HANDSFREE:
			if (two_mic)
				rt5671_dsp_handsfree_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_handsfree_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HEADPHONE:
			if (two_mic)
				rt5671_dsp_headphone_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_headphone_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HEADSET:
			if (two_mic)
				rt5671_dsp_headset_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_headset_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_BLUETOOTH:
			if (two_mic)
				rt5671_dsp_bluetooth_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_bluetooth_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HANDSET_NB:
			if (two_mic)
				rt5671_dsp_handset_nb_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_handset_nb_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HANDSFREE_NB:
			if (two_mic)
				rt5671_dsp_handsfree_nb_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_handsfree_nb_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HEADPHONE_NB:
			if (two_mic)
				rt5671_dsp_headphone_nb_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_headphone_nb_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HEADSET_NB:
			if (two_mic)
				rt5671_dsp_headset_nb_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_headset_nb_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_BLUETOOTH_NB:
			if (two_mic)
				rt5671_dsp_bluetooth_nb_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_bluetooth_nb_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HANDSET_VOIP:
			if (two_mic)
				rt5671_dsp_handset_voip_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_handset_voip_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HANDSFREE_VOIP:
			if (two_mic)
				rt5671_dsp_handsfree_voip_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_handsfree_voip_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HEADPHONE_VOIP:
			if (two_mic)
				rt5671_dsp_headphone_voip_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_headphone_voip_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_HEADSET_VOIP:
			if (two_mic)
				rt5671_dsp_headset_voip_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_headset_voip_1mic_buf = mic_file_buf;
			break;

		case RT5671_DSP_BLUETOOTH_VOIP:
			if (two_mic)
				rt5671_dsp_bluetooth_voip_2mic_buf = mic_file_buf;
			else
				rt5671_dsp_bluetooth_voip_1mic_buf = mic_file_buf;
			break;

		default:
			return 0;
		}
	}

	if (*mic_file_size)
		load_dsp_parameters(codec, mic_file_buf);


	if (*file_size == 0) {
		*file_size = rt5671_read_dsp_code_from_file(file_name,
				(u8 **)&file_buf);

		switch (mode) {
		case RT5671_DSP_HANDSET:
			rt5671_dsp_handset_buf = file_buf;
			break;
		
		case RT5671_DSP_HANDSFREE:
			rt5671_dsp_handsfree_buf = file_buf;
			break;
		
		case RT5671_DSP_HEADPHONE:
			rt5671_dsp_headphone_buf = file_buf;
			break;
		
		case RT5671_DSP_HEADSET:
			rt5671_dsp_headset_buf = file_buf;
			break;
		
		case RT5671_DSP_BLUETOOTH:
			rt5671_dsp_bluetooth_buf = file_buf;
			break;
		
		case RT5671_DSP_HANDSET_NB:
			rt5671_dsp_handset_nb_buf = file_buf;
			break;
		
		case RT5671_DSP_HANDSFREE_NB:
			rt5671_dsp_handsfree_nb_buf = file_buf;
			break;
		
		case RT5671_DSP_HEADPHONE_NB:
			rt5671_dsp_headphone_nb_buf = file_buf;
			break;
		
		case RT5671_DSP_HEADSET_NB:
			rt5671_dsp_headset_nb_buf = file_buf;
			break;
		
		case RT5671_DSP_BLUETOOTH_NB:
			rt5671_dsp_bluetooth_nb_buf = file_buf;
			break;
		
		case RT5671_DSP_HANDSET_VOIP:
			rt5671_dsp_handset_voip_buf = file_buf;
			break;
		
		case RT5671_DSP_HANDSFREE_VOIP:
			rt5671_dsp_handsfree_voip_buf = file_buf;
			break;
		
		case RT5671_DSP_HEADPHONE_VOIP:
			rt5671_dsp_headphone_voip_buf = file_buf;
			break;
		
		case RT5671_DSP_HEADSET_VOIP:
			rt5671_dsp_headset_voip_buf = file_buf;
			break;
		
		case RT5671_DSP_BLUETOOTH_VOIP:
			rt5671_dsp_bluetooth_voip_buf = file_buf;
			break;
		
		default:
			return 0;
		}
	}

	if (*file_size) {
		load_dsp_parameters(codec, file_buf);
	} else {
		for (i = 0; i < tab_num; i++) {
			ret = rt5671_dsp_write(codec, mode_tab[i][0], mode_tab[i][1]);
			if (ret < 0)
				goto mode_err;
		}
	}

	return 0;

mode_err:

	dev_err(codec->dev, "Fail to set mode %d parameters: %d\n", mode, ret);
	return ret;
}

/**
 * rt5671_dsp_snd_effect - Set DSP sound effect.
 *
 * Set parameters of sound effect to DSP.
 *
 * Returns 0 for success or negative error code.
 */
int rt5671_dsp_snd_effect(struct snd_soc_codec *codec)
{
	struct rt5671_priv *rt5671 = snd_soc_codec_get_drvdata(codec);
	int ret, rate;

	snd_soc_update_bits(codec, RT5671_GEN_CTRL1, RT5671_RST_DSP,
		RT5671_RST_DSP);
	snd_soc_update_bits(codec, RT5671_GEN_CTRL1, RT5671_RST_DSP, 0);

	mdelay(10);

	ret = rt5671_dsp_do_patch(codec, 1);
	if (ret < 0)
		goto effect_err;
#if 0
	ret = rt5671_dsp_rate(codec,
		rt5671->sysclk ?
		rt5671->sysclk : 11289600,
		rt5671->lrck[rt5671->aif_pu] ?
		rt5671->lrck[rt5671->aif_pu] : 44100);
#else
	rate = 16000;

	ret = rt5671_dsp_rate(codec,
		rt5671->sysclk ?
		rt5671->sysclk : 12288000, rate);
#endif
	if (ret < 0)
		goto effect_err;

	ret = rt5671_dsp_conf(codec);
	if (ret < 0)
		goto effect_err;
	
	ret = rt5671_dsp_set_data_source(codec,
		(snd_soc_read(codec, RT5671_DSP_PATH1) & 0xc) >> 2);
	if (ret < 0)
		goto effect_err;

	ret = rt5671_dsp_set_mode(codec, rt5671->dsp_sw, rt5671->dsp_2mic);
	if (ret < 0)
		goto effect_err;

	return 0;

effect_err:

	return ret;
}

static int rt5671_dsp_event(struct snd_soc_dapm_widget *w,
			struct snd_kcontrol *k, int event)
{
	struct snd_soc_codec *codec = w->codec;

	switch (event) {
	case SND_SOC_DAPM_POST_PMD:
		dev_dbg(codec->dev, "%s(): PMD\n", __func__);
		rt5671_dsp_write(codec, 0x22f9, 1);
		break;

	case SND_SOC_DAPM_POST_PMU:
		dev_dbg(codec->dev, "%s(): PMU\n", __func__);
		rt5671_dsp_snd_effect(codec);
		printk("read %x=%x\n", 0x3fb5, rt5671_dsp_read(codec, 0x3fb5));
		break;

	default:
		return 0;
	}

	return 0;
}

static const struct snd_soc_dapm_widget rt5671_dsp_dapm_widgets[] = {
	SND_SOC_DAPM_SUPPLY_S("Voice DSP", 1, SND_SOC_NOPM,
		0, 0, rt5671_dsp_event,
		SND_SOC_DAPM_POST_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA("DSP Downstream", SND_SOC_NOPM,
		0, 0, NULL, 0),
	SND_SOC_DAPM_PGA("DSP Upstream", SND_SOC_NOPM,
		0, 0, NULL, 0),
};

static const struct snd_soc_dapm_route rt5671_dsp_dapm_routes[] = {
	{"DSP Downstream", NULL, "Voice DSP"},
	{"DSP Downstream", NULL, "RxDP Mux"},
	{"DSP Upstream", NULL, "Voice DSP"},
	{"DSP Upstream", NULL, "TDM Data Mux"},
	{"DSP DL Mux", "DSP", "DSP Downstream"},
	{"DSP UL Mux", "DSP", "DSP Upstream"},
};

/**
 * rt5671_dsp_show - Dump DSP registers.
 * @dev: codec device.
 * @attr: device attribute.
 * @buf: buffer for display.
 *
 * To show non-zero values of all DSP registers.
 *
 * Returns buffer length.
 */
static ssize_t rt5671_dsp_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct rt5671_priv *rt5671 = i2c_get_clientdata(client);
	struct snd_soc_codec *codec = rt5671->codec;
	unsigned short (*rt5671_dsp_tab)[2];
	unsigned int val;
	int cnt = 0, i, tab_num;

	switch (rt5671->dsp_sw) {
	case RT5671_DSP_HANDSET:
		cnt += sprintf(buf, "[HANDSET]\n");
		rt5671_dsp_tab = rt5671_dsp_handset;
		tab_num = RT5671_DSP_HANDSET_NUM;
		break;

	case RT5671_DSP_HANDSFREE:
		cnt += sprintf(buf, "[HANDSFREE]\n");
		rt5671_dsp_tab = rt5671_dsp_handsfree;
		tab_num = RT5671_DSP_HANDSFREE_NUM;
		break;

	case RT5671_DSP_HEADPHONE:
		cnt += sprintf(buf, "[HEADPHONE]\n");
		rt5671_dsp_tab = rt5671_dsp_headphone;
		tab_num = RT5671_DSP_HEADPHONE_NUM;
		break;

	case RT5671_DSP_HEADSET:
		cnt += sprintf(buf, "[HEADSET]\n");
		rt5671_dsp_tab = rt5671_dsp_headset;
		tab_num = RT5671_DSP_HEADSET_NUM;
		break;

	case RT5671_DSP_BLUETOOTH:
		cnt += sprintf(buf, "[BLUETOOTH]\n");
		rt5671_dsp_tab = rt5671_dsp_bluetooth;
		tab_num = RT5671_DSP_BLUETOOTH_NUM;
		break;

	case RT5671_DSP_HANDSET_NB:
		cnt += sprintf(buf, "[HANDSET_NB]\n");
		rt5671_dsp_tab = rt5671_dsp_handset_nb;
		tab_num = RT5671_DSP_HANDSET_NB_NUM;
		break;

	case RT5671_DSP_HANDSFREE_NB:
		cnt += sprintf(buf, "[HANDSFREE_NB]\n");
		rt5671_dsp_tab = rt5671_dsp_handsfree_nb;
		tab_num = RT5671_DSP_HANDSFREE_NB_NUM;
		break;

	case RT5671_DSP_HEADPHONE_NB:
		cnt += sprintf(buf, "[HEADPHONE_NB]\n");
		rt5671_dsp_tab = rt5671_dsp_headphone_nb;
		tab_num = RT5671_DSP_HEADPHONE_NB_NUM;
		break;

	case RT5671_DSP_HEADSET_NB:
		cnt += sprintf(buf, "[HEADSET_NB]\n");
		rt5671_dsp_tab = rt5671_dsp_headset_nb;
		tab_num = RT5671_DSP_HEADSET_NB_NUM;
		break;

	case RT5671_DSP_BLUETOOTH_NB:
		cnt += sprintf(buf, "[BLUETOOTH_NB]\n");
		rt5671_dsp_tab = rt5671_dsp_bluetooth_nb;
		tab_num = RT5671_DSP_BLUETOOTH_NB_NUM;
		break;

	case RT5671_DSP_HANDSET_VOIP:
		cnt += sprintf(buf, "[HANDSET_VOIP]\n");
		rt5671_dsp_tab = rt5671_dsp_handset_voip;
		tab_num = RT5671_DSP_HANDSET_VOIP_NUM;
		break;

	case RT5671_DSP_HANDSFREE_VOIP:
		cnt += sprintf(buf, "[HANDSFREE_VOIP]\n");
		rt5671_dsp_tab = rt5671_dsp_handsfree_voip;
		tab_num = RT5671_DSP_HANDSFREE_VOIP_NUM;
		break;

	case RT5671_DSP_HEADPHONE_VOIP:
		cnt += sprintf(buf, "[HEADPHONE_VOIP]\n");
		rt5671_dsp_tab = rt5671_dsp_headphone_voip;
		tab_num = RT5671_DSP_HEADPHONE_VOIP_NUM;
		break;

	case RT5671_DSP_HEADSET_VOIP:
		cnt += sprintf(buf, "[HEADSET_VOIP]\n");
		rt5671_dsp_tab = rt5671_dsp_headset_voip;
		tab_num = RT5671_DSP_HEADSET_VOIP_NUM;
		break;

	case RT5671_DSP_BLUETOOTH_VOIP:
		cnt += sprintf(buf, "[BLUETOOTH_VOIP]\n");
		rt5671_dsp_tab = rt5671_dsp_bluetooth_voip;
		tab_num = RT5671_DSP_BLUETOOTH_VOIP_NUM;
		break;

	default:
		cnt += sprintf(buf, "RT5642 DSP Disabled\n");
		goto dsp_done;
	}

	for (i = 0; i < tab_num; i++) {
		if (cnt + RT5671_DSP_REG_DISP_LEN >= PAGE_SIZE)
			break;
		val = rt5671_dsp_read(codec, rt5671_dsp_tab[i][0]);
		if (!val)
			continue;
		cnt += snprintf(buf + cnt, RT5671_DSP_REG_DISP_LEN,
			"%04x: %04x\n", rt5671_dsp_tab[i][0], val);
	}

	rt5671_dsp_tab = rt5671_dsp_init;
	tab_num = RT5671_DSP_INIT_NUM;
	for (i = 0; i < tab_num; i++) {
		if (cnt + RT5671_DSP_REG_DISP_LEN >= PAGE_SIZE)
			break;
		val = rt5671_dsp_read(codec, rt5671_dsp_tab[i][0]);
		if (!val)
			continue;
		cnt += snprintf(buf + cnt, RT5671_DSP_REG_DISP_LEN,
			"%04x: %04x\n",
			rt5671_dsp_tab[i][0], val);
	}
	
	rt5671_dsp_tab = rt5671_dsp_data_src;
	tab_num = RT5671_DSP_TDM_SRC_PAR_NUM;
	for (i = 0; i < tab_num; i++) {
		if (cnt + RT5671_DSP_REG_DISP_LEN >= PAGE_SIZE)
			break;
		val = rt5671_dsp_read(codec, rt5671_dsp_tab[i][0]);
		if (!val)
			continue;
		cnt += snprintf(buf + cnt, RT5671_DSP_REG_DISP_LEN,
			"%04x: %04x\n",
			rt5671_dsp_tab[i][0], val);
	}

	tab_num = RT5671_DSP_RATE_NUM;
	for (i = 0; i < tab_num; i++) {
		if (cnt + RT5671_DSP_REG_DISP_LEN >= PAGE_SIZE)
			break;
		val = rt5671_dsp_read(codec, rt5671_dsp_rate_par[i]);
		//if (!val)
		//	continue;
		cnt += snprintf(buf + cnt, RT5671_DSP_REG_DISP_LEN,
			"%04x: %04x\n",
			rt5671_dsp_rate_par[i], val);
	}
	if (cnt + RT5671_DSP_REG_DISP_LEN < PAGE_SIZE) {
		val = rt5671_dsp_read(codec, 0x3fb5);
		cnt += snprintf(buf + cnt, RT5671_DSP_REG_DISP_LEN,
			"%04x: %04x\n",
			0x3fb5, val);
	}
dsp_done:

	if (cnt >= PAGE_SIZE)
		cnt = PAGE_SIZE - 1;

	return cnt;
}

static ssize_t dsp_reg_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct rt5671_priv *rt5671 = i2c_get_clientdata(client);
	struct snd_soc_codec *codec = rt5671->codec;
	unsigned int val = 0, addr = 0;
	int i;

	pr_debug("register \"%s\" count = %d\n", buf, count);

	/* address */
	for (i = 0; i < count; i++)
		if (*(buf + i) <= '9' && *(buf + i) >= '0')
			addr = (addr << 4) | (*(buf + i) - '0');
		else if (*(buf + i) <= 'f' && *(buf + i) >= 'a')
			addr = (addr << 4) | ((*(buf + i) - 'a') + 0xa);
		else if (*(buf + i) <= 'A' && *(buf + i) >= 'A')
			addr = (addr << 4) | ((*(buf + i) - 'A') + 0xa);
		else
			break;

	/* Value*/
	for (i = i + 1; i < count; i++)
		if (*(buf + i) <= '9' && *(buf + i) >= '0')
			val = (val << 4) | (*(buf + i) - '0');
		else if (*(buf + i) <= 'f' && *(buf + i) >= 'a')
			val = (val << 4) | ((*(buf + i) - 'a') + 0xa);
		else if (*(buf + i) <= 'F' && *(buf + i) >= 'A')
			val = (val << 4) | ((*(buf + i) - 'A') + 0xa);
		else
			break;

	pr_debug("addr=0x%x val=0x%x\n", addr, val);
	if (i == count)
		pr_debug("0x%04x = 0x%04x\n",
			addr, rt5671_dsp_read(codec, addr));
	else
		rt5671_dsp_write(codec, addr, val);

	return count;
}
static DEVICE_ATTR(dsp_reg, 0666, rt5671_dsp_show, dsp_reg_store);

/**
 * rt5671_dsp_probe - register DSP for rt5671
 * @codec: audio codec
 *
 * To register DSP function for rt5671.
 *
 * Returns 0 for success or negative error code.
 */
int rt5671_dsp_probe(struct snd_soc_codec *codec)
{
	struct rt5671_priv *rt5671 = snd_soc_codec_get_drvdata(codec);
	int ret;

	if (codec == NULL)
		return -EINVAL;

#if 1
	INIT_DELAYED_WORK(&rt5671->patch_work, rt5671_do_dsp_patch);
		schedule_delayed_work(&rt5671->patch_work,
				msecs_to_jiffies(100));
#else
	snd_soc_update_bits(codec, RT5671_PWR_DIG2,
		RT5671_PWR_I2S_DSP, RT5671_PWR_I2S_DSP);

	snd_soc_update_bits(codec, RT5671_GEN_CTRL1, RT5671_RST_DSP, 0);
	mdelay(1);
	snd_soc_update_bits(codec, RT5671_GEN_CTRL1, RT5671_RST_DSP,
		RT5671_RST_DSP);
	mdelay(15);
	snd_soc_update_bits(codec, RT5671_GEN_CTRL1, RT5671_RST_DSP, 0);

	mdelay(10);
	
	ret = rt5671_dsp_do_patch(codec, 0);
	if (ret < 0)
		pr_err("Download DSP patch code fail\n.");

	rt5671_dsp_rate(codec, 12288000, 16000);
	rt5671_dsp_conf(codec);

	rt5671_dsp_write(codec, 0x22fb, 0);
	/* power down DSP*/
	mdelay(15);
	printk("read %x=%x\n", 0x3fb5, rt5671_dsp_read(codec, 0x3fb5));
	rt5671_dsp_write(codec, 0x22f9, 1);

	snd_soc_update_bits(codec, RT5671_PWR_DIG2,
		RT5671_PWR_I2S_DSP, 0);
#endif
	snd_soc_add_codec_controls(codec, rt5671_dsp_snd_controls,
			ARRAY_SIZE(rt5671_dsp_snd_controls));
	snd_soc_dapm_new_controls(&codec->dapm, rt5671_dsp_dapm_widgets,
			ARRAY_SIZE(rt5671_dsp_dapm_widgets));
	snd_soc_dapm_add_routes(&codec->dapm, rt5671_dsp_dapm_routes,
			ARRAY_SIZE(rt5671_dsp_dapm_routes));

	ret = device_create_file(codec->dev, &dev_attr_dsp_reg);
	if (ret != 0) {
		dev_err(codec->dev,
			"Failed to create dsp_reg sysfs files: %d\n", ret);
		return ret;
	}

	return 0;
}
EXPORT_SYMBOL_GPL(rt5671_dsp_probe);

#ifdef RTK_IOCTL
int rt5671_dsp_ioctl_common(struct snd_hwdep *hw,
	struct file *file, unsigned int cmd, unsigned long arg)
{
	struct rt_codec_cmd rt_codec;
	int *buf;
	int *p;
	int ret;

	struct rt_codec_cmd __user *_rt_codec = (struct rt_codec_cmd *)arg;
	struct snd_soc_codec *codec = hw->private_data;
	struct rt5671_priv *rt5671 = snd_soc_codec_get_drvdata(codec);

	if (copy_from_user(&rt_codec, _rt_codec, sizeof(rt_codec))) {
		dev_err(codec->dev, "copy_from_user faild\n");
		return -EFAULT;
	}
	dev_dbg(codec->dev, "rt_codec.number=%d\n", rt_codec.number);
	buf = kmalloc(sizeof(*buf) * rt_codec.number, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;
	if (copy_from_user(buf, rt_codec.buf, sizeof(*buf) * rt_codec.number))
		goto err;

	ret = snd_soc_update_bits(codec, RT5671_PWR_DIG2,
		RT5671_PWR_I2S_DSP, RT5671_PWR_I2S_DSP);
	if (ret < 0) {
		dev_err(codec->dev,
			"Failed to power up DSP IIS interface: %d\n", ret);
		goto err;
	}

	switch (cmd) {
	case RT_READ_CODEC_DSP_IOCTL:
		for (p = buf; p < buf + rt_codec.number / 2; p++)
			*(p + rt_codec.number / 2) = rt5671_dsp_read(codec, *p);
		if (copy_to_user(rt_codec.buf, buf,
			sizeof(*buf) * rt_codec.number))
			goto err;
		break;

	case RT_WRITE_CODEC_DSP_IOCTL:
		if (codec == NULL) {
			dev_dbg(codec->dev, "codec is null\n");
			break;
		}
		for (p = buf; p < buf + rt_codec.number / 2; p++)
			rt5671_dsp_write(codec, *p, *(p + rt_codec.number / 2));
		break;

	case RT_GET_CODEC_DSP_MODE_IOCTL:
		*buf = rt5671->dsp_sw;
		if (copy_to_user(rt_codec.buf, buf,
			sizeof(*buf) * rt_codec.number))
			goto err;
		break;

	default:
		dev_info(codec->dev, "unsported dsp command\n");
		break;
	}

	kfree(buf);
	return 0;

err:
	kfree(buf);
	return -EFAULT;
}
EXPORT_SYMBOL_GPL(rt5671_dsp_ioctl_common);
#endif

#ifdef CONFIG_PM
int rt5671_dsp_suspend(struct snd_soc_codec *codec)
{
	return 0;
}
EXPORT_SYMBOL_GPL(rt5671_dsp_suspend);

int rt5671_dsp_resume(struct snd_soc_codec *codec)
{
	return 0;
}
EXPORT_SYMBOL_GPL(rt5671_dsp_resume);
#endif

