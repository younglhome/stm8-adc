
/******************** (C) COPYRIGHT  喆帆电子    ***************************
 * 文件名    ：key.c
 * 描述      ：按键端口配置  
 * 实验平台  ：STM8s001J3开发板
 * 作者      ：wagnjin  QQ：28669816
 * 淘宝店铺  ：https://shop33781225.taobao.com
 *修改时间   ：2018-05-03
***************************************************************************/
#include "key.h"


/**
  * @brief KEY_Init
  * @param Not
  * @retval Not
  */
void KEY_Init(void)
{
  /* 初始化按键，上拉输入 */
  GPIO_Init(KEY_GPIO_PORT, (GPIO_Pin_TypeDef)KEY_GPIO_PINS, GPIO_MODE_IN_PU_NO_IT);
}


/**
  * @brief KEY_Scan
  * @param Not
  * @retval 按下返回：KEY_PRESS  没按返回：0x00
  */
unsigned char KEY_Scan(void)
{
   /* 读取按键引脚电平 */
  if(!GPIO_ReadInputPin(KEY_GPIO_PORT,KEY_GPIO_PINS))
    return KEY_PRESS;
  else
    return 0x00;
}
