/**
 ******************************************************************************
 * @file           : psg.h
 * @brief          : Programmable Sound Generator Driver Header
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 YUMENEGI INDUSTRIES.
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef PSG_H_
#define PSG_H_

#include <stdint.h>

/// @brief SN76489AN channels
#define SN76489AN_TONE_CHANNEL_0 0
#define SN76489AN_TONE_CHANNEL_1 1
#define SN76489AN_TONE_CHANNEL_2 2
#define SN76489AN_NOISE_CHANNEL 3

void PSG_Init(void);
void PSG_Write(uint8_t payload);
void PSG_SetFrequency(uint8_t channel, uint16_t freq);
void PSG_SetAttenuation(uint8_t channel, uint8_t attenuation);
void PSG_SetNoise(uint8_t type, uint8_t shift_rate);

#endif // PSG_H_