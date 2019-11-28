/******************** (C) COPYRIGHT  喆帆电子    ***************************
 * 文件名    ：TM1652.c
 * 描述      ：HT1652数码管驱动  
 * 实验平台  ：STM8s001J3开发板
 * 作者      ：wagnjin  QQ：28669816
 * 淘宝店铺  ：https://shop33781225.taobao.com
 *修改时间   ：2018-05-03
***************************************************************************/

#include "tm1652.h"

void SHUMAGUAN_Init(void)
{

  GPIO_Init(TM1652_GPIO, TM1652_SDA, GPIO_MODE_OUT_PP_HIGH_FAST);//初始化TM1651 推挽输出high 10M
  TM1652_Set(0x18,0x38);//初始化
}
    
///=======================================
void Delay_us(u8 i) //nus 延时  2.5us
{
  for(; i>0; i--)
  {
    nop(); nop(); nop();nop(); 
    nop(); nop(); nop();nop(); 
  }        
}

//=========================================
void I2CWrByte(u8 sdat) //写一个字节
{
  unsigned char i=0, sfalg=0;
  GPIO_WriteHigh(TM1652_GPIO, TM1652_SDA);
  GPIO_WriteLow(TM1652_GPIO, TM1652_SDA);
  Delay_us(52);    //保持52us
  
 //发送8位数据
  for(i=0; i<8; i++)
  {
      if(sdat & 0x01)
      {
          GPIO_WriteHigh(TM1652_GPIO, TM1652_SDA);
          sfalg++;
      }else
      {
          GPIO_WriteLow(TM1652_GPIO, TM1652_SDA);
      }
      Delay_us(52); 
      sdat >>=1;
  }

  //校验位,按照发送数据中1的个数来判断
  if(sfalg%2==0)			         
  {
      GPIO_WriteHigh(TM1652_GPIO, TM1652_SDA);
  }
  else			        
  {
      GPIO_WriteLow(TM1652_GPIO, TM1652_SDA);
  }
  Delay_us(52); 
  
  //停止位
  GPIO_WriteHigh(TM1652_GPIO, TM1652_SDA);  
  Delay_us(52);   
}



void TM1652_Set(u8 add,u8 dat) //数码管显示
{
	I2CWrByte(add); //第一个显存地址
        Delay_us(10);
	I2CWrByte(dat);
        Delay_us(10);
}

/******************* (C) COPYRIGHT   风驰iCreate嵌入式开发工作室 *****END OF FILE****/