/* LGE_CHANGE_S
* Comment : add realtek alsa sound driver for odin hdk
* 2013-06-20, hyunsoo.yoon@lge.com
*/
/*
 * rt5671.h  --  RT5671 ALSA SoC audio driver
 *
 * Copyright 2011 Realtek Microelectronics
 * Author: Johnny Hsu <johnnyhsu@realtek.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __RT5671_H__
#define __RT5671_H__
#define REALTEK_USE_AMIC	0
/* Info */
#define RT5671_RESET				0x00
#define RT5671_VENDOR_ID			0xfd
#define RT5671_VENDOR_ID1			0xfe
#define RT5671_VENDOR_ID2			0xff
/*  I/O - Output */
#define RT5671_HP_VOL				0x02
#define RT5671_LOUT1				0x03
#define RT5671_MONO_OUT				0x04
/* I/O - Input */
#define RT5671_CJ_CTRL1				0x0a
#define RT5671_CJ_CTRL2				0x0b
#define RT5671_CJ_CTRL3				0x0c
#define RT5671_IN1_IN2				0x0d
#define RT5671_IN3				0x0e
#define RT5671_INL1_INR1_VOL			0x0f
/* I/O - ADC/DAC/DMIC */
#define RT5671_SIDETONE_CTRL			0x18
#define RT5671_DAC1_DIG_VOL			0x19
#define RT5671_DAC2_DIG_VOL			0x1a
#define RT5671_DAC_CTRL				0x1b
#define RT5671_STO1_ADC_DIG_VOL			0x1c
#define RT5671_MONO_ADC_DIG_VOL			0x1d
#define RT5671_ADC_BST_VOL1			0x1e
#define RT5671_STO2_ADC_DIG_VOL			0x1f
/* Mixer - D-D */
#define RT5671_ADC_BST_VOL2			0x20
#define RT5671_STO2_ADC_MIXER			0x26
#define RT5671_STO1_ADC_MIXER			0x27
#define RT5671_MONO_ADC_MIXER			0x28
#define RT5671_AD_DA_MIXER			0x29
#define RT5671_STO_DAC_MIXER			0x2a
#define RT5671_DD_MIXER				0x2b
#define RT5671_DIG_MIXER			0x2c
#define RT5671_DSP_PATH1			0x2d
#define RT5671_DSP_PATH2			0x2e
#define RT5671_DIG_INF1_DATA			0x2f
#define RT5671_DIG_INF2_DATA			0x30
/* Mixer - PDM */
#define RT5671_PDM_OUT_CTRL			0x31
#define RT5671_PDM_DATA_CTRL1			0x32
#define RT5671_PDM1_DATA_CTRL2			0x33
#define RT5671_PDM1_DATA_CTRL3			0x34
#define RT5671_PDM1_DATA_CTRL4			0x35
#define RT5671_PDM2_DATA_CTRL2			0x36
#define RT5671_PDM2_DATA_CTRL3			0x37
#define RT5671_PDM2_DATA_CTRL4			0x38
/* Mixer - ADC */
#define RT5671_REC_L1_MIXER			0x3b
#define RT5671_REC_L2_MIXER			0x3c
#define RT5671_REC_R1_MIXER			0x3d
#define RT5671_REC_R2_MIXER			0x3e
#define RT5671_REC_MONO1_MIXER			0x3f
#define RT5671_REC_MONO2_MIXER			0x40
/* Mixer - DAC */
#define RT5671_HPO_MIXER			0x45
#define RT5671_MONO_MIXER			0x4c
#define RT5671_OUT_L1_MIXER			0x4f
#define RT5671_OUT_R1_MIXER			0x52
#define RT5671_LOUT_MIXER			0x53
/* Power */
#define RT5671_PWR_DIG1				0x61
#define RT5671_PWR_DIG2				0x62
#define RT5671_PWR_ANLG1			0x63
#define RT5671_PWR_ANLG2			0x64
#define RT5671_PWR_MIXER			0x65
#define RT5671_PWR_VOL				0x66
/* Private Register Control */
#define RT5671_PRIV_INDEX			0x6a
#define RT5671_PRIV_DATA			0x6c
/* Format - ADC/DAC */
#define RT5671_I2S4_SDP				0x6f
#define RT5671_I2S1_SDP				0x70
#define RT5671_I2S2_SDP				0x71
#define RT5671_I2S3_SDP				0x72
#define RT5671_ADDA_CLK1			0x73
#define RT5671_ADDA_CLK2			0x74
#define RT5671_DMIC_CTRL1			0x75
#define RT5671_DMIC_CTRL2			0x76
/* Format - TDM Control */
#define RT5671_TDM_CTRL_1			0x77
#define RT5671_TDM_CTRL_2			0x78
#define RT5671_TDM_CTRL_3			0x79

/* Function - Analog */
#define RT5671_DSP_CLK				0x7f
#define RT5671_GLB_CLK				0x80
#define RT5671_PLL_CTRL1			0x81
#define RT5671_PLL_CTRL2			0x82
#define RT5671_ASRC_1				0x83
#define RT5671_ASRC_2				0x84
#define RT5671_ASRC_3				0x85
#define RT5671_ASRC_4				0x86
#define RT5671_ASRC_5				0x87
#define RT5671_ASRC_7				0x89
#define RT5671_ASRC_8				0x8a
#define RT5671_ASRC_9				0x8b
#define RT5671_ASRC_10				0x8c
#define RT5671_ASRC_11				0x8d
#define RT5671_DEPOP_M1				0x8e
#define RT5671_DEPOP_M2				0x8f
#define RT5671_DEPOP_M3				0x90
#define RT5671_CHARGE_PUMP			0x91
#define RT5671_MICBIAS				0x93
#define RT5671_A_JD_CTRL1			0x94
#define RT5671_A_JD_CTRL2			0x95
#define RT5671_ASRC_12				0x97
#define RT5671_ASRC_13				0x98
#define RT5671_ASRC_14				0x99
#define RT5671_VAD_CTRL1			0x9a
#define RT5671_VAD_CTRL2			0x9b
#define RT5671_VAD_CTRL3			0x9c
#define RT5671_VAD_CTRL4			0x9d
#define RT5671_VAD_CTRL5			0x9e
/* Function - Digital */
#define RT5671_ADC_EQ_CTRL1			0xae
#define RT5671_ADC_EQ_CTRL2			0xaf
#define RT5671_EQ_CTRL1				0xb0
#define RT5671_EQ_CTRL2				0xb1
#define RT5671_ALC_DRC_CTRL1			0xb2
#define RT5671_ALC_DRC_CTRL2			0xb3
#define RT5671_ALC_CTRL_1			0xb4
#define RT5671_ALC_CTRL_2			0xb5
#define RT5671_ALC_CTRL_3			0xb6
#define RT5671_ALC_CTRL_4			0xb7
#define RT5671_JD_CTRL				0xbb
#define RT5671_IRQ_CTRL1			0xbc
#define RT5671_IRQ_CTRL2			0xbd
#define RT5671_IRQ_CTRL3			0xbe
#define RT5671_INT_IRQ_ST			0xbf
#define RT5671_GPIO_CTRL1			0xc0
#define RT5671_GPIO_CTRL2			0xc1
#define RT5671_GPIO_CTRL3			0xc2
#define RT5671_SCRABBLE_FUN			0xcd
#define RT5671_SCRABBLE_CTRL			0xce
#define RT5671_BASE_BACK			0xcf
#define RT5671_MP3_PLUS1			0xd0
#define RT5671_MP3_PLUS2			0xd1
#define RT5671_ADJ_HPF1				0xd3
#define RT5671_ADJ_HPF2				0xd4
#define RT5671_HP_CALIB_AMP_DET			0xd6
#define RT5671_SV_ZCD1				0xd9
#define RT5671_SV_ZCD2				0xda
#define RT5671_IL_CMD				0xdb
#define RT5671_IL_CMD2				0xdc
#define RT5671_IL_CMD3				0xdd
#define RT5671_DRC_HL_CTRL1			0xe6
#define RT5671_DRC_HL_CTRL2			0xe7
#define RT5671_ADC_MONO_HP_CTRL1		0xec
#define RT5671_ADC_MONO_HP_CTRL2		0xed
#define RT5671_ADC_STO2_HP_CTRL1		0xee
#define RT5671_ADC_STO2_HP_CTRL2		0xef
#define RT5671_JD_CTRL3				0xf8
#define RT5671_JD_CTRL4				0xf9
/* General Control */
#define RT5671_DIG_MISC				0xfa
#define RT5671_GEN_CTRL2			0xfb
#define RT5671_GEN_CTRL3			0xfc


/* Index of Codec Private Register definition */
#define RT5671_DIG_VOL				0x00
#define RT5671_PR_ALC_CTRL_1			0x01
#define RT5671_PR_ALC_CTRL_2			0x02
#define RT5671_PR_ALC_CTRL_3			0x03
#define RT5671_PR_ALC_CTRL_4			0x04
#define RT5671_PR_ALC_CTRL_5			0x05
#define RT5671_PR_ALC_CTRL_6			0x06
#define RT5671_BIAS_CUR1			0x12
#define RT5671_BIAS_CUR3			0x14
#define RT5671_CLSD_INT_REG1			0x1c
#define RT5671_MAMP_INT_REG2			0x37
#define RT5671_CHOP_DAC_ADC			0x3d
#define RT5671_MIXER_INT_REG			0x3f
#define RT5671_3D_SPK				0x63
#define RT5671_WND_1				0x6c
#define RT5671_WND_2				0x6d
#define RT5671_WND_3				0x6e
#define RT5671_WND_4				0x6f
#define RT5671_WND_5				0x70
#define RT5671_WND_8				0x73
#define RT5671_DIP_SPK_INF			0x75
#define RT5671_HP_DCC_INT1			0x77
#define RT5671_EQ_BW_LOP			0xa0
#define RT5671_EQ_GN_LOP			0xa1
#define RT5671_EQ_FC_BP1			0xa2
#define RT5671_EQ_BW_BP1			0xa3
#define RT5671_EQ_GN_BP1			0xa4
#define RT5671_EQ_FC_BP2			0xa5
#define RT5671_EQ_BW_BP2			0xa6
#define RT5671_EQ_GN_BP2			0xa7
#define RT5671_EQ_FC_BP3			0xa8
#define RT5671_EQ_BW_BP3			0xa9
#define RT5671_EQ_GN_BP3			0xaa
#define RT5671_EQ_FC_BP4			0xab
#define RT5671_EQ_BW_BP4			0xac
#define RT5671_EQ_GN_BP4			0xad
#define RT5671_EQ_FC_HIP1			0xae
#define RT5671_EQ_GN_HIP1			0xaf
#define RT5671_EQ_FC_HIP2			0xb0
#define RT5671_EQ_BW_HIP2			0xb1
#define RT5671_EQ_GN_HIP2			0xb2
#define RT5671_EQ_PRE_VOL			0xb3
#define RT5671_EQ_PST_VOL			0xb4


/* global definition */
#define RT5671_L_MUTE				(0x1 << 15)
#define RT5671_L_MUTE_SFT			15
#define RT5671_VOL_L_MUTE			(0x1 << 14)
#define RT5671_VOL_L_SFT			14
#define RT5671_R_MUTE				(0x1 << 7)
#define RT5671_R_MUTE_SFT			7
#define RT5671_VOL_R_MUTE			(0x1 << 6)
#define RT5671_VOL_R_SFT			6
#define RT5671_L_VOL_MASK			(0x3f << 8)
#define RT5671_L_VOL_SFT			8
#define RT5671_R_VOL_MASK			(0x3f)
#define RT5671_R_VOL_SFT			0

/* Combo Jack Control 1 (0x0a) */
#define RT5671_CBJ_BST1_MASK			(0xf << 12)
#define RT5671_CBJ_BST1_SFT			(12)
#define RT5671_CBJ_JD_HP_EN			(0x1 << 9)
#define RT5671_CBJ_JD_MIC_EN			(0x1 << 8)
#define RT5671_CBJ_BST1_EN			(0x1 << 2)

/* Combo Jack Control 1 (0x0b) */
#define RT5671_CBJ_MN_JD			(0x1 << 12)
#define RT5671_CAPLESS_EN			(0x1 << 11)
#define RT5671_CBJ_DET_MODE			(0x1 << 7)

/* IN1 and IN2 Control (0x0d) */
/* IN3 and IN4 Control (0x0e) */
#define RT5671_BST_MASK1			(0xf<<12)
#define RT5671_BST_SFT1				12
#define RT5671_BST_MASK2			(0xf<<8)
#define RT5671_BST_SFT2				8
#define RT5671_IN_DF1				(0x1 << 7)
#define RT5671_IN_SFT1				7
#define RT5671_IN_DF2				(0x1 << 6)
#define RT5671_IN_SFT2				6

/* INL and INR Volume Control (0x0f) */
#define RT5671_INL_SEL_MASK			(0x1 << 15)
#define RT5671_INL_SEL_SFT			15
#define RT5671_INL_SEL_IN4P			(0x0 << 15)
#define RT5671_INL_SEL_MONOP			(0x1 << 15)
#define RT5671_INL_VOL_MASK			(0x1f << 8)
#define RT5671_INL_VOL_SFT			8
#define RT5671_INR_SEL_MASK			(0x1 << 7)
#define RT5671_INR_SEL_SFT			7
#define RT5671_INR_SEL_IN4N			(0x0 << 7)
#define RT5671_INR_SEL_MONON			(0x1 << 7)
#define RT5671_INR_VOL_MASK			(0x1f)
#define RT5671_INR_VOL_SFT			0

/* Sidetone Control (0x18) */
#define RT5671_ST_SEL_MASK			(0x7 << 9)
#define RT5671_ST_SEL_SFT			9
#define RT5671_M_ST_DACR2			(0x1 << 8)
#define RT5671_M_ST_DACR2_SFT			8
#define RT5671_M_ST_DACL2			(0x1 << 7)
#define RT5671_M_ST_DACL2_SFT			7
#define RT5671_ST_EN				(0x1 << 6)
#define RT5671_ST_EN_SFT			6

/* DAC1 Digital Volume (0x19) */
#define RT5671_DAC_L1_VOL_MASK			(0xff << 8)
#define RT5671_DAC_L1_VOL_SFT			8
#define RT5671_DAC_R1_VOL_MASK			(0xff)
#define RT5671_DAC_R1_VOL_SFT			0

/* DAC2 Digital Volume (0x1a) */
#define RT5671_DAC_L2_VOL_MASK			(0xff << 8)
#define RT5671_DAC_L2_VOL_SFT			8
#define RT5671_DAC_R2_VOL_MASK			(0xff)
#define RT5671_DAC_R2_VOL_SFT			0

/* DAC2 Control (0x1b) */
#define RT5671_M_DAC_L2_VOL			(0x1 << 13)
#define RT5671_M_DAC_L2_VOL_SFT			13
#define RT5671_M_DAC_R2_VOL			(0x1 << 12)
#define RT5671_M_DAC_R2_VOL_SFT			12
#define RT5671_DAC2_L_SEL_MASK			(0x7 << 4)
#define RT5671_DAC2_L_SEL_SFT			4
#define RT5671_DAC2_R_SEL_MASK			(0x7 << 0)
#define RT5671_DAC2_R_SEL_SFT			0

/* ADC Digital Volume Control (0x1c) */
#define RT5671_ADC_L_VOL_MASK			(0x7f << 8)
#define RT5671_ADC_L_VOL_SFT			8
#define RT5671_ADC_R_VOL_MASK			(0x7f)
#define RT5671_ADC_R_VOL_SFT			0

/* Mono ADC Digital Volume Control (0x1d) */
#define RT5671_MONO_ADC_L_VOL_MASK		(0x7f << 8)
#define RT5671_MONO_ADC_L_VOL_SFT		8
#define RT5671_MONO_ADC_R_VOL_MASK		(0x7f)
#define RT5671_MONO_ADC_R_VOL_SFT		0

/* ADC Boost Volume Control (0x1e) */
#define RT5671_STO1_ADC_L_BST_MASK		(0x3 << 14)
#define RT5671_STO1_ADC_L_BST_SFT		14
#define RT5671_STO1_ADC_R_BST_MASK		(0x3 << 12)
#define RT5671_STO1_ADC_R_BST_SFT		12
#define RT5671_STO1_ADC_COMP_MASK		(0x3 << 10)
#define RT5671_STO1_ADC_COMP_SFT		10
#define RT5671_STO2_ADC_L_BST_MASK		(0x3 << 8)
#define RT5671_STO2_ADC_L_BST_SFT		8
#define RT5671_STO2_ADC_R_BST_MASK		(0x3 << 6)
#define RT5671_STO2_ADC_R_BST_SFT		6
#define RT5671_STO2_ADC_COMP_MASK		(0x3 << 4)
#define RT5671_STO2_ADC_COMP_SFT		4

/* Stereo2 ADC Mixer Control (0x26) */
#define RT5671_STO2_ADC_SRC_MASK		(0x1 << 15)
#define RT5671_STO2_ADC_SRC_SFT			15

/* Stereo ADC Mixer Control (0x26 0x27) */
#define RT5671_M_ADC_L1				(0x1 << 14)
#define RT5671_M_ADC_L1_SFT			14
#define RT5671_M_ADC_L2				(0x1 << 13)
#define RT5671_M_ADC_L2_SFT			13
#define RT5671_ADC_1_SRC_MASK			(0x1 << 12)
#define RT5671_ADC_1_SRC_SFT			12
#define RT5671_ADC_1_SRC_ADC			(0x1 << 12)
#define RT5671_ADC_1_SRC_DACMIX			(0x0 << 12)
#define RT5671_ADC_2_SRC_MASK			(0x1 << 11)
#define RT5671_ADC_2_SRC_SFT			11
#define RT5671_ADC_SRC_MASK			(0x1 << 10)
#define RT5671_ADC_SRC_SFT			10
#define RT5671_DMIC_SRC_MASK			(0x3 << 8)
#define RT5671_DMIC_SRC_SFT			8
#define RT5671_M_ADC_R1				(0x1 << 6)
#define RT5671_M_ADC_R1_SFT			6
#define RT5671_M_ADC_R2				(0x1 << 5)
#define RT5671_M_ADC_R2_SFT			5
#define RT5671_DMIC3_SRC_MASK			(0x1 << 1)
#define RT5671_DMIC3_SRC_SFT			0

/* Mono ADC Mixer Control (0x28) */
#define RT5671_M_MONO_ADC_L1			(0x1 << 14)
#define RT5671_M_MONO_ADC_L1_SFT		14
#define RT5671_M_MONO_ADC_L2			(0x1 << 13)
#define RT5671_M_MONO_ADC_L2_SFT		13
#define RT5671_MONO_ADC_L1_SRC_MASK		(0x1 << 12)
#define RT5671_MONO_ADC_L1_SRC_SFT		12
#define RT5671_MONO_ADC_L1_SRC_DACMIXL		(0x0 << 12)
#define RT5671_MONO_ADC_L1_SRC_ADCL		(0x1 << 12)
#define RT5671_MONO_ADC_L2_SRC_MASK		(0x1 << 11)
#define RT5671_MONO_ADC_L2_SRC_SFT		11
#define RT5671_MONO_ADC_L_SRC_MASK		(0x1 << 10)
#define RT5671_MONO_ADC_L_SRC_SFT		10
#define RT5671_MONO_DMIC_L_SRC_MASK		(0x3 << 8)
#define RT5671_MONO_DMIC_L_SRC_SFT		8
#define RT5671_M_MONO_ADC_R1			(0x1 << 6)
#define RT5671_M_MONO_ADC_R1_SFT		6
#define RT5671_M_MONO_ADC_R2			(0x1 << 5)
#define RT5671_M_MONO_ADC_R2_SFT		5
#define RT5671_MONO_ADC_R1_SRC_MASK		(0x1 << 4)
#define RT5671_MONO_ADC_R1_SRC_SFT		4
#define RT5671_MONO_ADC_R1_SRC_ADCR		(0x1 << 4)
#define RT5671_MONO_ADC_R1_SRC_DACMIXR		(0x0 << 4)
#define RT5671_MONO_ADC_R2_SRC_MASK		(0x1 << 3)
#define RT5671_MONO_ADC_R2_SRC_SFT		3
#define RT5671_MONO_ADC_R_SRC_MASK		(0x1 << 2)
#define RT5671_MONO_ADC_R_SRC_SFT		2
#define RT5671_MONO_DMIC_R_SRC_MASK		(0x3)
#define RT5671_MONO_DMIC_R_SRC_SFT		0

/* ADC Mixer to DAC Mixer Control (0x29) */
#define RT5671_M_ADCMIX_L			(0x1 << 15)
#define RT5671_M_ADCMIX_L_SFT			15
#define RT5671_M_DAC1_L				(0x1 << 14)
#define RT5671_M_DAC1_L_SFT			14
#define RT5671_DAC1_R_SEL_MASK			(0x3 << 10)
#define RT5671_DAC1_R_SEL_SFT			10
#define RT5671_DAC1_R_SEL_IF1			(0x0 << 10)
#define RT5671_DAC1_R_SEL_IF2			(0x1 << 10)
#define RT5671_DAC1_R_SEL_IF3			(0x2 << 10)
#define RT5671_DAC1_R_SEL_IF4			(0x3 << 10)
#define RT5671_DAC1_L_SEL_MASK			(0x3 << 8)
#define RT5671_DAC1_L_SEL_SFT			8
#define RT5671_DAC1_L_SEL_IF1			(0x0 << 8)
#define RT5671_DAC1_L_SEL_IF2			(0x1 << 8)
#define RT5671_DAC1_L_SEL_IF3			(0x2 << 8)
#define RT5671_DAC1_L_SEL_IF4			(0x3 << 8)
#define RT5671_M_ADCMIX_R			(0x1 << 7)
#define RT5671_M_ADCMIX_R_SFT			7
#define RT5671_M_DAC1_R				(0x1 << 6)
#define RT5671_M_DAC1_R_SFT			6

/* Stereo DAC Mixer Control (0x2a) */
#define RT5671_M_DAC_L1				(0x1 << 14)
#define RT5671_M_DAC_L1_SFT			14
#define RT5671_DAC_L1_STO_L_VOL_MASK		(0x1 << 13)
#define RT5671_DAC_L1_STO_L_VOL_SFT		13
#define RT5671_M_DAC_L2				(0x1 << 12)
#define RT5671_M_DAC_L2_SFT			12
#define RT5671_DAC_L2_STO_L_VOL_MASK		(0x1 << 11)
#define RT5671_DAC_L2_STO_L_VOL_SFT		11
#define RT5671_M_ANC_DAC_L			(0x1 << 10)
#define RT5671_M_ANC_DAC_L_SFT			10
#define RT5671_M_DAC_R1_STO_L			(0x1 << 9)
#define RT5671_M_DAC_R1_STO_L_SFT		9
#define RT5671_DAC_R1_STO_L_VOL_MASK		(0x1 << 8)
#define RT5671_DAC_R1_STO_L_VOL_SFT		8
#define RT5671_M_DAC_R1				(0x1 << 6)
#define RT5671_M_DAC_R1_SFT			6
#define RT5671_DAC_R1_STO_R_VOL_MASK		(0x1 << 5)
#define RT5671_DAC_R1_STO_R_VOL_SFT		5
#define RT5671_M_DAC_R2				(0x1 << 4)
#define RT5671_M_DAC_R2_SFT			4
#define RT5671_DAC_R2_STO_R_VOL_MASK		(0x1 << 3)
#define RT5671_DAC_R2_STO_R_VOL_SFT		3
#define RT5671_M_ANC_DAC_R			(0x1 << 2)
#define RT5671_M_ANC_DAC_R_SFT			2
#define RT5671_M_DAC_L1_STO_R			(0x1 << 1)
#define RT5671_M_DAC_L1_STO_R_SFT		1
#define RT5671_DAC_L1_STO_R_VOL_MASK		(0x1)
#define RT5671_DAC_L1_STO_R_VOL_SFT		0

/* Mono DAC Mixer Control (0x2b) */
#define RT5671_M_DAC_L1_MONO_L			(0x1 << 14)
#define RT5671_M_DAC_L1_MONO_L_SFT		14
#define RT5671_DAC_L1_MONO_L_VOL_MASK		(0x1 << 13)
#define RT5671_DAC_L1_MONO_L_VOL_SFT		13
#define RT5671_M_DAC_L2_MONO_L			(0x1 << 12)
#define RT5671_M_DAC_L2_MONO_L_SFT		12
#define RT5671_DAC_L2_MONO_L_VOL_MASK		(0x1 << 11)
#define RT5671_DAC_L2_MONO_L_VOL_SFT		11
#define RT5671_M_DAC_R2_MONO_L			(0x1 << 10)
#define RT5671_M_DAC_R2_MONO_L_SFT		10
#define RT5671_DAC_R2_MONO_L_VOL_MASK		(0x1 << 9)
#define RT5671_DAC_R2_MONO_L_VOL_SFT		9
#define RT5671_M_DAC_R1_MONO_R			(0x1 << 6)
#define RT5671_M_DAC_R1_MONO_R_SFT		6
#define RT5671_DAC_R1_MONO_R_VOL_MASK		(0x1 << 5)
#define RT5671_DAC_R1_MONO_R_VOL_SFT		5
#define RT5671_M_DAC_R2_MONO_R			(0x1 << 4)
#define RT5671_M_DAC_R2_MONO_R_SFT		4
#define RT5671_DAC_R2_MONO_R_VOL_MASK		(0x1 << 3)
#define RT5671_DAC_R2_MONO_R_VOL_SFT		3
#define RT5671_M_DAC_L2_MONO_R			(0x1 << 2)
#define RT5671_M_DAC_L2_MONO_R_SFT		2
#define RT5671_DAC_L2_MONO_R_VOL_MASK		(0x1 << 1)
#define RT5671_DAC_L2_MONO_R_VOL_SFT		1

/* Digital Mixer Control (0x2c) */
#define RT5671_M_STO_L_DAC_L			(0x1 << 15)
#define RT5671_M_STO_L_DAC_L_SFT		15
#define RT5671_STO_L_DAC_L_VOL_MASK		(0x1 << 14)
#define RT5671_STO_L_DAC_L_VOL_SFT		14
#define RT5671_M_DAC_L2_DAC_L			(0x1 << 13)
#define RT5671_M_DAC_L2_DAC_L_SFT		13
#define RT5671_DAC_L2_DAC_L_VOL_MASK		(0x1 << 12)
#define RT5671_DAC_L2_DAC_L_VOL_SFT		12
#define RT5671_M_STO_R_DAC_R			(0x1 << 11)
#define RT5671_M_STO_R_DAC_R_SFT		11
#define RT5671_STO_R_DAC_R_VOL_MASK		(0x1 << 10)
#define RT5671_STO_R_DAC_R_VOL_SFT		10
#define RT5671_M_DAC_R2_DAC_R			(0x1 << 9)
#define RT5671_M_DAC_R2_DAC_R_SFT		9
#define RT5671_DAC_R2_DAC_R_VOL_MASK		(0x1 << 8)
#define RT5671_DAC_R2_DAC_R_VOL_SFT		8
#define RT5671_M_DAC_R2_DAC_L			(0x1 << 7)
#define RT5671_M_DAC_R2_DAC_L_SFT		7
#define RT5671_DAC_R2_DAC_L_VOL_MASK		(0x1 << 6)
#define RT5671_DAC_R2_DAC_L_VOL_SFT		6
#define RT5671_M_DAC_L2_DAC_R			(0x1 << 5)
#define RT5671_M_DAC_L2_DAC_R_SFT		5
#define RT5671_DAC_L2_DAC_R_VOL_MASK		(0x1 << 4)
#define RT5671_DAC_L2_DAC_R_VOL_SFT		4

/* DSP Path Control 1 (0x2d) */
#define RT5671_RXDP_SEL_MASK			(0x7 << 13)
#define RT5671_RXDP_SEL_SFT			13
#define RT5671_RXDP_SRC_MASK			(0x1 << 15)
#define RT5671_RXDP_SRC_SFT			15
#define RT5671_RXDP_SRC_NOR			(0x0 << 15)
#define RT5671_RXDP_SRC_DIV3			(0x1 << 15)
#define RT5671_TXDP_SRC_MASK			(0x1 << 14)
#define RT5671_TXDP_SRC_SFT			14
#define RT5671_TXDP_SRC_NOR			(0x0 << 14)
#define RT5671_TXDP_SRC_DIV3			(0x1 << 14)
#define RT5671_DSP_UL_SEL			(0x1 << 1)
#define RT5671_DSP_UL_SFT			1
#define RT5671_DSP_DL_SEL			0x1
#define RT5671_DSP_DL_SFT			0

/* DSP Path Control 2 (0x2e) */
#define RT5671_TXDP_L_VOL_MASK			(0x7f << 8)
#define RT5671_TXDP_L_VOL_SFT			8
#define RT5671_TXDP_R_VOL_MASK			(0x7f)
#define RT5671_TXDP_R_VOL_SFT			0

/* Digital Interface Data Control (0x2f) */
#define RT5671_IF1_ADC2_IN_SEL			(0x1 << 15)
#define RT5671_IF1_ADC2_IN_SFT			15
#define RT5671_IF2_ADC_IN_MASK			(0x7 << 12)
#define RT5671_IF2_ADC_IN_SFT			12
#define RT5671_IF2_DAC_SEL_MASK			(0x3 << 10)
#define RT5671_IF2_DAC_SEL_SFT			10
#define RT5671_IF2_ADC_SEL_MASK			(0x3 << 8)
#define RT5671_IF2_ADC_SEL_SFT			8
#define RT5671_IF3_DAC_SEL_MASK			(0x3 << 6)
#define RT5671_IF3_DAC_SEL_SFT			6
#define RT5671_IF3_ADC_SEL_MASK			(0x3 << 4)
#define RT5671_IF3_ADC_SEL_SFT			4
#define RT5671_IF3_ADC_IN_MASK			(0x7)
#define RT5671_IF3_ADC_IN_SFT			0

/* Digital Interface Data Control (0x30) */
#define RT5671_IF4_ADC_IN_MASK			(0x3 << 4)
#define RT5671_IF4_ADC_IN_SFT			4

/* PDM Output Control (0x31) */
#define RT5671_PDM1_L_MASK			(0x1 << 15)
#define RT5671_PDM1_L_SFT			15
#define RT5671_M_PDM1_L				(0x1 << 14)
#define RT5671_M_PDM1_L_SFT			14
#define RT5671_PDM1_R_MASK			(0x1 << 13)
#define RT5671_PDM1_R_SFT			13
#define RT5671_M_PDM1_R				(0x1 << 12)
#define RT5671_M_PDM1_R_SFT			12
#define RT5671_PDM2_L_MASK			(0x1 << 11)
#define RT5671_PDM2_L_SFT			11
#define RT5671_M_PDM2_L				(0x1 << 10)
#define RT5671_M_PDM2_L_SFT			10
#define RT5671_PDM2_R_MASK			(0x1 << 9)
#define RT5671_PDM2_R_SFT			9
#define RT5671_M_PDM2_R				(0x1 << 8)
#define RT5671_M_PDM2_R_SFT			8
#define RT5671_PDM2_BUSY			(0x1 << 7)
#define RT5671_PDM1_BUSY			(0x1 << 6)
#define RT5671_PDM_PATTERN			(0x1 << 5)
#define RT5671_PDM_GAIN				(0x1 << 4)
#define RT5671_PDM_DIV_MASK			(0x3)

/* REC Left Mixer Control 1 (0x3b) */
#define RT5671_G_HP_L_RM_L_MASK			(0x7 << 13)
#define RT5671_G_HP_L_RM_L_SFT			13
#define RT5671_G_IN_L_RM_L_MASK			(0x7 << 10)
#define RT5671_G_IN_L_RM_L_SFT			10
#define RT5671_G_BST4_RM_L_MASK			(0x7 << 7)
#define RT5671_G_BST4_RM_L_SFT			7
#define RT5671_G_BST3_RM_L_MASK			(0x7 << 4)
#define RT5671_G_BST3_RM_L_SFT			4
#define RT5671_G_BST2_RM_L_MASK			(0x7 << 1)
#define RT5671_G_BST2_RM_L_SFT			1

/* REC Left Mixer Control 2 (0x3c) */
#define RT5671_G_BST1_RM_L_MASK			(0x7 << 13)
#define RT5671_G_BST1_RM_L_SFT			13
#define RT5671_M_IN_L_RM_L			(0x1 << 5)
#define RT5671_M_IN_L_RM_L_SFT			5
#define RT5671_M_BST4_RM_L			(0x1 << 4)
#define RT5671_M_BST4_RM_L_SFT			4
#define RT5671_M_BST3_RM_L			(0x1 << 3)
#define RT5671_M_BST3_RM_L_SFT			3
#define RT5671_M_BST2_RM_L			(0x1 << 2)
#define RT5671_M_BST2_RM_L_SFT			2
#define RT5671_M_BST1_RM_L			(0x1 << 1)
#define RT5671_M_BST1_RM_L_SFT			1

/* REC Right Mixer Control 1 (0x3d) */
#define RT5671_G_HP_R_RM_R_MASK			(0x7 << 13)
#define RT5671_G_HP_R_RM_R_SFT			13
#define RT5671_G_IN_R_RM_R_MASK			(0x7 << 10)
#define RT5671_G_IN_R_RM_R_SFT			10
#define RT5671_G_BST4_RM_R_MASK			(0x7 << 7)
#define RT5671_G_BST4_RM_R_SFT			7
#define RT5671_G_BST3_RM_R_MASK			(0x7 << 4)
#define RT5671_G_BST3_RM_R_SFT			4
#define RT5671_G_BST2_RM_R_MASK			(0x7 << 1)
#define RT5671_G_BST2_RM_R_SFT			1

/* REC Right Mixer Control 2 (0x3e) */
#define RT5671_G_BST1_RM_R_MASK			(0x7 << 13)
#define RT5671_G_BST1_RM_R_SFT			13
#define RT5671_M_IN_R_RM_R			(0x1 << 5)
#define RT5671_M_IN_R_RM_R_SFT			5
#define RT5671_M_BST4_RM_R			(0x1 << 4)
#define RT5671_M_BST4_RM_R_SFT			4
#define RT5671_M_BST3_RM_R			(0x1 << 3)
#define RT5671_M_BST3_RM_R_SFT			3
#define RT5671_M_BST2_RM_R			(0x1 << 2)
#define RT5671_M_BST2_RM_R_SFT			2
#define RT5671_M_BST1_RM_R			(0x1 << 1)
#define RT5671_M_BST1_RM_R_SFT			1

/* REC Mono Mixer Control 2 (0x40) */
#define RT5671_G_BST1_RM_M_MASK			(0x7 << 13)
#define RT5671_G_BST1_RM_M_SFT			13
#define RT5671_M_BST4_RM_M			(0x1 << 4)
#define RT5671_M_BST4_RM_M_SFT			4
#define RT5671_M_BST3_RM_M			(0x1 << 3)
#define RT5671_M_BST3_RM_M_SFT			3
#define RT5671_M_BST2_RM_M			(0x1 << 2)
#define RT5671_M_BST2_RM_M_SFT			2
#define RT5671_M_BST1_RM_M			(0x1 << 1)
#define RT5671_M_BST1_RM_M_SFT			1


/* HPMIX Control (0x45) */
#define RT5671_M_DAC2_HM			(0x1 << 15)
#define RT5671_M_DAC2_HM_SFT			15
#define RT5671_M_DAC1_HM			(0x1 << 14)
#define RT5671_M_DAC1_HM_SFT			14
#define RT5671_M_HPVOL_HM			(0x1 << 13)
#define RT5671_M_HPVOL_HM_SFT			13
#define RT5671_G_HPOMIX_MASK			(0x1 << 12)
#define RT5671_G_HPOMIX_SFT			12
#define RT5671_M_INR1_HMR			(0x1 << 3)
#define RT5671_M_INR1_HMR_SFT			3
#define RT5671_M_DACR1_HMR			(0x1 << 2)
#define RT5671_M_DACR1_HMR_SFT			2
#define RT5671_M_INL1_HML			(0x1 << 1)
#define RT5671_M_INL1_HML_SFT			1
#define RT5671_M_DACL1_HML			(0x1)
#define RT5671_M_DACL1_HML_SFT			0

/* Mono Output Mixer Control (0x4c) */
#define RT5671_M_DAC_L1_MA			(0x1 << 14)
#define RT5671_M_DAC_L1_MA_SFT			14
#define RT5671_M_OV_R_MM			(0x1 << 13)
#define RT5671_M_OV_R_MM_SFT			13
#define RT5671_M_OV_L_MM			(0x1 << 12)
#define RT5671_M_OV_L_MM_SFT			12
#define RT5671_G_MONOMIX_MASK			(0x1 << 10)
#define RT5671_G_MONOMIX_SFT			10
#define RT5671_M_DAC_R2_MM			(0x1 << 9)
#define RT5671_M_DAC_R2_MM_SFT			9
#define RT5671_M_DAC_L2_MM			(0x1 << 8)
#define RT5671_M_DAC_L2_MM_SFT			8
#define RT5671_M_BST4_MM			(0x1 << 7)
#define RT5671_M_BST4_MM_SFT			7

/* Output Left Mixer Control 1 (0x4d) */
#define RT5671_G_BST3_OM_L_MASK			(0x7 << 13)
#define RT5671_G_BST3_OM_L_SFT			13
#define RT5671_G_BST2_OM_L_MASK			(0x7 << 10)
#define RT5671_G_BST2_OM_L_SFT			10
#define RT5671_G_BST1_OM_L_MASK			(0x7 << 7)
#define RT5671_G_BST1_OM_L_SFT			7
#define RT5671_G_IN_L_OM_L_MASK			(0x7 << 4)
#define RT5671_G_IN_L_OM_L_SFT			4
#define RT5671_G_RM_L_OM_L_MASK			(0x7 << 1)
#define RT5671_G_RM_L_OM_L_SFT			1

/* Output Left Mixer Control 2 (0x4e) */
#define RT5671_G_DAC_R2_OM_L_MASK		(0x7 << 13)
#define RT5671_G_DAC_R2_OM_L_SFT		13
#define RT5671_G_DAC_L2_OM_L_MASK		(0x7 << 10)
#define RT5671_G_DAC_L2_OM_L_SFT		10
#define RT5671_G_DAC_L1_OM_L_MASK		(0x7 << 7)
#define RT5671_G_DAC_L1_OM_L_SFT		7

/* Output Left Mixer Control 3 (0x4f) */
#define RT5671_M_BST2_OM_L			(0x1 << 6)
#define RT5671_M_BST2_OM_L_SFT			6
#define RT5671_M_BST1_OM_L			(0x1 << 5)
#define RT5671_M_BST1_OM_L_SFT			5
#define RT5671_M_IN_L_OM_L			(0x1 << 4)
#define RT5671_M_IN_L_OM_L_SFT			4
#define RT5671_M_DAC_L2_OM_L			(0x1 << 1)
#define RT5671_M_DAC_L2_OM_L_SFT		1
#define RT5671_M_DAC_L1_OM_L			(0x1)
#define RT5671_M_DAC_L1_OM_L_SFT		0

/* Output Right Mixer Control 1 (0x50) */
#define RT5671_G_BST4_OM_R_MASK			(0x7 << 13)
#define RT5671_G_BST4_OM_R_SFT			13
#define RT5671_G_BST2_OM_R_MASK			(0x7 << 10)
#define RT5671_G_BST2_OM_R_SFT			10
#define RT5671_G_BST1_OM_R_MASK			(0x7 << 7)
#define RT5671_G_BST1_OM_R_SFT			7
#define RT5671_G_IN_R_OM_R_MASK			(0x7 << 4)
#define RT5671_G_IN_R_OM_R_SFT			4
#define RT5671_G_RM_R_OM_R_MASK			(0x7 << 1)
#define RT5671_G_RM_R_OM_R_SFT			1

/* Output Right Mixer Control 2 (0x51) */
#define RT5671_G_DAC_L2_OM_R_MASK		(0x7 << 13)
#define RT5671_G_DAC_L2_OM_R_SFT		13
#define RT5671_G_DAC_R2_OM_R_MASK		(0x7 << 10)
#define RT5671_G_DAC_R2_OM_R_SFT		10
#define RT5671_G_DAC_R1_OM_R_MASK		(0x7 << 7)
#define RT5671_G_DAC_R1_OM_R_SFT		7

/* Output Right Mixer Control 3 (0x52) */
#define RT5671_M_BST4_OM_R			(0x1 << 7)
#define RT5671_M_BST4_OM_R_SFT			7
#define RT5671_M_BST3_OM_R			(0x1 << 6)
#define RT5671_M_BST3_OM_R_SFT			6
#define RT5671_M_IN_R_OM_R			(0x1 << 4)
#define RT5671_M_IN_R_OM_R_SFT			4
#define RT5671_M_DAC_R2_OM_R			(0x1 << 1)
#define RT5671_M_DAC_R2_OM_R_SFT		1
#define RT5671_M_DAC_R1_OM_R			(0x1)
#define RT5671_M_DAC_R1_OM_R_SFT		0

/* LOUT Mixer Control (0x53) */
#define RT5671_M_DAC_L1_LM			(0x1 << 15)
#define RT5671_M_DAC_L1_LM_SFT			15
#define RT5671_M_DAC_R1_LM			(0x1 << 14)
#define RT5671_M_DAC_R1_LM_SFT			14
#define RT5671_M_OV_L_LM			(0x1 << 13)
#define RT5671_M_OV_L_LM_SFT			13
#define RT5671_M_OV_R_LM			(0x1 << 12)
#define RT5671_M_OV_R_LM_SFT			12
#define RT5671_G_LOUTMIX_MASK			(0x1 << 11)
#define RT5671_G_LOUTMIX_SFT			11

/* Power Management for Digital 1 (0x61) */
#define RT5671_PWR_I2S1				(0x1 << 15)
#define RT5671_PWR_I2S1_BIT			15
#define RT5671_PWR_I2S2				(0x1 << 14)
#define RT5671_PWR_I2S2_BIT			14
#define RT5671_PWR_I2S3				(0x1 << 13)
#define RT5671_PWR_I2S3_BIT			13
#define RT5671_PWR_DAC_L1			(0x1 << 12)
#define RT5671_PWR_DAC_L1_BIT			12
#define RT5671_PWR_DAC_R1			(0x1 << 11)
#define RT5671_PWR_DAC_R1_BIT			11
#define RT5671_PWR_I2S4				(0x1 << 10)
#define RT5671_PWR_I2S4_BIT			10
#define RT5671_PWR_DAC_L2			(0x1 << 7)
#define RT5671_PWR_DAC_L2_BIT			7
#define RT5671_PWR_DAC_R2			(0x1 << 6)
#define RT5671_PWR_DAC_R2_BIT			6
#define RT5671_PWR_ADC_3			(0x1 << 3)
#define RT5671_PWR_ADC_3_BIT			3
#define RT5671_PWR_ADC_L			(0x1 << 2)
#define RT5671_PWR_ADC_L_BIT			2
#define RT5671_PWR_ADC_R			(0x1 << 1)
#define RT5671_PWR_ADC_R_BIT			1
#define RT5671_PWR_CLS_D			(0x1)
#define RT5671_PWR_CLS_D_BIT			0

/* Power Management for Digital 2 (0x62) */
#define RT5671_PWR_ADC_S1F			(0x1 << 15)
#define RT5671_PWR_ADC_S1F_BIT			15
#define RT5671_PWR_ADC_MF_L			(0x1 << 14)
#define RT5671_PWR_ADC_MF_L_BIT			14
#define RT5671_PWR_ADC_MF_R			(0x1 << 13)
#define RT5671_PWR_ADC_MF_R_BIT			13
#define RT5671_PWR_I2S_DSP			(0x1 << 12)
#define RT5671_PWR_I2S_DSP_BIT			12
#define RT5671_PWR_DAC_S1F			(0x1 << 11)
#define RT5671_PWR_DAC_S1F_BIT			11
#define RT5671_PWR_DAC_MF_L			(0x1 << 10)
#define RT5671_PWR_DAC_MF_L_BIT			10
#define RT5671_PWR_DAC_MF_R			(0x1 << 9)
#define RT5671_PWR_DAC_MF_R_BIT			9
#define RT5671_PWR_ADC_S2F			(0x1 << 8)
#define RT5671_PWR_ADC_S2F_BIT			8
#define RT5671_PWR_PDM1				(0x1 << 7)
#define RT5671_PWR_PDM1_BIT			7
#define RT5671_PWR_PDM2				(0x1 << 6)
#define RT5671_PWR_PDM2_BIT			6

/* Power Management for Analog 1 (0x63) */
#define RT5671_PWR_VREF1			(0x1 << 15)
#define RT5671_PWR_VREF1_BIT			15
#define RT5671_PWR_FV1				(0x1 << 14)
#define RT5671_PWR_FV1_BIT			14
#define RT5671_PWR_MB				(0x1 << 13)
#define RT5671_PWR_MB_BIT			13
#define RT5671_PWR_LM				(0x1 << 12)
#define RT5671_PWR_LM_BIT			12
#define RT5671_PWR_BG				(0x1 << 11)
#define RT5671_PWR_BG_BIT			11
#define RT5671_PWR_MA				(0x1 << 10)
#define RT5671_PWR_MA_BIT			10
#define RT5671_PWR_MM				(0x1 << 9)
#define RT5671_PWR_MM_BIT			9
#define RT5671_PWR_HP_L				(0x1 << 7)
#define RT5671_PWR_HP_L_BIT			7
#define RT5671_PWR_HP_R				(0x1 << 6)
#define RT5671_PWR_HP_R_BIT			6
#define RT5671_PWR_HA				(0x1 << 5)
#define RT5671_PWR_HA_BIT			5
#define RT5671_PWR_VREF2			(0x1 << 4)
#define RT5671_PWR_VREF2_BIT			4
#define RT5671_PWR_FV2				(0x1 << 3)
#define RT5671_PWR_FV2_BIT			3
#define RT5671_LDO_SEL_MASK			(0x3)
#define RT5671_LDO_SEL_SFT			0

/* Power Management for Analog 2 (0x64) */
#define RT5671_PWR_BST1				(0x1 << 15)
#define RT5671_PWR_BST1_BIT			15
#define RT5671_PWR_BST2				(0x1 << 14)
#define RT5671_PWR_BST2_BIT			14
#define RT5671_PWR_BST3				(0x1 << 13)
#define RT5671_PWR_BST3_BIT			13
#define RT5671_PWR_BST4				(0x1 << 12)
#define RT5671_PWR_BST4_BIT			12
#define RT5671_PWR_MB1				(0x1 << 11)
#define RT5671_PWR_MB1_BIT			11
#define RT5671_PWR_MB2				(0x1 << 10)
#define RT5671_PWR_MB2_BIT			10
#define RT5671_PWR_PLL				(0x1 << 9)
#define RT5671_PWR_PLL_BIT			9
#define RT5671_PWR_BST1_P			(0x1 << 6)
#define RT5671_PWR_BST1_P_BIT			6
#define RT5671_PWR_BST2_P			(0x1 << 5)
#define RT5671_PWR_BST2_P_BIT			5
#define RT5671_PWR_BST3_P			(0x1 << 4)
#define RT5671_PWR_BST3_P_BIT			4
#define RT5671_PWR_BST4_P			(0x1 << 3)
#define RT5671_PWR_BST4_P_BIT			3
#define RT5671_PWR_JD1				(0x1 << 2)
#define RT5671_PWR_JD1_BIT			2
#define RT5671_PWR_JD				(0x1 << 1)
#define RT5671_PWR_JD_BIT			1

/* Power Management for Mixer (0x65) */
#define RT5671_PWR_OM_L				(0x1 << 15)
#define RT5671_PWR_OM_L_BIT			15
#define RT5671_PWR_OM_R				(0x1 << 14)
#define RT5671_PWR_OM_R_BIT			14
#define RT5671_PWR_RM_L				(0x1 << 11)
#define RT5671_PWR_RM_L_BIT			11
#define RT5671_PWR_RM_R				(0x1 << 10)
#define RT5671_PWR_RM_R_BIT			10
#define RT5671_PWR_RM_M				(0x1 << 9)
#define RT5671_PWR_RM_M_BIT			9

/* Power Management for Volume (0x66) */
#define RT5671_PWR_HV_L				(0x1 << 11)
#define RT5671_PWR_HV_L_BIT			11
#define RT5671_PWR_HV_R				(0x1 << 10)
#define RT5671_PWR_HV_R_BIT			10
#define RT5671_PWR_IN_L				(0x1 << 9)
#define RT5671_PWR_IN_L_BIT			9
#define RT5671_PWR_IN_R				(0x1 << 8)
#define RT5671_PWR_IN_R_BIT			8
#define RT5671_PWR_MIC_DET			(0x1 << 5)
#define RT5671_PWR_MIC_DET_BIT			5

/* I2S1/2/3 Audio Serial Data Port Control (0x70 0x71 0x72) */
#define RT5671_I2S_MS_MASK			(0x1 << 15)
#define RT5671_I2S_MS_SFT			15
#define RT5671_I2S_MS_M				(0x0 << 15)
#define RT5671_I2S_MS_S				(0x1 << 15)
#define RT5671_I2S_IF_MASK			(0x7 << 12)
#define RT5671_I2S_IF_SFT			12
#define RT5671_I2S_O_CP_MASK			(0x3 << 10)
#define RT5671_I2S_O_CP_SFT			10
#define RT5671_I2S_O_CP_OFF			(0x0 << 10)
#define RT5671_I2S_O_CP_U_LAW			(0x1 << 10)
#define RT5671_I2S_O_CP_A_LAW			(0x2 << 10)
#define RT5671_I2S_I_CP_MASK			(0x3 << 8)
#define RT5671_I2S_I_CP_SFT			8
#define RT5671_I2S_I_CP_OFF			(0x0 << 8)
#define RT5671_I2S_I_CP_U_LAW			(0x1 << 8)
#define RT5671_I2S_I_CP_A_LAW			(0x2 << 8)
#define RT5671_I2S_BP_MASK			(0x1 << 7)
#define RT5671_I2S_BP_SFT			7
#define RT5671_I2S_BP_NOR			(0x0 << 7)
#define RT5671_I2S_BP_INV			(0x1 << 7)
#define RT5671_I2S_DL_MASK			(0x3 << 2)
#define RT5671_I2S_DL_SFT			2
#define RT5671_I2S_DL_16			(0x0 << 2)
#define RT5671_I2S_DL_20			(0x1 << 2)
#define RT5671_I2S_DL_24			(0x2 << 2)
#define RT5671_I2S_DL_8				(0x3 << 2)
#define RT5671_I2S_DF_MASK			(0x3)
#define RT5671_I2S_DF_SFT			0
#define RT5671_I2S_DF_I2S			(0x0)
#define RT5671_I2S_DF_LEFT			(0x1)
#define RT5671_I2S_DF_PCM_A			(0x2)
#define RT5671_I2S_DF_PCM_B			(0x3)

/* I2S2 Audio Serial Data Port Control (0x71) */
#define RT5671_I2S2_SDI_MASK			(0x1 << 6)
#define RT5671_I2S2_SDI_SFT			6
#define RT5671_I2S2_SDI_I2S1			(0x0 << 6)
#define RT5671_I2S2_SDI_I2S2			(0x1 << 6)

/* ADC/DAC Clock Control 1 (0x73) */
#define RT5671_I2S_BCLK_MS1_MASK		(0x1 << 15)
#define RT5671_I2S_BCLK_MS1_SFT			15
#define RT5671_I2S_BCLK_MS1_32			(0x0 << 15)
#define RT5671_I2S_BCLK_MS1_64			(0x1 << 15)
#define RT5671_I2S_PD1_MASK			(0x7 << 12)
#define RT5671_I2S_PD1_SFT			12
#define RT5671_I2S_PD1_1			(0x0 << 12)
#define RT5671_I2S_PD1_2			(0x1 << 12)
#define RT5671_I2S_PD1_3			(0x2 << 12)
#define RT5671_I2S_PD1_4			(0x3 << 12)
#define RT5671_I2S_PD1_6			(0x4 << 12)
#define RT5671_I2S_PD1_8			(0x5 << 12)
#define RT5671_I2S_PD1_12			(0x6 << 12)
#define RT5671_I2S_PD1_16			(0x7 << 12)
#define RT5671_I2S_BCLK_MS2_MASK		(0x1 << 11)
#define RT5671_I2S_BCLK_MS2_SFT			11
#define RT5671_I2S_BCLK_MS2_32			(0x0 << 11)
#define RT5671_I2S_BCLK_MS2_64			(0x1 << 11)
#define RT5671_I2S_PD2_MASK			(0x7 << 8)
#define RT5671_I2S_PD2_SFT			8
#define RT5671_I2S_PD2_1			(0x0 << 8)
#define RT5671_I2S_PD2_2			(0x1 << 8)
#define RT5671_I2S_PD2_3			(0x2 << 8)
#define RT5671_I2S_PD2_4			(0x3 << 8)
#define RT5671_I2S_PD2_6			(0x4 << 8)
#define RT5671_I2S_PD2_8			(0x5 << 8)
#define RT5671_I2S_PD2_12			(0x6 << 8)
#define RT5671_I2S_PD2_16			(0x7 << 8)
#define RT5671_I2S_BCLK_MS3_MASK		(0x1 << 7)
#define RT5671_I2S_BCLK_MS3_SFT			7
#define RT5671_I2S_BCLK_MS3_32			(0x0 << 7)
#define RT5671_I2S_BCLK_MS3_64			(0x1 << 7)
#define RT5671_I2S_PD3_MASK			(0x7 << 4)
#define RT5671_I2S_PD3_SFT			4
#define RT5671_I2S_PD3_1			(0x0 << 4)
#define RT5671_I2S_PD3_2			(0x1 << 4)
#define RT5671_I2S_PD3_3			(0x2 << 4)
#define RT5671_I2S_PD3_4			(0x3 << 4)
#define RT5671_I2S_PD3_6			(0x4 << 4)
#define RT5671_I2S_PD3_8			(0x5 << 4)
#define RT5671_I2S_PD3_12			(0x6 << 4)
#define RT5671_I2S_PD3_16			(0x7 << 4)
#define RT5671_DAC_OSR_MASK			(0x3 << 2)
#define RT5671_DAC_OSR_SFT			2
#define RT5671_DAC_OSR_128			(0x0 << 2)
#define RT5671_DAC_OSR_64			(0x1 << 2)
#define RT5671_DAC_OSR_32			(0x2 << 2)
#define RT5671_DAC_OSR_16			(0x3 << 2)
#define RT5671_ADC_OSR_MASK			(0x3)
#define RT5671_ADC_OSR_SFT			0
#define RT5671_ADC_OSR_128			(0x0)
#define RT5671_ADC_OSR_64			(0x1)
#define RT5671_ADC_OSR_32			(0x2)
#define RT5671_ADC_OSR_16			(0x3)

/* ADC/DAC Clock Control 2 (0x74) */
#define RT5671_DAC_L_OSR_MASK			(0x3 << 14)
#define RT5671_DAC_L_OSR_SFT			14
#define RT5671_DAC_L_OSR_128			(0x0 << 14)
#define RT5671_DAC_L_OSR_64			(0x1 << 14)
#define RT5671_DAC_L_OSR_32			(0x2 << 14)
#define RT5671_DAC_L_OSR_16			(0x3 << 14)
#define RT5671_ADC_R_OSR_MASK			(0x3 << 12)
#define RT5671_ADC_R_OSR_SFT			12
#define RT5671_ADC_R_OSR_128			(0x0 << 12)
#define RT5671_ADC_R_OSR_64			(0x1 << 12)
#define RT5671_ADC_R_OSR_32			(0x2 << 12)
#define RT5671_ADC_R_OSR_16			(0x3 << 12)
#define RT5671_DAHPF_EN				(0x1 << 11)
#define RT5671_DAHPF_EN_SFT			11
#define RT5671_ADHPF_EN				(0x1 << 10)
#define RT5671_ADHPF_EN_SFT			10

/* Digital Microphone Control (0x75) */
#define RT5671_DMIC_1_EN_MASK			(0x1 << 15)
#define RT5671_DMIC_1_EN_SFT			15
#define RT5671_DMIC_1_DIS			(0x0 << 15)
#define RT5671_DMIC_1_EN			(0x1 << 15)
#define RT5671_DMIC_2_EN_MASK			(0x1 << 14)
#define RT5671_DMIC_2_EN_SFT			14
#define RT5671_DMIC_2_DIS			(0x0 << 14)
#define RT5671_DMIC_2_EN			(0x1 << 14)
#define RT5671_DMIC_1L_LH_MASK			(0x1 << 13)
#define RT5671_DMIC_1L_LH_SFT			13
#define RT5671_DMIC_1L_LH_FALLING		(0x0 << 13)
#define RT5671_DMIC_1L_LH_RISING		(0x1 << 13)
#define RT5671_DMIC_1R_LH_MASK			(0x1 << 12)
#define RT5671_DMIC_1R_LH_SFT			12
#define RT5671_DMIC_1R_LH_FALLING		(0x0 << 12)
#define RT5671_DMIC_1R_LH_RISING		(0x1 << 12)
#define RT5671_DMIC_2_DP_MASK			(0x1 << 10)
#define RT5671_DMIC_2_DP_SFT			10
#define RT5671_DMIC_2_DP_GPIO4			(0x0 << 10)
#define RT5671_DMIC_2_DP_IN1N			(0x1 << 10)
#define RT5671_DMIC_2L_LH_MASK			(0x1 << 9)
#define RT5671_DMIC_2L_LH_SFT			9
#define RT5671_DMIC_2L_LH_FALLING		(0x0 << 9)
#define RT5671_DMIC_2L_LH_RISING		(0x1 << 9)
#define RT5671_DMIC_2R_LH_MASK			(0x1 << 8)
#define RT5671_DMIC_2R_LH_SFT			8
#define RT5671_DMIC_2R_LH_FALLING		(0x0 << 8)
#define RT5671_DMIC_2R_LH_RISING		(0x1 << 8)
#define RT5671_DMIC_CLK_MASK			(0x7 << 5)
#define RT5671_DMIC_CLK_SFT			5
#define RT5671_DMIC_3_EN_MASK			(0x1 << 4)
#define RT5671_DMIC_3_EN_SFT			4
#define RT5671_DMIC_3_DIS			(0x0 << 4)
#define RT5671_DMIC_3_EN			(0x1 << 4)

#if REALTEK_USE_AMIC
#define RT5671_DMIC_1_DP_MASK			(0x1 << 11)
#define RT5671_DMIC_1_DP_SFT			11
#define RT5671_DMIC_1_DP_GPIO3			(0x0 << 11)
#define RT5671_DMIC_1_DP_GPIO7			(0x2 << 0)
#define RT5671_DMIC_1_DP_IN1P			(0x1 << 11)
#else
#define RT5671_DMIC_1_DP_MASK			(0x3 << 0)
#define RT5671_DMIC_1_DP_SFT			0
#define RT5671_DMIC_1_DP_GPIO6			(0x0 << 0)
#define RT5671_DMIC_1_DP_IN3P			(0x1 << 0)
#define RT5671_DMIC_1_DP_GPIO7			(0x2 << 0)
#endif

/* Clock Control 1 (0x7f) */
#define RT5671_I2S_BCLK_MS4_MASK		(0x1 << 15)
#define RT5671_I2S_BCLK_MS4_SFT			15
#define RT5671_I2S_BCLK_MS4_32			(0x0 << 15)
#define RT5671_I2S_BCLK_MS4_64			(0x1 << 15)
#define RT5671_I2S_PD4_MASK			(0x7 << 12)
#define RT5671_I2S_PD4_SFT			12
#define RT5671_I2S_PD4_1			(0x0 << 12)
#define RT5671_I2S_PD4_2			(0x1 << 12)
#define RT5671_I2S_PD4_3			(0x2 << 12)
#define RT5671_I2S_PD4_4			(0x3 << 12)
#define RT5671_I2S_PD4_6			(0x4 << 12)
#define RT5671_I2S_PD4_8			(0x5 << 12)
#define RT5671_I2S_PD4_12			(0x6 << 12)
#define RT5671_I2S_PD4_16			(0x7 << 12)

/* Global Clock Control (0x80) */
#define RT5671_SCLK_SRC_MASK			(0x3 << 14)
#define RT5671_SCLK_SRC_SFT			14
#define RT5671_SCLK_SRC_MCLK			(0x0 << 14)
#define RT5671_SCLK_SRC_PLL1			(0x1 << 14)
#define RT5671_SCLK_SRC_RCCLK			(0x2 << 14) /* 15MHz */
#define RT5671_PLL1_SRC_MASK			(0x7 << 11)
#define RT5671_PLL1_SRC_SFT			11
#define RT5671_PLL1_SRC_MCLK			(0x0 << 11)
#define RT5671_PLL1_SRC_BCLK1			(0x1 << 11)
#define RT5671_PLL1_SRC_BCLK2			(0x2 << 11)
#define RT5671_PLL1_SRC_BCLK3			(0x3 << 11)
#define RT5671_PLL1_SRC_BCLK4			(0x4 << 11)
#define RT5671_PLL1_SRC_Int			(0x5 << 11)
#define RT5671_PLL1_PD_MASK			(0x1 << 3)
#define RT5671_PLL1_PD_SFT			3
#define RT5671_PLL1_PD_1			(0x0 << 3)
#define RT5671_PLL1_PD_2			(0x1 << 3)

#define RT5671_PLL_INP_MAX			40000000
#define RT5671_PLL_INP_MIN			256000
/* PLL M/N/K Code Control 1 (0x81) */
#define RT5671_PLL_N_MAX			0x1ff
#define RT5671_PLL_N_MASK			(RT5671_PLL_N_MAX << 7)
#define RT5671_PLL_N_SFT			7
#define RT5671_PLL_K_MAX			0x1f
#define RT5671_PLL_K_MASK			(RT5671_PLL_K_MAX)
#define RT5671_PLL_K_SFT			0

/* PLL M/N/K Code Control 2 (0x82) */
#define RT5671_PLL_M_MAX			0xf
#define RT5671_PLL_M_MASK			(RT5671_PLL_M_MAX << 12)
#define RT5671_PLL_M_SFT			12
#define RT5671_PLL_M_BP				(0x1 << 11)
#define RT5671_PLL_M_BP_SFT			11

/* ASRC Control 1 (0x83) */
#define RT5671_STO_T_MASK			(0x1 << 15)
#define RT5671_STO_T_SFT			15
#define RT5671_STO_T_SCLK			(0x0 << 15)
#define RT5671_STO_T_LRCK1			(0x1 << 15)
#define RT5671_M1_T_MASK			(0x1 << 14)
#define RT5671_M1_T_SFT				14
#define RT5671_M1_T_I2S2			(0x0 << 14)
#define RT5671_M1_T_I2S2_D3			(0x1 << 14)
#define RT5671_I2S2_F_MASK			(0x1 << 12)
#define RT5671_I2S2_F_SFT			12
#define RT5671_I2S2_F_I2S2_D2			(0x0 << 12)
#define RT5671_I2S2_F_I2S1_TCLK			(0x1 << 12)
#define RT5671_DMIC_1_M_MASK			(0x1 << 9)
#define RT5671_DMIC_1_M_SFT			9
#define RT5671_DMIC_1_M_NOR			(0x0 << 9)
#define RT5671_DMIC_1_M_ASYN			(0x1 << 9)
#define RT5671_DMIC_2_M_MASK			(0x1 << 8)
#define RT5671_DMIC_2_M_SFT			8
#define RT5671_DMIC_2_M_NOR			(0x0 << 8)
#define RT5671_DMIC_2_M_ASYN			(0x1 << 8)

/* ASRC Control 2 (0x84) */
#define RT5671_MDA_L_M_MASK			(0x1 << 15)
#define RT5671_MDA_L_M_SFT			15
#define RT5671_MDA_L_M_NOR			(0x0 << 15)
#define RT5671_MDA_L_M_ASYN			(0x1 << 15)
#define RT5671_MDA_R_M_MASK			(0x1 << 14)
#define RT5671_MDA_R_M_SFT			14
#define RT5671_MDA_R_M_NOR			(0x0 << 14)
#define RT5671_MDA_R_M_ASYN			(0x1 << 14)
#define RT5671_MAD_L_M_MASK			(0x1 << 13)
#define RT5671_MAD_L_M_SFT			13
#define RT5671_MAD_L_M_NOR			(0x0 << 13)
#define RT5671_MAD_L_M_ASYN			(0x1 << 13)
#define RT5671_MAD_R_M_MASK			(0x1 << 12)
#define RT5671_MAD_R_M_SFT			12
#define RT5671_MAD_R_M_NOR			(0x0 << 12)
#define RT5671_MAD_R_M_ASYN			(0x1 << 12)
#define RT5671_ADC_M_MASK			(0x1 << 11)
#define RT5671_ADC_M_SFT			11
#define RT5671_ADC_M_NOR			(0x0 << 11)
#define RT5671_ADC_M_ASYN			(0x1 << 11)
#define RT5671_STO_DAC_M_MASK			(0x1 << 5)
#define RT5671_STO_DAC_M_SFT			5
#define RT5671_STO_DAC_M_NOR			(0x0 << 5)
#define RT5671_STO_DAC_M_ASYN			(0x1 << 5)
#define RT5671_I2S1_R_D_MASK			(0x1 << 4)
#define RT5671_I2S1_R_D_SFT			4
#define RT5671_I2S1_R_D_DIS			(0x0 << 4)
#define RT5671_I2S1_R_D_EN			(0x1 << 4)
#define RT5671_I2S2_R_D_MASK			(0x1 << 3)
#define RT5671_I2S2_R_D_SFT			3
#define RT5671_I2S2_R_D_DIS			(0x0 << 3)
#define RT5671_I2S2_R_D_EN			(0x1 << 3)
#define RT5671_PRE_SCLK_MASK			(0x3)
#define RT5671_PRE_SCLK_SFT			0
#define RT5671_PRE_SCLK_512			(0x0)
#define RT5671_PRE_SCLK_1024			(0x1)
#define RT5671_PRE_SCLK_2048			(0x2)

/* ASRC Control 3 (0x85) */
#define RT5671_I2S1_RATE_MASK			(0xf << 12)
#define RT5671_I2S1_RATE_SFT			12
#define RT5671_I2S2_RATE_MASK			(0xf << 8)
#define RT5671_I2S2_RATE_SFT			8

/* ASRC Control 4 (0x89) */
#define RT5671_I2S1_PD_MASK			(0x7 << 12)
#define RT5671_I2S1_PD_SFT			12
#define RT5671_I2S2_PD_MASK			(0x7 << 8)
#define RT5671_I2S2_PD_SFT			8

/* HPOUT Over Current Detection (0x8b) */
#define RT5671_HP_OVCD_MASK			(0x1 << 10)
#define RT5671_HP_OVCD_SFT			10
#define RT5671_HP_OVCD_DIS			(0x0 << 10)
#define RT5671_HP_OVCD_EN			(0x1 << 10)
#define RT5671_HP_OC_TH_MASK			(0x3 << 8)
#define RT5671_HP_OC_TH_SFT			8
#define RT5671_HP_OC_TH_90			(0x0 << 8)
#define RT5671_HP_OC_TH_105			(0x1 << 8)
#define RT5671_HP_OC_TH_120			(0x2 << 8)
#define RT5671_HP_OC_TH_135			(0x3 << 8)

/* Class D Over Current Control (0x8c) */
#define RT5671_CLSD_OC_MASK			(0x1 << 9)
#define RT5671_CLSD_OC_SFT			9
#define RT5671_CLSD_OC_PU			(0x0 << 9)
#define RT5671_CLSD_OC_PD			(0x1 << 9)
#define RT5671_AUTO_PD_MASK			(0x1 << 8)
#define RT5671_AUTO_PD_SFT			8
#define RT5671_AUTO_PD_DIS			(0x0 << 8)
#define RT5671_AUTO_PD_EN			(0x1 << 8)
#define RT5671_CLSD_OC_TH_MASK			(0x3f)
#define RT5671_CLSD_OC_TH_SFT			0

/* Class D Output Control (0x8d) */
#define RT5671_CLSD_RATIO_MASK			(0xf << 12)
#define RT5671_CLSD_RATIO_SFT			12
#define RT5671_CLSD_OM_MASK			(0x1 << 11)
#define RT5671_CLSD_OM_SFT			11
#define RT5671_CLSD_OM_MONO			(0x0 << 11)
#define RT5671_CLSD_OM_STO			(0x1 << 11)
#define RT5671_CLSD_SCH_MASK			(0x1 << 10)
#define RT5671_CLSD_SCH_SFT			10
#define RT5671_CLSD_SCH_L			(0x0 << 10)
#define RT5671_CLSD_SCH_S			(0x1 << 10)

/* Depop Mode Control 1 (0x8e) */
#define RT5671_SMT_TRIG_MASK			(0x1 << 15)
#define RT5671_SMT_TRIG_SFT			15
#define RT5671_SMT_TRIG_DIS			(0x0 << 15)
#define RT5671_SMT_TRIG_EN			(0x1 << 15)
#define RT5671_HP_L_SMT_MASK			(0x1 << 9)
#define RT5671_HP_L_SMT_SFT			9
#define RT5671_HP_L_SMT_DIS			(0x0 << 9)
#define RT5671_HP_L_SMT_EN			(0x1 << 9)
#define RT5671_HP_R_SMT_MASK			(0x1 << 8)
#define RT5671_HP_R_SMT_SFT			8
#define RT5671_HP_R_SMT_DIS			(0x0 << 8)
#define RT5671_HP_R_SMT_EN			(0x1 << 8)
#define RT5671_HP_CD_PD_MASK			(0x1 << 7)
#define RT5671_HP_CD_PD_SFT			7
#define RT5671_HP_CD_PD_DIS			(0x0 << 7)
#define RT5671_HP_CD_PD_EN			(0x1 << 7)
#define RT5671_RSTN_MASK			(0x1 << 6)
#define RT5671_RSTN_SFT				6
#define RT5671_RSTN_DIS				(0x0 << 6)
#define RT5671_RSTN_EN				(0x1 << 6)
#define RT5671_RSTP_MASK			(0x1 << 5)
#define RT5671_RSTP_SFT				5
#define RT5671_RSTP_DIS				(0x0 << 5)
#define RT5671_RSTP_EN				(0x1 << 5)
#define RT5671_HP_CO_MASK			(0x1 << 4)
#define RT5671_HP_CO_SFT			4
#define RT5671_HP_CO_DIS			(0x0 << 4)
#define RT5671_HP_CO_EN				(0x1 << 4)
#define RT5671_HP_CP_MASK			(0x1 << 3)
#define RT5671_HP_CP_SFT			3
#define RT5671_HP_CP_PD				(0x0 << 3)
#define RT5671_HP_CP_PU				(0x1 << 3)
#define RT5671_HP_SG_MASK			(0x1 << 2)
#define RT5671_HP_SG_SFT			2
#define RT5671_HP_SG_DIS			(0x0 << 2)
#define RT5671_HP_SG_EN				(0x1 << 2)
#define RT5671_HP_DP_MASK			(0x1 << 1)
#define RT5671_HP_DP_SFT			1
#define RT5671_HP_DP_PD				(0x0 << 1)
#define RT5671_HP_DP_PU				(0x1 << 1)
#define RT5671_HP_CB_MASK			(0x1)
#define RT5671_HP_CB_SFT			0
#define RT5671_HP_CB_PD				(0x0)
#define RT5671_HP_CB_PU				(0x1)

/* Depop Mode Control 2 (0x8f) */
#define RT5671_DEPOP_MASK			(0x1 << 13)
#define RT5671_DEPOP_SFT			13
#define RT5671_DEPOP_AUTO			(0x0 << 13)
#define RT5671_DEPOP_MAN			(0x1 << 13)
#define RT5671_RAMP_MASK			(0x1 << 12)
#define RT5671_RAMP_SFT				12
#define RT5671_RAMP_DIS				(0x0 << 12)
#define RT5671_RAMP_EN				(0x1 << 12)
#define RT5671_BPS_MASK				(0x1 << 11)
#define RT5671_BPS_SFT				11
#define RT5671_BPS_DIS				(0x0 << 11)
#define RT5671_BPS_EN				(0x1 << 11)
#define RT5671_FAST_UPDN_MASK			(0x1 << 10)
#define RT5671_FAST_UPDN_SFT			10
#define RT5671_FAST_UPDN_DIS			(0x0 << 10)
#define RT5671_FAST_UPDN_EN			(0x1 << 10)
#define RT5671_MRES_MASK			(0x3 << 8)
#define RT5671_MRES_SFT				8
#define RT5671_MRES_15MO			(0x0 << 8)
#define RT5671_MRES_25MO			(0x1 << 8)
#define RT5671_MRES_35MO			(0x2 << 8)
#define RT5671_MRES_45MO			(0x3 << 8)
#define RT5671_VLO_MASK				(0x1 << 7)
#define RT5671_VLO_SFT				7
#define RT5671_VLO_3V				(0x0 << 7)
#define RT5671_VLO_32V				(0x1 << 7)
#define RT5671_DIG_DP_MASK			(0x1 << 6)
#define RT5671_DIG_DP_SFT			6
#define RT5671_DIG_DP_DIS			(0x0 << 6)
#define RT5671_DIG_DP_EN			(0x1 << 6)
#define RT5671_DP_TH_MASK			(0x3 << 4)
#define RT5671_DP_TH_SFT			4

/* Depop Mode Control 3 (0x90) */
#define RT5671_CP_SYS_MASK			(0x7 << 12)
#define RT5671_CP_SYS_SFT			12
#define RT5671_CP_FQ1_MASK			(0x7 << 8)
#define RT5671_CP_FQ1_SFT			8
#define RT5671_CP_FQ2_MASK			(0x7 << 4)
#define RT5671_CP_FQ2_SFT			4
#define RT5671_CP_FQ3_MASK			(0x7)
#define RT5671_CP_FQ3_SFT			0
#define RT5671_CP_FQ_1_5_KHZ			0
#define RT5671_CP_FQ_3_KHZ			1
#define RT5671_CP_FQ_6_KHZ			2
#define RT5671_CP_FQ_12_KHZ			3
#define RT5671_CP_FQ_24_KHZ			4
#define RT5671_CP_FQ_48_KHZ			5
#define RT5671_CP_FQ_96_KHZ			6
#define RT5671_CP_FQ_192_KHZ			7

/* HPOUT charge pump (0x91) */
#define RT5671_OSW_L_MASK			(0x1 << 11)
#define RT5671_OSW_L_SFT			11
#define RT5671_OSW_L_DIS			(0x0 << 11)
#define RT5671_OSW_L_EN				(0x1 << 11)
#define RT5671_OSW_R_MASK			(0x1 << 10)
#define RT5671_OSW_R_SFT			10
#define RT5671_OSW_R_DIS			(0x0 << 10)
#define RT5671_OSW_R_EN				(0x1 << 10)
#define RT5671_PM_HP_MASK			(0x3 << 8)
#define RT5671_PM_HP_SFT			8
#define RT5671_PM_HP_LV				(0x0 << 8)
#define RT5671_PM_HP_MV				(0x1 << 8)
#define RT5671_PM_HP_HV				(0x2 << 8)
#define RT5671_IB_HP_MASK			(0x3 << 6)
#define RT5671_IB_HP_SFT			6
#define RT5671_IB_HP_125IL			(0x0 << 6)
#define RT5671_IB_HP_25IL			(0x1 << 6)
#define RT5671_IB_HP_5IL			(0x2 << 6)
#define RT5671_IB_HP_1IL			(0x3 << 6)

/* PV detection and SPK gain control (0x92) */
#define RT5671_PVDD_DET_MASK			(0x1 << 15)
#define RT5671_PVDD_DET_SFT			15
#define RT5671_PVDD_DET_DIS			(0x0 << 15)
#define RT5671_PVDD_DET_EN			(0x1 << 15)
#define RT5671_SPK_AG_MASK			(0x1 << 14)
#define RT5671_SPK_AG_SFT			14
#define RT5671_SPK_AG_DIS			(0x0 << 14)
#define RT5671_SPK_AG_EN			(0x1 << 14)

/* Micbias Control (0x93) */
#define RT5671_MIC1_BS_MASK			(0x1 << 15)
#define RT5671_MIC1_BS_SFT			15
#define RT5671_MIC1_BS_9AV			(0x0 << 15)
#define RT5671_MIC1_BS_75AV			(0x1 << 15)
#define RT5671_MIC2_BS_MASK			(0x1 << 14)
#define RT5671_MIC2_BS_SFT			14
#define RT5671_MIC2_BS_9AV			(0x0 << 14)
#define RT5671_MIC2_BS_75AV			(0x1 << 14)
#define RT5671_MIC1_CLK_MASK			(0x1 << 13)
#define RT5671_MIC1_CLK_SFT			13
#define RT5671_MIC1_CLK_DIS			(0x0 << 13)
#define RT5671_MIC1_CLK_EN			(0x1 << 13)
#define RT5671_MIC2_CLK_MASK			(0x1 << 12)
#define RT5671_MIC2_CLK_SFT			12
#define RT5671_MIC2_CLK_DIS			(0x0 << 12)
#define RT5671_MIC2_CLK_EN			(0x1 << 12)
#define RT5671_MIC1_OVCD_MASK			(0x1 << 11)
#define RT5671_MIC1_OVCD_SFT			11
#define RT5671_MIC1_OVCD_DIS			(0x0 << 11)
#define RT5671_MIC1_OVCD_EN			(0x1 << 11)
#define RT5671_MIC1_OVTH_MASK			(0x3 << 9)
#define RT5671_MIC1_OVTH_SFT			9
#define RT5671_MIC1_OVTH_600UA			(0x0 << 9)
#define RT5671_MIC1_OVTH_1500UA			(0x1 << 9)
#define RT5671_MIC1_OVTH_2000UA			(0x2 << 9)
#define RT5671_MIC2_OVCD_MASK			(0x1 << 8)
#define RT5671_MIC2_OVCD_SFT			8
#define RT5671_MIC2_OVCD_DIS			(0x0 << 8)
#define RT5671_MIC2_OVCD_EN			(0x1 << 8)
#define RT5671_MIC2_OVTH_MASK			(0x3 << 6)
#define RT5671_MIC2_OVTH_SFT			6
#define RT5671_MIC2_OVTH_600UA			(0x0 << 6)
#define RT5671_MIC2_OVTH_1500UA			(0x1 << 6)
#define RT5671_MIC2_OVTH_2000UA			(0x2 << 6)
#define RT5671_PWR_MB_MASK			(0x1 << 5)
#define RT5671_PWR_MB_SFT			5
#define RT5671_PWR_MB_PD			(0x0 << 5)
#define RT5671_PWR_MB_PU			(0x1 << 5)
#define RT5671_PWR_CLK25M_MASK			(0x1 << 4)
#define RT5671_PWR_CLK25M_SFT			4
#define RT5671_PWR_CLK25M_PD			(0x0 << 4)
#define RT5671_PWR_CLK25M_PU			(0x1 << 4)

/* VAD Control 4 (0x9d) */
#define RT5671_VAD_SEL_MASK			(0x3 << 8)
#define RT5671_VAD_SEL_SFT			8

/* EQ Control 1 (0xb0) */
#define RT5671_EQ_SRC_MASK			(0x1 << 15)
#define RT5671_EQ_SRC_SFT			15
#define RT5671_EQ_SRC_DAC			(0x0 << 15)
#define RT5671_EQ_SRC_ADC			(0x1 << 15)
#define RT5671_EQ_UPD				(0x1 << 14)
#define RT5671_EQ_UPD_BIT			14
#define RT5671_EQ_CD_MASK			(0x1 << 13)
#define RT5671_EQ_CD_SFT			13
#define RT5671_EQ_CD_DIS			(0x0 << 13)
#define RT5671_EQ_CD_EN				(0x1 << 13)
#define RT5671_EQ_DITH_MASK			(0x3 << 8)
#define RT5671_EQ_DITH_SFT			8
#define RT5671_EQ_DITH_NOR			(0x0 << 8)
#define RT5671_EQ_DITH_LSB			(0x1 << 8)
#define RT5671_EQ_DITH_LSB_1			(0x2 << 8)
#define RT5671_EQ_DITH_LSB_2			(0x3 << 8)

/* EQ Control 2 (0xb1) */
#define RT5671_EQ_HPF1_M_MASK			(0x1 << 8)
#define RT5671_EQ_HPF1_M_SFT			8
#define RT5671_EQ_HPF1_M_HI			(0x0 << 8)
#define RT5671_EQ_HPF1_M_1ST			(0x1 << 8)
#define RT5671_EQ_LPF1_M_MASK			(0x1 << 7)
#define RT5671_EQ_LPF1_M_SFT			7
#define RT5671_EQ_LPF1_M_LO			(0x0 << 7)
#define RT5671_EQ_LPF1_M_1ST			(0x1 << 7)
#define RT5671_EQ_HPF2_MASK			(0x1 << 6)
#define RT5671_EQ_HPF2_SFT			6
#define RT5671_EQ_HPF2_DIS			(0x0 << 6)
#define RT5671_EQ_HPF2_EN			(0x1 << 6)
#define RT5671_EQ_HPF1_MASK			(0x1 << 5)
#define RT5671_EQ_HPF1_SFT			5
#define RT5671_EQ_HPF1_DIS			(0x0 << 5)
#define RT5671_EQ_HPF1_EN			(0x1 << 5)
#define RT5671_EQ_BPF4_MASK			(0x1 << 4)
#define RT5671_EQ_BPF4_SFT			4
#define RT5671_EQ_BPF4_DIS			(0x0 << 4)
#define RT5671_EQ_BPF4_EN			(0x1 << 4)
#define RT5671_EQ_BPF3_MASK			(0x1 << 3)
#define RT5671_EQ_BPF3_SFT			3
#define RT5671_EQ_BPF3_DIS			(0x0 << 3)
#define RT5671_EQ_BPF3_EN			(0x1 << 3)
#define RT5671_EQ_BPF2_MASK			(0x1 << 2)
#define RT5671_EQ_BPF2_SFT			2
#define RT5671_EQ_BPF2_DIS			(0x0 << 2)
#define RT5671_EQ_BPF2_EN			(0x1 << 2)
#define RT5671_EQ_BPF1_MASK			(0x1 << 1)
#define RT5671_EQ_BPF1_SFT			1
#define RT5671_EQ_BPF1_DIS			(0x0 << 1)
#define RT5671_EQ_BPF1_EN			(0x1 << 1)
#define RT5671_EQ_LPF_MASK			(0x1)
#define RT5671_EQ_LPF_SFT			0
#define RT5671_EQ_LPF_DIS			(0x0)
#define RT5671_EQ_LPF_EN			(0x1)
#define RT5671_EQ_CTRL_MASK			(0x7f)

/* Memory Test (0xb2) */
#define RT5671_MT_MASK				(0x1 << 15)
#define RT5671_MT_SFT				15
#define RT5671_MT_DIS				(0x0 << 15)
#define RT5671_MT_EN				(0x1 << 15)

/* DRC/AGC Control 1 (0xb4) */
#define RT5671_DRC_AGC_P_MASK			(0x1 << 15)
#define RT5671_DRC_AGC_P_SFT			15
#define RT5671_DRC_AGC_P_DAC			(0x0 << 15)
#define RT5671_DRC_AGC_P_ADC			(0x1 << 15)
#define RT5671_DRC_AGC_MASK			(0x1 << 14)
#define RT5671_DRC_AGC_SFT			14
#define RT5671_DRC_AGC_DIS			(0x0 << 14)
#define RT5671_DRC_AGC_EN			(0x1 << 14)
#define RT5671_DRC_AGC_UPD			(0x1 << 13)
#define RT5671_DRC_AGC_UPD_BIT			13
#define RT5671_DRC_AGC_AR_MASK			(0x1f << 8)
#define RT5671_DRC_AGC_AR_SFT			8
#define RT5671_DRC_AGC_R_MASK			(0x7 << 5)
#define RT5671_DRC_AGC_R_SFT			5
#define RT5671_DRC_AGC_R_48K			(0x1 << 5)
#define RT5671_DRC_AGC_R_96K			(0x2 << 5)
#define RT5671_DRC_AGC_R_192K			(0x3 << 5)
#define RT5671_DRC_AGC_R_441K			(0x5 << 5)
#define RT5671_DRC_AGC_R_882K			(0x6 << 5)
#define RT5671_DRC_AGC_R_1764K			(0x7 << 5)
#define RT5671_DRC_AGC_RC_MASK			(0x1f)
#define RT5671_DRC_AGC_RC_SFT			0

/* DRC/AGC Control 2 (0xb5) */
#define RT5671_DRC_AGC_POB_MASK			(0x3f << 8)
#define RT5671_DRC_AGC_POB_SFT			8
#define RT5671_DRC_AGC_CP_MASK			(0x1 << 7)
#define RT5671_DRC_AGC_CP_SFT			7
#define RT5671_DRC_AGC_CP_DIS			(0x0 << 7)
#define RT5671_DRC_AGC_CP_EN			(0x1 << 7)
#define RT5671_DRC_AGC_CPR_MASK			(0x3 << 5)
#define RT5671_DRC_AGC_CPR_SFT			5
#define RT5671_DRC_AGC_CPR_1_1			(0x0 << 5)
#define RT5671_DRC_AGC_CPR_1_2			(0x1 << 5)
#define RT5671_DRC_AGC_CPR_1_3			(0x2 << 5)
#define RT5671_DRC_AGC_CPR_1_4			(0x3 << 5)
#define RT5671_DRC_AGC_PRB_MASK			(0x1f)
#define RT5671_DRC_AGC_PRB_SFT			0

/* DRC/AGC Control 3 (0xb6) */
#define RT5671_DRC_AGC_NGB_MASK			(0xf << 12)
#define RT5671_DRC_AGC_NGB_SFT			12
#define RT5671_DRC_AGC_TAR_MASK			(0x1f << 7)
#define RT5671_DRC_AGC_TAR_SFT			7
#define RT5671_DRC_AGC_NG_MASK			(0x1 << 6)
#define RT5671_DRC_AGC_NG_SFT			6
#define RT5671_DRC_AGC_NG_DIS			(0x0 << 6)
#define RT5671_DRC_AGC_NG_EN			(0x1 << 6)
#define RT5671_DRC_AGC_NGH_MASK			(0x1 << 5)
#define RT5671_DRC_AGC_NGH_SFT			5
#define RT5671_DRC_AGC_NGH_DIS			(0x0 << 5)
#define RT5671_DRC_AGC_NGH_EN			(0x1 << 5)
#define RT5671_DRC_AGC_NGT_MASK			(0x1f)
#define RT5671_DRC_AGC_NGT_SFT			0

/* Jack Detect Control (0xbb) */
#define RT5671_JD_MASK				(0x7 << 13)
#define RT5671_JD_SFT				13
#define RT5671_JD_DIS				(0x0 << 13)
#define RT5671_JD_GPIO1				(0x1 << 13)
#define RT5671_JD_JD1_IN4P			(0x2 << 13)
#define RT5671_JD_JD2_IN4N			(0x3 << 13)
#define RT5671_JD_GPIO2				(0x4 << 13)
#define RT5671_JD_GPIO3				(0x5 << 13)
#define RT5671_JD_GPIO4				(0x6 << 13)
#define RT5671_JD_HP_MASK			(0x1 << 11)
#define RT5671_JD_HP_SFT			11
#define RT5671_JD_HP_DIS			(0x0 << 11)
#define RT5671_JD_HP_EN				(0x1 << 11)
#define RT5671_JD_HP_TRG_MASK			(0x1 << 10)
#define RT5671_JD_HP_TRG_SFT			10
#define RT5671_JD_HP_TRG_LO			(0x0 << 10)
#define RT5671_JD_HP_TRG_HI			(0x1 << 10)
#define RT5671_JD_SPL_MASK			(0x1 << 9)
#define RT5671_JD_SPL_SFT			9
#define RT5671_JD_SPL_DIS			(0x0 << 9)
#define RT5671_JD_SPL_EN			(0x1 << 9)
#define RT5671_JD_SPL_TRG_MASK			(0x1 << 8)
#define RT5671_JD_SPL_TRG_SFT			8
#define RT5671_JD_SPL_TRG_LO			(0x0 << 8)
#define RT5671_JD_SPL_TRG_HI			(0x1 << 8)
#define RT5671_JD_SPR_MASK			(0x1 << 7)
#define RT5671_JD_SPR_SFT			7
#define RT5671_JD_SPR_DIS			(0x0 << 7)
#define RT5671_JD_SPR_EN			(0x1 << 7)
#define RT5671_JD_SPR_TRG_MASK			(0x1 << 6)
#define RT5671_JD_SPR_TRG_SFT			6
#define RT5671_JD_SPR_TRG_LO			(0x0 << 6)
#define RT5671_JD_SPR_TRG_HI			(0x1 << 6)
#define RT5671_JD_MO_MASK			(0x1 << 5)
#define RT5671_JD_MO_SFT			5
#define RT5671_JD_MO_DIS			(0x0 << 5)
#define RT5671_JD_MO_EN				(0x1 << 5)
#define RT5671_JD_MO_TRG_MASK			(0x1 << 4)
#define RT5671_JD_MO_TRG_SFT			4
#define RT5671_JD_MO_TRG_LO			(0x0 << 4)
#define RT5671_JD_MO_TRG_HI			(0x1 << 4)
#define RT5671_JD_LO_MASK			(0x1 << 3)
#define RT5671_JD_LO_SFT			3
#define RT5671_JD_LO_DIS			(0x0 << 3)
#define RT5671_JD_LO_EN				(0x1 << 3)
#define RT5671_JD_LO_TRG_MASK			(0x1 << 2)
#define RT5671_JD_LO_TRG_SFT			2
#define RT5671_JD_LO_TRG_LO			(0x0 << 2)
#define RT5671_JD_LO_TRG_HI			(0x1 << 2)
#define RT5671_JD1_IN4P_MASK			(0x1 << 1)
#define RT5671_JD1_IN4P_SFT			1
#define RT5671_JD1_IN4P_DIS			(0x0 << 1)
#define RT5671_JD1_IN4P_EN			(0x1 << 1)
#define RT5671_JD2_IN4N_MASK			(0x1)
#define RT5671_JD2_IN4N_SFT			0
#define RT5671_JD2_IN4N_DIS			(0x0)
#define RT5671_JD2_IN4N_EN			(0x1)

/* IRQ Control 1 (0xbd) */
#define RT5671_IRQ_JD_MASK			(0x1 << 15)
#define RT5671_IRQ_JD_SFT			15
#define RT5671_IRQ_JD_BP			(0x0 << 15)
#define RT5671_IRQ_JD_NOR			(0x1 << 15)
#define RT5671_IRQ_OT_MASK			(0x1 << 14)
#define RT5671_IRQ_OT_SFT			14
#define RT5671_IRQ_OT_BP			(0x0 << 14)
#define RT5671_IRQ_OT_NOR			(0x1 << 14)
#define RT5671_JD_STKY_MASK			(0x1 << 13)
#define RT5671_JD_STKY_SFT			13
#define RT5671_JD_STKY_DIS			(0x0 << 13)
#define RT5671_JD_STKY_EN			(0x1 << 13)
#define RT5671_OT_STKY_MASK			(0x1 << 12)
#define RT5671_OT_STKY_SFT			12
#define RT5671_OT_STKY_DIS			(0x0 << 12)
#define RT5671_OT_STKY_EN			(0x1 << 12)
#define RT5671_JD_P_MASK			(0x1 << 11)
#define RT5671_JD_P_SFT				11
#define RT5671_JD_P_NOR				(0x0 << 11)
#define RT5671_JD_P_INV				(0x1 << 11)
#define RT5671_OT_P_MASK			(0x1 << 10)
#define RT5671_OT_P_SFT				10
#define RT5671_OT_P_NOR				(0x0 << 10)
#define RT5671_OT_P_INV				(0x1 << 10)

/* IRQ Control 2 (0xbe) */
#define RT5671_IRQ_MB1_OC_MASK			(0x1 << 15)
#define RT5671_IRQ_MB1_OC_SFT			15
#define RT5671_IRQ_MB1_OC_BP			(0x0 << 15)
#define RT5671_IRQ_MB1_OC_NOR			(0x1 << 15)
#define RT5671_IRQ_MB2_OC_MASK			(0x1 << 14)
#define RT5671_IRQ_MB2_OC_SFT			14
#define RT5671_IRQ_MB2_OC_BP			(0x0 << 14)
#define RT5671_IRQ_MB2_OC_NOR			(0x1 << 14)
#define RT5671_MB1_OC_STKY_MASK			(0x1 << 11)
#define RT5671_MB1_OC_STKY_SFT			11
#define RT5671_MB1_OC_STKY_DIS			(0x0 << 11)
#define RT5671_MB1_OC_STKY_EN			(0x1 << 11)
#define RT5671_MB2_OC_STKY_MASK			(0x1 << 10)
#define RT5671_MB2_OC_STKY_SFT			10
#define RT5671_MB2_OC_STKY_DIS			(0x0 << 10)
#define RT5671_MB2_OC_STKY_EN			(0x1 << 10)
#define RT5671_MB1_OC_P_MASK			(0x1 << 7)
#define RT5671_MB1_OC_P_SFT			7
#define RT5671_MB1_OC_P_NOR			(0x0 << 7)
#define RT5671_MB1_OC_P_INV			(0x1 << 7)
#define RT5671_MB2_OC_P_MASK			(0x1 << 6)
#define RT5671_MB2_OC_P_SFT			6
#define RT5671_MB2_OC_P_NOR			(0x0 << 6)
#define RT5671_MB2_OC_P_INV			(0x1 << 6)
#define RT5671_MB1_OC_CLR			(0x1 << 3)
#define RT5671_MB1_OC_CLR_SFT			3
#define RT5671_MB2_OC_CLR			(0x1 << 2)
#define RT5671_MB2_OC_CLR_SFT			2

/* GPIO Control 1 (0xc0) */
#define RT5671_GP1_PIN_MASK			(0x1 << 15)
#define RT5671_GP1_PIN_SFT			15
#define RT5671_GP1_PIN_GPIO1			(0x0 << 15)
#define RT5671_GP1_PIN_IRQ			(0x1 << 15)
#define RT5671_GP2_PIN_MASK			(0x1 << 14)
#define RT5671_GP2_PIN_SFT			14
#define RT5671_GP2_PIN_GPIO2			(0x0 << 14)
#define RT5671_GP2_PIN_DMIC1_SCL		(0x1 << 14)
#define RT5671_GP3_PIN_MASK			(0x3 << 12)
#define RT5671_GP3_PIN_SFT			12
#define RT5671_GP3_PIN_GPIO3			(0x0 << 12)
#define RT5671_GP3_PIN_DMIC1_SDA		(0x1 << 12)
#define RT5671_GP3_PIN_IRQ			(0x2 << 12)
#define RT5671_GP4_PIN_MASK			(0x1 << 11)
#define RT5671_GP4_PIN_SFT			11
#define RT5671_GP4_PIN_GPIO4			(0x0 << 11)
#define RT5671_GP4_PIN_DMIC2_SDA		(0x1 << 11)
#define RT5671_DP_SIG_MASK			(0x1 << 10)
#define RT5671_DP_SIG_SFT			10
#define RT5671_DP_SIG_TEST			(0x0 << 10)
#define RT5671_DP_SIG_AP			(0x1 << 10)
#define RT5671_GPIO_M_MASK			(0x1 << 9)
#define RT5671_GPIO_M_SFT			9
#define RT5671_GPIO_M_FLT			(0x0 << 9)
#define RT5671_GPIO_M_PH			(0x1 << 9)
#define RT5671_I2S2_PIN_MASK			(0x1 << 8)
#define RT5671_I2S2_PIN_SFT			8
#define RT5671_I2S2_PIN_I2S			(0x0 << 8)
#define RT5671_I2S2_PIN_GPIO			(0x1 << 8)
#define RT5671_GP5_PIN_MASK			(0x1 << 7)
#define RT5671_GP5_PIN_SFT			7
#define RT5671_GP5_PIN_GPIO5			(0x0 << 7)
#define RT5671_GP5_PIN_DMIC3_SCL		(0x1 << 7)
#define RT5671_GP6_PIN_MASK			(0x1 << 6)
#define RT5671_GP6_PIN_SFT			6
#define RT5671_GP6_PIN_GPIO6			(0x0 << 6)
#define RT5671_GP6_PIN_DMIC1_SDA		(0x1 << 6)
#define RT5671_GP7_PIN_MASK			(0x3 << 4)
#define RT5671_GP7_PIN_SFT			4
#define RT5671_GP7_PIN_GPIO7			(0x0 << 4)
#define RT5671_GP7_PIN_DMIC1_SDA		(0x1 << 4)
#define RT5671_GP7_PIN_PDM_SCL2			(0x2 << 4)
#define RT5671_GP8_PIN_MASK			(0x1 << 3)
#define RT5671_GP8_PIN_SFT			3
#define RT5671_GP8_PIN_GPIO8			(0x0 << 3)
#define RT5671_GP8_PIN_DMIC2_SDA		(0x1 << 3)
#define RT5671_GP9_PIN_MASK			(0x1 << 2)
#define RT5671_GP9_PIN_SFT			2
#define RT5671_GP9_PIN_GPIO9			(0x0 << 2)
#define RT5671_GP9_PIN_DMIC3_SDA		(0x1 << 2)
#define RT5671_GP10_PIN_MASK			(0x3)
#define RT5671_GP10_PIN_SFT			0
#define RT5671_GP10_PIN_GPIO9			(0x0)
#define RT5671_GP10_PIN_DMIC3_SDA		(0x1)
#define RT5671_GP10_PIN_PDM_ADT2		(0x2)

/* GPIO Control 3 (0xc2) */
#define RT5671_GP4_PF_MASK			(0x1 << 11)
#define RT5671_GP4_PF_SFT			11
#define RT5671_GP4_PF_IN			(0x0 << 11)
#define RT5671_GP4_PF_OUT			(0x1 << 11)
#define RT5671_GP4_OUT_MASK			(0x1 << 10)
#define RT5671_GP4_OUT_SFT			10
#define RT5671_GP4_OUT_LO			(0x0 << 10)
#define RT5671_GP4_OUT_HI			(0x1 << 10)
#define RT5671_GP4_P_MASK			(0x1 << 9)
#define RT5671_GP4_P_SFT			9
#define RT5671_GP4_P_NOR			(0x0 << 9)
#define RT5671_GP4_P_INV			(0x1 << 9)
#define RT5671_GP3_PF_MASK			(0x1 << 8)
#define RT5671_GP3_PF_SFT			8
#define RT5671_GP3_PF_IN			(0x0 << 8)
#define RT5671_GP3_PF_OUT			(0x1 << 8)
#define RT5671_GP3_OUT_MASK			(0x1 << 7)
#define RT5671_GP3_OUT_SFT			7
#define RT5671_GP3_OUT_LO			(0x0 << 7)
#define RT5671_GP3_OUT_HI			(0x1 << 7)
#define RT5671_GP3_P_MASK			(0x1 << 6)
#define RT5671_GP3_P_SFT			6
#define RT5671_GP3_P_NOR			(0x0 << 6)
#define RT5671_GP3_P_INV			(0x1 << 6)
#define RT5671_GP2_PF_MASK			(0x1 << 5)
#define RT5671_GP2_PF_SFT			5
#define RT5671_GP2_PF_IN			(0x0 << 5)
#define RT5671_GP2_PF_OUT			(0x1 << 5)
#define RT5671_GP2_OUT_MASK			(0x1 << 4)
#define RT5671_GP2_OUT_SFT			4
#define RT5671_GP2_OUT_LO			(0x0 << 4)
#define RT5671_GP2_OUT_HI			(0x1 << 4)
#define RT5671_GP2_P_MASK			(0x1 << 3)
#define RT5671_GP2_P_SFT			3
#define RT5671_GP2_P_NOR			(0x0 << 3)
#define RT5671_GP2_P_INV			(0x1 << 3)
#define RT5671_GP1_PF_MASK			(0x1 << 2)
#define RT5671_GP1_PF_SFT			2
#define RT5671_GP1_PF_IN			(0x0 << 2)
#define RT5671_GP1_PF_OUT			(0x1 << 2)
#define RT5671_GP1_OUT_MASK			(0x1 << 1)
#define RT5671_GP1_OUT_SFT			1
#define RT5671_GP1_OUT_LO			(0x0 << 1)
#define RT5671_GP1_OUT_HI			(0x1 << 1)
#define RT5671_GP1_P_MASK			(0x1)
#define RT5671_GP1_P_SFT			0
#define RT5671_GP1_P_NOR			(0x0)
#define RT5671_GP1_P_INV			(0x1)

/* Scramble Function (0xcd) */
#define RT5671_SCB_KEY_MASK			(0xff)
#define RT5671_SCB_KEY_SFT			0

/* Scramble Control (0xce) */
#define RT5671_SCB_SWAP_MASK			(0x1 << 15)
#define RT5671_SCB_SWAP_SFT			15
#define RT5671_SCB_SWAP_DIS			(0x0 << 15)
#define RT5671_SCB_SWAP_EN			(0x1 << 15)
#define RT5671_SCB_MASK				(0x1 << 14)
#define RT5671_SCB_SFT				14
#define RT5671_SCB_DIS				(0x0 << 14)
#define RT5671_SCB_EN				(0x1 << 14)

/* Baseback Control (0xcf) */
#define RT5671_BB_MASK				(0x1 << 15)
#define RT5671_BB_SFT				15
#define RT5671_BB_DIS				(0x0 << 15)
#define RT5671_BB_EN				(0x1 << 15)
#define RT5671_BB_CT_MASK			(0x7 << 12)
#define RT5671_BB_CT_SFT			12
#define RT5671_BB_CT_A				(0x0 << 12)
#define RT5671_BB_CT_B				(0x1 << 12)
#define RT5671_BB_CT_C				(0x2 << 12)
#define RT5671_BB_CT_D				(0x3 << 12)
#define RT5671_M_BB_L_MASK			(0x1 << 9)
#define RT5671_M_BB_L_SFT			9
#define RT5671_M_BB_R_MASK			(0x1 << 8)
#define RT5671_M_BB_R_SFT			8
#define RT5671_M_BB_HPF_L_MASK			(0x1 << 7)
#define RT5671_M_BB_HPF_L_SFT			7
#define RT5671_M_BB_HPF_R_MASK			(0x1 << 6)
#define RT5671_M_BB_HPF_R_SFT			6
#define RT5671_G_BB_BST_MASK			(0x3f)
#define RT5671_G_BB_BST_SFT			0

/* MP3 Plus Control 1 (0xd0) */
#define RT5671_M_MP3_L_MASK			(0x1 << 15)
#define RT5671_M_MP3_L_SFT			15
#define RT5671_M_MP3_R_MASK			(0x1 << 14)
#define RT5671_M_MP3_R_SFT			14
#define RT5671_M_MP3_MASK			(0x1 << 13)
#define RT5671_M_MP3_SFT			13
#define RT5671_M_MP3_DIS			(0x0 << 13)
#define RT5671_M_MP3_EN				(0x1 << 13)
#define RT5671_EG_MP3_MASK			(0x1f << 8)
#define RT5671_EG_MP3_SFT			8
#define RT5671_MP3_HLP_MASK			(0x1 << 7)
#define RT5671_MP3_HLP_SFT			7
#define RT5671_MP3_HLP_DIS			(0x0 << 7)
#define RT5671_MP3_HLP_EN			(0x1 << 7)
#define RT5671_M_MP3_ORG_L_MASK			(0x1 << 6)
#define RT5671_M_MP3_ORG_L_SFT			6
#define RT5671_M_MP3_ORG_R_MASK			(0x1 << 5)
#define RT5671_M_MP3_ORG_R_SFT			5

/* MP3 Plus Control 2 (0xd1) */
#define RT5671_MP3_WT_MASK			(0x1 << 13)
#define RT5671_MP3_WT_SFT			13
#define RT5671_MP3_WT_1_4			(0x0 << 13)
#define RT5671_MP3_WT_1_2			(0x1 << 13)
#define RT5671_OG_MP3_MASK			(0x1f << 8)
#define RT5671_OG_MP3_SFT			8
#define RT5671_HG_MP3_MASK			(0x3f)
#define RT5671_HG_MP3_SFT			0

/* 3D HP Control 1 (0xd2) */
#define RT5671_3D_CF_MASK			(0x1 << 15)
#define RT5671_3D_CF_SFT			15
#define RT5671_3D_CF_DIS			(0x0 << 15)
#define RT5671_3D_CF_EN				(0x1 << 15)
#define RT5671_3D_HP_MASK			(0x1 << 14)
#define RT5671_3D_HP_SFT			14
#define RT5671_3D_HP_DIS			(0x0 << 14)
#define RT5671_3D_HP_EN				(0x1 << 14)
#define RT5671_3D_BT_MASK			(0x1 << 13)
#define RT5671_3D_BT_SFT			13
#define RT5671_3D_BT_DIS			(0x0 << 13)
#define RT5671_3D_BT_EN				(0x1 << 13)
#define RT5671_3D_1F_MIX_MASK			(0x3 << 11)
#define RT5671_3D_1F_MIX_SFT			11
#define RT5671_3D_HP_M_MASK			(0x1 << 10)
#define RT5671_3D_HP_M_SFT			10
#define RT5671_3D_HP_M_SUR			(0x0 << 10)
#define RT5671_3D_HP_M_FRO			(0x1 << 10)
#define RT5671_M_3D_HRTF_MASK			(0x1 << 9)
#define RT5671_M_3D_HRTF_SFT			9
#define RT5671_M_3D_D2H_MASK			(0x1 << 8)
#define RT5671_M_3D_D2H_SFT			8
#define RT5671_M_3D_D2R_MASK			(0x1 << 7)
#define RT5671_M_3D_D2R_SFT			7
#define RT5671_M_3D_REVB_MASK			(0x1 << 6)
#define RT5671_M_3D_REVB_SFT			6

/* Adjustable high pass filter control 1 (0xd3) */
#define RT5671_2ND_HPF_MASK			(0x1 << 15)
#define RT5671_2ND_HPF_SFT			15
#define RT5671_2ND_HPF_DIS			(0x0 << 15)
#define RT5671_2ND_HPF_EN			(0x1 << 15)
#define RT5671_HPF_CF_L_MASK			(0x7 << 12)
#define RT5671_HPF_CF_L_SFT			12
#define RT5671_1ST_HPF_MASK			(0x1 << 11)
#define RT5671_1ST_HPF_SFT			11
#define RT5671_1ST_HPF_DIS			(0x0 << 11)
#define RT5671_1ST_HPF_EN			(0x1 << 11)
#define RT5671_HPF_CF_R_MASK			(0x7 << 8)
#define RT5671_HPF_CF_R_SFT			8
#define RT5671_ZD_T_MASK			(0x3 << 6)
#define RT5671_ZD_T_SFT				6
#define RT5671_ZD_F_MASK			(0x3 << 4)
#define RT5671_ZD_F_SFT				4
#define RT5671_ZD_F_IM				(0x0 << 4)
#define RT5671_ZD_F_ZC_IM			(0x1 << 4)
#define RT5671_ZD_F_ZC_IOD			(0x2 << 4)
#define RT5671_ZD_F_UN				(0x3 << 4)

/* HP calibration control and Amp detection (0xd6) */
#define RT5671_SI_DAC_MASK			(0x1 << 11)
#define RT5671_SI_DAC_SFT			11
#define RT5671_SI_DAC_AUTO			(0x0 << 11)
#define RT5671_SI_DAC_TEST			(0x1 << 11)
#define RT5671_DC_CAL_M_MASK			(0x1 << 10)
#define RT5671_DC_CAL_M_SFT			10
#define RT5671_DC_CAL_M_CAL			(0x0 << 10)
#define RT5671_DC_CAL_M_NOR			(0x1 << 10)
#define RT5671_DC_CAL_MASK			(0x1 << 9)
#define RT5671_DC_CAL_SFT			9
#define RT5671_DC_CAL_DIS			(0x0 << 9)
#define RT5671_DC_CAL_EN			(0x1 << 9)
#define RT5671_HPD_RCV_MASK			(0x7 << 6)
#define RT5671_HPD_RCV_SFT			6
#define RT5671_HPD_PS_MASK			(0x1 << 5)
#define RT5671_HPD_PS_SFT			5
#define RT5671_HPD_PS_DIS			(0x0 << 5)
#define RT5671_HPD_PS_EN			(0x1 << 5)
#define RT5671_CAL_M_MASK			(0x1 << 4)
#define RT5671_CAL_M_SFT			4
#define RT5671_CAL_M_DEP			(0x0 << 4)
#define RT5671_CAL_M_CAL			(0x1 << 4)
#define RT5671_CAL_MASK				(0x1 << 3)
#define RT5671_CAL_SFT				3
#define RT5671_CAL_DIS				(0x0 << 3)
#define RT5671_CAL_EN				(0x1 << 3)
#define RT5671_CAL_TEST_MASK			(0x1 << 2)
#define RT5671_CAL_TEST_SFT			2
#define RT5671_CAL_TEST_DIS			(0x0 << 2)
#define RT5671_CAL_TEST_EN			(0x1 << 2)
#define RT5671_CAL_P_MASK			(0x3)
#define RT5671_CAL_P_SFT			0
#define RT5671_CAL_P_NONE			(0x0)
#define RT5671_CAL_P_CAL			(0x1)
#define RT5671_CAL_P_DAC_CAL			(0x2)

/* Soft volume and zero cross control 1 (0xd9) */
#define RT5671_SV_MASK				(0x1 << 15)
#define RT5671_SV_SFT				15
#define RT5671_SV_DIS				(0x0 << 15)
#define RT5671_SV_EN				(0x1 << 15)
#define RT5671_SPO_SV_MASK			(0x1 << 14)
#define RT5671_SPO_SV_SFT			14
#define RT5671_SPO_SV_DIS			(0x0 << 14)
#define RT5671_SPO_SV_EN			(0x1 << 14)
#define RT5671_OUT_SV_MASK			(0x1 << 13)
#define RT5671_OUT_SV_SFT			13
#define RT5671_OUT_SV_DIS			(0x0 << 13)
#define RT5671_OUT_SV_EN			(0x1 << 13)
#define RT5671_HP_SV_MASK			(0x1 << 12)
#define RT5671_HP_SV_SFT			12
#define RT5671_HP_SV_DIS			(0x0 << 12)
#define RT5671_HP_SV_EN				(0x1 << 12)
#define RT5671_ZCD_DIG_MASK			(0x1 << 11)
#define RT5671_ZCD_DIG_SFT			11
#define RT5671_ZCD_DIG_DIS			(0x0 << 11)
#define RT5671_ZCD_DIG_EN			(0x1 << 11)
#define RT5671_ZCD_MASK				(0x1 << 10)
#define RT5671_ZCD_SFT				10
#define RT5671_ZCD_PD				(0x0 << 10)
#define RT5671_ZCD_PU				(0x1 << 10)
#define RT5671_M_ZCD_MASK			(0x3f << 4)
#define RT5671_M_ZCD_SFT			4
#define RT5671_M_ZCD_RM_L			(0x1 << 9)
#define RT5671_M_ZCD_RM_R			(0x1 << 8)
#define RT5671_M_ZCD_SM_L			(0x1 << 7)
#define RT5671_M_ZCD_SM_R			(0x1 << 6)
#define RT5671_M_ZCD_OM_L			(0x1 << 5)
#define RT5671_M_ZCD_OM_R			(0x1 << 4)
#define RT5671_SV_DLY_MASK			(0xf)
#define RT5671_SV_DLY_SFT			0

/* Soft volume and zero cross control 2 (0xda) */
#define RT5671_ZCD_HP_MASK			(0x1 << 15)
#define RT5671_ZCD_HP_SFT			15
#define RT5671_ZCD_HP_DIS			(0x0 << 15)
#define RT5671_ZCD_HP_EN			(0x1 << 15)


/* Codec Private Register definition */
/* 3D Speaker Control (0x63) */
#define RT5671_3D_SPK_MASK			(0x1 << 15)
#define RT5671_3D_SPK_SFT			15
#define RT5671_3D_SPK_DIS			(0x0 << 15)
#define RT5671_3D_SPK_EN			(0x1 << 15)
#define RT5671_3D_SPK_M_MASK			(0x3 << 13)
#define RT5671_3D_SPK_M_SFT			13
#define RT5671_3D_SPK_CG_MASK			(0x1f << 8)
#define RT5671_3D_SPK_CG_SFT			8
#define RT5671_3D_SPK_SG_MASK			(0x1f)
#define RT5671_3D_SPK_SG_SFT			0

/* Wind Noise Detection Control 1 (0x6c) */
#define RT5671_WND_MASK				(0x1 << 15)
#define RT5671_WND_SFT				15
#define RT5671_WND_DIS				(0x0 << 15)
#define RT5671_WND_EN				(0x1 << 15)

/* Wind Noise Detection Control 2 (0x6d) */
#define RT5671_WND_FC_NW_MASK			(0x3f << 10)
#define RT5671_WND_FC_NW_SFT			10
#define RT5671_WND_FC_WK_MASK			(0x3f << 4)
#define RT5671_WND_FC_WK_SFT			4

/* Wind Noise Detection Control 3 (0x6e) */
#define RT5671_HPF_FC_MASK			(0x3f << 6)
#define RT5671_HPF_FC_SFT			6
#define RT5671_WND_FC_ST_MASK			(0x3f)
#define RT5671_WND_FC_ST_SFT			0

/* Wind Noise Detection Control 4 (0x6f) */
#define RT5671_WND_TH_LO_MASK			(0x3ff)
#define RT5671_WND_TH_LO_SFT			0

/* Wind Noise Detection Control 5 (0x70) */
#define RT5671_WND_TH_HI_MASK			(0x3ff)
#define RT5671_WND_TH_HI_SFT			0

/* Wind Noise Detection Control 8 (0x73) */
#define RT5671_WND_WIND_MASK			(0x1 << 13) /* Read-Only */
#define RT5671_WND_WIND_SFT			13
#define RT5671_WND_STRONG_MASK			(0x1 << 12) /* Read-Only */
#define RT5671_WND_STRONG_SFT			12
enum {
	RT5671_NO_WIND,
	RT5671_BREEZE,
	RT5671_STORM,
};

/* Dipole Speaker Interface (0x75) */
#define RT5671_DP_ATT_MASK			(0x3 << 14)
#define RT5671_DP_ATT_SFT			14
#define RT5671_DP_SPK_MASK			(0x1 << 10)
#define RT5671_DP_SPK_SFT			10
#define RT5671_DP_SPK_DIS			(0x0 << 10)
#define RT5671_DP_SPK_EN			(0x1 << 10)

/* EQ Pre Volume Control (0xb3) */
#define RT5671_EQ_PRE_VOL_MASK			(0xffff)
#define RT5671_EQ_PRE_VOL_SFT			0

/* EQ Post Volume Control (0xb4) */
#define RT5671_EQ_PST_VOL_MASK			(0xffff)
#define RT5671_EQ_PST_VOL_SFT			0

/* Jack Detect Control 3 (0xf8) */
#define RT5671_CMP_MIC_IN_DET_MASK		(0x7 << 12)
#define RT5671_JD_CBJ_EN			(0x1 << 7)
#define RT5671_JD_CBJ_POL			(0x1 << 6)
#define RT5671_JD_TRI_CBJ_SEL_MASK		(0x7 << 3)
#define RT5671_JD_TRI_CBJ_SEL_SFT		(3)
#define RT5671_JD_TRI_HPO_SEL_MASK		(0x7)
#define RT5671_JD_TRI_HPO_SEL_SFT		(0)
#define RT5671_JD_F_GPIO_JD1			(0x0)
#define RT5671_JD_F_JD1_1			(0x1)
#define RT5671_JD_F_JD1_2			(0x2)
#define RT5671_JD_F_JD2				(0x3)
#define RT5671_JD_F_JD3				(0x4)
#define RT5671_JD_F_GPIO_JD2			(0x5)
#define RT5671_JD_F_MX0B_12			(0x6)

/* Digital Misc Control (0xfa) */
#define RT5671_RST_DSP				(0x1 << 13)
#define RT5671_IF1_ADC1_IN1_SEL			(0x1 << 12)
#define RT5671_IF1_ADC1_IN1_SFT			12
#define RT5671_IF1_ADC1_IN2_SEL			(0x1 << 11)
#define RT5671_IF1_ADC1_IN2_SFT			11
#define RT5671_IF1_ADC2_IN1_SEL			(0x1 << 10)
#define RT5671_IF1_ADC2_IN1_SFT			10

/* General Control2 (0xfb) */
#define RT5671_RXDC_SRC_MASK			(0x1 << 7)
#define RT5671_RXDC_SRC_STO			(0x0 << 7)
#define RT5671_RXDC_SRC_MONO			(0x1 << 7)
#define RT5671_RXDC_SRC_SFT			(7)
#define RT5671_RXDP2_SEL_MASK			(0x1 << 3)
#define RT5671_RXDP2_SEL_IF2			(0x0 << 3)
#define RT5671_RXDP2_SEL_ADC			(0x1 << 3)
#define RT5671_RXDP2_SEL_SFT			(3)


/* Vendor ID (0xfd) */
#define RT5671_VER_C				0x2
#define RT5671_VER_D				0x3


/* Volume Rescale */
#define RT5671_VOL_RSCL_MAX 0x27
#define RT5671_VOL_RSCL_RANGE 0x1F
/* Debug String Length */
#define RT5671_REG_DISP_LEN 23

#define RT5671_NO_JACK		BIT(0)
#define RT5671_HEADSET_DET	BIT(1)
#define RT5671_HEADPHO_DET	BIT(2)

int rt5671_headset_detect(struct snd_soc_codec *codec, int jack_insert);
int rt5671_check_interrupt_event(struct snd_soc_codec *codec, int *data);
#if REALTEK_USE_AMIC
int rt5671_gpio2_control(struct snd_soc_codec *codec, int on); 
#else
int rt5671_gpio8_control(struct snd_soc_codec *codec, int on); 
#endif
/* System Clock Source */
enum {
	RT5671_SCLK_S_MCLK,
	RT5671_SCLK_S_PLL1,
	RT5671_SCLK_S_RCCLK,
};

/* PLL1 Source */
enum {
	RT5671_PLL1_S_MCLK,
	RT5671_PLL1_S_BCLK1,
	RT5671_PLL1_S_BCLK2,
	RT5671_PLL1_S_BCLK3,
	RT5671_PLL1_S_BCLK4,
};

enum {
	RT5671_AIF1,
	RT5671_AIF2,
	RT5671_AIF3,
	RT5671_AIF4,
	RT5671_AIFS,
};

enum {
	RT5671_BTN_EVENT = BIT(0), /* Button Push */
	RT5671_BR_EVENT = BIT(1), /* Button Release */
	RT5671_J_IN_EVENT = BIT(2), /* Jack insert */
	RT5671_J_OUT_EVENT = BIT(3), /* Jack evulse */
	RT5671_VAD_EVENT = BIT(4), /* VAD Triggered */
	RT5671_UN_EVENT = BIT(5), /* Unknown */
};

#define RT5671_U_IF1 (0x1)
#define RT5671_U_IF2 (0x1 << 1)
#define RT5671_U_IF3 (0x1 << 2)
#define RT5671_U_IF4 (0x1 << 3)

enum {
	RT5671_DMIC_DIS,
	RT5671_DMIC1,
	RT5671_DMIC2,
	RT5671_DMIC3,
};

struct rt5671_pll_code {
	bool m_bp; /* Indicates bypass m code or not. */
	int m_code;
	int n_code;
	int k_code;
};

struct rt5671_priv {
	struct snd_soc_codec *codec;
	struct delayed_work patch_work;
	struct regmap *regmap;

	int aif_pu;
	int sysclk;
	int sysclk_src;
	int lrck[RT5671_AIFS];
	int bclk[RT5671_AIFS];
	int master[RT5671_AIFS];

	int pll_src;
	int pll_in;
	int pll_out;

	int dmic_en;
	bool combo_jack_en;
	int dsp_sw; /* expected parameter setting */
	bool dsp_play_pass;
	bool dsp_rec_pass;
	bool vad_en;
	int stream;
	int jack_type;
};

#endif /* __RT5671_H__ */
/* LGE_CHANGE_E */
