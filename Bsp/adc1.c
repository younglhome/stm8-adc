/******************** (C) COPYRIGHT  喆帆电子    ***************************
 * 文件名    ：adc1.c
 * 描述      ：adc1配置  
 * 实验平台  ：STM8s001J3开发板
 * 作者      ：wagnjin  QQ：28669816
 * 淘宝店铺  ：https://shop33781225.taobao.com
 *修改时间   ：2018-05-03
***************************************************************************/

/* 包含头文件 ----------------------------------------------------------------*/

#include "adc1.h"

/**
  * @函数名       ADC1_Config
  * @功  能       配置ADC1
  * @参  数       无
  * @返回值       无
  */
void ADC1_Config(void)
{
  /*  初始化 ADC1 通道6的IO口 */
  GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_IN_FL_NO_IT);
  
  /* 使ADC1 的寄存器恢复缺省值*/
  ADC1_DeInit();

  /* 初始化ADC1 */
  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, ADC1_CHANNEL_6, ADC1_PRESSEL_FCPU_D2, \
            ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL6,\
            DISABLE);

  /* 使能 EOC 中断 */
  //ADC1_ITConfig(ADC1_IT_EOCIE ,ENABLE);

  /* 使能总中断 */  
  enableInterrupts();
  
  /*开始转换 */
  ADC1_StartConversion();
}


/************************ Copyright (C)2017 LGG. All Rights Reserved *****END OF FILE****/

