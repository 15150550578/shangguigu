#include "system_stm32f4xx.h"

#define SCB_CPACR (*(volatile uint32_t *)0xE000ED88UL)

uint32_t SystemCoreClock = 16000000U;

void SystemInit(void)
{
    /* 打开 Cortex-M4 FPU，避免带 FPU 编译时进 HardFault */
    SCB_CPACR |= (0xFu << 20);
}
