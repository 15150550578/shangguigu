#include "delay.h"

void Delay_us(uint16_t us)
{
  SysTick->LOAD = us * 16U - 1U; // 设置计数值
  SysTick->VAL = 0U;
  SysTick->CTRL |= 0x05; // 使能SysTick定时器，选择处理器时钟作为时钟源
  while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0U); // 等待计数完成
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void Delay_ms(uint16_t ms)
{
  while(ms--)
  {
    Delay_us(1000); // 调用微秒延时函数
  }
}

void Delay_s(uint16_t s)
{
  while(s--)
  {
    Delay_ms(1000); // 调用毫秒延时函数
  }
}
