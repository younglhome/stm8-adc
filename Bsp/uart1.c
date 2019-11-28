/**
  ******************************************************************************
  * @�ļ�         uart1.c
  * @����         LGG
  * @�汾         V1.0.0
  * @����         2017-11-18
  * @ժҪ         uart1Դ�ļ�
  ******************************************************************************
*/ 

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "uart1.h"
#include "stdio.h"
#include "string.h"
#include "assert.h"

/**
  * @������       UART1_Config
  * @��  ��       ����UART1�볬���ն�ͨѶ
  * @��  ��       ��
  * @����ֵ       ��
  */
void UART1_Config(void)
{
  /* EVAL COM (UART) configuration -----------------------------------------*/
  /* USART configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - None parity
        - Receive and transmit enabled
        - UART Clock disabled
  */
  UART1_Init((uint32_t)115200, UART1_WORDLENGTH_8D,UART1_STOPBITS_1, UART1_PARITY_NO,
                   UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);

  /* ʹ�ܽ����ж� */
  UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
  
  /* ʹ�ܷ����ж� */
  UART1_ITConfig(UART1_IT_TXE, ENABLE);

  /* ʹ�� UART1 */
  UART1_Cmd(ENABLE);
  
}

static void Delay(uint32_t nCount)
{
  /* ���� nCount ֵ */
  while (nCount != 0)
  {
    nCount--;
  }
}

void UART1_SendByte(uint8_t byte)
{
    UART1_SendData8(byte);
    Delay(UART1_SEND_DELAY_COUNT); 
}


void UART1_Send_IntToStr(uint16_t num)
{
    char buffer [17];
    // itoa(num, buffer, 10);
    sprintf(buffer,"%d",num);
    for (int i = 0; i < strlen(buffer); ++i)
    {
      UART1_SendByte(buffer[i]);
    }
}

void UART1_printf(char* str)
{
    assert(str != NULL);
    for (int i = 0; i < strlen(str); ++i)
    {
      UART1_SendByte(str[i]);
    }
}

/************************ Copyright (C)2017 LGG. All Rights Reserved *****END OF FILE****/


