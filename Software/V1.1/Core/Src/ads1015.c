/* Includes ------------------------------------------------------------------*/
#include "i2c.h"
#include "ads1015.h"

/* USER CODE BEGIN 0 */
//Sys_StausTypeDef Sys_Staus1;

/* USER CODE END 0 */


/* USER CODE BEGIN 1 */

/* ADS1015 write function */
int16_t ADS1015_Write_nBytes(uint8_t *data, uint16_t addr, uint16_t length)
{
	if( HAL_I2C_Mem_Write( &hi2c1, ADDR_ADS1015_Write, addr, I2C_MEMADD_SIZE_8BIT, data, length, 1000 ) == HAL_OK )
			return 0;
	else
			return -1;
}

/* ADS1015 read function */ 
int16_t ADS1015_Read_nBytes(uint8_t *data, uint16_t addr, uint16_t length)
{
	if( HAL_I2C_Mem_Read( &hi2c1, ADDR_ADS1015_Read, addr, I2C_MEMADD_SIZE_8BIT, data, length, 1000 ) == HAL_OK )
			return 0;
	else
			return -1;
}

/* ADS1015 read adc value */
void ADS1015_Read_AinX(uint8_t *Value,uint8_t Channel)
{
	uint8_t Config[2];
	switch(Channel)
	{
		case Ain_NTC: 		
			Config[0] = (uint8_t)(ADS1015_Config_AIN0 >> 8) ;
			Config[1] = (uint8_t)(ADS1015_Config_AIN0 & 0xff) ;
			ADS1015_Write_nBytes(Config, 0x01, 0x02);
			HAL_Delay(10);
			ADS1015_Read_nBytes(Value, 0x0, 0x2);
			break;
		
		case Ain_Input_Voltgage: 		
			Config[0] = (uint8_t)(ADS1015_Config_AIN1 >> 8) ;
			Config[1] = (uint8_t)(ADS1015_Config_AIN1 & 0xff) ;
			ADS1015_Write_nBytes(Config, 0x01, 0x02);
			HAL_Delay(10);
			ADS1015_Read_nBytes(Value, 0x0, 0x2);
			break;
		
		case Ain_Input_Current: 		
			Config[0] = (uint8_t)(ADS1015_Config_AIN2 >> 8) ;
			Config[1] = (uint8_t)(ADS1015_Config_AIN2 & 0xff) ;
			ADS1015_Write_nBytes(Config, 0x01, 0x02);
			HAL_Delay(10);
			ADS1015_Read_nBytes(Value, 0x0, 0x2);
			break;
		
		case Ain_Input_5V: 		
			Config[0] = (uint8_t)(ADS1015_Config_AIN3 >> 8) ;
			Config[1] = (uint8_t)(ADS1015_Config_AIN3 & 0xff) ;
			ADS1015_Write_nBytes(Config, 0x01, 0x02);
			HAL_Delay(10);
			ADS1015_Read_nBytes(Value, 0x0, 0x2);
			break;
		
		default : break;
	}
}

/* ADS1015  adc value process to system status*/
void ADS1015_Value_Process(void)
{
	uint8_t Value[2];
	uint16_t temp;
	ADS1015_Read_AinX(Value,Ain_Input_Voltgage);
	printf("ADS1015 AN0 value is : 0x%x%x\n\r",Value[0],Value[1]);
	temp = (Value[0]<<8)+Value[1];	
	temp = temp >>4;   //µÍ4Î»ÎÞÐ§
	temp = temp;
	printf("ADS1015 AN1 value is : 0x%x\n\r",temp);
	Sys_Staus1.Voltage = temp;
	
}


/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
