#include "ym3438.h"

/// @brief YM3438 Master Clock Frequency
#define YM3438_MCLK             8000000 // 8 MHz

/// @brief Cycles to wait after address write mode
#define YM3438_W1_CYCLES        240     // Rounded up to be safe

/// @brief Cycles to wait after writing data to upper registers
#define YM3438_W2_UPPER_CYCLES  1020    // Rounded up to be safe

/// @brief Cycles to wait after writing to lower registers
#define YM3438_W2_LOWER_CYCLES  600     // Rounded up to be safe

void YM3438_AddressWriteMode(uint8_t address, uint8_t bank) {

}

void YM3438_DataWriteMode(uint8_t data, uint8_t bank) {

}

void YM3438_RegisterWrite(uint8_t reg, uint8_t bank, uint8_t data) {

}

void YM3438_BlockingWaitW1() {

}

void YM3438_BlockingWaitW2() {

}