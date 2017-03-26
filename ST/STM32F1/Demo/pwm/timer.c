#include "timer.h"
#include "led.h"
#include "usart.h"

// ͨ�ö�ʱ��3�жϳ�ʼ��
// ʱ��ѡ��ΪAPB1��2���� ��APB1Ϊ36M
// arr: �Զ���װֵ psc ʱ��Ԥ��Ƶ��
void TIM3_Int_Init(uint16_t arr, uint16_t psc) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct; 
	NVIC_InitTypeDef NVIC_InitStruct; 
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	
	TIM_TimeBaseStruct.TIM_Period = arr;
	TIM_TimeBaseStruct.TIM_Prescaler = psc; 
	TIM_TimeBaseStruct.TIM_ClockDivision = 0; 
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct); 
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); // ʹ��ָ����TIM3�ж� ��������ж�
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn; 
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3; 
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStruct); 
	
	TIM_Cmd(TIM3, ENABLE); // ʹ��TIMx����
}

// TIM3�жϷ������
void TIM3_IRQHandler(void) {
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update); // ���TIMx���жϴ�����λ
		LED1 = (!LED1);
	}
}

// TIM3 PWM���ֳ�ʼ��
// PWM�����ʼ��
// arr �Զ���װֵ
// psc ʱ��Ԥ��Ƶ��
void TIM3_PWM_Init(uint16_t arr, uint16_t psc) {
	GPIO_InitTypeDef GPIO_InitStruct; 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct; 
	TIM_OCInitTypeDef TIM_OCInitStruct; 
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); 
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); // Timer3 ������ӳ�� TIM3_CH2 -> PB5
	
	// ʹ��GPIOB.5����������� ���TIM3_CH2��PWM���岨�� 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStruct); 
	
	// ��ʼ��TIM3
	TIM_TimeBaseStruct.TIM_Period = arr; 
	TIM_TimeBaseStruct.TIM_Prescaler = psc; 
	TIM_TimeBaseStruct.TIM_ClockDivision = 0; 
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStruct); 
	
	// ��ʼ��TIM3 CH12 PWM ģʽ
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC2Init(TIM3, &TIM_OCInitStruct); 
	
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	 
	TIM_Cmd(TIM3, ENABLE); 
}
