#include "led.h"

//初始化
void LED_Init(void)
{
    RCC->AHB1ENR |=1;
	RCC->AHB1ENR |=RCC_AHB1ENR_GPIOAEN;

	//设置GPIOA1模式为通用输出模式
	GPIOA->MODER &= ~GPIO_MODER_MODER1; 
	GPIOA->MODER |=GPIO_MODER_MODER1_0;

    //设置GPIOA2模式为通用输出模式
    GPIOA->MODER &= ~GPIO_MODER_MODER2;
    GPIOA->MODER |= GPIO_MODER_MODER2_0;
    LED_On(LED1);
    LED_Off(LED2);
}

//控制LED开关
void LED_On(uint16_t led)
{
    GPIOA->ODR &= ~led; // 设置对应的LED引脚为低电平，点亮LED
}

void LED_Off(uint16_t led)
{   
    GPIOA->ODR |= led; // 设置对应的LED引脚为高电平，熄灭LED
}

//翻转LED状态
void LED_Toggle(uint16_t led)
{
    GPIOA->ODR ^= led;
}

//对一组LED灯，全开全关
void LED_AllOn(uint16_t leds[], uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        LED_On(leds[i]);
    }
}

void LED_AllOff(uint16_t leds[], uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        LED_Off(leds[i]);
    }
}