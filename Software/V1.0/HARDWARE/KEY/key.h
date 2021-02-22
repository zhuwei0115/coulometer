#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"
#include "sys.h" 
#include "usart.h"

#define KEY_UP PEin(0)
#define KEY_DOWN PEin(1)
#define KEY_LEFT PEin(2)
#define KEY_RIGHT PEin(3)
#define KEY_CENTER PEin(4)

#define EC11_KEY PEin(5)


#define KEY_UP_PRESS        0x01
#define KEY_DOWN_PRESS      0x02
#define KEY_LEFT_PRESS      0x04
#define KEY_RIGHT_PRESS     0x08
#define KEY_CENTER_PRESS    0x10

#define EC11_KEY_PRESS      0x20


#endif
