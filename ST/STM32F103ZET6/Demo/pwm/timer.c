#include "timer.h"
#include "led.h"
#include "usart.h"

// 通用定时器3中断初始化
// 时钟选择为APB1的2倍， 而APB1为36M
// arr: 自动重装值 psc 时钟预分频数
void TIM3_Int_Init(uint16_t arr, uint16_t psc) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct; 
	NVIC_InitTypeDef NVIC_InitStruct; 
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	
	TIM_TimeBaseStruct.TIM_Period = arr;
	TIM_TimeBaseStruct.TIM_Prescaler = psc; 
	TIM_TimeBaseStruct.TIM_ClockDivision = 0; 
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct); 
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // 使能指定的TIM3中断 允许更新中断
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn; 
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3; 
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStruct); 
	
	TIM_Cmd(TIM3, ENABLE); // 使能TIMx外设
}

// TIM3中断服务程序
void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); // 清楚TIMx的中断待处理位
		LED1 = (!LED1);
	}
}

// TIM3 PWM部分初始化
// PWM输出初始化
// arr 自动重装值
// psc 时钟预分频数
void TIM3_PWM_Init(uint16_t arr, uint16_t psc) {
	GPIO_InitTypeDef GPIO_InitStruct; 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct; 
	TIM_OCInitTypeDef TIM_OCInitStruct; 
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); 
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); // Timer3 部分重映射 TIM3_CH2 -> PB5
	
	// 使用GPIOB.5复用输出功能 输出TIM3_CH2的PWM脉冲波形 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStruct); 
	
	// 初始化TIM3
	TIM_TimeBaseStruct.TIM_Period = arr; 
	TIM_TimeBaseStruct.TIM_Prescaler = psc; 
	TIM_TimeBaseStruct.TIM_ClockDivision = 0; 
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct); 
	
	// 初始化TIM3 CH12 PWM 模式
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC2Init(TIM3, &TIM_OCInitStruct); 
	
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	 
	TIM_Cmd(TIM3, ENABLE); 
}
