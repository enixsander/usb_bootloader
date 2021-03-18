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
#include "config_BIK.h"

#define WIDTH 800
#define HEIGHT 480

#define SCAN_PERIOD       10
#define I2C_EXP_PERIOD    25
#define LED_UPDATE_PERIOD 50
#define I2C_EEPROM_ADDRESS 0xA0
#define MEMORY_ADDRESS 0x00

//DMA
#define DMA_SIZE1 20
#define DMA_SIZE3 50
#define NUMB_ADC1_CHANNEL 5
#define NUMB_ADC3_CHANNEL 1

#define DA7_ADDR   0x6D
#define DD7_ADDR   0x61
#define DD8_ADDR   0x62
#define DD9_ADDR   0x63
#define DD10_ADDR  0x64
#define DD11_ADDR  0x38

#define SB1   0x00000020 //1 << 0x05
#define SB2   0x00000010
#define SB3   0x00000008
#define SB4   0x00000004
#define SB5   0x00000002
#define SB6   0x00000001 //1 << 0x00
#define SB7   0x00002000 //1 << 0x0D
#define SB8   0x00001000
#define SB9   0x00000800
#define SB10  0x00000400
#define SB11  0x00000200
#define SB12  0x00000100 //1 << 0x08
#define SB13  0x00200000 //1 << 0x15
#define SB14  0x00100000
#define SB15  0x00080000
#define SB16  0x00040000
#define SB17  0x00020000
#define SB18  0x00010000 //1 << 0x10
#define SB19  0x20000000 //1 << 0x1D
#define SB20  0x10000000
#define SB21  0x08000000
#define SB22  0x04000000
#define SB23  0x02000000
#define SB24  0x01000000 //1 << 0x18

#define MASK_12 0x03
#define MASK_34 0x0C
#define MASK_56 0x30
#define MASK_78 0xC0

#define bit1 0x01
#define bit3 0x04
#define bit5 0x10
#define bit7 0x40

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
