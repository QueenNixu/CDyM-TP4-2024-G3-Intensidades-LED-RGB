#include "LED.h"
#include "PWM.h"

volatile uint8_t red_intensity = 0;
volatile uint8_t green_intensity = 0;
volatile uint8_t blue_intensity = 0;
volatile char current_color = 'B';

void update_color_intensity(uint16_t adc_value) {
	uint16_t intensity = adc_value / 4;
	switch (current_color) {
		case 'R':
		red_intensity = intensity;
		setPWM_red(red_intensity);
		break;
		case 'G':
		green_intensity = intensity;
		setPWM_green(green_intensity);
		break;
		case 'B':
		blue_intensity = intensity;
		setPWM_blue(blue_intensity);
		break;
	}
}

void setPWM_red(uint8_t red) {
	PWM_delta = 255 - red; // Ajusta el valor de PWM_delta para controlar la intensidad del rojo
}

void setPWM_green(uint8_t green) {
	OCR1B = 255 - green; // Invertir el valor para el ánodo común
}

void setPWM_blue(uint8_t blue) {
	OCR1A = 255 - blue; // Invertir el valor para el ánodo común
}

void LED_init() {
	setPWM_red(0);
	setPWM_green(0);
	setPWM_blue(0);
}