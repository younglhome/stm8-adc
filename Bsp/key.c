
/******************** (C) COPYRIGHT  ��������    ***************************
 * �ļ���    ��key.c
 * ����      �������˿�����  
 * ʵ��ƽ̨  ��STM8s001J3������
 * ����      ��wagnjin  QQ��28669816
 * �Ա�����  ��https://shop33781225.taobao.com
 *�޸�ʱ��   ��2018-05-03
***************************************************************************/
#include "key.h"


/**
  * @brief KEY_Init
  * @param Not
  * @retval Not
  */
void KEY_Init(void)
{
  /* ��ʼ���������������� */
  GPIO_Init(KEY_GPIO_PORT, (GPIO_Pin_TypeDef)KEY_GPIO_PINS, GPIO_MODE_IN_PU_NO_IT);
}


/**
  * @brief KEY_Scan
  * @param Not
  * @retval ���·��أ�KEY_PRESS  û�����أ�0x00
  */
unsigned char KEY_Scan(void)
{
   /* ��ȡ�������ŵ�ƽ */
  if(!GPIO_ReadInputPin(KEY_GPIO_PORT,KEY_GPIO_PINS))
    return KEY_PRESS;
  else
    return 0x00;
}
