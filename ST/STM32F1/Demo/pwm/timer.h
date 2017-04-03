#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdint.h>
#include "stm32f10x_tim.h"

void TIM3_Int_Init(uint16_t arr, uint16_t psc); 
void TIM3_IRQHandler(void); 
void TIM3_PWM_Init(uint16_t arr, uint16_t psc); 

#endif
