#include <stdint.h>
#include <stm32f4xx.h>

#include "usart.h"
#include "delay.h"
uint8_t str[100]; //定义接收字符串的缓冲区
uint8_t length=0;
int main(void)
{

  //初始化串口
  USART_Init();
 
  while (1) 
  {
    USART_ReceiveString(str, &length); //接收字符串
    USART_SendString("Received: "); //发送提示信息
    USART_SendString(str); //发送字符串
  }
}



