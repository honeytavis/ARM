#include "delay.h"
#include "sys.h"

#if SYSTEM_SUPPORT_UCOS
#include "includes.h"
#endif

static uint8_t  fac_us = 0;
static uint16_t fac_ms = 0;

#ifdef OS_CRITICAL_METHOD
void SysTick_Handler(void) {				   
  OSIntEnter();
  OSTimeTick();
  OSIntExit(); 
}
#endif

void delay_init() {
#ifdef OS_CRITICAL_METHOD
	uint32_t reload;
#endif
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); // 外部时钟 HCLK/8
	fac_us = SystemCoreClock/8000000;
	 
#ifdef OS_CRITICAL_METHOD
	reload = SystemCoreClock/8000000;
	reload *= 1000000/OS_TICKS_PER_SEC;
	fac_ms = 1000/OS_TICKS_PER_SEC;
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	SysTick->LOAD  = reload;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
#else
	fac_ms = (uint16_t)fac_us*1000;
#endif
}								    

#ifdef OS_CRITICAL_METHOD
void delay_us(uint32_t N) {		
	uint32_t ticks;
	uint32_t told, tnow, tcnt=0;
	uint32_t reload = SysTick->LOAD;

	ticks = N*fac_us;
	tcnt = 0;
	told = SysTick->VAL;

	for (;;) {
		tnow = SysTick->VAL;	
		if (tnow != told) {	    
			if(tnow < told) {
				tcnt += told-tnow;
			} else {
				tcnt += reload-tnow+told;	    
			}
			told = tnow;
			if(tcnt >= ticks) {
				break;
			}
		}
	} // for
}

void delay_ms(uint16_t N) {
	if(OSRunning == TRUE) {
		if(N >= fac_ms) {
			OSTimeDly(N/fac_ms);
		}
		N %= fac_ms;
	}
	delay_us((uint32_t)(N*1000));
}

#else
void delay_us(uint32_t N) {
	uint32_t temp;
	SysTick->LOAD = N*fac_us;
	SysTick->VAL = 0x00;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	do {
		temp = SysTick->CTRL;
	} while ((temp&0x01) && (!(temp&(1<<16))));

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL = 0X00;
}

void delay_ms(uint16_t N) {	 		  	  
	uint32_t temp;		   
	SysTick->LOAD = (uint32_t)N*fac_ms;
	SysTick->VAL = 0x00;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	do {
		temp = SysTick->CTRL;
	} while ((temp&0x01) && (!(temp&(1<<16))));

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL = 0X00;
} 

#endif
