
/******************** (C) COPYRIGHT  ��������    ***************************
 * �ļ���    ��led.c
 * ����      ��led�ƶ˿�����  
 * ʵ��ƽ̨  ��STM8s001J3������
 * ����      ��wagnjin  QQ��28669816
 * �Ա�����  ��https://shop33781225.taobao.com
 *�޸�ʱ��   ��2018-05-03
***************************************************************************/

#include "led.h"


/**
  * @brief LED_Init
  * @param Not
  * @retval Not
  */
void LED_Init(void)
{
  /* ��ʼ��LED1 IO��Ϊ���ģʽ */
  GPIO_Init(LED1_GPIO_PORT, (GPIO_Pin_TypeDef)LED1_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);
  
}


