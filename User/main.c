/******************** (C) COPYRIGHT  ��������    ***************************
 * �ļ���    ��main.c
 * ����      ��������  
 * ʵ��ƽ̨  ��STM8s001J3������
 * ����      ��wagnjin  QQ��28669816
 * �Ա�����  ��https://shop33781225.taobao.com
 *�޸�ʱ��   ��2018-05-03
***************************************************************************/
/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm8s.h"
#include "tim4.h"
#include "led.h"
#include "stm8s_it.h"
#include "tm1652.h"
#include "key.h"
#include "adc1.h"
/* ��ֵ���� ----------------------------------------------------------------*/
uint16_t  data;

u8 CODE[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f, //0~9��ʾ����
             0x77,0x7c,0x58,0x5e,0x79,0x71,                     //a~f��ʾ����
             0x6f,0x76,0x04,0x38,0x54,0x5c,0x73,0x50,0x6d,0x78,0x1c,0x3e,0x00,0x6e,0x40}; 
             //g   H     i   L    n    o     p    r    s    t   u    U          y   -

/* �������� ------------------------------------------------------------------*/
void  Delay(uint32_t nCount);
void  display(u8 disnum,u8 disbit,u8 dotbit);
void  discount(s16 disdata,u8 dotbit);
void  disfun(void);
u8 key_read(void);  
/* ������ ------------------------------------------------------------------*/
/**
  * @������       main
  * @��  ��       ���������
  * @��  ��       ��
  * @����ֵ       ��
  */
void main(void)
{
  u8 key;
 /*******************��ʼ����������������*************************/
  GPIO_Init(KEY_GPIO_PORT, (GPIO_Pin_TypeDef)KEY_GPIO_PINS, GPIO_MODE_IN_PU_NO_IT);
  if(!GPIO_ReadInputPin(KEY_GPIO_PORT,KEY_GPIO_PINS))
  {
    while(1);
  }
  GPIO_DeInit(KEY_GPIO_PORT);
 /****************************************************************/
  
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);        //����ϵͳʱ��HSI = 16M/1
  Delay(5000);
  LED_Init();
  KEY_Init();
  ADC1_Config();
  TIM4_Config();
  SHUMAGUAN_Init();

  enableInterrupts();   //ʹ�����ж� 
  
  while (1)
  {
    if(ms_10==1)
    {
      ms_10=0;
      data++;
      if(data>=10)
      {
        data=0;
        Conversion_Value = ADC1_GetConversionValue();
        discount(Conversion_Value,0);
      }
      /*ɨ�谴��*/
      key=key_read();
      if(key)
      {
          GPIO_WriteReverse(LED1_GPIO_PORT, (GPIO_Pin_TypeDef)LED1_GPIO_PINS); 
      }
    }
  }

}
void  display(u8 disnum,u8 disbit,u8 dotbit)  //��ʾ����ֵ���ڼ�λ��ʾ���Ƿ���˸���Ƿ��С����
{
      u8 discode;
      discode=CODE[disnum];
      if(dotbit==1)  discode=discode|0x80;
      if (disbit==1)  TM1652_Set(0x08,discode);//GR1
      else if (disbit==2)  TM1652_Set(0x88,discode);//GR2
      else if (disbit==3)  TM1652_Set(0x48,discode);//GR3
      else if (disbit==4)  TM1652_Set(0xc8,discode);//GR4
      else                 TM1652_Set(0x28,discode);//GR5       
      Delay(1800);      
 }
void  discount(s16 disdata,u8 dotbit)
{
      u8 i;
      u16 temp; 
      if(disdata>=0)//��
      {
        temp=disdata;
        if(temp>9999)
        {
          display(NUMf,1,0);
          display(NUMf,2,0);
          display(NUMf,3,0);
          display(NUMf,4,0);
        }
        else if((temp>999)||(dotbit==3))
        {
          i=temp/1000; 
          temp=temp%1000;
          if(dotbit==3) display(i,1,1);//ǧλ
          else          display(i,1,0);
          i=temp/100;
          temp=temp%100; //��λ
          if(dotbit==2) display(i,2,1);
          else          display(i,2,0);
          i=temp/10;
          temp=temp%10; //ʮλ
          if(dotbit==1) display(i,3,1);
          else          display(i,3,0);        
          display(temp,4,0); 
        }
        else if((temp>99)||(dotbit==2))
        {
          display(NUMx,1,0);
          i=temp/100;
          temp=temp%100; //��λ
          if(dotbit==2) display(i,2,1);
          else          display(i,2,0);
          i=temp/10;
          temp=temp%10; //ʮλ
          if(dotbit==1) display(i,3,1);
          else          display(i,3,0);        
          display(temp,4,0); 
        }
        else if((temp>9)||(dotbit==1))
        {
          display(NUMx,1,0);
          display(NUMx,2,0);
          i=temp/10;
          temp=temp%10; //ʮλ
          if(dotbit==1) display(i,3,1);
          else          display(i,3,0);        
          display(temp,4,0); 
        }   
        else
        {
          display(NUMx,1,0);
          display(NUMx,2,0);
          display(NUMx,3,0);
          display(temp,4,0); 
        }
      }
      else
      {
        temp=(u16)(-disdata);
        if(temp>999)
        {
          display(NUM_,1,0);
          display(NUMf,2,0);
          display(NUMf,3,0);
          display(NUMf,4,0);
        }
        else if((temp>99)||(dotbit==2))
        {
          display(NUM_,1,0);
          i=temp/100;
          temp=temp%100; //��λ
          if(dotbit==2) display(i,2,1);
          else          display(i,2,0);
          i=temp/10;
          temp=temp%10; //ʮλ
          if(dotbit==1) display(i,3,1);
          else          display(i,3,0);        
          display(temp,4,0); 
        }
        else if((temp>9)||(dotbit==1))
        {
          display(NUMx,1,0);
          display(NUM_,2,0);
          i=temp/10;
          temp=temp%10; //ʮλ
          if(dotbit==1) display(i,3,1);
          else          display(i,3,0);        
          display(temp,4,0); 
        }   
        else 
        {
          display(NUMx,1,0);
          display(NUMx,2,0);
          display(NUM_,3,0);
          display(temp,4,0); 
        }
      }
}
u8 key_read(void)  
{  
    static u8 key_state = 0;
    u8 key_press, key_return = 0;  
    key_press =KEY_Scan();                      // ������ֵ  
    switch (key_state)  
    {  
      case 0:                                 // ������ʼ̬  
        if (key_press)     key_state = 1;   // 1�������£�״̬ת��������������ȷ��״̬  
      break;  
        
      case 1:                      // ����������ȷ��̬  
        if (key_press)  
        {  
             key_state = 2;   // ������Ȼ���ڰ��£�������ɣ�״̬ת�������¼�ʱ��ļ�ʱ״̬�������صĻ����޼��¼�  
        }  
        else  
             key_state = 0;   // ������̧��ת����������ʼ̬���˴���ɺ�ʵ�������������ʵ�����İ��º��ͷŶ��ڴ������ġ�  
      break;  
      case 2:                 // �ȴ������ͷ�״̬����״ֻ̬�����ް����¼�  
        if (key_press==0) 
        {
          key_state = 0; //�������ͷţ�ת����������ʼ̬  
          key_return=1;
        }
      break;  
 
    }  
    
    return key_return;  
}  


/**
  * @������       Delay
  * @��  ��       ����ӳ�
  * @��  ��       nCount
  * @����ֵ       ��
  */
void Delay(uint32_t nCount)
{
  /* ���� nCount ֵ */
  while (nCount != 0)
  {
    nCount--;
  }
}


#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ Copyright (C)2017 LGG. All Rights Reserved *****END OF FILE****/
