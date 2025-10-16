/**
 * @file        ym3438.h
 * @brief       Header file for ym3438 driver
 * @details     This is the application specific driver for ym3438
 * @author      yumenegi
 * @date        2025
 * @copyright   ponco2
 */

#ifndef YM3438_H_
#define YM3438_H_

#include <stdint.h>

void YM3438_AddressWriteMode(uint8_t address, uint8_t bank);

void YM3438_DataWriteMode(uint8_t data, uint8_t bank);

void YM3438_RegisterWrite(uint8_t reg, uint8_t bank, uint8_t data);

void YM3438_BlockingWaitW1();

void YM3438_BlockingWaitW2();

#endif // YM3438_H_