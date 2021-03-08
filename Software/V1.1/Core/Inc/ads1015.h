/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADS1015_H__
#define __ADS1015_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

//extern I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN Private defines */

#define ADDR_ADS1015_Write 0x90
#define ADDR_ADS1015_Read 0x91

#define ADS1015_Config_AIN0 0xc083
#define ADS1015_Config_AIN1 0xd083
#define ADS1015_Config_AIN2 0xe083
#define ADS1015_Config_AIN3 0xf083

#define Ain_NTC 0
#define Ain_Input_Voltgage 1
#define Ain_Input_Current 2
#define Ain_Input_5V 3

/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
int16_t ADS1015_Write_nBytes(uint8_t *data, uint16_t addr, uint16_t length);
int16_t ADS1015_Read_nBytes(uint8_t *data, uint16_t addr, uint16_t length);
void ADS1015_Read_AinX(uint8_t *Value,uint8_t Channel);
void ADS1015_Value_Process(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __I2C_H__ */

