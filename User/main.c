/******************** (C) COPYRIGHT  喆帆电子    ***************************
 * 文件名    ：main.c
 * 描述      ：主函数  
 * 实验平台  ：STM8s001J3开发板
 * 作者      ：wagnjin  QQ：28669816
 * 淘宝店铺  ：https://shop33781225.taobao.com
 *修改时间   ：2018-05-03
***************************************************************************/
/* 包含头文件 ----------------------------------------------------------------*/
#include "stm8s.h"
#include "tim4.h"
#include "led.h"
#include "stm8s_it.h"
#include "tm1652.h"
#include "key.h"
#include "adc1.h"
/* 数值定义 ----------------------------------------------------------------*/
uint16_t  data;

u8 CODE[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f, //0~9显示代码
             0x77,0x7c,0x58,0x5e,0x79,0x71,                     //a~f显示代码
             0x6f,0x76,0x04,0x38,0x54,0x5c,0x73,0x50,0x6d,0x78,0x1c,0x3e,0x00,0x6e,0x40}; 
             //g   H     i   L    n    o     p    r    s    t   u    U          y   -

/* 函数声明 ------------------------------------------------------------------*/
void  Delay(uint32_t nCount);
void  display(u8 disnum,u8 disbit,u8 dotbit);
void  discount(s16 disdata,u8 dotbit);
void  disfun(void);
u8 key_read(void);  
/* 主函数 ------------------------------------------------------------------*/
/**
  * @函数名       main
  * @功  能       主函数入口
  * @参  数       无
  * @返回值       无
  */
void main(void)
{
  u8 key;
 /*******************初始化按键，防锁代码*************************/
  GPIO_Init(KEY_GPIO_PORT, (GPIO_Pin_TypeDef)KEY_GPIO_PINS, GPIO_MODE_IN_PU_NO_IT);
  if(!GPIO_ReadInputPin(KEY_GPIO_PORT,KEY_GPIO_PINS))
  {
    while(1);
  }
  GPIO_DeInit(KEY_GPIO_PORT);
 /****************************************************************/
  
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);        //配置系统时钟HSI = 16M/1
  Delay(5000);
  LED_Init();
  KEY_Init();
  ADC1_Config();
  TIM4_Config();
  SHUMAGUAN_Init();

  enableInterrupts();   //使能总中断 
  
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
      /*扫描按键*/
      key=key_read();
      if(key)
      {
          GPIO_WriteReverse(LED1_GPIO_PORT, (GPIO_Pin_TypeDef)LED1_GPIO_PINS); 
      }
    }
  }

}
void  display(u8 disnum,u8 disbit,u8 dotbit)  //显示的数值，第几位显示，是否闪烁，是否带小数点
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
      if(disdata>=0)//正
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
          if(dotbit==3) display(i,1,1);//千位
          else          display(i,1,0);
          i=temp/100;
          temp=temp%100; //百位
          if(dotbit==2) display(i,2,1);
          else          display(i,2,0);
          i=temp/10;
          temp=temp%10; //十位
          if(dotbit==1) display(i,3,1);
          else          display(i,3,0);        
          display(temp,4,0); 
        }
        else if((temp>99)||(dotbit==2))
        {
          display(NUMx,1,0);
          i=temp/100;
          temp=temp%100; //百位
          if(dotbit==2) display(i,2,1);
          else          display(i,2,0);
          i=temp/10;
          temp=temp%10; //十位
          if(dotbit==1) display(i,3,1);
          else          display(i,3,0);        
          display(temp,4,0); 
        }
        else if((temp>9)||(dotbit==1))
        {
          display(NUMx,1,0);
          display(NUMx,2,0);
          i=temp/10;
          temp=temp%10; //十位
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
          temp=temp%100; //百位
          if(dotbit==2) display(i,2,1);
          else          display(i,2,0);
          i=temp/10;
          temp=temp%10; //十位
          if(dotbit==1) display(i,3,1);
          else          display(i,3,0);        
          display(temp,4,0); 
        }
        else if((temp>9)||(dotbit==1))
        {
          display(NUMx,1,0);
          display(NUM_,2,0);
          i=temp/10;
          temp=temp%10; //十位
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
    key_press =KEY_Scan();                      // 读按键值  
    switch (key_state)  
    {  
      case 0:                                 // 按键初始态  
        if (key_press)     key_state = 1;   // 1键被按下，状态转换到按键消抖和确认状态  
      break;  
        
      case 1:                      // 按键消抖与确认态  
        if (key_press)  
        {  
             key_state = 2;   // 按键仍然处于按下，消抖完成，状态转换到按下键时间的计时状态，但返回的还是无键事件  
        }  
        else  
             key_state = 0;   // 按键已抬起，转换到按键初始态。此处完成和实现软件消抖，其实按键的按下和释放都在此消抖的。  
      break;  
      case 2:                 // 等待按键释放状态，此状态只返回无按键事件  
        if (key_press==0) 
        {
          key_state = 0; //按键已释放，转换到按键初始态  
          key_return=1;
        }
      break;  
 
    }  
    
    return key_return;  
}  


/**
  * @函数名       Delay
  * @功  能       软件延迟
  * @参  数       nCount
  * @返回值       无
  */
void Delay(uint32_t nCount)
{
  /* 减少 nCount 值 */
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
