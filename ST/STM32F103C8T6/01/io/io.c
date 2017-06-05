///
/// @version 1.0 2017-05-18 15:45
/// @author Tavis
///

#include "io.h"
#include "stm32f10x.h"

void IO_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct; 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
	
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6; 
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
}
