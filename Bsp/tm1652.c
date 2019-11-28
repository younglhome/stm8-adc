/******************** (C) COPYRIGHT  ��������    ***************************
 * �ļ���    ��TM1652.c
 * ����      ��HT1652���������  
 * ʵ��ƽ̨  ��STM8s001J3������
 * ����      ��wagnjin  QQ��28669816
 * �Ա�����  ��https://shop33781225.taobao.com
 *�޸�ʱ��   ��2018-05-03
***************************************************************************/

#include "tm1652.h"

void SHUMAGUAN_Init(void)
{

  GPIO_Init(TM1652_GPIO, TM1652_SDA, GPIO_MODE_OUT_PP_HIGH_FAST);//��ʼ��TM1651 �������high 10M
  TM1652_Set(0x18,0x38);//��ʼ��
}
    
///=======================================
void Delay_us(u8 i) //nus ��ʱ  2.5us
{
  for(; i>0; i--)
  {
    nop(); nop(); nop();nop(); 
    nop(); nop(); nop();nop(); 
  }        
}

//=========================================
void I2CWrByte(u8 sdat) //дһ���ֽ�
{
  unsigned char i=0, sfalg=0;
  GPIO_WriteHigh(TM1652_GPIO, TM1652_SDA);
  GPIO_WriteLow(TM1652_GPIO, TM1652_SDA);
  Delay_us(52);    //����52us
  
 //����8λ����
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

  //У��λ,���շ���������1�ĸ������ж�
  if(sfalg%2==0)			         
  {
      GPIO_WriteHigh(TM1652_GPIO, TM1652_SDA);
  }
  else			        
  {
      GPIO_WriteLow(TM1652_GPIO, TM1652_SDA);
  }
  Delay_us(52); 
  
  //ֹͣλ
  GPIO_WriteHigh(TM1652_GPIO, TM1652_SDA);  
  Delay_us(52);   
}



void TM1652_Set(u8 add,u8 dat) //�������ʾ
{
	I2CWrByte(add); //��һ���Դ��ַ
        Delay_us(10);
	I2CWrByte(dat);
        Delay_us(10);
}

/******************* (C) COPYRIGHT   ���iCreateǶ��ʽ���������� *****END OF FILE****/