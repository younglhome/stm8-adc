#ifndef __LED__H
#define __LED__H

#include "stm8s.h"


/* 定义LED1 IO PORT与PIN */
#define LED1_GPIO_PORT  (GPIOB)
#define LED1_GPIO_PINS  (GPIO_PIN_5)


/* 声明外部调用函数 */
void LED_Init(void);
#endif

