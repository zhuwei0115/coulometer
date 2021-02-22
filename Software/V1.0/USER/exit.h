#ifndef __EXIT_H
#define __EXIT_H

#include "stm32f10x.h"
#include "sys.h" 

#define EC11_A PEin(6)
#define EC11_B PEin(7)

void EXTIX_Init(void);
void EXTI9_5_IRQHandler(void);


#endif
