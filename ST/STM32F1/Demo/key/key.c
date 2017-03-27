///
/// @version 1.0 2017-03-27 15:17
/// @author Tavis
///

#include "stm32f10x.h"
#include "key.h"
#include "delay.h"

void Key_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4; // KEY0 -> KEY2
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // Input Pull Up
	GPIO_Init(GPIOE, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; // Input Pull Down
	GPIO_Init(GPIOA, &GPIO_InitStruct);

}

uint8_t Key_Scan(uint8_t mode) {
	static uint8_t key_up = 1; // 按键松开标志

	if (mode)
		key_up = 1;

	if (key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || WK_UP == 1)) { // 有按键按下
		delay_ms(5); // 去抖
		key_up = 0;
		
		if (KEY0 == 0) {
			return KEY0_PRES; // KEY0 被按下
		} else if (KEY1 == 0) {
			return KEY1_PRES; // KEY1 被按下
		} else if (KEY2 == 0) {
			return KEY2_PRES; // KEY2 被按下
		} else if (WK_UP == 1) {
			return WKUP_PRES; // WK_UP 被按下  
		} 
	} else if ((KEY0 == 1) && (KEY1 == 1) && (KEY2 == 1) && (WK_UP == 0)) { // 所有按键都弹开
		key_up = 1; 
	}
	return 0; // 无按键被按下
}
