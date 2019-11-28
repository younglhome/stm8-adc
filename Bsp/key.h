#ifndef __KEY__H
#define __KEY__H

#include "stm8s.h"


#define KEY_GPIO_PORT  (GPIOC)
#define KEY_GPIO_PINS  (GPIO_PIN_5)

#define KEY_PRESS       0x01


void KEY_Init(void);
u8 KEY_Scan(void);

#endif