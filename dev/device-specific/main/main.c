/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 YUMENEGI INDUSTRIES.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "note_freq.h"
#include "psg.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include <stdint.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void SN76489_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void TIM3_Init(void);
static void playFamima(void);

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick.
   */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  TIM3_Init();
  if (HAL_TIM_OC_Start(&htim3, TIM_CHANNEL_2) != HAL_OK) {
    // Starting the timer failed
    Error_Handler();
  }
  SN76489_GPIO_Init();
  MX_USART2_UART_Init();
  // Mute All
  PSG_Init();
  HAL_Delay(WHOLE_DELAY_MS_95BPM);

  /* Main loop */
  while (1) {
    if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin) == GPIO_PIN_RESET)
      playFamima();
    // PSG_SetFrequency(SN76489AN_TONE_CHANNEL_0, NOTE_A4);
    // PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x00);
    // HAL_Delay(EIGHTH_DELAY_MS_95BPM);
    // PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0F);
    // HAL_Delay(WHOLE_QUARTER_MS_95BPM);
  }
}

/**
 * @brief  Plays the Famima jingle
 * @return None
 */
static void playFamima(void) {
  // F#
  PSG_SetFrequency(SN76489AN_TONE_CHANNEL_0, NOTE_FS5);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x08);
  HAL_Delay(EIGHTH_DELAY_MS_95BPM);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0F);

  // D
  PSG_SetFrequency(SN76489AN_TONE_CHANNEL_0, NOTE_D5);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x08);
  HAL_Delay(EIGHTH_DELAY_MS_95BPM);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0F);

  // F# + A
  PSG_SetFrequency(SN76489AN_TONE_CHANNEL_0, NOTE_A4);
  PSG_SetFrequency(SN76489AN_TONE_CHANNEL_1, NOTE_FS4);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0A);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_1, 0x0A);
  HAL_Delay(EIGHTH_DELAY_MS_95BPM);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0F);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_1, 0x0F);

  // D
  PSG_SetFrequency(SN76489AN_TONE_CHANNEL_0, NOTE_D5);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x08);
  HAL_Delay(EIGHTH_DELAY_MS_95BPM);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0F);

  // A + E
  PSG_SetFrequency(SN76489AN_TONE_CHANNEL_0, NOTE_E5);
  PSG_SetFrequency(SN76489AN_TONE_CHANNEL_1, NOTE_A4);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0A);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_1, 0x0A);
  HAL_Delay(EIGHTH_DELAY_MS_95BPM);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0F);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_1, 0x0F);

  // A
  PSG_SetFrequency(SN76489AN_TONE_CHANNEL_0, NOTE_A5);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x08);
  HAL_Delay(QUARTER_DELAY_MS_95BPM);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0F);

  // E
  PSG_SetFrequency(SN76489AN_TONE_CHANNEL_0, NOTE_E4);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x08);
  HAL_Delay(EIGHTH_DELAY_MS_95BPM);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0F);

  // A + E
  PSG_SetFrequency(SN76489AN_TONE_CHANNEL_0, NOTE_A4);
  PSG_SetFrequency(SN76489AN_TONE_CHANNEL_1, NOTE_E5);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0A);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_1, 0x0A);
  HAL_Delay(EIGHTH_DELAY_MS_95BPM);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0F);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_1, 0x0F);

  // F#
  PSG_SetFrequency(SN76489AN_TONE_CHANNEL_0, NOTE_FS5);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x08);
  HAL_Delay(EIGHTH_DELAY_MS_95BPM);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0F);

  // A + E
  PSG_SetFrequency(SN76489AN_TONE_CHANNEL_0, NOTE_A4);
  PSG_SetFrequency(SN76489AN_TONE_CHANNEL_1, NOTE_E5);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0A);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_1, 0x0A);
  HAL_Delay(EIGHTH_DELAY_MS_95BPM);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0F);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_1, 0x0F);

  // F#
  PSG_SetFrequency(SN76489AN_TONE_CHANNEL_0, NOTE_A4);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x08);
  HAL_Delay(EIGHTH_DELAY_MS_95BPM);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0F);

  // F# + D
  PSG_SetFrequency(SN76489AN_TONE_CHANNEL_0, NOTE_FS4);
  PSG_SetFrequency(SN76489AN_TONE_CHANNEL_1, NOTE_D5);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0A);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_1, 0x0A);
  HAL_Delay(QUARTER_DELAY_MS_95BPM);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_0, 0x0F);
  PSG_SetAttenuation(SN76489AN_TONE_CHANNEL_1, 0x0F);

  HAL_Delay(QUARTER_DELAY_MS_95BPM);
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
   */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }
}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void) {

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK) {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);
}

/**
 * @brief Initializes the GPIO pins used for the SN76489 interface.
 * This function should be called once at startup.
 */
static void SN76489_GPIO_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Set initial state for all pins before configuring them */
  // WE is active-low, so its idle state should be HIGH.
  HAL_GPIO_WritePin(SN_WE_GPIO_PORT, SN_WE_PIN, GPIO_PIN_SET);

  // Set data pins to LOW. It's good practice to start with a known state.
  HAL_GPIO_WritePin(SN_D0_GPIO_PORT, SN_D0_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SN_D1_GPIO_PORT, SN_D1_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SN_D2_GPIO_PORT, SN_D2_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SN_D3_GPIO_PORT, SN_D3_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SN_D4_GPIO_PORT, SN_D4_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SN_D5_GPIO_PORT, SN_D5_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SN_D6_GPIO_PORT, SN_D6_PIN, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(SN_D7_GPIO_PORT, SN_D7_PIN, GPIO_PIN_RESET);

  /* Configure common GPIO settings */
  GPIO_InitStruct.Mode =
      GPIO_MODE_OUTPUT_PP; // Push-Pull: Actively drives HIGH and LOW.
  GPIO_InitStruct.Pull =
      GPIO_NOPULL; // No internal pull-up or pull-down needed.
  GPIO_InitStruct.Speed =
      GPIO_SPEED_FREQ_HIGH; // High speed for fast bit-banging.

  /* Configure pins on GPIOA */
  GPIO_InitStruct.Pin = SN_D0_PIN | SN_D5_PIN | SN_D6_PIN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Configure pins on GPIOB */
  GPIO_InitStruct.Pin =
      SN_D1_PIN | SN_D2_PIN | SN_D3_PIN | SN_D4_PIN | SN_WE_PIN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* Configure pins on GPIOC */
  GPIO_InitStruct.Pin = SN_D7_PIN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/**
 * @brief TIM3 Initialization Function
 * @param None
 * @retval None
 */
void TIM3_Init(void) {
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 9;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  if (HAL_TIM_Base_Init(&htim3) != HAL_OK) {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK) {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim3) != HAL_OK) {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK) {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
  sConfigOC.Pulse = 5;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK) {
    Error_Handler();
  }

  HAL_TIM_MspPostInit(&htim3);
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1) {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line
     number, ex: printf("Wrong parameters value: file %s on line %d\r\n", file,
     line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
