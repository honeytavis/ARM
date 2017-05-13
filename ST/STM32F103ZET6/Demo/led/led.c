#include "stm32f10x.h"
// #include "led.h"

void LED_Init(void) {
  GPIO_InitTypeDef GPIO_Init_Tag; 
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE , ENABLE);
  
  // LED0(red) --> PB.5
  GPIO_Init_Tag.GPIO_Pin  = GPIO_Pin_5; 
  GPIO_Init_Tag.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init_Tag.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOB, &GPIO_Init_Tag); 
  GPIO_SetBits(GPIOB, GPIO_Pin_5); 
  
  // LED1(blue) --> PE.5
  GPIO_Init_Tag.GPIO_Pin  = GPIO_Pin_5; 
  GPIO_Init_Tag.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init_Tag.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOE, &GPIO_Init_Tag); 
  GPIO_SetBits(GPIOE, GPIO_Pin_5); 
}
