#ifndef __LED__H
#define __LED__H

#include "stm8s.h"


/* ����LED1 IO PORT��PIN */
#define LED1_GPIO_PORT  (GPIOB)
#define LED1_GPIO_PINS  (GPIO_PIN_5)


/* �����ⲿ���ú��� */
void LED_Init(void);
#endif

