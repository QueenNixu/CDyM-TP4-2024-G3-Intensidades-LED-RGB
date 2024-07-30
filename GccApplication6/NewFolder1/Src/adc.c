#include "ADC.h"

void ADC_Init(void) {
	ADMUX = (1<<REFS0); // AVcc como referencia
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // Habilitar el ADC y establecer el prescaler a 128 (para una frecuencia de reloj de 16 MHz)
}

uint16_t ADC_Read(uint8_t channel) {
	
	channel &= 0x07; // Seleccionar el canal ADC (enmascarar los 3 bits más bajos del canal)
	ADMUX = (ADMUX & 0xF8) | channel;

	ADCSRA |= (1<<ADSC); // Iniciar la conversión
	while (ADCSRA & (1<<ADSC)); // Esperar a que la conversión termine
	return ADCW; // Devolver el valor entero del ADC
}
