///
/// @version 1.0 2017-03-22 21:09
/// @author Tavis
///

#include "led.h"
#include "io.h"
#include "stm32f10x.h"

void Delay(uint32_t count) {
	for (; count > 1; --count); 
}

int main()
{
	uint8_t X0 = 0;
	uint8_t X1 = 0;

  IO_Init();  
	LED_Init(); 

  for (; ;) {
		X0 = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9); 
		X1 = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10); 

	  if (X1 && X0) {
	  		GPIO_SetBits(GPIOA, GPIO_Pin_0); 
	  		GPIO_ResetBits(GPIOA, GPIO_Pin_2); 
	  		GPIO_ResetBits(GPIOA, GPIO_Pin_4); 
	  		GPIO_SetBits(GPIOA, GPIO_Pin_6); 
	  		GPIO_SetBits(GPIOC, GPIO_Pin_13); 
		} else if (X1 && (!X0)) {
	  		GPIO_ResetBits(GPIOA, GPIO_Pin_0); 
	  		GPIO_SetBits(GPIOA, GPIO_Pin_2); 
	  		GPIO_ResetBits(GPIOA, GPIO_Pin_4); 
	  		GPIO_SetBits(GPIOA, GPIO_Pin_6); 
	  		GPIO_SetBits(GPIOC, GPIO_Pin_13); 
		} else if ((!X1) && X0) {
	  		GPIO_ResetBits(GPIOA, GPIO_Pin_0); 
	  		GPIO_ResetBits(GPIOA, GPIO_Pin_2); 
	  		GPIO_SetBits(GPIOA, GPIO_Pin_4); 
	  		GPIO_SetBits(GPIOA, GPIO_Pin_6); 
	  		GPIO_SetBits(GPIOC, GPIO_Pin_13); 
		} else {
	  		GPIO_SetBits(GPIOA, GPIO_Pin_0); 
	  		GPIO_ResetBits(GPIOA, GPIO_Pin_2); 
	  		GPIO_ResetBits(GPIOA, GPIO_Pin_4); 
	  		GPIO_ResetBits(GPIOA, GPIO_Pin_6); 
	  		GPIO_ResetBits(GPIOC, GPIO_Pin_13); 
		}

		Delay(0xfffff); 
	}
  
  return 0;
}
