/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LPS_CS_Pin GPIO_PIN_14
#define LPS_CS_GPIO_Port GPIOC
#define BAT_CG_POK_Pin GPIO_PIN_15
#define BAT_CG_POK_GPIO_Port GPIOC
#define MIC_SD_Pin GPIO_PIN_1
#define MIC_SD_GPIO_Port GPIOA
#define LCD_PWM_Pin GPIO_PIN_2
#define LCD_PWM_GPIO_Port GPIOA
#define BLE_MOD_Pin GPIO_PIN_3
#define BLE_MOD_GPIO_Port GPIOA
#define SW2_Pin GPIO_PIN_4
#define SW2_GPIO_Port GPIOA
#define SW2_EXTI_IRQn EXTI4_IRQn
#define SW1_Pin GPIO_PIN_5
#define SW1_GPIO_Port GPIOA
#define SW1_EXTI_IRQn EXTI9_5_IRQn
#define SD_CMD_Pin GPIO_PIN_6
#define SD_CMD_GPIO_Port GPIOA
#define SW3_Pin GPIO_PIN_7
#define SW3_GPIO_Port GPIOA
#define SW3_EXTI_IRQn EXTI9_5_IRQn
#define LCD_SCK_Pin GPIO_PIN_0
#define LCD_SCK_GPIO_Port GPIOB
#define SP_PWM_Pin GPIO_PIN_1
#define SP_PWM_GPIO_Port GPIOB
#define LCD_DC_Pin GPIO_PIN_2
#define LCD_DC_GPIO_Port GPIOB
#define LPS_SCK_Pin GPIO_PIN_10
#define LPS_SCK_GPIO_Port GPIOB
#define MIC_WS_Pin GPIO_PIN_12
#define MIC_WS_GPIO_Port GPIOB
#define MIC_CK_Pin GPIO_PIN_13
#define MIC_CK_GPIO_Port GPIOB
#define LPS_MISO_Pin GPIO_PIN_14
#define LPS_MISO_GPIO_Port GPIOB
#define SD_CLK_Pin GPIO_PIN_15
#define SD_CLK_GPIO_Port GPIOB
#define SD_D1_Pin GPIO_PIN_8
#define SD_D1_GPIO_Port GPIOA
#define SD_D2_Pin GPIO_PIN_9
#define SD_D2_GPIO_Port GPIOA
#define LPS_MOSI_Pin GPIO_PIN_10
#define LPS_MOSI_GPIO_Port GPIOA
#define SD_SW_Pin GPIO_PIN_11
#define SD_SW_GPIO_Port GPIOA
#define VPP_EN_Pin GPIO_PIN_12
#define VPP_EN_GPIO_Port GPIOA
#define SD_D0_Pin GPIO_PIN_4
#define SD_D0_GPIO_Port GPIOB
#define SD_D3_Pin GPIO_PIN_5
#define SD_D3_GPIO_Port GPIOB
#define BAT_IMU_SCL_Pin GPIO_PIN_6
#define BAT_IMU_SCL_GPIO_Port GPIOB
#define BAT_IMU_SDA_Pin GPIO_PIN_7
#define BAT_IMU_SDA_GPIO_Port GPIOB
#define LCD_MOSI_Pin GPIO_PIN_8
#define LCD_MOSI_GPIO_Port GPIOB
#define LCD_RES_Pin GPIO_PIN_9
#define LCD_RES_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
