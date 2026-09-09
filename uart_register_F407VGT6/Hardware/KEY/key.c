#include "key.h"

void KEY_Init(void)
{
    //配置时钟
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; //使能GPIOA时钟
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; //使能系统配置控制器时钟
    
    //2.GPIO工作模式配置：输入=00。MODER0_0 是 01，那是输出模式
    GPIOA->MODER &= ~GPIO_MODER_MODER0;
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0;
    GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_1; //PA0下拉，未按下为低，按下WK_UP为高

    //3.中断配置
    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0; //清除EXTI0的映射
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA; //将EXTI0映射到PA0

    //4.配置EXTI
    EXTI->RTSR |= EXTI_RTSR_TR0; //上升沿触发
    EXTI->IMR |= EXTI_IMR_MR0; //使能中断请求
    
    //5.配置NVIC
    NVIC_SetPriorityGrouping(3); //设置中断优先级分组
    NVIC_SetPriority(EXTI0_IRQn, 2); //设置中断优先级
    NVIC_EnableIRQ(EXTI0_IRQn); //使能中断
}


//中断服务函数
void EXTI0_IRQHandler(void)
{
    if (EXTI->PR & EXTI_PR_PR0) //检查中断挂起标志
    {
        Delay_ms(10); //先消抖，再判断、再清标志，避免抖动连进两次中断
        if ((GPIOA->IDR & GPIO_IDR_IDR_0) != 0) //PA0仍为高，确认是按下
        {
            LED_Toggle(LED1);
        }
        EXTI->PR = EXTI_PR_PR0; //延时后再清，把抖动产生的挂起位一并清掉
    }
}
