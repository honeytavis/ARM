#ifndef _KEY_H_
#define _KEY_H_

#include <stdint.h>

#define KEY0 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)
#define KEY1 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)
#define KEY2 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)
#define WK_UP GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)

#define KEY0_PRES 1
#define KEY1_PRES 2
#define KEY2_PRES 3
#define WKUP_PRES 4

void Key_Init(void); 
uint8_t Key_Scan(uint8_t mode); 

#endif
