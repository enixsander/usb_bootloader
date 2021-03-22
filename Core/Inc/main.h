/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#define DA7_ADDR   0x6D
#define DD7_ADDR   0x61
#define DD8_ADDR   0x62
#define DD9_ADDR   0x63
#define DD10_ADDR  0x64
#define DD11_ADDR  0x38

typedef struct __attribute__((packed)) {
  uint8_t reg_address;
  uint8_t PWM0;
  uint8_t PWM1;
  uint8_t PWM2;
  uint8_t PWM3;
  uint8_t PWM4;
  uint8_t PWM5;
  uint8_t PWM6;
  uint8_t PWM7;
  uint8_t PWM8;
  uint8_t PWM9;
  uint8_t PWM10;
  uint8_t PWM11;
  uint8_t PWM12;
  uint8_t PWM13;
  uint8_t PWM14;
  uint8_t PWM15;
  uint8_t GLOBAL_PWM;
} tlc59116_control_type;
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USBOH_ID_Pin GPIO_PIN_12
#define USBOH_ID_GPIO_Port GPIOB
#define USBOH_PON_Pin GPIO_PIN_3
#define USBOH_PON_GPIO_Port GPIOG
#define EN_5V_Pin GPIO_PIN_5
#define EN_5V_GPIO_Port GPIOD
#define CPU_OK_Pin GPIO_PIN_14
#define CPU_OK_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
