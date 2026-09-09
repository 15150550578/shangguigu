#include <stdint.h>
#include <stm32f4xx.h>
#include "led.h"
#include "delay.h"

int main(void)
{

  //1、初始化LED
  LED_Init();
  //2、定义一个LED数组
  uint16_t leds[] = {LED1, LED2, LED3};
  //3、循环点亮LED灯
    while (1) {
    for (uint8_t i = 0; i < sizeof(leds) / sizeof(leds[0]); i++) {
      LED_On(leds[i]);
      Delay_ms(500); // 延时500毫秒
      LED_Off(leds[i]);
      Delay_ms(500); // 延时500毫秒
    }
}
  }


