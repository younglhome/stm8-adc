/******************** (C) COPYRIGHT  喆帆电子    ***************************
 * 文件名    ：time4.c
 * 描述      ：定时器4配置  
 * 实验平台  ：STM8s001J3开发板
 * 作者      ：wagnjin  QQ：28669816
 * 淘宝店铺  ：https://shop33781225.taobao.com
 *修改时间   ：2018-05-03
***************************************************************************/
/* 包含头文件 ----------------------------------------------------------------*/
#include "tim4.h"


/**
  * @函数名       TIM4_Config
  * @功  能       配置TIM4定时1ms中断一次
  * @参  数       无
  * @返回值       无
  */
void TIM4_Config(void)
{
  /* 
    TIM4 配置:
   - TIM4的时钟是16 MHz, 128分频后是125kHz
    16 MHz / 128 = 125 000 Hz
   - 预装载值设为124（125-1）时，计数器溢出的时间为1ms
    125000 / 125 = 1000Hz = 1ms
  */

  /* 128分频，预装载值为（125-1） */
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, 249);
  
  /* 清除TIM4的更新标志位 */
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  
  /* 使能更新中断 */
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);

  /* 使能总中断 */
  enableInterrupts();

  /* 使能TIM4，开始计数 */
  TIM4_Cmd(ENABLE);
}

/************************ Copyright (C)2017 LGG. All Rights Reserved *****END OF FILE****/
