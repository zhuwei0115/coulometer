/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
#define FOUT_Pin GPIO_PIN_1
#define FOUT_GPIO_Port GPIOA
#define SYS_POWER_EN_Pin GPIO_PIN_2
#define SYS_POWER_EN_GPIO_Port GPIOA
#define HALL_IN_Pin GPIO_PIN_3
#define HALL_IN_GPIO_Port GPIOA
#define LED0_Pin GPIO_PIN_4
#define LED0_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_5
#define LED1_GPIO_Port GPIOA
#define KEY_DOWN_Pin GPIO_PIN_6
#define KEY_DOWN_GPIO_Port GPIOA
#define KEY_UP_Pin GPIO_PIN_7
#define KEY_UP_GPIO_Port GPIOA
#define KEY_MODE_Pin GPIO_PIN_0
#define KEY_MODE_GPIO_Port GPIOB
#define BT_UART_TXD_Pin GPIO_PIN_10
#define BT_UART_TXD_GPIO_Port GPIOB
#define BT_UART_RXD_Pin GPIO_PIN_11
#define BT_UART_RXD_GPIO_Port GPIOB
#define BT_EN_Pin GPIO_PIN_14
#define BT_EN_GPIO_Port GPIOB
#define BT_STATE_Pin GPIO_PIN_15
#define BT_STATE_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

//ϵͳ״̬
typedef struct 
{
	uint8_t RTC_Hours;				//ʵʱʱ�� ʱ
	uint8_t RTC_Minutes;			//ʵʱʱ�� ��
	uint8_t RTC_Seconds;			//ʵʱʱ�� ��	
	uint8_t Run_Hours;				//����ʱ�� ʱ
	uint8_t Run_Minutes;			//����ʱ�� ��
	uint8_t Run_Seconds;			//����ʱ�� ��
	uint16_t Total_Capicity;			//������������
	uint16_t Current_Capicity;		//��ص�ǰ����
	uint8_t SOC;				//���ʣ�����
	uint16_t Voltage;			//��ص�ѹ
	uint16_t Current;			//�ŵ�������
	uint16_t Power;			//��ǰ����
	uint8_t Chrg_or_Dischrg;			//����ʱ�� ��
}Sys_StausTypeDef;

extern Sys_StausTypeDef Sys_Staus1;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
