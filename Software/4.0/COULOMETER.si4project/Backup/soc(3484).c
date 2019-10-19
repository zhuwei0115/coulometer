#include "soc.h" 


u8 Get_OCV_SOC(ADC_Value * ADC_Value_Struct)
{
	u8 i;
	for(i=1;i<101;i++)
	{
		if(ADC_Value_Struct.ADC_Voltage<OcvTable_Dischg_1C[i].Voltage)    
		{
			 //判断当前电压跟第i-1和第i参数哪个更接近就取哪个SOC值
			if((ADC_Value_Struct.ADC_Voltage-OcvTable_Dischg_1C[i-1].Voltage) < (OcvTable_Dischg_1C[i-1].Voltage-ADC_Value_Struct.ADC_Voltage))  
			{
				return OcvTable_Dischg_1C[i-1].SOC;
			}
			else
				return OcvTable_Dischg_1C[i].SOC;
		}
		else
			return OcvTable_Dischg_1C[100].SOC;
	}

}
 
u8 Get_Realtime_SOC(ADC_Value * ADC_Value_Struct , u8 Old_SOC , u8 Interval)
{
	u8 New_SOC;
	switch (ADC_Value_Struct.Bat_Status)
	{
		case Bat_Idle :
			New_SOC = Get_OCV_SOC(ADC_Value_Struct);
			break;
		case Bat_Charging :
			New_SOC = Old_SOC + 
			
	}

	return New_SOC;
}







