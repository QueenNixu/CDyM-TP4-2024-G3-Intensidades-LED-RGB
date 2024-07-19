#ifndef PWM_H
#define PWM_H

#include <avr/io.h>

extern volatile uint8_t PWM_delta;

void PWM_Init(void);
void PWM_soft_Update(void);
void Timer0_Init(void);

#endif
