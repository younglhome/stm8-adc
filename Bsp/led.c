
/******************** (C) COPYRIGHT  喆帆电子    ***************************
 * 文件名    ：led.c
 * 描述      ：led灯端口配置  
 * 实验平台  ：STM8s001J3开发板
 * 作者      ：wagnjin  QQ：28669816
 * 淘宝店铺  ：https://shop33781225.taobao.com
 *修改时间   ：2018-05-03
***************************************************************************/

#include "led.h"


/**
  * @brief LED_Init
  * @param Not
  * @retval Not
  */
void LED_Init(void)
{
  /* 初始化LED1 IO口为输出模式 */
  GPIO_Init(LED1_GPIO_PORT, (GPIO_Pin_TypeDef)LED1_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
  
}


