#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>
#include <stm32f4xx.h>

void Delay_us(uint16_t us);
void Delay_ms(uint16_t ms);
void Delay_s(uint16_t s);

#endif // DELAY_H
