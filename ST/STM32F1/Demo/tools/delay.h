#ifndef _DELAY_H_
#define _DELAY_H_

#include "stdint.h"

void delay_init(void);
void delay_ms(uint16_t N);
void delay_us(uint32_t N);

#endif
