#ifndef LED_H
#define LED_H

#include <avr/io.h>

void update_color_intensity(uint16_t adc_value);
void setPWM_red(uint8_t red);
void setPWM_green(uint8_t green);
void setPWM_blue(uint8_t blue);
void LED_init(void);

#endif
