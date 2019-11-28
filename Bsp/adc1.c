/******************** (C) COPYRIGHT  ��������    ***************************
 * �ļ���    ��adc1.c
 * ����      ��adc1����  
 * ʵ��ƽ̨  ��STM8s001J3������
 * ����      ��wagnjin  QQ��28669816
 * �Ա�����  ��https://shop33781225.taobao.com
 *�޸�ʱ��   ��2018-05-03
***************************************************************************/

/* ����ͷ�ļ� ----------------------------------------------------------------*/

#include "adc1.h"

/**
  * @������       ADC1_Config
  * @��  ��       ����ADC1
  * @��  ��       ��
  * @����ֵ       ��
  */
void ADC1_Config(void)
{
  /*  ��ʼ�� ADC1 ͨ��6��IO�� */
  GPIO_Init(GPIOD, GPIO_PIN_6, GPIO_MODE_IN_FL_NO_IT);
  
  /* ʹADC1 �ļĴ����ָ�ȱʡֵ*/
  ADC1_DeInit();

  /* ��ʼ��ADC1 */
  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, ADC1_CHANNEL_6, ADC1_PRESSEL_FCPU_D2, \
            ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL6,\
            DISABLE);

  /* ʹ�� EOC �ж� */
  //ADC1_ITConfig(ADC1_IT_EOCIE ,ENABLE);

  /* ʹ�����ж� */  
  enableInterrupts();
  
  /*��ʼת�� */
  ADC1_StartConversion();
}


/************************ Copyright (C)2017 LGG. All Rights Reserved *****END OF FILE****/

