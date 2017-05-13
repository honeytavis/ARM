///
/// @version 1.0 2017-04-05 10:50
/// @author Tavis
///

#include "stm32f10x.h"
// #include "misc.h"
// #include "stm32f10x_rcc.h"
// #include "stm32f10x_gpio.h"

// #define USART1_BAUDRATE 9600 
#define USART1_BAUDRATE 115200

void USART1_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct; 
  USART_InitTypeDef USART_InitStruct; 
	NVIC_InitTypeDef NVIC_InitStruct; 

// 使能 GPIOA USART 时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE);

// USART1_TXD GPIOA.9 
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;       // PA.9
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

// USART1_RXD GPIOA.10
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;            // PA.10
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING; // 浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStruct);

// USART1 Init
	USART_InitStruct.USART_BaudRate = USART1_BAUDRATE; 
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;   // 数据位8位
	USART_InitStruct.USART_StopBits = USART_StopBits_1;        // 停止位1位
	// USART_InitStruct.USART_Parity = USART_Parity_No;           // 无奇偶校验
	USART_InitStruct.USART_Parity = USART_Parity_Odd;           // 奇校验
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx; // 收发模式 
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_InitStruct);

// USART1 NVIC
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn; 
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3; // 抢占优先级 3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;        // 子优先级 3
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;           // IRQ通道使能
	NVIC_Init(&NVIC_InitStruct); 

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 

// 使能串口 
	USART_Cmd(USART1, ENABLE); 

}

void USART1_IRQHandler(void) {
	uint8_t res; 

	if (USART_GetITStatus(USART1, USART_IT_RXNE)) {
		res = USART_ReceiveData(USART1); 
		USART_SendData(USART1, res); 
	}
}
