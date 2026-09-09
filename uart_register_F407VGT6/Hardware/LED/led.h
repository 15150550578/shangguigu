#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"

#define LED1 GPIO_ODR_ODR_1
#define LED2 GPIO_ODR_ODR_2

//初始化
void LED_Init(void);

//控制LED开关
void LED_On(uint16_t led);
void LED_Off(uint16_t led);
//翻转LED状态
void LED_Toggle(uint16_t led);


//对一组LED灯，全开全关
void LED_AllOn(uint16_t leds[], uint8_t size);
void LED_AllOff(uint16_t leds[], uint8_t size);
#endif /* __LED_H */
