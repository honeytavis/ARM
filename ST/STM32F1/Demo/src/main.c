///
/// @version 1.0 2017-03-22 21:09
/// @author Tavis
///

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stdint.h"
#include "delay.h"
#include "led.h"
#include "timer.h"
#include "key.h"
#include "beep.h"

void LED_Blink(void); 
void Beep(void); 
void Key_Press(void); 
void TIM3_PWM(uint16_t arr, uint16_t psc); 

int main()
{

  // LED_Blink(); 
	// Beep(); 
  // TIM3_PWM(7199, 0); // 72000/7200 = 10KHz 
	Key_Press(); 
  
  return 0;
}

void LED_Blink(void) {
  delay_init(); 
  LED_Init(); 

  // for (;;) {
  //   GPIO_ResetBits(GPIOB, GPIO_Pin_5); 
  //   GPIO_ResetBits(GPIOE, GPIO_Pin_5); 
  //   delay_ms(100); 

  //   GPIO_SetBits(GPIOB, GPIO_Pin_5); 
  //   GPIO_SetBits(GPIOE, GPIO_Pin_5); 
  //   delay_ms(100); 
  // }

  for (;;) {
    PBout(5) = 1; 
    PEout(5) = 1; 
    delay_ms(100); 

    PBout(5) = 0; 
    PEout(5) = 0; 
    delay_ms(100); 
  }
}

void Beep(void) {
  delay_init(); 
	Beep_Init(); 

	for (;;) {
		GPIO_SetBits(GPIOB, GPIO_Pin_8); 
		delay_ms(100); 

		GPIO_ResetBits(GPIOB, GPIO_Pin_8); 
		delay_ms(100); 
	}
}

void Key_Press(void) {
	uint8_t key = 0; 

  delay_init(); 
	LED_Init(); 
	Key_Init(); 
	Beep_Init(); 

	LED0 = 0; 

	for (;;) {
		key = Key_Scan(0); 
		if (key) {
			switch(key) {
				case KEY0_PRES: LED0 = !LED0; break; // LED0 翻转
				case KEY1_PRES: LED1 = !LED1; break; // LED1 翻转
				case KEY2_PRES: LED0 = !LED0; LED1 = !LED1; break; // LED0 LED1 同时翻转
				case WKUP_PRES: BEEP = !BEEP; break;

			}
		}
		delay_ms(100); // 采样频率
	}
}

void TIM3_PWM(uint16_t arr, uint16_t psc) {
  uint16_t led0Brightness = 0; 
  uint8_t status = 1; 

  TIM3_PWM_Init(arr, 0); 
  TIM_SetCompare2(TIM3, led0Brightness); 

  delay_init(); 

  for (;;) {
    if (status) {
      led0Brightness += 100; 
      TIM_SetCompare2(TIM3, led0Brightness); 
      delay_ms(100); 
      if (led0Brightness > arr) {
        status = 0; 
      }
    } else {
      led0Brightness -= 100; 
      TIM_SetCompare2(TIM3, led0Brightness); 
      delay_ms(100); 
      if (led0Brightness < 1) {
        status = 1; 
      }
    }
  }
}
