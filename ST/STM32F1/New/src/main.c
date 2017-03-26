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

void LED_Blink(void); 
void TIM3_PWM(uint16_t arr, uint16_t psc); 

int main()
{
  delay_init(); 

  LED_Blink(); 
  // TIM3_PWM(7199, 0); // 72000/7200 = 10KHz 
  
  return 0;
}

void TIM3_PWM(uint16_t arr, uint16_t psc) {
  uint16_t led0Brightness = 0; 
  uint8_t status = 1; 

  TIM3_PWM_Init(arr, 0); 
  TIM_SetCompare2(TIM3, led0Brightness); 

  for (; ;) {
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


void LED_Blink(void) {
  LED_Init(); 

  // for (; ;) {
  //   GPIO_ResetBits(GPIOB, GPIO_Pin_5); 
  //   GPIO_ResetBits(GPIOE, GPIO_Pin_5); 
  //   delay_ms(100); 

  //   GPIO_SetBits(GPIOB, GPIO_Pin_5); 
  //   GPIO_SetBits(GPIOE, GPIO_Pin_5); 
  //   delay_ms(100); 
  // }

  for (; ;) {
    PBout(5) = 1; 
    PEout(5) = 1; 
    delay_ms(100); 

    PBout(5) = 0; 
    PEout(5) = 0; 
    delay_ms(100); 
  }
}
