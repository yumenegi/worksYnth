#include "psg.h"

#include "cmsis_gcc.h"
#include "main.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>

#define PSG_WAIT_CYCLE 100

/// @brief Are we using chip enable?
// #define SN76489AN_USE_CE

/// @brief Defines SN76489AN Constants
/// @brief Currently set at 3.5MHz
#define SN76489AN_REF_CLK 4500000

///@brief Macro to convert hertz 10-bit wave number
#define SN76489AN_CALC_TONE_TMR_SET(f) (SN76489AN_REF_CLK / f / 32)

/// @brief SN76489 data byte indicator
#define SN76489AN_LATCH_BYTE 1 << 7

/// @brief SN76489 channel selector bit
#define SN76489AN_FREQ_SEL 0
#define SN76489AN_ATTEN_SEL 1 << 4
#define SN76489AN_SHIFT_RATE_SEL 0

/// @brief SN76489 Noise Channel Config
#define SN76489AN_NOISE_PERIODIC 0
#define SN76489AN_NOISE_WHITE 1 << 2

/// @brief SN76489 bit masks
#define SN76489AN_LATCH_MASK 0b1111
#define SN76489AN_DATA_FREQ_MASK 0b111111
#define SN76489AN_DATA_ATTEN_MASK 0b1111
#define SN76489AN_LATCH_SHIFT_RATE_MASK 0b11

static void PSG_Wait() {
  for (volatile int i = 0; i < PSG_WAIT_CYCLE; i++) {
    __NOP();
  }
}

void PSG_Init(void) {
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0F);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_1, 0x0F);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_2, 0x0F);
  PSG_SetAttenuation(SN76489AN_NOISE_CHANNEL, 0x0F);
}

void PSG_Write(uint8_t payload) {
  // Set the 8 data pins based on the bits in the 'data' byte
  // Note that D0 is MSB
  HAL_GPIO_WritePin(SN_D0_GPIO_PORT, SN_D0_PIN,
                    (payload & 0x80) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SN_D1_GPIO_PORT, SN_D1_PIN,
                    (payload & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SN_D2_GPIO_PORT, SN_D2_PIN,
                    (payload & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SN_D3_GPIO_PORT, SN_D3_PIN,
                    (payload & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SN_D4_GPIO_PORT, SN_D4_PIN,
                    (payload & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SN_D5_GPIO_PORT, SN_D5_PIN,
                    (payload & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SN_D6_GPIO_PORT, SN_D6_PIN,
                    (payload & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SN_D7_GPIO_PORT, SN_D7_PIN,
                    (payload & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);

  // Pulse the Write Enable pin (high -> low -> high) to latch the data
  HAL_GPIO_WritePin(SN_WE_GPIO_PORT, SN_WE_PIN, GPIO_PIN_RESET);
  PSG_Wait(); // Hold WE low for a minimum time (see datasheet)
  HAL_GPIO_WritePin(SN_WE_GPIO_PORT, SN_WE_PIN, GPIO_PIN_SET);
  PSG_Wait(); // Hold WE low for a minimum time (see datasheet)
}

void PSG_SetFrequency(uint8_t channel, uint16_t freq) {
  // Calculate frequency
  uint16_t wave_number = SN76489AN_CALC_TONE_TMR_SET(freq);

  // Construct payload and send latch byte
  uint8_t payload = SN76489AN_LATCH_BYTE | (channel << 5) | SN76489AN_FREQ_SEL |
                    ((uint8_t)(wave_number & SN76489AN_LATCH_MASK));
  PSG_Write(payload);
  PSG_Wait();

  // Construct data byte and send
  payload = (wave_number >> 4) & SN76489AN_DATA_FREQ_MASK;
  PSG_Write(payload);
  PSG_Wait();
}

void PSG_SetAttenuation(uint8_t channel, uint8_t attenuation) {
  // Construct payload and send latch byte
  uint8_t payload = SN76489AN_LATCH_BYTE | (channel << 5) |
                    SN76489AN_ATTEN_SEL |
                    ((uint8_t)(attenuation & SN76489AN_LATCH_MASK));
  PSG_Write(payload);
  PSG_Wait();
}

void PSG_SetNoise(uint8_t type, uint8_t shift_rate) {
  // Construct payload and send latch byte
  uint8_t payload = SN76489AN_LATCH_BYTE | (SN76489AN_NOISE_CHANNEL << 5) |
                    SN76489AN_SHIFT_RATE_SEL | ((type & 0x01) << 2) |
                    (shift_rate & SN76489AN_LATCH_SHIFT_RATE_MASK);
  PSG_Write(payload);
  PSG_Wait();
}