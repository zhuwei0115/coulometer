#include "soc.h" 


Bat_Status Get_OCV_SOC(ADC_Value * ADC_Value_Struct ,u16 Bat_Capacity)
{
	u8 i;
	Bat_Status Bat_Status1;
	for(i=1;i<101;i++)
	{
		if(ADC_Value_Struct->ADC_Voltage<OcvTable_Dischg_1C[i].Voltage)    
		{
			 //判断当前电压跟第i-1和第i参数哪个更接近就取哪个SOC值
			if((ADC_Value_Struct->ADC_Voltage-OcvTable_Dischg_1C[i-1].Voltage) < (OcvTable_Dischg_1C[i-1].Voltage-ADC_Value_Struct->ADC_Voltage))  
			{
				Bat_Status1.SOC = OcvTable_Dischg_1C[i-1].SOC;
			}
			else
				Bat_Status1.SOC = OcvTable_Dischg_1C[i].SOC;
		}
		else
			Bat_Status1.SOC = OcvTable_Dischg_1C[100].SOC;
	}
	Bat_Status1.Current_Capacity = (u16)(Bat_Status1.SOC * Bat_Capacity);
	return Bat_Status1;	
}
 
Bat_Status Get_Realtime_SOC(ADC_Value * ADC_Value_Struct , Bat_Status *Old_Status , u8 Interval , u16 Bat_Capacity)
{
	Bat_Status New_Status;
	switch (ADC_Value_Struct.Bat_Status)
	{
		case Bat_Idle :
			New_Status.Current_Capacity = Old_Status->Current_Capacity;   //暂且认为固定损耗=0
			New_Status.SOC = Old_Status->SOC;
			break;
		case Bat_Charging :
			New_Status.Current_Capacity =  Old_Status->Current_Capacity + ADC_Value_Struct->ADC_Current*Interval;
			New_Status.SOC = New_Status.Current_Capacity*100/Bat_Capacity;		
		case Bat_Discharging :
			New_Status.Current_Capacity =  Old_Status->Current_Capacity - ADC_Value_Struct->ADC_Current*Interval;
			New_Status.SOC = New_Status.Current_Capacity*100/Bat_Capacity;			
	}
	return New_Status;
}







